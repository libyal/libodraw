/*
 * Library track_value type test program
 *
 * Copyright (C) 2010-2024, Joachim Metz <joachim.metz@gmail.com>
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

#include "odraw_test_libcerror.h"
#include "odraw_test_libodraw.h"
#include "odraw_test_macros.h"
#include "odraw_test_memory.h"
#include "odraw_test_unused.h"

#include "../libodraw/libodraw_track_value.h"

#if defined( __GNUC__ ) && !defined( LIBODRAW_DLL_IMPORT )

/* Tests the libodraw_track_value_initialize function
 * Returns 1 if successful or 0 if not
 */
int odraw_test_track_value_initialize(
     void )
{
	libcerror_error_t *error            = NULL;
	libodraw_track_value_t *track_value = NULL;
	int result                          = 0;

#if defined( HAVE_ODRAW_TEST_MEMORY )
	int number_of_malloc_fail_tests     = 1;
	int number_of_memset_fail_tests     = 1;
	int test_number                     = 0;
#endif

	/* Test regular cases
	 */
	result = libodraw_track_value_initialize(
	          &track_value,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	ODRAW_TEST_ASSERT_IS_NOT_NULL(
	 "track_value",
	 track_value );

	ODRAW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libodraw_track_value_free(
	          &track_value,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	ODRAW_TEST_ASSERT_IS_NULL(
	 "track_value",
	 track_value );

	ODRAW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libodraw_track_value_initialize(
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

	track_value = (libodraw_track_value_t *) 0x12345678UL;

	result = libodraw_track_value_initialize(
	          &track_value,
	          &error );

	track_value = NULL;

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
		/* Test libodraw_track_value_initialize with malloc failing
		 */
		odraw_test_malloc_attempts_before_fail = test_number;

		result = libodraw_track_value_initialize(
		          &track_value,
		          &error );

		if( odraw_test_malloc_attempts_before_fail != -1 )
		{
			odraw_test_malloc_attempts_before_fail = -1;

			if( track_value != NULL )
			{
				libodraw_track_value_free(
				 &track_value,
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
			 "track_value",
			 track_value );

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
		/* Test libodraw_track_value_initialize with memset failing
		 */
		odraw_test_memset_attempts_before_fail = test_number;

		result = libodraw_track_value_initialize(
		          &track_value,
		          &error );

		if( odraw_test_memset_attempts_before_fail != -1 )
		{
			odraw_test_memset_attempts_before_fail = -1;

			if( track_value != NULL )
			{
				libodraw_track_value_free(
				 &track_value,
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
			 "track_value",
			 track_value );

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
	if( track_value != NULL )
	{
		libodraw_track_value_free(
		 &track_value,
		 NULL );
	}
	return( 0 );
}

/* Tests the libodraw_track_value_free function
 * Returns 1 if successful or 0 if not
 */
int odraw_test_track_value_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libodraw_track_value_free(
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

/* Tests the libodraw_track_value_get_bytes_per_sector function
 * Returns 1 if successful or 0 if not
 */
int odraw_test_track_value_get_bytes_per_sector(
     void )
{
	libcerror_error_t *error            = NULL;
	libodraw_track_value_t *track_value = NULL;
	uint32_t bytes_per_sector           = 0;
	int result                          = 0;

	/* Initialize test
	 */
	result = libodraw_track_value_initialize(
	          &track_value,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	ODRAW_TEST_ASSERT_IS_NOT_NULL(
	 "track_value",
	 track_value );

	ODRAW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libodraw_track_value_get_bytes_per_sector(
	          track_value,
	          &bytes_per_sector,
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
	result = libodraw_track_value_get_bytes_per_sector(
	          NULL,
	          &bytes_per_sector,
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

	result = libodraw_track_value_get_bytes_per_sector(
	          track_value,
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

	/* Clean up
	 */
	result = libodraw_track_value_free(
	          &track_value,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	ODRAW_TEST_ASSERT_IS_NULL(
	 "track_value",
	 track_value );

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
	if( track_value != NULL )
	{
		libodraw_track_value_free(
		 &track_value,
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
	 "libodraw_track_value_initialize",
	 odraw_test_track_value_initialize );

	ODRAW_TEST_RUN(
	 "libodraw_track_value_free",
	 odraw_test_track_value_free );

	/* TODO: add tests for libodraw_track_value_get */

	/* TODO: add tests for libodraw_track_value_set */

	ODRAW_TEST_RUN(
	 "libodraw_track_value_get_bytes_per_sector",
	 odraw_test_track_value_get_bytes_per_sector );

#endif /* defined( __GNUC__ ) && !defined( LIBODRAW_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

