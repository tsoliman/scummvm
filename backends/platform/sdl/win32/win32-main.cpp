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

// Disable symbol overrides so that we can use system headers.
#define FORBIDDEN_SYMBOL_ALLOW_ALL

#include "common/scummsys.h"

#ifdef WIN32

// Fix for bug #2895217 "MSVC compilation broken with r47595":
// We need to keep this on top of the "common/scummsys.h"(base/main.h) include,
// otherwise we will get errors about the windows headers redefining
// "ARRAYSIZE" for example.
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef ARRAYSIZE // winnt.h defines ARRAYSIZE, but we want our own one...

#include "backends/platform/sdl/win32/win32.h"
#include "backends/plugins/sdl/sdl-provider.h"
#include "base/commandLine.h"
#include "base/main.h"
#include "common/config-manager.h"
#include "common/fs.h"

int __stdcall WinMain(HINSTANCE /*hInst*/, HINSTANCE /*hPrevInst*/,  LPSTR /*lpCmdLine*/, int /*iShowCmd*/) {
	SDL_SetModuleHandle(GetModuleHandle(NULL));
	return main(__argc, __argv);
}

#define PEGASUS_DVD_TARGET "pegasus-dvd-release"

int main(int argc, char *argv[]) {
	// Create our OSystem instance
	g_system = new OSystem_Win32();
	assert(g_system);

	// Pre initialize the backend
	((OSystem_Win32 *)g_system)->init();

#ifdef DYNAMIC_MODULES
	PluginManager::instance().addPluginProvider(new SDLPluginProvider());
#endif

	// Get the path to our EXE
	HMODULE hModule = GetModuleHandleW(NULL);
	WCHAR wideCharPath[MAX_PATH];
	GetModuleFileNameW(hModule, wideCharPath, MAX_PATH);

	// Convert to ANSI
	char buf[MAX_PATH];
	WideCharToMultiByte(CP_ACP, 0, wideCharPath, -1, buf, MAX_PATH, NULL, NULL);

	// Find the directory the EXE is in
	Common::String exePath(buf);
	Common::FSNode exeNode(exePath);
	Common::FSNode ppDataDirectory = exeNode.getParent().getChild("PP Data");

	Common::String ppDataPath;

	// If we have the "PP Data" folder in the same directory as this bundle
	if (ppDataDirectory.exists()) {
		// Try to use this directory
		ppDataPath = ppDataDirectory.getPath();
	} else {
		// Search mounted volumes for the Journeyman disc
		bool foundData = false;
		char szLogicalDrives[26 * 4 + 1];
		DWORD dwResult = GetLogicalDriveStrings(sizeof(szLogicalDrives), szLogicalDrives);
		if (dwResult > 0 && dwResult <= sizeof(szLogicalDrives)) {
			char *szSingleDrive = szLogicalDrives;
			while (*szSingleDrive) {
				if (GetVolumeInformation(szSingleDrive, buf, sizeof(buf), NULL, NULL, NULL, NULL, 0) && !scumm_stricmp(buf, "Journeyman")) {
					Common::String discPath(szSingleDrive);
					Common::FSNode discNode(discPath);
					Common::FSNode discDataDirectory = discNode.getChild("PP Data");
					if (discDataDirectory.exists()) {
						foundData = true;
						ppDataPath = discDataDirectory.getPath();
						break;
					}
				}
				szSingleDrive += strlen(szSingleDrive) + 1;
			}
		}

		if (!foundData) {
			warning("Game data missing");
			return 1;
		}
	}

	// Work this into the config file
	Base::registerDefaults();
	ConfMan.loadDefaultConfigFile();

	// Add the special target if it doesn't already exist
	if (!ConfMan.hasGameDomain(PEGASUS_DVD_TARGET)) {
		ConfMan.addGameDomain(PEGASUS_DVD_TARGET);
		ConfMan.set("gameid", "pegasus", PEGASUS_DVD_TARGET);
		ConfMan.set("gfx_mode", "opengl_linear", PEGASUS_DVD_TARGET);
		ConfMan.set("fullscreen", "true", PEGASUS_DVD_TARGET);
		ConfMan.set("console", "false", PEGASUS_DVD_TARGET);
		ConfMan.set("platform", "windows", PEGASUS_DVD_TARGET);
	}

	// Always update the path
	ConfMan.set("path", ppDataPath, PEGASUS_DVD_TARGET);

	// Flush for good luck
	ConfMan.flushToDisk();

	const char *pegasusParams[] = {
		argv[0],
		"--gui-theme=scummpegasus",
		PEGASUS_DVD_TARGET
	};

	// Invoke the actual ScummVM main entry point:
	int res = scummvm_main(ARRAYSIZE(pegasusParams), pegasusParams);

	// Free OSystem
	delete (OSystem_Win32 *)g_system;

	return res;
}

#endif
