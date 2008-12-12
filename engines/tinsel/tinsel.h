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
 * $URL$
 * $Id$
 *
 */

#ifndef TINSEL_H
#define TINSEL_H

#include "common/scummsys.h"
#include "common/system.h"
#include "common/error.h"
#include "common/events.h"
#include "common/keyboard.h"
#include "common/util.h"

#include "sound/mididrv.h"
#include "sound/mixer.h"

#include "engines/engine.h"
#include "tinsel/debugger.h"
#include "tinsel/graphics.h"
#include "tinsel/sound.h"
#include "tinsel/dw.h"

namespace Tinsel {

class MidiMusicPlayer;
class PCMMusicPlayer;
class Scheduler;
class SoundManager;

enum TinselGameID {
	GID_DW1 = 0,
	GID_DW2 = 1
};

enum TinselGameFeatures {
	GF_DEMO = 1 << 0,
	GF_CD = 1 << 1,
	GF_FLOPPY = 1 << 2,
	GF_SCNFILES = 1 << 3,

	// The GF_USE_?FLAGS values specify how many country flags are displayed
	// in the subtitles options dialog.
	// None of these defined -> 1 language, in ENGLISH.TXT
	GF_USE_3FLAGS = 1 << 4,	// French, German, Spanish
	GF_USE_4FLAGS = 1 << 5,	// French, German, Spanish, Italian
	GF_USE_5FLAGS = 1 << 6	// All 5 flags
};

/**
 * The following is the ScummVM definitions of the various Tinsel versions:
 * TINSEL_V0 - This was an early engine version that was only used in the Discworld 1
 *			demo. It is not currently supported.
 * TINSEL_V1 - This was the engine version used by Discworld 1. Note that there were two
 *			major releases: an earlier version that used *.gra files, and a later one that
 *			used *.scn files, and contained certain script and engine bugfixes. In ScummVM,
 *			we treat both releases as 'Tinsel 1', since the engine fixes from the later
 *			version work equally well the earlier version data.
 * TINSEL_V2 - This is the engine used for the Discworld 2 game.
 */
enum TinselEngineVersion {
	TINSEL_V0 = 0,
	TINSEL_V1 = 1,
	TINSEL_V2 = 2
};

enum {
	kTinselDebugAnimations = 1 << 0,
	kTinselDebugActions = 1 << 1,
	kTinselDebugSound = 1 << 2,
	kTinselDebugMusic = 2 << 3
};

#define DEBUG_BASIC 1
#define DEBUG_INTERMEDIATE 2
#define DEBUG_DETAILED 3

struct TinselGameDescription;

enum TinselKeyDirection {
	MSK_LEFT = 1, MSK_RIGHT = 2, MSK_UP = 4, MSK_DOWN = 8,
	MSK_DIRECTION = MSK_LEFT | MSK_RIGHT | MSK_UP | MSK_DOWN
};

typedef bool (*KEYFPTR)(const Common::KeyState &);

#define	SCREEN_WIDTH	(_vm->screen().w)	// PC screen dimensions
#define	SCREEN_HEIGHT	(_vm->screen().h)
#define	SCRN_CENTRE_X	((SCREEN_WIDTH  - 1) / 2)	// screen centre x
#define	SCRN_CENTRE_Y	((SCREEN_HEIGHT - 1) / 2)	// screen centre y
#define UNUSED_LINES	48
#define EXTRA_UNUSED_LINES	3
//#define	SCREEN_BOX_HEIGHT1	(SCREEN_HEIGHT - UNUSED_LINES)
//#define	SCREEN_BOX_HEIGHT2	(SCREEN_BOX_HEIGHT1 - EXTRA_UNUSED_LINES)
#define	SCREEN_BOX_HEIGHT1	SCREEN_HEIGHT
#define	SCREEN_BOX_HEIGHT2	SCREEN_HEIGHT

#define GAME_FRAME_DELAY (1000 / ONE_SECOND)

#define TinselVersion (_vm->getVersion())
#define TinselV0 (TinselVersion == TINSEL_V0)
#define TinselV1 (TinselVersion == TINSEL_V1)
#define TinselV2 (TinselVersion == TINSEL_V2)

class TinselEngine : public Engine {
	int _gameId;
	Common::KeyState _keyPressed;
	Common::RandomSource _random;
	Graphics::Surface _screenSurface;
	Common::Point _mousePos;
	uint8 _dosPlayerDir;
	Console *_console;
	Scheduler *_scheduler;

	static const char *_sampleIndices[][3];
	static const char *_sampleFiles[][3];
	static const char *_textFiles[][3];

protected:

	// Engine APIs
	virtual Common::Error init();
	virtual Common::Error go();
	virtual bool hasFeature(EngineFeature f) const;
	Common::Error loadGameState(int slot);
#if 0
	Common::Error saveGameState(int slot, const char *desc);
#endif
	bool canLoadGameStateCurrently();
#if 0
	bool canSaveGameStateCurrently();
#endif
	virtual void syncSoundSettings();

public:
	TinselEngine(OSystem *syst, const TinselGameDescription *gameDesc);
	virtual ~TinselEngine();
	int getGameId() {
		return _gameId;
	}

	const TinselGameDescription *_gameDescription;
	uint32 getGameID() const;
	uint32 getFeatures() const;
	Common::Language getLanguage() const;
	uint16 getVersion() const;
	Common::Platform getPlatform() const;

	const char *getSampleIndex(LANGUAGE lang);
	const char *getSampleFile(LANGUAGE lang);
	const char *getTextFile(LANGUAGE lang);

	MidiDriver *_driver;
	SoundManager *_sound;
	MidiMusicPlayer *_midiMusic;
	PCMMusicPlayer *_pcmMusic;

	KEYFPTR _keyHandler;
private:
	//MidiMusicPlayer *_midiMusic;
	int _musicVolume;

	void NextGameCycle(void);
	void CreateConstProcesses(void);
	void RestartGame(void);
	void RestartDrivers(void);
	void ChopDrivers(void);
	void ProcessKeyEvent(const Common::Event &event);
	bool pollEvent();

public:
	const Common::String getTargetName() const { return _targetName; }
	Common::String getSavegameFilename(int16 saveNum) const;
	Common::SaveFileManager *getSaveFileMan() { return _saveFileMan; }
	Graphics::Surface &screen() { return _screenSurface; }

	Common::Point getMousePosition() const { return _mousePos; }
	void setMousePosition(const Common::Point &pt) {
		int ySize = (g_system->getHeight() - _screenSurface.h) / 2;
		g_system->warpMouse(pt.x, pt.y + ySize);
		_mousePos = pt;
	}
	void divertKeyInput(KEYFPTR fptr) { _keyHandler = fptr; }
	int getRandomNumber(int maxNumber) { return _random.getRandomNumber(maxNumber); }
	uint8 getKeyDirection() const { return _dosPlayerDir; }
};

// Global reference to the TinselEngine object
extern TinselEngine *_vm;

// Externally available methods
void CuttingScene(bool bCutting);
void CDChangeForRestore(int cdNumber);
void CdHasChanged(void);

} // End of namespace Tinsel

#endif /* TINSEL_H */
