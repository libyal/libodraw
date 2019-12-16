/*
 * Info handle
 *
 * Copyright (C) 2010-2019, Joachim Metz <joachim.metz@gmail.com>
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
#include <byte_stream.h>
#include <memory.h>
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#if defined( HAVE_SYS_UTSNAME_H )
#include <sys/utsname.h>
#endif

#include "info_handle.h"
#include "odrawtools_libcerror.h"
#include "odrawtools_libodraw.h"

#define INFO_HANDLE_VALUE_SIZE			512
#define INFO_HANDLE_VALUE_IDENTIFIER_SIZE	64
#define INFO_HANDLE_NOTIFY_STREAM		stdout

/* Retrieves the data file type
 * Returns a string represenation of the data file type
 */
const char *info_handle_get_data_file_type(
             uint8_t data_file_type )
{
	switch( data_file_type )
	{
		case LIBODRAW_FILE_TYPE_BINARY_LITTLE_ENDIAN:
			return( "binary little-endian" );

		case LIBODRAW_FILE_TYPE_BINARY_BIG_ENDIAN:
			return( "binary big-endian" );

		case LIBODRAW_FILE_TYPE_AUDIO_AIFF:
			return( "audio AIFF" );

		case LIBODRAW_FILE_TYPE_AUDIO_WAVE:
			return( "audio WAVE" );

		case LIBODRAW_FILE_TYPE_AUDIO_MPEG1_LAYER3:
			return( "audio MP3" );

		default:
			break;
	}
	return( "UNKNOWN" );
}

/* Retrieves the track type
 * Returns a string represenation of the track type
 */
const char *info_handle_get_track_type(
             uint8_t track_type )
{
	switch( track_type )
	{
		case LIBODRAW_TRACK_TYPE_AUDIO:
			return( "audio (sector size: 2352)" );

		case LIBODRAW_TRACK_TYPE_CDG:
			return( "CD+G (sector size: 2448)" );

		case LIBODRAW_TRACK_TYPE_MODE1_2048:
			return( "mode1/2048 (sector size: 2048)" );

		case LIBODRAW_TRACK_TYPE_MODE1_2352:
			return( "mode1/2352 (sector size: 2352)" );

		case LIBODRAW_TRACK_TYPE_MODE2_2048:
			return( "mode2/2048 (sector size: 2048)" );

		case LIBODRAW_TRACK_TYPE_MODE2_2324:
			return( "mode2/2324 (sector size: 2324)" );

		case LIBODRAW_TRACK_TYPE_MODE2_2336:
			return( "mode2/2336 (sector size: 2336)" );

		case LIBODRAW_TRACK_TYPE_MODE2_2352:
			return( "mode2/2352 (sector size: 2352)" );

		case LIBODRAW_TRACK_TYPE_CDI_2336:
			return( "CDI/2336 (sector size: 2336)" );

		case LIBODRAW_TRACK_TYPE_CDI_2352:
			return( "CDI/2352 (sector size: 2352)" );

		default:
			break;
	}
	return( "UNKNOWN" );
}

/* Creates an info handle
 * Make sure the value info_handle is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int info_handle_initialize(
     info_handle_t **info_handle,
     libcerror_error_t **error )
{
	static char *function = "info_handle_initialize";

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( *info_handle != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid info handle value already set.",
		 function );

		return( -1 );
	}
	*info_handle = memory_allocate_structure(
			info_handle_t );

	if( *info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create info handle.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *info_handle,
	     0,
	     sizeof( info_handle_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear info handle.",
		 function );

		goto on_error;
	}
	if( libodraw_handle_initialize(
	     &( ( *info_handle )->input_handle ),
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
	( *info_handle )->notify_stream = INFO_HANDLE_NOTIFY_STREAM;

	return( 1 );

on_error:
	if( *info_handle != NULL )
	{
		memory_free(
		 *info_handle );

		*info_handle = NULL;
	}
	return( -1 );
}

/* Frees an info handle
 * Returns 1 if successful or -1 on error
 */
