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

#ifndef BACKENDS_CLOUD_GOOGLEDRIVE_GOOGLEDRIVEUPLOADREQUEST_H
#define BACKENDS_CLOUD_GOOGLEDRIVE_GOOGLEDRIVEUPLOADREQUEST_H

#include "backends/cloud/storage.h"
#include "backends/networking/curl/curljsonrequest.h"
#include "backends/networking/curl/request.h"
#include "common/callback.h"

namespace Cloud {
namespace GoogleDrive {
class GoogleDriveStorage;

class GoogleDriveUploadRequest: public Networking::Request {
	GoogleDriveStorage *_storage;
	Common::String _savePath;
	Common::SeekableReadStream *_contentsStream;
	Storage::UploadCallback _uploadCallback;
	Request *_workingRequest;
	bool _ignoreCallback;
	Common::String _resolvedId, _parentId;
	Common::String _uploadUrl;
	uint64 _serverReceivedBytes;

	void start();
	void resolveId();
	void idResolvedCallback(const Storage::UploadResponse &response);
	void idResolveFailedCallback(const Networking::ErrorResponse &error);
	void startUpload();
	void startUploadCallback(const Networking::JsonResponse &response);
	void startUploadErrorCallback(const Networking::ErrorResponse &error);
	void uploadNextPart();
	void partUploadedCallback(const Networking::JsonResponse &response);
	void partUploadedErrorCallback(const Networking::ErrorResponse &error);
	bool handleHttp308(const Networking::NetworkReadStream *stream);
	void finishUpload(StorageFile status);

public:
	GoogleDriveUploadRequest(GoogleDriveStorage *storage, const Common::String &path, Common::SeekableReadStream *contents, Storage::UploadCallback callback, Networking::ErrorCallback ecb);
	~GoogleDriveUploadRequest() override;

	void handle() override;
	void restart() override;
};

} // End of namespace GoogleDrive
} // End of namespace Cloud

#endif
