/*
 * Handle functions
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

#if !defined( _LIBODRAW_HANDLE_H )
#define _LIBODRAW_HANDLE_H

#include <common.h>
#include <types.h>

#include "libodraw_extern.h"
#include "libodraw_io_handle.h"
#include "libodraw_libbfio.h"
#include "libodraw_libcdata.h"
#include "libodraw_libcerror.h"
#include "libodraw_sector_range.h"
#include "libodraw_track_value.h"
#include "libodraw_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libodraw_internal_handle libodraw_internal_handle_t;

struct libodraw_internal_handle
{
	/* The current offset
	 */
	off64_t current_offset;

	/* The current run-out
	 */
	int current_run_out;

	/* The current lead-out
	 */
	int current_lead_out;

	/* The current track
	 */
	int current_track;

	/* The (storage) media size
	 */
	size64_t media_size;

	/* The number of sectors
	 */
	uint64_t number_of_sectors;

	/* The data file descriptors array
	 */
	libcdata_array_t *data_file_descriptors_array;

	/* The sessions array
	 */
	libcdata_array_t *sessions_array;

	/* The run-outs array
	 */
	libcdata_array_t *run_outs_array;

	/* The lead-outs array
	 */
	libcdata_array_t *lead_outs_array;

	/* The tracks array
	 */
	libcdata_array_t *tracks_array;

	/* The basename
	 */
	system_character_t *basename;

	/* The basename size
	 */
	size_t basename_size;

	/* The access flags
	 */
	int access_flags;

	/* The maximum number of open handles in the pool
	 */
	int maximum_number_of_open_handles;

	/* The IO handle
	 */
	libodraw_io_handle_t *io_handle;

	/* The table of contents (TOC) file IO handle
	 */
	libbfio_handle_t *toc_file_io_handle;

	/* Value to indicate if the table of contents (TOC) file IO handle was created inside the library
	 */
	uint8_t toc_file_io_handle_created_in_library;

	/* Value to indicate if the table of contents (TOC) file IO handle was opened inside the library
	 */
	uint8_t toc_file_io_handle_opened_in_library;

	/* The data file pool of file IO handles
	 */
	libbfio_pool_t *data_file_io_pool;

	/* Value to indicate if the data file IO pool was created inside the library
	 */
	uint8_t data_file_io_pool_created_in_library;
};

LIBODRAW_EXTERN \
int libodraw_handle_initialize(
     libodraw_handle_t **handle,
     libcerror_error_t **error );

LIBODRAW_EXTERN \
int libodraw_handle_free(
     libodraw_handle_t **handle,
     libcerror_error_t **error );

LIBODRAW_EXTERN \
int libodraw_handle_signal_abort(
     libodraw_handle_t *handle,
     libcerror_error_t **error );

LIBODRAW_EXTERN \
int libodraw_handle_open(
     libodraw_handle_t *handle,
     const char *filename,
     int access_flags,
     libcerror_error_t **error );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

LIBODRAW_EXTERN \
int libodraw_handle_open_wide(
     libodraw_handle_t *handle,
     const wchar_t *filename,
     int access_flags,
     libcerror_error_t **error );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

LIBODRAW_EXTERN \
int libodraw_handle_open_file_io_handle(
     libodraw_handle_t *handle,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libcerror_error_t **error );

LIBODRAW_EXTERN \
int libodraw_handle_open_data_files(
     libodraw_handle_t *handle,
     libcerror_error_t **error );

LIBODRAW_EXTERN \
int libodraw_handle_open_data_files_file_io_pool(
     libodraw_handle_t *handle,
     libbfio_pool_t *file_io_pool,
     libcerror_error_t **error );

int libodraw_handle_open_data_file(
     libodraw_internal_handle_t *internal_handle,
     int data_file_index,
     const char *filename,
     libcerror_error_t **error );

#if defined( HAVE_WIDE_CHARACTER_TYPE )
int libodraw_handle_open_data_file_wide(
     libodraw_internal_handle_t *internal_handle,
     int data_file_index,
     const wchar_t *filename,
     libcerror_error_t **error );
#endif

