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

#include "audio/decoders/wave.h"
#include "audio/audiostream.h"
#include "common/archive.h"
#include "common/config-manager.h"
#include "common/debug.h"
#include "common/debug-channels.h"
#include "common/error.h"
#include "common/events.h"
#include "common/file.h"
#include "common/savefile.h"
#include "common/system.h"
#include "common/str.h"
#include "common/timer.h"
#include "engines/util.h"
#include "image/bmp.h"

#include "private/cursors.h"
#include "private/private.h"
#include "private/tokens.h"
#include "private/grammar.h"

namespace Private {

PrivateEngine *g_private = NULL;

extern int parse(char *);

PrivateEngine::PrivateEngine(OSystem *syst, const ADGameDescription *gd)
    : Engine(syst), _gameDescription(gd) {
    _rnd = new Common::RandomSource("private");

    // Debug channels
    DebugMan.addDebugChannel(kPrivateDebugFunction, "functions", "Function execution debug channel");
    DebugMan.addDebugChannel(kPrivateDebugCode, "code", "Code execution debug channel");
    DebugMan.addDebugChannel(kPrivateDebugScript, "script", "Script execution debug channel");

    // Global object for external reference
    g_private = this;

    // Setting execution
    _nextSetting = "";
    _currentSetting = "";
    _pausedSetting = "";
    _modified = false;
    _mode = -1;
    _toTake = false;

    // Movies
    _nextMovie = "";
    _nextVS = "";
    _repeatedMovieExit = "";

    // Save and load
    _saveGameMask = {};
    _loadGameMask = {};

    // Interface
    _framePath = "inface/general/inface2.bmp";

    // Police
    _policeBustEnabled = false;
    _policeBustSetting = "";
    _numberClicks = 0;
    _sirenSound = "po/audio/posfx002.wav";

    // General sounds
    _globalAudioPath = "global/audio/";
    _noStopSounds = false;

    // Radios and phone
    _policeRadioArea = {};
    _AMRadioArea = {};
    _phoneArea = {};
    // TODO: use this as a default sound for radio
    _infaceRadioPath = "inface/radio/";
    _phonePrefix = "inface/telephon/";
    _phoneCallSound = "phone.wav";

    // Dossiers
    _dossierPage = 0;
    _dossierSuspect = 0;
    _dossierNextSuspectMask = {};
    _dossierPrevSuspectMask = {};

    // Diary
    _diaryLocPrefix = "inface/diary/loclist/";
}

PrivateEngine::~PrivateEngine() {
    // Dispose your resources here
    delete _frame;
    delete _rnd;

    // Remove all of our debug levels
    DebugMan.clearAllDebugChannels();
}

void PrivateEngine::initializePath(const Common::FSNode &gamePath) {
    SearchMan.addDirectory(gamePath.getPath(), gamePath, 0, 10);
}

void PrivateEngine::setOrigin(const int point[2]) {
    delete _origin;
    _origin = new Common::Point(point[0], point[1]);;
}

Common::Error PrivateEngine::run() {

    assert(_installerArchive.open("SUPPORT/ASSETS.Z"));
    Common::SeekableReadStream *file = NULL;
    // if the full game is used
    if (!isDemo()) {
        assert(_installerArchive.hasFile("GAME.DAT"));
        file = _installerArchive.createReadStreamForMember("GAME.DAT");
    } else {
        // if the demo from archive.org is used
        if (_installerArchive.hasFile("GAME.TXT"))
            file = _installerArchive.createReadStreamForMember("GAME.TXT");

        // if the demo from the full retail CDROM is used
        else {
            if (_installerArchive.hasFile("DEMOGAME.DAT"))
                file = _installerArchive.createReadStreamForMember("DEMOGAME.DAT");
        }
    }

    // Read assets file
    assert(file != NULL);
    char *buf = (char *)malloc(file->size()+1);
    file->read(buf, file->size()+1);

    // Initialize stuff
    initFuncs();
    initCursors();
    parse(buf);
    free(buf);
    delete file;
    assert(maps.constants.size() > 0);

    // Initialize graphics
    _screenW = 640;
    _screenH = 480;
    //_pixelFormat = Graphics::PixelFormat::createFormatCLUT8();
    _pixelFormat = Graphics::PixelFormat(4, 8, 8, 8, 8, 24, 16, 8, 0);
    _transparentColor = _pixelFormat.RGBToColor(0,255,0);
    initGraphics(_screenW, _screenH, &_pixelFormat);
    screenRect = Common::Rect(0, 0, _screenW, _screenH);
    changeCursor("default");
    _origin = new Common::Point(0, 0);
    _image = new Image::BitmapDecoder();
    _compositeSurface = new Graphics::ManagedSurface();
    _compositeSurface->create(_screenW, _screenH, _pixelFormat);
    _compositeSurface->setTransparentColor(_transparentColor);

    // Load the game frame once
    Common::File frameFile;
    assert(frameFile.open(convertPath(_framePath)));
    _image->loadStream(frameFile);
    _frame = _image->getSurface()->convertTo(_pixelFormat, _image->getPalette());

    // Main event loop
    Common::Event event;
    Common::Point mousePos;
    _videoDecoder = nullptr;

    int saveSlot = ConfMan.getInt("save_slot");
    if (saveSlot >= 0) { // load the savegame
        loadGameState(saveSlot);
    } else {
        _nextSetting = kGoIntro;
        //setNextSetting(new Common::String(kGoIntro));
    }

    while (!shouldQuit()) {
        checkPhoneCall();

        while (g_system->getEventManager()->pollEvent(event)) {
            mousePos = g_system->getEventManager()->getMousePos();
            // Events
            switch (event.type) {
            case Common::EVENT_KEYDOWN:
                if (event.kbd.keycode == Common::KEYCODE_ESCAPE && _videoDecoder)
                    skipVideo();

                break;

            case Common::EVENT_QUIT:
            case Common::EVENT_RETURN_TO_LAUNCHER:
                break;

            case Common::EVENT_LBUTTONDOWN:
                _numberClicks++;
                if (selectDossierNextSuspect(mousePos))
                    break;
                else if (selectDossierPrevSuspect(mousePos))
                    break;

                selectPauseMovie(mousePos);
                selectPhoneArea(mousePos);
                selectPoliceRadioArea(mousePos);
                selectAMRadioArea(mousePos);
                selectLoadGame(mousePos);
                selectSaveGame(mousePos);
                if (_nextSetting.empty())
                    selectMask(mousePos);
                if (_nextSetting.empty())
                    selectExit(mousePos);
                break;

            case Common::EVENT_MOUSEMOVE:
                // Reset cursor to default
                changeCursor("default");
                // The following functions will return true
                // if the cursor is changed
                if      (cursorPauseMovie(mousePos)) {}
                else if (cursorMask(mousePos))       {}
                else     cursorExit(mousePos);
                break;

            default:
                break;
            }
        }

        checkPoliceBust();

        // Movies
        if (!_nextMovie.empty()) {
            removeTimer();
            _videoDecoder = new Video::SmackerDecoder();
            playVideo(_nextMovie);
            _nextMovie = "";
            continue;
        }

        if (!_nextVS.empty() && _currentSetting == kMainDesktop) {
            loadImage(_nextVS, 160, 120);
            drawScreen();
        }

        if (_videoDecoder) {
            if (_videoDecoder->getCurFrame() == 0)
                stopSound(true);
            if (_videoDecoder->endOfVideo()) {
                _videoDecoder->close();
                delete _videoDecoder;
                _videoDecoder = nullptr;
            } else if (_videoDecoder->needsUpdate()) {
                drawScreen();
            }
            continue;
        }

        if (!_nextSetting.empty()) {
            removeTimer();
            debugC(1, kPrivateDebugFunction, "Executing %s", _nextSetting.c_str());
            clearAreas();
            _currentSetting = _nextSetting;
            settings.load(_nextSetting);
            _nextSetting = "";
            execute(prog);
            changeCursor("default");
            drawScreen();
        }

        g_system->updateScreen();
        g_system->delayMillis(10);
    }
    return Common::kNoError;
}

void PrivateEngine::initFuncs() {
    for (Private::FuncTable *fnc = funcTable; fnc->name; fnc++) {
        Common::String *name = new Common::String(fnc->name);
        _functions.setVal(*name, (void *)fnc->func);
    }
}

void PrivateEngine::clearAreas() {
    _exits.clear();
    _masks.clear();

    if (_loadGameMask.surf) 
        _loadGameMask.surf->free();
    delete _loadGameMask.surf;
    _loadGameMask = {};

    if (_saveGameMask.surf)
        _saveGameMask.surf->free();
    delete _saveGameMask.surf;
    _saveGameMask = {};

    if (_policeRadioArea.surf)
        _policeRadioArea.surf->free();
    delete _policeRadioArea.surf; 
    _policeRadioArea = {};

    if (_AMRadioArea.surf)
        _AMRadioArea.surf->free();
    delete _AMRadioArea.surf;
    _AMRadioArea = {};

    if (_phoneArea.surf)
        _phoneArea.surf->free();
    delete _phoneArea.surf;
    _phoneArea = {};

    if (_dossierNextSuspectMask.surf)
        _dossierNextSuspectMask.surf->free();
    delete _dossierNextSuspectMask.surf;
    _dossierNextSuspectMask = {};

    if (_dossierPrevSuspectMask.surf)
        _dossierPrevSuspectMask.surf->free();
    delete _dossierPrevSuspectMask.surf;
    _dossierPrevSuspectMask = {};
}

void PrivateEngine::startPoliceBust() {
    // This logic was extracted from the binary
    int policeIndex = maps.variables.getVal(kPoliceIndex)->u.val;
    int r = _rnd->getRandomNumber(0xc);
    if (policeIndex > 0x14) {
        policeIndex = 0x15;
    }
    _maxNumberClicks = r + 0x10 + (policeIndex * 0xe) / -0x15;
    _sirenWarning = _rnd->getRandomNumber(0x7) + 3;
    _numberClicks = 0;
    if (_sirenWarning >= _maxNumberClicks)
        _sirenWarning = _maxNumberClicks - 1;
}

void PrivateEngine::checkPoliceBust() {
    if (!_policeBustEnabled)
        return;

    if (_numberClicks < _sirenWarning)
        return;

    if (_numberClicks == _sirenWarning) {
        stopSound(true);
        playSound(_sirenSound, 0, false, false);
        _numberClicks++; // Won't execute again
        return;
    }

    if (_numberClicks == _maxNumberClicks+1) {
        uint policeIndex = maps.variables.getVal(kPoliceIndex)->u.val;
        _policeBustSetting = _currentSetting;
        if (policeIndex <= 13) {
            _nextSetting = kPOGoBustMovie;
        } else {
            _nextSetting = kPoliceBustFromMO;
        }
        clearAreas();
        _policeBustEnabled = false;
    }
}

bool PrivateEngine::cursorExit(Common::Point mousePos) {
    mousePos = mousePos - *_origin;
    if (mousePos.x < 0 || mousePos.y < 0)
        return false;

    int rs = 100000000;
    int cs = 0;
    ExitInfo e;
    Common::String cursor = "";

    for (ExitList::iterator it = _exits.begin(); it != _exits.end(); ++it) {
        e = *it;
        cs = e.rect.width()*e.rect.height();

        if (e.rect.contains(mousePos)) {
            if (cs < rs && !e.cursor.empty()) {
                rs = cs;
                cursor = e.cursor;
            }
        }
    }

    if (!cursor.empty()) {
        changeCursor(cursor);
        return true;
    }

    return false;
}

bool PrivateEngine::inMask(Graphics::ManagedSurface *surf, Common::Point mousePos) {
    if (surf == NULL)
        return false;

    mousePos = mousePos - *_origin;
    if (mousePos.x < 0 || mousePos.y < 0)
        return false;

    if (mousePos.x > surf->w || mousePos.y > surf->h)
        return false;

    return (*((uint32 *)surf->getBasePtr(mousePos.x, mousePos.y)) != _transparentColor);
}


bool PrivateEngine::cursorMask(Common::Point mousePos) {
    MaskInfo m;
    bool inside = false;
    for (MaskList::iterator it = _masks.begin(); it != _masks.end(); ++it) {
        m = *it;

        if (inMask(m.surf, mousePos)) {
            if (!m.cursor.empty()) { // TODO: check this
                inside = true;
                changeCursor(m.cursor);
                break;
            }
        }
    }
    return inside;
}

bool PrivateEngine::cursorPauseMovie(Common::Point mousePos) {
    if (_mode == 1) {
        Common::Rect window(_origin->x, _origin->y, _screenW - _origin->x, _screenH - _origin->y);
        if (!window.contains(mousePos)) {
            return true;
        }
    }
    return false;
}

void PrivateEngine::selectPauseMovie(Common::Point mousePos) {
    if (_mode == 1) {
        Common::Rect window(_origin->x, _origin->y, _screenW - _origin->x, _screenH - _origin->y);
        if (!window.contains(mousePos)) {
            if (!_pausedSetting.empty()) {
                _pausedSetting = _currentSetting;
                _nextSetting = kPauseMovie;
            }
        }
    }
}

void PrivateEngine::selectExit(Common::Point mousePos) {
    mousePos = mousePos - *_origin;
    if (mousePos.x < 0 || mousePos.y < 0)
        return;

    Common::String ns = "";
    int rs = 100000000;
    int cs = 0;
    ExitInfo e;
    for (ExitList::iterator it = _exits.begin(); it != _exits.end(); ++it) {
        e = *it;
        cs = e.rect.width()*e.rect.height();
        //debug("Testing exit %s %d", e.nextSetting->c_str(), cs);
        if (e.rect.contains(mousePos)) {
            //debug("Inside! %d %d", cs, rs);
            if (cs < rs && !e.nextSetting.empty()) { // TODO: check this
                // an item was not taken
                if (_toTake) {
                    playSound(getLeaveSound(), 1, false, false);
                    _toTake = false;
                }

                //debug("Found Exit %s %d", e.nextSetting->c_str(), cs);
                rs = cs;
                ns = e.nextSetting;
            }
        }
    }
    if (!ns.empty()) {
        _nextSetting = ns;
    }
}

void PrivateEngine::selectMask(Common::Point mousePos) {
    Common::String ns = "";
    MaskInfo m;
    for (MaskList::iterator it = _masks.begin(); it != _masks.end(); ++it) {
        m = *it;
        //debug("Testing mask %s", m.nextSetting->c_str());
        if (inMask(m.surf, mousePos)) {
            //debug("Inside!");
            if (!m.nextSetting.empty()) { // TODO: check this
                //debug("Found Mask %s", m.nextSetting->c_str());
                ns = m.nextSetting;
            }

            if (m.flag1 != NULL) { // TODO: check this
                setSymbol(m.flag1, 1);
                // an item was taken
                if (_toTake) {
                    playSound(getTakeSound(), 1, false, false);
                    _toTake = false;
                }
            }

            if (m.flag2 != NULL) {
                setSymbol(m.flag2, 1);
            }
            break;
        }
    }
    if (!ns.empty()) {
        //debug("Mask selected %s", ns->c_str());
        _nextSetting = ns;
    }
}

void PrivateEngine::selectAMRadioArea(Common::Point mousePos) {
    if (_AMRadioArea.surf == NULL)
        return;

    if (_AMRadio.empty())
        return;

    if (inMask(_AMRadioArea.surf, mousePos)) {
        Common::String sound = _infaceRadioPath + "comm_/" + _AMRadio.back() + ".wav";
        playSound(sound, 1, false, false);
        _AMRadio.pop_back();
    }
}

void PrivateEngine::selectPoliceRadioArea(Common::Point mousePos) {
    if (_policeRadioArea.surf == NULL)
        return;

    if (_policeRadio.empty())
        return;

    if (inMask(_policeRadioArea.surf, mousePos)) {
        Common::String sound = _infaceRadioPath + "police/" + _policeRadio.back() + ".wav";
        playSound(sound, 1, false, false);
        _policeRadio.pop_back();
    }
}

void PrivateEngine::checkPhoneCall() {
    if (_phoneArea.surf == NULL)
        return;

    if (_phone.empty())
        return;

    if (!_mixer->isSoundHandleActive(_fgSoundHandle))
        playSound(_phonePrefix + _phoneCallSound, 1, false, false);
}

void PrivateEngine::selectPhoneArea(Common::Point mousePos) {
    if (_phoneArea.surf == NULL)
        return;

    if (_phone.empty())
        return;

    if (inMask(_phoneArea.surf, mousePos)) {
        PhoneInfo i = _phone.back();
        setSymbol(i.flag, i.val);
        Common::String sound = _phonePrefix + i.sound + ".wav";
        playSound(sound, 1, true, false);
        _phone.pop_back();
    }
}

void PrivateEngine::loadDossier() {
    int x = 40;
    int y = 30;

    DossierInfo m = _dossiers[_dossierSuspect];

    if (_dossierPage == 0) {
        loadImage(m.page1, x, y);
    } else if (_dossierPage == 1) {
        loadImage(m.page2, x, y);
    } else
        assert(0);
}

bool PrivateEngine::selectDossierNextSuspect(Common::Point mousePos) {
    if (_dossierNextSuspectMask.surf == NULL)
        return false;

    if (inMask(_dossierNextSuspectMask.surf, mousePos)) {
        if ((_dossierSuspect + 1) < _dossiers.size()) {
            _dossierSuspect++;
            _dossierPage = 0;
            loadDossier();
            drawMask(_dossierNextSuspectMask.surf);
            drawMask(_dossierPrevSuspectMask.surf);
            drawScreen();
        }
        return true;
    }
    return false;
}

bool PrivateEngine::selectDossierPrevSuspect(Common::Point mousePos) {
    if (_dossierPrevSuspectMask.surf == NULL)
        return false;

    if (inMask(_dossierPrevSuspectMask.surf, mousePos)) {
        if (_dossierSuspect > 0) {
            _dossierSuspect--;
            _dossierPage = 0;
            loadDossier();
            drawMask(_dossierNextSuspectMask.surf);
            drawMask(_dossierPrevSuspectMask.surf);
            drawScreen();
        }
        return true;
    }
    return false;
}

void PrivateEngine::selectLoadGame(Common::Point mousePos) {
    if (_loadGameMask.surf == NULL)
        return;

    if (inMask(_loadGameMask.surf, mousePos)) {
        loadGameDialog();
    }
}

void PrivateEngine::selectSaveGame(Common::Point mousePos) {
    if (_saveGameMask.surf == NULL)
        return;

    if (inMask(_saveGameMask.surf, mousePos)) {
        saveGameDialog();
    }
}

bool PrivateEngine::hasFeature(EngineFeature f) const {
    return (f == kSupportsReturnToLauncher);
}

void PrivateEngine::restartGame() {
    debugC(1, kPrivateDebugFunction, "restartGame");

    for (NameList::iterator it = maps.variableList.begin(); it != maps.variableList.end(); ++it) {
        Private::Symbol *sym = maps.variables.getVal(*it);
        if (*(sym->name) != "kAlternateGame")
            sym->u.val = 0;
    }

    // Diary
    for (NameList::iterator it = maps.locationList.begin(); it != maps.locationList.end(); ++it) {
        Private::Symbol *sym = maps.locations.getVal(*it);
        sym->u.val = 0;
    }
    inventory.clear();
    _dossiers.clear();

    // Sounds
    _AMRadio.clear();
    _policeRadio.clear();
    _phone.clear();
    _playedPhoneClips.clear();

    // Movies
    _repeatedMovieExit = "";
    _playedMovies.clear();

}

Common::Error PrivateEngine::loadGameStream(Common::SeekableReadStream *stream) {
    // We don't want to continue with any sound from a previous game
    stopSound(true);

    Common::Serializer s(stream, nullptr);
    debugC(1, kPrivateDebugFunction, "loadGameStream");
    _nextSetting = kStartGame;
    int val;

    for (NameList::iterator it = maps.variableList.begin(); it != maps.variableList.end(); ++it) {
        s.syncAsUint32LE(val);
        Private::Symbol *sym = maps.variables.getVal(*it);
        sym->u.val = val;
    }

    // Diary
    for (NameList::iterator it = maps.locationList.begin(); it != maps.locationList.end(); ++it) {
        s.syncAsUint32LE(val);
        Private::Symbol *sym = maps.locations.getVal(*it);
        sym->u.val = val;
    }
    uint32 size = stream->readUint32LE();
    for (uint32 i = 0; i < size; ++i) {
        inventory.push_back(stream->readString());
    }

    // Dossiers
    size = stream->readUint32LE();
    DossierInfo m = {};
    for (uint32 i = 0; i < size; ++i) {
        m.page1 = stream->readString();
        m.page2 = stream->readString();
        _dossiers.push_back(m);
    }

    // Radios
    size = stream->readUint32LE();
    _AMRadio.clear();

    for (uint32 i = 0; i < size; ++i) {
        _AMRadio.push_back(stream->readString());
    }

    size = stream->readUint32LE();
    _policeRadio.clear();

    for (uint32 i = 0; i < size; ++i) {
        _policeRadio.push_back(stream->readString());
    }

    size = stream->readUint32LE();
    _phone.clear();
    PhoneInfo p = {};
    for (uint32 j = 0; j < size; ++j) {
        p.sound = stream->readString();
        p.flag  = maps.variables.getVal(stream->readString());
        p.val   = stream->readUint32LE();
        _phone.push_back(p);
    }

    // Played media
    _repeatedMovieExit = stream->readString();
    _playedMovies.clear();
    size = stream->readUint32LE();
    for (uint32 i = 0; i < size; ++i) {
        _playedMovies.setVal(stream->readString(), true);
    }

    _playedPhoneClips.clear();
    size = stream->readUint32LE();
    for (uint32 i = 0; i < size; ++i) {
        _playedPhoneClips.setVal(stream->readString(), true);
    }

    return Common::kNoError;
}

Common::Error PrivateEngine::saveGameStream(Common::WriteStream *stream, bool isAutosave) {
    debugC(1, kPrivateDebugFunction, "saveGameStream(%d)", isAutosave);
    if (isAutosave)
        return Common::kNoError;

    // Variables
    for (NameList::iterator it = maps.variableList.begin(); it != maps.variableList.end(); ++it) {
        Private::Symbol *sym = maps.variables.getVal(*it);
        stream->writeUint32LE(sym->u.val);
    }

    // Diary
    for (NameList::iterator it = maps.locationList.begin(); it != maps.locationList.end(); ++it) {
        Private::Symbol *sym = maps.locations.getVal(*it);
        stream->writeUint32LE(sym->u.val);
    }

    stream->writeUint32LE(inventory.size());
    for (NameList::iterator it = inventory.begin(); it != inventory.end(); ++it) {
        stream->writeString(*it);
        stream->writeByte(0);
    }

    // Dossiers
    stream->writeUint32LE(_dossiers.size());
    for (DossierArray::iterator it = _dossiers.begin(); it != _dossiers.end(); ++it) {
        stream->writeString(it->page1.c_str());
        stream->writeByte(0);

        if (!it->page2.empty())
            stream->writeString(it->page2.c_str());
        stream->writeByte(0);
    }

    // Radios
    stream->writeUint32LE(_AMRadio.size());
    for (SoundList::iterator it = _AMRadio.begin(); it != _AMRadio.end(); ++it) {
        stream->writeString(*it);
        stream->writeByte(0);
    }
    stream->writeUint32LE(_policeRadio.size());
    for (SoundList::iterator it = _policeRadio.begin(); it != _policeRadio.end(); ++it) {
        stream->writeString(*it);
        stream->writeByte(0);
    }

    stream->writeUint32LE(_phone.size());
    for (PhoneList::iterator it = _phone.begin(); it != _phone.end(); ++it) {
        stream->writeString(it->sound);
        stream->writeByte(0);
        stream->writeString(*it->flag->name);
        stream->writeByte(0);
        stream->writeUint32LE(it->val);
    }

    // Played media
    stream->writeString(_repeatedMovieExit);
    stream->writeByte(0);

    stream->writeUint32LE(_playedMovies.size());
    for (PlayedMediaTable::iterator it = _playedMovies.begin(); it != _playedMovies.end(); ++it) {
        stream->writeString(it->_key);
        stream->writeByte(0);
    }

    stream->writeUint32LE(_playedPhoneClips.size());
    for (PlayedMediaTable::iterator it = _playedPhoneClips.begin(); it != _playedPhoneClips.end(); ++it) {
        stream->writeString(it->_key);
        stream->writeByte(0);
    }

    return Common::kNoError;
}

Common::String PrivateEngine::convertPath(Common::String name) {
    Common::String path(name);
    Common::String s1("\\");
    Common::String s2("/");

    while (path.contains(s1))
        Common::replace(path, s1, s2);

    s1 = Common::String("\"");
    s2 = Common::String("");

    Common::replace(path, s1, s2);
    Common::replace(path, s1, s2);

    path.toLowercase();
    return path;
}

void PrivateEngine::playSound(const Common::String &name, uint loops, bool stopOthers, bool background) {
    debugC(1, kPrivateDebugFunction, "%s(%s,%d,%d,%d)", __FUNCTION__, name.c_str(), loops, stopOthers, background);

    Common::File *file = new Common::File();
    Common::String path = convertPath(name);

    if (!file->open(path))
        error("unable to find sound file %s", path.c_str());

    Audio::LoopingAudioStream *stream;
    stream = new Audio::LoopingAudioStream(Audio::makeWAVStream(file, DisposeAfterUse::YES), loops);
    if (stopOthers) {
        stopSound(true);
    }

    Audio::SoundHandle *sh = NULL;
    if (background) {
        _mixer->stopHandle(_bgSoundHandle);
        sh = &_bgSoundHandle;
    } else {
        _mixer->stopHandle(_fgSoundHandle);
        sh = &_fgSoundHandle;
    }

    _mixer->playStream(Audio::Mixer::kSFXSoundType, sh, stream, -1, Audio::Mixer::kMaxChannelVolume);
}

void PrivateEngine::playVideo(const Common::String &name) {
    debugC(1, kPrivateDebugFunction, "%s(%s)", __FUNCTION__, name.c_str());
    //stopSound(true);
    Common::File *file = new Common::File();
    Common::String path = convertPath(name);

    if (!file->open(path))
        error("unable to find video file %s", path.c_str());

    if (!_videoDecoder->loadStream(file))
        error("unable to load video %s", path.c_str());
    _videoDecoder->start();
}

void PrivateEngine::skipVideo() {
    _videoDecoder->close();
    delete _videoDecoder;
    _videoDecoder = nullptr;
}

void PrivateEngine::stopSound(bool all) {
    debugC(1, kPrivateDebugFunction, "%s(%d)", __FUNCTION__, all);

    if (all) {
        _mixer->stopHandle(_fgSoundHandle);
        _mixer->stopHandle(_bgSoundHandle);
    } else {
        _mixer->stopHandle(_fgSoundHandle);
    }
}

void PrivateEngine::loadImage(const Common::String &name, int x, int y) {
    debugC(1, kPrivateDebugFunction, "%s(%s,%d,%d)", __FUNCTION__, name.c_str(), x, y);
    Common::File file;
    Common::String path = convertPath(name);
    if (!file.open(path))
        error("unable to load image %s", path.c_str());

    _image->loadStream(file);
    Graphics::Surface *surf = _image->getSurface()->convertTo(_pixelFormat, _image->getPalette());
    _compositeSurface->transBlitFrom(*surf, *_origin + Common::Point(x,y), _transparentColor);
    surf->free();
    delete surf;
    _image->destroy();
    //drawScreen();
}

void PrivateEngine::drawScreenFrame() {
    g_system->copyRectToScreen(_frame->getPixels(), _frame->pitch, 0, 0, _screenW, _screenH);
    //surf->copyRectToSurface(*_frame, 0, 0, Common::Rect(0, 0, _screenW, _screenH));
}


Graphics::ManagedSurface *PrivateEngine::loadMask(const Common::String &name, int x, int y, bool drawn) {
    debugC(1, kPrivateDebugFunction, "%s(%s,%d,%d,%d)", __FUNCTION__, name.c_str(), x, y, drawn);
    Common::File file;
    Common::String path = convertPath(name);
    if (!file.open(path))
        error("unable to load mask %s", path.c_str());

    _image->loadStream(file);
    Graphics::ManagedSurface *surf = new Graphics::ManagedSurface();
    surf->create(_screenW, _screenH, _pixelFormat);
    surf->fillRect(screenRect, _transparentColor);
    Graphics::Surface *csurf = _image->getSurface()->convertTo(_pixelFormat, _image->getPalette());
    surf->transBlitFrom(*csurf, Common::Point(x,y));
    csurf->free();
    delete csurf;
    _image->destroy();

    if (drawn) {
        drawMask(surf);
    }

    return surf;
}

void PrivateEngine::drawMask(Graphics::ManagedSurface *surf) {
    _compositeSurface->transBlitFrom(surf->rawSurface(), *_origin, _transparentColor);
    //drawScreen();
}

void PrivateEngine::drawScreen() {
    Graphics::ManagedSurface *surface = _compositeSurface;

    if (_videoDecoder) {
        const Graphics::Surface *frame = _videoDecoder->decodeNextFrame();
        //frame->create(_videoDecoder->getWidth(), _videoDecoder->getHeight(), _pixelFormat);
        //frame->copyFrom(*_videoDecoder->decodeNextFrame());
        Graphics::Surface *cframe = frame->convertTo(_pixelFormat, _videoDecoder->getPalette());
        Common::Point center((_screenW - _videoDecoder->getWidth())/2, (_screenH - _videoDecoder->getHeight())/2);
        surface->transBlitFrom(*cframe, center);
        //frame->free();
        cframe->free();
        //delete frame;
        delete cframe;
    }

    if (_mode == 1) {
        drawScreenFrame();
    }

    Common::Rect w(_origin->x, _origin->y, _screenW - _origin->x, _screenH - _origin->y);
    Graphics::Surface sa = surface->getSubArea(w);
    g_system->copyRectToScreen(sa.getPixels(), sa.pitch, _origin->x, _origin->y, sa.w, sa.h);
    //if (_image->getPalette() != nullptr)
    //    g_system->getPaletteManager()->setPalette(_image->getPalette(), _image->getPaletteStartIndex(), _image->getPaletteColorCount());
    g_system->updateScreen();

}

bool PrivateEngine::getRandomBool(uint p) {
    uint r = _rnd->getRandomNumber(100);
    return (r <= p);
}

Common::String PrivateEngine::getPaperShuffleSound() {
    uint r = _rnd->getRandomNumber(6);
    return Common::String::format("%sglsfx0%d.wav", _globalAudioPath.c_str(), kPaperShuffleSound[r]);
}

Common::String PrivateEngine::getTakeSound() {
    if (isDemo())
        return (_globalAudioPath + "mvo007.wav");

    uint r = _rnd->getRandomNumber(4) + 1;
    return Common::String::format("%stook%d.wav", _globalAudioPath.c_str(), r);
}

Common::String PrivateEngine::getTakeLeaveSound() {
    uint r = _rnd->getRandomNumber(1);
    if (r == 0) {
        return (_globalAudioPath + "mvo001.wav");
    } else {
        return (_globalAudioPath + "mvo006.wav");
    }
}

Common::String PrivateEngine::getLeaveSound() {
    if (isDemo())
        return (_globalAudioPath + "mvo008.wav");

    uint r = _rnd->getRandomNumber(4) + 1;
    return Common::String::format("%sleft%d.wav", _globalAudioPath.c_str(), r);
}

Common::String PrivateEngine::getRandomPhoneClip(const char *clip, int i, int j) {
    uint r = i + _rnd->getRandomNumber(j - i);
    return Common::String::format("%s%02d", clip, r);
}

// Timers
void timerCallback(void *refCon) {
    g_private->removeTimer();
    g_private->_nextSetting = *(Common::String *)refCon;
}

bool PrivateEngine::installTimer(uint32 delay, Common::String *ns) {
    return g_system->getTimerManager()->installTimerProc(&timerCallback, delay, (void *)ns, "timerCallback");
}

void PrivateEngine::removeTimer() {
    g_system->getTimerManager()->removeTimerProc(&timerCallback);
}

// Diary

void PrivateEngine::loadLocations(Common::Rect *rect) {
    uint32 i = 0;
    int16 offset = 44;
    for (NameList::iterator it = maps.locationList.begin(); it != maps.locationList.end(); ++it) {
        Private::Symbol *sym = maps.locations.getVal(*it);
        i++;
        if (sym->u.val) {
            offset = offset + 22;
            Common::String s =
              Common::String::format("%sdryloc%d.bmp", _diaryLocPrefix.c_str(), i);

            loadMask(s, rect->left + 120, rect->top + offset, true);
        }
    }
}

void PrivateEngine::loadInventory(uint32 x, Common::Rect *r1, Common::Rect *r2) {
    int16 offset = 0;
    for (NameList::iterator it = inventory.begin(); it != inventory.end(); ++it) {
        offset = offset + 22;
        //debug("%hd %hd", rect->left, rect->top + offset);
        loadMask(*it, r1->left, r1->top + offset, true);
    }
}

} // End of namespace Private
