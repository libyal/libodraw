/*
 * Library data_file type test program
 *
 * Copyright (C) 2010-2017, Joachim Metz <joachim.metz@gmail.com>
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
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "odraw_test_libcerror.h"
#include "odraw_test_libodraw.h"
#include "odraw_test_macros.h"
#include "odraw_test_memory.h"
#include "odraw_test_unused.h"

#include "../libodraw/libodraw_data_file.h"

/* Tests the libodraw_data_file_free function
 * Returns 1 if successful or 0 if not
 */
int odraw_test_data_file_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libodraw_data_file_free(
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

#if defined( __GNUC__ )

#endif /* defined( __GNUC__ ) */

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

#if defined( __GNUC__ )

	/* TODO: add tests for libodraw_data_file_initialize */

#endif /* defined( __GNUC__ ) */

	ODRAW_TEST_RUN(
	 "libodraw_data_file_free",
	 odraw_test_data_file_free );

#if defined( __GNUC__ )

	/* TODO: add tests for libodraw_data_file_get_filename_size */

	/* TODO: add tests for libodraw_data_file_get_filename */

	/* TODO: add tests for libodraw_data_file_set_filename */

	/* TODO: add tests for libodraw_data_file_get_filename_size_wide */

	/* TODO: add tests for libodraw_data_file_get_filename_wide */

	/* TODO: add tests for libodraw_data_file_set_filename_wide */

	/* TODO: add tests for libodraw_data_file_get_type */

#endif /* defined( __GNUC__ ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

