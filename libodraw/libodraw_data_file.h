/*
 * Data file functions
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

#if !defined( _LIBODRAW_INTERNAL_DATA_FILE_H )
#define _LIBODRAW_INTERNAL_DATA_FILE_H

#include <common.h>
#include <types.h>

#include "libodraw_extern.h"
#include "libodraw_data_file_descriptor.h"
#include "libodraw_handle.h"
#include "libodraw_libcerror.h"
#include "libodraw_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libodraw_internal_data_file libodraw_internal_data_file_t;

struct libodraw_internal_data_file
{
	/* The internal handle
	 */
	libodraw_internal_handle_t *internal_handle;

	/* The data file descriptor
	 */
	libodraw_data_file_descriptor_t *data_file_descriptor;
};

int libodraw_data_file_initialize(
     libodraw_data_file_t **data_file,
     libodraw_internal_handle_t *internal_handle,
     libodraw_data_file_descriptor_t *data_file_descriptor,
     libcerror_error_t **error );

LIBODRAW_EXTERN \
int libodraw_data_file_free(
     libodraw_data_file_t **data_file,
     libcerror_error_t **error );

LIBODRAW_EXTERN \
int libodraw_data_file_get_filename_size(
     libodraw_data_file_t *data_file,
     size_t *filename_size,
     libcerror_error_t **error );

LIBODRAW_EXTERN \
int libodraw_data_file_get_filename(
     libodraw_data_file_t *data_file,
     char *filename,
     size_t filename_size,
     libcerror_error_t **error );

LIBODRAW_EXTERN \
int libodraw_data_file_set_filename(
     libodraw_data_file_t *data_file,
     const char *filename,
     size_t filename_length,
     libcerror_error_t **error );

#if defined( HAVE_WIDE_CHARACTER_TYPE )
LIBODRAW_EXTERN \
int libodraw_data_file_get_filename_size_wide(
     libodraw_data_file_t *data_file,
     size_t *filename_size,
     libcerror_error_t **error );

LIBODRAW_EXTERN \
int libodraw_data_file_get_filename_wide(
     libodraw_data_file_t *data_file,
     wchar_t *filename,
     size_t filename_size,
     libcerror_error_t **error );

LIBODRAW_EXTERN \
int libodraw_data_file_set_filename_wide(
     libodraw_data_file_t *data_file,
     const wchar_t *filename,
     size_t filename_length,
     libcerror_error_t **error );
#endif

LIBODRAW_EXTERN \
int libodraw_data_file_get_type(
     libodraw_data_file_t *data_file,
     uint8_t *type,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBODRAW_INTERNAL_DATA_FILE_H ) */

