/*
 * Verification handle
 *
 * Copyright (C) 2010-2021, Joachim Metz <joachim.metz@gmail.com>
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

#include "byte_size_string.h"
#include "digest_hash.h"
#include "log_handle.h"
#include "odrawtools_libcerror.h"
#include "odrawtools_libcsplit.h"
#include "odrawtools_libhmac.h"
#include "odrawtools_libodraw.h"
#include "odrawtools_system_split_string.h"
#include "process_status.h"
#include "storage_media_buffer.h"
#include "verification_handle.h"

#define VERIFICATION_HANDLE_VALUE_SIZE			64
#define VERIFICATION_HANDLE_VALUE_IDENTIFIER_SIZE	32
#define VERIFICATION_HANDLE_NOTIFY_STREAM		stdout

/* Creates a verification handle
 * Make sure the value verification_handle is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int verification_handle_initialize(
     verification_handle_t **verification_handle,
     uint8_t calculate_md5,
     libcerror_error_t **error )
{
	static char *function = "verification_handle_initialize";

	if( verification_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid verification handle.",
		 function );

		return( -1 );
	}
	if( *verification_handle != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid verification handle value already set.",
		 function );

		return( -1 );
	}
	*verification_handle = memory_allocate_structure(
	                        verification_handle_t );

	if( *verification_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create verification handle.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *verification_handle,
	     0,
	     sizeof( verification_handle_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear verification handle.",
		 function );

		memory_free(
		 *verification_handle );

		*verification_handle = NULL;

		return( -1 );
	}
	if( libodraw_handle_initialize(
	     &( ( *verification_handle )->input_handle ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize input handle.",
		 function );

		goto on_error;
	}
#ifdef TODO
	/* TODO: have application determine limit value and set to value - 4 */
	if( libodraw_handle_set_maximum_number_of_open_handles(
	     ( *verification_handle )->input_handle,
	     1000,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set maximum number of open handles.",
		 function );

		goto on_error;
	}
#endif
	if( calculate_md5 != 0 )
	{
		( *verification_handle )->calculated_md5_hash_string = system_string_allocate(
									33 );

		if( ( *verification_handle )->calculated_md5_hash_string == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create calculated MD5 digest hash string.",
			 function );

			goto on_error;
		}
	}
	( *verification_handle )->calculate_md5 = calculate_md5;
	( *verification_handle )->notify_stream = VERIFICATION_HANDLE_NOTIFY_STREAM;

	return( 1 );

on_error:
	if( *verification_handle != NULL )
	{
		if( ( *verification_handle )->calculated_sha1_hash_string != NULL )
		{
			memory_free(
			 ( *verification_handle )->calculated_sha1_hash_string );
		}
		if( ( *verification_handle )->calculated_md5_hash_string != NULL )
		{
			memory_free(
			 ( *verification_handle )->calculated_md5_hash_string );
		}
		if( ( *verification_handle )->input_handle != NULL )
		{
			libodraw_handle_free(
			 &( ( *verification_handle )->input_handle ),
			 NULL );
		}
		memory_free(
		 *verification_handle );

		*verification_handle = NULL;
	}
	return( -1 );
}

/* Frees a verification handle
 * Returns 1 if successful or -1 on error
 */