int info_handle_free(
     info_handle_t **info_handle,
     libcerror_error_t **error )
{
	static char *function = "info_handle_free";
	int result            = 1;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( *info_handle != NULL )
	{
		if( ( *info_handle )->input_handle != NULL )
		{
			if( libodraw_handle_free(
			     &( ( *info_handle )->input_handle ),
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free input handle.",
				 function );

				result = -1;
			}
		}
		memory_free(
		 *info_handle );

		*info_handle = NULL;
	}
	return( result );
}

/* Signals the info handle to abort
 * Returns 1 if successful or -1 on error
 */
int info_handle_signal_abort(
     info_handle_t *info_handle,
     libcerror_error_t **error )
{
	static char *function = "info_handle_signal_abort";

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( info_handle->input_handle != NULL )
	{
		if( libodraw_handle_signal_abort(
		     info_handle->input_handle,
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
	return( 1 );
}

/* Opens the input of the info handle
 * Returns 1 if successful or -1 on error
 */
int info_handle_open_input(
     info_handle_t *info_handle,
     const system_character_t *filename,
     libcerror_error_t **error )
{
	static char *function = "info_handle_open_input";

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( info_handle->input_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid info handle - missing input handle.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( libodraw_handle_open_wide(
	     info_handle->input_handle,
	     filename,
	     LIBODRAW_OPEN_READ,
	     error ) != 1 )
#else
	if( libodraw_handle_open(
	     info_handle->input_handle,
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
	if( info_handle->ignore_data_files == 0 )
	{
		if( libodraw_handle_open_data_files(
		     info_handle->input_handle,
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
	}
	return( 1 );
}

/* Closes the info handle
 * Returns the 0 if succesful or -1 on error
 */
int info_handle_close(
     info_handle_t *info_handle,
     libcerror_error_t **error )
{
	static char *function = "info_handle_close";

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( info_handle->input_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid info handle - missing input handle.",
		 function );

		return( -1 );
	}
	if( libodraw_handle_close(
	     info_handle->input_handle,
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

/* Prints the data files
 * Returns 1 if successful or -1 on error
 */
int info_handle_data_files_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error )
{
	libodraw_data_file_t *data_file = NULL;
	system_character_t *filename    = NULL;
	static char *function           = "info_handle_data_files_fprint";
	size_t filename_size            = 0;
	uint8_t data_file_type          = 0;
	int data_file_index             = 0;
	int number_of_data_files        = 0;
	int result                      = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( info_handle->input_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid info handle - missing input handle.",
		 function );

		return( -1 );
	}
	if( libodraw_handle_get_number_of_data_files(
	     info_handle->input_handle,
	     &number_of_data_files,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of data files.",
		 function );

		return( -1 );
	}
	if( number_of_data_files > 0 )
	{
		fprintf(
		 info_handle->notify_stream,
		 "Data files:\n" );

		fprintf(
		 info_handle->notify_stream,
		 "\ttotal number: %" PRIu32 "\n",
		 number_of_data_files );

		for( data_file_index = 0;
		     data_file_index < number_of_data_files;
		     data_file_index++ )
		{
			if( libodraw_handle_get_data_file(
			     info_handle->input_handle,
			     data_file_index,
			     &data_file,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve the data file: %d.",
				 function,
				 data_file_index );

				goto on_error;
			}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
			result = libodraw_data_file_get_filename_size_wide(
			          data_file,
			          &filename_size,
			          error );
#else
			result = libodraw_data_file_get_filename_size(
			          data_file,
			          &filename_size,
			          error );
#endif
			if( result != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve the data file: %d filename size.",
				 function,
				 data_file_index );

				goto on_error;
			}
			if( filename_size > 0 )
			{
				filename = system_string_allocate(
				            filename_size );

				if( filename == NULL )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_MEMORY,
					 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
					 "%s: unable to create filename.",
					 function );

					goto on_error;
				}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
				result = libodraw_data_file_get_filename_wide(
				          data_file,
				          filename,
				          filename_size,
				          error );
#else
				result = libodraw_data_file_get_filename(
				          data_file,
				          filename,
				          filename_size,
				          error );
#endif
				if( result != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
					 "%s: unable to retrieve the data file: %d filename.",
					 function,
					 data_file_index );

					memory_free(
					 filename );

					goto on_error;
				}
				if( libodraw_data_file_get_type(
				     data_file,
				     &data_file_type,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
					 "%s: unable to retrieve the data file: %d type.",
					 function,
					 data_file_index );

					goto on_error;
				}
				fprintf(
				 info_handle->notify_stream,
				 "\tfilename: %" PRIs_SYSTEM " (type: %s)\n",
				 filename,
				 info_handle_get_data_file_type(
				  data_file_type ) );

				memory_free(
				 filename );
			}
			if( libodraw_data_file_free(
			     &data_file,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free data file: %d.",
				 function,
				 data_file_index );

				goto on_error;
			}
		}
		fprintf(
		 info_handle->notify_stream,
		 "\n" );
	}
	return( 1 );

on_error:
	if( data_file != NULL )
	{
		libodraw_data_file_free(
	         &data_file,
	         error );
	}
	return( -1 );
}

/* Prints the sessions
 * Returns 1 if successful or -1 on error
 */
int info_handle_sessions_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error )
{
	static char *function      = "info_handle_sessions_fprint";
	uint64_t last_sector       = 0;
	uint64_t number_of_sectors = 0;
	uint64_t start_sector      = 0;
	int number_of_sessions     = 0;
	int result                 = 1;
	int session_index          = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( info_handle->input_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid info handle - missing input handle.",
		 function );

		return( -1 );
	}
	if( libodraw_handle_get_number_of_sessions(
	     info_handle->input_handle,
	     &number_of_sessions,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of sessions.",
		 function );

		return( -1 );
	}
	if( number_of_sessions > 0 )
	{
		fprintf(
		 info_handle->notify_stream,
		 "Sessions:\n" );
		fprintf(
		 info_handle->notify_stream,
		 "\ttotal number: %" PRIu32 "\n",
		 number_of_sessions );

		for( session_index = 0;
		     session_index < number_of_sessions;
		     session_index++ )
		{
			if( libodraw_handle_get_session(
			     info_handle->input_handle,
			     session_index,
			     &start_sector,
			     &number_of_sectors,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve the session: %d.",
				 function,
				 session_index );

				start_sector      = 0;
				number_of_sectors = 0;

				result = -1;
			}
			last_sector = start_sector + number_of_sectors;

			if( number_of_sectors != 0 )
			{
				last_sector -= 1;
			}
			fprintf(
			 info_handle->notify_stream,
			 "\tat sectors(s): %" PRIu64 " - %" PRIu64 " number: %" PRIu64 "\n",
			 start_sector,
			 last_sector,
			 number_of_sectors );
		}
		fprintf(
		 info_handle->notify_stream,
		 "\n" );
	}
	return( result );
}

/* Prints the lead-outs
 * Returns 1 if successful or -1 on error
 */
int info_handle_lead_outs_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error )
{
	static char *function      = "info_handle_lead_outs_fprint";
	uint64_t last_sector       = 0;
	uint64_t number_of_sectors = 0;
	uint64_t start_sector      = 0;
	int number_of_lead_outs    = 0;
	int result                 = 1;
	int lead_out_index         = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( info_handle->input_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid info handle - missing input handle.",
		 function );

		return( -1 );
	}
	if( libodraw_handle_get_number_of_lead_outs(
	     info_handle->input_handle,
	     &number_of_lead_outs,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of lead-outs.",
		 function );

		return( -1 );
	}
	if( number_of_lead_outs > 0 )
	{
		fprintf(
		 info_handle->notify_stream,
		 "Lead-outs:\n" );
		fprintf(
		 info_handle->notify_stream,
		 "\ttotal number: %" PRIu32 "\n",
		 number_of_lead_outs );

		for( lead_out_index = 0;
		     lead_out_index < number_of_lead_outs;
		     lead_out_index++ )
		{
			if( libodraw_handle_get_lead_out(
			     info_handle->input_handle,
			     lead_out_index,
			     &start_sector,
			     &number_of_sectors,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve the lead-out: %d.",
				 function,
				 lead_out_index );

				start_sector      = 0;
				number_of_sectors = 0;

				result = -1;
			}
			last_sector = start_sector + number_of_sectors;

			if( number_of_sectors != 0 )
			{
				last_sector -= 1;
			}
			fprintf(
			 info_handle->notify_stream,
			 "\tat sectors(s): %" PRIu64 " - %" PRIu64 " number: %" PRIu64 "\n",
			 start_sector,
			 last_sector,
			 number_of_sectors );
		}
		fprintf(
		 info_handle->notify_stream,
		 "\n" );
	}
	return( result );
}

