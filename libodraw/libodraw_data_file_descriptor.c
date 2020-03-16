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

#include <common.h>
#include <memory.h>
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#include "libodraw_data_file_descriptor.h"
#include "libodraw_libcerror.h"
#include "libodraw_libclocale.h"
#include "libodraw_libuna.h"

/* Creates a data file descriptor
 * Make sure the value data_file_descriptor is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libodraw_data_file_descriptor_initialize(
     libodraw_data_file_descriptor_t **data_file_descriptor,
     libcerror_error_t **error )
{
	static char *function = "libodraw_data_file_descriptor_initialize";

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
	if( *data_file_descriptor != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid data file descriptor value already set.",
		 function );

		return( -1 );
	}
	*data_file_descriptor = memory_allocate_structure(
	                         libodraw_data_file_descriptor_t );

	if( *data_file_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create data file descriptor.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *data_file_descriptor,
	     0,
	     sizeof( libodraw_data_file_descriptor_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear data file descriptor.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *data_file_descriptor != NULL )
	{
		memory_free(
		 *data_file_descriptor );

		*data_file_descriptor = NULL;
	}
	return( -1 );
}

/* Frees a data file descriptor
 * Returns 1 if successful or -1 on error
 */
int libodraw_data_file_descriptor_free(
     libodraw_data_file_descriptor_t **data_file_descriptor,
     libcerror_error_t **error )
{
	static char *function = "libodraw_data_file_descriptor_free";

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
	if( *data_file_descriptor != NULL )
	{
		if( ( *data_file_descriptor )->name != NULL )
		{
			memory_free(
			 ( *data_file_descriptor )->name );
		}
		memory_free(
		 *data_file_descriptor );

		*data_file_descriptor = NULL;
	}
	return( 1 );
}

/* Retrieves the size of the name
 * Returns 1 if successful or -1 on error
 */