int verification_handle_free(
     verification_handle_t **verification_handle,
     libcerror_error_t **error )
{
	static char *function = "verification_handle_free";
	int result            = 1;

	if( verification_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid verification handle.",
		 function );

		return( -1 );
	}
	if( *verification_handle != NULL )
	{
		if( ( ( *verification_handle )->input_handle != NULL )
		 && ( libodraw_handle_free(
		       &( ( *verification_handle )->input_handle ),
		       error ) != 1 ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free input handle.",
			 function );

			result = -1;
		}
		if( ( *verification_handle )->md5_context != NULL )
		{
			if( libhmac_md5_free(
			     &( ( *verification_handle )->md5_context ),
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free MD5 context.",
				 function );

				result = -1;
			}
		}
		if( ( *verification_handle )->calculated_md5_hash_string != NULL )
		{
			memory_free(
			 ( *verification_handle )->calculated_md5_hash_string );
		}
		if( ( *verification_handle )->sha1_context != NULL )
		{
			if( libhmac_sha1_free(
			     &( ( *verification_handle )->sha1_context ),
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free SHA1 context.",
				 function );

				result = -1;
			}
		}
		if( ( *verification_handle )->calculated_sha1_hash_string != NULL )
		{
			memory_free(
			 ( *verification_handle )->calculated_sha1_hash_string );
		}
		if( ( *verification_handle )->sha256_context != NULL )
		{
			if( libhmac_sha256_free(
			     &( ( *verification_handle )->sha256_context ),
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free SHA256 context.",
				 function );

				result = -1;
			}
		}
		if( ( *verification_handle )->calculated_sha256_hash_string != NULL )
		{
			memory_free(
			 ( *verification_handle )->calculated_sha256_hash_string );
		}
		memory_free(
		 *verification_handle );

		*verification_handle = NULL;
	}
	return( result );
}

/* Signals the verification handle to abort
 * Returns 1 if successful or -1 on error
 */
int verification_handle_signal_abort(
     verification_handle_t *verification_handle,
     libcerror_error_t **error )
{
	static char *function = "verification_handle_signal_abort";

	if( verification_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid verification handle.",
		 function );

		return( -1 );
	}
	if( verification_handle->input_handle != NULL )
	{
		if( libodraw_handle_signal_abort(
		     verification_handle->input_handle,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to signal input handle to abort.",
			 function );

			return( -1 );
		}
	}
	verification_handle->abort = 1;

	return( 1 );
}

/* Opens the input of the verification handle
 * Returns 1 if successful or -1 on error
 */
int verification_handle_open_input(
     verification_handle_t *verification_handle,
     const system_character_t *filename,
     libcerror_error_t **error )
{
	static char *function = "verification_handle_open_input";

	if( verification_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid verification handle.",
		 function );

		return( -1 );
	}
	if( verification_handle->input_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid verification handle - missing input handle.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( libodraw_handle_open_wide(
	     verification_handle->input_handle,
	     filename,
	     LIBODRAW_OPEN_READ,
	     error ) != 1 )
#else
	if( libodraw_handle_open(
	     verification_handle->input_handle,
	     filename,
	     LIBODRAW_OPEN_READ,
	     error ) != 1 )
#endif
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open file.",
		 function );

		return( -1 );
	}
	if( libodraw_handle_open_data_files(
	     verification_handle->input_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open data files.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Closes the verification handle
 * Returns the 0 if succesful or -1 on error
 */
int verification_handle_close(
     verification_handle_t *verification_handle,
     libcerror_error_t **error )
{
	static char *function = "verification_handle_close";

	if( verification_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid verification handle.",
		 function );

		return( -1 );
	}
	if( libodraw_handle_close(
	     verification_handle->input_handle,
	     error ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close input handle.",
		 function );

		return( -1 );
	}
	return( 0 );
}

/* Prepares a buffer after reading the input of the verification handle
 * Returns the resulting buffer size or -1 on error
 */
ssize_t verification_handle_prepare_read_buffer(
         verification_handle_t *verification_handle,
         storage_media_buffer_t *storage_media_buffer,
         libcerror_error_t **error )
{
	static char *function = "verification_handle_prepare_read_buffer";
	ssize_t process_count = 0;

	if( verification_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid verification handle.",
		 function );

		return( -1 );
	}
	if( storage_media_buffer == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid storage media buffer.",
		 function );

		return( -1 );
	}
	process_count = (ssize_t) storage_media_buffer->raw_buffer_data_size;

	verification_handle->last_offset_read += process_count;

	return( process_count );
}

/* Reads a buffer from the input of the verification handle
 * Returns the number of bytes written or -1 on error
 */
