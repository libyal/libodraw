/*
 * OSS-Fuzz target for libodraw handle type
 *
 * Copyright (C) 2010-2026, Joachim Metz <joachim.metz@gmail.com>
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

#include <stddef.h>
#include <stdint.h>

/* Note that some of the OSS-Fuzz engines use C++
 */
extern "C" {

#include "ossfuzz_libbfio.h"
#include "ossfuzz_libodraw.h"

#if !defined( LIBODRAW_HAVE_BFIO )

/* Opens a handle using a Basic File IO (bfio) handle
 * Returns 1 if successful or -1 on error
 */
LIBODRAW_EXTERN \
int libodraw_handle_open_file_io_handle(
      libodraw_handle_t *handle,
      libbfio_handle_t *file_io_handle,
      int access_flags,
      libodraw_error_t **error );

/* Opens the data files using a Basic File IO (bfio) pool
 * This function assumes the data files are in same order as defined by the table of contents (TOC) file
 * Returns 1 if successful or -1 on error
 */
LIBODRAW_EXTERN \
int libodraw_handle_open_data_files_file_io_pool(
      libodraw_handle_t *handle,
      libbfio_pool_t *file_io_pool,
      libodraw_error_t **error );

#endif /* !defined( LIBODRAW_HAVE_BFIO ) */

int LLVMFuzzerTestOneInput(
      const uint8_t *data,
      size_t size )
{
	uint8_t buffer[ 512 ];

	libodraw_data_file_t *data_file          = NULL;
	libbfio_handle_t *file_io_handle         = NULL;
	libbfio_pool_t *file_io_pool             = NULL;
	libodraw_handle_t *handle                = NULL;
	off64_t media_offset                     = 0;
	size64_t media_size                      = 0;
	uint64_t lead_out_start_sector          = 0;
	uint64_t lead_out_number_of_sectors     = 0;
	uint64_t number_of_sectors              = 0;
	uint64_t session_start_sector           = 0;
	uint64_t session_number_of_sectors      = 0;
	uint32_t bytes_per_sector               = 0;
	uint8_t track_type                      = 0;
	uint64_t track_start_sector             = 0;
	uint64_t track_number_of_sectors        = 0;
	uint64_t track_data_file_start_sector   = 0;
	int data_file_index                    = 0;
	int entry_index                        = 0;
	int number_of_data_files               = 0;
	int number_of_lead_outs                = 0;
	int number_of_sessions                 = 0;
	int number_of_tracks                   = 0;
	int track_index                        = 0;
	int track_data_file_index              = 0;
	int read_iterator                      = 0;

	if( libbfio_memory_range_initialize(
	     &file_io_handle,
	     NULL ) != 1 )
	{
		return( 0 );
	}
	if( libbfio_memory_range_set(
	     file_io_handle,
	     (uint8_t *) data,
	     size,
	     NULL ) != 1 )
	{
		goto on_error_libbfio;
	}
	if( libbfio_pool_initialize(
	     &file_io_pool,
	     0,
	     0,
	     NULL ) != 1 )
	{
		goto on_error_libbfio;
	}
	if( libodraw_handle_initialize(
	     &handle,
	     NULL ) != 1 )
	{
		goto on_error_libbfio;
	}
	if( libodraw_handle_open_file_io_handle(
	     handle,
	     file_io_handle,
	     LIBODRAW_OPEN_READ,
	     NULL ) != 1 )
	{
		goto on_error_libodraw;
	}
	if( libbfio_pool_append_handle(
	     file_io_pool,
	     &entry_index,
	     file_io_handle,
	     LIBBFIO_OPEN_READ,
	     NULL ) != 1 )
	{
		goto on_error_libodraw;
	}
	/* The file IO pool takes over management of the file IO handle
	 */
	file_io_handle = NULL;

	if( libodraw_handle_open_data_files_file_io_pool(
	     handle,
	     file_io_pool,
	     NULL ) != 1 )
	{
		goto on_error_libodraw;
	}
	if( libodraw_handle_get_bytes_per_sector(
	     handle,
	     &bytes_per_sector,
	     NULL ) != 1 )
	{
		goto on_error_libodraw;
	}
	if( libodraw_handle_get_number_of_sectors(
	     handle,
	     &number_of_sectors,
	     NULL ) != 1 )
	{
		goto on_error_libodraw;
	}
	if( libodraw_handle_get_media_size(
	     handle,
	     &media_size,
	     NULL ) != 1 )
	{
		goto on_error_libodraw;
	}
	if( libodraw_handle_get_number_of_data_files(
	     handle,
	     &number_of_data_files,
	     NULL ) == 1 )
	{
		for( data_file_index = 0;
		     data_file_index < number_of_data_files;
		     data_file_index++ )
		{
			if( data_file_index >= 16 )
			{
				break;
			}
			if( libodraw_handle_get_data_file(
			     handle,
			     data_file_index,
			     &data_file,
			     NULL ) != 1 )
			{
				goto on_error_libodraw;
			}
			if( libodraw_data_file_free(
			     &data_file,
			     NULL ) != 1 )
			{
				goto on_error_libodraw;
			}
		}
	}
	if( libodraw_handle_get_number_of_sessions(
	     handle,
	     &number_of_sessions,
	     NULL ) == 1 )
	{
		if( number_of_sessions > 0 )
		{
			if( libodraw_handle_get_session(
			     handle,
			     0,
			     &session_start_sector,
			     &session_number_of_sectors,
			     NULL ) != 1 )
			{
				goto on_error_libodraw;
			}
		}
	}
	if( libodraw_handle_get_number_of_lead_outs(
	     handle,
	     &number_of_lead_outs,
	     NULL ) == 1 )
	{
		if( number_of_lead_outs > 0 )
		{
			if( libodraw_handle_get_lead_out(
			     handle,
			     0,
			     &lead_out_start_sector,
			     &lead_out_number_of_sectors,
			     NULL ) != 1 )
			{
				goto on_error_libodraw;
			}
		}
	}
	if( libodraw_handle_get_number_of_tracks(
	     handle,
	     &number_of_tracks,
	     NULL ) == 1 )
	{
		for( track_index = 0;
		     track_index < number_of_tracks;
		     track_index++ )
		{
			if( track_index >= 16 )
			{
				break;
			}
			if( libodraw_handle_get_track(
			     handle,
			     track_index,
			     &track_start_sector,
			     &track_number_of_sectors,
			     &track_type,
			     &track_data_file_index,
			     &track_data_file_start_sector,
			     NULL ) != 1 )
			{
				goto on_error_libodraw;
			}
		}
	}
	for( read_iterator = 0;
	     read_iterator < 128;
	     read_iterator++ )
	{
		if( media_offset >= media_size )
		{
			break;
		}
		if( libodraw_handle_read_buffer_at_offset(
		     handle,
		     buffer,
		     497,
		     media_offset,
		     NULL ) == -1 )
		{
			goto on_error_libodraw;
		}
		media_offset += 497;
	}
	libodraw_handle_close(
	 handle,
	 NULL );

on_error_libodraw:
	libodraw_handle_free(
	 &handle,
	 NULL );

on_error_libbfio:
	/* Note that on error the handle still has a reference to file_io_pool
	 * that will be closed. Therefore the file IO pool and handle need to
	 * be freed after closing or freeing the handle.
	 */
	if( file_io_pool != NULL )
	{
		libbfio_pool_free(
		 &file_io_pool,
		 NULL );
	}
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( 0 );
}

} /* extern "C" */
