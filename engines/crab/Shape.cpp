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

/*
 * This code is based on the CRAB engine
 *
 * Copyright (c) Arvind Raja Yadav
 *
 * Licensed under MIT
 *
 */

#include "crab/Shape.h"

namespace Crab {

void Shape::load(rapidxml::xml_node<char> *node, const bool &echo) {
	if (nodeValid("polygon", node, echo)) {
		type = SHAPE_POLYGON;
		poly.load(node, rect);
	} else {
		rect.load(node, echo, "x", "y", "width", "height");
		if (nodeValid("ellipse", node, echo))
			type = SHAPE_ELLIPSE;
		else
			type = SHAPE_RECT;
	}
}

CollisionData Shape::Collide(Rect box) {
	CollisionData res;
	res.intersect = rect.Collide(box);

	if (res.intersect) {
		res.type = type;
		if (type == SHAPE_POLYGON) {
			PolygonCollisionResult pcr = poly.Collide(box);
			res.intersect = pcr.intersect;
			res.data.x = pcr.mtv.x;
			res.data.y = pcr.mtv.y;
			return res;
		} else
			res.data = rect;
	}

	return res;
}

bool Shape::Contains(const Vector2i &pos) {
	if (rect.Contains(pos)) {
		if (type == SHAPE_POLYGON)
			return poly.Contains(pos.x, pos.y);
		else
			return true;
	}

	return false;
}

void Shape::draw(const int &XOffset, const int &YOffset, const uint8 &r, const uint8 &g, const uint8 &b, const uint8 &a) {
	if (type == SHAPE_POLYGON)
		poly.draw(XOffset, YOffset, r, g, b, a);
	else
		rect.draw(XOffset, YOffset, r, g, b, a);
}

} // End of namespace Crab
