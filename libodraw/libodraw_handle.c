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

#include <common.h>
#include <memory.h>
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#include "libodraw_codepage.h"
#include "libodraw_cue_parser.h"
#include "libodraw_data_file.h"
#include "libodraw_data_file_descriptor.h"
#include "libodraw_debug.h"
#include "libodraw_definitions.h"
#include "libodraw_io_handle.h"
#include "libodraw_handle.h"
#include "libodraw_libbfio.h"
#include "libodraw_libcdata.h"
#include "libodraw_libcerror.h"
#include "libodraw_libclocale.h"
#include "libodraw_libcnotify.h"
#include "libodraw_libcpath.h"
#include "libodraw_libuna.h"
#include "libodraw_sector_range.h"
#include "libodraw_track_value.h"
#include "libodraw_types.h"

extern int cue_parser_parse_buffer(
            libodraw_handle_t *handle,
            const uint8_t *buffer,
            size_t buffer_size,
            libcerror_error_t **error );

/* Creates a handle
 * Make sure the value handle is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libodraw_handle_initialize(
     libodraw_handle_t **handle,
     libcerror_error_t **error )
{
	libodraw_internal_handle_t *internal_handle = NULL;
	static char *function                       = "libodraw_handle_initialize";

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	if( *handle != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid handle value already set.",
		 function );

		return( -1 );
	}
	internal_handle = memory_allocate_structure(
	                   libodraw_internal_handle_t );

	if( internal_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create handle.",
		 function );

		return( -1 );
	}
	if( memory_set(
	     internal_handle,
	     0,
	     sizeof( libodraw_internal_handle_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear handle.",
		 function );

		memory_free(
		 internal_handle );

		return( -1 );
	}
	if( libcdata_array_initialize(
	     &( internal_handle->data_file_descriptors_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create data file descriptors array.",
		 function );

		goto on_error;
	}
	if( libcdata_array_initialize(
	     &( internal_handle->sessions_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create sessions array.",
		 function );

		goto on_error;
	}
	if( libcdata_array_initialize(
	     &( internal_handle->run_outs_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create run-outs array.",
		 function );

		goto on_error;
	}
	if( libcdata_array_initialize(
	     &( internal_handle->lead_outs_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create lead-outs array.",
		 function );

		goto on_error;
	}
	if( libcdata_array_initialize(
	     &( internal_handle->tracks_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create tracks array.",
		 function );

		goto on_error;
	}
	if( libodraw_io_handle_initialize(
	     &( internal_handle->io_handle ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create IO handle.",
		 function );

		goto on_error;
	}
	internal_handle->maximum_number_of_open_handles = LIBBFIO_POOL_UNLIMITED_NUMBER_OF_OPEN_HANDLES;

	*handle = (libodraw_handle_t *) internal_handle;

	return( 1 );

on_error:
	if( internal_handle != NULL )
	{
		if( internal_handle->tracks_array != NULL )
		{
			libcdata_array_free(
			 &( internal_handle->tracks_array ),
			 NULL,
			 NULL );
		}
		if( internal_handle->lead_outs_array != NULL )
		{
			libcdata_array_free(
			 &( internal_handle->lead_outs_array ),
			 NULL,
			 NULL );
		}
		if( internal_handle->run_outs_array != NULL )
		{
			libcdata_array_free(
			 &( internal_handle->run_outs_array ),
			 NULL,
			 NULL );
		}
		if( internal_handle->sessions_array != NULL )
		{
			libcdata_array_free(
			 &( internal_handle->sessions_array ),
			 NULL,
			 NULL );
		}
		if( internal_handle->data_file_descriptors_array != NULL )
		{
			libcdata_array_free(
			 &( internal_handle->data_file_descriptors_array ),
			 NULL,
			 NULL );
		}
		memory_free(
		 internal_handle );
	}
	return( -1 );
}

/* Frees a handle
 * Returns 1 if successful or -1 on error
 */
int libodraw_handle_free(
     libodraw_handle_t **handle,
     libcerror_error_t **error )
{
	libodraw_internal_handle_t *internal_handle = NULL;
	static char *function                       = "libodraw_handle_free";
	int result                                  = 1;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	if( *handle != NULL )
	{
		internal_handle = (libodraw_internal_handle_t *) *handle;

		if( ( internal_handle->toc_file_io_handle != NULL )
		 || ( internal_handle->data_file_io_pool != NULL ) )
		{
			if( libodraw_handle_close(
			     *handle,
			     error ) != 0 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_CLOSE_FAILED,
				 "%s: unable to close handle.",
				 function );

				result = -1;
			}
		}
		*handle = NULL;

		if( libcdata_array_free(
		     &( internal_handle->data_file_descriptors_array ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libodraw_data_file_descriptor_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free files array.",
			 function );

			result = -1;
		}
		if( libcdata_array_free(
		     &( internal_handle->sessions_array ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libodraw_sector_range_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free sessions array.",
			 function );

			result = -1;
		}
		if( libcdata_array_free(
		     &( internal_handle->run_outs_array ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libodraw_sector_range_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free run-outs array.",
			 function );

			result = -1;
		}
		if( libcdata_array_free(
		     &( internal_handle->lead_outs_array ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libodraw_sector_range_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free lead-outs array.",
			 function );

			result = -1;
		}
		if( libcdata_array_free(
		     &( internal_handle->tracks_array ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libodraw_track_value_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free tracks array.",
			 function );

			result = -1;
		}
		if( libodraw_io_handle_free(
		     &( internal_handle->io_handle ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free IO handle.",
			 function );

			result = -1;
		}
		memory_free(
		 internal_handle );
	}
	return( result );
}

/* Signals the handle to abort its current activity
 * Returns 1 if successful or -1 on error
 */
int libodraw_handle_signal_abort(
     libodraw_handle_t *handle,
     libcerror_error_t **error )
{
	libodraw_internal_handle_t *internal_handle = NULL;
	static char *function                       = "libodraw_handle_signal_abort";

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libodraw_internal_handle_t *) handle;

	if( internal_handle->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing IO handle.",
		 function );

		return( -1 );
	}
	internal_handle->io_handle->abort = 1;

	return( 1 );
}

/* Opens a handle using a table of contents (TOC) file
 * Returns 1 if successful or -1 on error
 */
int libodraw_handle_open(
     libodraw_handle_t *handle,
     const char *filename,
     int access_flags,
     libcerror_error_t **error )
{
	libbfio_handle_t *file_io_handle            = NULL;
	libodraw_internal_handle_t *internal_handle = NULL;
	char *basename_end                          = NULL;
	static char *function                       = "libodraw_handle_open";
	size_t basename_length                      = 0;
	size_t filename_length                      = 0;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libodraw_internal_handle_t *) handle;

	if( internal_handle->basename != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid handle - basename already set.",
		 function );

		return( -1 );
	}
	if( filename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename.",
		 function );

		return( -1 );
	}
	if( ( ( access_flags & LIBODRAW_ACCESS_FLAG_READ ) == 0 )
	 && ( ( access_flags & LIBODRAW_ACCESS_FLAG_WRITE ) == 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported access flags.",
		 function );

		return( -1 );
	}
	if( ( access_flags & LIBODRAW_ACCESS_FLAG_WRITE ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: write access currently not supported.",
		 function );

		return( -1 );
	}
	filename_length = narrow_string_length(
	                   filename );

	basename_end = narrow_string_search_character_reverse(
	                filename,
	                (int) LIBCPATH_SEPARATOR,
	                filename_length + 1 );

	if( basename_end != NULL )
	{
		basename_length = (size_t) ( basename_end - filename ) + 1;
	}
	if( basename_length > 0 )
	{
		if( libodraw_internal_handle_set_basename(
		     internal_handle,
		     filename,
		     basename_length,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set basename.",
			 function );

			goto on_error;
		}
	}
	if( libbfio_file_initialize(
	     &file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create file IO handle.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libbfio_handle_set_track_offsets_read(
	     file_io_handle,
	     1,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set track offsets read in file IO handle.",
		 function );

		goto on_error;
	}
#endif
	if( libbfio_file_set_name(
	     file_io_handle,
	     filename,
	     filename_length + 1,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set filename in file IO handle.",
		 function );

		goto on_error;
	}
	if( libodraw_handle_open_file_io_handle(
	     handle,
	     file_io_handle,
	     access_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open file: %s.",
		 function,
		 filename );

		goto on_error;
	}
	internal_handle->toc_file_io_handle_created_in_library = 1;

	return( 1 );

on_error:
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	if( internal_handle->basename != NULL )
	{
		memory_free(
		 internal_handle->basename );

		internal_handle->basename = NULL;
	}
	internal_handle->basename_size = 0;

	return( -1 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Opens a handle using a table of contents (TOC) file
 * Returns 1 if successful or -1 on error
 */
int libodraw_handle_open_wide(
     libodraw_handle_t *handle,
     const wchar_t *filename,
     int access_flags,
     libcerror_error_t **error )
{
	libbfio_handle_t *file_io_handle            = NULL;
	libodraw_internal_handle_t *internal_handle = NULL;
	wchar_t *basename_end                       = NULL;
	static char *function                       = "libodraw_handle_open_wide";
	size_t basename_length                      = 0;
	size_t filename_length                      = 0;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libodraw_internal_handle_t *) handle;

	if( internal_handle->basename != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid handle - basename already set.",
		 function );

		return( -1 );
	}
	if( filename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename.",
		 function );

		return( -1 );
	}
	if( ( ( access_flags & LIBODRAW_ACCESS_FLAG_READ ) == 0 )
	 && ( ( access_flags & LIBODRAW_ACCESS_FLAG_WRITE ) == 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported access flags.",
		 function );

		return( -1 );
	}
	if( ( access_flags & LIBODRAW_ACCESS_FLAG_WRITE ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: write access currently not supported.",
		 function );

		return( -1 );
	}
	filename_length = wide_string_length(
	                   filename );

/* TODO does this work for UTF-16 ? */
	basename_end = wide_string_search_character_reverse(
	                filename,
	                (wint_t) LIBCPATH_SEPARATOR,
	                filename_length + 1 );

	if( basename_end != NULL )
	{
		basename_length = (size_t) ( basename_end - filename ) + 1;
	}
	if( basename_length > 0 )
	{
		if( libodraw_internal_handle_set_basename_wide(
		     internal_handle,
		     filename,
		     basename_length,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set basename.",
			 function );

			goto on_error;
		}
	}
	if( libbfio_file_initialize(
	     &file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create file IO handle.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libbfio_handle_set_track_offsets_read(
	     file_io_handle,
	     1,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set track offsets read in file IO handle.",
		 function );

		goto on_error;
	}
#endif
	if( libbfio_file_set_name_wide(
	     file_io_handle,
	     filename,
	     wide_string_length(
	      filename ) + 1,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set filename in file IO handle.",
		 function );

		goto on_error;
	}
	if( libodraw_handle_open_file_io_handle(
	     handle,
	     file_io_handle,
	     access_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open file: %ls.",
		 function,
		 filename );

		goto on_error;
	}
	internal_handle->toc_file_io_handle_created_in_library = 1;

	return( 1 );

on_error:
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	if( internal_handle->basename != NULL )
	{
		memory_free(
		 internal_handle->basename );

		internal_handle->basename = NULL;
	}
	internal_handle->basename_size = 0;

	return( -1 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Opens a handle using a Basic File IO (bfio) handle of a table of contents (TOC) file
 * Returns 1 if successful or -1 on error
 */
int libodraw_handle_open_file_io_handle(
     libodraw_handle_t *handle,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libcerror_error_t **error )
{
	libodraw_internal_handle_t *internal_handle = NULL;
	static char *function                       = "libodraw_handle_open_file_io_handle";
	int bfio_access_flags                       = 0;
	int file_io_handle_is_open                  = 0;
	int file_io_handle_opened_in_library        = 0;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libodraw_internal_handle_t *) handle;

	if( internal_handle->toc_file_io_handle != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid handle - file IO handle already set.",
		 function );

		return( -1 );
	}
	if( file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file IO handle.",
		 function );

		return( -1 );
	}
	if( ( ( access_flags & LIBODRAW_ACCESS_FLAG_READ ) == 0 )
	 && ( ( access_flags & LIBODRAW_ACCESS_FLAG_WRITE ) == 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported access flags.",
		 function );

		return( -1 );
	}
	if( ( access_flags & LIBODRAW_ACCESS_FLAG_WRITE ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: write access currently not supported.",
		 function );

		return( -1 );
	}
	if( ( access_flags & LIBODRAW_ACCESS_FLAG_READ ) != 0 )
	{
		bfio_access_flags = LIBBFIO_ACCESS_FLAG_READ;
	}
	file_io_handle_is_open = libbfio_handle_is_open(
	                          file_io_handle,
	                          error );

	if( file_io_handle_is_open == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open file.",
		 function );

		goto on_error;
	}
	else if( file_io_handle_is_open == 0 )
	{
		if( libbfio_handle_open(
		     file_io_handle,
		     bfio_access_flags,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_OPEN_FAILED,
			 "%s: unable to open file IO handle.",
			 function );

			goto on_error;
		}
		file_io_handle_opened_in_library = 1;
	}
	if( libodraw_handle_open_read(
	     internal_handle,
	     file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read from handle.",
		 function );

		goto on_error;
	}
	internal_handle->access_flags                         = access_flags;
	internal_handle->toc_file_io_handle                   = file_io_handle;
	internal_handle->toc_file_io_handle_opened_in_library = file_io_handle_opened_in_library;

	return( 1 );

on_error:
	if( ( file_io_handle_is_open == 0 )
	 && ( file_io_handle_opened_in_library != 0 ) )
	{
		libbfio_handle_close(
		 file_io_handle,
		 error );
	}
	return( -1 );
}

/* Opens the data files
 * If the data filenames were not set explicitly this function assumes the data files
 * are in the same location as the table of contents (TOC) file
 * Returns 1 if successful or -1 on error
 */
