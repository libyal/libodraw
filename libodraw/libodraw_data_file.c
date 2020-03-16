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

#include <common.h>
#include <memory.h>
#include <types.h>

#include "libodraw_data_file.h"
#include "libodraw_data_file_descriptor.h"
#include "libodraw_handle.h"
#include "libodraw_libcerror.h"
#include "libodraw_libuna.h"
#include "libodraw_types.h"

/* Creates a data file
 * Make sure the value data_file is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libodraw_data_file_initialize(
     libodraw_data_file_t **data_file,
     libodraw_internal_handle_t *internal_handle,
     libodraw_data_file_descriptor_t *data_file_descriptor,
     libcerror_error_t **error )
{
	libodraw_internal_data_file_t *internal_data_file = NULL;
	static char *function                             = "libodraw_data_file_initialize";

	if( data_file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data_file.",
		 function );

		return( -1 );
	}
	if( *data_file != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid data file value already set.",
		 function );

		return( -1 );
	}
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
	if( data_file_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data file descriptor.",
		 function );

		return( -1 );
	}
	internal_data_file = memory_allocate_structure(
	                      libodraw_internal_data_file_t );

	if( internal_data_file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create data file.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_data_file,
	     0,
	     sizeof( libodraw_internal_data_file_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear data file.",
		 function );

		goto on_error;
	}
	internal_data_file->internal_handle      = internal_handle;
	internal_data_file->data_file_descriptor = data_file_descriptor;

	*data_file = (libodraw_data_file_t *) internal_data_file;

	return( 1 );

on_error:
	if( internal_data_file != NULL )
	{
		memory_free(
		 internal_data_file );
	}
	return( -1 );
}

/* Frees a data_file
 * Returns 1 if successful or -1 on error
 */
int libodraw_data_file_free(
     libodraw_data_file_t **data_file,
     libcerror_error_t **error )
{
	libodraw_internal_data_file_t *internal_data_file = NULL;
	static char *function                             = "libodraw_data_file_free";

	if( data_file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data_file.",
		 function );

		return( -1 );
	}
	if( *data_file != NULL )
	{
		internal_data_file = (libodraw_internal_data_file_t *) *data_file;
		*data_file         = NULL;

		/* The internal_handle and data_file_descriptor references are freed elsewhere
		 */
		memory_free(
		 internal_data_file );
	}
	return( 1 );
}

/* Retrieves the filename size
 * The filename size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libodraw_data_file_get_filename_size(
     libodraw_data_file_t *data_file,
     size_t *filename_size,
     libcerror_error_t **error )
{
	libodraw_internal_data_file_t *internal_data_file = NULL;
	static char *function                             = "libodraw_data_file_get_filename_size";

	if( data_file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data file.",
		 function );

		return( -1 );
	}
	internal_data_file = (libodraw_internal_data_file_t *) data_file;

	if( internal_data_file->data_file_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid data file - missing data file descriptor.",
		 function );

		return( -1 );
	}
	if( libodraw_data_file_descriptor_get_name_size(
	     internal_data_file->data_file_descriptor,
	     filename_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve data file descriptor name size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the filename
 * The filename size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libodraw_data_file_get_filename(
     libodraw_data_file_t *data_file,
     char *filename,
     size_t filename_size,
     libcerror_error_t **error )
{
	libodraw_internal_data_file_t *internal_data_file = NULL;
	static char *function                             = "libodraw_data_file_get_filename";

	if( data_file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data file.",
		 function );

		return( -1 );
	}
	internal_data_file = (libodraw_internal_data_file_t *) data_file;

	if( internal_data_file->data_file_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid data file - missing data file descriptor.",
		 function );

		return( -1 );
	}
	if( libodraw_data_file_descriptor_get_name(
	     internal_data_file->data_file_descriptor,
	     filename,
	     filename_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve data file descriptor name.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Sets the segment file
 * Returns 1 if successful or -1 on error
 */
