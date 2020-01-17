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

#include "ultima/shared/core/saveable_object.h"
#include "ultima/shared/core/tree_item.h"
#include "ultima/shared/core/named_item.h"
#include "ultima/shared/core/project_item.h"

namespace Ultima {
namespace Shared {

ClassDef SaveableObject::type() {
	return ClassDef("SaveableObject", nullptr);
}

bool SaveableObject::isInstanceOf(const ClassDef &classDef) const {
	ClassDef def = getType();
	for (;;) {
		if (def == classDef)
			return true;

		if (!def.hasParent())
			break;
		def = def.parent();
	}

	return false;
}

} // End of namespace Shared
} // End of namespace Ultima
