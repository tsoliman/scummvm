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
 */

#ifndef BURIED_GRAPHICS_H
#define BURIED_GRAPHICS_H

#include "common/rect.h"
#include "common/scummsys.h"

namespace Common {
class SeekableReadStream;
}

namespace Graphics {
class Font;
struct Surface;
}

namespace Buried {

class BuriedEngine;

enum Cursor {
	kCursorNone            =     0,

	// Windows cursors
	kCursorArrow           = 32512,
	kCursorWait            = 32514,

	// Buried in Time Cursors
	kCursorEmptyArrow      =   100,
	kCursorFinger          =   101,
	kCursorMagnifyingGlass =   102,
	kCursorOpenHand        =   103,
	kCursorClosedHand      =   104,
	kCursorPutDown         =   105,
	kCursorNextPage        =   106,
	kCursorPrevPage        =   107,
	kCursorMoveUp          =   108,
	kCursorMoveDown        =   109,
	kCursorLocateCursorA   =   110,
	kCursorLocateCursorB   =   111,
	kCursorArrowUp         =   112,
	kCursorArrowLeft       =   113,
	kCursorArrowDown       =   114,
	kCursorArrowRight      =   115
};

class GraphicsManager {
public:
	GraphicsManager(BuriedEngine *vm);
	~GraphicsManager();

	byte *getDefaultPalette() const { return _palette; }
	Graphics::Font *createFont(int size, bool bold = false) const;
	Cursor setCursor(Cursor newCursor);
	Graphics::Surface *getBitmap(uint32 bitmapID);
	Graphics::Surface *getBitmap(const Common::String &fileName);
	uint32 getColor(byte r, byte g, byte b);

	void invalidateRect(const Common::Rect &rect);
	const Common::Rect &getDirtyRect() const { return _dirtyRect; }

	void markMouseMoved() { _mouseMoved = true; }
	void updateScreen(bool drawWindows = true);
	Graphics::Surface *getScreen() const { return _screen; }

	void blit(const Graphics::Surface *surface, int x, int y);
	void blit(const Graphics::Surface *surface, const Common::Rect &srcRect, const Common::Rect &dstRect);
	void fillRect(const Common::Rect &rect, uint32 color);

	Graphics::Surface *remapPalettedFrame(const Graphics::Surface *frame, const byte *palette);

private:
	BuriedEngine *_vm;
	Cursor _curCursor;

	Common::Rect _dirtyRect;
	bool _mouseMoved;
	Graphics::Surface *_screen;
	byte *_palette;
	
	byte *createDefaultPalette() const;
	Graphics::Surface *getBitmap(Common::SeekableReadStream *stream);

	Common::SeekableReadStream *findArialStream(bool bold) const;
};

} // End of namespace Buried

#endif