int libodraw_data_file_set_filename(
     libodraw_data_file_t *data_file,
     const char *filename,
     size_t filename_length,
     libcerror_error_t **error )
{
	libodraw_internal_data_file_t *internal_data_file = NULL;
	static char *function                             = "libodraw_data_file_set_filename";

	if( data_file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data file.",
		 function );

		return( -1 );
	}
	internal_data_file = (libodraw_internal_data_file_t *) data_file;

	if( internal_data_file->data_file_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid data file - missing data file descriptor.",
		 function );

		return( -1 );
	}
	if( libodraw_data_file_descriptor_set_name(
	     internal_data_file->data_file_descriptor,
	     filename,
	     filename_length,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set data file descriptor name.",
		 function );

		return( -1 );
	}
	internal_data_file->data_file_descriptor->name_set = 1;

	return( 1 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Retrieves the filename size
 * The filename size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libodraw_data_file_get_filename_size_wide(
     libodraw_data_file_t *data_file,
     size_t *filename_size,
     libcerror_error_t **error )
{
	libodraw_internal_data_file_t *internal_data_file = NULL;
	static char *function                             = "libodraw_data_file_get_filename_size_wide";

	if( data_file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data file.",
		 function );

		return( -1 );
	}
	internal_data_file = (libodraw_internal_data_file_t *) data_file;

	if( internal_data_file->data_file_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid data file - missing data file descriptor.",
		 function );

		return( -1 );
	}
	if( libodraw_data_file_descriptor_get_name_size_wide(
	     internal_data_file->data_file_descriptor,
	     filename_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve data file descriptor name size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the filename
 * The filename size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libodraw_data_file_get_filename_wide(
     libodraw_data_file_t *data_file,
     wchar_t *filename,
     size_t filename_size,
     libcerror_error_t **error )
{
	libodraw_internal_data_file_t *internal_data_file = NULL;
	static char *function                             = "libodraw_data_file_get_filename_wide";

	if( data_file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data file.",
		 function );

		return( -1 );
	}
	internal_data_file = (libodraw_internal_data_file_t *) data_file;

	if( internal_data_file->data_file_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid data file - missing data file descriptor.",
		 function );

		return( -1 );
	}
	if( libodraw_data_file_descriptor_get_name_wide(
	     internal_data_file->data_file_descriptor,
	     filename,
	     filename_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve data file descriptor name.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Sets the segment file
 * Returns 1 if successful or -1 on error
 */
int libodraw_data_file_set_filename_wide(
     libodraw_data_file_t *data_file,
     const wchar_t *filename,
     size_t filename_length,
     libcerror_error_t **error )
{
	libodraw_internal_data_file_t *internal_data_file = NULL;
	static char *function                             = "libodraw_data_file_set_filename_wide";

	if( data_file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data file.",
		 function );

		return( -1 );
	}
	internal_data_file = (libodraw_internal_data_file_t *) data_file;

	if( internal_data_file->data_file_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid data file - missing data file descriptor.",
		 function );

		return( -1 );
	}
	if( libodraw_data_file_descriptor_set_name_wide(
	     internal_data_file->data_file_descriptor,
	     filename,
	     filename_length,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set data file descriptor name.",
		 function );

		return( -1 );
	}
	internal_data_file->data_file_descriptor->name_set = 1;

	return( 1 );
}

#endif

/* Retrieves the file type
 * Returns 1 if successful or -1 on error
 */
int libodraw_data_file_get_type(
     libodraw_data_file_t *data_file,
     uint8_t *type,
     libcerror_error_t **error )
{
	libodraw_internal_data_file_t *internal_data_file = NULL;
	static char *function                             = "libodraw_data_file_get_type";

	if( data_file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data file.",
		 function );

		return( -1 );
	}
	internal_data_file = (libodraw_internal_data_file_t *) data_file;

	if( internal_data_file->data_file_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid data file - missing data file descriptor.",
		 function );

		return( -1 );
	}
	if( type == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid type.",
		 function );

		return( -1 );
	}
	*type = internal_data_file->data_file_descriptor->type;

	return( 1 );
}