int libodraw_data_file_descriptor_get_name_size(
     libodraw_data_file_descriptor_t *data_file_descriptor,
     size_t *name_size,
     libcerror_error_t **error )
{
	static char *function = "libodraw_data_file_descriptor_get_name_size";

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	int result            = 0;
#endif

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
	if( data_file_descriptor->name == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid data file descriptor - missing name.",
		 function );

		return( -1 );
	}
	if( name_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid name size.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf8_string_size_from_utf32(
		          (libuna_utf32_character_t *) data_file_descriptor->name,
		          data_file_descriptor->name_size,
		          name_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf8_string_size_from_utf16(
		          (libuna_utf16_character_t *) data_file_descriptor->name,
		          data_file_descriptor->name_size,
		          name_size,
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_byte_stream_size_from_utf32(
		          (libuna_utf32_character_t *) data_file_descriptor->name,
		          data_file_descriptor->name_size,
		          libclocale_codepage,
		          name_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_byte_stream_size_from_utf16(
		          (libuna_utf16_character_t *) data_file_descriptor->name,
		          data_file_descriptor->name_size,
		          libclocale_codepage,
		          name_size,
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
		 "%s: unable to determine name size.",
		 function );

		return( -1 );
	}
#else
	*name_size = data_file_descriptor->name_size;
#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

	return( 1 );
}

/* Retrieves the name
 * Returns 1 if successful or -1 on error
 */
int libodraw_data_file_descriptor_get_name(
     libodraw_data_file_descriptor_t *data_file_descriptor,
     char *name,
     size_t name_size,
     libcerror_error_t **error )
{
	static char *function   = "libodraw_data_file_descriptor_get_name";
	size_t narrow_name_size = 0;

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	int result              = 0;
#endif

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
	if( data_file_descriptor->name == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid data file descriptor - missing name.",
		 function );

		return( -1 );
	}
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
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf8_string_size_from_utf32(
		          (libuna_utf32_character_t *) data_file_descriptor->name,
		          data_file_descriptor->name_size,
		          &narrow_name_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf8_string_size_from_utf16(
		          (libuna_utf16_character_t *) data_file_descriptor->name,
		          data_file_descriptor->name_size,
		          &narrow_name_size,
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_byte_stream_size_from_utf32(
		          (libuna_utf32_character_t *) data_file_descriptor->name,
		          data_file_descriptor->name_size,
		          libclocale_codepage,
		          &narrow_name_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_byte_stream_size_from_utf16(
		          (libuna_utf16_character_t *) data_file_descriptor->name,
		          data_file_descriptor->name_size,
		          libclocale_codepage,
		          &narrow_name_size,
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
		 "%s: unable to determine narrow name size.",
		 function );

		return( -1 );
	}
#else
	narrow_name_size = data_file_descriptor->name_size;
#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

	if( name_size < narrow_name_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: name too small.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf8_string_copy_from_utf32(
		          (libuna_utf8_character_t *) name,
		          name_size,
		          (libuna_utf32_character_t *) data_file_descriptor->name,
		          data_file_descriptor->name_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf8_string_copy_from_utf16(
		          (libuna_utf8_character_t *) name,
		          name_size,
		          (libuna_utf16_character_t *) data_file_descriptor->name,
		          data_file_descriptor->name_size,
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_byte_stream_copy_from_utf32(
		          (uint8_t *) name,
		          name_size,
		          libclocale_codepage,
		          (libuna_utf32_character_t *) data_file_descriptor->name,
		          data_file_descriptor->name_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_byte_stream_copy_from_utf16(
		          (uint8_t *) name,
		          name_size,
		          libclocale_codepage,
		          (libuna_utf16_character_t *) data_file_descriptor->name,
		          data_file_descriptor->name_size,
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
		 "%s: unable to set name.",
		 function );

		return( -1 );
	}
#else
	if( system_string_copy(
	     name,
	     data_file_descriptor->name,
	     data_file_descriptor->name_size ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to set name.",
		 function );

		return( -1 );
	}
	name[ data_file_descriptor->name_size - 1 ] = 0;
#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

	return( 1 );
}

/* Sets the name
 * Returns 1 if successful or -1 on error
 */
int libodraw_data_file_descriptor_set_name(
     libodraw_data_file_descriptor_t *data_file_descriptor,
     const char *name,
     size_t name_length,
     libcerror_error_t **error )
{
	static char *function = "libodraw_data_file_descriptor_set_name";

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	int result            = 0;
#endif

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
	if( data_file_descriptor->name != NULL )
	{
		memory_free(
		 data_file_descriptor->name );

		data_file_descriptor->name      = NULL;
		data_file_descriptor->name_size = 0;
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_size_from_utf8(
		          (libuna_utf8_character_t *) name,
		          name_length + 1,
		          &( data_file_descriptor->name_size ),
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_size_from_utf8(
		          (libuna_utf8_character_t *) name,
		          name_length + 1,
		          &( data_file_descriptor->name_size ),
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_size_from_byte_stream(
		          (uint8_t *) name,
		          name_length + 1,
		          libclocale_codepage,
		          &( data_file_descriptor->name_size ),
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_size_from_byte_stream(
		          (uint8_t *) name,
		          name_length + 1,
		          libclocale_codepage,
		          &( data_file_descriptor->name_size ),
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
		 "%s: unable to determine name size.",
		 function );

		return( -1 );
	}
#else
	data_file_descriptor->name_size = name_length + 1;
#endif
	data_file_descriptor->name = system_string_allocate(
	                              data_file_descriptor->name_size );

	if( data_file_descriptor->name == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create name.",
		 function );

		data_file_descriptor->name_size = 0;

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_copy_from_utf8(
		          (libuna_utf32_character_t *) data_file_descriptor->name,
		          data_file_descriptor->name_size,
		          (libuna_utf8_character_t *) name,
		          name_length + 1,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_copy_from_utf8(
		          (libuna_utf16_character_t *) data_file_descriptor->name,
		          data_file_descriptor->name_size,
		          (libuna_utf8_character_t *) name,
		          name_length + 1,
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_copy_from_byte_stream(
		          (libuna_utf32_character_t *) data_file_descriptor->name,
		          data_file_descriptor->name_size,
		          (uint8_t *) name,
		          name_length + 1,
		          libclocale_codepage,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_copy_from_byte_stream(
		          (libuna_utf16_character_t *) data_file_descriptor->name,
		          data_file_descriptor->name_size,
		          (uint8_t *) name,
		          name_length + 1,
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
		 "%s: unable to set name.",
		 function );

		memory_free(
		 data_file_descriptor->name );

		data_file_descriptor->name      = NULL;
		data_file_descriptor->name_size = 0;

		return( -1 );
	}
#else
	if( system_string_copy(
	     data_file_descriptor->name,
	     name,
	     name_length ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to set name.",
		 function );

		memory_free(
		 data_file_descriptor->name );

		data_file_descriptor->name      = NULL;
		data_file_descriptor->name_size = 0;

		return( -1 );
	}
	data_file_descriptor->name[ name_length ] = 0;
#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

	return( 1 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Retrieves the size of the name
 * Returns 1 if successful or -1 on error
 */
int libodraw_data_file_descriptor_get_name_size_wide(
     libodraw_data_file_descriptor_t *data_file_descriptor,
     size_t *name_size,
     libcerror_error_t **error )
{
	static char *function = "libodraw_data_file_descriptor_get_name_size_wide";

#if !defined( HAVE_WIDE_SYSTEM_CHARACTER )
	int result            = 0;
#endif

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
	if( data_file_descriptor->name == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid data file descriptor - missing name.",
		 function );

		return( -1 );
	}
	if( name_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid name size.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	*name_size = data_file_descriptor->name_size;
#else
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_size_from_utf8(
		          (libuna_utf8_character_t *) data_file_descriptor->name,
		          data_file_descriptor->name_size,
		          name_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_size_from_utf8(
		          (libuna_utf8_character_t *) data_file_descriptor->name,
		          data_file_descriptor->name_size,
		          name_size,
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_size_from_byte_stream(
		          (uint8_t *) data_file_descriptor->name,
		          data_file_descriptor->name_size,
		          libclocale_codepage,
		          name_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_size_from_byte_stream(
		          (uint8_t *) data_file_descriptor->name,
		          data_file_descriptor->name_size,
		          libclocale_codepage,
		          name_size,
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
		 "%s: unable to determine name size.",
		 function );

		return( -1 );
	}
#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */
	return( 1 );
}

/* Retrieves the name
 * Returns 1 if successful or -1 on error
 */
int libodraw_data_file_descriptor_get_name_wide(
     libodraw_data_file_descriptor_t *data_file_descriptor,
     wchar_t *name,
     size_t name_size,
     libcerror_error_t **error )
{
	static char *function = "libodraw_data_file_descriptor_get_name_wide";
	size_t wide_name_size = 0;

#if !defined( HAVE_WIDE_SYSTEM_CHARACTER )
	int result            = 0;
#endif

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
	if( data_file_descriptor->name == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid data file descriptor - missing name.",
		 function );

		return( -1 );
	}
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
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	wide_name_size = data_file_descriptor->name_size;
#else
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_size_from_utf8(
		          (libuna_utf8_character_t *) data_file_descriptor->name,
		          data_file_descriptor->name_size,
		          &wide_name_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_size_from_utf8(
		          (libuna_utf8_character_t *) data_file_descriptor->name,
		          data_file_descriptor->name_size,
		          &wide_name_size,
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_size_from_byte_stream(
		          (uint8_t *) data_file_descriptor->name,
		          data_file_descriptor->name_size,
		          libclocale_codepage,
		          &wide_name_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_size_from_byte_stream(
		          (uint8_t *) data_file_descriptor->name,
		          data_file_descriptor->name_size,
		          libclocale_codepage,
		          &wide_name_size,
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
		 "%s: unable to determine name size.",
		 function );

		return( -1 );
	}
#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */
	if( name_size < wide_name_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: name too small.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( system_string_copy(
	     name,
	     data_file_descriptor->name,
	     data_file_descriptor->name_size ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to set name.",
		 function );

		return( -1 );
	}
	name[ data_file_descriptor->name_size - 1 ] = 0;
#else
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_copy_from_utf8(
		          (libuna_utf32_character_t *) name,
		          name_size,
		          (libuna_utf8_character_t *) data_file_descriptor->name,
		          data_file_descriptor->name_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_copy_from_utf8(
		          (libuna_utf16_character_t *) name,
		          name_size,
		          (libuna_utf8_character_t *) data_file_descriptor->name,
		          data_file_descriptor->name_size,
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_copy_from_byte_stream(
		          (libuna_utf32_character_t *) name,
		          name_size,
		          (uint8_t *) data_file_descriptor->name,
		          data_file_descriptor->name_size,
		          libclocale_codepage,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_copy_from_byte_stream(
		          (libuna_utf16_character_t *) name,
		          name_size,
		          (uint8_t *) data_file_descriptor->name,
		          data_file_descriptor->name_size,
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
		 "%s: unable to set name.",
		 function );

		return( -1 );
	}
#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */
	return( 1 );
}

/* Sets the name
 * Returns 1 if successful or -1 on error
 */
int libodraw_data_file_descriptor_set_name_wide(
     libodraw_data_file_descriptor_t *data_file_descriptor,
     const wchar_t *name,
     size_t name_length,
     libcerror_error_t **error )
{
	static char *function = "libodraw_data_file_descriptor_set_name_wide";

#if !defined( HAVE_WIDE_SYSTEM_CHARACTER )
	int result            = 0;
#endif

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
	if( data_file_descriptor->name != NULL )
	{
		memory_free(
		 data_file_descriptor->name );

		data_file_descriptor->name      = NULL;
		data_file_descriptor->name_size = 0;
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	data_file_descriptor->name_size = name_length + 1;
#else
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf8_string_size_from_utf32(
		          (libuna_utf32_character_t *) name,
		          name_length + 1,
		          &( data_file_descriptor->name_size ),
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf8_string_size_from_utf16(
		          (libuna_utf16_character_t *) name,
		          name_length + 1,
		          &( data_file_descriptor->name_size ),
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_byte_stream_size_from_utf32(
		          (libuna_utf32_character_t *) name,
		          name_length + 1,
		          libclocale_codepage,
		          &( data_file_descriptor->name_size ),
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_byte_stream_size_from_utf16(
		          (libuna_utf16_character_t *) name,
		          name_length + 1,
		          libclocale_codepage,
		          &( data_file_descriptor->name_size ),
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
		 "%s: unable to determine name size.",
		 function );

		return( -1 );
	}
#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */
	data_file_descriptor->name = system_string_allocate(
	                              data_file_descriptor->name_size );

	if( data_file_descriptor->name == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create name.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( system_string_copy(
	     data_file_descriptor->name,
	     name,
	     name_length ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to set name.",
		 function );

		memory_free(
		 data_file_descriptor->name );

		data_file_descriptor->name      = NULL;
		data_file_descriptor->name_size = 0;

		return( -1 );
	}
	data_file_descriptor->name[ name_length ] = 0;
#else
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf8_string_copy_from_utf32(
		          (libuna_utf8_character_t *) data_file_descriptor->name,
		          data_file_descriptor->name_size,
		          (libuna_utf32_character_t *) name,
		          name_length + 1,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf8_string_copy_from_utf16(
		          (libuna_utf8_character_t *) data_file_descriptor->name,
		          data_file_descriptor->name_size,
		          (libuna_utf16_character_t *) name,
		          name_length + 1,
		          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_byte_stream_copy_from_utf32(
		          (uint8_t *) data_file_descriptor->name,
		          data_file_descriptor->name_size,
		          libclocale_codepage,
		          (libuna_utf32_character_t *) name,
		          name_length + 1,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_byte_stream_copy_from_utf16(
		          (uint8_t *) data_file_descriptor->name,
		          data_file_descriptor->name_size,
		          libclocale_codepage,
		          (libuna_utf16_character_t *) name,
		          name_length + 1,
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
		 "%s: unable to set name.",
		 function );

		memory_free(
		 data_file_descriptor->name );

		data_file_descriptor->name      = NULL;
		data_file_descriptor->name_size = 0;

		return( -1 );
	}
#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */
	return( 1 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