int libodraw_handle_open_data_files(
     libodraw_handle_t *handle,
     libcerror_error_t **error )
{
	libodraw_data_file_descriptor_t *data_file_descriptor = NULL;
	libodraw_internal_handle_t *internal_handle           = NULL;
	system_character_t *data_file_location                = NULL;
	system_character_t *data_file_name_start              = NULL;
	static char *function                                 = "libodraw_handle_open_data_files";
	size_t data_file_location_size                        = 0;
	size_t data_file_name_size                            = 0;
	int data_file_descriptor_index                        = 0;
	int number_of_data_file_descriptors                   = 0;
	int result                                            = 0;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libodraw_internal_handle_t *) handle;

	if( internal_handle->toc_file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing TOC file IO handle.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_number_of_entries(
	     internal_handle->data_file_descriptors_array,
	     &number_of_data_file_descriptors,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of data file descriptors.",
		 function );

		return( -1 );
	}
	for( data_file_descriptor_index = 0;
	     data_file_descriptor_index < number_of_data_file_descriptors;
	     data_file_descriptor_index++ )
	{
		if( libcdata_array_get_entry_by_index(
		     internal_handle->data_file_descriptors_array,
		     data_file_descriptor_index,
		     (intptr_t **) &data_file_descriptor,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve data file descriptor: %d.",
			 function,
			 data_file_descriptor_index );

			goto on_error;
		}
		if( data_file_descriptor == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing data file descriptor: %d.",
			 function,
			 data_file_descriptor_index );

			goto on_error;
		}
		if( ( data_file_descriptor->name == NULL )
		 || ( data_file_descriptor->name_size == 0 ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: invalid data file descriptor: %d - missing name.",
			 function,
			 data_file_descriptor_index );

			goto on_error;
		}
		if( data_file_descriptor->name_set == 0 )
		{
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
			data_file_name_start = wide_string_search_character_reverse(
			                        data_file_descriptor->name,
			                        (wint_t) LIBCPATH_SEPARATOR,
			                        data_file_descriptor->name_size );
#else
			data_file_name_start = narrow_string_search_character_reverse(
			                        data_file_descriptor->name,
			                        (int) LIBCPATH_SEPARATOR,
		        	                data_file_descriptor->name_size );
#endif
		}
		if( data_file_name_start != NULL )
		{
			/* Ignore the path separator itself
			 */
			data_file_name_start++;

/* TODO does this work for UTF-16 ? */
			data_file_name_size = (size_t) ( data_file_name_start - data_file_descriptor->name );
		}
		else
		{
			data_file_name_start = data_file_descriptor->name;
			data_file_name_size  = data_file_descriptor->name_size;
		}
		if( ( data_file_descriptor->name_set == 0 )
		 && ( internal_handle->basename != NULL ) )
		{
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
			if( libcpath_path_join_wide(
			     &data_file_location,
			     &data_file_location_size,
			     internal_handle->basename,
			     internal_handle->basename_size - 1,
			     data_file_name_start,
			     data_file_name_size - 1,
			     error ) != 1 )
#else
			if( libcpath_path_join(
			     &data_file_location,
			     &data_file_location_size,
			     internal_handle->basename,
			     internal_handle->basename_size - 1,
			     data_file_name_start,
			     data_file_name_size - 1,
			     error ) != 1 )
#endif
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
				 "%s: unable to create data file location.",
				 function );

				goto on_error;
			}
		}
		else
		{
			data_file_location      = data_file_name_start;
			data_file_location_size = data_file_name_size;
		}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libodraw_handle_open_data_file_wide(
			  internal_handle,
			  data_file_descriptor_index,
			  data_file_location,
			  error );
#else
		result = libodraw_handle_open_data_file(
			  internal_handle,
			  data_file_descriptor_index,
			  data_file_location,
			  error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_OPEN_FAILED,
			 "%s: unable to open data file: %" PRIs_SYSTEM ".",
			 function,
			 data_file_location );

			goto on_error;
		}
		if( ( data_file_location != NULL )
		 && ( data_file_location != data_file_name_start ) )
		{
			memory_free(
			 data_file_location );
		}
		data_file_name_start = NULL;
		data_file_location   = NULL;
	}
	if( libodraw_handle_set_media_values(
	     internal_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set media values.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( ( data_file_location != NULL )
	 && ( data_file_location != data_file_name_start ) )
	{
		memory_free(
		 data_file_location );
	}
	return( -1 );
}

/* Opens the data files using a Basic File IO (bfio) pool
 * This function assumes the data files are in same order as defined by the table of contents (TOC) file
 * Returns 1 if successful or -1 on error
 */
int libodraw_handle_open_data_files_file_io_pool(
     libodraw_handle_t *handle,
     libbfio_pool_t *file_io_pool,
     libcerror_error_t **error )
{
	libodraw_internal_handle_t *internal_handle = NULL;
	static char *function                       = "libodraw_handle_open_data_files_file_io_pool";

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libodraw_internal_handle_t *) handle;

	if( internal_handle->toc_file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing TOC file IO handle.",
		 function );

		return( -1 );
	}
	if( internal_handle->data_file_io_pool != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid handle - data file IO pool already exists.",
		 function );

		return( -1 );
	}
	if( file_io_pool == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file IO pool.",
		 function );

		return( -1 );
	}
	internal_handle->data_file_io_pool = file_io_pool;

	if( libodraw_handle_set_media_values(
	     internal_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set media values.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Opens a specific data file
 * Returns 1 if successful or -1 on error
 */
int libodraw_handle_open_data_file(
     libodraw_internal_handle_t *internal_handle,
     int data_file_index,
     const char *filename,
     libcerror_error_t **error )
{
	libbfio_handle_t *file_io_handle = NULL;
	static char *function            = "libodraw_handle_open_data_file";

	if( internal_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	if( internal_handle->toc_file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing TOC file IO handle.",
		 function );

		return( -1 );
	}
	if( filename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename.",
		 function );

		return( -1 );
	}
	if( libbfio_file_initialize(
	     &file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create file IO handle.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libbfio_handle_set_track_offsets_read(
	     file_io_handle,
	     1,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set track offsets read in file IO handle.",
		 function );

		goto on_error;
	}
#endif
	if( libbfio_file_set_name(
	     file_io_handle,
	     filename,
	     narrow_string_length(
	      filename ) + 1,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set filename in file IO handle.",
		 function );

		goto on_error;
	}
	if( libodraw_handle_open_data_file_io_handle(
	     internal_handle,
	     data_file_index,
	     file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open data file: %s.",
		 function,
		 filename );

		goto on_error;
	}
	return( 1 );

on_error:
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( -1 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Opens a specific data file
 * Returns 1 if successful or -1 on error
 */
int libodraw_handle_open_data_file_wide(
     libodraw_internal_handle_t *internal_handle,
     int data_file_index,
     const wchar_t *filename,
     libcerror_error_t **error )
{
	libbfio_handle_t *file_io_handle = NULL;
	static char *function            = "libodraw_handle_open_data_file_wide";

	if( internal_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	if( internal_handle->toc_file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing TOC file IO handle.",
		 function );

		return( -1 );
	}
	if( filename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename.",
		 function );

		return( -1 );
	}
	if( libbfio_file_initialize(
	     &file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create file IO handle.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libbfio_handle_set_track_offsets_read(
	     file_io_handle,
	     1,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set track offsets read in file IO handle.",
		 function );

		goto on_error;
	}
#endif
	if( libbfio_file_set_name_wide(
	     file_io_handle,
	     filename,
	     wide_string_length(
	      filename ) + 1,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set filename in file IO handle.",
		 function );

		goto on_error;
	}
	if( libodraw_handle_open_data_file_io_handle(
	     internal_handle,
	     data_file_index,
	     file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open data file: %ls.",
		 function,
		 filename );

		goto on_error;
	}
	return( 1 );

on_error:
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( -1 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Opens a data file using a Basic File IO (bfio) handle
 * Returns 1 if successful or -1 on error
 */
int libodraw_handle_open_data_file_io_handle(
     libodraw_internal_handle_t *internal_handle,
     int data_file_index,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	static char *function               = "libodraw_handle_open_data_file_io_handle";
	int bfio_access_flags               = 0;
	int number_of_data_file_descriptors = 0;

	if( internal_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	if( internal_handle->toc_file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing TOC file IO handle.",
		 function );

		return( -1 );
	}
	if( file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file IO handle.",
		 function );

		return( -1 );
	}
	if( ( ( internal_handle->access_flags & LIBODRAW_ACCESS_FLAG_READ ) == 0 )
	 && ( ( internal_handle->access_flags & LIBODRAW_ACCESS_FLAG_WRITE ) == 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported access flags.",
		 function );

		return( -1 );
	}
	if( ( internal_handle->access_flags & LIBODRAW_ACCESS_FLAG_WRITE ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: write access currently not supported.",
		 function );

		return( -1 );
	}
	if( internal_handle->data_file_io_pool == NULL )
	{
		if( libcdata_array_get_number_of_entries(
		     internal_handle->data_file_descriptors_array,
		     &number_of_data_file_descriptors,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve number of data file descriptors.",
			 function );

			return( -1 );
		}
		if( libbfio_pool_initialize(
		     &( internal_handle->data_file_io_pool ),
		     number_of_data_file_descriptors,
		     internal_handle->maximum_number_of_open_handles,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create data file file IO pool.",
			 function );

			return( -1 );
		}
		internal_handle->data_file_io_pool_created_in_library = 1;
	}
	if( ( internal_handle->access_flags & LIBODRAW_ACCESS_FLAG_READ ) != 0 )
	{
		bfio_access_flags = LIBBFIO_ACCESS_FLAG_READ;
	}
	if( libbfio_handle_open(
	     file_io_handle,
	     bfio_access_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open file IO handle.",
		 function );

		return( -1 );
	}
	/* This function currently does not allow the file_io_handle to be set more than once
	 */
	if( libbfio_pool_set_handle(
	     internal_handle->data_file_io_pool,
	     data_file_index,
	     file_io_handle,
	     bfio_access_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set file IO handle: %d in pool.",
		 function,
		 data_file_index );

		return( -1 );
	}
	return( 1 );
}

/* Closes a handle
 * Returns 0 if successful or -1 on error
 */
int libodraw_handle_close(
     libodraw_handle_t *handle,
     libcerror_error_t **error )
{
	libodraw_internal_handle_t *internal_handle = NULL;
	static char *function                       = "libodraw_handle_close";
	int result                                  = 0;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libodraw_internal_handle_t *) handle;

	if( internal_handle->toc_file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing TOC file IO handle.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( internal_handle->toc_file_io_handle_created_in_library != 0 )
		{
			if( libodraw_debug_print_read_offsets(
			     internal_handle->toc_file_io_handle,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
				 "%s: unable to print the read offsets.",
				 function );

				result = -1;
			}
		}
	}
#endif
	if( internal_handle->toc_file_io_handle_opened_in_library != 0 )
	{
		if( libbfio_handle_close(
		     internal_handle->toc_file_io_handle,
		     error ) != 0 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_CLOSE_FAILED,
			 "%s: unable to close TOC file IO handle.",
			 function );

			result = -1;
		}
		internal_handle->toc_file_io_handle_opened_in_library = 0;
	}
	if( internal_handle->toc_file_io_handle_created_in_library != 0 )
	{
		if( libbfio_handle_free(
		     &( internal_handle->toc_file_io_handle ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free TOC file IO handle.",
			 function );

			result = -1;
		}
		internal_handle->toc_file_io_handle_created_in_library = 0;
	}
	internal_handle->toc_file_io_handle = NULL;

	if( internal_handle->data_file_io_pool != 0 )
	{
		if( internal_handle->data_file_io_pool != NULL )
		{
			if( libbfio_pool_close_all(
			     internal_handle->data_file_io_pool,
			     error ) != 0 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_GENERIC,
				 "%s: unable close data files IO pool.",
				 function );

				result = -1;
			}
			if( libbfio_pool_free(
			     &( internal_handle->data_file_io_pool ),
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free data files IO pool.",
				 function );

				result = -1;
			}
		}
		internal_handle->data_file_io_pool_created_in_library = 0;
	}
	internal_handle->data_file_io_pool = NULL;

	internal_handle->current_offset    = 0;
	internal_handle->current_run_out   = 0;
	internal_handle->current_lead_out  = 0;
	internal_handle->current_track     = 0;
	internal_handle->media_size        = 0;
	internal_handle->number_of_sectors = 0;

	if( libodraw_io_handle_clear(
	     internal_handle->io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to clear IO handle.",
		 function );

		result = -1;
	}
	if( libcdata_array_empty(
	     internal_handle->data_file_descriptors_array,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libodraw_data_file_descriptor_free,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to empty data file descriptors array.",
		 function );

		result = -1;
	}
	if( libcdata_array_empty(
	     internal_handle->sessions_array,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libodraw_sector_range_free,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to empty sessions array.",
		 function );

		result = -1;
	}
	if( libcdata_array_empty(
	     internal_handle->run_outs_array,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libodraw_sector_range_free,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to empty run-outs array.",
		 function );

		result = -1;
	}
	if( libcdata_array_empty(
	     internal_handle->lead_outs_array,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libodraw_sector_range_free,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to empty lead-outs array.",
		 function );

		result = -1;
	}
	if( libcdata_array_empty(
	     internal_handle->tracks_array,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libodraw_track_value_free,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to empty tracks array.",
		 function );

		result = -1;
	}
	if( internal_handle->basename != NULL )
	{
		memory_free(
		 internal_handle->basename );

		internal_handle->basename = NULL;
	}
	internal_handle->basename_size = 0;

	return( result );
}

/* Opens a handle for reading
 * Returns 1 if successful or -1 on error
 */
int libodraw_handle_open_read(
     libodraw_internal_handle_t *internal_handle,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	uint8_t *buffer       = NULL;
	static char *function = "libodraw_handle_open_read";
	size64_t file_size    = 0;
	size_t buffer_size    = 0;
	ssize_t read_count    = 0;
	int result            = 1;

	if( internal_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	if( internal_handle->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing IO handle.",
		 function );

		return( -1 );
	}
	if( libcdata_array_empty(
	     internal_handle->data_file_descriptors_array,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libodraw_track_value_free,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to empty data file descriptors array.",
		 function );

		goto on_error;
	}
	if( libcdata_array_empty(
	     internal_handle->sessions_array,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libodraw_sector_range_free,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to empty sessions array.",
		 function );

		goto on_error;
	}
	if( libcdata_array_empty(
	     internal_handle->run_outs_array,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libodraw_sector_range_free,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to empty run-outs array.",
		 function );

		goto on_error;
	}
	if( libcdata_array_empty(
	     internal_handle->lead_outs_array,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libodraw_sector_range_free,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to empty lead-outs array.",
		 function );

		goto on_error;
	}
	if( libcdata_array_empty(
	     internal_handle->tracks_array,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libodraw_track_value_free,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to empty tracks array.",
		 function );

		goto on_error;
	}
	if( internal_handle->io_handle->abort != 0 )
	{
		internal_handle->io_handle->abort = 0;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "Reading file:\n" );
	}
#endif
	if( libbfio_handle_get_size(
	     file_io_handle,
	     &file_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve TOC file size.",
		 function );

		goto on_error;
	}
	if( file_size > (size64_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid file size value exceeds maximum.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading TOC file header at offset: 0 (0x00000000)\n",
		 function );
	}
#endif
	if( libbfio_handle_seek_offset(
	     file_io_handle,
	     0,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek TOC file offset: 0.",
		 function );

		goto on_error;
	}
	/* Lex wants 2 zero bytes at the end of the buffer
	 */
	buffer_size = (size_t) file_size + 2;

	buffer = (uint8_t *) memory_allocate(
	                      sizeof( uint8_t ) * buffer_size );

	if( buffer == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create buffer.",
		 function );

		goto on_error;
	}
	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
	              buffer,
	              (size_t) file_size,
	              error );

	if( read_count != (ssize_t) file_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read TOC file data.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: file data:\n",
		 function );
		libcnotify_print_data(
		 buffer,
		 (size_t) file_size,
		 0 );
	}