ssize_t verification_handle_read_buffer(
         verification_handle_t *verification_handle,
         storage_media_buffer_t *storage_media_buffer,
         size_t read_size,
         libcerror_error_t **error )
{
	static char *function = "verification_handle_read_buffer";
	ssize_t read_count    = 0;

	if( verification_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid verification handle.",
		 function );

		return( -1 );
	}
	if( storage_media_buffer == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid storage media buffer.",
		 function );

		return( -1 );
	}
	read_count = libodraw_handle_read_buffer(
                      verification_handle->input_handle,
                      storage_media_buffer->raw_buffer,
                      read_size,
	              error );

	if( read_count == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read storage media buffer.",
		 function );

		return( -1 );
	}
	storage_media_buffer->raw_buffer_data_size = (size_t) read_count;

	return( read_count );
}

/* Initializes the integrity hash(es)
 * Returns 1 if successful or -1 on error
 */
int verification_handle_initialize_integrity_hash(
     verification_handle_t *verification_handle,
     libcerror_error_t **error )
{
	static char *function = "verification_handle_initialize_integrity_hash";

	if( verification_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid verification handle.",
		 function );

		return( -1 );
	}
	if( verification_handle->calculate_md5 != 0 )
	{
		if( libhmac_md5_initialize(
		     &( verification_handle->md5_context ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to initialize MD5 context.",
			 function );

			goto on_error;
		}
		verification_handle->md5_context_initialized = 1;
	}
	if( verification_handle->calculate_sha1 != 0 )
	{
		if( libhmac_sha1_initialize(
		     &( verification_handle->sha1_context ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to initialize SHA1 context.",
			 function );

			goto on_error;
		}
		verification_handle->sha1_context_initialized = 1;
	}
	if( verification_handle->calculate_sha256 != 0 )
	{
		if( libhmac_sha256_initialize(
		     &( verification_handle->sha256_context ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to initialize SHA256 context.",
			 function );

			goto on_error;
		}
		verification_handle->sha256_context_initialized = 1;
	}
	return( 1 );

on_error:
	if( verification_handle->sha1_context != NULL )
	{
		libhmac_sha1_free(
		 &( verification_handle->sha1_context ),
		 NULL );
	}
	if( verification_handle->md5_context != NULL )
	{
		libhmac_md5_free(
		 &( verification_handle->md5_context ),
		 NULL );
	}
	return( -1 );
}

/* Updates the integrity hash(es)
 * Returns 1 if successful or -1 on error
 */
int verification_handle_update_integrity_hash(
     verification_handle_t *verification_handle,
     uint8_t *buffer,
     size_t buffer_size,
     libcerror_error_t **error )
{
	static char *function = "verification_handle_update_integrity_hash";

	if( verification_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid verification handle.",
		 function );

		return( -1 );
	}
	if( buffer == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid buffer.",
		 function );

		return( -1 );
	}
	if( ( buffer_size == 0 )
	 || ( buffer_size > (size_t) SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid buffer size value out of bounds.",
		 function );

		return( -1 );
	}
	if( verification_handle->calculate_md5 != 0 )
	{
		if( libhmac_md5_update(
		     verification_handle->md5_context,
		     buffer,
		     buffer_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to update MD5 digest hash.",
			 function );

			return( -1 );
		}
	}
	if( verification_handle->calculate_sha1 != 0 )
	{
		if( libhmac_sha1_update(
		     verification_handle->sha1_context,
		     buffer,
		     buffer_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to update SHA1 digest hash.",
			 function );

			return( -1 );
		}
	}
	if( verification_handle->calculate_sha256 != 0 )
	{
		if( libhmac_sha256_update(
		     verification_handle->sha256_context,
		     buffer,
		     buffer_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to update SHA256 digest hash.",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}

/* Finalizes the integrity hash(es)
 * Returns 1 if successful or -1 on error
 */
int verification_handle_finalize_integrity_hash(
     verification_handle_t *verification_handle,
     libcerror_error_t **error )
{
	uint8_t calculated_md5_hash[ LIBHMAC_MD5_HASH_SIZE ];
	uint8_t calculated_sha1_hash[ LIBHMAC_SHA1_HASH_SIZE ];
	uint8_t calculated_sha256_hash[ LIBHMAC_SHA256_HASH_SIZE ];

	static char *function = "verification_handle_finalize_integrity_hash";

	if( verification_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid verification handle.",
		 function );

		return( -1 );
	}
	if( verification_handle->calculate_md5 != 0 )
	{
		if( verification_handle->calculated_md5_hash_string == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: invalid verification handle - missing calculated MD5 hash string.",
			 function );

			return( -1 );
		}
		if( libhmac_md5_finalize(
		     verification_handle->md5_context,
		     calculated_md5_hash,
		     LIBHMAC_MD5_HASH_SIZE,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to finalize MD5 hash.",
			 function );

			return( -1 );
		}
		if( libhmac_md5_free(
		     &( verification_handle->md5_context ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free MD5 context.",
			 function );

			return( -1 );
		}
		if( digest_hash_copy_to_string(
		     calculated_md5_hash,
		     LIBHMAC_MD5_HASH_SIZE,
		     verification_handle->calculated_md5_hash_string,
		     33,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBODRAW_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set calculated MD5 hash string.",
			 function );

			return( -1 );
		}
	}
	if( verification_handle->calculate_sha1 != 0 )
	{
		if( verification_handle->calculated_sha1_hash_string == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: invalid verification handle - missing calculated SHA1 hash string.",
			 function );

			return( -1 );
		}
		if( libhmac_sha1_finalize(
		     verification_handle->sha1_context,
		     calculated_sha1_hash,
		     LIBHMAC_SHA1_HASH_SIZE,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to finalize SHA1 hash.",
			 function );

			return( -1 );
		}
		if( libhmac_sha1_free(
		     &( verification_handle->sha1_context ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free SHA1 context.",
			 function );

			return( -1 );
		}
		if( digest_hash_copy_to_string(
		     calculated_sha1_hash,
		     LIBHMAC_SHA1_HASH_SIZE,
		     verification_handle->calculated_sha1_hash_string,
		     41,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create calculated SHA1 hash string.",
			 function );

			return( -1 );
		}
	}
	if( verification_handle->calculate_sha256 != 0 )
	{
		if( verification_handle->calculated_sha256_hash_string == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: invalid verification handle - missing calculated SHA256 hash string.",
			 function );

			return( -1 );
		}
		if( libhmac_sha256_finalize(
		     verification_handle->sha256_context,
		     calculated_sha256_hash,
		     LIBHMAC_SHA256_HASH_SIZE,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to finalize SHA256 hash.",
			 function );

			return( -1 );
		}
		if( libhmac_sha256_free(
		     &( verification_handle->sha256_context ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free SHA256 context.",
			 function );

			return( -1 );
		}
		if( digest_hash_copy_to_string(
		     calculated_sha256_hash,
		     LIBHMAC_SHA256_HASH_SIZE,
		     verification_handle->calculated_sha256_hash_string,
		     65,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create calculated SHA256 hash string.",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}

/* Verifies the input
 * Returns 1 if successful, 0 if not or -1 on error
 */
int verification_handle_verify_input(
     verification_handle_t *verification_handle,
     uint8_t print_status_information,
     log_handle_t *log_handle,
     libcerror_error_t **error )
{
	process_status_t *process_status             = NULL;
	storage_media_buffer_t *storage_media_buffer = NULL;
	uint8_t *data                                = NULL;
	static char *function                        = "verification_handle_verify_input";
	size64_t media_size                          = 0;
	size64_t verify_count                        = 0;
	size_t data_size                             = 0;
	size_t process_buffer_size                   = 0;
	size_t read_size                             = 0;
	ssize_t process_count                        = 0;
	ssize_t read_count                           = 0;
	int status                                   = PROCESS_STATUS_COMPLETED;

	if( verification_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid verification handle.",
		 function );

		return( -1 );
	}
	if( verification_handle->process_buffer_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid process buffer size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( libodraw_handle_get_media_size(
	     verification_handle->input_handle,
	     &media_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve media size.",
		 function );

		goto on_error;
	}
	if( verification_handle->process_buffer_size == 0 )
	{
		process_buffer_size = 32768;
	}
	else
	{
		process_buffer_size = verification_handle->process_buffer_size;
	}
	if( storage_media_buffer_initialize(
	     &storage_media_buffer,
	     process_buffer_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create storage media buffer.",
		 function );

		goto on_error;
	}
	if( verification_handle_initialize_integrity_hash(
	     verification_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize integrity hash(es).",
		 function );

		goto on_error;
	}
	if( process_status_initialize(
	     &process_status,
	     _SYSTEM_STRING( "Verify" ),
	     _SYSTEM_STRING( "verified" ),
	     _SYSTEM_STRING( "Read" ),
	     verification_handle->notify_stream,
	     print_status_information,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create process status.",
		 function );

		goto on_error;
	}
	if( process_status_start(
	     process_status,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to start process status.",
		 function );

		goto on_error;
	}
	while( verify_count < media_size )
	{
		read_size = process_buffer_size;

		if( ( media_size - verify_count ) < read_size )
		{
			read_size = (size_t) ( media_size - verify_count );
		}
		read_count = verification_handle_read_buffer(
		              verification_handle,
		              storage_media_buffer,
		              read_size,
		              error );

		if( read_count < 0 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			"%s: unable to read data.",
			 function );

			goto on_error;
		}
		if( read_count == 0 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unexpected end of data.",
			 function );

			goto on_error;
		}
		process_count = verification_handle_prepare_read_buffer(
		                 verification_handle,
		                 storage_media_buffer,
		                 error );

		if( process_count < 0 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			"%s: unable to prepare buffer after read.",
			 function );

			goto on_error;
		}
		if( process_count > (ssize_t) read_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: more bytes read than requested.",
			 function );

			goto on_error;
		}
		verify_count += (size64_t) process_count;

		if( storage_media_buffer_get_data(
		     storage_media_buffer,
		     &data,
		     &data_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to determine storage media buffer data.",
			 function );

			goto on_error;
		}
		if( verification_handle_update_integrity_hash(
		     verification_handle,
		     data,
		     process_count,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GENERIC,
			 "%s: unable to update integrity hash(es).",
			 function );

			goto on_error;
		}
		if( process_status_update(
		     process_status,
		     verify_count,
		     media_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to update process status.",
			 function );

			goto on_error;
		}
		if( verification_handle->abort != 0 )
		{
			break;
		}
  	}
	if( storage_media_buffer_free(
	     &storage_media_buffer,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free storage media buffer.",
		 function );

		goto on_error;
	}
	if( verification_handle_finalize_integrity_hash(
	     verification_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to finalize integrity hash(es).",
		 function );

		goto on_error;
	}
	if( verification_handle->abort != 0 )
	{
		status = PROCESS_STATUS_ABORTED;
	}
	if( process_status_stop(
	     process_status,
	     verify_count,
	     status,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to stop process status.",
		 function );

		goto on_error;
	}
	if( process_status_free(
	     &process_status,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free process status.",
		 function );

		goto on_error;
	}
	if( verification_handle->abort == 0 )
	{
		if( verification_handle_hash_values_fprint(
		     verification_handle,
		     verification_handle->notify_stream,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print hash values.",
			 function );

			goto on_error;
		}
		fprintf(
		 verification_handle->notify_stream,
		 "\n" );

		if( log_handle != NULL )
		{
			if( verification_handle_hash_values_fprint(
			     verification_handle,
			     log_handle->log_stream,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
				 "%s: unable to print hash values in log handle.",
				 function );

				goto on_error;
			}
		}
	}
/* TODO use the information file to retrieve the stored hashes */
	return( 1 );

on_error:
	if( process_status != NULL )
	{
		process_status_stop(
		 process_status,
		 verify_count,
		 PROCESS_STATUS_FAILED,
		 NULL );
		process_status_free(
		 &process_status,
		 NULL );
	}
	if( storage_media_buffer != NULL )
	{
		storage_media_buffer_free(
		 &storage_media_buffer,
		 NULL );
	}
	return( -1 );
}

/* Sets the process buffer size
 * Returns 1 if successful, 0 if unsupported value or -1 on error
 */
int verification_handle_set_process_buffer_size(
     verification_handle_t *verification_handle,
     const system_character_t *string,
     libcerror_error_t **error )
{
	static char *function  = "verification_handle_set_process_buffer_size";
	size_t string_length   = 0;
	uint64_t size_variable = 0;
	int result             = 0;

	if( verification_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid verification handle.",
		 function );

		return( -1 );
	}
	string_length = system_string_length(
	                 string );

	result = byte_size_string_convert(
	          string,
	          string_length,
	          &size_variable,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine process buffer size.",
		 function );

		return( -1 );
	}
	else if( result != 0 )
	{
		if( size_variable > (uint64_t) SSIZE_MAX )
		{
			result = 0;
		}
		else
		{
			verification_handle->process_buffer_size = (size_t) size_variable;
		}
	}
	return( result );
}

/* Sets the additional digest types
 * Returns 1 if successful or -1 on error
 */
int verification_handle_set_additional_digest_types(
     verification_handle_t *verification_handle,
     const system_character_t *string,
     libcerror_error_t **error )
{
	system_character_t *string_segment     = NULL;
	system_split_string_t *string_elements = NULL;
	static char *function                  = "verification_handle_set_additional_digest_types";
	size_t string_length                   = 0;
	size_t string_segment_size             = 0;
	uint8_t calculate_sha1                 = 0;
	uint8_t calculate_sha256               = 0;
	int number_of_segments                 = 0;
	int result                             = 0;
	int segment_index                      = 0;

	if( verification_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid verification handle.",
		 function );

		return( -1 );
	}
	string_length = system_string_length(
	                 string );

	if( system_string_split(
	     string,
	     string_length + 1,
	     (system_character_t) ',',
	     &string_elements,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to split string.",
		 function );

		goto on_error;
	}
	if( system_split_string_get_number_of_segments(
	     string_elements,
	     &number_of_segments,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of segments.",
		 function );

		goto on_error;
	}
	for( segment_index = 0;
	     segment_index < number_of_segments;
	     segment_index++ )
	{
		if( system_split_string_get_segment_by_index(
		     string_elements,
		     segment_index,
		     &string_segment,
		     &string_segment_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve string segment: %d.",
			 function,
			 segment_index );

			goto on_error;
		}
		if( string_segment == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing string segment: %d.",
			 function,
			 segment_index );

			goto on_error;
		}
		if( string_segment_size == 5 )
		{
			if( system_string_compare(
			     string_segment,
			     _SYSTEM_STRING( "sha1" ),
			     4 ) == 0 )
			{
				calculate_sha1 = 1;
			}
			else if( system_string_compare(
			          string_segment,
			          _SYSTEM_STRING( "SHA1" ),
			          4 ) == 0 )
			{
				calculate_sha1 = 1;
			}
		}
		else if( string_segment_size == 6 )
		{
			if( system_string_compare(
			     string_segment,
			     _SYSTEM_STRING( "sha-1" ),
			     5 ) == 0 )
			{
				calculate_sha1 = 1;
			}
			else if( system_string_compare(
			          string_segment,
			          _SYSTEM_STRING( "sha_1" ),
			          5 ) == 0 )
			{
				calculate_sha1 = 1;
			}
			else if( system_string_compare(
			          string_segment,
			          _SYSTEM_STRING( "SHA-1" ),
			          5 ) == 0 )
			{
				calculate_sha1 = 1;
			}
			else if( system_string_compare(
			          string_segment,
			          _SYSTEM_STRING( "SHA_1" ),
			          5 ) == 0 )
			{
				calculate_sha1 = 1;
			}
		}
		else if( string_segment_size == 7 )
		{
			if( system_string_compare(
			     string_segment,
			     _SYSTEM_STRING( "sha256" ),
			     6 ) == 0 )
			{
				calculate_sha256 = 1;
			}
			else if( system_string_compare(
			          string_segment,
			          _SYSTEM_STRING( "SHA256" ),
			          6 ) == 0 )
			{
				calculate_sha256 = 1;
			}
		}
		else if( string_segment_size == 8 )
		{
			if( system_string_compare(
			     string_segment,
			     _SYSTEM_STRING( "sha-256" ),
			     7 ) == 0 )
			{
				calculate_sha256 = 1;
			}
			else if( system_string_compare(
			          string_segment,
			          _SYSTEM_STRING( "sha_256" ),
			          7 ) == 0 )
			{
				calculate_sha256 = 1;
			}
			else if( system_string_compare(
			          string_segment,
			          _SYSTEM_STRING( "SHA-256" ),
			          7 ) == 0 )
			{
				calculate_sha256 = 1;
			}
			else if( system_string_compare(
			          string_segment,
			          _SYSTEM_STRING( "SHA_256" ),
			          7 ) == 0 )
			{
				calculate_sha256 = 1;
			}
		}
	}
	if( ( calculate_sha1 != 0 )
	 && ( verification_handle->calculate_sha1 == 0 ) )
	{
		verification_handle->calculated_sha1_hash_string = system_string_allocate(
		                                                    41 );

		if( verification_handle->calculated_sha1_hash_string == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create calculated SHA1 digest hash string.",
			 function );

			goto on_error;
		}
		verification_handle->calculate_sha1 = 1;
	}
	if( ( calculate_sha256 != 0 )
	 && ( verification_handle->calculate_sha256 == 0 ) )
	{
		verification_handle->calculated_sha256_hash_string = system_string_allocate(
		                                                      65 );

		if( verification_handle->calculated_sha256_hash_string == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create calculated SHA256 digest hash string.",
			 function );

			goto on_error;
		}
		verification_handle->calculate_sha256 = 1;
	}
	if( system_split_string_free(
	     &string_elements,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free split string.",
		 function );

		goto on_error;
	}
	return( result );

