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

#define FORBIDDEN_SYMBOL_ALLOW_ALL

#include "backends/platform/sdl/sdl-window.h"

#include "common/textconsole.h"

#include "icons/scummvm.xpm"

#if SDL_VERSION_ATLEAST(2, 0, 0)
static const uint32 fullscreenMask = SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_FULLSCREEN;
#endif

SdlWindow::SdlWindow()
#if SDL_VERSION_ATLEAST(2, 0, 0)
	: _window(nullptr), _inputGrabState(false), _windowCaption("ScummVM"),
	_lastFlags(0), _lastX(SDL_WINDOWPOS_UNDEFINED), _lastY(SDL_WINDOWPOS_UNDEFINED)
#endif
	{
}

SdlWindow::~SdlWindow() {
#if SDL_VERSION_ATLEAST(2, 0, 0)
	destroyWindow();
#endif
}

void SdlWindow::setupIcon() {
	int x, y, w, h, ncols, nbytes, i;
	unsigned int rgba[256];
	unsigned int *icon;

	if (sscanf(scummvm_icon[0], "%d %d %d %d", &w, &h, &ncols, &nbytes) != 4) {
		warning("Wrong format of scummvm_icon[0] (%s)", scummvm_icon[0]);

		return;
	}
	if ((w > 512) || (h > 512) || (ncols > 255) || (nbytes > 1)) {
		warning("Could not load the built-in icon (%d %d %d %d)", w, h, ncols, nbytes);
		return;
	}
	icon = (unsigned int*)malloc(w*h*sizeof(unsigned int));
	if (!icon) {
		warning("Could not allocate temp storage for the built-in icon");
		return;
	}

	for (i = 0; i < ncols; i++) {
		unsigned char code;
		char color[32];
		memset(color, 0, sizeof(color));
		unsigned int col;
		if (sscanf(scummvm_icon[1 + i], "%c c %s", &code, color) != 2) {
			warning("Wrong format of scummvm_icon[%d] (%s)", 1 + i, scummvm_icon[1 + i]);
		}
		if (!strcmp(color, "None"))
			col = 0x00000000;
		else if (!strcmp(color, "black"))
			col = 0xFF000000;
		else if (color[0] == '#') {
			if (sscanf(color + 1, "%06x", &col) != 1) {
				warning("Wrong format of color (%s)", color + 1);
			}
			col |= 0xFF000000;
		} else {
			warning("Could not load the built-in icon (%d %s - %s) ", code, color, scummvm_icon[1 + i]);
			free(icon);
			return;
		}

		rgba[code] = col;
	}
	for (y = 0; y < h; y++) {
		const char *line = scummvm_icon[1 + ncols + y];
		for (x = 0; x < w; x++) {
			icon[x + w * y] = rgba[(int)line[x]];
		}
	}

	SDL_Surface *sdl_surf = SDL_CreateRGBSurfaceFrom(icon, w, h, 32, w * 4, 0xFF0000, 0x00FF00, 0x0000FF, 0xFF000000);
	if (!sdl_surf) {
		warning("SDL_CreateRGBSurfaceFrom(icon) failed");
	}

#if SDL_VERSION_ATLEAST(2, 0, 0)
	if (_window) {
		SDL_SetWindowIcon(_window, sdl_surf);
	}
#else
	SDL_WM_SetIcon(sdl_surf, NULL);
#endif

	SDL_FreeSurface(sdl_surf);
	free(icon);
}

void SdlWindow::setWindowCaption(const Common::String &caption) {
#if SDL_VERSION_ATLEAST(2, 0, 0)
	_windowCaption = caption;
	if (_window) {
		SDL_SetWindowTitle(_window, caption.c_str());
	}
#else
	SDL_WM_SetCaption(caption.c_str(), caption.c_str());
#endif
}

void SdlWindow::toggleMouseGrab() {
#if SDL_VERSION_ATLEAST(2, 0, 0)
	if (_window) {
		_inputGrabState = !(SDL_GetWindowGrab(_window) == SDL_TRUE);
		SDL_SetWindowGrab(_window, _inputGrabState ? SDL_TRUE : SDL_FALSE);
	}
#else
	if (SDL_WM_GrabInput(SDL_GRAB_QUERY) == SDL_GRAB_OFF) {
		SDL_WM_GrabInput(SDL_GRAB_ON);
	} else {
		SDL_WM_GrabInput(SDL_GRAB_OFF);
	}
#endif
}

bool SdlWindow::hasMouseFocus() const {
#if SDL_VERSION_ATLEAST(2, 0, 0)
	if (_window) {
		return (SDL_GetWindowFlags(_window) & SDL_WINDOW_MOUSE_FOCUS);
	} else {
		return false;
	}
#else
	return (SDL_GetAppState() & SDL_APPMOUSEFOCUS);
#endif
}

