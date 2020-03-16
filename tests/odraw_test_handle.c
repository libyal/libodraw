/*
 * Library handle type test program
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
#include <file_stream.h>
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "odraw_test_functions.h"
#include "odraw_test_getopt.h"
#include "odraw_test_libcerror.h"
#include "odraw_test_libodraw.h"
#include "odraw_test_macros.h"
#include "odraw_test_memory.h"

#include "../libodraw/libodraw_handle.h"

#if defined( HAVE_WIDE_SYSTEM_CHARACTER ) && SIZEOF_WCHAR_T != 2 && SIZEOF_WCHAR_T != 4
#error Unsupported size of wchar_t
#endif

/* Define to make odraw_test_handle generate verbose output
#define ODRAW_TEST_HANDLE_VERBOSE
 */

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
	if( libodraw_handle_open_data_files(
	     *handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open data files.",
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
	libcerror_error_t *error        = NULL;
	libodraw_handle_t *handle       = NULL;
	int result                      = 0;

#if defined( HAVE_ODRAW_TEST_MEMORY )
	int number_of_malloc_fail_tests = 1;
	int number_of_memset_fail_tests = 1;
	int test_number                 = 0;
#endif

	/* Test regular cases
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

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libodraw_handle_initialize with malloc failing
		 */
		odraw_test_malloc_attempts_before_fail = test_number;

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
	}
	for( test_number = 0;
	     test_number < number_of_memset_fail_tests;
	     test_number++ )
	{
		/* Test libodraw_handle_initialize with memset failing
		 */
		odraw_test_memset_attempts_before_fail = test_number;

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

/* Tests the libodraw_handle_open function
 * Returns 1 if successful or 0 if not
 */
int odraw_test_handle_open(
     const system_character_t *source )
{
	char narrow_source[ 256 ];

	libcerror_error_t *error  = NULL;
	libodraw_handle_t *handle = NULL;
	int result                = 0;

	/* Initialize test
	 */
	result = odraw_test_get_narrow_source(
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

	/* Test error cases
	 */
	result = libodraw_handle_open(
	          handle,
	          narrow_source,
	          LIBODRAW_OPEN_READ,
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

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Tests the libodraw_handle_open_wide function
 * Returns 1 if successful or 0 if not
 */
int odraw_test_handle_open_wide(
     const system_character_t *source )
{
	wchar_t wide_source[ 256 ];

	libcerror_error_t *error  = NULL;
	libodraw_handle_t *handle = NULL;
	int result                = 0;

	/* Initialize test
	 */
	result = odraw_test_get_wide_source(
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

	/* Test error cases
	 */
	result = libodraw_handle_open_wide(
	          handle,
	          wide_source,
	          LIBODRAW_OPEN_READ,
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

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Tests the libodraw_handle_close function
 * Returns 1 if successful or 0 if not
 */
int odraw_test_handle_close(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libodraw_handle_close(
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

/* Tests the libodraw_handle_open and libodraw_handle_close functions
 * Returns 1 if successful or 0 if not
 */
int odraw_test_handle_open_close(
     const system_character_t *source )
{
	libcerror_error_t *error  = NULL;
	libodraw_handle_t *handle = NULL;
	int result                = 0;

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

	/* Test open and close
	 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libodraw_handle_open_wide(
	          handle,
	          source,
	          LIBODRAW_OPEN_READ,
	          &error );
#else
	result = libodraw_handle_open(
	          handle,
	          source,
	          LIBODRAW_OPEN_READ,
	          &error );
#endif

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	ODRAW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

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

	/* Test open and close a second time to validate clean up on close
	 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libodraw_handle_open_wide(
	          handle,
	          source,
	          LIBODRAW_OPEN_READ,
	          &error );
#else
	result = libodraw_handle_open(
	          handle,
	          source,
	          LIBODRAW_OPEN_READ,
	          &error );
#endif

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	ODRAW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

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

/* Tests the libodraw_handle_signal_abort function
 * Returns 1 if successful or 0 if not
 */
int odraw_test_handle_signal_abort(
     libodraw_handle_t *handle )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libodraw_handle_signal_abort(
	          handle,
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
	result = libodraw_handle_signal_abort(
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

/* Tests the libodraw_handle_read_buffer function
 * Returns 1 if successful or 0 if not
 */
int odraw_test_handle_read_buffer(
     libodraw_handle_t *handle )
{
	uint8_t buffer[ 128 ];

	libcerror_error_t *error = NULL;
	off64_t offset           = 0;
	ssize_t read_count       = 0;

	/* Test regular cases
	 */
	read_count = libodraw_handle_read_buffer(
	              handle,
	              buffer,
	              16,
	              &error );

	ODRAW_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) 16 );

	ODRAW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Reset offset to 0
	 */
	offset = libodraw_handle_seek_offset(
	          handle,
	          0,
	          SEEK_SET,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) 0 );

	ODRAW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	read_count = libodraw_handle_read_buffer(
	              NULL,
	              buffer,
	              16,
	              &error );

	ODRAW_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	ODRAW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	read_count = libodraw_handle_read_buffer(
	              handle,
	              NULL,
	              16,
	              &error );

	ODRAW_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	ODRAW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	read_count = libodraw_handle_read_buffer(
	              handle,
	              buffer,
	              (size_t) SSIZE_MAX + 1,
	              &error );

	ODRAW_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

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

/* Tests the libodraw_handle_seek_offset function
 * Returns 1 if successful or 0 if not
 */
int odraw_test_handle_seek_offset(
     libodraw_handle_t *handle )
{
	libcerror_error_t *error = NULL;
	off64_t offset           = 0;
	size64_t size            = 0;

	/* Test regular cases
	 */
	offset = libodraw_handle_seek_offset(
	          handle,
	          1024,
	          SEEK_SET,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) 1024 );

	ODRAW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	offset = libodraw_handle_seek_offset(
	          handle,
	          -512,
	          SEEK_CUR,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) 512 );

	ODRAW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	offset = libodraw_handle_seek_offset(
	          handle,
	          0,
	          SEEK_END,
	          &error );

	ODRAW_TEST_ASSERT_NOT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) -1 );

	ODRAW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	size = (size64_t) offset;

	offset = libodraw_handle_seek_offset(
	          handle,
	          (off64_t) ( size + 512 ),
	          SEEK_SET,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) ( size + 512 ) );

	ODRAW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Reset offset to 0
	 */
	offset = libodraw_handle_seek_offset(
	          handle,
	          0,
	          SEEK_SET,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) 0 );

	ODRAW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	offset = libodraw_handle_seek_offset(
	          NULL,
	          0,
	          SEEK_SET,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) -1 );

	ODRAW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	offset = libodraw_handle_seek_offset(
	          handle,
	          -1,
	          SEEK_SET,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) -1 );

	ODRAW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	offset = libodraw_handle_seek_offset(
	          handle,
	          -1,
	          SEEK_CUR,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) -1 );

	ODRAW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	offset = libodraw_handle_seek_offset(
	          handle,
	          (off64_t) ( -1 * ( size + 1 ) ),
	          SEEK_END,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) -1 );

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

/* Tests the libodraw_handle_get_offset function
 * Returns 1 if successful or 0 if not
 */
int odraw_test_handle_get_offset(
     libodraw_handle_t *handle )
{
	libcerror_error_t *error = NULL;
	off64_t offset           = 0;
	int offset_is_set        = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libodraw_handle_get_offset(
	          handle,
	          &offset,
	          &error );

	ODRAW_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	ODRAW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	offset_is_set = result;

	/* Test error cases
	 */
	result = libodraw_handle_get_offset(
	          NULL,
	          &offset,
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

	if( offset_is_set != 0 )
	{
		result = libodraw_handle_get_offset(
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

#if defined( __GNUC__ ) && !defined( LIBODRAW_DLL_IMPORT )

/* Tests the libodraw_handle_get_basename_size function
 * Returns 1 if successful or 0 if not
 */
int odraw_test_handle_get_basename_size(
     libodraw_handle_t *handle )
{
	libcerror_error_t *error = NULL;
	size_t basename_size     = 0;
	int basename_size_is_set = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libodraw_handle_get_basename_size(
	          (libodraw_internal_handle_t *) handle,
	          &basename_size,
	          &error );

	ODRAW_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	ODRAW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	basename_size_is_set = result;

	/* Test error cases
	 */
	result = libodraw_handle_get_basename_size(
	          NULL,
	          &basename_size,
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

	if( basename_size_is_set != 0 )
	{
		result = libodraw_handle_get_basename_size(
		          (libodraw_internal_handle_t *) handle,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Tests the libodraw_handle_get_basename_size_wide function
 * Returns 1 if successful or 0 if not
 */
int odraw_test_handle_get_basename_size_wide(
     libodraw_handle_t *handle )
{
	libcerror_error_t *error      = NULL;
	size_t basename_size_wide     = 0;
	int basename_size_wide_is_set = 0;
	int result                    = 0;

	/* Test regular cases
	 */
	result = libodraw_handle_get_basename_size_wide(
	          (libodraw_internal_handle_t *) handle,
	          &basename_size_wide,
	          &error );

	ODRAW_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	ODRAW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	basename_size_wide_is_set = result;

	/* Test error cases
	 */
	result = libodraw_handle_get_basename_size_wide(
	          NULL,
	          &basename_size_wide,
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

	if( basename_size_wide_is_set != 0 )
	{
		result = libodraw_handle_get_basename_size_wide(
		          (libodraw_internal_handle_t *) handle,
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

#endif /* defined( __GNUC__ ) && !defined( LIBODRAW_DLL_IMPORT ) */

/* Tests the libodraw_handle_get_ascii_codepage function
 * Returns 1 if successful or 0 if not
 */
int odraw_test_handle_get_ascii_codepage(
     libodraw_handle_t *handle )
{
	libcerror_error_t *error  = NULL;
	int ascii_codepage        = 0;
	int ascii_codepage_is_set = 0;
	int result                = 0;

	/* Test regular cases
	 */
	result = libodraw_handle_get_ascii_codepage(
	          handle,
	          &ascii_codepage,
	          &error );

	ODRAW_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	ODRAW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	ascii_codepage_is_set = result;

	/* Test error cases
	 */
	result = libodraw_handle_get_ascii_codepage(
	          NULL,
	          &ascii_codepage,
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

	if( ascii_codepage_is_set != 0 )
	{
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
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libodraw_handle_set_ascii_codepage function
 * Returns 1 if successful or 0 if not
 */
int odraw_test_handle_set_ascii_codepage(
     libodraw_handle_t *handle )
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
	int codepage             = 0;
	int index                = 0;
	int result               = 0;

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
	result = libodraw_handle_set_ascii_codepage(
	          handle,
	          LIBODRAW_CODEPAGE_WINDOWS_1252,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

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
	return( 0 );
}

/* Tests the libodraw_handle_get_number_of_data_files function
 * Returns 1 if successful or 0 if not
 */
int odraw_test_handle_get_number_of_data_files(
     libodraw_handle_t *handle )
{
	libcerror_error_t *error        = NULL;
	int number_of_data_files        = 0;
	int number_of_data_files_is_set = 0;
	int result                      = 0;

	/* Test regular cases
	 */
	result = libodraw_handle_get_number_of_data_files(
	          handle,
	          &number_of_data_files,
	          &error );

	ODRAW_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	ODRAW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	number_of_data_files_is_set = result;

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

	if( number_of_data_files_is_set != 0 )
	{
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
	}
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
	libodraw_handle_t *handle  = NULL;
	system_character_t *source = NULL;
	system_integer_t option    = 0;
	int result                 = 0;

	while( ( option = odraw_test_getopt(
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

		ODRAW_TEST_RUN(
		 "libodraw_handle_close",
		 odraw_test_handle_close );

		ODRAW_TEST_RUN_WITH_ARGS(
		 "libodraw_handle_open_close",
		 odraw_test_handle_open_close,
		 source );

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
		 "libodraw_handle_signal_abort",
		 odraw_test_handle_signal_abort,
		 handle );

		/* TODO: add tests for libodraw_handle_open_data_files */

		/* TODO: add tests for libodraw_handle_open_data_files_file_io_pool */

#if defined( __GNUC__ ) && !defined( LIBODRAW_DLL_IMPORT )

		/* TODO: add tests for libodraw_handle_open_data_file */

		/* TODO: add tests for libodraw_handle_open_data_file_wide */

		/* TODO: add tests for libodraw_handle_open_data_file_io_handle */

		/* TODO: add tests for libodraw_handle_open_read */

#endif /* defined( __GNUC__ ) && !defined( LIBODRAW_DLL_IMPORT ) */

		ODRAW_TEST_RUN_WITH_ARGS(
		 "libodraw_handle_read_buffer",
		 odraw_test_handle_read_buffer,
		 handle );

#if defined( __GNUC__ ) && !defined( LIBODRAW_DLL_IMPORT )

		/* TODO: add tests for libodraw_handle_read_buffer_from_run_out */

		/* TODO: add tests for libodraw_handle_read_buffer_from_lead_out */

		/* TODO: add tests for libodraw_handle_read_buffer_from_unspecified_sector */

		/* TODO: add tests for libodraw_handle_read_buffer_from_track */

#endif /* defined( __GNUC__ ) && !defined( LIBODRAW_DLL_IMPORT ) */

		/* TODO: add tests for libodraw_handle_read_buffer_at_offset */

		/* TODO: add tests for libodraw_handle_write_buffer */

		/* TODO: add tests for libodraw_handle_write_buffer_at_offset */

		ODRAW_TEST_RUN_WITH_ARGS(
		 "libodraw_handle_seek_offset",
		 odraw_test_handle_seek_offset,
		 handle );

#if defined( __GNUC__ ) && !defined( LIBODRAW_DLL_IMPORT )

		/* TODO: add tests for libodraw_handle_get_run_out_at_offset */

		/* TODO: add tests for libodraw_handle_get_lead_out_at_offset */

		/* TODO: add tests for libodraw_handle_get_track_at_offset */

#endif /* defined( __GNUC__ ) && !defined( LIBODRAW_DLL_IMPORT ) */

		ODRAW_TEST_RUN_WITH_ARGS(
		 "libodraw_handle_get_offset",
		 odraw_test_handle_get_offset,
		 handle );

#if defined( __GNUC__ ) && !defined( LIBODRAW_DLL_IMPORT )

		ODRAW_TEST_RUN_WITH_ARGS(
		 "libodraw_handle_get_basename_size",
		 odraw_test_handle_get_basename_size,
		 handle );

		/* TODO: add tests for libodraw_handle_get_basename */

		/* TODO: add tests for libodraw_handle_set_basename */

#if defined( HAVE_WIDE_CHARACTER_TYPE )

		ODRAW_TEST_RUN_WITH_ARGS(
		 "libodraw_handle_get_basename_size_wide",
		 odraw_test_handle_get_basename_size_wide,
		 handle );

		/* TODO: add tests for libodraw_handle_get_basename_wide */

		/* TODO: add tests for libodraw_handle_set_basename_wide */

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

#endif /* defined( __GNUC__ ) && !defined( LIBODRAW_DLL_IMPORT ) */

		/* TODO: add tests for libodraw_handle_set_maximum_number_of_open_handles */

#if defined( __GNUC__ ) && !defined( LIBODRAW_DLL_IMPORT )

		/* TODO: add tests for libodraw_handle_set_media_values */

#endif /* defined( __GNUC__ ) && !defined( LIBODRAW_DLL_IMPORT ) */

		ODRAW_TEST_RUN_WITH_ARGS(
		 "libodraw_handle_get_ascii_codepage",
		 odraw_test_handle_get_ascii_codepage,
		 handle );

		ODRAW_TEST_RUN_WITH_ARGS(
		 "libodraw_handle_set_ascii_codepage",
		 odraw_test_handle_set_ascii_codepage,
		 handle );

		ODRAW_TEST_RUN_WITH_ARGS(
		 "libodraw_handle_get_number_of_data_files",
		 odraw_test_handle_get_number_of_data_files,
		 handle );

		/* TODO: add tests for libodraw_handle_get_data_file */

		/* TODO: add tests for libodraw_handle_append_data_file */

		/* TODO: add tests for libodraw_handle_append_data_file_wide */

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

