/*
 * Info handle
 *
 * Copyright (C) 2010-2019, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _INFO_HANDLE_H )
#define _INFO_HANDLE_H

#include <common.h>
#include <file_stream.h>
#include <types.h>

#include "odrawtools_libcerror.h"
#include "odrawtools_libodraw.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct info_handle info_handle_t;

struct info_handle
{
	/* The libodraw input handle
	 */
	libodraw_handle_t *input_handle;

	/* Value to indicate to ignore the data files
	 */
	uint8_t ignore_data_files;

	/* The notification output stream
	 */
	FILE *notify_stream;
};

const char *info_handle_get_data_file_type(
             uint8_t data_file_type );

const char *info_handle_get_track_type(
             uint8_t track_type );

int info_handle_initialize(
     info_handle_t **info_handle,
     libcerror_error_t **error );

int info_handle_free(
     info_handle_t **info_handle,
     libcerror_error_t **error );

int info_handle_signal_abort(
     info_handle_t *info_handle,
     libcerror_error_t **error );

int info_handle_open_input(
     info_handle_t *info_handle,
     const system_character_t *filename,
     libcerror_error_t **error );

int info_handle_close(
     info_handle_t *info_handle,
     libcerror_error_t **error );

int info_handle_data_files_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error );

int info_handle_sessions_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error );

int info_handle_lead_outs_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error );

int info_handle_tracks_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error );

int info_handle_handle_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _INFO_HANDLE_H ) */

