/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "common/events.h"

#include "hypno/grammar.h"
#include "hypno/hypno.h"

namespace Hypno {

//Actions

void HypnoEngine::runMenu(Hotspots *hs) {
	Hotspot *h = hs->begin();
	assert(h->type == MakeMenu);
	debugC(1, kHypnoDebugScene, "hotspot actions size: %d", h->actions.size());
	for (Actions::const_iterator itt = h->actions.begin(); itt != h->actions.end(); ++itt) {
		Action *action = *itt;
		switch (action->type) {
			case QuitAction:
				runQuit((Quit *)action);
			break;
			case TimerAction:
				runTimer((Timer *)action);
			break;
			case BackgroundAction:
				runBackground((Background *)action);
			break;
			case OverlayAction:
				runOverlay((Overlay *)action);
			break;
			case AmbientAction: 
				runAmbient((Ambient *)action);
			break;
			case IntroAction:
				runIntro((Intro *)action);
			break;
			case CutsceneAction:
				runCutscene((Cutscene *)action);
			break;
			case PaletteAction:
				runPalette((Palette *)action);
			break;

			default:
			break;
		}

		//else if (typeid(*action) == typeid(Mice))
		//	runMice(h, (Mice*) action);
	}

	Graphics::Surface *menu = nullptr;
	bool transparent = false;
	if (_conversation.empty()) {
		if (h->flags[0] == "HINTS" || h->flags[1] == "HINTS" || h->flags[2] == "HINTS") {
			menu = decodeFrame("int_main/hint1.smk", 0);
		} else if (h->flags[0] == "AUTO_BUTTONS" || h->flags[0] == "SINGLE_RUN") {
			if (isDemo()) {
				if (_currentLevel != "sixdemo/mis/demo.mis" && _currentLevel != "sixdemo/mis/order.mis") {
					menu = decodeFrame("int_main/resume.smk", 0);
					transparent = true;
				}
			} else {
				menu = decodeFrame("int_main/menu.smk", 0);
			}
		} 

		if (menu) {
			h->rect = Common::Rect(0, 0, menu->w, menu->h);
			drawImage(*menu, 0, 0, transparent);
		}
	}
}

void HypnoEngine::runBackground(Background *a) {	
	if (a->condition.size() > 0) {
		bool condition = _sceneState[a->condition];

		if (a->flag1 == "/NSTATE" || a->flag2 == "/NSTATE") 
			condition = !condition;

		if (!condition)
			return;
	}

	loadImage(a->path, a->origin.x, a->origin.y, false);
}

void HypnoEngine::runTimer(Timer *a) {
	if (_timerStarted)
		return; // Do not start another timer

	uint32 delay = a->delay/1000;
	debugC(1, kHypnoDebugScene, "Starting timer with %d secons", delay);

	if (delay == 0 || !startCountdown(delay))
		error("Failed to start countdown");
}

void HypnoEngine::runOverlay(Overlay *a) {
	loadImage(a->path, a->origin.x, a->origin.y, false);
}

void HypnoEngine::runMice(Mice *a) {
	changeCursor(a->path, a->index);
}

void HypnoEngine::runPalette(Palette *a) {
	loadPalette(a->path);
}

void HypnoEngine::runEscape() {
	_nextHotsToRemove = stack.back();
	_nextSequentialVideoToPlay = _escapeSequentialVideoToPlay;
	_escapeSequentialVideoToPlay.clear();
}

void HypnoEngine::runIntro(Intro *a) {
	// Should not repeat the same
	if (_intros.contains(a->path))
		return;

	_intros[a->path] = true;
	MVideo v(a->path, Common::Point(0, 0), false, true, false);
	runIntro(v);
}


void HypnoEngine::runCutscene(Cutscene *a) {
	stopSound();
	defaultCursor();
	_music.clear();
	_nextSequentialVideoToPlay.push_back(MVideo(a->path, Common::Point(0, 0), false, true, false));
}

bool HypnoEngine::runGlobal(Global *a) {
	debugC(1, kHypnoDebugScene, "Runing global with command '%s' and variable '%s'", a->command.c_str(), a->variable.c_str());
	if (a->command == "TURNON")
		_sceneState[a->variable] = 1;
	else if (a->command == "TURNOFF")
		_sceneState[a->variable] = 0;
	else if (a->command == "TOGGLE")
		_sceneState[a->variable] = !_sceneState[a->variable];
	else if (a->command == "CHECK") {
		if (!_sceneState[a->variable]) // Clear any video to play
			_nextSequentialVideoToPlay.clear();
		return _sceneState[a->variable];
	} else if (a->command == "NCHECK") {
		if (_sceneState[a->variable]) // Clear any video to play
			_nextSequentialVideoToPlay.clear();
		return !_sceneState[a->variable];
	} else if (a->command == "CLEAR") {
		resetSceneState();
		return true;
	} else
		error("Invalid command %s", a->command.c_str());
	return true;
}

void HypnoEngine::runPlay(Play *a) {
	if (a->condition.size() > 0 && !_sceneState[a->condition])
		return;

	if (a->flag == "/BITMAP")
		loadImage(a->path, a->origin.x, a->origin.y, false);
	else {
		_nextSequentialVideoToPlay.push_back(MVideo(a->path, a->origin, false, false, false));
	}
}

void HypnoEngine::runAmbient(Ambient *a) {
	if (a->flag == "/BITMAP") {
		Graphics::Surface *frame = decodeFrame(a->path, a->frameNumber);
		Graphics::Surface *sframe;
		if (a->fullscreen)
			sframe = frame->scale(_screenW, _screenH);
		else
			sframe = frame;
		drawImage(*sframe, a->origin.x, a->origin.y, true);
		if (a->fullscreen){
			frame->free();
			delete frame;
		}
		sframe->free();
		delete sframe;
	} else {
		bool loop = a->flag == "/LOOP";
		if (loop) { // Avoid re-adding the same looping video
			if (_intros.contains(a->path))
				return;
			_intros[a->path] = true;
		}
		_nextSequentialVideoToPlay.push_back(MVideo(a->path, a->origin, false, a->fullscreen, loop));
	}
}

void HypnoEngine::runWalN(WalN *a) {
	if (a->condition.size() > 0 && !_sceneState[a->condition])
		return;

	if (a->wn == "WAL0")
		_nextSequentialVideoToPlay.push_back(MVideo(a->path, a->origin, false, false, false));
	else if (a->wn == "WAL1")
		_escapeSequentialVideoToPlay.push_back(MVideo(a->path, a->origin, false, false, false));
	else
		error("Invalid WALN command: %s", a->wn.c_str());
}

void HypnoEngine::runSave(Save *a) {
	// TODO: enable this when saving in the main menu is available
	//saveGameDialog();
}

void HypnoEngine::runLoad(Load *a) {
	loadGameDialog();
}

void HypnoEngine::runLoadCheckpoint(LoadCheckpoint *a) {
	if (_checkpoint.empty())
		error("Invalid checkpoint!");
	loadGame(_checkpoint, _sceneState["GS_PUZZLELEVEL"], _sceneState["GS_COMBATLEVEL"]);
}

void HypnoEngine::runQuit(Quit *a) {
	quitGame();
}

void HypnoEngine::runChangeLevel(ChangeLevel *a) {
	debugC(1, kHypnoDebugScene, "Next level is '%s'", a->level.c_str());	
	_nextLevel = a->level;
}

void HypnoEngine::runTalk(Talk *a) {
	_conversation.push_back(a);
	_refreshConversation = true;
}

} // End of namespace Hypno