/* Prints the tracks
 * Returns 1 if successful or -1 on error
 */
int info_handle_tracks_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error )
{
	static char *function           = "info_handle_tracks_fprint";
	uint64_t data_file_start_sector = 0;
	uint64_t last_sector            = 0;
	uint64_t number_of_sectors      = 0;
	uint64_t start_sector           = 0;
	uint8_t track_type              = 0;
	int data_file_index             = 0;
	int number_of_tracks            = 0;
	int result                      = 1;
	int track_index                 = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( info_handle->input_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid info handle - missing input handle.",
		 function );

		return( -1 );
	}
	if( libodraw_handle_get_number_of_tracks(
	     info_handle->input_handle,
	     &number_of_tracks,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of tracks.",
		 function );

		return( -1 );
	}
	if( number_of_tracks > 0 )
	{
		fprintf(
		 info_handle->notify_stream,
		 "Tracks:\n" );
		fprintf(
		 info_handle->notify_stream,
		 "\ttotal number: %" PRIu32 "\n",
		 number_of_tracks );

		for( track_index = 0;
		     track_index < number_of_tracks;
		     track_index++ )
		{
			if( libodraw_handle_get_track(
			     info_handle->input_handle,
			     track_index,
			     &start_sector,
			     &number_of_sectors,
			     &track_type,
			     &data_file_index,
			     &data_file_start_sector,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve the track: %d.",
				 function,
				 track_index );

				start_sector           = 0;
				number_of_sectors      = 0;
				track_type             = 0;
				data_file_index        = 0;
				data_file_start_sector = 0;

				result = -1;
			}
			fprintf(
			 info_handle->notify_stream,
			 "\ttype: %s",
			 info_handle_get_track_type(
			  track_type ) );

			last_sector = start_sector + number_of_sectors;

			if( number_of_sectors != 0 )
			{
				last_sector -= 1;
			}
			fprintf(
			 info_handle->notify_stream,
			 " at sectors(s): %" PRIu64 " - %" PRIu64 " number: %" PRIu64 "",
			 start_sector,
			 last_sector,
			 number_of_sectors );

			fprintf(
			 info_handle->notify_stream,
			 " (data file: %d, start sector: %" PRIu64 ")",
			 data_file_index,
			 data_file_start_sector );

			fprintf(
			 info_handle->notify_stream,
			 "\n" );
		}
		fprintf(
		 info_handle->notify_stream,
		 "\n" );
	}
	return( result );
}