#endif
	/* Lex wants 2 zero bytes at the end of the buffer
	 */
	buffer[ buffer_size - 2 ] = 0;
	buffer[ buffer_size - 1 ] = 0;

	result = cue_parser_parse_buffer(
	          (libodraw_handle_t *) internal_handle,
	          buffer,
	          buffer_size,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to parse file data.",
		 function );

		goto on_error;
	}
	memory_free(
	 buffer );

	buffer = NULL;

	if( internal_handle->io_handle->abort != 0 )
	{
		internal_handle->io_handle->abort = 0;
	}
	return( result );

on_error:
	if( buffer != NULL )
	{
		memory_free(
		 buffer );
	}
	return( -1 );
}

/* Reads a buffer
 * Returns the number of bytes read or -1 on error
 */
ssize_t libodraw_handle_read_buffer(
         libodraw_handle_t *handle,
         void *buffer,
         size_t buffer_size,
         libcerror_error_t **error )
{
	libodraw_internal_handle_t *internal_handle = NULL;
	libodraw_sector_range_t *sector_range       = NULL;
	libodraw_track_value_t *track_value         = NULL;
	static char *function                       = "libodraw_handle_read_buffer";
	size_t buffer_offset                        = 0;
	ssize_t read_count                          = 0;
	uint64_t current_sector                     = 0;
	int in_known_range                          = 0;
	int number_of_lead_outs                     = 0;
	int number_of_run_outs                      = 0;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libodraw_internal_handle_t *) handle;

	if( internal_handle->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing IO handle.",
		 function );

		return( -1 );
	}
	if( internal_handle->io_handle->bytes_per_sector == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - invalid IO handle - missing bytes per sector.",
		 function );

		return( -1 );
	}
	if( internal_handle->current_offset < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid handle - invalid IO handle - current offset value out of bounds.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_number_of_entries(
	     internal_handle->run_outs_array,
	     &number_of_run_outs,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of elements in run-outs array.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_number_of_entries(
	     internal_handle->lead_outs_array,
	     &number_of_lead_outs,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of elements in lead-outs array.",
		 function );

		return( -1 );
	}
	if( (size64_t) internal_handle->current_offset >= internal_handle->media_size )
	{
		return( 0 );
	}
	current_sector = (uint64_t) ( internal_handle->current_offset / internal_handle->io_handle->bytes_per_sector );

	if( current_sector > (uint64_t) UINT32_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: current sector value out of bounds.",
		 function );

		return( -1 );
	}
	while( buffer_offset < buffer_size )
	{
		in_known_range = 0;

		if( libcdata_array_get_entry_by_index(
		     internal_handle->tracks_array,
		     internal_handle->current_track,
		     (intptr_t **) &track_value,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve track value: %d from array.",
			 function,
			 internal_handle->current_track );

			return( -1 );
		}
		if( track_value == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing track value: %d.",
			 function,
			 internal_handle->current_track );

			return( -1 );
		}
		/* TODO currently assumes that current track start sector is always relative to the start of the media */
		if( ( current_sector >= track_value->start_sector )
		 && ( current_sector < track_value->end_sector ) )
		{
			in_known_range = 1;

			read_count = libodraw_handle_read_buffer_from_track(
			              internal_handle,
			              (uint8_t *) &( ( (uint8_t *) buffer )[ buffer_offset ] ),
			              buffer_size - buffer_offset,
			              error );

			if( read_count == -1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_READ_FAILED,
				 "%s: unable to read buffer from track: %d.",
				 function,
				 internal_handle->current_track );

				return( -1 );
			}
			buffer_offset += read_count;

			internal_handle->current_offset += (off64_t) read_count;

			current_sector = (uint64_t) ( internal_handle->current_offset / internal_handle->io_handle->bytes_per_sector );

			if( current_sector > (uint64_t) UINT32_MAX )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: current sector value out of bounds.",
				 function );

				return( -1 );
			}
			if( current_sector >= track_value->end_sector )
			{
				internal_handle->current_track += 1;
			}
		}
		if( buffer_offset >= buffer_size )
		{
			break;
		}
		if( (size64_t) internal_handle->current_offset >= internal_handle->media_size )
		{
			break;
		}
		if( internal_handle->current_run_out < number_of_run_outs )
		{
			if( libcdata_array_get_entry_by_index(
			     internal_handle->run_outs_array,
			     internal_handle->current_run_out,
			     (intptr_t **) &sector_range,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve run-out sector range: %d from array.",
				 function,
				 internal_handle->current_run_out );

				return( -1 );
			}
			if( sector_range == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
				 "%s: missing run-out sector range: %d.",
				 function,
				 internal_handle->current_run_out );

				return( -1 );
			}
			/* TODO currently assumes that current run-out start sector is always relative to the start of the media */
			if( ( current_sector >= sector_range->start_sector )
			 && ( current_sector < sector_range->end_sector ) )
			{
				in_known_range = 1;

				read_count = libodraw_handle_read_buffer_from_run_out(
					      internal_handle,
					      (uint8_t *) &( ( (uint8_t *) buffer )[ buffer_offset ] ),
					      buffer_size - buffer_offset,
					      error );

				if( read_count == -1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_IO,
					 LIBCERROR_IO_ERROR_READ_FAILED,
					 "%s: unable to read buffer from run-out: %d.",
					 function,
					 internal_handle->current_run_out );

					return( -1 );
				}
				buffer_offset += read_count;

				internal_handle->current_offset += (off64_t) read_count;

				current_sector = (uint64_t) ( internal_handle->current_offset / internal_handle->io_handle->bytes_per_sector );

				if( current_sector > (uint64_t) UINT32_MAX )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
					 "%s: current sector value out of bounds.",
					 function );

					return( -1 );
				}
				if( current_sector >= sector_range->end_sector )
				{
					internal_handle->current_run_out += 1;
				}
			}
			if( buffer_offset >= buffer_size )
			{
				break;
			}
			if( (size64_t) internal_handle->current_offset >= internal_handle->media_size )
			{
				break;
			}
		}
		if( internal_handle->current_lead_out < number_of_lead_outs )
		{
			if( libcdata_array_get_entry_by_index(
			     internal_handle->lead_outs_array,
			     internal_handle->current_lead_out,
			     (intptr_t **) &sector_range,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve lead-out sector range: %d from array.",
				 function,
				 internal_handle->current_lead_out );

				return( -1 );
			}
			if( sector_range == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
				 "%s: missing lead-out sector range: %d.",
				 function,
				 internal_handle->current_lead_out );

				return( -1 );
			}
			/* TODO currently assumes that current lead-out start sector is always relative to the start of the media */
			if( ( current_sector >= sector_range->start_sector )
			 && ( current_sector < sector_range->end_sector ) )
			{
				in_known_range = 1;

				read_count = libodraw_handle_read_buffer_from_lead_out(
					      internal_handle,
					      (uint8_t *) &( ( (uint8_t *) buffer )[ buffer_offset ] ),
					      buffer_size - buffer_offset,
					      error );

				if( read_count == -1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_IO,
					 LIBCERROR_IO_ERROR_READ_FAILED,
					 "%s: unable to read buffer from lead-out: %d.",
					 function,
					 internal_handle->current_lead_out );

					return( -1 );
				}
				buffer_offset += read_count;

				internal_handle->current_offset += (off64_t) read_count;

				current_sector = (uint64_t) ( internal_handle->current_offset / internal_handle->io_handle->bytes_per_sector );

				if( current_sector > (uint64_t) UINT32_MAX )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
					 "%s: current sector value out of bounds.",
					 function );

					return( -1 );
				}
				if( current_sector >= sector_range->end_sector )
				{
					internal_handle->current_lead_out += 1;
				}
			}
			if( buffer_offset >= buffer_size )
			{
				break;
			}
			if( (size64_t) internal_handle->current_offset >= internal_handle->media_size )
			{
				break;
			}
		}
		if( in_known_range == 0 )
		{
			read_count = libodraw_handle_read_buffer_from_unspecified_sector(
			              internal_handle,
			              (uint8_t *) &( ( (uint8_t *) buffer )[ buffer_offset ] ),
			              buffer_size - buffer_offset,
			              error );

			if( read_count == -1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_READ_FAILED,
				 "%s: unable to read buffer from unspecified.",
				 function );

				return( -1 );
			}
			buffer_offset += read_count;

			internal_handle->current_offset += (off64_t) read_count;

			current_sector = (uint64_t) ( internal_handle->current_offset / internal_handle->io_handle->bytes_per_sector );

			if( current_sector > (uint64_t) UINT32_MAX )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: current sector value out of bounds.",
				 function );

				return( -1 );
			}
			if( current_sector >= track_value->end_sector )
			{
				internal_handle->current_track += 1;
			}
			if( buffer_offset >= buffer_size )
			{
				break;
			}
			if( (size64_t) internal_handle->current_offset >= internal_handle->media_size )
			{
				break;
			}
		}
		if( internal_handle->io_handle->abort != 0 )
		{
			break;
		}
	}
	return( (size_t) buffer_offset );
}

/* Reads a buffer from run-out
 * Returns the number of bytes read or -1 on error
 */
ssize_t libodraw_handle_read_buffer_from_run_out(
         libodraw_internal_handle_t *internal_handle,
         uint8_t *buffer,
         size_t buffer_size,
         libcerror_error_t **error )
{
	libodraw_track_value_t *track_value   = NULL;
	libodraw_sector_range_t *sector_range = NULL;
	uint8_t *read_buffer                  = NULL;
	uint8_t *sector_data                  = NULL;
	static char *function                 = "libodraw_handle_read_buffer_from_run_out";
	off64_t current_sector_offset         = 0;
	off64_t run_out_data_offset           = 0;
	size64_t data_file_number_of_sectors  = 0;
	size64_t data_file_size               = 0;
	size64_t required_number_of_sectors   = 0;
	uint64_t current_sector               = 0;
	uint64_t run_out_data_start_sector    = 0;
	size_t read_number_of_sectors         = 0;
	size_t read_size                      = 0;
	ssize_t read_count                    = 0;

	if( internal_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	if( internal_handle->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing IO handle.",
		 function );

		return( -1 );
	}
	if( internal_handle->io_handle->bytes_per_sector == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - invalid IO handle - missing bytes per sector.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_entry_by_index(
	     internal_handle->run_outs_array,
	     internal_handle->current_run_out,
	     (intptr_t **) &sector_range,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve run-out sector range: %d from array.",
		 function,
		 internal_handle->current_run_out );

		goto on_error;
	}
	if( sector_range == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: missing run-out sector range: %d.",
		 function,
		 internal_handle->current_run_out );

		goto on_error;
	}
	current_sector = (uint64_t) ( internal_handle->current_offset / internal_handle->io_handle->bytes_per_sector );

	if( current_sector > (uint64_t) UINT32_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: current sector value out of bounds.",
		 function );

		return( -1 );
	}
	/* TODO currently assumes that current run-out start sector is always relative to the start of the media */
	if( ( current_sector < sector_range->start_sector )
	 || ( current_sector >= sector_range->end_sector ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: current sector value out of bounds.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading data from run-out: %d at sector(s): %" PRIu64 " - %" PRIu64 "\n",
		 function,
		 internal_handle->current_run_out,
		 sector_range->start_sector,
		 sector_range->end_sector );
	}
