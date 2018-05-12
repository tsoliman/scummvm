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

#include <common/stream.h>
#include <graphics/surface.h>
#include "cel_decoder.h"

namespace Pink {

bool CelDecoder::loadStream(Common::SeekableReadStream *stream) {
    close();

    /* uint32 frameSize = */ stream->readUint32LE();
    uint16 frameType = stream->readUint16LE();

    // Check FLC magic number
    if (frameType != 0xAF12) {
        warning("FlicDecoder::loadStream(): attempted to load non-FLC data (type = 0x%04X)", frameType);
        return false;
    }

    uint16 frameCount = stream->readUint16LE();
    uint16 width = stream->readUint16LE();
    uint16 height = stream->readUint16LE();
    uint16 colorDepth = stream->readUint16LE();
    if (colorDepth != 8) {
        warning("FlicDecoder::loadStream(): attempted to load an FLC with a palette of color depth %d. Only 8-bit color palettes are supported", colorDepth);
        return false;
    }

    addTrack(new CelVideoTrack(stream, frameCount, width, height));
    return true;
}

int32 CelDecoder::getX(){
    CelVideoTrack *track = (CelVideoTrack*) getTrack(0);
    if (!track)
        return -1;
    return track->getX();
}

int32 CelDecoder::getY() {
    CelVideoTrack *track = (CelVideoTrack*) getTrack(0);
    if (!track)
        return -1;
    return track->getY();
}


uint16 CelDecoder::getTransparentColourIndex() {
    CelVideoTrack *track = (CelVideoTrack*) getTrack(0);
    if (!track)
        return 0;
    return track->getTransparentColourIndex();
}

const Graphics::Surface *CelDecoder::getCurrentFrame() {
    CelVideoTrack *track = (CelVideoTrack*) getTrack(0);
    if (!track)
        return 0;
    return track->getCurrentFrame();
}

Common::Point CelDecoder::getCenter() {
    CelVideoTrack *track = (CelVideoTrack*) getTrack(0);
    if (!track)
        return {0,0};
    return track->getCenter();
}

Common::Rect &CelDecoder::getRectangle() {
    CelVideoTrack *track = (CelVideoTrack*) getTrack(0);
    return track->getRect();
}

void CelDecoder::setX(int32 x) {
    CelVideoTrack *track = (CelVideoTrack*) getTrack(0);
    track->setX(x);
}

void CelDecoder::setY(int32 y) {
    CelVideoTrack *track = (CelVideoTrack*) getTrack(0);
    track->setY(y);
}

CelDecoder::CelVideoTrack::CelVideoTrack(Common::SeekableReadStream *stream, uint16 frameCount, uint16 width, uint16 height, bool skipHeader)
        : FlicVideoTrack(stream, frameCount, width, height, 1), _center(0,0), _transparentColourIndex(0){
    readHeader();
}

#define PREFIX_TYPE 0xF100
#define CEL_DATA 3

void CelDecoder::CelVideoTrack::readPrefixChunk() {
    _fileStream->seek(0x80);
    uint32 chunkSize = _fileStream->readUint32LE();
    uint16 chunkType = _fileStream->readUint16LE();
    if (chunkType != PREFIX_TYPE)
        return;
    uint32 offset = 6;

    uint32 subchunkSize = _fileStream->readUint32LE();
    uint16 subchunkType = _fileStream->readUint16LE();

    switch (subchunkType) {
        case CEL_DATA:
            _fileStream->readUint16LE();
            _center.x = _fileStream->readUint16LE();
            _center.y = _fileStream->readUint16LE();
            break;
        default:
            error("Unknown subchunk type");
            _fileStream->skip(subchunkSize - 6);
            break;
    }
    _rect = Common::Rect::center(_center.x, _center.y, _surface->w, _surface->h);
}

void CelDecoder::CelVideoTrack::readHeader() {
    _fileStream->readUint16LE();

    _frameDelay = _startFrameDelay = _fileStream->readUint32LE();

    _fileStream->seek(80);
    _offsetFrame1 = _fileStream->readUint32LE();
    _offsetFrame2 = _fileStream->readUint32LE();

    if (_offsetFrame1 > 0x80) {
        readPrefixChunk();
    }

    _fileStream->seek(_offsetFrame1);
}

int32 CelDecoder::CelVideoTrack::getX() const {
    return (_center.x - getWidth() / 2) < 0 ? 0 : _center.x - getWidth() / 2;
}

int32 CelDecoder::CelVideoTrack::getY() const {
    return (_center.y - getHeight() / 2) < 0 ? 0 : _center.y - getHeight() / 2;
}

uint16 CelDecoder::CelVideoTrack::getTransparentColourIndex() {
    return _transparentColourIndex;
}

const Graphics::Surface *CelDecoder::CelVideoTrack::getCurrentFrame() {
    return _surface;
}

Common::Point CelDecoder::CelVideoTrack::getCenter() {
    return _center;
}

Common::Rect &CelDecoder::CelVideoTrack::getRect() {
    return _rect;
}

#define FRAME_TYPE 0xF1FA

const Graphics::Surface *CelDecoder::CelVideoTrack::decodeNextFrame() {
    // Read chunk
    /*uint32 frameSize = */ _fileStream->readUint32LE();
    uint16 frameType = _fileStream->readUint16LE();

    switch (frameType) {
        case FRAME_TYPE:
            handleFrame();
            break;
        default:
            error("FlicDecoder::decodeFrame(): unknown main chunk type (type = 0x%02X)", frameType);
            break;
    }

    _curFrame++;
    _nextFrameStartTime += _frameDelay;

    if (_atRingFrame) {
        // If we decoded the ring frame, seek to the second frame
        _atRingFrame = false;
        _fileStream->seek(_offsetFrame2);
    }

    if (_curFrame == 0)
        _transparentColourIndex = *(byte*)_surface->getBasePtr(0,0);

    return _surface;
}

void CelDecoder::CelVideoTrack::setX(int32 x) {
    _center.x = x ;//+ getWidth() / 2;
}

void CelDecoder::CelVideoTrack::setY(int32 y) {
    _center.y = y;//+ getHeight() / 2;
}

} // End of namepsace Pink