int libodraw_handle_open_data_file_io_handle(
     libodraw_internal_handle_t *internal_handle,
     int data_file_index,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

LIBODRAW_EXTERN \
int libodraw_handle_close(
     libodraw_handle_t *handle,
     libcerror_error_t **error );

int libodraw_handle_open_read(
     libodraw_internal_handle_t *internal_handle,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

LIBODRAW_EXTERN \
ssize_t libodraw_handle_read_buffer(
         libodraw_handle_t *handle,
         void *buffer,
         size_t buffer_size,
         libcerror_error_t **error );

ssize_t libodraw_handle_read_buffer_from_run_out(
         libodraw_internal_handle_t *internal_handle,
         uint8_t *buffer,
         size_t buffer_size,
         libcerror_error_t **error );

ssize_t libodraw_handle_read_buffer_from_lead_out(
         libodraw_internal_handle_t *internal_handle,
         uint8_t *buffer,
         size_t buffer_size,
         libcerror_error_t **error );

ssize_t libodraw_handle_read_buffer_from_unspecified_sector(
         libodraw_internal_handle_t *internal_handle,
         uint8_t *buffer,
         size_t buffer_size,
         libcerror_error_t **error );

ssize_t libodraw_handle_read_buffer_from_track(
         libodraw_internal_handle_t *internal_handle,
         uint8_t *buffer,
         size_t buffer_size,
         libcerror_error_t **error );

LIBODRAW_EXTERN \
ssize_t libodraw_handle_read_buffer_at_offset(
         libodraw_handle_t *handle,
         void *buffer,
         size_t buffer_size,
         off64_t offset,
         libcerror_error_t **error );

off64_t libodraw_internal_handle_seek_offset(
         libodraw_internal_handle_t *internal_handle,
         off64_t offset,
         int whence,
         libcerror_error_t **error );

LIBODRAW_EXTERN \
off64_t libodraw_handle_seek_offset(
         libodraw_handle_t *handle,
         off64_t offset,
         int whence,
         libcerror_error_t **error );

int libodraw_handle_get_run_out_at_offset(
     libodraw_internal_handle_t *internal_handle,
     off64_t offset,
     int *run_out_index,
     libodraw_sector_range_t **run_out_sector_range,
     off64_t *run_out_offset,
     libcerror_error_t **error );

int libodraw_handle_get_lead_out_at_offset(
     libodraw_internal_handle_t *internal_handle,
     off64_t offset,
     int *lead_out_index,
     libodraw_sector_range_t **lead_out_sector_range,
     off64_t *lead_out_offset,
     libcerror_error_t **error );

int libodraw_handle_get_track_at_offset(
     libodraw_internal_handle_t *internal_handle,
     off64_t offset,
     int *track_index,
     libodraw_track_value_t **track_value,
     off64_t *track_offset,
     libcerror_error_t **error );

LIBODRAW_EXTERN \
int libodraw_handle_get_offset(
     libodraw_handle_t *handle,
     off64_t *offset,
     libcerror_error_t **error );

int libodraw_internal_handle_get_basename_size(
     libodraw_internal_handle_t *internal_handle,
     size_t *basename_size,
     libcerror_error_t **error );

int libodraw_internal_handle_get_basename(
     libodraw_internal_handle_t *internal_handle,
     char *basename,
     size_t basename_size,
     libcerror_error_t **error );

int libodraw_internal_handle_set_basename(
     libodraw_internal_handle_t *internal_handle,
     const char *basename,
     size_t basename_length,
     libcerror_error_t **error );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

int libodraw_internal_handle_get_basename_size_wide(
     libodraw_internal_handle_t *internal_handle,
     size_t *basename_size,
     libcerror_error_t **error );

int libodraw_internal_handle_get_basename_wide(
     libodraw_internal_handle_t *internal_handle,
     wchar_t *basename,
     size_t basename_size,
     libcerror_error_t **error );

int libodraw_internal_handle_set_basename_wide(
     libodraw_internal_handle_t *internal_handle,
     const wchar_t *basename,
     size_t basename_length,
     libcerror_error_t **error );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

LIBODRAW_EXTERN \
int libodraw_handle_set_maximum_number_of_open_handles(
     libodraw_handle_t *handle,
     int maximum_number_of_open_handles,
     libcerror_error_t **error );

int libodraw_handle_set_media_values(
     libodraw_internal_handle_t *internal_handle,
     libcerror_error_t **error );

LIBODRAW_EXTERN \
int libodraw_handle_get_ascii_codepage(
     libodraw_handle_t *handle,
     int *ascii_codepage,
     libcerror_error_t **error );

LIBODRAW_EXTERN \
int libodraw_handle_set_ascii_codepage(
     libodraw_handle_t *handle,
     int ascii_codepage,
     libcerror_error_t **error );

LIBODRAW_EXTERN \
int libodraw_handle_get_number_of_data_files(
     libodraw_handle_t *handle,
     int *number_of_data_files,
     libcerror_error_t **error );

LIBODRAW_EXTERN \
int libodraw_handle_get_data_file(
     libodraw_handle_t *handle,
     int index,
     libodraw_data_file_t **data_file,
     libcerror_error_t **error );

LIBODRAW_EXTERN \
int libodraw_handle_append_data_file(
     libodraw_handle_t *handle,
     const char *name,
     size_t name_length,
     uint8_t type,
     libcerror_error_t **error );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

LIBODRAW_EXTERN \
int libodraw_handle_append_data_file_wide(
     libodraw_handle_t *handle,
     const wchar_t *name,
     size_t name_length,
     uint8_t type,
     libcerror_error_t **error );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

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

#endif /* !defined( _LIBODRAW_HANDLE_H ) */