#endif
	/* Retrieves the track that corresponds to the run-out
	 */
	if( libcdata_array_get_entry_by_index(
	     internal_handle->tracks_array,
	     internal_handle->current_track - 1,
	     (intptr_t **) &track_value,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve track value: %d from array.",
		 function,
		 internal_handle->current_track - 1 );

		goto on_error;
	}
	if( track_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: missing track value: %d.",
		 function,
		 internal_handle->current_track - 1 );

		goto on_error;
	}
	if( track_value->end_sector != sector_range->start_sector )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: sector range start sector value out of bounds.",
		 function );

		goto on_error;
	}
	current_sector_offset = internal_handle->current_offset
	                      - (off64_t) ( current_sector * internal_handle->io_handle->bytes_per_sector );

	if( ( current_sector_offset < 0 )
	 || ( current_sector_offset >= internal_handle->io_handle->bytes_per_sector ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid current sector offset value out of bounds.",
		 function );

		goto on_error;
	}
	read_number_of_sectors = buffer_size / internal_handle->io_handle->bytes_per_sector;

	if( ( buffer_size % internal_handle->io_handle->bytes_per_sector ) != 0 )
	{
		read_number_of_sectors += 1;
	}
	if( ( (uint64_t) read_number_of_sectors + current_sector ) > sector_range->end_sector )
	{
		read_number_of_sectors = (size_t) ( sector_range->end_sector - current_sector );
	}
	if( libbfio_pool_get_size(
	     internal_handle->data_file_io_pool,
	     track_value->data_file_index,
	     &data_file_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve data file: %d size.",
		 function,
		 track_value->data_file_index );

		goto on_error;
	}
	data_file_number_of_sectors = data_file_size / track_value->bytes_per_sector;

	/* Determine if the required number of sectors are available in the data file
	 */
	required_number_of_sectors = track_value->data_file_start_sector
	                           + track_value->number_of_sectors
	                           + sector_range->number_of_sectors;

	if( required_number_of_sectors > data_file_number_of_sectors )
	{
		read_size = ( read_number_of_sectors * internal_handle->io_handle->bytes_per_sector )
		          - (size_t) current_sector_offset;

		if( read_size > buffer_size )
		{
			read_size = buffer_size;
		}
		/* Fill the buffer with 0 byte values if the run-out data is
		 * not available in the data file
		 */
		if( memory_set(
		     buffer,
		     0,
		     read_size ) == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
			 "%s: unable to copy run-out data to buffer.",
			 function );

			goto on_error;
		}
		read_count = (ssize_t) read_size;
	}
	else
	{
		run_out_data_start_sector = current_sector
		                          - sector_range->start_sector
		                          + track_value->number_of_sectors;

		run_out_data_offset = track_value->data_file_offset
		                    + ( run_out_data_start_sector * track_value->bytes_per_sector );

		read_size = read_number_of_sectors * track_value->bytes_per_sector;

		if( track_value->bytes_per_sector != internal_handle->io_handle->bytes_per_sector )
		{
/* TODO use sector data cache ? */
			sector_data = (uint8_t *) memory_allocate(
			                           sizeof( uint8_t ) * read_size );

			if( sector_data == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
				 "%s: unable to create sector data.",
				 function );

				goto on_error;
			}
			read_buffer = sector_data;
		}
		else
		{
			read_buffer          = buffer;
			read_size           -= (size_t) current_sector_offset;
			run_out_data_offset += current_sector_offset;

			if( read_size > buffer_size )
			{
				read_size = buffer_size;
			}
		}
		if( libbfio_pool_seek_offset(
		     internal_handle->data_file_io_pool,
		     track_value->data_file_index,
		     run_out_data_offset,
		     SEEK_SET,
		     error ) == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_SEEK_FAILED,
			 "%s: unable to seek data file: %d offset: %" PRIi64 ".",
			 function,
			 track_value->data_file_index,
			 run_out_data_offset );

			goto on_error;
		}
		read_count = libbfio_pool_read_buffer(
			      internal_handle->data_file_io_pool,
			      track_value->data_file_index,
			      read_buffer,
			      read_size,
			      error );

		if( read_count != (ssize_t) read_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read buffer from data file: %d.",
			 function,
			 track_value->data_file_index );

			goto on_error;
		}
		if( track_value->bytes_per_sector != internal_handle->io_handle->bytes_per_sector )
		{
			read_count = libodraw_io_handle_copy_sector_data_to_buffer(
				      internal_handle->io_handle,
				      sector_data,
				      read_size,
			              track_value->bytes_per_sector,
				      LIBODRAW_TRACK_TYPE_UNKNOWN,
				      buffer,
				      buffer_size,
				      (uint32_t) current_sector,
				      (uint32_t) current_sector_offset,
				      error );

			if( read_count < 0 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
				 "%s: unable to copy sector data to buffer.",
				 function );

				goto on_error;
			}
			memory_free(
			 sector_data );

			sector_data = NULL;
		}
	}
	return( read_count );

on_error:
	if( sector_data != NULL )
	{
		memory_free(
		 sector_data );
	}
	return( -1 );
}

/* Reads a buffer from lead-out
 * Returns the number of bytes read or -1 on error
 */
ssize_t libodraw_handle_read_buffer_from_lead_out(
         libodraw_internal_handle_t *internal_handle,
         uint8_t *buffer,
         size_t buffer_size,
         libcerror_error_t **error )
{
	libodraw_track_value_t *track_value   = NULL;
	libodraw_sector_range_t *sector_range = NULL;
	uint8_t *read_buffer                  = NULL;
	uint8_t *sector_data                  = NULL;
	static char *function                 = "libodraw_handle_read_buffer_from_lead_out";
	off64_t current_sector_offset         = 0;
	off64_t lead_out_data_offset          = 0;
	size64_t data_file_number_of_sectors  = 0;
	size64_t data_file_size               = 0;
	size64_t required_number_of_sectors   = 0;
	uint64_t current_sector               = 0;
	uint64_t lead_out_data_start_sector   = 0;
	size_t read_number_of_sectors         = 0;
	size_t read_size                      = 0;
	ssize_t read_count                    = 0;

	if( internal_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	if( internal_handle->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing IO handle.",
		 function );

		return( -1 );
	}
	if( internal_handle->io_handle->bytes_per_sector == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - invalid IO handle - missing bytes per sector.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_entry_by_index(
	     internal_handle->lead_outs_array,
	     internal_handle->current_lead_out,
	     (intptr_t **) &sector_range,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve lead-out sector range: %d from array.",
		 function,
		 internal_handle->current_lead_out );

		goto on_error;
	}
	if( sector_range == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: missing lead-out sector range: %d.",
		 function,
		 internal_handle->current_lead_out );

		goto on_error;
	}
	current_sector = (uint64_t) ( internal_handle->current_offset / internal_handle->io_handle->bytes_per_sector );

	if( current_sector > (uint64_t) UINT32_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: current sector value out of bounds.",
		 function );

		return( -1 );
	}
	/* TODO currently assumes that current lead-out start sector is always relative to the start of the media */
	if( ( current_sector < sector_range->start_sector )
	 || ( current_sector >= sector_range->end_sector ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: current sector value out of bounds.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading data from lead-out: %d at sector(s): %" PRIu64 " - %" PRIu64 "\n",
		 function,
		 internal_handle->current_lead_out,
		 sector_range->start_sector,
		 sector_range->end_sector );
	}
#endif
	/* Retrieves the track that corresponds to the lead-out
	 */
	if( libcdata_array_get_entry_by_index(
	     internal_handle->tracks_array,
	     internal_handle->current_track - 1,
	     (intptr_t **) &track_value,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve track value: %d from array.",
		 function,
		 internal_handle->current_track - 1 );

		goto on_error;
	}
	if( track_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: missing track value: %d.",
		 function,
		 internal_handle->current_track - 1 );

		goto on_error;
	}
	if( track_value->end_sector != sector_range->start_sector )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: sector range start sector value out of bounds.",
		 function );

		goto on_error;
	}
	current_sector_offset = internal_handle->current_offset
	                      - (off64_t) ( current_sector * internal_handle->io_handle->bytes_per_sector );

	if( ( current_sector_offset < 0 )
	 || ( current_sector_offset >= internal_handle->io_handle->bytes_per_sector ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid current sector offset value out of bounds.",
		 function );

		goto on_error;
	}
	read_number_of_sectors = buffer_size / internal_handle->io_handle->bytes_per_sector;

	if( ( buffer_size % internal_handle->io_handle->bytes_per_sector ) != 0 )
	{
		read_number_of_sectors += 1;
	}
	if( ( (uint64_t) read_number_of_sectors + current_sector ) > sector_range->end_sector )
	{
		read_number_of_sectors = (size_t) ( sector_range->end_sector - current_sector );
	}
	if( libbfio_pool_get_size(
	     internal_handle->data_file_io_pool,
	     track_value->data_file_index,
	     &data_file_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve data file: %d size.",
		 function,
		 track_value->data_file_index );

		goto on_error;
	}
	data_file_number_of_sectors = data_file_size / track_value->bytes_per_sector;

	/* Determine if the required number of sectors are available in the data file
	 */
	required_number_of_sectors = track_value->data_file_start_sector
	                           + track_value->number_of_sectors
	                           + sector_range->number_of_sectors;

	if( required_number_of_sectors > data_file_number_of_sectors )
	{
		read_size = ( read_number_of_sectors * internal_handle->io_handle->bytes_per_sector )
		          - (size_t) current_sector_offset;

		if( read_size > buffer_size )
		{
			read_size = buffer_size;
		}
		/* Fill the buffer with 0 byte values if the lead-out data is
		 * not available in the data file
		 */
		if( memory_set(
		     buffer,
		     0,
		     read_size ) == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
			 "%s: unable to copy lead-out data to buffer.",
			 function );

			goto on_error;
		}
		read_count = (ssize_t) read_size;
	}
	else
	{
		lead_out_data_start_sector = current_sector
		                           - sector_range->start_sector
		                           + track_value->number_of_sectors;

		lead_out_data_offset = track_value->data_file_offset
		                     + ( lead_out_data_start_sector * track_value->bytes_per_sector );

		read_size = read_number_of_sectors * track_value->bytes_per_sector;

		if( track_value->bytes_per_sector != internal_handle->io_handle->bytes_per_sector )
		{
/* TODO use sector data cache ? */
			sector_data = (uint8_t *) memory_allocate(
			                           sizeof( uint8_t ) * read_size );

			if( sector_data == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
				 "%s: unable to create sector data.",
				 function );

				goto on_error;
			}
			read_buffer = sector_data;
		}
		else
		{
			read_buffer           = buffer;
			read_size            -= (size_t) current_sector_offset;
			lead_out_data_offset += current_sector_offset;

			if( read_size > buffer_size )
			{
				read_size = buffer_size;
			}
		}
		if( libbfio_pool_seek_offset(
		     internal_handle->data_file_io_pool,
		     track_value->data_file_index,
		     lead_out_data_offset,
		     SEEK_SET,
		     error ) == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_SEEK_FAILED,
			 "%s: unable to seek data file: %d offset: %" PRIi64 ".",
			 function,
			 track_value->data_file_index,
			 lead_out_data_offset );

			goto on_error;
		}
		read_count = libbfio_pool_read_buffer(
			      internal_handle->data_file_io_pool,
			      track_value->data_file_index,
			      read_buffer,
			      read_size,
			      error );

		if( read_count != (ssize_t) read_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read buffer from data file: %d.",
			 function,
			 track_value->data_file_index );

			goto on_error;
		}
		if( track_value->bytes_per_sector != internal_handle->io_handle->bytes_per_sector )
		{
			read_count = libodraw_io_handle_copy_sector_data_to_buffer(
				      internal_handle->io_handle,
				      sector_data,
				      read_size,
			              track_value->bytes_per_sector,
				      LIBODRAW_TRACK_TYPE_UNKNOWN,
				      buffer,
				      buffer_size,
				      (uint32_t) current_sector,
				      (uint32_t) current_sector_offset,
				      error );

			if( read_count < 0 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
				 "%s: unable to copy sector data to buffer.",
				 function );

				goto on_error;
			}
			memory_free(
			 sector_data );

			sector_data = NULL;
		}
	}
	return( read_count );

on_error:
	if( sector_data != NULL )
	{
		memory_free(
		 sector_data );
	}
	return( -1 );
}

/* Reads a buffer from a sector in an unspecified range
 * Returns the number of bytes read or -1 on error
 */
ssize_t libodraw_handle_read_buffer_from_unspecified_sector(
         libodraw_internal_handle_t *internal_handle,
         uint8_t *buffer,
         size_t buffer_size,
         libcerror_error_t **error )
{
	libodraw_track_value_t *track_value    = NULL;
	uint8_t *read_buffer                   = NULL;
	uint8_t *sector_data                   = NULL;
	static char *function                  = "libodraw_handle_read_buffer_from_unspecified_sector";
	off64_t current_sector_offset          = 0;
	off64_t unspecified_data_offset        = 0;
	size64_t data_file_number_of_sectors   = 0;
	size64_t data_file_size                = 0;
	size64_t required_number_of_sectors    = 0;
	uint64_t current_sector                = 0;
	uint64_t unspecified_data_start_sector = 0;
	size_t read_size                       = 0;
	ssize_t read_count                     = 0;

	if( internal_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	if( internal_handle->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing IO handle.",
		 function );

		return( -1 );
	}
	if( internal_handle->io_handle->bytes_per_sector == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - invalid IO handle - missing bytes per sector.",
		 function );

		return( -1 );
	}
	current_sector = (uint64_t) ( internal_handle->current_offset / internal_handle->io_handle->bytes_per_sector );

	if( current_sector > (uint64_t) UINT32_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: current sector value out of bounds.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading data from unspecified range.\n",
		 function );
	}
#endif
	/* Retrieves the track that corresponds to the unspecified range
	 */
	if( libcdata_array_get_entry_by_index(
	     internal_handle->tracks_array,
	     internal_handle->current_track - 1,
	     (intptr_t **) &track_value,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve track value: %d from array.",
		 function,
		 internal_handle->current_track - 1 );

		goto on_error;
	}
	if( track_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: missing track value: %d.",
		 function,
		 internal_handle->current_track - 1 );

		goto on_error;
	}
	current_sector_offset = internal_handle->current_offset
	                      - (off64_t) ( current_sector * internal_handle->io_handle->bytes_per_sector );

	if( ( current_sector_offset < 0 )
	 || ( current_sector_offset >= internal_handle->io_handle->bytes_per_sector ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid current sector offset value out of bounds.",
		 function );

		goto on_error;
	}
	if( libbfio_pool_get_size(
	     internal_handle->data_file_io_pool,
	     track_value->data_file_index,
	     &data_file_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve data file: %d size.",
		 function,
		 track_value->data_file_index );

		goto on_error;
	}
	data_file_number_of_sectors = data_file_size / track_value->bytes_per_sector;

	unspecified_data_start_sector = current_sector
	                              - track_value->end_sector;

	/* Determine if the required number of sectors are available in the data file
	 */
	required_number_of_sectors = track_value->data_file_start_sector
	                           + track_value->number_of_sectors
	                           + unspecified_data_start_sector
	                           + 1;

	if( required_number_of_sectors > data_file_number_of_sectors )
	{
		read_size = internal_handle->io_handle->bytes_per_sector
		          - (size_t) current_sector_offset;

		if( read_size > buffer_size )
		{
			read_size = buffer_size;
		}
		/* Fill the buffer with 0 byte values if the unspecified data is
		 * not available in the data file
		 */
		if( memory_set(
		     buffer,
		     0,
		     read_size ) == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
			 "%s: unable to copy unspecified data to buffer.",
			 function );

			goto on_error;
		}
		read_count = (ssize_t) read_size;
	}
	else
	{
		unspecified_data_offset = track_value->data_file_offset
		                        + ( unspecified_data_start_sector * track_value->bytes_per_sector );

		read_size = track_value->bytes_per_sector;

		if( track_value->bytes_per_sector != internal_handle->io_handle->bytes_per_sector )
		{
/* TODO use sector data cache ? */
			sector_data = (uint8_t *) memory_allocate(
			                           sizeof( uint8_t ) * read_size );

			if( sector_data == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
				 "%s: unable to create sector data.",
				 function );

				goto on_error;
			}
			read_buffer = sector_data;
		}
		else
		{
			read_buffer              = buffer;
			read_size               -= (size_t) current_sector_offset;
			unspecified_data_offset += current_sector_offset;

			if( read_size > buffer_size )
			{
				read_size = buffer_size;
			}
		}
		if( libbfio_pool_seek_offset(
		     internal_handle->data_file_io_pool,
		     track_value->data_file_index,
		     unspecified_data_offset,
		     SEEK_SET,
		     error ) == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_SEEK_FAILED,
			 "%s: unable to seek data file: %d offset: %" PRIi64 ".",
			 function,
			 track_value->data_file_index,
			 unspecified_data_offset );

			goto on_error;
		}
		read_count = libbfio_pool_read_buffer(
			      internal_handle->data_file_io_pool,
			      track_value->data_file_index,
			      read_buffer,
			      read_size,
			      error );

		if( read_count != (ssize_t) read_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read buffer from data file: %d.",
			 function,
			 track_value->data_file_index );

			goto on_error;
		}
		if( track_value->bytes_per_sector != internal_handle->io_handle->bytes_per_sector )
		{
			read_count = libodraw_io_handle_copy_sector_data_to_buffer(
				      internal_handle->io_handle,
				      sector_data,
				      read_size,
			              track_value->bytes_per_sector,
				      LIBODRAW_TRACK_TYPE_UNKNOWN,
				      buffer,
				      buffer_size,
				      (uint32_t) current_sector,
				      (uint32_t) current_sector_offset,
				      error );

			if( read_count < 0 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
				 "%s: unable to copy sector data to buffer.",
				 function );

				goto on_error;
			}
			memory_free(
			 sector_data );

			sector_data = NULL;
		}
	}
	return( read_count );

