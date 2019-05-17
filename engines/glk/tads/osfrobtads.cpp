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

#include "glk/tads/osfrobtads.h"
#include "common/file.h"

namespace Glk {
namespace TADS {

osfildef *osfoprb(const char *fname, os_filetype_t typ) {
	Common::File f;
	if (f.open(fname))
		return f.readStream(f.size());
	else
		return nullptr;
}

osfildef *osfoprwtb(const char *fname, os_filetype_t typ) {
	Common::DumpFile *df = new Common::DumpFile();
	if (df->open(fname))
		return df;
	delete df;
	return nullptr;
}

int osfrb(osfildef *fp, void *buf, size_t count) {
	return dynamic_cast<Common::ReadStream *>(fp)->read(buf, count);
}

bool osfwb(osfildef *fp, void *buf, size_t count) {
	return dynamic_cast<Common::WriteStream *>(fp)->write(buf, count) != count;
}

void osfflush(osfildef *fp) {
	dynamic_cast<Common::WriteStream *>(fp)->flush();
}

osfildef *osfopwt(const char *fname, os_filetype_t typ) {
	return osfoprwtb(fname, typ);
}

} // End of namespace TADS
} // End of namespace Glk
