/*
 * Metadata functions
 *
 * Copyright (c) 2010-2014, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBODRAW_METADATA_H )
#define _LIBODRAW_METADATA_H

#include <common.h>
#include <types.h>

#include "libodraw_extern.h"
#include "libodraw_libcerror.h"
#include "libodraw_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

LIBODRAW_EXTERN \
int libodraw_handle_get_media_size(
     libodraw_handle_t *handle,
     size64_t *media_size,
     libcerror_error_t **error );

LIBODRAW_EXTERN \
int libodraw_handle_get_bytes_per_sector(
     libodraw_handle_t *handle,
     uint32_t *bytes_per_sector,
     libcerror_error_t **error );

LIBODRAW_EXTERN \
int libodraw_handle_set_bytes_per_sector(
     libodraw_handle_t *handle,
     uint32_t bytes_per_sector,
     libcerror_error_t **error );

LIBODRAW_EXTERN \
int libodraw_handle_get_number_of_sectors(
     libodraw_handle_t *handle,
     uint64_t *number_of_sectors,
     libcerror_error_t **error );

LIBODRAW_EXTERN \
int libodraw_handle_get_number_of_sessions(
     libodraw_handle_t *handle,
     int *number_of_sessions,
     libcerror_error_t **error );

LIBODRAW_EXTERN \
int libodraw_handle_get_session(
     libodraw_handle_t *handle,
     int index,
     uint64_t *start_sector,
     uint64_t *number_of_sectors,
     libcerror_error_t **error );

LIBODRAW_EXTERN \
int libodraw_handle_append_session(
     libodraw_handle_t *handle,
     uint64_t start_sector,
     uint64_t number_of_sectors,
     libcerror_error_t **error );

LIBODRAW_EXTERN \
int libodraw_handle_get_number_of_lead_outs(
     libodraw_handle_t *handle,
     int *number_of_lead_outs,
     libcerror_error_t **error );

LIBODRAW_EXTERN \
int libodraw_handle_get_lead_out(
     libodraw_handle_t *handle,
     int index,
     uint64_t *start_sector,
     uint64_t *number_of_sectors,
     libcerror_error_t **error );

LIBODRAW_EXTERN \
int libodraw_handle_append_lead_out(
     libodraw_handle_t *handle,
     uint64_t start_sector,
     uint64_t number_of_sectors,
     libcerror_error_t **error );

LIBODRAW_EXTERN \
int libodraw_handle_get_number_of_tracks(
     libodraw_handle_t *handle,
     int *number_of_tracks,
     libcerror_error_t **error );

LIBODRAW_EXTERN \
int libodraw_handle_get_track(
     libodraw_handle_t *handle,
     int index,
     uint64_t *start_sector,
     uint64_t *number_of_sectors,
     uint8_t *type,
     int *data_file_index,
     uint64_t *data_file_start_sector,
     libcerror_error_t **error );

LIBODRAW_EXTERN \
int libodraw_handle_append_track(
     libodraw_handle_t *handle,
     uint64_t start_sector,
     uint64_t number_of_sectors,
     uint8_t type,
     int data_file_index,
     uint64_t data_file_start_sector,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