on_error:
	if( sector_data != NULL )
	{
		memory_free(
		 sector_data );
	}
	return( -1 );
}

/* Reads a buffer from track
 * Returns the number of bytes read or -1 on error
 */
ssize_t libodraw_handle_read_buffer_from_track(
         libodraw_internal_handle_t *internal_handle,
         uint8_t *buffer,
         size_t buffer_size,
         libcerror_error_t **error )
{
	libodraw_track_value_t *track_value = NULL;
	uint8_t *read_buffer                = NULL;
	uint8_t *sector_data                = NULL;
	static char *function               = "libodraw_handle_read_buffer_from_track";
	off64_t current_sector_offset       = 0;
	off64_t track_data_offset           = 0;
	uint64_t current_sector             = 0;
	uint64_t track_data_start_sector    = 0;
	size_t read_number_of_sectors       = 0;
	size_t read_size                    = 0;
	ssize_t read_count                  = 0;

	if( internal_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	if( internal_handle->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing IO handle.",
		 function );

		return( -1 );
	}
	if( internal_handle->io_handle->bytes_per_sector == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - invalid IO handle - missing bytes per sector.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_entry_by_index(
	     internal_handle->tracks_array,
	     internal_handle->current_track,
	     (intptr_t **) &track_value,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve track value: %d from array.",
		 function,
		 internal_handle->current_track );

		goto on_error;
	}
	if( track_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: missing track value: %d.",
		 function,
		 internal_handle->current_track );

		goto on_error;
	}
	current_sector = (uint64_t) ( internal_handle->current_offset / internal_handle->io_handle->bytes_per_sector );

	if( current_sector > (uint64_t) UINT32_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: current sector value out of bounds.",
		 function );

		return( -1 );
	}
	/* TODO currently assumes that current track start sector is always relative to the start of the media */
	if( ( current_sector < track_value->start_sector )
	 || ( current_sector >= track_value->end_sector ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: current sector value out of bounds.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading data from track: %d at sector(s): %" PRIu64 " - %" PRIu64 "\n",
		 function,
		 internal_handle->current_track,
		 track_value->start_sector,
		 track_value->end_sector );
	}
#endif
	current_sector_offset = internal_handle->current_offset
	                      - (off64_t) ( current_sector * internal_handle->io_handle->bytes_per_sector );

	if( ( current_sector_offset < 0 )
	 || ( current_sector_offset >= internal_handle->io_handle->bytes_per_sector ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid current sector offset value out of bounds.",
		 function );

		goto on_error;
	}
	track_data_start_sector = current_sector - track_value->start_sector;

	track_data_offset = track_value->data_file_offset
	                  + ( track_data_start_sector * track_value->bytes_per_sector );

	read_number_of_sectors = buffer_size / internal_handle->io_handle->bytes_per_sector;

	if( ( buffer_size % internal_handle->io_handle->bytes_per_sector ) != 0 )
	{
		read_number_of_sectors += 1;
	}
	if( ( (uint64_t) read_number_of_sectors + current_sector ) > track_value->end_sector )
	{
		read_number_of_sectors = (size_t) ( track_value->end_sector - current_sector );
	}
	read_size = read_number_of_sectors * track_value->bytes_per_sector;

	if( track_value->bytes_per_sector != internal_handle->io_handle->bytes_per_sector )
	{
/* TODO handle more track types */
		if( ( track_value->type != LIBODRAW_TRACK_TYPE_AUDIO )
		 && ( track_value->type != LIBODRAW_TRACK_TYPE_MODE1_2048 )
		 && ( track_value->type != LIBODRAW_TRACK_TYPE_MODE1_2352 )
		 && ( track_value->type != LIBODRAW_TRACK_TYPE_MODE2_2048 )
		 && ( track_value->type != LIBODRAW_TRACK_TYPE_MODE2_2336 )
		 && ( track_value->type != LIBODRAW_TRACK_TYPE_MODE2_2352 ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported track type.",
			 function );

			goto on_error;
		}
/* TODO use sector data cache ? */
		sector_data = (uint8_t *) memory_allocate(
		                           sizeof( uint8_t ) * read_size );

		if( sector_data == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create sector data.",
			 function );

			goto on_error;
		}
		read_buffer = sector_data;
	}
	else
	{
		read_buffer        = buffer;
		read_size         -= (size_t) current_sector_offset;
		track_data_offset += current_sector_offset;

		if( read_size > buffer_size )
		{
			read_size = buffer_size;
		}
	}
	if( libbfio_pool_seek_offset(
	     internal_handle->data_file_io_pool,
	     track_value->data_file_index,
	     track_data_offset,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek data file: %d offset: %" PRIi64 ".",
		 function,
		 track_value->data_file_index,
		 track_data_offset );

		goto on_error;
	}
	read_count = libbfio_pool_read_buffer(
		      internal_handle->data_file_io_pool,
		      track_value->data_file_index,
		      read_buffer,
		      read_size,
		      error );

	if( read_count != (ssize_t) read_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read buffer from data file: %d.",
		 function,
		 track_value->data_file_index );

		goto on_error;
	}
	if( track_value->bytes_per_sector != internal_handle->io_handle->bytes_per_sector )
	{
		read_count = libodraw_io_handle_copy_sector_data_to_buffer(
		              internal_handle->io_handle,
		              sector_data,
		              read_size,
		              track_value->bytes_per_sector,
		              track_value->type,
		              buffer,
		              buffer_size,
			      (uint32_t) current_sector,
		              (uint32_t) current_sector_offset,
		              error );

		if( read_count < 0 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy sector data to buffer.",
			 function );

			goto on_error;
		}
		memory_free(
		 sector_data );

		sector_data = NULL;
	}
	return( read_count );

on_error:
	if( sector_data != NULL )
	{
		memory_free(
		 sector_data );
	}
	return( -1 );
}

/* Reads (media) data at a specific offset
 * Returns the number of bytes read or -1 on error
 */
ssize_t libodraw_handle_read_buffer_at_offset(
         libodraw_handle_t *handle,
         void *buffer,
         size_t buffer_size,
         off64_t offset,
         libcerror_error_t **error )
{
	static char *function = "libodraw_handle_read_buffer_at_offset";
	ssize_t read_count    = 0;

	if( libodraw_handle_seek_offset(
	     handle,
	     offset,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek offset.",
		 function );

		return( -1 );
	}
	read_count = libodraw_handle_read_buffer(
	              handle,
	              buffer,
	              buffer_size,
	              error );

	if( read_count <= -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read buffer.",
		 function );

		return( -1 );
	}
	return( read_count );
}

/* Seeks a certain offset of the (media) data
 * This function is not multi-thread safe acquire write lock before call
 * Returns the offset if seek is successful or -1 on error
 */
off64_t libodraw_internal_handle_seek_offset(
         libodraw_internal_handle_t *internal_handle,
         off64_t offset,
         int whence,
         libcerror_error_t **error )
{
	libodraw_sector_range_t *lead_out_sector_range = NULL;
	libodraw_sector_range_t *run_out_sector_range  = NULL;
	libodraw_track_value_t *track_value            = NULL;
	static char *function                          = "libodraw_internal_handle_seek_offset";
	off64_t lead_out_offset                        = 0;
	off64_t run_out_offset                         = 0;
	off64_t track_offset                           = 0;
	int current_lead_out                           = 0;
	int current_run_out                            = 0;
	int current_track                              = 0;

	if( internal_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	if( internal_handle->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing IO handle.",
		 function );

		return( -1 );
	}
	if( ( whence != SEEK_CUR )
	 && ( whence != SEEK_END )
	 && ( whence != SEEK_SET ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported whence.",
		 function );

		return( -1 );
	}
	if( whence == SEEK_CUR )
	{
		offset += internal_handle->current_offset;
	}
	else if( whence == SEEK_END )
	{
		offset += (off64_t) internal_handle->media_size;
	}
	if( offset < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid offset value out of bounds.",
		 function );

		return( -1 );
	}
	if( offset < (off64_t) internal_handle->media_size )
	{
		if( libodraw_handle_get_run_out_at_offset(
		     internal_handle,
		     offset,
		     &current_run_out,
		     &run_out_sector_range,
		     &run_out_offset,
		     error ) == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve run-out at offset: %" PRIi64 ".",
			 function,
			 offset );

			return( -1 );
		}
		if( libodraw_handle_get_lead_out_at_offset(
		     internal_handle,
		     offset,
		     &current_lead_out,
		     &lead_out_sector_range,
		     &lead_out_offset,
		     error ) == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve lead-out at offset: %" PRIi64 ".",
			 function,
			 offset );

			return( -1 );
		}
		if( libodraw_handle_get_track_at_offset(
		     internal_handle,
		     offset,
		     &current_track,
		     &track_value,
		     &track_offset,
		     error ) == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve track at offset: %" PRIi64 ".",
			 function,
			 offset );

			return( -1 );
		}
	}
	else
	{
		if( libcdata_array_get_number_of_entries(
		     internal_handle->run_outs_array,
		     &current_run_out,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve number of elements in run-outs array.",
			 function );

			return( -1 );
		}
		if( libcdata_array_get_number_of_entries(
		     internal_handle->lead_outs_array,
		     &current_lead_out,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve number of elements in lead-outs array.",
			 function );

			return( -1 );
		}
		if( libcdata_array_get_number_of_entries(
		     internal_handle->tracks_array,
		     &current_track,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve number of elements in tracks array.",
			 function );

			return( -1 );
		}
	}
	internal_handle->current_offset   = offset;
	internal_handle->current_run_out  = current_run_out;
	internal_handle->current_lead_out = current_lead_out;
	internal_handle->current_track    = current_track;

	return( offset );
}

/* Seeks a certain offset of the (media) data
 * Returns the offset if seek is successful or -1 on error
 */
off64_t libodraw_handle_seek_offset(
         libodraw_handle_t *handle,
         off64_t offset,
         int whence,
         libcerror_error_t **error )
{
	libodraw_internal_handle_t *internal_handle = NULL;
	static char *function                       = "libodraw_handle_seek_offset";

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libodraw_internal_handle_t *) handle;

	if( internal_handle->data_file_io_pool == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing data file IO pool.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LIBODRAW_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	offset = libodraw_internal_handle_seek_offset(
	          internal_handle,
	          offset,
	          whence,
	          error );

	if( offset == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek offset.",
		 function );

		offset = -1;
	}
#if defined( HAVE_LIBODRAW_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	return( offset );
}

/* Retrieves a run-out sector range for the specified offset
 * When no matching run-out was found the run_out_index value contains the next run-out index on return
 * Returns 1 if successful, 0 if no matching run-out was found or -1 on error
 */
int libodraw_handle_get_run_out_at_offset(
     libodraw_internal_handle_t *internal_handle,
     off64_t offset,
     int *run_out_index,
     libodraw_sector_range_t **run_out_sector_range,
     off64_t *run_out_offset,
     libcerror_error_t **error )
{
	static char *function   = "libodraw_handle_get_run_out_at_offset";
	uint64_t current_sector = 0;
	int number_of_run_outs  = 0;

	if( internal_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	if( internal_handle->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing IO handle.",
		 function );

		return( -1 );
	}
	if( internal_handle->io_handle->bytes_per_sector == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - invalid IO handle - missing bytes per sector.",
		 function );

		return( -1 );
	}
	if( run_out_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid run-out index.",
		 function );

		return( -1 );
	}
	if( run_out_sector_range == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid run-out sector range.",
		 function );

		return( -1 );
	}
	if( run_out_offset == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid run-out offset.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_number_of_entries(
	     internal_handle->run_outs_array,
	     &number_of_run_outs,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of elements in run-outs array.",
		 function );

		return( -1 );
	}
	current_sector = offset / internal_handle->io_handle->bytes_per_sector;

	if( current_sector > (uint64_t) UINT32_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: current sector value out of bounds.",
		 function );

		return( -1 );
	}
	for( *run_out_index = 0;
	     *run_out_index < number_of_run_outs;
	     *run_out_index += 1 )
	{
		if( libcdata_array_get_entry_by_index(
		     internal_handle->run_outs_array,
		     *run_out_index,
		     (intptr_t **) run_out_sector_range,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve run-out sector range: %d from array.",
			 function,
			 number_of_run_outs - 1 );

			return( -1 );
		}
		if( *run_out_sector_range == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing run-out sector range: %d.",
			 function,
			 *run_out_index );

			return( -1 );
		}
		if( ( current_sector >= ( *run_out_sector_range )->start_sector )
		 && ( current_sector < ( *run_out_sector_range )->end_sector ) )
		{
			*run_out_offset = offset - ( ( *run_out_sector_range )->start_sector * internal_handle->io_handle->bytes_per_sector );

			return( 1 );
		}
		if( current_sector < ( *run_out_sector_range )->start_sector )
		{
			break;
		}
	}
	*run_out_sector_range = NULL;
	*run_out_offset       = 0;

	return( 0 );
}

