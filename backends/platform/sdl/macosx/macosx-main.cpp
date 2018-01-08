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

#ifdef MACOSX

#include "backends/platform/sdl/macosx/macosx.h"
#include "backends/plugins/sdl/sdl-provider.h"
#include "base/commandLine.h"
#include "base/main.h"
#include "common/config-manager.h"
#include "common/fs.h"

#include "CoreFoundation/CoreFoundation.h"

#define PEGASUS_DVD_TARGET "pegasus-dvd-release"

int main(int argc, char *argv[]) {

	// Create our OSystem instance
	g_system = new OSystem_MacOSX();
	assert(g_system);

	// Pre initialize the backend
	((OSystem_MacOSX *)g_system)->init();

#ifdef DYNAMIC_MODULES
	PluginManager::instance().addPluginProvider(new SDLPluginProvider());
#endif

	// HACK: Special Pegasus release parameters

	// Attempt to detect the PP Data directory
	// Get URL of the Resource directory of the .app bundle
	CFURLRef fileUrl = CFBundleCopyBundleURL(CFBundleGetMainBundle());

	if (!fileUrl) {
		warning("Failed to get bundle URL");
		return 1;
	}

	// Try to convert the URL to an absolute path
	char buf[MAXPATHLEN];
	if (!CFURLGetFileSystemRepresentation(fileUrl, true, (UInt8 *)buf, sizeof(buf))) {
		warning("Failed to get FS representation of bundle URL");
		return 1;
	}

	CFRelease(fileUrl);

	Common::String bundlePath(buf);
	Common::FSNode bundleNode(bundlePath);
	Common::FSNode bundleParent = bundleNode.getParent();
	Common::FSNode ppDataDirectory = bundleParent.getChild("PP Data");

	Common::String ppDataPath;

	// If we have the "PP Data" folder in the same directory as this bundle
	if (ppDataDirectory.exists()) {
		// Try to use this directory
		ppDataPath = ppDataDirectory.getPath();
	} else {
		// Try to get it off the disc
		Common::String discPath("/Volumes/Journeyman/");
		Common::FSNode discNode(discPath);
		Common::FSNode discDataDirectory = discNode.getChild("PP Data");
		if (discDataDirectory.exists()) {
			ppDataPath = discDataDirectory.getPath();
		} else {
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
		ConfMan.set("platform", "macintosh", PEGASUS_DVD_TARGET);
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
	delete (OSystem_MacOSX *)g_system;

	return res;
}

#endif
