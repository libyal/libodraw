/*
 * The internal definitions
 *
 * Copyright (c) 2010-2013-2011, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#if !defined( _LIBODRAW_INTERNAL_DEFINITIONS_H )
#define _LIBODRAW_INTERNAL_DEFINITIONS_H

#include <common.h>
#include <byte_stream.h>

#define LIBODRAW_ENDIAN_BIG				_BYTE_STREAM_ENDIAN_BIG
#define LIBODRAW_ENDIAN_LITTLE				_BYTE_STREAM_ENDIAN_LITTLE

/* Define HAVE_LOCAL_LIBODRAW for local use of libodraw
 */
#if !defined( HAVE_LOCAL_LIBODRAW )
#include <libodraw/definitions.h>

/* The definitions in <libodraw/definitions.h> are copied here
 * for local use of libodraw
 */
#else
#define LIBODRAW_VERSION				@VERSION@

/* The version string
 */
#define LIBODRAW_VERSION_STRING				"@VERSION@"

/* The access flags definitions
 * bit 1        set to 1 for read access
 * bit 2        set to 1 for write access
 * bit 3-8      not used
 */
enum LIBODRAW_ACCESS_FLAGS
{
	LIBODRAW_ACCESS_FLAG_READ			= 0x01,
/* Reserved: not supported yet */
	LIBODRAW_ACCESS_FLAG_WRITE			= 0x02
};

/* The file access macros
 */
#define LIBODRAW_OPEN_READ				( LIBODRAW_ACCESS_FLAG_READ )
/* Reserved: not supported yet */
#define LIBODRAW_OPEN_WRITE				( LIBODRAW_ACCESS_FLAG_WRITE )
/* Reserved: not supported yet */
#define LIBODRAW_OPEN_READ_WRITE			( LIBODRAW_ACCESS_FLAG_READ | LIBODRAW_ACCESS_FLAG_WRITE )

/* The file types
 */
enum LIBODRAW_FILE_TYPES
{
	LIBODRAW_FILE_TYPE_UNKNOWN,
	LIBODRAW_FILE_TYPE_BINARY_LITTLE_ENDIAN,
	LIBODRAW_FILE_TYPE_BINARY_BIG_ENDIAN,
	LIBODRAW_FILE_TYPE_AUDIO_AIFF,
	LIBODRAW_FILE_TYPE_AUDIO_WAVE,
	LIBODRAW_FILE_TYPE_AUDIO_MPEG1_LAYER3,
};

#define LIBODRAW_FILE_TYPE_BINARY			LIBODRAW_FILE_TYPE_BINARY_LITTLE_ENDIAN
#define LIBODRAW_FILE_TYPE_MOTOROLA			LIBODRAW_FILE_TYPE_BINARY_BIG_ENDIAN
#define LIBODRAW_FILE_TYPE_AIFF				LIBODRAW_FILE_TYPE_AUDIO_AIFF
#define LIBODRAW_FILE_TYPE_WAVE				LIBODRAW_FILE_TYPE_AUDIO_WAVE
#define LIBODRAW_FILE_TYPE_MP3				LIBODRAW_FILE_TYPE_AUDIO_MPEG1_LAYER3

/* The track types
 */
enum LIBODRAW_TRACK_TYPES
{
	LIBODRAW_TRACK_TYPE_UNKNOWN,
	LIBODRAW_TRACK_TYPE_AUDIO,
	LIBODRAW_TRACK_TYPE_CDG,
	LIBODRAW_TRACK_TYPE_MODE1_2048,
	LIBODRAW_TRACK_TYPE_MODE1_2352,
	LIBODRAW_TRACK_TYPE_MODE2_2048,
	LIBODRAW_TRACK_TYPE_MODE2_2324,
	LIBODRAW_TRACK_TYPE_MODE2_2336,
	LIBODRAW_TRACK_TYPE_MODE2_2352,
	LIBODRAW_TRACK_TYPE_CDI_2336,
	LIBODRAW_TRACK_TYPE_CDI_2352,
};

#endif

#endif

