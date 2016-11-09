/*
 * Library handle type testing program
 *
 * Copyright (C) 2010-2016, Joachim Metz <joachim.metz@gmail.com>
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

#include <common.h>
#include <file_stream.h>
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "odraw_test_libcerror.h"
#include "odraw_test_libclocale.h"
#include "odraw_test_libcsystem.h"
#include "odraw_test_libodraw.h"
#include "odraw_test_libuna.h"
#include "odraw_test_macros.h"
#include "odraw_test_memory.h"

#if SIZEOF_WCHAR_T != 2 && SIZEOF_WCHAR_T != 4
#error Unsupported size of wchar_t
#endif

/* Define to make odraw_test_handle generate verbose output
#define ODRAW_TEST_HANDLE_VERBOSE
 */

/* Retrieves source as a narrow string
 * Returns 1 if successful or -1 on error
 */
int odraw_test_handle_get_narrow_source(
     const system_character_t *source,
     char *narrow_string,
     size_t narrow_string_size,
     libcerror_error_t **error )
{
	static char *function     = "odraw_test_handle_get_narrow_source";
	size_t narrow_source_size = 0;
	size_t source_length      = 0;

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	int result                = 0;
#endif

	if( source == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid source.",
		 function );

		return( -1 );
	}
	if( narrow_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid narrow string.",
		 function );

		return( -1 );
	}
	if( narrow_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid narrow string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	source_length = system_string_length(
	                 source );

	if( source_length > (size_t) ( SSIZE_MAX - 1 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid source length value out of bounds.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf8_string_size_from_utf32(
		          (libuna_utf32_character_t *) source,
		          source_length + 1,
		          &narrow_source_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf8_string_size_from_utf16(
		          (libuna_utf16_character_t *) source,
		          source_length + 1,
		          &narrow_source_size,
		          error );
#endif
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_byte_stream_size_from_utf32(
		          (libuna_utf32_character_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          &narrow_source_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_byte_stream_size_from_utf16(
		          (libuna_utf16_character_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          &narrow_source_size,
		          error );
#endif
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine narrow string size.",
		 function );

		return( -1 );
	}
#else
	narrow_source_size = source_length + 1;

#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

	if( narrow_string_size < narrow_source_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: narrow string too small.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf8_string_copy_from_utf32(
		          (libuna_utf8_character_t *) narrow_string,
		          narrow_string_size,
		          (libuna_utf32_character_t *) source,
		          source_length + 1,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf8_string_copy_from_utf16(
		          (libuna_utf8_character_t *) narrow_string,
		          narrow_string_size,
		          (libuna_utf16_character_t *) source,
		          source_length + 1,
		          error );
#endif
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_byte_stream_copy_from_utf32(
		          (uint8_t *) narrow_string,
		          narrow_string_size,
		          libclocale_codepage,
		          (libuna_utf32_character_t *) source,
		          source_length + 1,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_byte_stream_copy_from_utf16(
		          (uint8_t *) narrow_string,
		          narrow_string_size,
		          libclocale_codepage,
		          (libuna_utf16_character_t *) source,
		          source_length + 1,
		          error );
#endif
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set narrow string.",
		 function );

		return( -1 );
	}
#else
	if( system_string_copy(
	     narrow_string,
	     source,
	     source_length ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to set narrow string.",
		 function );

		return( -1 );
	}
	narrow_string[ source_length ] = 0;

#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

	return( 1 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Retrieves source as a wide string
 * Returns 1 if successful or -1 on error
 */
int odraw_test_handle_get_wide_source(
     const system_character_t *source,
     wchar_t *wide_string,
     size_t wide_string_size,
     libcerror_error_t **error )
{
	static char *function   = "odraw_test_handle_get_wide_source";
	size_t wide_source_size = 0;
	size_t source_length    = 0;

#if !defined( HAVE_WIDE_SYSTEM_CHARACTER )
	int result              = 0;
#endif

	if( source == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid source.",
		 function );

		return( -1 );
	}
	if( wide_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid wide string.",
		 function );

		return( -1 );
	}
	if( wide_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid wide string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	source_length = system_string_length(
	                 source );

	if( source_length > (size_t) ( SSIZE_MAX - 1 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid source length value out of bounds.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	wide_source_size = source_length + 1;
#else
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_size_from_utf8(
		          (libuna_utf8_character_t *) source,
		          source_length + 1,
		          &wide_source_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_size_from_utf8(
		          (libuna_utf8_character_t *) source,
		          source_length + 1,
		          &wide_source_size,
		          error );
#endif
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_size_from_byte_stream(
		          (uint8_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          &wide_source_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_size_from_byte_stream(
		          (uint8_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          &wide_source_size,
		          error );
#endif
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine wide string size.",
		 function );

		return( -1 );
	}

#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

	if( wide_string_size < wide_source_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: wide string too small.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( system_string_copy(
	     wide_string,
	     source,
	     source_length ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to set wide string.",
		 function );

		return( -1 );
	}
	wide_string[ source_length ] = 0;
#else
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_copy_from_utf8(
		          (libuna_utf32_character_t *) wide_string,
		          wide_string_size,
		          (libuna_utf8_character_t *) source,
		          source_length + 1,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_copy_from_utf8(
		          (libuna_utf16_character_t *) wide_string,
		          wide_string_size,
		          (libuna_utf8_character_t *) source,
		          source_length + 1,
		          error );
#endif
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_copy_from_byte_stream(
		          (libuna_utf32_character_t *) wide_string,
		          wide_string_size,
		          (uint8_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_copy_from_byte_stream(
		          (libuna_utf16_character_t *) wide_string,
		          wide_string_size,
		          (uint8_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          error );
#endif
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set wide string.",
		 function );

		return( -1 );
	}

#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

	return( 1 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Creates and opens a source handle
 * Returns 1 if successful or -1 on error
 */
int odraw_test_handle_open_source(
     libodraw_handle_t **handle,
     const system_character_t *source,
     libcerror_error_t **error )
{
	static char *function = "odraw_test_handle_open_source";
	int result            = 0;

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
	if( source == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid source.",
		 function );

		return( -1 );
	}
	if( libodraw_handle_initialize(
	     handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize handle.",
		 function );

		goto on_error;
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libodraw_handle_open_wide(
	          *handle,
	          source,
	          LIBODRAW_OPEN_READ,
	          error );
#else
	result = libodraw_handle_open(
	          *handle,
	          source,
	          LIBODRAW_OPEN_READ,
	          error );
#endif
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open handle.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *handle != NULL )
	{
		libodraw_handle_free(
		 handle,
		 NULL );
	}
	return( -1 );
}

/* Closes and frees a source handle
 * Returns 1 if successful or -1 on error
 */
int odraw_test_handle_close_source(
     libodraw_handle_t **handle,
     libcerror_error_t **error )
{
	static char *function = "odraw_test_handle_close_source";
	int result            = 0;

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
	if( libodraw_handle_free(
	     handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free handle.",
		 function );

		result = -1;
	}
	return( result );
}

/* Tests the libodraw_handle_initialize function
 * Returns 1 if successful or 0 if not
 */
int odraw_test_handle_initialize(
     void )
{
	libcerror_error_t *error = NULL;
	libodraw_handle_t *handle      = NULL;
	int result               = 0;

	/* Test libodraw_handle_initialize
	 */
	result = libodraw_handle_initialize(
	          &handle,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        ODRAW_TEST_ASSERT_IS_NOT_NULL(
         "handle",
         handle );

        ODRAW_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libodraw_handle_free(
	          &handle,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        ODRAW_TEST_ASSERT_IS_NULL(
         "handle",
         handle );

        ODRAW_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libodraw_handle_initialize(
	          NULL,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        ODRAW_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	handle = (libodraw_handle_t *) 0x12345678UL;

	result = libodraw_handle_initialize(
	          &handle,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        ODRAW_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	handle = NULL;

#if defined( HAVE_ODRAW_TEST_MEMORY )

	/* Test libodraw_handle_initialize with malloc failing
	 */
	odraw_test_malloc_attempts_before_fail = 0;

	result = libodraw_handle_initialize(
	          &handle,
	          &error );

	if( odraw_test_malloc_attempts_before_fail != -1 )
	{
		odraw_test_malloc_attempts_before_fail = -1;

		if( handle != NULL )
		{
			libodraw_handle_free(
			 &handle,
			 NULL );
		}
	}
	else
	{
		ODRAW_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		ODRAW_TEST_ASSERT_IS_NULL(
		 "handle",
		 handle );

		ODRAW_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Test libodraw_handle_initialize with memset failing
	 */
	odraw_test_memset_attempts_before_fail = 0;

	result = libodraw_handle_initialize(
	          &handle,
	          &error );

	if( odraw_test_memset_attempts_before_fail != -1 )
	{
		odraw_test_memset_attempts_before_fail = -1;

		if( handle != NULL )
		{
			libodraw_handle_free(
			 &handle,
			 NULL );
		}
	}
	else
	{
		ODRAW_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		ODRAW_TEST_ASSERT_IS_NULL(
		 "handle",
		 handle );

		ODRAW_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_ODRAW_TEST_MEMORY ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( handle != NULL )
	{
		libodraw_handle_free(
		 &handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libodraw_handle_free function
 * Returns 1 if successful or 0 if not
 */
int odraw_test_handle_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libodraw_handle_free(
	          NULL,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        ODRAW_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libodraw_handle_open functions
 * Returns 1 if successful or 0 if not
 */
int odraw_test_handle_open(
     const system_character_t *source )
{
	char narrow_source[ 256 ];

	libcerror_error_t *error = NULL;
	libodraw_handle_t *handle      = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = odraw_test_handle_get_narrow_source(
	          source,
	          narrow_source,
	          256,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        ODRAW_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libodraw_handle_initialize(
	          &handle,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        ODRAW_TEST_ASSERT_IS_NOT_NULL(
         "handle",
         handle );

        ODRAW_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test open
	 */
	result = libodraw_handle_open(
	          handle,
	          narrow_source,
	          LIBODRAW_OPEN_READ,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        ODRAW_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Clean up
	 */
	result = libodraw_handle_close(
	          handle,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

        ODRAW_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libodraw_handle_free(
	          &handle,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        ODRAW_TEST_ASSERT_IS_NULL(
         "handle",
         handle );

        ODRAW_TEST_ASSERT_IS_NULL(
         "error",
         error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( handle != NULL )
	{
		libodraw_handle_free(
		 &handle,
		 NULL );
	}
	return( 0 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Tests the libodraw_handle_open_wide functions
 * Returns 1 if successful or 0 if not
 */
int odraw_test_handle_open_wide(
     const system_character_t *source )
{
	wchar_t wide_source[ 256 ];

	libcerror_error_t *error = NULL;
	libodraw_handle_t *handle      = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = odraw_test_handle_get_wide_source(
	          source,
	          wide_source,
	          256,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        ODRAW_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libodraw_handle_initialize(
	          &handle,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        ODRAW_TEST_ASSERT_IS_NOT_NULL(
         "handle",
         handle );

        ODRAW_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test open
	 */
	result = libodraw_handle_open_wide(
	          handle,
	          wide_source,
	          LIBODRAW_OPEN_READ,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        ODRAW_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Clean up
	 */
	result = libodraw_handle_close(
	          handle,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

        ODRAW_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libodraw_handle_free(
	          &handle,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        ODRAW_TEST_ASSERT_IS_NULL(
         "handle",
         handle );

        ODRAW_TEST_ASSERT_IS_NULL(
         "error",
         error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( handle != NULL )
	{
		libodraw_handle_free(
		 &handle,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Tests the libodraw_handle_get_ascii_codepage functions
 * Returns 1 if successful or 0 if not
 */
int odraw_test_handle_get_ascii_codepage(
     libodraw_handle_t *handle )
{
	libcerror_error_t *error = NULL;
	int codepage             = 0;
	int result               = 0;

	result = libodraw_handle_get_ascii_codepage(
	          handle,
	          &codepage,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        ODRAW_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libodraw_handle_get_ascii_codepage(
	          NULL,
	          &codepage,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        ODRAW_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	result = libodraw_handle_get_ascii_codepage(
	          handle,
	          NULL,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        ODRAW_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libodraw_handle_set_ascii_codepage functions
 * Returns 1 if successful or 0 if not
 */
int odraw_test_handle_set_ascii_codepage(
     void )
{
	int supported_codepages[ 15 ] = {
		LIBODRAW_CODEPAGE_ASCII,
		LIBODRAW_CODEPAGE_WINDOWS_874,
		LIBODRAW_CODEPAGE_WINDOWS_932,
		LIBODRAW_CODEPAGE_WINDOWS_936,
		LIBODRAW_CODEPAGE_WINDOWS_949,
		LIBODRAW_CODEPAGE_WINDOWS_950,
		LIBODRAW_CODEPAGE_WINDOWS_1250,
		LIBODRAW_CODEPAGE_WINDOWS_1251,
		LIBODRAW_CODEPAGE_WINDOWS_1252,
		LIBODRAW_CODEPAGE_WINDOWS_1253,
		LIBODRAW_CODEPAGE_WINDOWS_1254,
		LIBODRAW_CODEPAGE_WINDOWS_1255,
		LIBODRAW_CODEPAGE_WINDOWS_1256,
		LIBODRAW_CODEPAGE_WINDOWS_1257,
		LIBODRAW_CODEPAGE_WINDOWS_1258 };

	int unsupported_codepages[ 17 ] = {
		LIBODRAW_CODEPAGE_ISO_8859_1,
		LIBODRAW_CODEPAGE_ISO_8859_2,
		LIBODRAW_CODEPAGE_ISO_8859_3,
		LIBODRAW_CODEPAGE_ISO_8859_4,
		LIBODRAW_CODEPAGE_ISO_8859_5,
		LIBODRAW_CODEPAGE_ISO_8859_6,
		LIBODRAW_CODEPAGE_ISO_8859_7,
		LIBODRAW_CODEPAGE_ISO_8859_8,
		LIBODRAW_CODEPAGE_ISO_8859_9,
		LIBODRAW_CODEPAGE_ISO_8859_10,
		LIBODRAW_CODEPAGE_ISO_8859_11,
		LIBODRAW_CODEPAGE_ISO_8859_13,
		LIBODRAW_CODEPAGE_ISO_8859_14,
		LIBODRAW_CODEPAGE_ISO_8859_15,
		LIBODRAW_CODEPAGE_ISO_8859_16,
		LIBODRAW_CODEPAGE_KOI8_R,
		LIBODRAW_CODEPAGE_KOI8_U };

	libcerror_error_t *error = NULL;
	libodraw_handle_t *handle      = NULL;
	int codepage             = 0;
	int index                = 0;
	int result               = 0;

	/* Initialize test
	 */
	result = libodraw_handle_initialize(
	          &handle,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        ODRAW_TEST_ASSERT_IS_NOT_NULL(
         "handle",
         handle );

        ODRAW_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test set ASCII codepage
	 */
	for( index = 0;
	     index < 15;
	     index++ )
	{
		codepage = supported_codepages[ index ];

		result = libodraw_handle_set_ascii_codepage(
		          handle,
		          codepage,
		          &error );

		ODRAW_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

	        ODRAW_TEST_ASSERT_IS_NULL(
	         "error",
	         error );
	}
	/* Test error cases
	 */
	result = libodraw_handle_set_ascii_codepage(
	          NULL,
	          LIBODRAW_CODEPAGE_ASCII,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        ODRAW_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	for( index = 0;
	     index < 17;
	     index++ )
	{
		codepage = unsupported_codepages[ index ];

		result = libodraw_handle_set_ascii_codepage(
		          handle,
		          codepage,
		          &error );

		ODRAW_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

	        ODRAW_TEST_ASSERT_IS_NOT_NULL(
	         "error",
	         error );

		libcerror_error_free(
		 &error );
	}
	/* Clean up
	 */
	result = libodraw_handle_free(
	          &handle,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        ODRAW_TEST_ASSERT_IS_NULL(
         "handle",
         handle );

        ODRAW_TEST_ASSERT_IS_NULL(
         "error",
         error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( handle != NULL )
	{
		libodraw_handle_free(
		 &handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libodraw_handle_get_number_of_data_files functions
 * Returns 1 if successful or 0 if not
 */
int odraw_test_handle_get_number_of_data_files(
     libodraw_handle_t *handle )
{
	libcerror_error_t *error = NULL;
	int number_of_data_files    = 0;
	int result               = 0;

	result = libodraw_handle_get_number_of_data_files(
	          handle,
	          &number_of_data_files,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        ODRAW_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libodraw_handle_get_number_of_data_files(
	          NULL,
	          &number_of_data_files,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        ODRAW_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	result = libodraw_handle_get_number_of_data_files(
	          handle,
	          NULL,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        ODRAW_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libodraw_handle_get_number_of_sectors functions
 * Returns 1 if successful or 0 if not
 */
int odraw_test_handle_get_number_of_sectors(
     libodraw_handle_t *handle )
{
	libcerror_error_t *error   = NULL;
	uint16_t number_of_sectors = 0;
	int result                 = 0;

	result = libodraw_handle_get_number_of_sectors(
	          handle,
	          &number_of_sectors,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        ODRAW_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libodraw_handle_get_number_of_sectors(
	          NULL,
	          &number_of_sectors,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        ODRAW_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	result = libodraw_handle_get_number_of_sectors(
	          handle,
	          NULL,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        ODRAW_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libodraw_handle_get_number_of_sessions functions
 * Returns 1 if successful or 0 if not
 */
int odraw_test_handle_get_number_of_sessions(
     libodraw_handle_t *handle )
{
	libcerror_error_t *error = NULL;
	int number_of_sessions    = 0;
	int result               = 0;

	result = libodraw_handle_get_number_of_sessions(
	          handle,
	          &number_of_sessions,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        ODRAW_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libodraw_handle_get_number_of_sessions(
	          NULL,
	          &number_of_sessions,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        ODRAW_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	result = libodraw_handle_get_number_of_sessions(
	          handle,
	          NULL,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        ODRAW_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libodraw_handle_get_number_of_lead_outs functions
 * Returns 1 if successful or 0 if not
 */
int odraw_test_handle_get_number_of_lead_outs(
     libodraw_handle_t *handle )
{
	libcerror_error_t *error = NULL;
	int number_of_lead_outs    = 0;
	int result               = 0;

	result = libodraw_handle_get_number_of_lead_outs(
	          handle,
	          &number_of_lead_outs,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        ODRAW_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libodraw_handle_get_number_of_lead_outs(
	          NULL,
	          &number_of_lead_outs,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        ODRAW_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	result = libodraw_handle_get_number_of_lead_outs(
	          handle,
	          NULL,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        ODRAW_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libodraw_handle_get_number_of_tracks functions
 * Returns 1 if successful or 0 if not
 */
int odraw_test_handle_get_number_of_tracks(
     libodraw_handle_t *handle )
{
	libcerror_error_t *error = NULL;
	int number_of_tracks    = 0;
	int result               = 0;

	result = libodraw_handle_get_number_of_tracks(
	          handle,
	          &number_of_tracks,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        ODRAW_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libodraw_handle_get_number_of_tracks(
	          NULL,
	          &number_of_tracks,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        ODRAW_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	result = libodraw_handle_get_number_of_tracks(
	          handle,
	          NULL,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        ODRAW_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc,
     wchar_t * const argv[] )
#else
int main(
     int argc,
     char * const argv[] )
#endif
{
	libcerror_error_t *error   = NULL;
	system_character_t *source = NULL;
	libodraw_handle_t *handle        = NULL;
	system_integer_t option    = 0;
	int result                 = 0;

	while( ( option = libcsystem_getopt(
	                   argc,
	                   argv,
	                   _SYSTEM_STRING( "" ) ) ) != (system_integer_t) -1 )
	{
		switch( option )
		{
			case (system_integer_t) '?':
			default:
				fprintf(
				 stderr,
				 "Invalid argument: %" PRIs_SYSTEM ".\n",
				 argv[ optind - 1 ] );

				return( EXIT_FAILURE );
		}
	}
	if( optind < argc )
	{
		source = argv[ optind ];
	}
#if defined( HAVE_DEBUG_OUTPUT ) && defined( ODRAW_TEST_HANDLE_VERBOSE )
	libodraw_notify_set_verbose(
	 1 );
	libodraw_notify_set_stream(
	 stderr,
	 NULL );
#endif

	ODRAW_TEST_RUN(
	 "libodraw_handle_initialize",
	 odraw_test_handle_initialize );

	ODRAW_TEST_RUN(
	 "libodraw_handle_free",
	 odraw_test_handle_free );

	ODRAW_TEST_RUN(
	 "libodraw_handle_set_ascii_codepage",
	 odraw_test_handle_set_ascii_codepage );

#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )
	if( source != NULL )
	{
		ODRAW_TEST_RUN_WITH_ARGS(
		 "libodraw_handle_open",
		 odraw_test_handle_open,
		 source );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

		ODRAW_TEST_RUN_WITH_ARGS(
		 "libodraw_handle_open_wide",
		 odraw_test_handle_open_wide,
		 source );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

#if defined( LIBODRAW_HAVE_BFIO )

		/* TODO add test for libodraw_handle_open_file_io_handle */

#endif /* defined( LIBODRAW_HAVE_BFIO ) */

		/* TODO add test for libodraw_handle_close */

		/* Initialize test
		 */
		result = odraw_test_handle_open_source(
		          &handle,
		          source,
		          &error );

		ODRAW_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

	        ODRAW_TEST_ASSERT_IS_NOT_NULL(
	         "handle",
	         handle );

	        ODRAW_TEST_ASSERT_IS_NULL(
	         "error",
	         error );

		ODRAW_TEST_RUN_WITH_ARGS(
		 "libodraw_handle_get_ascii_codepage",
		 odraw_test_handle_get_ascii_codepage,
		 handle );

		ODRAW_TEST_RUN_WITH_ARGS(
		 "libodraw_handle_get_number_of_data_files",
		 odraw_test_handle_get_number_of_data_files,
		 handle );

		ODRAW_TEST_RUN_WITH_ARGS(
		 "libodraw_handle_get_number_of_sectors",
		 odraw_test_handle_get_number_of_sectors,
		 handle );

		ODRAW_TEST_RUN_WITH_ARGS(
		 "libodraw_handle_get_number_of_sessions",
		 odraw_test_handle_get_number_of_sessions,
		 handle );

		ODRAW_TEST_RUN_WITH_ARGS(
		 "libodraw_handle_get_number_of_lead_outs",
		 odraw_test_handle_get_number_of_lead_outs,
		 handle );

		ODRAW_TEST_RUN_WITH_ARGS(
		 "libodraw_handle_get_number_of_tracks",
		 odraw_test_handle_get_number_of_tracks,
		 handle );

		/* Clean up
		 */
		result = odraw_test_handle_close_source(
		          &handle,
		          &error );

		ODRAW_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 0 );

		ODRAW_TEST_ASSERT_IS_NULL(
	         "handle",
	         handle );

	        ODRAW_TEST_ASSERT_IS_NULL(
	         "error",
	         error );
	}
#endif /* !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 ) */

	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( handle != NULL )
	{
		odraw_test_handle_close_source(
		 &handle,
		 NULL );
	}
	return( EXIT_FAILURE );
}

