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

#include "m4/burger/rooms/section5/section5_room.h"
#include "m4/burger/vars.h"
#include "m4/wscript/wst_regs.h"

namespace M4 {
namespace Burger {
namespace Rooms {

void Section5Room::preload() {
	Rooms::Room::preload();
	_G(flags)[V186] = 0;
}

HotSpotRec *Section5Room::custom_hotspot_which(int32 x, int32 y) {
	HotSpotRec *hotspot = Rooms::Room::custom_hotspot_which(x, y);
	if (hotspot != nullptr || _G(flags)[V186] == 0 || !verifyMachineExists(_walker1) ||
		(_G(game).room_id != 502 && _G(game).room_id != 505))
		return hotspot;

	assert(_borkTable);
	int index = _walker1->myAnim8->myRegs[IDX_CELS_INDEX];
	int x1 = _borkTable[index]._x;
	int y1 = _borkTable[index]._y;
	int total = (x - x1) * (x - x1) + (y - y1) * (y - y1);

	return (total < _borkThreshold) ? &_borkHotspot : nullptr;
}

} // namespace Rooms
} // namespace Burger
} // namespace M4
