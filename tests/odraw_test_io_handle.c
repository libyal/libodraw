/*
 * Library io_handle type test program
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

#include <common.h>
#include <file_stream.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#if defined( HAVE_STRING_H ) || defined( WINAPI )
#include <string.h>
#endif

#include "odraw_test_libcerror.h"
#include "odraw_test_libodraw.h"
#include "odraw_test_macros.h"
#include "odraw_test_memory.h"
#include "odraw_test_unused.h"

#include "../libodraw/libodraw_io_handle.h"

#if defined( __GNUC__ ) && !defined( LIBODRAW_DLL_IMPORT )

/* Tests the libodraw_io_handle_initialize function
 * Returns 1 if successful or 0 if not
 */
int odraw_test_io_handle_initialize(
     void )
{
	libcerror_error_t *error        = NULL;
	libodraw_io_handle_t *io_handle = NULL;
	int result                      = 0;

#if defined( HAVE_ODRAW_TEST_MEMORY )
	int number_of_malloc_fail_tests = 1;
	int number_of_memset_fail_tests = 1;
	int test_number                 = 0;
#endif

	/* Test regular cases
	 */
	result = libodraw_io_handle_initialize(
	          &io_handle,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	ODRAW_TEST_ASSERT_IS_NOT_NULL(
	 "io_handle",
	 io_handle );

	ODRAW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libodraw_io_handle_free(
	          &io_handle,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	ODRAW_TEST_ASSERT_IS_NULL(
	 "io_handle",
	 io_handle );

	ODRAW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libodraw_io_handle_initialize(
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

	io_handle = (libodraw_io_handle_t *) 0x12345678UL;

	result = libodraw_io_handle_initialize(
	          &io_handle,
	          &error );

	io_handle = NULL;

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	ODRAW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_ODRAW_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libodraw_io_handle_initialize with malloc failing
		 */
		odraw_test_malloc_attempts_before_fail = test_number;

		result = libodraw_io_handle_initialize(
		          &io_handle,
		          &error );

		if( odraw_test_malloc_attempts_before_fail != -1 )
		{
			odraw_test_malloc_attempts_before_fail = -1;

			if( io_handle != NULL )
			{
				libodraw_io_handle_free(
				 &io_handle,
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
			 "io_handle",
			 io_handle );

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
		/* Test libodraw_io_handle_initialize with memset failing
		 */
		odraw_test_memset_attempts_before_fail = test_number;

		result = libodraw_io_handle_initialize(
		          &io_handle,
		          &error );

		if( odraw_test_memset_attempts_before_fail != -1 )
		{
			odraw_test_memset_attempts_before_fail = -1;

			if( io_handle != NULL )
			{
				libodraw_io_handle_free(
				 &io_handle,
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
			 "io_handle",
			 io_handle );

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
	if( io_handle != NULL )
	{
		libodraw_io_handle_free(
		 &io_handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libodraw_io_handle_free function
 * Returns 1 if successful or 0 if not
 */
int odraw_test_io_handle_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libodraw_io_handle_free(
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

/* Tests the libodraw_io_handle_clear function
 * Returns 1 if successful or 0 if not
 */
int odraw_test_io_handle_clear(
     void )
{
	libcerror_error_t *error        = NULL;
	libodraw_io_handle_t *io_handle = NULL;
	int result                      = 0;

	/* Initialize test
	 */
	result = libodraw_io_handle_initialize(
	          &io_handle,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	ODRAW_TEST_ASSERT_IS_NOT_NULL(
	 "io_handle",
	 io_handle );

	ODRAW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libodraw_io_handle_clear(
	          io_handle,
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
	result = libodraw_io_handle_clear(
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

#if defined( HAVE_ODRAW_TEST_MEMORY )

	/* Test libodraw_io_handle_clear with memset failing
	 */
	odraw_test_memset_attempts_before_fail = 0;

	result = libodraw_io_handle_clear(
	          io_handle,
	          &error );

	if( odraw_test_memset_attempts_before_fail != -1 )
	{
		odraw_test_memset_attempts_before_fail = -1;
	}
	else
	{
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
#endif /* defined( HAVE_ODRAW_TEST_MEMORY ) */

	/* Clean up
	 */
	result = libodraw_io_handle_free(
	          &io_handle,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	ODRAW_TEST_ASSERT_IS_NULL(
	 "io_handle",
	 io_handle );

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
	if( io_handle != NULL )
	{
		libodraw_io_handle_free(
		 &io_handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libodraw_io_handle_copy_sector_data_to_buffer function
 * Returns 1 if successful or 0 if not
 */
int odraw_test_io_handle_copy_sector_data_to_buffer(
     void )
{
	libcerror_error_t *error          = NULL;
	libodraw_io_handle_t *io_handle   = NULL;
	uint8_t *buffer                   = NULL;
	uint8_t *sector_data              = NULL;
	size_t buffer_size                = 0;
	size_t number_of_bytes            = 0;
	size_t sector_data_size           = 0;
	size_t sector_offset              = 0;
	ssize_t read_count                = 0;
	int result                        = 0;

	/* Create the sector data
	 */
	sector_data_size = 2336;

	sector_data = (uint8_t *) malloc( 2352 );

	if( sector_data == NULL )
	{
		fprintf( stdout, "unable to create sector data.\n" );

		goto on_error;
	}
	for( number_of_bytes = 0;
	     number_of_bytes < sector_data_size;
	     number_of_bytes++ )
	{
		sector_data[ number_of_bytes ] = (uint8_t) ( ( number_of_bytes * 199 ) % 255 );
	}
	result = libodraw_io_handle_initialize(
	          &io_handle,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	ODRAW_TEST_ASSERT_IS_NOT_NULL(
	 "io_handle",
	 io_handle );

	ODRAW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	io_handle->bytes_per_sector = 2048;

	/* Test regular case with a sector size (2336) that differs from the
	 * IO handle sector size (2048), including a non-zero sector offset.
	 * This reproduces the heap-buffer-overflow reported by the fuzzer.
	 */
	buffer_size   = 497;
	sector_offset = 1868;

	buffer = (uint8_t *) malloc( buffer_size );

	if( buffer == NULL )
	{
		fprintf( stdout, "unable to create buffer.\n" );

		goto on_error;
	}
	memset( buffer, 0xee, buffer_size );

	read_count = libodraw_io_handle_copy_sector_data_to_buffer(
	              io_handle,
	              sector_data,
	              sector_data_size,
	              sector_data_size,
	              LIBODRAW_TRACK_TYPE_UNKNOWN,
	              buffer,
	              buffer_size,
	              0,
	              sector_offset,
	              &error );

	ODRAW_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) 468 );

	ODRAW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	if( memcmp(
	     buffer,
	     &( sector_data[ sector_offset ] ),
	     468 ) != 0 )
	{
		fprintf( stdout, "unexpected buffer content.\n" );

		goto on_error;
	}
	if( ( buffer[ read_count     ] != 0xee )
	 || ( buffer[ read_count + 1 ] != 0xee )
	 || ( buffer[ read_count + 2 ] != 0xee ) )
	{
		fprintf( stdout, "unexpected data beyond read count.\n" );

		goto on_error;
	}
	free( buffer );

	buffer = NULL;

	/* Test regular case converting a MODE1 2352 sector to a 2048 buffer
	 */
	buffer_size = 2048;

	buffer = (uint8_t *) malloc( buffer_size );

	if( buffer == NULL )
	{
		fprintf( stdout, "unable to create buffer.\n" );

		goto on_error;
	}
	memset( buffer, 0xee, buffer_size );

	memset( sector_data, 0, 2352 );

	sector_data[ 0 ] = 0x00;
	sector_data[ 1 ] = 0xff;
	sector_data[ 2 ] = 0xff;
	sector_data[ 3 ] = 0xff;
	sector_data[ 4 ] = 0xff;
	sector_data[ 5 ] = 0xff;
	sector_data[ 6 ] = 0xff;
	sector_data[ 7 ] = 0xff;
	sector_data[ 8 ] = 0xff;
	sector_data[ 9 ] = 0xff;
	sector_data[ 10 ] = 0xff;
	sector_data[ 11 ] = 0x00;
	sector_data[ 15 ]  = 0x01;

	memset(
	 &( sector_data[ 16 ] ),
	 0x5a,
	 2048 );

	read_count = libodraw_io_handle_copy_sector_data_to_buffer(
	              io_handle,
	              sector_data,
	              2352,
	              2352,
	              LIBODRAW_TRACK_TYPE_MODE1_2352,
	              buffer,
	              buffer_size,
	              0,
	              0,
	              &error );

	ODRAW_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) 2048 );

	ODRAW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	if( memcmp(
	     buffer,
	     &( sector_data[ 16 ] ),
	     2048 ) != 0 )
	{
		fprintf( stdout, "unexpected buffer content.\n" );

		goto on_error;
	}
	free( buffer );

	buffer = NULL;

	/* Test error cases
	 */
	read_count = libodraw_io_handle_copy_sector_data_to_buffer(
	              NULL,
	              sector_data,
	              sector_data_size,
	              sector_data_size,
	              LIBODRAW_TRACK_TYPE_UNKNOWN,
	              sector_data,
	              sector_data_size,
	              0,
	              0,
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

	read_count = libodraw_io_handle_copy_sector_data_to_buffer(
	              io_handle,
	              NULL,
	              sector_data_size,
	              sector_data_size,
	              LIBODRAW_TRACK_TYPE_UNKNOWN,
	              sector_data,
	              sector_data_size,
	              0,
	              0,
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

	read_count = libodraw_io_handle_copy_sector_data_to_buffer(
	              io_handle,
	              sector_data,
	              sector_data_size,
	              sector_data_size,
	              LIBODRAW_TRACK_TYPE_UNKNOWN,
	              NULL,
	              sector_data_size,
	              0,
	              0,
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

	/* Test error case with sector offset value out of bounds
	 */
	read_count = libodraw_io_handle_copy_sector_data_to_buffer(
	              io_handle,
	              sector_data,
	              sector_data_size,
	              sector_data_size,
	              LIBODRAW_TRACK_TYPE_UNKNOWN,
	              sector_data,
	              sector_data_size,
	              0,
	              sector_data_size,
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

	/* Test error case with corrupt XA sub-header
	 * Note the sector data is too small to contain a XA sub-header,
	 * this must be reported as an error instead of reading past the end
	 */
	buffer_size = 2048;

	buffer = (uint8_t *) malloc( buffer_size );

	if( buffer == NULL )
	{
		fprintf( stdout, "unable to create buffer.\n" );

		goto on_error;
	}
	read_count = libodraw_io_handle_copy_sector_data_to_buffer(
	              io_handle,
	              sector_data,
	              2,
	              2336,
	              LIBODRAW_TRACK_TYPE_MODE2_2336,
	              buffer,
	              buffer_size,
	              0,
	              0,
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

	free( buffer );

	buffer = NULL;

	result = libodraw_io_handle_free(
	          &io_handle,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	ODRAW_TEST_ASSERT_IS_NULL(
	 "io_handle",
	 io_handle );

	ODRAW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	free( sector_data );

	sector_data = NULL;

	return( 1 );

on_error:
	if( buffer != NULL )
	{
		free( buffer );
	}
	if( sector_data != NULL )
	{
		free( sector_data );
	}
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( io_handle != NULL )
	{
		libodraw_io_handle_free(
		 &io_handle,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBODRAW_DLL_IMPORT ) */

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc ODRAW_TEST_ATTRIBUTE_UNUSED,
     wchar_t * const argv[] ODRAW_TEST_ATTRIBUTE_UNUSED )
#else
int main(
     int argc ODRAW_TEST_ATTRIBUTE_UNUSED,
     char * const argv[] ODRAW_TEST_ATTRIBUTE_UNUSED )
#endif
{
	ODRAW_TEST_UNREFERENCED_PARAMETER( argc )
	ODRAW_TEST_UNREFERENCED_PARAMETER( argv )

#if defined( __GNUC__ ) && !defined( LIBODRAW_DLL_IMPORT )

	ODRAW_TEST_RUN(
	 "libodraw_io_handle_initialize",
	 odraw_test_io_handle_initialize );

	ODRAW_TEST_RUN(
	 "libodraw_io_handle_free",
	 odraw_test_io_handle_free );

	ODRAW_TEST_RUN(
	 "libodraw_io_handle_clear",
	 odraw_test_io_handle_clear );

	ODRAW_TEST_RUN(
	 "libodraw_io_handle_copy_sector_data_to_buffer",
	 odraw_test_io_handle_copy_sector_data_to_buffer );

#endif /* defined( __GNUC__ ) && !defined( LIBODRAW_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

