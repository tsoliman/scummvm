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
#include "engines/util.h"
#include "bagel/console.h"
#include "bagel/spacebar/spacebar.h"
#include "bagel/spacebar/master_win.h"
#include "bagel/spacebar/bib_odds_wnd.h"
#include "bagel/boflib/app.h"
#include "bagel/baglib/start_dialog.h"
#include "bagel/baglib/opt_window.h"
#include "bagel/baglib/buttons.h"
#include "bagel/boflib/gui/movie.h"

namespace Bagel {
namespace SpaceBar {

#define LOGOSMK1 		"$SBARDIR\\INTRO\\LOGO1.SMK"
#define LOGOSMK2 		"$SBARDIR\\INTRO\\LOGO2.SMK"
#define LOGOSMK3   		"$SBARDIR\\INTRO\\LOGO3.SMK"
#define LOGOSMK3EX 		"$SBARDIR\\INTRO\\LOGO3EX.SMK"

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

SpaceBarEngine::SpaceBarEngine(OSystem *syst, const ADGameDescription *gameDesc) :
		BagelEngine(syst, gameDesc), CBagel(&SPACEBAR_REG) {
	SBarBibOddsWnd::initStatics();
}

ERROR_CODE SpaceBarEngine::Initialize() {
	Assert(IsValidObject(this));

	CBagel::Initialize();

	if (!ErrorOccurred()) {
		CSBarMasterWin *pGameWindow;
		BOOL bShowLogo;

		bShowLogo = TRUE;

		if ((pGameWindow = new CSBarMasterWin()) != nullptr) {
			// This is the primary game window
			SetMainWindow(pGameWindow);

			// Init sound system
			InitializeSoundSystem(1, 22050, 8);

			CBofBitmap *pBmp;
			if ((pBmp = new CBofBitmap(pGameWindow->Width(), pGameWindow->Height(), m_pPalette)) != nullptr) {
				pBmp->FillRect(nullptr, COLOR_BLACK);
			} else {
				ReportError(ERR_MEMORY, "Unable to allocate a CBofBitmap");
			}

			pGameWindow->Show();
			pGameWindow->ValidateRect(nullptr);

			// Paint the screen black
			if (pBmp != nullptr)
				pBmp->Paint(pGameWindow, 0, 0);

			BOOL bRestart = TRUE;
			if (HaveSavedGames()) {
				bRestart = FALSE;

				CBagStartDialog cDlg(BuildSysDir("START.BMP"), nullptr, pGameWindow);
				INT nRetVal;

				CBofWindow *pLastWin = g_pHackWindow;
				g_pHackWindow = &cDlg;

				nRetVal = cDlg.DoModal();

				g_pHackWindow = pLastWin;

				switch (nRetVal) {
				case RESTORE_BTN:
					break;

				case RESTART_BTN:
					bRestart = TRUE;

					// Hide that dialog
					if (pBmp != nullptr) {
						pBmp->Paint(pGameWindow, 0, 0);
					}
					break;

				case QUIT_BTN:
					// Hide that dialog
					if (pBmp != nullptr) {
						pBmp->Paint(pGameWindow, 0, 0);
					}
					pGameWindow->Close();
					break;
				}
			}

			if (bRestart) {
				// Should we show the intro movies?
				GetOption("Startup", "ShowLogo", &bShowLogo, TRUE);

				// Play intro movies, logo screens, etc...
				// (Unless user holds down the shift key, or ShowLogo=0 in SPACEBAR.INI)
				if (bShowLogo && !IsKeyDown(BKEY_SHIFT)) {
					CBofString cString(LOGOSMK1);
					MACROREPLACE(cString);

					// Play the movie only if it exists
					if (FileExists(cString.GetBuffer())) {
						BofPlayMovie(pGameWindow, cString.GetBuffer());
						if (pBmp != nullptr) {
							pBmp->Paint(pGameWindow, 0, 0);
						}
					}
					if (shouldQuit())
						return ERR_NONE;

					cString = LOGOSMK2;
					MACROREPLACE(cString);
					if (FileExists(cString.GetBuffer())) {
						BofPlayMovie(pGameWindow, cString.GetBuffer());
						if (pBmp != nullptr) {
							pBmp->Paint(pGameWindow, 0, 0);
						}
					}
					if (shouldQuit())
						return ERR_NONE;

					// Use hi-res movie if user has a fast machine
					cString = (GetMachineSpeed() < 100) ? LOGOSMK3EX : LOGOSMK3;
					MACROREPLACE(cString);

					if (FileExists(cString.GetBuffer())) {
						BofPlayMovie(pGameWindow, cString.GetBuffer());
						if (pBmp != nullptr) {
							pBmp->Paint(pGameWindow, 0, 0);
						}
					}
				}
				if (shouldQuit())
					return ERR_NONE;

				// Start a new game (In entry vestible)
				pGameWindow->NewGame();
			}

			if (pBmp != nullptr)
				delete pBmp;

		} else {
			ReportError(ERR_MEMORY, "Unable to allocate the main SpaceBar Window");
		}
	}

	return m_errCode;
}

ERROR_CODE SpaceBarEngine::ShutDown() {
	CBagel::ShutDown();

	// No more Sound System
	ShutDownSoundSystem();

	return m_errCode;
}


ERROR_CODE SpaceBarEngine::InitializeSoundSystem(WORD nChannels, DWORD nFreq, WORD nBitsPerSample) {
	// Nothing to do

	return ERR_NONE;
}

ERROR_CODE SpaceBarEngine::ShutDownSoundSystem() {
	_mixer->stopAll();
	return m_errCode;
}


Common::Error SpaceBarEngine::run() {
	// Initialize graphics mode
	Graphics::PixelFormat format(2, 5, 6, 5, 0, 11, 5, 0, 0);
	initGraphics(640, 480, &format);

	_screen = new Graphics::Screen();

	// Set the engine's debugger console
	setDebugger(new Console());

	// Initialize
	PreInit();
	Initialize();

	// Run the app
	if (!ErrorOccurred() && !shouldQuit())
		RunApp();

	// Shutdown
	PreShutDown();
	ShutDown();
	PostShutDown();

	return Common::kNoError;
}

} // namespace SpaceBar
} // namespace Bagel