/* Prints the handle information
 * Returns 1 if successful or -1 on error
 */
int info_handle_handle_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error )
{
	static char *function = "info_handle_handle_fprint";
	size64_t media_size   = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( info_handle->input_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid info handle - missing input handle.",
		 function );

		return( -1 );
	}
	fprintf(
	 info_handle->notify_stream,
	 "Optical disc information:\n" );

	if( libodraw_handle_get_media_size(
	     info_handle->input_handle,
	     &media_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve media size.",
		 function );

		return( -1 );
	}
	fprintf(
	 info_handle->notify_stream,
	 "\tmedia size: %" PRIu64 "\n",
	 media_size );

	fprintf(
	 info_handle->notify_stream,
	 "\n" );

	if( info_handle_data_files_fprint(
	     info_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
		 "%s: unable to print data files.",
		 function );

		return( -1 );
	}
	if( info_handle_sessions_fprint(
	     info_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
		 "%s: unable to print sessions.",
		 function );

		return( -1 );
	}
	if( info_handle_lead_outs_fprint(
	     info_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
		 "%s: unable to print lead-outs.",
		 function );

		return( -1 );
	}
	if( info_handle_tracks_fprint(
	     info_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
		 "%s: unable to print tracks.",
		 function );

		return( -1 );
	}
	return( 1 );
}

