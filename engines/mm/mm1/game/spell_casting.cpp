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

#include "mm/mm1/game/spell_casting.h"
#include "mm/mm1/maps/maps.h"
#include "mm/mm1/globals.h"

namespace MM {
namespace MM1 {
namespace Game {

static const int8 SPELLS_SP_GEMS[47 * 2] = {
	 0,   0,  0,  0, 0, -1, 0, 0,
	 0,   1,  0,  0, 0,  0, 0, 0,
	 1,   0,  0,  0, 0,  0, 0, 1,
	 0,   0,  0,  0, 2,  0, 2, 2,
	 0,   0,  0,  3, 3,
	 4,   4,  4,  4, 4,
	10,   5,  5,  5, 5,

	 0,   0, -1,  0, 0,  0, 0, 0,
	 0,   0,  1,  0, 0,  0, 0, 0,
	-1,   0,  1, -1, 0,  0, 1, 0,
	 0,   0,  2,  0, 0,  2, 2, 2,
	 0,   0,  3,  3, 3,
	 4,   4,  4,  4, 4,
	 5, 100,  5,  5, 5
};

static const byte SPELL_FLAGS[47 * 2] = {
	 1,  1,  9,  4,  2,  4,  0,  1,
	 4,  5,  9,  0,  0,  0,  9,  9,
	 2,  4,  4,  2,  9,  9,  2,  2,
	 6,  6,  0,  0,  6, 25,  5,  2,
	17,  0,  1,  4,  4,
	17,  4,  6,  4,  2,
	 1,  1,  0,  6, 25,

	 1,  2,  9,  9,  0,  2,  2,  9,
	 9,  9,  9,  2,  2,  5,  5,  9,
	 9, 18,  1,  9,  1,  1,  1,  9,
	 9,  9,  9,  9,  2,  0,  1,  1,
	17,  0,  9,  2,  2,
	 1,  9,  2,  0,  2,
	 2,  2, 17,  1,  1
};

enum SpellFlag {
	SF_COMBAT_ONLY = 1,
	SF_CAST_ON = 4,
	SF_OUTDOORS_ONLY = 0x10
};

void SpellCasting::setSpell(Character *chr, int lvl, int num) {
	int lvlNum;
	int setNum = chr->_class == ARCHER || chr->_class == SORCERER ? 1 : 0;
	_spellState = SS_OK;

	// Figure the offset in the spell list
	int spellNum = 0;
	for (lvlNum = 2; lvlNum < MIN(lvl, 5); ++lvlNum)
		spellNum += 8;
	for (lvlNum = 5; lvlNum < lvl; ++lvlNum)
		spellNum += 5;

	// Get required SP
	int spellIndex = setNum * 47 + spellNum;
	int requiredSp = lvl - 1;

	if (SPELLS_SP_GEMS[spellIndex] < 0)
		// required SP increases with character's level
		requiredSp = chr->_level;

	if (!chr->_v2c) {
		if (SPELLS_SP_GEMS[spellIndex] < 0 && chr->_sp._current < chr->_level._current)
			_spellState = SS_NOT_ENOUGH_SP;
		else if ((lvl - 1) > chr->_sp._current)
			_spellState = SS_NOT_ENOUGH_SP;
	}

	int requiredGems = (uint8)SPELLS_SP_GEMS[spellIndex] & 0x7f;
	if (_spellState == SS_OK)
		setSpell(spellIndex, requiredSp, requiredGems);
}

void SpellCasting::setSpell(int spellIndex, int requiredSp, int requiredGems) {
	_spellIndex = spellIndex;
	_requiredSp = requiredSp;
	_requiredGems = requiredGems;
	_spellState = SS_OK;

	Maps::Map &map = *g_maps->_currentMap;

	if (SPELL_FLAGS[spellIndex] & SF_COMBAT_ONLY)
		_spellState = SS_COMBAT_ONLY;
	else if ((SPELL_FLAGS[spellIndex] & SF_OUTDOORS_ONLY) && !(map[0] & 0x80))
		_spellState = SS_OUTDOORS_ONLY;
	else if (g_maps->_currentState & 2)
		_spellState = SS_MAGIC_DOESNT_WORK;
}

bool SpellCasting::hasCharTarget() const {
	return (SPELL_FLAGS[_spellIndex] & SF_CAST_ON) != 0;
}

Common::String SpellCasting::getSpellError() const {
	switch (_spellState) {
	case SS_NOT_ENOUGH_SP:
		return STRING["dialogs.misc.not_enough_sp"];
	case SS_NOT_ENOUGH_GEMS:
		return STRING["dialogs.misc.not_enough_gems"];
	case SS_COMBAT_ONLY:
		return STRING["dialogs.misc.combat_only"];
	case SS_DOESNT_WORK:
		return STRING["dialogs.misc.magic_doesnt_work"];
	case SS_OUTDOORS_ONLY:
		return STRING["dialogs.misc.outdoors_only"];
	default:
		return STRING["dialogs.misc.done"];
	}
}

void SpellCasting::castSpell(int spellIndex, Character *destChar) {
	// TODO
}

} // namespace Game
} // namespace MM1
} // namespace MM
