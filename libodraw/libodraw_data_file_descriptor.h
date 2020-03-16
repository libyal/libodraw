/*
 * Data file descriptor functions
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

#if !defined( _LIBODRAW_DATA_FILE_DESCRIPTOR_H )
#define _LIBODRAW_DATA_FILE_DESCRIPTOR_H

#include <common.h>
#include <types.h>

#include "libodraw_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libodraw_data_file_descriptor libodraw_data_file_descriptor_t;

struct libodraw_data_file_descriptor
{
	/* The name
	 */
	system_character_t *name;

	/* The name size
	 */
	size_t name_size;

	/* Value to indicate the name was set by the data_file_set_filename functions
	 */
	uint8_t name_set;

	/* The type
	 */
	uint8_t type;
};

int libodraw_data_file_descriptor_initialize(
     libodraw_data_file_descriptor_t **data_file_descriptor,
     libcerror_error_t **error );

int libodraw_data_file_descriptor_free(
     libodraw_data_file_descriptor_t **data_file_descriptor,
     libcerror_error_t **error );

int libodraw_data_file_descriptor_get_name_size(
     libodraw_data_file_descriptor_t *data_file_descriptor,
     size_t *name_size,
     libcerror_error_t **error );

int libodraw_data_file_descriptor_get_name(
     libodraw_data_file_descriptor_t *data_file_descriptor,
     char *name,
     size_t name_size,
     libcerror_error_t **error );

int libodraw_data_file_descriptor_set_name(
     libodraw_data_file_descriptor_t *data_file_descriptor,
     const char *name,
     size_t name_length,
     libcerror_error_t **error );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

int libodraw_data_file_descriptor_get_name_size_wide(
     libodraw_data_file_descriptor_t *data_file_descriptor,
     size_t *name_size,
     libcerror_error_t **error );

int libodraw_data_file_descriptor_get_name_wide(
     libodraw_data_file_descriptor_t *data_file_descriptor,
     wchar_t *name,
     size_t name_size,
     libcerror_error_t **error );

int libodraw_data_file_descriptor_set_name_wide(
     libodraw_data_file_descriptor_t *data_file_descriptor,
     const wchar_t *name,
     size_t name_length,
     libcerror_error_t **error );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBODRAW_DATA_FILE_DESCRIPTOR_H ) */

