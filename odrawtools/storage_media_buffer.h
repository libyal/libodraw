/*
 * Storage media buffer
 *
 * Copyright (C) 2010-2018, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _STORAGE_MEDIA_BUFFER_H )
#define _STORAGE_MEDIA_BUFFER_H

#include <common.h>
#include <types.h>

#include "odrawtools_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct storage_media_buffer storage_media_buffer_t;

struct storage_media_buffer
{
	/* The raw buffer
	 */
	uint8_t *raw_buffer;

	/* The raw buffer size
	 */
	size_t raw_buffer_size;

	/* The size of the data in the raw buffer
	 */
	size_t raw_buffer_data_size;
};

int storage_media_buffer_initialize(
     storage_media_buffer_t **buffer,
     size_t size,
     libcerror_error_t **error );

int storage_media_buffer_free(
     storage_media_buffer_t **buffer,
     libcerror_error_t **error );

int storage_media_buffer_resize(
     storage_media_buffer_t *buffer,
     size_t size,
     libcerror_error_t **error );

int storage_media_buffer_get_data(
     storage_media_buffer_t *buffer,
     uint8_t **data,
     size_t *data_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _STORAGE_MEDIA_BUFFER_H ) */

