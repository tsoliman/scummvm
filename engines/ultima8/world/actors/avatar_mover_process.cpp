/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#include "ultima8/misc/pent_include.h"
#include "ultima8/world/actors/avatar_mover_process.h"
#include "ultima8/world/actors/animation.h"
#include "ultima8/kernel/gui_app.h"
#include "ultima8/world/actors/main_actor.h"
#include "ultima8/gumps/game_map_gump.h"
#include "ultima8/kernel/kernel.h"
#include "ultima8/world/actors/actor_anim_process.h"
#include "ultima8/world/actors/targeted_anim_process.h"
#include "ultima8/world/actors/avatar_gravity_process.h"
#include "ultima8/graphics/shape_info.h"
#include "ultima8/conf/setting_manager.h"
#include "ultima8/audio/music_process.h"
#include "ultima8/world/get_object.h"
#include "ultima8/filesys/idata_source.h"
#include "ultima8/filesys/odata_source.h"
#include "common/system.h"

namespace Ultima8 {

// p_dynamic_cast stuff
DEFINE_RUNTIME_CLASSTYPE_CODE(AvatarMoverProcess, Process)

AvatarMoverProcess::AvatarMoverProcess() : Process() {
	lastframe = 0;
	lastAttack = 0;
	idleTime = 0;
	lastHeadShakeAnim = Animation::lookLeft;
	mouseButton[0].state = MBS_HANDLED | MBS_RELHANDLED;
	mouseButton[1].state = MBS_HANDLED | MBS_RELHANDLED;
	mouseButton[0].curDown = 0;
	mouseButton[1].curDown = 0;
	mouseButton[0].lastDown = 0;
	mouseButton[1].lastDown = 0;
	type = 1; // CONSTANT! (type 1 = persistent)
}


AvatarMoverProcess::~AvatarMoverProcess() {

}

void AvatarMoverProcess::run() {
	Kernel *kernel = Kernel::get_instance();
	uint32 framenum = kernel->getFrameNum();

	// only run once per frame
	if (framenum == lastframe)
		return;
	lastframe = framenum;


	MainActor *avatar = getMainActor();

	// busy, so don't move
	if (kernel->getNumProcesses(1, 0x00F0) > 0) {
		idleTime = 0;
		return;
	}


	if (avatar->getLastAnim() == Animation::hang) {
		handleHangingMode();
		return;
	}

	// falling, so don't move
	if (avatar->getGravityPID() != 0) {
		idleTime = 0;
		return;
	}

	bool combatRun = (avatar->getActorFlags() & Actor::ACT_COMBATRUN) != 0;
	if (avatar->isInCombat() && !combatRun)
		handleCombatMode();
	else
		handleNormalMode();
}

void AvatarMoverProcess::handleHangingMode() {
	GUIApp *guiapp = GUIApp::get_instance();
	MainActor *avatar = getMainActor();
	uint32 now = g_system->getMillis();
	bool stasis = guiapp->isAvatarInStasis();

	idleTime = 0;

	if (stasis) return;

	bool m0clicked = false;
	bool m1clicked = false;
	if (!(mouseButton[0].state & MBS_HANDLED) &&
	        now - mouseButton[0].curDown > DOUBLE_CLICK_TIMEOUT) {
		m0clicked = true;
		mouseButton[0].state |= MBS_HANDLED;
	}
	if (!(mouseButton[1].state & MBS_HANDLED) &&
	        now - mouseButton[1].curDown > DOUBLE_CLICK_TIMEOUT) {
		m1clicked = true;
		mouseButton[1].state |= MBS_HANDLED;
	}
	if (!(mouseButton[0].state & MBS_RELHANDLED))
		mouseButton[0].state |= MBS_RELHANDLED;
	if (!(mouseButton[1].state & MBS_RELHANDLED))
		mouseButton[1].state |= MBS_RELHANDLED;


	// if left mouse is down, try to climb up

	if ((mouseButton[0].state & MBS_DOWN) &&
	        (!(mouseButton[0].state & MBS_HANDLED) || m0clicked)) {
		mouseButton[0].state |= MBS_HANDLED;
		mouseButton[0].lastDown = 0;

		if (avatar->tryAnim(Animation::climb40, 8) == Animation::SUCCESS) {
			avatar->ensureGravityProcess()->terminate();
			waitFor(avatar->doAnim(Animation::climb40, 8));
		}
	}
}

void AvatarMoverProcess::handleCombatMode() {
	GUIApp *guiapp = GUIApp::get_instance();
	MainActor *avatar = getMainActor();
	Animation::Sequence lastanim = avatar->getLastAnim();
	Animation::Sequence nextanim = Animation::walk;
	int32 direction = avatar->getDir();
	uint32 now = g_system->getMillis();
	bool stasis = guiapp->isAvatarInStasis();

	int mx, my;
	guiapp->getMouseCoords(mx, my);
	unsigned int mouselength = guiapp->getMouseLength(mx, my);

	// adjust to world direction
	int32 mousedir = (guiapp->getMouseDirection(mx, my) + 7) % 8;

	// never idle when in combat
	idleTime = 0;

	// If Avatar has fallen down, stand up.
	if (lastanim == Animation::die || lastanim == Animation::fallBackwards) {
		if (!stasis)
			waitFor(avatar->doAnim(Animation::standUp, mousedir));
		return;
	}

	// if we were blocking, and no longer holding the mouse, stop
	if (lastanim == Animation::startBlock &&
	        !(mouseButton[0].state & MBS_DOWN)) {
//		pout << "AvatarMover: combat stop blocking" << std::endl;
		waitFor(avatar->doAnim(Animation::stopBlock, direction));
		return;
	}

	// can't do any new actions if in stasis
	if (stasis)
		return;

	bool m0clicked = false;
	bool m1clicked = false;

	if (!(mouseButton[0].state & MBS_HANDLED) &&
	        now - mouseButton[0].curDown > DOUBLE_CLICK_TIMEOUT) {
		m0clicked = true;
		mouseButton[0].state |= MBS_HANDLED;
	}

	if (!(mouseButton[1].state & MBS_HANDLED) &&
	        now - mouseButton[1].curDown > DOUBLE_CLICK_TIMEOUT) {
		m1clicked = true;
		mouseButton[1].state |= MBS_HANDLED;
	}

	if (!(mouseButton[0].state & MBS_RELHANDLED))
		mouseButton[0].state |= MBS_RELHANDLED;

	if (!(mouseButton[1].state & MBS_RELHANDLED))
		mouseButton[1].state |= MBS_RELHANDLED;

	if ((mouseButton[0].state & MBS_DOWN) &&
	        (mouseButton[0].state & MBS_HANDLED) && mouseButton[0].lastDown > 0) {
		// left click-and-hold = block
		if (lastanim == Animation::startBlock)
			return;

//		pout << "AvatarMover: combat block" << std::endl;

		if (checkTurn(mousedir, false)) return;

		waitFor(avatar->doAnim(Animation::startBlock, mousedir));
		return;
	}

	if ((mouseButton[0].state & MBS_DOWN) &&
	        !(mouseButton[0].state & MBS_HANDLED) &&
	        mouseButton[0].curDown - mouseButton[0].lastDown <= DOUBLE_CLICK_TIMEOUT) {
		mouseButton[0].state |= MBS_HANDLED;
		mouseButton[0].lastDown = 0;

		if (canAttack()) {
			// double left click = attack
//			pout << "AvatarMover: combat attack" << std::endl;

			if (checkTurn(mousedir, true)) return;

			waitFor(avatar->doAnim(Animation::attack, mousedir));
			lastAttack = lastframe;

			// attacking gives str/dex
			avatar->accumulateStr(1 + (std::rand() % 2));
			avatar->accumulateDex(2 + (std::rand() % 2));
		}

		return;
	}

	if ((mouseButton[1].state & MBS_DOWN) &&
	        !(mouseButton[1].state & MBS_HANDLED) &&
	        mouseButton[1].curDown - mouseButton[1].lastDown <= DOUBLE_CLICK_TIMEOUT) {
		mouseButton[1].state |= MBS_HANDLED;
		mouseButton[1].lastDown = 0;

		Gump *desktopgump = GUIApp::get_instance()->getDesktopGump();
		if (desktopgump->TraceObjId(mx, my) == 1) {
			// double right click on avatar = toggle combat mode
			avatar->toggleInCombat();
			waitFor(avatar->doAnim(Animation::unreadyWeapon, direction));
			return;
		}

		if (canAttack()) {
			// double right click = kick
//			pout << "AvatarMover: combat kick" << std::endl;

			if (checkTurn(mousedir, false)) return;

			waitFor(avatar->doAnim(Animation::kick, mousedir));
			lastAttack = lastframe;

			// kicking gives str/dex
			avatar->accumulateStr(1 + (std::rand() % 2));
			avatar->accumulateDex(2 + (std::rand() % 2));
		}

		return;
	}

	if ((mouseButton[1].state & MBS_DOWN) &&
	        (mouseButton[1].state & MBS_HANDLED) && mouseButton[1].lastDown > 0) {
		// right mouse button is down long enough to act on it
		// if facing right direction, walk
		//!! TODO: check if you can actually take this step

		if (checkTurn(mousedir, true)) return;

		int32 nextdir = mousedir;

		if (lastanim == Animation::run) {
			// want to run while in combat mode?
			// first sheath weapon
			nextanim = Animation::readyWeapon;
		} else if (abs(direction - mousedir) == 4) {
			nextanim = Animation::retreat;
			nextdir = direction;
		} else
			nextanim = Animation::advance;

		if (mouselength == 2) {
			// Take a step before running
			nextanim = Animation::walk;
			avatar->setActorFlag(Actor::ACT_COMBATRUN);
			avatar->toggleInCombat();
			MusicProcess::get_instance()->playCombatMusic(110); // CONSTANT!!
		}

		nextanim = Animation::checkWeapon(nextanim, lastanim);
		waitFor(avatar->doAnim(nextanim, nextdir));
		return;
	}

	// if clicked, turn in mouse direction
	if (m0clicked || m1clicked)
		if (checkTurn(mousedir, false)) return;

	// not doing anything in particular? stand
	// TODO: make sure falling works properly.
	if (lastanim != Animation::combatStand) {
		nextanim = Animation::combatStand;
		nextanim = Animation::checkWeapon(nextanim, lastanim);
		waitFor(avatar->doAnim(nextanim, direction));
	}
}

void AvatarMoverProcess::handleNormalMode() {
	GUIApp *guiapp = GUIApp::get_instance();
	MainActor *avatar = getMainActor();
	Animation::Sequence lastanim = avatar->getLastAnim();
	Animation::Sequence nextanim = Animation::walk;
	int32 direction = avatar->getDir();
	uint32 now = g_system->getMillis();
	bool stasis = guiapp->isAvatarInStasis();
	bool combatRun = (avatar->getActorFlags() & Actor::ACT_COMBATRUN) != 0;

	int mx, my;
	guiapp->getMouseCoords(mx, my);
	unsigned int mouselength = guiapp->getMouseLength(mx, my);

	// adjust to world direction
	int32 mousedir = (guiapp->getMouseDirection(mx, my) + 7) % 8;

	// Store current idle time. (Also see end of function.)
	uint32 currentIdleTime = idleTime;
	idleTime = 0;

	// User toggled combat while in combatRun
	if (avatar->isInCombat()) {
		avatar->clearActorFlag(Actor::ACT_COMBATRUN);
		avatar->toggleInCombat();
	}

	// If Avatar has fallen down, stand up.
	if (lastanim == Animation::die || lastanim == Animation::fallBackwards) {
		if (!stasis) {
//			pout << "AvatarMover: standing up" << std::endl;
			waitFor(avatar->doAnim(Animation::standUp, direction));
		}
		return;
	}

	// If still in combat stance, sheathe weapon
	if (!stasis && Animation::isCombatAnim(lastanim)) {
//		pout << "AvatarMover: sheathing weapon" << std::endl;

		ProcId anim1 = avatar->doAnim(Animation::unreadyWeapon, direction);
		ProcId anim2 = avatar->doAnim(Animation::stand, direction);
		Process *anim2p = Kernel::get_instance()->getProcess(anim2);
		anim2p->waitFor(anim1);
		waitFor(anim2);

		return;
	}

	bool m0clicked = false;
	bool m1clicked = false;

	// check mouse state to see what needs to be done
	if (!(mouseButton[0].state & MBS_HANDLED) &&
	        now - mouseButton[0].curDown > DOUBLE_CLICK_TIMEOUT) {
		m0clicked = true;
		mouseButton[0].state |= MBS_HANDLED;
	}

	if (!(mouseButton[1].state & MBS_HANDLED) &&
	        now - mouseButton[1].curDown > DOUBLE_CLICK_TIMEOUT) {
		m1clicked = true;
		mouseButton[1].state |= MBS_HANDLED;
	}

	// see if mouse was just released
	if (!(mouseButton[0].state & MBS_RELHANDLED))
		mouseButton[0].state |= MBS_RELHANDLED; // don't care about left

	if (!(mouseButton[1].state & MBS_RELHANDLED)) {
		mouseButton[1].state |= MBS_RELHANDLED;

		// if we were running in combat mode, slow to a walk, draw weapon
		// (even in stasis)
		if (combatRun) {
			avatar = getMainActor();
			avatar->clearActorFlag(Actor::ACT_COMBATRUN);
			avatar->toggleInCombat();
			ProcId walkpid = avatar->doAnim(Animation::walk, direction);
			ProcId drawpid = avatar->doAnim(Animation::readyWeapon, direction);
			Process *drawproc = Kernel::get_instance()->getProcess(drawpid);
			drawproc->waitFor(walkpid);
			waitFor(drawpid);
			return;
		}

		// if we were running, slow to a walk before stopping
		// (even in stasis)
		if (lastanim == Animation::run) {
			ProcId walkpid = avatar->doAnim(Animation::walk, direction);
			ProcId standpid = avatar->doAnim(Animation::stand, direction);
			Process *standproc = Kernel::get_instance()->getProcess(standpid);
			standproc->waitFor(walkpid);
			waitFor(standpid);
			return;
		}

		// TODO: if we were hanging, fall

		// otherwise, stand
		if (!stasis)
			waitFor(avatar->doAnim(Animation::stand, direction));
		return;
	}

	// can't do any new actions if in stasis
	if (stasis)
		return;

	// both mouse buttons down
	if (!(mouseButton[0].state & MBS_HANDLED) &&
	        !(mouseButton[1].state & MBS_HANDLED)) {
		// notice these are all unsigned.
		uint32 down = mouseButton[1].curDown;
		if (mouseButton[0].curDown < down) {
			down = down - mouseButton[0].curDown;
		} else {
			down = mouseButton[0].curDown - down;
		}

		if (down < DOUBLE_CLICK_TIMEOUT) {
			mouseButton[0].state |= MBS_HANDLED;
			mouseButton[1].state |= MBS_HANDLED;
			// We got a left mouse down.
			// Note that this automatically means right was down too.

			if (checkTurn(mousedir, false)) return;

			nextanim = Animation::jumpUp;
			if (mouselength > 0) {
				nextanim = Animation::jump;
			}
			// check if there's something we can climb up onto here

			Animation::Sequence climbanim = Animation::climb72;
			while (climbanim >= Animation::climb16) {
				if (avatar->tryAnim(climbanim, direction) ==
				        Animation::SUCCESS) {
					nextanim = climbanim;
				}
				climbanim = static_cast<Animation::Sequence>(climbanim - 1);
			}

			if (nextanim == Animation::jump) {
				jump(nextanim, direction);
				return;
			}

			if (nextanim != Animation::jumpUp) {
				// climbing gives str/dex
				avatar->accumulateStr(2 + nextanim - Animation::climb16);
				avatar->accumulateDex(2 * (2 + nextanim - Animation::climb16));
			}

			nextanim = Animation::checkWeapon(nextanim, lastanim);
			waitFor(avatar->doAnim(nextanim, direction));
			return;
		}
	}

	if ((!(mouseButton[0].state & MBS_HANDLED) || m0clicked) &&
	        (mouseButton[1].state & MBS_DOWN)) {
		mouseButton[0].state |= MBS_HANDLED;
		// We got a left mouse down.
		// Note that this automatically means right was down at the time too.

		if (checkTurn(mousedir, false)) return;

		nextanim = Animation::jumpUp;

		// check if we need to do a running jump
		if (lastanim == Animation::run ||
		        lastanim == Animation::runningJump) {
			pout << "AvatarMover: running jump" << std::endl;
			jump(Animation::runningJump, direction);
			return;
		} else if (mouselength > 0) {
			pout << "AvatarMover: jump" << std::endl;
			jump(Animation::jump, direction);
			return;
		}
		nextanim = Animation::checkWeapon(nextanim, lastanim);
		waitFor(avatar->doAnim(nextanim, direction));
		return;

		// CHECKME: check what needs to happen when keeping left pressed
	}

	if ((mouseButton[1].state & MBS_DOWN) &&
	        !(mouseButton[1].state & MBS_HANDLED) &&
	        mouseButton[1].curDown - mouseButton[1].lastDown <= DOUBLE_CLICK_TIMEOUT) {
		Gump *desktopgump = GUIApp::get_instance()->getDesktopGump();
		if (desktopgump->TraceObjId(mx, my) == 1) {
			// double right click on avatar = toggle combat mode
			mouseButton[1].state |= MBS_HANDLED;
			mouseButton[1].lastDown = 0;

			avatar->toggleInCombat();
			waitFor(avatar->doAnim(Animation::readyWeapon, direction));
			return;
		}
	}

	if ((mouseButton[1].state & MBS_DOWN) &&
	        (mouseButton[1].state & MBS_HANDLED)) {
		// right mouse button is down long enough to act on it
		// if facing right direction, walk

		nextanim = Animation::step;

		if (mouselength == 1)
			nextanim = Animation::walk;

		if (mouselength == 2) {
			if (lastanim == Animation::run
			        || lastanim == Animation::runningJump
			        || lastanim == Animation::walk)
				nextanim = Animation::run;
			else
				nextanim = Animation::walk;
		}

		step(nextanim, mousedir);
		return;
	}

	if (m1clicked)
		if (checkTurn(mousedir, false)) return;

	// doing another animation?
	if (Kernel::get_instance()->getNumProcesses(1, 0x00F0))
		return;

	// idle
	idleTime = currentIdleTime + 1;

	// currently shaking head?
	if (lastanim == Animation::lookLeft || lastanim == Animation::lookRight) {
		if ((std::rand() % 1500) + 30 < idleTime) {
			lastHeadShakeAnim = lastanim;
			waitFor(avatar->doAnim(Animation::stand, direction));
			idleTime = 0;
			return;
		}
	} else {
		if ((std::rand() % 3000) + 150 < idleTime) {
			if (std::rand() % 5 == 0)
				nextanim = lastHeadShakeAnim;
			else if (lastHeadShakeAnim == Animation::lookLeft)
				nextanim = Animation::lookRight;
			else
				nextanim = Animation::lookLeft;
			waitFor(avatar->doAnim(nextanim, direction));
			idleTime = 0;
		}
	}
}

void AvatarMoverProcess::step(Animation::Sequence action, int direction,
                              bool adjusted) {
	assert(action == Animation::step || action == Animation::walk ||
	       action == Animation::run);

	MainActor *avatar = getMainActor();
	Animation::Sequence lastanim = avatar->getLastAnim();

	Animation::Result res = avatar->tryAnim(action, direction);

	int stepdir = direction;

	if (res == Animation::FAILURE ||
	        (action == Animation::step && res == Animation::END_OFF_LAND)) {
		int altdir1 = (stepdir + 1) % 8;
		int altdir2 = (stepdir + 7) % 8;

		res = avatar->tryAnim(action, altdir1);
		if (res == Animation::FAILURE ||
		        (action == Animation::step && res == Animation::END_OFF_LAND)) {
			res = avatar->tryAnim(action, altdir2);
			if (res == Animation::FAILURE ||
			        (action == Animation::step && res == Animation::END_OFF_LAND)) {
				// Can't walk in this direction.
				// Try to take a smaller step

				if (action == Animation::walk) {
					step(Animation::step, direction, true);
					return;
				} else if (action == Animation::run) {
					step(Animation::walk, direction, true);
					return;
				}

			} else {
				stepdir = altdir2;
			}
		} else {
			stepdir = altdir1;
		}


	}

	if (action == Animation::step && res == Animation::END_OFF_LAND &&
	        lastanim != Animation::keepBalance && !adjusted) {
		if (checkTurn(stepdir, false)) return;
		waitFor(avatar->doAnim(Animation::keepBalance, stepdir));
		return;
	}

	if (action == Animation::step && res == Animation::FAILURE) {
		action = Animation::stand;
	}


	bool moving = (action == Animation::run || action == Animation::walk);

	if (checkTurn(stepdir, moving)) return;

	action = Animation::checkWeapon(action, lastanim);
	waitFor(avatar->doAnim(action, stepdir));
}

void AvatarMoverProcess::jump(Animation::Sequence action, int direction) {
	GUIApp *guiapp = GUIApp::get_instance();
	MainActor *avatar = getMainActor();
	int mx, my;
	guiapp->getMouseCoords(mx, my);

	// running jump
	if (action == Animation::runningJump) {
		waitFor(avatar->doAnim(action, direction));
		return;
	}

	// airwalk
	if ((avatar->getActorFlags() & Actor::ACT_AIRWALK) &&
	        action == Animation::jump) {
		waitFor(avatar->doAnim(Animation::airwalkJump, direction));
		return;
	}

	bool targeting;
	SettingManager::get_instance()->get("targetedjump", targeting);

	if (targeting) {
		int32 coords[3];
		GameMapGump *gameMap = guiapp->getGameMapGump();
		// We need the Gump's x/y for TraceCoordinates
		gameMap->ScreenSpaceToGump(mx, my);
		ObjId targetId = gameMap->TraceCoordinates(mx, my, coords);
		Item *target = getItem(targetId);

		int32 ax, ay, az;
		avatar->getCentre(ax, ay, az);

		int32 xrange = ax - coords[0];
		if (xrange < 0) xrange = -xrange;
		int32 yrange = ay - coords[1];
		if (yrange < 0) yrange = -yrange;
		int maxrange = avatar->getStr() * 32;

		if (target && target->getShapeInfo()->is_land() &&
		        xrange < maxrange && yrange < maxrange) {
			// Original also only lets you jump at the Z_FACE
			Process *p = new TargetedAnimProcess(avatar, Animation::jumpUp,
			                                     direction, coords);
			waitFor(Kernel::get_instance()->addProcess(p));
			return;
		}
		// invalid target or out of range
		waitFor(avatar->doAnim(Animation::shakeHead, direction));
	} else {
		waitFor(avatar->doAnim(Animation::jump, direction));
	}
}

void AvatarMoverProcess::turnToDirection(int direction) {
	MainActor *avatar = getMainActor();
	bool combatRun = (avatar->getActorFlags() & Actor::ACT_COMBATRUN) != 0;
	int curdir = avatar->getDir();
	int step;
	bool combat = avatar->isInCombat() && !combatRun;
	Animation::Sequence turnanim;
	Animation::Sequence standanim = Animation::stand;

	if ((curdir - direction + 8) % 8 < 4) {
		step = -1;
		turnanim = Animation::lookLeft;
	} else {
		step = 1;
		turnanim = Animation::lookRight;
	}

	if (combat) {
		turnanim = Animation::combatStand;
		standanim = Animation::combatStand;
	}

	ProcId prevpid = 0;

	for (int dir = curdir; dir != direction;) {
		ProcId animpid = avatar->doAnim(turnanim, dir);

		if (prevpid) {
			Process *proc = Kernel::get_instance()->getProcess(animpid);
			assert(proc);
			proc->waitFor(prevpid);
		}

		prevpid = animpid;

		dir = (dir + step + 8) % 8;
	}

	ProcId animpid = avatar->doAnim(standanim, direction);

	if (prevpid) {
		Process *proc = Kernel::get_instance()->getProcess(animpid);
		assert(proc);
		proc->waitFor(prevpid);
	}

	waitFor(animpid);
}

bool AvatarMoverProcess::checkTurn(int direction, bool moving) {
	MainActor *avatar = getMainActor();
	bool combatRun = (avatar->getActorFlags() & Actor::ACT_COMBATRUN) != 0;
	int curdir = avatar->getDir();
	bool combat = avatar->isInCombat() && !combatRun;
	Animation::Sequence lastanim = avatar->getLastAnim();

	// Note: don't need to turn if moving backward in combat stance
	// CHECKME: currently, first turn in the right direction
	if (direction != curdir && !(
	            combat && abs(direction - curdir) == 4)) {
		if (moving &&
		        (lastanim == Animation::walk || lastanim == Animation::run ||
		         lastanim == Animation::combatStand) &&
		        (abs(direction - curdir) + 1 % 8 <= 2)) {
			// don't need to explicitly do a turn animation
			return false;
		}

		if (moving && lastanim == Animation::run) {
			// slow down to a walk first
			waitFor(avatar->doAnim(Animation::walk, curdir));
			return true;
		}

		turnToDirection(direction);
		return true;
	}

	return false;
}

bool AvatarMoverProcess::canAttack() {
	MainActor *avatar = getMainActor();
	return (lastframe > lastAttack + (25 - avatar->getDex()));
}

void AvatarMoverProcess::OnMouseDown(int button, int mx, int my) {
	int bid = 0;

	switch (button) {
	case BUTTON_LEFT: {
		bid = 0;
		break;
	}
	case BUTTON_RIGHT: {
		bid = 1;
		break;
	}
	default:
		CANT_HAPPEN_MSG("invalid MouseDown passed to AvatarMoverProcess");
		break;
	};

	mouseButton[bid].lastDown = mouseButton[bid].curDown;
	mouseButton[bid].curDown = g_system->getMillis();
	mouseButton[bid].state |= MBS_DOWN;
	mouseButton[bid].state &= ~MBS_HANDLED;
}

void AvatarMoverProcess::OnMouseUp(int button) {
	int bid = 0;

	if (button == BUTTON_LEFT) {
		bid = 0;
	} else if (button == BUTTON_RIGHT) {
		bid = 1;
	} else {
		CANT_HAPPEN_MSG("invalid MouseUp passed to AvatarMoverProcess");
	}

	mouseButton[bid].state &= ~MBS_DOWN;
	mouseButton[bid].state &= ~MBS_RELHANDLED;
}


void AvatarMoverProcess::saveData(ODataSource *ods) {
	Process::saveData(ods);

	ods->write4(lastAttack);
	ods->write4(idleTime);
	ods->write2(static_cast<uint8>(lastHeadShakeAnim));
}

bool AvatarMoverProcess::loadData(IDataSource *ids, uint32 version) {
	if (!Process::loadData(ids, version)) return false;

	lastAttack = ids->read4();
	idleTime = ids->read4();
	lastHeadShakeAnim = static_cast<Animation::Sequence>(ids->read2());

	return true;
}

} // End of namespace Ultima8
