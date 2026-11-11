/*
 * OSS-Fuzz target for libodraw data file type
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
	char string[ 64 ];

	libodraw_data_file_t *data_file    = NULL;
	libbfio_handle_t *file_io_handle   = NULL;
	libbfio_pool_t *file_io_pool       = NULL;
	libodraw_handle_t *handle          = NULL;
	uint8_t data_file_type             = 0;
	size_t filename_set_size           = 0;
	size_t string_size                 = 0;
	int data_file_index                = 0;
	int entry_index                    = 0;
	int number_of_data_files           = 0;

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
	if( libodraw_handle_get_number_of_data_files(
	     handle,
	     &number_of_data_files,
	     NULL ) == 1 )
	{
		if( number_of_data_files > 0 )
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
					goto on_error_libodraw_data_file;
				}
				if( libodraw_data_file_get_filename_size(
				     data_file,
				     &string_size,
				     NULL ) != 1 )
				{
					goto on_error_libodraw_data_file;
				}
				if( libodraw_data_file_get_filename(
				     data_file,
				     string,
				     64,
				     NULL ) != 1 )
				{
					goto on_error_libodraw_data_file;
				}
				if( libodraw_data_file_get_type(
				     data_file,
				     &data_file_type,
				     NULL ) != 1 )
				{
					goto on_error_libodraw_data_file;
				}
				/* Set the filename of the data file using the fuzz data
				 * to exercise the name conversion in the data file descriptor
				 */
				if( size > 0 )
				{
					filename_set_size = (size_t) 64;

					if( size < filename_set_size )
					{
						filename_set_size = size;
					}
					libodraw_data_file_set_filename(
					 data_file,
					 (char *) data,
					 filename_set_size,
					 NULL );
				}
on_error_libodraw_data_file:
				libodraw_data_file_free(
				 &data_file,
				 NULL );
			}
		}
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