/* Retrieves a lead-out sector range for the specified offset
 * When no matching lead-out was found the lead_out_index value contains the next lead-out index on return
 * Returns 1 if successful, 0 if no matching lead-out was found or -1 on error
 */
int libodraw_handle_get_lead_out_at_offset(
     libodraw_internal_handle_t *internal_handle,
     off64_t offset,
     int *lead_out_index,
     libodraw_sector_range_t **lead_out_sector_range,
     off64_t *lead_out_offset,
     libcerror_error_t **error )
{
	static char *function   = "libodraw_handle_get_lead_out_at_offset";
	uint64_t current_sector = 0;
	int number_of_lead_outs = 0;

	if( internal_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	if( internal_handle->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing IO handle.",
		 function );

		return( -1 );
	}
	if( internal_handle->io_handle->bytes_per_sector == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - invalid IO handle - missing bytes per sector.",
		 function );

		return( -1 );
	}
	if( lead_out_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid lead-out index.",
		 function );

		return( -1 );
	}
	if( lead_out_sector_range == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid lead-out sector range.",
		 function );

		return( -1 );
	}
	if( lead_out_offset == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid lead-out offset.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_number_of_entries(
	     internal_handle->lead_outs_array,
	     &number_of_lead_outs,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of elements in lead-outs array.",
		 function );

		return( -1 );
	}
	current_sector = offset / internal_handle->io_handle->bytes_per_sector;

	if( current_sector > (uint64_t) UINT32_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: current sector value out of bounds.",
		 function );

		return( -1 );
	}
	for( *lead_out_index = 0;
	     *lead_out_index < number_of_lead_outs;
	     *lead_out_index += 1 )
	{
		if( libcdata_array_get_entry_by_index(
		     internal_handle->lead_outs_array,
		     *lead_out_index,
		     (intptr_t **) lead_out_sector_range,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve lead-out sector range: %d from array.",
			 function,
			 number_of_lead_outs - 1 );

			return( -1 );
		}
		if( *lead_out_sector_range == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing lead-out sector range: %d.",
			 function,
			 *lead_out_index );

			return( -1 );
		}
		if( ( current_sector >= ( *lead_out_sector_range )->start_sector )
		 && ( current_sector < ( *lead_out_sector_range )->end_sector ) )
		{
			*lead_out_offset = offset - ( ( *lead_out_sector_range )->start_sector * internal_handle->io_handle->bytes_per_sector );

			return( 1 );
		}
		if( current_sector < ( *lead_out_sector_range )->start_sector )
		{
			break;
		}
	}
	*lead_out_sector_range = NULL;
	*lead_out_offset       = 0;

	return( 0 );
}

/* Retrieves a track value for the specified offset
 * When no matching track was found the track_index value contains the next track index on return
 * Returns 1 if successful, 0 if no matching track was found or -1 on error
 */
int libodraw_handle_get_track_at_offset(
     libodraw_internal_handle_t *internal_handle,
     off64_t offset,
     int *track_index,
     libodraw_track_value_t **track_value,
     off64_t *track_offset,
     libcerror_error_t **error )
{
	static char *function   = "libodraw_handle_get_track_at_offset";
	uint64_t current_sector = 0;
	int number_of_tracks    = 0;

	if( internal_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	if( internal_handle->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing IO handle.",
		 function );

		return( -1 );
	}
	if( internal_handle->io_handle->bytes_per_sector == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - invalid IO handle - missing bytes per sector.",
		 function );

		return( -1 );
	}
	if( track_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid track index.",
		 function );

		return( -1 );
	}
	if( track_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid track value.",
		 function );

		return( -1 );
	}
	if( track_offset == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid track offset.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_number_of_entries(
	     internal_handle->tracks_array,
	     &number_of_tracks,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of elements in tracks array.",
		 function );

		return( -1 );
	}
	current_sector = offset / internal_handle->io_handle->bytes_per_sector;

	if( current_sector > (uint64_t) UINT32_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: current sector value out of bounds.",
		 function );

		return( -1 );
	}
	for( *track_index = 0;
	     *track_index < number_of_tracks;
	     *track_index += 1 )
	{
		if( libcdata_array_get_entry_by_index(
		     internal_handle->tracks_array,
		     *track_index,
		     (intptr_t **) track_value,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve track value: %d from array.",
			 function,
			 number_of_tracks - 1 );

			return( -1 );
		}
		if( *track_value == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing track value: %d.",
			 function,
			 *track_index );

			return( -1 );
		}
		if( ( current_sector >= ( *track_value )->start_sector )
		 && ( current_sector < ( *track_value )->end_sector ) )
		{
			*track_offset = offset - ( ( *track_value )->start_sector * internal_handle->io_handle->bytes_per_sector );

			return( 1 );
		}
		if( current_sector < ( *track_value )->start_sector )
		{
			break;
		}
	}
	*track_value  = NULL;
	*track_offset = 0;

	return( 0 );
}

/* Retrieves the current offset of the (media) data
 * Returns 1 if successful or -1 on error
 */
int libodraw_handle_get_offset(
     libodraw_handle_t *handle,
     off64_t *offset,
     libcerror_error_t **error )
{
	libodraw_internal_handle_t *internal_handle = NULL;
	static char *function                       = "libodraw_handle_get_offset";

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libodraw_internal_handle_t *) handle;

	if( internal_handle->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing IO handle.",
		 function );

		return( -1 );
	}
	if( offset == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid offset.",
		 function );

		return( -1 );
	}
	*offset = internal_handle->current_offset;

	return( 1 );
}

/* Retrieves the size of the basename
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
int libodraw_internal_handle_get_basename_size(
     libodraw_internal_handle_t *internal_handle,
     size_t *basename_size,
     libcerror_error_t **error )
{
	static char *function = "libodraw_internal_handle_get_basename_size";

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	int result            = 0;
#endif

	if( internal_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	if( basename_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid basename size.",
		 function );

		return( -1 );
	}
	if( internal_handle->basename == NULL )
	{
		return( 0 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf8_string_size_from_utf32(
		          (libuna_utf32_character_t *) internal_handle->basename,
		          internal_handle->basename_size,
		          basename_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf8_string_size_from_utf16(
		          (libuna_utf16_character_t *) internal_handle->basename,
		          internal_handle->basename_size,
		          basename_size,
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_byte_stream_size_from_utf32(
		          (libuna_utf32_character_t *) internal_handle->basename,
		          internal_handle->basename_size,
		          libclocale_codepage,
		          basename_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_byte_stream_size_from_utf16(
		          (libuna_utf16_character_t *) internal_handle->basename,
		          internal_handle->basename_size,
		          libclocale_codepage,
		          basename_size,
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine basename size.",
		 function );

		return( -1 );
	}
#else
	*basename_size = internal_handle->basename_size;
#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

	return( 1 );
}

/* Retrieves the basename
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
int libodraw_internal_handle_get_basename(
     libodraw_internal_handle_t *internal_handle,
     char *basename,
     size_t basename_size,
     libcerror_error_t **error )
{
	static char *function       = "libodraw_internal_handle_get_basename";
	size_t narrow_basename_size = 0;

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	int result                  = 0;
#endif

	if( internal_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	if( basename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid basename.",
		 function );

		return( -1 );
	}
	if( internal_handle->basename == NULL )
	{
		return( 0 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf8_string_size_from_utf32(
		          (libuna_utf32_character_t *) internal_handle->basename,
		          internal_handle->basename_size,
		          &narrow_basename_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf8_string_size_from_utf16(
		          (libuna_utf16_character_t *) internal_handle->basename,
		          internal_handle->basename_size,
		          &narrow_basename_size,
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_byte_stream_size_from_utf32(
		          (libuna_utf32_character_t *) internal_handle->basename,
		          internal_handle->basename_size,
		          libclocale_codepage,
		          &narrow_basename_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_byte_stream_size_from_utf16(
		          (libuna_utf16_character_t *) internal_handle->basename,
		          internal_handle->basename_size,
		          libclocale_codepage,
		          &narrow_basename_size,
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine narrow basename size.",
		 function );

		return( -1 );
	}
#else
	narrow_basename_size = internal_handle->basename_size;
#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

	if( basename_size < narrow_basename_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: basename too small.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf8_string_copy_from_utf32(
		          (libuna_utf8_character_t *) basename,
		          basename_size,
		          (libuna_utf32_character_t *) internal_handle->basename,
		          internal_handle->basename_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf8_string_copy_from_utf16(
		          (libuna_utf8_character_t *) basename,
		          basename_size,
		          (libuna_utf16_character_t *) internal_handle->basename,
		          internal_handle->basename_size,
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_byte_stream_copy_from_utf32(
		          (uint8_t *) basename,
		          basename_size,
		          libclocale_codepage,
		          (libuna_utf32_character_t *) internal_handle->basename,
		          internal_handle->basename_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_byte_stream_copy_from_utf16(
		          (uint8_t *) basename,
		          basename_size,
		          libclocale_codepage,
		          (libuna_utf16_character_t *) internal_handle->basename,
		          internal_handle->basename_size,
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set basename.",
		 function );

		return( -1 );
	}
#else
	if( system_string_copy(
	     basename,
	     internal_handle->basename,
	     internal_handle->basename_size ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to set basename.",
		 function );

		return( -1 );
	}
	basename[ internal_handle->basename_size - 1 ] = 0;
#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

	return( 1 );
}

/* Sets the basename
 * Returns 1 if successful or -1 on error
 */
