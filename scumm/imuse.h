/* ScummVM - Scumm Interpreter
 * Copyright (C) 2001  Ludvig Strigeus
 * Copyright (C) 2001/2002 The ScummVM project
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

#ifndef IMUSE_H
#define IMUSE_H

class IMuseInternal;
class MidiDriver;
class OSystem;
class Scumm;
struct Serializer;
class SoundMixer;

class IMuse {
public:
	enum {
		PROP_TEMPO_BASE = 1,
	};

	IMuse() { }
	virtual ~IMuse() { };

	virtual void on_timer() = 0; // For the MacOS 9 port only
	virtual void pause(bool paused) = 0;
	virtual int save_or_load(Serializer *ser, Scumm *scumm) = 0;
	virtual int set_music_volume(uint vol) = 0;
	virtual int get_music_volume() = 0;
	virtual int set_master_volume(uint vol) = 0;
	virtual int get_master_volume() = 0;
	virtual bool start_sound(int sound) = 0;
	virtual int stop_sound(int sound) = 0;
	virtual int stop_all_sounds() = 0;
	virtual int get_sound_status(int sound) = 0;
	virtual int32 do_command(int a, int b, int c, int d, int e, int f, int g, int h) = 0;
	virtual int clear_queue() = 0;
	virtual void setBase(byte **base) = 0;
	virtual uint32 property(int prop, uint32 value) = 0;

	// Factory methods
	static IMuse *create(OSystem *syst, MidiDriver *midi, SoundMixer *mixer);

	static IMuse *create_adlib(OSystem *syst, SoundMixer *mixer) {
		return create(syst, NULL, mixer);
	}
	static IMuse *create_midi(OSystem *syst, MidiDriver *midi) {
		return create(syst, midi, NULL);
	}
};

#define MAX_DIGITAL_CHANNELS 8
#define MAX_IMUSE_JUMPS 1
#define MAX_IMUSE_REGIONS 3

class IMuseDigital {
private:

	struct region {
		uint32 _offset;		// begin of region
		uint32 _length;		// lenght of region
	};

	struct jump {
		uint32 _offset;		// jump position
		uint32 _dest;			// jump to 
		uint32 _id;				// id of jump
		uint32 _numLoops;	// allmost 500 except one value: 2
	};

	struct channel {
		int8 _volumeRight;
		int8 _volume;
		int8 _volumeFade;
		int8 _volumeFadeParam;
		int8 _volumeFadeStep;
		uint32 _delay;
		bool _isJump;
		uint32 _numLoops;
		uint32 _offsetStop;
		jump _jump[MAX_IMUSE_JUMPS];
		uint32 _numJumps;
		region _region[MAX_IMUSE_REGIONS];
		uint32 _numRegions;
		uint32 _offset;
		byte *_data;
		uint32 _freq;
		uint32 _channels;
		uint32 _bits;
		uint32 _size;
		int32 _idSound;
		uint32 _mixerSize;
		uint8 _mixerFlags;
		bool _used;
		bool _toBeRemoved;
		bool _initialized;
	} _channel[MAX_DIGITAL_CHANNELS];

	Scumm *_scumm;
	bool _pause;

public:
	IMuseDigital(Scumm *scumm);
	~IMuseDigital();
	void handler();
	void startSound(int sound);
	void stopSound(int sound);
	void stopAll();
	void pause(bool pause);
	int32 doCommand(int a, int b, int c, int d, int e, int f, int g, int h);
	int getSoundStatus(int sound);
};

#endif