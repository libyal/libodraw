/*
 * Library data_file_descriptor type test program
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
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "odraw_test_libcerror.h"
#include "odraw_test_libodraw.h"
#include "odraw_test_macros.h"
#include "odraw_test_memory.h"
#include "odraw_test_unused.h"

#include "../libodraw/libodraw_data_file_descriptor.h"

#if defined( __GNUC__ ) && !defined( LIBODRAW_DLL_IMPORT )

/* Tests the libodraw_data_file_descriptor_initialize function
 * Returns 1 if successful or 0 if not
 */
int odraw_test_data_file_descriptor_initialize(
     void )
{
	libcerror_error_t *error                              = NULL;
	libodraw_data_file_descriptor_t *data_file_descriptor = NULL;
	int result                                            = 0;

#if defined( HAVE_ODRAW_TEST_MEMORY )
	int number_of_malloc_fail_tests                       = 1;
	int number_of_memset_fail_tests                       = 1;
	int test_number                                       = 0;
#endif

	/* Test regular cases
	 */
	result = libodraw_data_file_descriptor_initialize(
	          &data_file_descriptor,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	ODRAW_TEST_ASSERT_IS_NOT_NULL(
	 "data_file_descriptor",
	 data_file_descriptor );

	ODRAW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libodraw_data_file_descriptor_free(
	          &data_file_descriptor,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	ODRAW_TEST_ASSERT_IS_NULL(
	 "data_file_descriptor",
	 data_file_descriptor );

	ODRAW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libodraw_data_file_descriptor_initialize(
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

	data_file_descriptor = (libodraw_data_file_descriptor_t *) 0x12345678UL;

	result = libodraw_data_file_descriptor_initialize(
	          &data_file_descriptor,
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

	data_file_descriptor = NULL;

#if defined( HAVE_ODRAW_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libodraw_data_file_descriptor_initialize with malloc failing
		 */
		odraw_test_malloc_attempts_before_fail = test_number;

		result = libodraw_data_file_descriptor_initialize(
		          &data_file_descriptor,
		          &error );

		if( odraw_test_malloc_attempts_before_fail != -1 )
		{
			odraw_test_malloc_attempts_before_fail = -1;

			if( data_file_descriptor != NULL )
			{
				libodraw_data_file_descriptor_free(
				 &data_file_descriptor,
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
			 "data_file_descriptor",
			 data_file_descriptor );

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
		/* Test libodraw_data_file_descriptor_initialize with memset failing
		 */
		odraw_test_memset_attempts_before_fail = test_number;

		result = libodraw_data_file_descriptor_initialize(
		          &data_file_descriptor,
		          &error );

		if( odraw_test_memset_attempts_before_fail != -1 )
		{
			odraw_test_memset_attempts_before_fail = -1;

			if( data_file_descriptor != NULL )
			{
				libodraw_data_file_descriptor_free(
				 &data_file_descriptor,
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
			 "data_file_descriptor",
			 data_file_descriptor );

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
	if( data_file_descriptor != NULL )
	{
		libodraw_data_file_descriptor_free(
		 &data_file_descriptor,
		 NULL );
	}
	return( 0 );
}

/* Tests the libodraw_data_file_descriptor_free function
 * Returns 1 if successful or 0 if not
 */
int odraw_test_data_file_descriptor_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libodraw_data_file_descriptor_free(
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

/* Tests the libodraw_data_file_descriptor_get_name_size function
 * Returns 1 if successful or 0 if not
 */
int odraw_test_data_file_descriptor_get_name_size(
     void )
{
	libcerror_error_t *error                              = NULL;
	libodraw_data_file_descriptor_t *data_file_descriptor = NULL;
	size_t name_size                                      = 0;
	int name_size_is_set                                  = 0;
	int result                                            = 0;

	/* Initialize test
	 */
	result = libodraw_data_file_descriptor_initialize(
	          &data_file_descriptor,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	ODRAW_TEST_ASSERT_IS_NOT_NULL(
	 "data_file_descriptor",
	 data_file_descriptor );

	ODRAW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libodraw_data_file_descriptor_get_name_size(
	          data_file_descriptor,
	          &name_size,
	          &error );

	ODRAW_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	ODRAW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	name_size_is_set = result;

	/* Test error cases
	 */
	result = libodraw_data_file_descriptor_get_name_size(
	          NULL,
	          &name_size,
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

	if( name_size_is_set != 0 )
	{
		result = libodraw_data_file_descriptor_get_name_size(
		          data_file_descriptor,
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
	/* Clean up
	 */
	result = libodraw_data_file_descriptor_free(
	          &data_file_descriptor,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	ODRAW_TEST_ASSERT_IS_NULL(
	 "data_file_descriptor",
	 data_file_descriptor );

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
	if( data_file_descriptor != NULL )
	{
		libodraw_data_file_descriptor_free(
		 &data_file_descriptor,
		 NULL );
	}
	return( 0 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Tests the libodraw_data_file_descriptor_get_name_size_wide function
 * Returns 1 if successful or 0 if not
 */
int odraw_test_data_file_descriptor_get_name_size_wide(
     void )
{
	libcerror_error_t *error                              = NULL;
	libodraw_data_file_descriptor_t *data_file_descriptor = NULL;
	size_t name_size_wide                                 = 0;
	int name_size_wide_is_set                             = 0;
	int result                                            = 0;

	/* Initialize test
	 */
	result = libodraw_data_file_descriptor_initialize(
	          &data_file_descriptor,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	ODRAW_TEST_ASSERT_IS_NOT_NULL(
	 "data_file_descriptor",
	 data_file_descriptor );

	ODRAW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libodraw_data_file_descriptor_get_name_size_wide(
	          data_file_descriptor,
	          &name_size_wide,
	          &error );

	ODRAW_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	ODRAW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	name_size_wide_is_set = result;

	/* Test error cases
	 */
	result = libodraw_data_file_descriptor_get_name_size_wide(
	          NULL,
	          &name_size_wide,
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

	if( name_size_wide_is_set != 0 )
	{
		result = libodraw_data_file_descriptor_get_name_size_wide(
		          data_file_descriptor,
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
	/* Clean up
	 */
	result = libodraw_data_file_descriptor_free(
	          &data_file_descriptor,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	ODRAW_TEST_ASSERT_IS_NULL(
	 "data_file_descriptor",
	 data_file_descriptor );

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
	if( data_file_descriptor != NULL )
	{
		libodraw_data_file_descriptor_free(
		 &data_file_descriptor,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

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
	 "libodraw_data_file_descriptor_initialize",
	 odraw_test_data_file_descriptor_initialize );

	ODRAW_TEST_RUN(
	 "libodraw_data_file_descriptor_free",
	 odraw_test_data_file_descriptor_free );

	/* TODO: add tests for libodraw_data_file_descriptor_get_name_size */

	/* TODO: add tests for libodraw_data_file_descriptor_get_name */

	/* TODO: add tests for libodraw_data_file_descriptor_set_name */

#if defined( HAVE_WIDE_CHARACTER_TYPE )

	/* TODO: add tests for libodraw_data_file_descriptor_get_name_size_wide */

	/* TODO: add tests for libodraw_data_file_descriptor_get_name_wide */

	/* TODO: add tests for libodraw_data_file_descriptor_set_name_wide */

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

#endif /* defined( __GNUC__ ) && !defined( LIBODRAW_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