int libodraw_internal_handle_set_basename(
     libodraw_internal_handle_t *internal_handle,
     const char *basename,
     size_t basename_length,
     libcerror_error_t **error )
{
	static char *function = "libodraw_internal_handle_set_basename";

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	int result            = 0;
#endif

	if( internal_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	if( basename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid basename.",
		 function );

		return( -1 );
	}
	if( internal_handle->basename != NULL )
	{
		memory_free(
		 internal_handle->basename );

		internal_handle->basename      = NULL;
		internal_handle->basename_size = 0;
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_size_from_utf8(
		          (libuna_utf8_character_t *) basename,
		          basename_length + 1,
		          &( internal_handle->basename_size ),
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_size_from_utf8(
		          (libuna_utf8_character_t *) basename,
		          basename_length + 1,
		          &( internal_handle->basename_size ),
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_size_from_byte_stream(
		          (uint8_t *) basename,
		          basename_length + 1,
		          libclocale_codepage,
		          &( internal_handle->basename_size ),
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_size_from_byte_stream(
		          (uint8_t *) basename,
		          basename_length + 1,
		          libclocale_codepage,
		          &( internal_handle->basename_size ),
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine basename size.",
		 function );

		return( -1 );
	}
#else
	internal_handle->basename_size = basename_length + 1;
#endif
	internal_handle->basename = system_string_allocate(
	                             internal_handle->basename_size );

	if( internal_handle->basename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create basename.",
		 function );

		internal_handle->basename_size = 0;

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_copy_from_utf8(
		          (libuna_utf32_character_t *) internal_handle->basename,
		          internal_handle->basename_size,
		          (libuna_utf8_character_t *) basename,
		          basename_length + 1,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_copy_from_utf8(
		          (libuna_utf16_character_t *) internal_handle->basename,
		          internal_handle->basename_size,
		          (libuna_utf8_character_t *) basename,
		          basename_length + 1,
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_copy_from_byte_stream(
		          (libuna_utf32_character_t *) internal_handle->basename,
		          internal_handle->basename_size,
		          (uint8_t *) basename,
		          basename_length + 1,
		          libclocale_codepage,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_copy_from_byte_stream(
		          (libuna_utf16_character_t *) internal_handle->basename,
		          internal_handle->basename_size,
		          (uint8_t *) basename,
		          basename_length + 1,
		          libclocale_codepage,
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set basename.",
		 function );

		memory_free(
		 internal_handle->basename );

		internal_handle->basename      = NULL;
		internal_handle->basename_size = 0;

		return( -1 );
	}
#else
	if( system_string_copy(
	     internal_handle->basename,
	     basename,
	     basename_length ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to set basename.",
		 function );

		memory_free(
		 internal_handle->basename );

		internal_handle->basename      = NULL;
		internal_handle->basename_size = 0;

		return( -1 );
	}
	internal_handle->basename[ basename_length ] = 0;
#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

	return( 1 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Retrieves the size of the basename
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
int libodraw_internal_handle_get_basename_size_wide(
     libodraw_internal_handle_t *internal_handle,
     size_t *basename_size,
     libcerror_error_t **error )
{
	static char *function = "libodraw_internal_handle_get_basename_size_wide";

#if !defined( HAVE_WIDE_SYSTEM_CHARACTER )
	int result            = 0;
#endif

	if( internal_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	if( basename_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid basename size.",
		 function );

		return( -1 );
	}
	if( internal_handle->basename == NULL )
	{
		return( 0 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	*basename_size = internal_handle->basename_size;
#else
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_size_from_utf8(
		          (libuna_utf8_character_t *) internal_handle->basename,
		          internal_handle->basename_size,
		          basename_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_size_from_utf8(
		          (libuna_utf8_character_t *) internal_handle->basename,
		          internal_handle->basename_size,
		          basename_size,
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_size_from_byte_stream(
		          (uint8_t *) internal_handle->basename,
		          internal_handle->basename_size,
		          libclocale_codepage,
		          basename_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_size_from_byte_stream(
		          (uint8_t *) internal_handle->basename,
		          internal_handle->basename_size,
		          libclocale_codepage,
		          basename_size,
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine basename size.",
		 function );

		return( -1 );
	}
#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */
	return( 1 );
}

/* Retrieves the basename
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
int libodraw_internal_handle_get_basename_wide(
     libodraw_internal_handle_t *internal_handle,
     wchar_t *basename,
     size_t basename_size,
     libcerror_error_t **error )
{
	static char *function     = "libodraw_internal_handle_get_basename_wide";
	size_t wide_basename_size = 0;

#if !defined( HAVE_WIDE_SYSTEM_CHARACTER )
	int result                = 0;
#endif

	if( internal_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	if( basename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid basename.",
		 function );

		return( -1 );
	}
	if( internal_handle->basename == NULL )
	{
		return( 0 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	wide_basename_size = internal_handle->basename_size;
#else
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_size_from_utf8(
		          (libuna_utf8_character_t *) internal_handle->basename,
		          internal_handle->basename_size,
		          &wide_basename_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_size_from_utf8(
		          (libuna_utf8_character_t *) internal_handle->basename,
		          internal_handle->basename_size,
		          &wide_basename_size,
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_size_from_byte_stream(
		          (uint8_t *) internal_handle->basename,
		          internal_handle->basename_size,
		          libclocale_codepage,
		          &wide_basename_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_size_from_byte_stream(
		          (uint8_t *) internal_handle->basename,
		          internal_handle->basename_size,
		          libclocale_codepage,
		          &wide_basename_size,
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine basename size.",
		 function );

		return( -1 );
	}
#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */
	if( basename_size < wide_basename_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: basename too small.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( system_string_copy(
	     basename,
	     internal_handle->basename,
	     internal_handle->basename_size ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to set basename.",
		 function );

		return( -1 );
	}
	basename[ internal_handle->basename_size - 1 ] = 0;
#else
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_copy_from_utf8(
		          (libuna_utf32_character_t *) basename,
		          basename_size,
		          (libuna_utf8_character_t *) internal_handle->basename,
		          internal_handle->basename_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_copy_from_utf8(
		          (libuna_utf16_character_t *) basename,
		          basename_size,
		          (libuna_utf8_character_t *) internal_handle->basename,
		          internal_handle->basename_size,
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_copy_from_byte_stream(
		          (libuna_utf32_character_t *) basename,
		          basename_size,
		          (uint8_t *) internal_handle->basename,
		          internal_handle->basename_size,
		          libclocale_codepage,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_copy_from_byte_stream(
		          (libuna_utf16_character_t *) basename,
		          basename_size,
		          (uint8_t *) internal_handle->basename,
		          internal_handle->basename_size,
		          libclocale_codepage,
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set basename.",
		 function );

		return( -1 );
	}
#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */
	return( 1 );
}

/* Sets the basename
 * Returns 1 if successful or -1 on error
 */
int libodraw_internal_handle_set_basename_wide(
     libodraw_internal_handle_t *internal_handle,
     const wchar_t *basename,
     size_t basename_length,
     libcerror_error_t **error )
{
	static char *function = "libodraw_internal_handle_set_basename_wide";

#if !defined( HAVE_WIDE_SYSTEM_CHARACTER )
	int result            = 0;
#endif

	if( internal_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	if( basename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid basename.",
		 function );

		return( -1 );
	}
	if( internal_handle->basename != NULL )
	{
		memory_free(
		 internal_handle->basename );

		internal_handle->basename      = NULL;
		internal_handle->basename_size = 0;
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	internal_handle->basename_size = basename_length + 1;
#else
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf8_string_size_from_utf32(
		          (libuna_utf32_character_t *) basename,
		          basename_length + 1,
		          &( internal_handle->basename_size ),
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf8_string_size_from_utf16(
		          (libuna_utf16_character_t *) basename,
		          basename_length + 1,
		          &( internal_handle->basename_size ),
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_byte_stream_size_from_utf32(
		          (libuna_utf32_character_t *) basename,
		          basename_length + 1,
		          libclocale_codepage,
		          &( internal_handle->basename_size ),
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_byte_stream_size_from_utf16(
		          (libuna_utf16_character_t *) basename,
		          basename_length + 1,
		          libclocale_codepage,
		          &( internal_handle->basename_size ),
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine basename size.",
		 function );

		return( -1 );
	}
#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */
	internal_handle->basename = system_string_allocate(
	                             internal_handle->basename_size );

	if( internal_handle->basename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create basename.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( system_string_copy(
	     internal_handle->basename,
	     basename,
	     basename_length ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to set basename.",
		 function );

		memory_free(
		 internal_handle->basename );

		internal_handle->basename      = NULL;
		internal_handle->basename_size = 0;

		return( -1 );
	}
	internal_handle->basename[ basename_length ] = 0;
#else
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf8_string_copy_from_utf32(
		          (libuna_utf8_character_t *) internal_handle->basename,
		          internal_handle->basename_size,
		          (libuna_utf32_character_t *) basename,
		          basename_length + 1,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf8_string_copy_from_utf16(
		          (libuna_utf8_character_t *) internal_handle->basename,
		          internal_handle->basename_size,
		          (libuna_utf16_character_t *) basename,
		          basename_length + 1,
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_byte_stream_copy_from_utf32(
		          (uint8_t *) internal_handle->basename,
		          internal_handle->basename_size,
		          libclocale_codepage,
		          (libuna_utf32_character_t *) basename,
		          basename_length + 1,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_byte_stream_copy_from_utf16(
		          (uint8_t *) internal_handle->basename,
		          internal_handle->basename_size,
		          libclocale_codepage,
		          (libuna_utf16_character_t *) basename,
		          basename_length + 1,
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set basename.",
		 function );

		memory_free(
		 internal_handle->basename );

		internal_handle->basename      = NULL;
		internal_handle->basename_size = 0;

		return( -1 );
	}
#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */
	return( 1 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Sets the maximum number of (concurrent) open file handles
 * Returns 1 if successful or -1 on error
 */
int libodraw_handle_set_maximum_number_of_open_handles(
     libodraw_handle_t *handle,
     int maximum_number_of_open_handles,
     libcerror_error_t **error )
{
	libodraw_internal_handle_t *internal_handle = NULL;
	static char *function                       = "libodraw_handle_set_maximum_number_of_open_handles";

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libodraw_internal_handle_t *) handle;

	if( internal_handle->data_file_io_pool != NULL )
	{
		if( libbfio_pool_set_maximum_number_of_open_handles(
		     internal_handle->data_file_io_pool,
		     maximum_number_of_open_handles,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set maximum number of open handles in data files IO handle.",
			 function );

			return( -1 );
		}
	}
	internal_handle->maximum_number_of_open_handles = maximum_number_of_open_handles;

	return( 1 );
}

/* Sets the media values
 * Returns 1 if successful or -1 on error
 */
int libodraw_handle_set_media_values(
     libodraw_internal_handle_t *internal_handle,
     libcerror_error_t **error )
{
	static char *function                 = "libodraw_handle_set_media_values";
	libodraw_sector_range_t *sector_range = NULL;
	libodraw_track_value_t *track_value   = NULL;
	size64_t data_file_size               = 0;
	uint64_t number_of_sectors            = 0;
	int number_of_file_io_handles         = 0;
	int number_of_sessions                = 0;
	int number_of_tracks                  = 0;

	if( internal_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	if( internal_handle->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing IO handle.",
		 function );

		return( -1 );
	}
	if( internal_handle->io_handle->bytes_per_sector == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - invalid IO handle - missing bytes per sector.",
		 function );

		return( -1 );
	}
	if( internal_handle->data_file_io_pool == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing data file IO pool.",
		 function );

		return( -1 );
	}
	if( libbfio_pool_get_number_of_handles(
	     internal_handle->data_file_io_pool,
	     &number_of_file_io_handles,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of file IO handles in pool.",
		 function );

		return( -1 );
	}
	if( libbfio_pool_get_size(
	     internal_handle->data_file_io_pool,
	     number_of_file_io_handles - 1,
	     &data_file_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve data file: %d size.",
		 function,
		 number_of_file_io_handles - 1 );

		return( -1 );
	}
	if( libcdata_array_get_number_of_entries(
	     internal_handle->tracks_array,
	     &number_of_tracks,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of elements in tracks array.",
		 function );

		return( -1 );
	}
	if( number_of_tracks == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: missing track values.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_entry_by_index(
	     internal_handle->tracks_array,
	     number_of_tracks - 1,
	     (intptr_t **) &track_value,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve track value: %d from array.",
		 function,
		 number_of_tracks - 1 );

		return( -1 );
	}
	if( track_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: missing track value: %d.",
		 function,
		 number_of_tracks - 1 );

		return( -1 );
	}
	if( track_value->bytes_per_sector == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid track value: %d - missing bytes per sector.",
		 function,
		 number_of_tracks - 1 );

		return( -1 );
	}
	if( internal_handle->media_size == 0 )
	{
/* TODO currently assumes that last track start sector is always relative to the start of the media */
		if( number_of_file_io_handles > 1 )
		{
			internal_handle->media_size = track_value->start_sector * track_value->bytes_per_sector;
		}
		internal_handle->media_size += data_file_size;

		internal_handle->number_of_sectors = internal_handle->media_size / track_value->bytes_per_sector;

		internal_handle->media_size = internal_handle->number_of_sectors * internal_handle->io_handle->bytes_per_sector;
	}
	if( track_value->number_of_sectors == 0 )
	{
		number_of_sectors = internal_handle->number_of_sectors - track_value->start_sector;

		if( number_of_sectors > (uint64_t) UINT32_MAX )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: number of sectors value out of bounds.",
			 function );

			return( -1 );
		}
		if( libodraw_track_value_set(
		     track_value,
		     track_value->start_sector,
		     number_of_sectors,
		     track_value->type,
		     track_value->data_file_index,
		     track_value->data_file_start_sector,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set last track value.",
			 function );

			return( -1 );
		}
	}
	if( libcdata_array_get_number_of_entries(
	     internal_handle->sessions_array,
	     &number_of_sessions,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of elements in sessions array.",
		 function );

		return( -1 );
	}
	if( number_of_sessions > 0 )
	{
		if( libcdata_array_get_entry_by_index(
		     internal_handle->sessions_array,
		     number_of_sessions - 1,
		     (intptr_t **) &sector_range,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve session sector range: %d from array.",
			 function,
			 number_of_sessions - 1 );

			return( -1 );
		}
		if( sector_range == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing sessions sector range: %d.",
			 function,
			 number_of_sessions - 1 );

			return( -1 );
		}
		if( sector_range->number_of_sectors == 0 )
		{
/* TODO currently assumes that last session is not followed by a lead-out */
			number_of_sectors = internal_handle->number_of_sectors - sector_range->start_sector;

			if( number_of_sectors > (uint64_t) UINT32_MAX )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: number of sectors value out of bounds.",
				 function );

				return( -1 );
			}
			if( libodraw_sector_range_set(
			     sector_range,
			     sector_range->start_sector,
			     number_of_sectors,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
				 "%s: unable to set last session sector range.",
				 function );

				return( -1 );
			}
		}
	}
	return( 1 );
}

/* Retrieves the handle ASCII codepage
 * Returns 1 if successful or -1 on error
 */
int libodraw_handle_get_ascii_codepage(
     libodraw_handle_t *handle,
     int *ascii_codepage,
     libcerror_error_t **error )
{
	libodraw_internal_handle_t *internal_handle = NULL;
	static char *function                       = "libodraw_handle_get_ascii_codepage";

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libodraw_internal_handle_t *) handle;

	if( internal_handle->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing IO handle.",
		 function );

		return( -1 );
	}
	if( ascii_codepage == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid ASCII codepage.",
		 function );

		return( -1 );
	}
	*ascii_codepage = internal_handle->io_handle->ascii_codepage;

	return( 1 );
}

/* Sets the handle ASCII codepage
 * Returns 1 if successful or -1 on error
 */
int libodraw_handle_set_ascii_codepage(
     libodraw_handle_t *handle,
     int ascii_codepage,
     libcerror_error_t **error )
{
	libodraw_internal_handle_t *internal_handle = NULL;
	static char *function                       = "libodraw_handle_set_ascii_codepage";

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libodraw_internal_handle_t *) handle;

	if( internal_handle->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing IO handle.",
		 function );

		return( -1 );
	}
	if( ( ascii_codepage != LIBODRAW_CODEPAGE_ASCII )
	 && ( ascii_codepage != LIBODRAW_CODEPAGE_WINDOWS_874 )
	 && ( ascii_codepage != LIBODRAW_CODEPAGE_WINDOWS_932 )
	 && ( ascii_codepage != LIBODRAW_CODEPAGE_WINDOWS_936 )
	 && ( ascii_codepage != LIBODRAW_CODEPAGE_WINDOWS_949 )
	 && ( ascii_codepage != LIBODRAW_CODEPAGE_WINDOWS_950 )
	 && ( ascii_codepage != LIBODRAW_CODEPAGE_WINDOWS_1250 )
	 && ( ascii_codepage != LIBODRAW_CODEPAGE_WINDOWS_1251 )
	 && ( ascii_codepage != LIBODRAW_CODEPAGE_WINDOWS_1252 )
	 && ( ascii_codepage != LIBODRAW_CODEPAGE_WINDOWS_1253 )
	 && ( ascii_codepage != LIBODRAW_CODEPAGE_WINDOWS_1254 )
	 && ( ascii_codepage != LIBODRAW_CODEPAGE_WINDOWS_1255 )
	 && ( ascii_codepage != LIBODRAW_CODEPAGE_WINDOWS_1256 )
	 && ( ascii_codepage != LIBODRAW_CODEPAGE_WINDOWS_1257 )
	 && ( ascii_codepage != LIBODRAW_CODEPAGE_WINDOWS_1258 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported ASCII codepage.",
		 function );

		return( -1 );
	}
	internal_handle->io_handle->ascii_codepage = ascii_codepage;

	return( 1 );
}

/* Retrieves the number of data files
 * Returns 1 if successful or -1 on error
 */
int libodraw_handle_get_number_of_data_files(
     libodraw_handle_t *handle,
     int *number_of_data_files,
     libcerror_error_t **error )
{
	libodraw_internal_handle_t *internal_handle = NULL;
	static char *function                       = "libodraw_handle_get_number_of_data_files";

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libodraw_internal_handle_t *) handle;

	if( libcdata_array_get_number_of_entries(
	     internal_handle->data_file_descriptors_array,
	     number_of_data_files,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of entries in data file descriptors array.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a data file
 * Returns 1 if successful or -1 on error
 */
int libodraw_handle_get_data_file(
     libodraw_handle_t *handle,
     int index,
     libodraw_data_file_t **data_file,
     libcerror_error_t **error )
{
	libodraw_data_file_descriptor_t *data_file_descriptor = NULL;
	libodraw_internal_handle_t *internal_handle           = NULL;
	static char *function                                 = "libodraw_handle_get_data_file";

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libodraw_internal_handle_t *) handle;

	if( libcdata_array_get_entry_by_index(
	     internal_handle->data_file_descriptors_array,
	     index,
	     (intptr_t **) &data_file_descriptor,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve data file descriptor: %d from array.",
		 function,
		 index );

		return( -1 );
	}
	if( libodraw_data_file_initialize(
	     data_file,
	     internal_handle,
	     data_file_descriptor,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create data file.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Appends a data file
 * Returns 1 if successful or -1 on error
 */
int libodraw_handle_append_data_file(
     libodraw_handle_t *handle,
     const char *name,
     size_t name_length,
     uint8_t type,
     libcerror_error_t **error )
{
	libodraw_data_file_descriptor_t *data_file_descriptor = NULL;
	libodraw_internal_handle_t *internal_handle           = NULL;
	static char *function                                 = "libodraw_handle_append_data_file";
	int entry_index                                       = 0;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libodraw_internal_handle_t *) handle;

	if( name == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid name.",
		 function );

		return( -1 );
	}
	if( ( type != LIBODRAW_FILE_TYPE_UNKNOWN )
	 && ( type != LIBODRAW_FILE_TYPE_BINARY_LITTLE_ENDIAN )
	 && ( type != LIBODRAW_FILE_TYPE_BINARY_BIG_ENDIAN )
	 && ( type != LIBODRAW_FILE_TYPE_AUDIO_AIFF )
	 && ( type != LIBODRAW_FILE_TYPE_AUDIO_WAVE )
	 && ( type != LIBODRAW_FILE_TYPE_AUDIO_MPEG1_LAYER3 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported type codepage.",
		 function );

		return( -1 );
	}
	if( libodraw_data_file_descriptor_initialize(
	     &data_file_descriptor,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create data file descriptor.",
		 function );

		goto on_error;
	}
	if( libodraw_data_file_descriptor_set_name(
	     data_file_descriptor,
	     name,
	     name_length,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set name in data file descriptor.",
		 function );

		goto on_error;
	}
	data_file_descriptor->type = type;

	if( libcdata_array_append_entry(
	     internal_handle->data_file_descriptors_array,
	     &entry_index,
	     (intptr_t *) data_file_descriptor,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
		 "%s: unable to append data file descriptor.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( data_file_descriptor != NULL )
	{
		libodraw_data_file_descriptor_free(
		 &data_file_descriptor,
		 NULL );
	}
	return( -1 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Appends a data file
 * Returns 1 if successful or -1 on error
 */
int libodraw_handle_append_data_file_wide(
     libodraw_handle_t *handle,
     const wchar_t *name,
     size_t name_length,
     uint8_t type,
     libcerror_error_t **error )
{
	libodraw_data_file_descriptor_t *data_file_descriptor = NULL;
	libodraw_internal_handle_t *internal_handle           = NULL;
	static char *function                                 = "libodraw_handle_append_data_file_wide";
	int entry_index                                       = 0;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libodraw_internal_handle_t *) handle;

	if( name == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid name.",
		 function );

		return( -1 );
	}
	if( ( type != LIBODRAW_FILE_TYPE_UNKNOWN )
	 && ( type != LIBODRAW_FILE_TYPE_BINARY_LITTLE_ENDIAN )
	 && ( type != LIBODRAW_FILE_TYPE_BINARY_BIG_ENDIAN )
	 && ( type != LIBODRAW_FILE_TYPE_AUDIO_AIFF )
	 && ( type != LIBODRAW_FILE_TYPE_AUDIO_WAVE )
	 && ( type != LIBODRAW_FILE_TYPE_AUDIO_MPEG1_LAYER3 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported type codepage.",
		 function );

		return( -1 );
	}
	if( libodraw_data_file_descriptor_initialize(
	     &data_file_descriptor,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create data file descriptor.",
		 function );

		goto on_error;
	}
	if( libodraw_data_file_descriptor_set_name_wide(
	     data_file_descriptor,
	     name,
	     name_length,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set name in data file descriptor.",
		 function );

		goto on_error;
	}
	data_file_descriptor->type = type;

	if( libcdata_array_append_entry(
	     internal_handle->data_file_descriptors_array,
	     &entry_index,
	     (intptr_t *) data_file_descriptor,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
		 "%s: unable to append data file descriptor.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( data_file_descriptor != NULL )
	{
		libodraw_data_file_descriptor_free(
		 &data_file_descriptor,
		 NULL );
	}
	return( -1 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Retrieves the number of media size
 * Returns 1 if successful or -1 on error
 */
int libodraw_handle_get_media_size(
     libodraw_handle_t *handle,
     size64_t *media_size,
     libcerror_error_t **error )
{
	libodraw_internal_handle_t *internal_handle = NULL;
	static char *function                       = "libodraw_handle_get_media_size";

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libodraw_internal_handle_t *) handle;

	if( media_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid media size.",
		 function );

		return( -1 );
	}
	*media_size = internal_handle->media_size;

	return( 1 );
}

/* Retrieves the number of bytes per sector
 * Returns 1 if successful or -1 on error
 */
int libodraw_handle_get_bytes_per_sector(
     libodraw_handle_t *handle,
     uint32_t *bytes_per_sector,
     libcerror_error_t **error )
{
	libodraw_internal_handle_t *internal_handle = NULL;
	static char *function                       = "libodraw_handle_get_bytes_per_sector";

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libodraw_internal_handle_t *) handle;

	if( internal_handle->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing IO handle.",
		 function );

		return( -1 );
	}
	if( bytes_per_sector == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid bytes per sector.",
		 function );

		return( -1 );
	}
	*bytes_per_sector = internal_handle->io_handle->bytes_per_sector;

	return( 1 );
}

/* Sets the number of bytes per sector
 * Returns 1 if successful or -1 on error
 */
int libodraw_handle_set_bytes_per_sector(
     libodraw_handle_t *handle,
     uint32_t bytes_per_sector,
     libcerror_error_t **error )
{
	libodraw_internal_handle_t *internal_handle = NULL;
	static char *function                       = "libodraw_handle_set_bytes_per_sector";

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libodraw_internal_handle_t *) handle;

	if( internal_handle->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing IO handle.",
		 function );

		return( -1 );
	}
/* TODO add support for 2352 */
	if( bytes_per_sector != 2048 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported bytes per sector.",
		 function );

		return( -1 );
	}
	internal_handle->io_handle->bytes_per_sector = bytes_per_sector;

	return( 1 );
}

/* Retrieves the number of sectors
 * Returns 1 if successful or -1 on error
 */
int libodraw_handle_get_number_of_sectors(
     libodraw_handle_t *handle,
     uint64_t *number_of_sectors,
     libcerror_error_t **error )
{
	libodraw_internal_handle_t *internal_handle = NULL;
	static char *function                       = "libodraw_handle_get_number_of_sectors";

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libodraw_internal_handle_t *) handle;

	if( number_of_sectors == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid number of sectors.",
		 function );

		return( -1 );
	}
	*number_of_sectors = internal_handle->number_of_sectors;

	return( 1 );
}

/* Retrieves the number of sessions
 * Returns 1 if successful or -1 on error
 */
int libodraw_handle_get_number_of_sessions(
     libodraw_handle_t *handle,
     int *number_of_sessions,
     libcerror_error_t **error )
{
	libodraw_internal_handle_t *internal_handle = NULL;
	static char *function                       = "libodraw_handle_get_number_of_sessions";

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libodraw_internal_handle_t *) handle;

	if( libcdata_array_get_number_of_entries(
	     internal_handle->sessions_array,
	     number_of_sessions,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of elements in sessions array.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a session
 * Returns 1 if successful or -1 on error
 */
int libodraw_handle_get_session(
     libodraw_handle_t *handle,
     int index,
     uint64_t *start_sector,
     uint64_t *number_of_sectors,
     libcerror_error_t **error )
{
	libodraw_internal_handle_t *internal_handle = NULL;
	libodraw_sector_range_t *sector_range       = NULL;
	static char *function                       = "libodraw_handle_get_session";

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libodraw_internal_handle_t *) handle;

	if( libcdata_array_get_entry_by_index(
	     internal_handle->sessions_array,
	     index,
	     (intptr_t **) &sector_range,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve session sector range: %d from array.",
		 function,
		 index );

		return( -1 );
	}
	if( libodraw_sector_range_get(
	     sector_range,
	     start_sector,
	     number_of_sectors,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve sector range.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Appends a session
 * Returns 1 if successful or -1 on error
 */
int libodraw_handle_append_session(
     libodraw_handle_t *handle,
     uint64_t start_sector,
     uint64_t number_of_sectors,
     libcerror_error_t **error )
{
	libodraw_internal_handle_t *internal_handle = NULL;
	libodraw_sector_range_t *sector_range       = NULL;
	static char *function                       = "libodraw_handle_append_session";
	int entry_index                             = 0;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libodraw_internal_handle_t *) handle;

	if( libodraw_sector_range_initialize(
	     &sector_range,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create sector range.",
		 function );

		goto on_error;
	}
	if( libodraw_sector_range_set(
	     sector_range,
	     start_sector,
	     number_of_sectors,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set sector range.",
		 function );

		goto on_error;
	}
	if( libcdata_array_append_entry(
	     internal_handle->sessions_array,
	     &entry_index,
	     (intptr_t *) sector_range,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
		 "%s: unable to append session sector range to array.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( sector_range != NULL )
	{
		libodraw_sector_range_free(
		 &sector_range,
		 NULL );
	}
	return( -1 );
}

/* Retrieves the number of lead-outs
 * Returns 1 if successful or -1 on error
 */
int libodraw_handle_get_number_of_lead_outs(
     libodraw_handle_t *handle,
     int *number_of_lead_outs,
     libcerror_error_t **error )
{
	libodraw_internal_handle_t *internal_handle = NULL;
	static char *function                       = "libodraw_handle_get_number_of_lead_outs";

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libodraw_internal_handle_t *) handle;

	if( libcdata_array_get_number_of_entries(
	     internal_handle->lead_outs_array,
	     number_of_lead_outs,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of elements in lead-outs array.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a lead-out
 * Returns 1 if successful or -1 on error
 */
int libodraw_handle_get_lead_out(
     libodraw_handle_t *handle,
     int index,
     uint64_t *start_sector,
     uint64_t *number_of_sectors,
     libcerror_error_t **error )
{
	libodraw_internal_handle_t *internal_handle = NULL;
	libodraw_sector_range_t *sector_range       = NULL;
	static char *function                       = "libodraw_handle_get_lead_out";

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libodraw_internal_handle_t *) handle;

	if( libcdata_array_get_entry_by_index(
	     internal_handle->lead_outs_array,
	     index,
	     (intptr_t **) &sector_range,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve lead-out sector range: %d from array.",
		 function,
		 index );

		return( -1 );
	}
	if( libodraw_sector_range_get(
	     sector_range,
	     start_sector,
	     number_of_sectors,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve sector range.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Appends a lead-out
 * Returns 1 if successful or -1 on error
 */
int libodraw_handle_append_lead_out(
     libodraw_handle_t *handle,
     uint64_t start_sector,
     uint64_t number_of_sectors,
     libcerror_error_t **error )
{
	libodraw_internal_handle_t *internal_handle = NULL;
	libodraw_sector_range_t *sector_range       = NULL;
	static char *function                       = "libodraw_handle_append_lead_out";
	int entry_index                             = 0;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libodraw_internal_handle_t *) handle;

	if( libodraw_sector_range_initialize(
	     &sector_range,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create sector range.",
		 function );

		goto on_error;
	}
	if( libodraw_sector_range_set(
	     sector_range,
	     start_sector,
	     number_of_sectors,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set sector range.",
		 function );

		goto on_error;
	}
	if( libcdata_array_append_entry(
	     internal_handle->lead_outs_array,
	     &entry_index,
	     (intptr_t *) sector_range,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
		 "%s: unable to append lead-out sector range to array.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( sector_range != NULL )
	{
		libodraw_sector_range_free(
		 &sector_range,
		 NULL );
	}
	return( -1 );
}

/* Retrieves the number of tracks
 * Returns 1 if successful or -1 on error
 */
int libodraw_handle_get_number_of_tracks(
     libodraw_handle_t *handle,
     int *number_of_tracks,
     libcerror_error_t **error )
{
	libodraw_internal_handle_t *internal_handle = NULL;
	static char *function                       = "libodraw_handle_get_number_of_tracks";

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libodraw_internal_handle_t *) handle;

	if( libcdata_array_get_number_of_entries(
	     internal_handle->tracks_array,
	     number_of_tracks,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of elements in tracks array.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a track
 * Returns 1 if successful or -1 on error
 */
int libodraw_handle_get_track(
     libodraw_handle_t *handle,
     int index,
     uint64_t *start_sector,
     uint64_t *number_of_sectors,
     uint8_t *type,
     int *data_file_index,
     uint64_t *data_file_start_sector,
     libcerror_error_t **error )
{
	libodraw_internal_handle_t *internal_handle = NULL;
	libodraw_track_value_t *track_value         = NULL;
	static char *function                       = "libodraw_handle_get_track";

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libodraw_internal_handle_t *) handle;

	if( libcdata_array_get_entry_by_index(
	     internal_handle->tracks_array,
	     index,
	     (intptr_t **) &track_value,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve track value: %d from array.",
		 function,
		 index );

		return( -1 );
	}
	if( libodraw_track_value_get(
	     track_value,
	     start_sector,
	     number_of_sectors,
	     type,
	     data_file_index,
	     data_file_start_sector,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve track value.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Appends a track
 * Returns 1 if successful or -1 on error
 */
int libodraw_handle_append_track(
     libodraw_handle_t *handle,
     uint64_t start_sector,
     uint64_t number_of_sectors,
     uint8_t type,
     int data_file_index,
     uint64_t data_file_start_sector,
     libcerror_error_t **error )
{
	libodraw_internal_handle_t *internal_handle = NULL;
	libodraw_track_value_t *track_value         = NULL;
	static char *function                       = "libodraw_handle_append_track";
	int entry_index                             = 0;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libodraw_internal_handle_t *) handle;

	if( libodraw_track_value_initialize(
	     &track_value,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create track value.",
		 function );

		goto on_error;
	}
	if( libodraw_track_value_set(
	     track_value,
	     start_sector,
	     number_of_sectors,
	     type,
	     data_file_index,
	     data_file_start_sector,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set track value.",
		 function );

		goto on_error;
	}
	if( libcdata_array_append_entry(
	     internal_handle->tracks_array,
	     &entry_index,
	     (intptr_t *) track_value,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
		 "%s: unable to append track to array.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( track_value != NULL )
	{
		libodraw_track_value_free(
		 &track_value,
		 NULL );
	}
	return( -1 );
}