on_error:
	if( string_elements != NULL )
	{
		system_split_string_free(
		 &string_elements,
		 NULL );
	}
	return( -1 );
}

/* Print the hash values to a stream
 * Returns 1 if successful or -1 on error
 */
int verification_handle_hash_values_fprint(
     verification_handle_t *verification_handle,
     FILE *stream,
     libcerror_error_t **error )
{
	static char *function = "verification_handle_hash_values_fprint";

	if( verification_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid verification handle.",
		 function );

		return( -1 );
	}
	if( stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
	if( verification_handle->calculate_md5 != 0 )
	{
		fprintf(
		 stream,
		 "MD5 hash calculated over data:\t\t%" PRIs_SYSTEM "\n",
		 verification_handle->calculated_md5_hash_string );
	}
	if( verification_handle->calculate_sha1 != 0 )
	{
		fprintf(
		 stream,
		 "SHA1 hash calculated over data:\t\t%" PRIs_SYSTEM "\n",
		 verification_handle->calculated_sha1_hash_string );
	}
	if( verification_handle->calculate_sha256 != 0 )
	{
		fprintf(
		 stream,
		 "SHA256 hash calculated over data:\t%" PRIs_SYSTEM "\n",
		 verification_handle->calculated_sha256_hash_string );
	}
	return( 1 );
}

