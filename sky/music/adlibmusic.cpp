/* ScummVM - Scumm Interpreter
 * Copyright (C) 2003 The ScummVM project
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
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * $Header$
 *
 */

#include "sky/music/adlibmusic.h"
#include "sound/fmopl.h"

void SkyAdlibMusic::passMixerFunc(void *param, int16 *buf, uint len) {

	((SkyAdlibMusic*)param)->premixerCall(buf, len);
}

SkyAdlibMusic::SkyAdlibMusic(SoundMixer *pMixer, SkyDisk *pSkyDisk, OSystem *system)
	: SkyMusicBase(pSkyDisk, system) {

	_driverFileBase = 60202;
    _mixer = pMixer;
	_sampleRate = g_system->property(OSystem::PROP_GET_SAMPLE_RATE, 0);
	if (0 != YM3812Init(1, 3579545, _sampleRate))
		error("Error initialising YM3812 sound chip emulation");
	_mixer->setupPremix(this, passMixerFunc);
}

SkyAdlibMusic::~SkyAdlibMusic(void) {

	_mixer->setupPremix(NULL, NULL);
	YM3812Shutdown();
}

void SkyAdlibMusic::setVolume(uint8 volume) {

	_musicVolume = volume;
	_mixer->setMusicVolume(_musicVolume << 1);
}

void SkyAdlibMusic::premixerCall(int16 *buf, uint len) {

	if (_musicData == NULL) {
		// no music loaded
		memset(buf, 0, len * sizeof(int16));
		return;
	} else if ((_currentMusic == 0) || (_numberOfChannels == 0)) {
		// music loaded but not played as of yet
		memset(buf, 0, len * sizeof(int16));
		// poll anyways as pollMusic() can activate the music
		pollMusic();
		_nextMusicPoll = _sampleRate/50;
		return;
	}
	uint32 render;
	while (len) {
		render = (len > _nextMusicPoll) ? (_nextMusicPoll) : (len);
		len -= render;
		_nextMusicPoll -= render;
		YM3812UpdateOne(0, buf, render);
		buf += render;
		if (_nextMusicPoll == 0) {
			pollMusic();
			_nextMusicPoll = _sampleRate/50;
		}
	}
}

void SkyAdlibMusic::setupPointers(void) {

	if (SkyState::_systemVars.gameVersion == 267) {
		// disk demo uses a different adlib driver version, some offsets have changed
		_musicDataLoc = (_musicData[0x11F8] << 8) | _musicData[0x11F7];
		_initSequence = _musicData + 0xE87;
	} else {
		_musicDataLoc = (_musicData[0x1202] << 8) | _musicData[0x1201];
		_initSequence = _musicData + 0xE91;
	}
	_nextMusicPoll = 0;
}

void SkyAdlibMusic::setupChannels(uint8 *channelData) {

	_numberOfChannels = channelData[0];
	channelData++;
	for (uint8 cnt = 0; cnt < _numberOfChannels; cnt++) {
		uint16 chDataStart = ((channelData[(cnt << 1) | 1] << 8) | channelData[cnt << 1]) + _musicDataLoc;
		_channels[cnt] = new SkyAdlibChannel(_musicData, chDataStart);
	}
}

void SkyAdlibMusic::startDriver(void) {

	uint16 cnt = 0;
	while (_initSequence[cnt] || _initSequence[cnt+1]) {
		YM3812Write(0, 0, _initSequence[cnt]);
		YM3812Write(0, 1, _initSequence[cnt+1]);
		cnt += 2;
	}
	_allowedCommands = 0xD;
}
