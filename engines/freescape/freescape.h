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

#ifndef FREESCAPE_H
#define FREESCAPE_H

#include "common/bitarray.h"
#include "common/random.h"
#include "engines/engine.h"
#include "graphics/palette.h"
#include "graphics/surface.h"
#include "graphics/tinygl/pixelbuffer.h"

#include "audio/mixer.h"
#include "audio/decoders/wave.h"
#include "audio/softsynth/pcspk.h"

#include "freescape/area.h"
#include "freescape/objects/geometricobject.h"
#include "freescape/objects/entrance.h"
#include "freescape/gfx.h"

namespace Freescape {

class Renderer;

#define FREESCAPE_DATA_BUNDLE Common::String("freescape.dat")

enum CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

typedef Common::HashMap<uint16, Area*> AreaMap;
typedef Common::Array<byte*> ColorMap;
typedef Common::HashMap<uint16, int32> StateVars;
typedef Common::HashMap<uint16, uint32> StateBits;

enum {
	kFreescapeDebugMove = 1 << 0,
	kFreescapeDebugParser = 1 << 1,
	kFreescapeDebugCode = 1 << 2,
	kFreescapeDebugMedia = 1 << 4,
};

struct entrancesTableEntry {
	int id;
	int position[3];
};

class FreescapeEngine : public Engine {
private:
	// We need random numbers
	Common::RandomSource *_rnd;

public:
	FreescapeEngine(OSystem *syst);
	~FreescapeEngine();

	// Game selection
	bool isDriller() { return _targetName.hasPrefix("driller") || _targetName.hasPrefix("spacestationoblivion"); }
	bool isDark() { return _targetName.hasPrefix("darkside"); }
	bool isEclipse() { return _targetName.hasPrefix("totaleclipse"); }
	bool isCastle() { return _targetName.hasPrefix("castle"); }

	Common::Error run() override;

	// UI
	Common::Rect _viewArea;
	Common::Rect _fullscreenViewArea;

	void convertBorder();
	void drawBorder();
	virtual void drawUI();
	Texture *_borderTexture;

	// Parsing assets
	uint8 _binaryBits;
	virtual void loadAssets();
	Common::Archive *_dataBundle;
	void loadDataBundle();
	void loadBorder();
	void loadColorPalette();

	// 16-bit
	void load16bitBinary(Common::SeekableReadStream *file);

	// 8-bit
	void load8bitBinary(Common::SeekableReadStream *file, int offset, int ncolors);
	Area *load8bitArea(Common::SeekableReadStream *file, uint16 ncolors);
	Object *load8bitObject(Common::SeekableReadStream *file);

	// Areas
	uint16 _startArea;
	AreaMap _areaMap;
	Area *_currentArea;
	Math::Vector3d _scale;

	virtual void gotoArea(uint16 areaID, int entranceID);
	// Entrance
	uint16 _startEntrance;
	Common::HashMap<int, const struct entrancesTableEntry*> _entranceTable;

	// Input
	bool _flyMode;
	bool _noClipMode;
	void processInput();
	virtual void pressedKey(const int keycode);
	void move(CameraMovement direction, uint8 scale, float deltaTime);
	void changePlayerHeight(int delta);
	void rise();
	void lower();
	bool checkFloor(Math::Vector3d currentPosition);
	bool tryStepUp(Math::Vector3d currentPosition);
	bool tryStepDown(Math::Vector3d currentPosition);

	void rotate(Common::Point lastMousePos, Common::Point mousePos);
	// Input state
	float _lastFrame;
	Common::Point _lastMousePos;

	// Interaction
	void shoot();

	// Euler Angles
	float _yaw;
	float _pitch;
	void traverseEntrance(uint16 entranceID);
	Math::Vector3d directionToVector(float pitch, float heading);

	// Camera options
	float _mouseSensitivity;
	float _movementSpeed;
	Math::Vector3d _cameraFront, _cameraRight;
	// Spacial attributes
	Math::Vector3d _position, _rotation, _velocity;
	Math::Vector3d _lastPosition;
	int _playerHeightNumber;
	Common::Array<int> _playerHeights;
	uint16 _playerHeight;
	uint16 _playerWidth;
	uint16 _playerDepth;

	// Effects
	Common::Array<Common::String*> _conditionSources;
	Common::Array<FCLInstructionVector> _conditions;

	bool checkCollisions(bool executeCode);
	void executeObjectConditions(GeometricObject *obj, bool shot, bool collided);
	void executeLocalGlobalConditions(bool shot, bool collided);
	void executeCode(FCLInstructionVector &code, bool shot, bool collided);