void SdlWindow::warpMouseInWindow(uint x, uint y) {
#if SDL_VERSION_ATLEAST(2, 0, 0)
	if (_window && hasMouseFocus()) {
		SDL_WarpMouseInWindow(_window, x, y);
	}
#else
	SDL_WarpMouse(x, y);
#endif
}

void SdlWindow::iconifyWindow() {
#if SDL_VERSION_ATLEAST(2, 0, 0)
	if (_window) {
		SDL_MinimizeWindow(_window);
	}
#else
	SDL_WM_IconifyWindow();
#endif
}

bool SdlWindow::getSDLWMInformation(SDL_SysWMinfo *info) const {
	SDL_VERSION(&info->version);
#if SDL_VERSION_ATLEAST(2, 0, 0)
	return SDL_GetWindowWMInfo(_window, info);
#else
	return SDL_GetWMInfo(info);
#endif
}

#if SDL_VERSION_ATLEAST(2, 0, 0)
SDL_Surface *copySDLSurface(SDL_Surface *src) {
	const bool locked = SDL_MUSTLOCK(src) == SDL_TRUE;

	if (locked) {
		if (SDL_LockSurface(src) != 0) {
			return nullptr;
		}
	}

	SDL_Surface *res = SDL_CreateRGBSurfaceFrom(src->pixels,
	                       src->w, src->h, src->format->BitsPerPixel,
	                       src->pitch, src->format->Rmask, src->format->Gmask,
	                       src->format->Bmask, src->format->Amask);

	if (locked) {
		SDL_UnlockSurface(src);
	}

	return res;
}

bool SdlWindow::createOrUpdateWindow(int width, int height, uint32 flags) {
	if (_inputGrabState) {
		flags |= SDL_WINDOW_INPUT_GRABBED;
	}

	// SDL_WINDOW_RESIZABLE can also be updated without recreating the window
	// starting with SDL 2.0.5, but it is not treated as updateable here
	// because:
	// 1. It is currently only changed in conjunction with the SDL_WINDOW_OPENGL
	//    flag, so the window will always be recreated anyway when changing
	//    resizability; and
	// 2. Users (particularly on Windows) will sometimes swap older SDL DLLs
	//    to avoid bugs, which would be impossible if the feature was enabled
	//    at compile time using SDL_VERSION_ATLEAST.
	const uint32 updateableFlagsMask = fullscreenMask | SDL_WINDOW_INPUT_GRABBED;

	const uint32 oldNonUpdateableFlags = _lastFlags & ~updateableFlagsMask;
	const uint32 newNonUpdateableFlags = flags & ~updateableFlagsMask;

	if (!_window || oldNonUpdateableFlags != newNonUpdateableFlags) {
		destroyWindow();
		_window = SDL_CreateWindow(_windowCaption.c_str(), _lastX,
								   _lastY, width, height, flags);
		if (_window) {
			setupIcon();
		}
	} else {
		const uint32 fullscreenFlags = flags & fullscreenMask;

		if (fullscreenFlags) {
			SDL_DisplayMode fullscreenMode;
			fullscreenMode.w = width;
			fullscreenMode.h = height;
			fullscreenMode.driverdata = nullptr;
			fullscreenMode.format = 0;
			fullscreenMode.refresh_rate = 0;
			SDL_SetWindowDisplayMode(_window, &fullscreenMode);
		} else {
			SDL_SetWindowSize(_window, width, height);
		}

		SDL_SetWindowFullscreen(_window, fullscreenFlags);
		SDL_SetWindowGrab(_window, (flags & SDL_WINDOW_INPUT_GRABBED) ? SDL_TRUE : SDL_FALSE);
	}

	if (!_window) {
		return false;
	}

	_lastFlags = flags;

	// The call to SDL_DestroyWindow (from destroyWindow()) causes a SDL_WINDOWEVENT_RESIZED event
	// to be sent with the old size when the destroyed window is in full screen. The code below will
	// add an SDL_WINDOWEVENT_SIZE_CHANGE to the event stack so that we get the proper size. That way
	// handleResizeEvent() in SdlEventSource gets called last with the correct size.
	SDL_SetWindowSize(_window, width, height);

	return true;
}

void SdlWindow::destroyWindow() {
	if (_window) {
		if (!(_lastFlags & fullscreenMask)) {
			SDL_GetWindowPosition(_window, &_lastX, &_lastY);
		}
		SDL_DestroyWindow(_window);
		_window = nullptr;
	}
}
#endif
