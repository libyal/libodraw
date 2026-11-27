/*
 * Library data_file type test program
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
#include <narrow_string.h>
#include <types.h>
#include <wide_string.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "odraw_test_libcerror.h"
#include "odraw_test_libodraw.h"
#include "odraw_test_macros.h"
#include "odraw_test_memory.h"
#include "odraw_test_unused.h"

#include "../libodraw/libodraw_data_file.h"
#include "../libodraw/libodraw_handle.h"

/* Tests the libodraw_data_file_free function
 * Returns 1 if successful or -1 on error
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

#if defined( __GNUC__ ) && !defined( LIBODRAW_DLL_IMPORT )

/* Creates a data file object for testing
 * Returns 1 if successful or -1 on error
 */
int odraw_test_data_file_create(
     libodraw_handle_t **handle,
     libodraw_data_file_descriptor_t **data_file_descriptor,
     libodraw_data_file_t **data_file,
     libcerror_error_t **error )
{
	static char *function = "odraw_test_data_file_create";

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
	if( libodraw_handle_initialize(
	     handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create handle.",
		 function );

		goto on_error;
	}
	if( libodraw_data_file_descriptor_initialize(
	     data_file_descriptor,
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
	if( libodraw_data_file_initialize(
	     data_file,
	     (libodraw_internal_handle_t *) *handle,
	     *data_file_descriptor,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create data file.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( data_file != NULL )
	{
		libodraw_data_file_free(
		 data_file,
		 NULL );
	}
	if( data_file_descriptor != NULL )
	{
		libodraw_data_file_descriptor_free(
		 data_file_descriptor,
		 NULL );
	}
	if( handle != NULL )
	{
		libodraw_handle_free(
		 handle,
		 NULL );
	}
	return( -1 );
}

/* Frees a data file object created for testing
 * Returns 1 if successful or -1 on error
 */
int odraw_test_data_file_free_test_data(
     libodraw_handle_t **handle,
     libodraw_data_file_descriptor_t **data_file_descriptor,
     libodraw_data_file_t **data_file,
     libcerror_error_t **error )
{
	static char *function = "odraw_test_data_file_free_test_data";

	if( libodraw_data_file_free(
	     data_file,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GENERIC,
		 "%s: unable to free data file.",
		 function );

		goto on_error;
	}
	if( libodraw_data_file_descriptor_free(
	     data_file_descriptor,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GENERIC,
		 "%s: unable to free data file descriptor.",
		 function );

		goto on_error;
	}
	if( libodraw_handle_free(
	     handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GENERIC,
		 "%s: unable to free handle.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( data_file_descriptor != NULL )
	{
		libodraw_data_file_descriptor_free(
		 data_file_descriptor,
		 NULL );
	}
	if( handle != NULL )
	{
		libodraw_handle_free(
		 handle,
		 NULL );
	}
	return( -1 );
}

/* Tests the libodraw_data_file_initialize function
 * Returns 1 if successful or -1 on error
 */
int odraw_test_data_file_initialize(
     void )
{
	libcerror_error_t *error                  = NULL;
	libodraw_handle_t *handle                 = NULL;
	libodraw_data_file_t *data_file           = NULL;
	libodraw_data_file_descriptor_t *data_file_descriptor = NULL;
	int result                                = 0;

	/* Test regular cases
	 */
	result = odraw_test_data_file_create(
	          &handle,
	          &data_file_descriptor,
	          &data_file,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	ODRAW_TEST_ASSERT_IS_NOT_NULL(
	 "handle",
	 handle );

	ODRAW_TEST_ASSERT_IS_NOT_NULL(
	 "data_file_descriptor",
	 data_file_descriptor );

	ODRAW_TEST_ASSERT_IS_NOT_NULL(
	 "data_file",
	 data_file );

	ODRAW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = odraw_test_data_file_free_test_data(
	          &handle,
	          &data_file_descriptor,
	          &data_file,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	ODRAW_TEST_ASSERT_IS_NULL(
	 "handle",
	 handle );

	ODRAW_TEST_ASSERT_IS_NULL(
	 "data_file_descriptor",
	 data_file_descriptor );

	ODRAW_TEST_ASSERT_IS_NULL(
	 "data_file",
	 data_file );

	ODRAW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libodraw_data_file_initialize(
	          NULL,
	          NULL,
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

	data_file = (libodraw_data_file_t *) 0x12345678UL;

	result = libodraw_data_file_initialize(
	          &data_file,
	          NULL,
	          NULL,
	          &error );

	data_file = NULL;

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	ODRAW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = odraw_test_data_file_create(
	          &handle,
	          &data_file_descriptor,
	          &data_file,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	ODRAW_TEST_ASSERT_IS_NOT_NULL(
	 "handle",
	 handle );

	ODRAW_TEST_ASSERT_IS_NOT_NULL(
	 "data_file_descriptor",
	 data_file_descriptor );

	ODRAW_TEST_ASSERT_IS_NOT_NULL(
	 "data_file",
	 data_file );

	ODRAW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libodraw_data_file_initialize(
	          NULL,
	          (libodraw_internal_handle_t *) handle,
	          data_file_descriptor,
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

	result = libodraw_data_file_initialize(
	          &data_file,
	          NULL,
	          data_file_descriptor,
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

	result = libodraw_data_file_initialize(
	          &data_file,
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

	result = odraw_test_data_file_free_test_data(
	          &handle,
	          &data_file_descriptor,
	          &data_file,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( data_file != NULL )
	{
		libodraw_data_file_free(
		 &data_file,
		 NULL );
	}
	if( data_file_descriptor != NULL )
	{
		libodraw_data_file_descriptor_free(
		 &data_file_descriptor,
		 NULL );
	}
	if( handle != NULL )
	{
		libodraw_handle_free(
		 &handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libodraw_data_file_get_type function
 * Returns 1 if successful or -1 on error
 */
int odraw_test_data_file_get_type(
     void )
{
	libcerror_error_t *error                  = NULL;
	libodraw_handle_t *handle                 = NULL;
	libodraw_data_file_t *data_file           = NULL;
	libodraw_data_file_descriptor_t *data_file_descriptor = NULL;
	uint8_t type                              = 0;
	int result                                = 0;

	/* Initialize test
	 */
	result = odraw_test_data_file_create(
	          &handle,
	          &data_file_descriptor,
	          &data_file,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	ODRAW_TEST_ASSERT_IS_NOT_NULL(
	 "handle",
	 handle );

	ODRAW_TEST_ASSERT_IS_NOT_NULL(
	 "data_file_descriptor",
	 data_file_descriptor );

	ODRAW_TEST_ASSERT_IS_NOT_NULL(
	 "data_file",
	 data_file );

	ODRAW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	data_file_descriptor->type = LIBODRAW_FILE_TYPE_BINARY;

	/* Test regular cases
	 */
	result = libodraw_data_file_get_type(
	          data_file,
	          &type,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "type",
	 (int) type,
	 (int) LIBODRAW_FILE_TYPE_BINARY );

	ODRAW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libodraw_data_file_get_type(
	          NULL,
	          &type,
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

	result = libodraw_data_file_get_type(
	          data_file,
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
	result = odraw_test_data_file_free_test_data(
	          &handle,
	          &data_file_descriptor,
	          &data_file,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( data_file != NULL )
	{
		libodraw_data_file_free(
		 &data_file,
		 NULL );
	}
	if( data_file_descriptor != NULL )
	{
		libodraw_data_file_descriptor_free(
		 &data_file_descriptor,
		 NULL );
	}
	if( handle != NULL )
	{
		libodraw_handle_free(
		 &handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libodraw_data_file_set_filename function
 * Returns 1 if successful or -1 on error
 */
int odraw_test_data_file_set_filename(
     void )
{
	libcerror_error_t *error                  = NULL;
	libodraw_handle_t *handle                 = NULL;
	libodraw_data_file_t *data_file           = NULL;
	libodraw_data_file_descriptor_t *data_file_descriptor = NULL;
	int result                                = 0;

	/* Initialize test
	 */
	result = odraw_test_data_file_create(
	          &handle,
	          &data_file_descriptor,
	          &data_file,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	ODRAW_TEST_ASSERT_IS_NOT_NULL(
	 "handle",
	 handle );

	ODRAW_TEST_ASSERT_IS_NOT_NULL(
	 "data_file_descriptor",
	 data_file_descriptor );

	ODRAW_TEST_ASSERT_IS_NOT_NULL(
	 "data_file",
	 data_file );

	ODRAW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libodraw_data_file_set_filename(
	          data_file,
	          "data.wav",
	          8,
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
	result = libodraw_data_file_set_filename(
	          NULL,
	          "data.wav",
	          8,
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

	result = libodraw_data_file_set_filename(
	          data_file,
	          NULL,
	          8,
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
	result = odraw_test_data_file_free_test_data(
	          &handle,
	          &data_file_descriptor,
	          &data_file,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( data_file != NULL )
	{
		libodraw_data_file_free(
		 &data_file,
		 NULL );
	}
	if( data_file_descriptor != NULL )
	{
		libodraw_data_file_descriptor_free(
		 &data_file_descriptor,
		 NULL );
	}
	if( handle != NULL )
	{
		libodraw_handle_free(
		 &handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libodraw_data_file_set_filename_wide function
 * Returns 1 if successful or -1 on error
 */
#if defined( HAVE_WIDE_CHARACTER_TYPE )
int odraw_test_data_file_set_filename_wide(
     void )
{
	libcerror_error_t *error                  = NULL;
	libodraw_handle_t *handle                 = NULL;
	libodraw_data_file_t *data_file           = NULL;
	libodraw_data_file_descriptor_t *data_file_descriptor = NULL;
	int result                                = 0;

	/* Initialize test
	 */
	result = odraw_test_data_file_create(
	          &handle,
	          &data_file_descriptor,
	          &data_file,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	ODRAW_TEST_ASSERT_IS_NOT_NULL(
	 "handle",
	 handle );

	ODRAW_TEST_ASSERT_IS_NOT_NULL(
	 "data_file_descriptor",
	 data_file_descriptor );

	ODRAW_TEST_ASSERT_IS_NOT_NULL(
	 "data_file",
	 data_file );

	ODRAW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libodraw_data_file_set_filename_wide(
	          data_file,
	          L"data.wav",
	          8,
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
	result = libodraw_data_file_set_filename_wide(
	          NULL,
	          L"data.wav",
	          8,
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

	result = libodraw_data_file_set_filename_wide(
	          data_file,
	          NULL,
	          8,
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
	result = odraw_test_data_file_free_test_data(
	          &handle,
	          &data_file_descriptor,
	          &data_file,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( data_file != NULL )
	{
		libodraw_data_file_free(
		 &data_file,
		 NULL );
	}
	if( data_file_descriptor != NULL )
	{
		libodraw_data_file_descriptor_free(
		 &data_file_descriptor,
		 NULL );
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

/* Tests the libodraw_data_file_get_filename_size function
 * Returns 1 if successful or -1 on error
 */
int odraw_test_data_file_get_filename_size(
     void )
{
	libcerror_error_t *error                  = NULL;
	libodraw_handle_t *handle                 = NULL;
	libodraw_data_file_t *data_file           = NULL;
	libodraw_data_file_descriptor_t *data_file_descriptor = NULL;
	size_t filename_size                      = 0;
	int result                                = 0;

	/* Initialize test
	 */
	result = odraw_test_data_file_create(
	          &handle,
	          &data_file_descriptor,
	          &data_file,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	ODRAW_TEST_ASSERT_IS_NOT_NULL(
	 "handle",
	 handle );

	ODRAW_TEST_ASSERT_IS_NOT_NULL(
	 "data_file_descriptor",
	 data_file_descriptor );

	ODRAW_TEST_ASSERT_IS_NOT_NULL(
	 "data_file",
	 data_file );

	ODRAW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Without a filename set the function should fail.
	 */
	result = libodraw_data_file_get_filename_size(
	          data_file,
	          &filename_size,
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

	result = libodraw_data_file_set_filename(
	          data_file,
	          "data.wav",
	          8,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	ODRAW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libodraw_data_file_get_filename_size(
	          data_file,
	          &filename_size,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	ODRAW_TEST_ASSERT_EQUAL_SIZE(
	 "filename_size",
	 filename_size,
	 9 * sizeof( char ) );

	ODRAW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libodraw_data_file_get_filename_size(
	          NULL,
	          &filename_size,
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

	result = libodraw_data_file_get_filename_size(
	          data_file,
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
	result = odraw_test_data_file_free_test_data(
	          &handle,
	          &data_file_descriptor,
	          &data_file,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( data_file != NULL )
	{
		libodraw_data_file_free(
		 &data_file,
		 NULL );
	}
	if( data_file_descriptor != NULL )
	{
		libodraw_data_file_descriptor_free(
		 &data_file_descriptor,
		 NULL );
	}
	if( handle != NULL )
	{
		libodraw_handle_free(
		 &handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libodraw_data_file_get_filename_size_wide function
 * Returns 1 if successful or -1 on error
 */
#if defined( HAVE_WIDE_CHARACTER_TYPE )
int odraw_test_data_file_get_filename_size_wide(
     void )
{
	libcerror_error_t *error                  = NULL;
	libodraw_handle_t *handle                 = NULL;
	libodraw_data_file_t *data_file           = NULL;
	libodraw_data_file_descriptor_t *data_file_descriptor = NULL;
	size_t filename_size                      = 0;
	int result                                = 0;

	/* Initialize test
	 */
	result = odraw_test_data_file_create(
	          &handle,
	          &data_file_descriptor,
	          &data_file,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	ODRAW_TEST_ASSERT_IS_NOT_NULL(
	 "handle",
	 handle );

	ODRAW_TEST_ASSERT_IS_NOT_NULL(
	 "data_file_descriptor",
	 data_file_descriptor );

	ODRAW_TEST_ASSERT_IS_NOT_NULL(
	 "data_file",
	 data_file );

	ODRAW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Without a filename set the function should fail.
	 */
	result = libodraw_data_file_get_filename_size_wide(
	          data_file,
	          &filename_size,
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

	result = libodraw_data_file_set_filename_wide(
	          data_file,
	          L"data.wav",
	          8,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	ODRAW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libodraw_data_file_get_filename_size_wide(
	          data_file,
	          &filename_size,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	ODRAW_TEST_ASSERT_EQUAL_SIZE(
	 "filename_size",
	 filename_size,
	 (size_t) 9 );

	ODRAW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libodraw_data_file_get_filename_size_wide(
	          NULL,
	          &filename_size,
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

	result = libodraw_data_file_get_filename_size_wide(
	          data_file,
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
	result = odraw_test_data_file_free_test_data(
	          &handle,
	          &data_file_descriptor,
	          &data_file,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( data_file != NULL )
	{
		libodraw_data_file_free(
		 &data_file,
		 NULL );
	}
	if( data_file_descriptor != NULL )
	{
		libodraw_data_file_descriptor_free(
		 &data_file_descriptor,
		 NULL );
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

/* Tests the libodraw_data_file_get_filename function
 * Returns 1 if successful or -1 on error
 */
int odraw_test_data_file_get_filename(
     void )
{
	libcerror_error_t *error                  = NULL;
	libodraw_handle_t *handle                 = NULL;
	libodraw_data_file_t *data_file           = NULL;
	libodraw_data_file_descriptor_t *data_file_descriptor = NULL;
	char buffer[ 32 ]                         = { 0 };
	int result                                = 0;

	/* Initialize test
	 */
	result = odraw_test_data_file_create(
	          &handle,
	          &data_file_descriptor,
	          &data_file,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	ODRAW_TEST_ASSERT_IS_NOT_NULL(
	 "handle",
	 handle );

	ODRAW_TEST_ASSERT_IS_NOT_NULL(
	 "data_file_descriptor",
	 data_file_descriptor );

	ODRAW_TEST_ASSERT_IS_NOT_NULL(
	 "data_file",
	 data_file );

	ODRAW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Without a filename set the function should fail.
	 */
	result = libodraw_data_file_get_filename(
	          data_file,
	          buffer,
	          sizeof( buffer ),
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

	result = libodraw_data_file_set_filename(
	          data_file,
	          "data.wav",
	          8,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	ODRAW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libodraw_data_file_get_filename(
	          data_file,
	          buffer,
	          sizeof( buffer ),
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "narrow_string_compare",
	 narrow_string_compare(
	  buffer,
	  "data.wav",
	  9 ),
	 0 );

	ODRAW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libodraw_data_file_get_filename(
	          NULL,
	          buffer,
	          sizeof( buffer ),
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

	result = libodraw_data_file_get_filename(
	          data_file,
	          NULL,
	          sizeof( buffer ),
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

	result = libodraw_data_file_get_filename(
	          data_file,
	          buffer,
	          5,
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
	result = odraw_test_data_file_free_test_data(
	          &handle,
	          &data_file_descriptor,
	          &data_file,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( data_file != NULL )
	{
		libodraw_data_file_free(
		 &data_file,
		 NULL );
	}
	if( data_file_descriptor != NULL )
	{
		libodraw_data_file_descriptor_free(
		 &data_file_descriptor,
		 NULL );
	}
	if( handle != NULL )
	{
		libodraw_handle_free(
		 &handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libodraw_data_file_get_filename_wide function
 * Returns 1 if successful or -1 on error
 */
#if defined( HAVE_WIDE_CHARACTER_TYPE )
int odraw_test_data_file_get_filename_wide(
     void )
{
	libcerror_error_t *error                  = NULL;
	libodraw_handle_t *handle                 = NULL;
	libodraw_data_file_t *data_file           = NULL;
	libodraw_data_file_descriptor_t *data_file_descriptor = NULL;
	wchar_t buffer[ 16 ]                      = { 0 };
	int result                                = 0;

	/* Initialize test
	 */
	result = odraw_test_data_file_create(
	          &handle,
	          &data_file_descriptor,
	          &data_file,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	ODRAW_TEST_ASSERT_IS_NOT_NULL(
	 "handle",
	 handle );

	ODRAW_TEST_ASSERT_IS_NOT_NULL(
	 "data_file_descriptor",
	 data_file_descriptor );

	ODRAW_TEST_ASSERT_IS_NOT_NULL(
	 "data_file",
	 data_file );

	ODRAW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Without a filename set the function should fail.
	 */
	result = libodraw_data_file_get_filename_wide(
	          data_file,
	          buffer,
	          16,
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

	result = libodraw_data_file_set_filename_wide(
	          data_file,
	          L"data.wav",
	          8,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	ODRAW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libodraw_data_file_get_filename_wide(
	          data_file,
	          buffer,
	          16,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "wide_string_compare",
	 wide_string_compare(
	  buffer,
	  L"data.wav",
	  9 ),
	 0 );

	ODRAW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libodraw_data_file_get_filename_wide(
	          NULL,
	          buffer,
	          16,
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

	result = libodraw_data_file_get_filename_wide(
	          data_file,
	          NULL,
	          16,
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

	result = libodraw_data_file_get_filename_wide(
	          data_file,
	          buffer,
	          5,
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
	result = odraw_test_data_file_free_test_data(
	          &handle,
	          &data_file_descriptor,
	          &data_file,
	          &error );

	ODRAW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( data_file != NULL )
	{
		libodraw_data_file_free(
		 &data_file,
		 NULL );
	}
	if( data_file_descriptor != NULL )
	{
		libodraw_data_file_descriptor_free(
		 &data_file_descriptor,
		 NULL );
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
	 "libodraw_data_file_initialize",
	 odraw_test_data_file_initialize );

	ODRAW_TEST_RUN(
	 "libodraw_data_file_get_type",
	 odraw_test_data_file_get_type );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

	ODRAW_TEST_RUN(
	 "libodraw_data_file_set_filename_wide",
	 odraw_test_data_file_set_filename_wide );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

	ODRAW_TEST_RUN(
	 "libodraw_data_file_set_filename",
	 odraw_test_data_file_set_filename );

	ODRAW_TEST_RUN(
	 "libodraw_data_file_get_filename_size",
	 odraw_test_data_file_get_filename_size );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

	ODRAW_TEST_RUN(
	 "libodraw_data_file_get_filename_size_wide",
	 odraw_test_data_file_get_filename_size_wide );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

	ODRAW_TEST_RUN(
	 "libodraw_data_file_get_filename",
	 odraw_test_data_file_get_filename );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

	ODRAW_TEST_RUN(
	 "libodraw_data_file_get_filename_wide",
	 odraw_test_data_file_get_filename_wide );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

#endif /* defined( __GNUC__ ) && !defined( LIBODRAW_DLL_IMPORT ) */

	ODRAW_TEST_RUN(
	 "libodraw_data_file_free",
	 odraw_test_data_file_free );

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}
