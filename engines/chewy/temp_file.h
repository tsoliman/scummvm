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

#ifndef CHEWY_TEMP_FILE_H
#define CHEWY_TEMP_FILE_H

#include "common/archive.h"
#include "common/list.h"
#include "common/memstream.h"
#include "common/path.h"
#include "common/str.h"

namespace Chewy {

class TempFileArchive : public Common::Archive {
	struct Entry {
		Common::String _name;
		byte *_data;
		size_t _size;
		Entry() : _data(nullptr), _size(0) {}
		Entry(const Common::String &name);
		~Entry();

		void allocate(size_t maxSize);
	};
	typedef Common::List<Entry> EntryList;

	class FileProxy : public Common::SeekableReadStream,
		public Common::SeekableWriteStream {
	private:
		byte *_ptr;
		int32 _pos, _size;
	public:
		FileProxy(byte *ptr, size_t ptrSize) :
			_ptr(ptr), _size(ptrSize), _pos(0) {}

		bool eos() const override;
		uint32 read(void *dataPtr, uint32 dataSize) override;
		int64 pos() const override;
		int64 size() const override;
		bool seek(int64 offset, int whence = SEEK_SET) override;

		uint32 write(const void *dataPtr, uint32 dataSize) override;
		bool flush() override;
		void finalize() override;
	};
private:
	EntryList _files;

	/**
	 * Finds an entry
	 */
	const Entry *getEntry(const Common::String &name) const;
public:
	/**
	 * Constructor
	 */
	TempFileArchive();

	/**
	 * Registers a temporary file by name.
	 */
	void add(const Common::String &name, size_t maxSize) {
		_files.push_back(Entry(name));
		_files.back().allocate(maxSize);
	}

	/**
	 * Check if a member with the given name is present in the Archive.
	 * Patterns are not allowed, as this is meant to be a quick File::exists()
	 * replacement.
	 */
	bool hasFile(const Common::Path &path) const override;

	/**
	 * Add all members of the Archive to list.
	 * Must only append to list, and not remove elements from it.
	 *
	 * @return the number of names added to list
	 */
	int listMembers(Common::ArchiveMemberList &list) const override;

	/**
	 * Returns a ArchiveMember representation of the given file.
	 */
	const Common::ArchiveMemberPtr getMember(const Common::Path &path) const override;

	/**
	 * Create a stream bound to a member with the specified name in the
	 * archive. If no member with this name exists, 0 is returned.
	 * @return the newly created input stream
	 */
	Common::SeekableReadStream *createReadStreamForMember(const Common::Path &path) const override;

	/**
	 * Creates a write stream
	 */
	Common::SeekableWriteStream *createWriteStreamForMember(const Common::Path &path);
};

} // End of namespace Chewy

#endif