	// Instructions
	void executeIncrementVariable(FCLInstruction &instruction);
	void executeDecrementVariable(FCLInstruction &instruction);
	void executeGoto(FCLInstruction &instruction);
	void executeIfThenElse(FCLInstruction &instruction);
	void executeMakeInvisible(FCLInstruction &instruction);
	void executeMakeVisible(FCLInstruction &instruction);
	void executeToggleVisibility(FCLInstruction &instruction);
	void executeDestroy(FCLInstruction &instruction);
	void executeRedraw(FCLInstruction &instruction);
	void executeSound(FCLInstruction &instruction);
	void executeDelay(FCLInstruction &instruction);
	bool executeEndIfNotEqual(FCLInstruction &instruction);
	void executeSetBit(FCLInstruction &instruction);
	void executeClearBit(FCLInstruction &instruction);
	void executeToggleBit(FCLInstruction &instruction);
	bool executeEndIfBitNotEqual(FCLInstruction &instruction);
	bool executeEndIfVisibilityIsEqual(FCLInstruction &instruction);
	void executeSwapJet(FCLInstruction &instruction);
	void executePrint(FCLInstruction &instruction);

	// Sound
	Audio::SoundHandle _handle;
	bool _usePrerecordedSounds;
	void playSound(int index);
	void playWav(const Common::String filename);
	void playSoundConst(double hzFreq, int duration);
	void playSoundSweepIncWL(double hzFreq1, double hzFreq2, double wlStepPerMS, int resolution);
	void playTeleporter(int totalIters);

	// Rendering
	int _screenW, _screenH;
	Renderer *_gfx;
	Common::String _renderMode;
	Graphics::PixelBuffer *getPalette(uint8 areaNumber, uint8 c1, uint8 c2, uint8 c3, uint8 c4, uint16 ncolors);
	ColorMap _colorMap;
	void drawFrame();
	uint8 _colorNumber;
	Math::Vector3d _scaleVector;
	float _nearClipPlane;
	float _farClipPlane;
	Graphics::Surface *_border;

	// Text messages and Fonts
	Common::StringArray _messagesList;
	void loadMessages(Common::SeekableReadStream *file, int offset, int size, int number);
	void loadFonts(Common::SeekableReadStream *file, int offset);
	Common::StringArray _currentAreaMessages;
	Common::StringArray _currentEphymeralMessages;
	Common::BitArray _font;
	void drawStringInSurface(const Common::String &str, int x, int y, uint32 fontColor, uint32 backColor, Graphics::Surface *surface);


	// Game state
	virtual void initGameState();
	StateVars _gameStateVars;
	StateBits _gameStateBits;
	virtual bool checkIfGameEnded();

	bool hasFeature(EngineFeature f) const override;
	bool canLoadGameStateCurrently() override { return true; }
	bool canSaveAutosaveCurrently() override { return false; }
	bool canSaveGameStateCurrently() override { return true; }
	Common::Error loadGameStream(Common::SeekableReadStream *stream) override;
	Common::Error saveGameStream(Common::WriteStream *stream, bool isAutosave = false) override;
};

class DrillerEngine : public FreescapeEngine {
public:
	DrillerEngine(OSystem *syst);

	uint32 _initialJetEnergy;
	uint32 _initialJetShield;

	uint32 _initialProveEnergy;
	uint32 _initialProveShield;

	void initGameState() override;
	bool checkIfGameEnded() override;

	void gotoArea(uint16 areaID, int entranceID) override;

	void loadAssets() override;
	void drawUI() override;

	void pressedKey(const int keycode) override;

	private:
	bool drillDeployed();
	void addDrill(const Math::Vector3d position);
	void removeDrill();
};

class DarkEngine : public FreescapeEngine {
public:
	DarkEngine(OSystem *syst);

	void loadAssets() override;
	void gotoArea(uint16 areaID, int entranceID) override;
	void drawUI() override;
};

class EclipseEngine : public FreescapeEngine {
public:
	EclipseEngine(OSystem *syst);

	void loadAssets() override;

	void gotoArea(uint16 areaID, int entranceID) override;

	void drawUI() override;
};

class CastleEngine : public FreescapeEngine {
public:
	CastleEngine(OSystem *syst);

	void loadAssets() override;

	void gotoArea(uint16 areaID, int entranceID) override;
};

extern FreescapeEngine *g_freescape;

} // namespace Freescape

#endif
