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

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * MIT License:
 *
 * Copyright (c) 2009 Alexei Svitkine, Eugene Sandulenko
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include "wage/wage.h"
#include "wage/entities.h"
#include "wage/script.h"
#include "wage/world.h"

#include "common/stream.h"

namespace Wage {

bool Script::execute(World *world, int loopCount, String *inputText, Designed *inputClick, WageEngine *callbacks) {
	_world = world;
	_loopCount = loopCount;
	_inputText = inputText;
	_inputClick = inputClick;
	_callbacks = callbacks;
	_handled = false;

	_data->skip(12);
	while (_data->pos() < _data->size()) {
		byte command = _data->readByte();

		debug(1, "Command: %x", command);

		switch(command) {
		case 0x80: // IF
			processIf();
			break;
		case 0x87: // EXIT
			debug(0, "exit at offset %d", _data->pos() - 1);

			return true;
		case 0x89: // MOVE
			{
				Scene *currentScene = _world->_player->_currentScene;
				processMove();
				if (_world->_player->_currentScene != currentScene)
					return true;
				break;
			}
		case 0x8B: // PRINT
			{
				Operand *op = readOperand();
				// TODO check op type is string or number, or something good...
				appendText(op->toString());
				byte d = _data->readByte();
				if (d != 0xFD)
					warning("Operand 0x8B (PRINT) End Byte != 0xFD");
				break;
			}
		case 0x8C: // SOUND
			{
				Operand *op = readOperand();
				// TODO check op type is string.
				_handled = true;
				callbacks->playSound(op->toString());
				byte d = _data->readByte();
				if (d != 0xFD)
					warning("Operand 0x8B (PRINT) End Byte != 0xFD");
				break;
			}
		case 0x8E: // LET
			processLet();
			break;
		case 0x95: // MENU
			{
				Operand *op = readStringOperand(); // allows empty menu
				// TODO check op type is string.
				_callbacks->setMenu(op->toString());
				byte d = _data->readByte();
				if (d != 0xFD)
					warning("Operand 0x8B (PRINT) End Byte != 0xFD");
			}
		case 0x88: // END
			break;
		default:
			debug(0, "Unknown opcode: %d", _data->pos());
		}
	}

	if (_world->_globalScript != this) {
		debug(0, "Executing global script...");
		bool globalHandled = _world->_globalScript->execute(_world, _loopCount, _inputText, _inputClick, _callbacks);
		if (globalHandled)
			_handled = true;
	} else if (inputText != NULL) {
		Common::String input(*inputText);
		input.toLowercase();
		if (input.equals("n") || input.contains("north")) {
			handleMoveCommand(Scene::NORTH, "north");
		} else if (input.equals("e") || input.contains("east")) {
			handleMoveCommand(Scene::EAST, "east");
		} else if (input.equals("s") || input.contains("south")) {
			handleMoveCommand(Scene::SOUTH, "south");
		} else if (input.equals("w") || input.contains("west")) {
			handleMoveCommand(Scene::WEST, "west");
		} else if (input.hasPrefix("take ")) {
			handleTakeCommand(&input.c_str()[5]);
		} else if (input.hasPrefix("get ")) {
			handleTakeCommand(&input.c_str()[4]);
		} else if (input.hasPrefix("pick up ")) {
			handleTakeCommand(&input.c_str()[8]);
		} else if (input.hasPrefix("drop ")) {
			handleDropCommand(&input.c_str()[5]);
		} else if (input.hasPrefix("aim ")) {
			handleAimCommand(&input.c_str()[4]);
		} else if (input.hasPrefix("wear ")) {
			handleWearCommand(&input.c_str()[5]);
		} else if (input.hasPrefix("put on ")) {
			handleWearCommand(&input.c_str()[7]);
		} else if (input.hasPrefix("offer ")) {
			handleOfferCommand(&input.c_str()[6]);
		} else if (input.contains("look")) {
			handleLookCommand();
		} else if (input.contains("inventory")) {
			handleInventoryCommand();
		} else if (input.contains("status")) {
			handleStatusCommand();
		} else if (input.contains("rest") || input.equals("wait")) {
			handleRestCommand();
		} else if (callbacks->getOffer() != NULL && input.contains("accept")) {
			handleAcceptCommand();
		} else {
			Chr *player = _world->_player;
			WeaponArray *weapons = player->getWeapons();
			for (WeaponArray::const_iterator weapon = weapons->begin(); weapon != weapons->end(); ++weapon) {
				if (tryAttack(*weapon, input)) {
					handleAttack(*weapon);
					break;
				}
			}

			delete weapons;
		}
/*
	// TODO: weapons, offer, etc...
	} else if (inputClick instanceof Obj) {
		Obj obj = (Obj) inputClick;
		if (obj.getType() != Obj.IMMOBILE_OBJECT) {
			takeObj(obj);
		} else {
			appendText(obj.getClickMessage());
		}
*/
	}

	return _handled;
}

Script::Operand *Script::readOperand() {
	byte operandType = _data->readByte();

	debug(2, "%x: readOperand: 0x%x", _data->pos(), operandType);

	Context *cont = &_world->_player->_context;
	switch (operandType) {
	case 0xA0: // TEXT$
		return new Operand(_inputText, TEXT_INPUT);
	case 0xA1:
		return new Operand(_inputClick, CLICK_INPUT);
	case 0xC0: // STORAGE@
		return new Operand(&_world->_storageScene, SCENE);
	case 0xC1: // SCENE@
		return new Operand(_world->_player->_currentScene, SCENE);
	case 0xC2: // PLAYER@
		return new Operand(_world->_player, CHR);
	case 0xC3: // MONSTER@
		return new Operand(_callbacks->_monster, CHR);
	case 0xC4: // RANDOMSCN@
		return new Operand(_world->_orderedScenes[_callbacks->_rnd->getRandomNumber(_world->_orderedScenes.size())], SCENE);
	case 0xC5: // RANDOMCHR@
		return new Operand(_world->_orderedChrs[_callbacks->_rnd->getRandomNumber(_world->_orderedChrs.size())], CHR);
	case 0xC6: // RANDOMOBJ@
		return new Operand(_world->_orderedObjs[_callbacks->_rnd->getRandomNumber(_world->_orderedObjs.size())], OBJ);
	case 0xB0: // VISITS#
		return new Operand(cont->_visits, NUMBER);
	case 0xB1: // RANDOM# for Star Trek, but VISITS# for some other games?
		return new Operand(1 + _callbacks->_rnd->getRandomNumber(100), NUMBER);
	case 0xB5: // RANDOM# // A random number between 1 and 100.
		return new Operand(1 + _callbacks->_rnd->getRandomNumber(100), NUMBER);
	case 0xB2: // LOOP#
		return new Operand(_loopCount, NUMBER);
	case 0xB3: // VICTORY#
		return new Operand(cont->_kills, NUMBER);
	case 0xB4: // BADCOPY#
		return new Operand(0, NUMBER); // ????
	case 0xFF:
		{
			// user variable
			int value = _data->readByte();

			// TODO: Verify that we're using the right index.
			return new Operand(cont->_userVariables[value - 1], NUMBER);
		}
	case 0xD0:
		return new Operand(cont->_statVariables[Context::PHYS_STR_BAS], NUMBER);
	case 0xD1:
		return new Operand(cont->_statVariables[Context::PHYS_HIT_BAS], NUMBER);
	case 0xD2:
		return new Operand(cont->_statVariables[Context::PHYS_ARM_BAS], NUMBER);
	case 0xD3:
		return new Operand(cont->_statVariables[Context::PHYS_ACC_BAS], NUMBER);
	case 0xD4:
		return new Operand(cont->_statVariables[Context::SPIR_STR_BAS], NUMBER);
	case 0xD5:
		return new Operand(cont->_statVariables[Context::SPIR_HIT_BAS], NUMBER);
	case 0xD6:
		return new Operand(cont->_statVariables[Context::SPIR_ARM_BAS], NUMBER);
	case 0xD7:
		return new Operand(cont->_statVariables[Context::SPIR_ACC_BAS], NUMBER);
	case 0xD8:
		return new Operand(cont->_statVariables[Context::PHYS_SPE_BAS], NUMBER);
	case 0xE0:
		return new Operand(cont->_statVariables[Context::PHYS_STR_CUR], NUMBER);
	case 0xE1:
		return new Operand(cont->_statVariables[Context::PHYS_HIT_CUR], NUMBER);
	case 0xE2:
		return new Operand(cont->_statVariables[Context::PHYS_ARM_CUR], NUMBER);
	case 0xE3:
		return new Operand(cont->_statVariables[Context::PHYS_ACC_CUR], NUMBER);
	case 0xE4:
		return new Operand(cont->_statVariables[Context::SPIR_STR_CUR], NUMBER);
	case 0xE5:
		return new Operand(cont->_statVariables[Context::SPIR_HIT_CUR], NUMBER);
	case 0xE6:
		return new Operand(cont->_statVariables[Context::SPIR_ARM_CUR], NUMBER);
	case 0xE7:
		return new Operand(cont->_statVariables[Context::SPIR_ACC_CUR], NUMBER);
	case 0xE8:
		return new Operand(cont->_statVariables[Context::PHYS_SPE_CUR], NUMBER);
	default:
		if (operandType >= 0x20 && operandType < 0x80) {
			_data->seek(-1, SEEK_CUR);
			return readStringOperand();
		} else {
			debug("Dunno what %x is (index=%d)!\n", operandType, _data->pos()-1);
		}
		return NULL;
	}
}

void Script::assign(byte operandType, int uservar, uint16 value) {
	Context *cont = &_world->_player->_context;

	switch (operandType) {
	case 0xFF:
		cont->_userVariables[uservar - 1] = value;
		break;
	case 0xD0:
		cont->_statVariables[Context::PHYS_STR_BAS] = value;
		break;
	case 0xD1:
		cont->_statVariables[Context::PHYS_HIT_BAS] = value;
		break;
	case 0xD2:
		cont->_statVariables[Context::PHYS_ARM_BAS] = value;
		break;
	case 0xD3:
		cont->_statVariables[Context::PHYS_ACC_BAS] = value;
		break;
	case 0xD4:
		cont->_statVariables[Context::SPIR_STR_BAS] = value;
		break;
	case 0xD5:
		cont->_statVariables[Context::SPIR_HIT_BAS] = value;
		break;
	case 0xD6:
		cont->_statVariables[Context::SPIR_ARM_BAS] = value;
		break;
	case 0xD7:
		cont->_statVariables[Context::SPIR_ACC_BAS] = value;
		break;
	case 0xD8:
		cont->_statVariables[Context::PHYS_SPE_BAS] = value;
		break;
	case 0xE0:
		cont->_statVariables[Context::PHYS_STR_CUR] = value;
		break;
	case 0xE1:
		cont->_statVariables[Context::PHYS_HIT_CUR] = value;
		break;
	case 0xE2:
		cont->_statVariables[Context::PHYS_ARM_CUR] = value;
		break;
	case 0xE3:
		cont->_statVariables[Context::PHYS_ACC_CUR] = value;
		break;
	case 0xE4:
		cont->_statVariables[Context::SPIR_STR_CUR] = value;
		break;
	case 0xE5:
		cont->_statVariables[Context::SPIR_HIT_CUR] = value;
		break;
	case 0xE6:
		cont->_statVariables[Context::SPIR_ARM_CUR] = value;
		break;
	case 0xE7:
		cont->_statVariables[Context::SPIR_ACC_CUR] = value;
		break;
	case 0xE8:
		cont->_statVariables[Context::PHYS_SPE_CUR] = value;
		break;
	default:
		debug("No idea what I'm supposed to assign! (%x at %d)!\n", operandType, _data->pos()-1);
	}
}

Script::Operand *Script::readStringOperand() {
	String *sb;
	bool allDigits = true;

	sb = new String();

	byte c = 0x20;
	while (c >= 0x20 && c < 0x80) {
		c = _data->readByte();
		if (c < '0' || c > '9')
			allDigits = false;
		*sb += c;
	}
	_data->seek(-1, SEEK_CUR);

	if (allDigits && sb->size() > 0) {
		debug(0, "Read number %s", sb->c_str());
		int r = atol(sb->c_str());
		delete sb;

		return new Operand(r, NUMBER);
	} else {
		// TODO: This string could be a room name or something like that.
		debug(0, "Read string %s", sb->c_str());
		return new Operand(sb, STRING);
	}
}

const char *Script::readOperator() {
	byte cmd = _data->readByte();

	debug(2, "readOperator: 0x%x", cmd);
	switch (cmd) {
	case 0x81:
		return "=";
	case 0x82:
		return "<";
	case 0x83:
		return ">";
	case 0x8f:
		return "+";
	case 0x90:
		return "-";
	case 0x91:
		return "*";
	case 0x92:
		return "/";
	case 0x93:
		return "==";
	case 0x94:
		return ">>";
	case 0xfd:
		return ";";
	default:
		warning("UNKNOWN OP %x", cmd);
	}
	return NULL;
}

void Script::processIf() {
	int logicalOp = 0; // 0 => initial, 1 => and, 2 => or
	bool result = true;
	bool done = false;

	do {
		Operand *lhs = readOperand();
		const char *op = readOperator();
		Operand *rhs = readOperand();

		bool condResult = eval(lhs, op, rhs);

		if (logicalOp == 1) {
			result = (result && condResult);
		} else if (logicalOp == 2) {
			result = (result || condResult);
		} else { // logicalOp == 0
			result = condResult;
		}

		byte logical = _data->readByte();

		if (logical == 0x84) {
			logicalOp = 1; // and
		} else if (logical == 0x85) {
			logicalOp = 2; // or
		} else if (logical == 0xFE) {
			done = true; // then
		}
	} while (!done);

	if (result == false) {
		skipBlock();
	}
}

void Script::skipIf() {
	do {
		readOperand();
		readOperator();
		readOperand();
	} while (_data->readByte() != 0xFE);
}

void Script::skipBlock() {
	int nesting = 1;

	while (true) {
		byte op = _data->readByte();

		if (_data->eos())
			return;

		if (op == 0x80) { // IF
			nesting++;
			skipIf();
		} else if (op == 0x88 || op == 0x87) { // END or EXIT
			_data->seek(-1, SEEK_CUR); // We need to reread it higher
			nesting--;
			if (nesting == 0) {
				_data->readByte(); // skiping
				return;
			}
		} else switch (op) {
			case 0x8B: // PRINT
			case 0x8C: // SOUND
			case 0x8E: // LET
			case 0x95: // MENU
				while (_data->readByte() != 0xFD)
					;
		}
	}
}

enum {
	kCompEqNumNum,
	kCompEqObjScene,
	kCompEqChrScene,
	kCompEqObjChr,
	kCompEqChrChr,
	kCompEqSceneScene,
	kCompEqStringTextInput,
	kCompEqTextInputString,
	kCompEqNumberTextInput,
	kCompEqTextInputNumber,
	kCompLtNumNum,
	kCompLtStringTextInput,
	kCompLtTextInputString,
	kCompLtObjChr,
	kCompLtChrObj,
	kCompLtObjScene,
	kCompGtNumNum,
	kCompGtStringString,
	kCompGtChrScene
};

struct Comparator {
	char operation;
	OperandTypes o1;
	OperandTypes o2;
	int compfunc;
} static comparators[] = {
	{ '=', NUMBER, NUMBER, kCompEqNumNum },
	{ '=', OBJ, SCENE, kCompEqObjScene },
	{ '=', CHR, SCENE, kCompEqChrScene },
	{ '=', OBJ, CHR, kCompEqObjChr },
	{ '=', CHR, CHR, kCompEqChrChr },
	{ '=', SCENE, SCENE, kCompEqSceneScene },
	{ '=', STRING, TEXT_INPUT, kCompEqStringTextInput },
	{ '=', TEXT_INPUT, STRING, kCompEqTextInputString },
	{ '=', NUMBER, TEXT_INPUT, kCompEqNumberTextInput },
	{ '=', TEXT_INPUT, NUMBER, kCompEqTextInputNumber },

	{ '<', NUMBER, NUMBER, kCompLtNumNum },
	{ '<', STRING, TEXT_INPUT, kCompLtStringTextInput },
	{ '<', TEXT_INPUT, STRING, kCompLtTextInputString },
	{ '<', OBJ, CHR, kCompLtObjChr },
	{ '<', CHR, OBJ, kCompLtChrObj },
	{ '<', OBJ, SCENE, kCompLtObjScene },
	{ '<', CHR, CHR, kCompEqChrChr }, // Same logic as =
	{ '<', SCENE, SCENE, kCompEqSceneScene },

	{ '>', NUMBER, NUMBER, kCompGtNumNum },
	{ '>', TEXT_INPUT, STRING, kCompLtTextInputString }, // Same logic as <
	//FIXME: this prevents the below cases from working due to exact
	//matches taking precedence over conversions...
	//{ '>', STRING, STRING, kCompGtStringString }, // Same logic as <
	{ '>', OBJ, CHR, kCompLtObjChr }, // Same logic as <
	{ '>', OBJ, SCENE, kCompLtObjScene }, // Same logic as <
	{ '>', CHR, SCENE, kCompGtChrScene },
	{ 0, OBJ, OBJ, 0 }
};

bool Script::compare(Operand *o1, Operand *o2, int comparator) {
	switch(comparator) {
	case kCompEqNumNum:
		return o1->_value.number == o2->_value.number;
	case kCompEqObjScene:
		error("FIXME kCompEqObjScene");
		//return o2->_value.scene->_objs.contains(*o1->_value.obj);
	case kCompEqChrScene:
		error("FIXME kCompEqChrScene");
		//return o2->_value.scene->_chrs.contains(*o1->_value.chr);
	case kCompEqObjChr:
		error("FIXME kCompEqObjChr");
		//return o2->_value.chr->_inventory.contains(*o1->_value.obj);
	case kCompEqChrChr:
		return o1->_value.chr == o2->_value.chr;
	case kCompEqSceneScene:
		return o1->_value.scene == o2->_value.scene;
	case kCompEqStringTextInput:
		if (_inputText == NULL) {
			return false;
		} else {
			Common::String s1(*_inputText), s2(*o1->_value.string);
			s1.toLowercase();
			s2.toLowercase();

			return s1.contains(s2);
		}
	case kCompEqTextInputString:
		return compare(o2, o1, kCompEqStringTextInput);
	case kCompEqNumberTextInput:
		if (_inputText == NULL) {
			return false;
		} else {
			Common::String s1(*_inputText), s2(o1->toString());
			s1.toLowercase();
			s2.toLowercase();

			return s1.contains(s2);
		}
	case kCompEqTextInputNumber:
		if (_inputText == NULL) {
			return false;
		} else {
			Common::String s1(*_inputText), s2(o2->toString());
			s1.toLowercase();
			s2.toLowercase();

			return s1.contains(s2);
		}
	case kCompLtNumNum:
		return o1->_value.number < o2->_value.number;
	case kCompLtStringTextInput:
		return !compare(o1, o2, kCompEqStringTextInput);
	case kCompLtTextInputString:
		return !compare(o2, o1, kCompEqStringTextInput);
	case kCompLtObjChr:
		return o1->_value.obj->_currentOwner != o2->_value.chr;
	case kCompLtChrObj:
		return compare(o2, o1, kCompLtObjChr);
	case kCompLtObjScene:
		return o1->_value.obj->_currentScene != o2->_value.scene;
	case kCompGtNumNum:
		return o1->_value.number > o2->_value.number;
	case kCompGtStringString:
		return o1->_value.string == o2->_value.string;
	case kCompGtChrScene:
		return (o1->_value.chr != NULL && o1->_value.chr->_currentScene != o2->_value.scene);
	}

	return false;
}

bool Script::eval(Operand *lhs, const char *op, Operand *rhs) {
	bool result = false;

	if (lhs->_type == CLICK_INPUT || rhs->_type == CLICK_INPUT) {
		return evalClickCondition(lhs, op, rhs);
	} else if (!strcmp(op, "==") || !strcmp(op, ">>")) {
		// TODO: check if >> can be used for click inputs and if == can be used for other things
		// exact string match
		if (lhs->_type == TEXT_INPUT) {
			if ((rhs->_type != STRING && rhs->_type != NUMBER) || _inputText == NULL) {
				result = false;
			} else {
				result = _inputText->equalsIgnoreCase(rhs->toString());
			}
		} else if (rhs->_type == TEXT_INPUT) {
			if ((lhs->_type != STRING && lhs->_type != NUMBER) || _inputText == NULL) {
				result = false;
			} else {
				result = _inputText->equalsIgnoreCase(lhs->toString());
			}
		} else {
			error("UNHANDLED CASE: [lhs=%d/%s, rhs=%d/%s]",
				lhs->_type, lhs->toString().c_str(), rhs->_type, rhs->toString().c_str());
		}
		if (!strcmp(op, ">>")) {
			result = !result;
		}

		return result;
	}

	return false;
}

bool Script::evalClickCondition(Operand *lhs, const char *op, Operand *rhs) {
	warning("STUB: evalClickCondition");

	return false;
}

void Script::processMove() {
	warning("STUB: processMove");
}

void Script::processLet() {
	const char *lastOp = NULL;
	int16 result = 0;
	int operandType = _data->readByte();
	int uservar = 0;

	if (operandType == 0xff) {
		uservar = _data->readByte();
	}

	byte eq = _data->readByte(); // skip "=" operator

	debug(2, "processLet: 0x%x, uservar: 0x%x, eq: 0x%x", operandType, uservar, eq);

	do {
		Operand *operand = readOperand();
		// TODO assert that value is NUMBER
		int16 value = operand->_value.number;
		if (lastOp != NULL) {
			if (lastOp[0] == '+')
				result += value;
			else if (lastOp[0] == '-')
				result -= value;
			else if (lastOp[0] == '/')
				result = (int16)(value == 0 ? 0 : result / value);
			else if (lastOp[0] == '*')
				result *= value;
		} else {
			result = value;
		}
		lastOp = readOperator();

		if (lastOp[0] == ';')
			break;
	} while (true);
	//System.out.println("processLet " + buildStringFromOffset(oldIndex - 1, index - oldIndex + 1) + "}");

	assign(operandType, uservar, result);
}

void Script::appendText(String str) {
	_handled = true;
	_callbacks->appendText(str);
}

void Script::handleMoveCommand(Scene::Directions dir, const char *dirName) {
	warning("STUB: handleMoveCommand");
}

void Script::handleLookCommand() {
	warning("STUB: handleLookCommand");
}

void Script::handleInventoryCommand() {
	warning("STUB: handleInventoryCommand");
}

void Script::handleStatusCommand() {
	warning("STUB: handleStatusCommand");
}

void Script::handleRestCommand() {
	warning("STUB: handleRestCommand");
}

void Script::handleAcceptCommand() {
	warning("STUB: handleAcceptCommand");
}

void Script::handleTakeCommand(const char *target) {
	warning("STUB: handleTakeCommand");
}

void Script::handleDropCommand(const char *target) {
	warning("STUB: handleDropCommand");
}

void Script::handleAimCommand(const char *target) {
	warning("STUB: handleAimCommand");
}

void Script::handleWearCommand(const char *target) {
	warning("STUB: handleWearCommand");
}

void Script::handleOfferCommand(const char *target) {
	warning("STUB: handleOfferCommand");
}

bool Script::tryAttack(Weapon *weapon, Common::String &input) {
	warning("STUB: tryAttack");

	return false;
}

void Script::handleAttack(Weapon *weapon) {
	warning("STUB: handleAttack");
}

} // End of namespace Wage
