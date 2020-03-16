/*
 * Input/Output (IO) handle functions
 *
 * Copyright (C) 2010-2020, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#if !defined( _LIBODRAW_IO_HANDLE_H )
#define _LIBODRAW_IO_HANDLE_H

#include <common.h>
#include <types.h>

#include "libodraw_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libodraw_io_handle libodraw_io_handle_t;

struct libodraw_io_handle
{
	/* The number of bytes per sector
	 */
	uint32_t bytes_per_sector;

	/* The mode
	 */
	uint8_t mode;

	/* The codepage of the extended ASCII strings
	 */
	int ascii_codepage;

	/* Value to indicate if abort was signalled
	 */
	int abort;
};

int libodraw_io_handle_initialize(
     libodraw_io_handle_t **io_handle,
     libcerror_error_t **error );

int libodraw_io_handle_free(
     libodraw_io_handle_t **io_handle,
     libcerror_error_t **error );

int libodraw_io_handle_clear(
     libodraw_io_handle_t *io_handle,
     libcerror_error_t **error );

ssize_t libodraw_io_handle_copy_sector_data_to_buffer(
         libodraw_io_handle_t *io_handle,
         const uint8_t *sector_data,
         size_t sector_data_size,
         uint32_t bytes_per_sector,
         uint8_t track_type,
         uint8_t *buffer,
         size_t buffer_size,
         uint32_t sector_index,
         uint32_t sector_offset,
         libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBODRAW_IO_HANDLE_H ) */

