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

#include "audio/mixer.h"
#include "common/config-manager.h"
#include "engines/util.h"
#include "bagel/console.h"
#include "bagel/music.h"
#include "bagel/spacebar/spacebar.h"
#include "bagel/spacebar/master_win.h"
#include "bagel/spacebar/bib_odds_wnd.h"
#include "bagel/spacebar/main_window.h"
#include "bagel/boflib/app.h"
#include "bagel/dialogs/start_dialog.h"
#include "bagel/dialogs/opt_window.h"
#include "bagel/baglib/button_object.h"
#include "bagel/boflib/file_functions.h"
#include "bagel/boflib/gui/movie.h"

namespace Bagel {
namespace SpaceBar {

#define LOGOSMK1        "$SBARDIR\\INTRO\\LOGO1.SMK"
#define LOGOSMK2        "$SBARDIR\\INTRO\\LOGO2.SMK"
#define LOGOSMK3        "$SBARDIR\\INTRO\\LOGO3.SMK"
#define LOGOSMK3EX      "$SBARDIR\\INTRO\\LOGO3EX.SMK"

static const BagelReg SPACEBAR_REG = {
	"The Space Bar",
	".",
	"spacebar.ini",
	"spacebar.sav",
	4000000,
	3,
	16,
	640,
	480
};

SpaceBarEngine *g_engine;

SpaceBarEngine::SpaceBarEngine(OSystem *syst, const ADGameDescription *gameDesc) :
		BagelEngine(syst, gameDesc), CBagel(&SPACEBAR_REG) {
		SBarBibOddsWnd::initialize();
		CMainWindow::initialize();

	g_engine = this;

	for (int i = 0; i < BIBBLE_NUM_BET_AREAS; ++i)
		g_cBetAreas[i] = CBetArea(BET_AREAS[i]);
}

SpaceBarEngine::~SpaceBarEngine() {
	g_engine = nullptr;

	CMainWindow::shutdown();
}

void SpaceBarEngine::initializePath(const Common::FSNode &gamePath) {
	BagelEngine::initializePath(gamePath);
	SearchMan.addDirectory("spacebar", gamePath.getChild("spacebar"), 0, 3);
}

ErrorCode SpaceBarEngine::initialize() {
	Assert(IsValidObject(this));
	CBofBitmap *pBmp = nullptr;

	CBagel::initialize();

	if (!errorOccurred()) {
		bool bShowLogo = true;

		if ((_masterWin = new CSBarMasterWin()) != nullptr) {
			// This is the primary game window
			setMainWindow(_masterWin);

			// Init sound system
			InitializeSoundSystem(1, 22050, 8);

			pBmp = new CBofBitmap(_masterWin->width(), _masterWin->height(), _pPalette);
			if (pBmp != nullptr) {
				pBmp->fillRect(nullptr, COLOR_BLACK);
			} else {
				reportError(ERR_MEMORY, "Unable to allocate a CBofBitmap");
			}

			_masterWin->show();
			_masterWin->validateRect(nullptr);

			// Paint the screen black
			if (pBmp != nullptr)
				pBmp->paint(_masterWin, 0, 0);

			_useOriginalSaveLoad = ConfMan.getBool("original_menus");

			bool bRestart = true;
			int saveSlot = ConfMan.hasKey("save_slot") ? ConfMan.getInt("save_slot") : -1;

			if (saveSlot != -1) {
				bRestart = loadGameState(saveSlot).getCode() != Common::kNoError;

			} else if (savesExist()) {
				bRestart = false;

				CBagStartDialog cDlg(buildSysDir("START.BMP"), _masterWin);

				CBofWindow *pLastWin = g_hackWindow;
				g_hackWindow = &cDlg;

				int nRetVal = cDlg.doModal();

				g_hackWindow = pLastWin;

				switch (nRetVal) {
				case RESTORE_BTN:
					break;

				case RESTART_BTN:
					bRestart = true;

					// Hide that dialog
					if (pBmp != nullptr) {
						pBmp->paint(_masterWin, 0, 0);
					}
					break;

				case QUIT_BTN:
					// Hide that dialog
					if (pBmp != nullptr) {
						pBmp->paint(_masterWin, 0, 0);
					}
					_masterWin->close();
					_masterWin = nullptr;
					break;
				}
			}

			if (bRestart) {
				// Should we show the intro movies?
				getOption("Startup", "ShowLogo", &bShowLogo, true);

				// Play intro movies, logo screens, etc...
				if (bShowLogo) {
					CBofString cString(LOGOSMK1);
					MACROREPLACE(cString);

					// Play the movie only if it exists
					if (fileExists(cString.GetBuffer())) {
						bofPlayMovie(_masterWin, cString.GetBuffer());
						if (pBmp != nullptr) {
							pBmp->paint(_masterWin, 0, 0);
						}
					}
					if (shouldQuit())
						goto exit;

					cString = LOGOSMK2;
					MACROREPLACE(cString);
					if (fileExists(cString.GetBuffer())) {
						bofPlayMovie(_masterWin, cString.GetBuffer());
						if (pBmp != nullptr) {
							pBmp->paint(_masterWin, 0, 0);
						}
					}
					if (shouldQuit())
						goto exit;

					// Use hi-res movie if user has a fast machine
					cString = (getMachineSpeed() < 100) ? LOGOSMK3EX : LOGOSMK3;
					MACROREPLACE(cString);

					if (fileExists(cString.GetBuffer())) {
						bofPlayMovie(_masterWin, cString.GetBuffer());
						if (pBmp != nullptr) {
							pBmp->paint(_masterWin, 0, 0);
						}
					}
				}
				if (shouldQuit())
					goto exit;

				// Start a new game (In entry vestibule)
				_masterWin->newGame();
			}

		} else {
			reportError(ERR_MEMORY, "Unable to allocate the main SpaceBar Window");
		}
	}

exit:

	delete pBmp;

	return _errCode;
}

ErrorCode SpaceBarEngine::shutdown() {
	CBagel::shutdown();

	// No more Sound System
	ShutDownSoundSystem();

	return _errCode;
}


ErrorCode SpaceBarEngine::InitializeSoundSystem(uint16 nChannels, uint32 nFreq, uint16 nBitsPerSample) {
	// Nothing to do

	return ERR_NONE;
}

ErrorCode SpaceBarEngine::ShutDownSoundSystem() {
	_mixer->stopAll();
	return _errCode;
}


Common::Error SpaceBarEngine::run() {
	// Initialize graphics mode
	Graphics::PixelFormat format(2, 5, 6, 5, 0, 11, 5, 0, 0);
	initGraphics(640, 480, &format);

	// Initialize systems
	_screen = new Graphics::Screen();
	_midi = new MusicPlayer();
	syncSoundSettings();

	// Set the engine's debugger console
	setDebugger(new Console());

	// Initialize
	preInit();
	initialize();

	// Run the app
	if (!errorOccurred() && !shouldQuit() && _masterWin)
		runApp();

	// shutdown
	preShutDown();
	shutdown();
	postShutDown();

	return Common::kNoError;
}

} // namespace SpaceBar
} // namespace Bagel
