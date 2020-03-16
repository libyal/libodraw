/*
 * Track value functions
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
#include <types.h>

#include "libodraw_definitions.h"
#include "libodraw_libcerror.h"
#include "libodraw_track_value.h"

/* Creates a track value
 * Make sure the value track_value is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libodraw_track_value_initialize(
     libodraw_track_value_t **track_value,
     libcerror_error_t **error )
{
	static char *function = "libodraw_track_value_initialize";

	if( track_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid track value.",
		 function );

		return( -1 );
	}
	if( *track_value != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid track value value already set.",
		 function );

		return( -1 );
	}
	*track_value = memory_allocate_structure(
			libodraw_track_value_t );

	if( *track_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create track value.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *track_value,
	     0,
	     sizeof( libodraw_track_value_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear track value.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *track_value != NULL )
	{
		memory_free(
		 *track_value );

		*track_value = NULL;
	}
	return( -1 );
}

/* Frees a track value
 * Returns 1 if successful or -1 on error
 */
int libodraw_track_value_free(
     libodraw_track_value_t **track_value,
     libcerror_error_t **error )
{
	static char *function = "libodraw_track_value_free";

	if( track_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid track value.",
		 function );

		return( -1 );
	}
	if( *track_value != NULL )
	{
		memory_free(
		 *track_value );

		*track_value = NULL;
	}
	return( 1 );
}

/* Retrieves a track value
 * Returns 1 if successful or -1 on error
 */
int libodraw_track_value_get(
     libodraw_track_value_t *track_value,
     uint64_t *start_sector,
     uint64_t *number_of_sectors,
     uint8_t *type,
     int *data_file_index,
     uint64_t *data_file_start_sector,
     libcerror_error_t **error )
{
	static char *function = "libodraw_track_value_get";

	if( track_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid track value.",
		 function );

		return( -1 );
	}
	if( start_sector == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid start sector.",
		 function );

		return( -1 );
	}
	if( number_of_sectors == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid number of sectors.",
		 function );

		return( -1 );
	}
	if( type == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid type.",
		 function );

		return( -1 );
	}
	if( data_file_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data file index.",
		 function );

		return( -1 );
	}
	if( data_file_start_sector == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data file start sector.",
		 function );

		return( -1 );
	}
	*start_sector           = track_value->start_sector;
	*number_of_sectors      = track_value->number_of_sectors;
	*type                   = track_value->type;
	*data_file_index        = track_value->data_file_index;
	*data_file_start_sector = track_value->data_file_start_sector;

	return( 1 );
}

/* Sets a track value
 * Returns 1 if successful or -1 on error
 */
int libodraw_track_value_set(
     libodraw_track_value_t *track_value,
     uint64_t start_sector,
     uint64_t number_of_sectors,
     uint8_t type,
     int data_file_index,
     uint64_t data_file_start_sector,
     libcerror_error_t **error )
{
	static char *function = "libodraw_track_value_set";

	if( track_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid track value.",
		 function );

		return( -1 );
	}
	if( start_sector > (uint64_t) INT64_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid start sector value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( number_of_sectors > (uint64_t) INT64_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid number of sectors value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( ( type != LIBODRAW_TRACK_TYPE_UNKNOWN )
	 && ( type != LIBODRAW_TRACK_TYPE_AUDIO )
	 && ( type != LIBODRAW_TRACK_TYPE_CDG )
	 && ( type != LIBODRAW_TRACK_TYPE_MODE1_2048 )
	 && ( type != LIBODRAW_TRACK_TYPE_MODE1_2352 )
	 && ( type != LIBODRAW_TRACK_TYPE_MODE2_2048 )
	 && ( type != LIBODRAW_TRACK_TYPE_MODE2_2324 )
	 && ( type != LIBODRAW_TRACK_TYPE_MODE2_2336 )
	 && ( type != LIBODRAW_TRACK_TYPE_MODE2_2352 )
	 && ( type != LIBODRAW_TRACK_TYPE_CDI_2336 )
	 && ( type != LIBODRAW_TRACK_TYPE_CDI_2352 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported type.",
		 function );

		return( -1 );
	}
	if( data_file_index < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_LESS_THAN_ZERO,
		 "%s: invalid data file index value less than zero.",
		 function );

		return( -1 );
	}
	if( data_file_start_sector > (uint64_t) INT64_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid data file start sector value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( data_file_start_sector > start_sector )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: data file start sector value out of bounds.",
		 function );

		return( -1 );
	}
	switch( type )
	{
		case LIBODRAW_TRACK_TYPE_MODE1_2048:
		case LIBODRAW_TRACK_TYPE_MODE2_2048:
			track_value->bytes_per_sector = 2048;

			break;

		case LIBODRAW_TRACK_TYPE_MODE2_2324:
			track_value->bytes_per_sector = 2324;

			break;

		case LIBODRAW_TRACK_TYPE_MODE2_2336:
		case LIBODRAW_TRACK_TYPE_CDI_2336:
			track_value->bytes_per_sector = 2336;

			break;

		case LIBODRAW_TRACK_TYPE_AUDIO:
		case LIBODRAW_TRACK_TYPE_MODE1_2352:
		case LIBODRAW_TRACK_TYPE_MODE2_2352:
		case LIBODRAW_TRACK_TYPE_CDI_2352:
			track_value->bytes_per_sector = 2352;

			break;

		case LIBODRAW_TRACK_TYPE_CDG:
			track_value->bytes_per_sector = 2448;

			break;
	}
	track_value->start_sector           = start_sector;
	track_value->end_sector             = start_sector + number_of_sectors;
	track_value->number_of_sectors      = number_of_sectors;
	track_value->type                   = type;
	track_value->data_file_index        = data_file_index;
	track_value->data_file_start_sector = data_file_start_sector;
	track_value->data_file_offset       = data_file_start_sector * track_value->bytes_per_sector;

	return( 1 );
}

/* Retrieves the bytes per sector
 * Returns 1 if successful or -1 on error
 */
int libodraw_track_value_get_bytes_per_sector(
     libodraw_track_value_t *track_value,
     uint32_t *bytes_per_sector,
     libcerror_error_t **error )
{
	static char *function = "libodraw_track_value_get_bytes_per_sector";

	if( track_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid track value.",
		 function );

		return( -1 );
	}
	if( bytes_per_sector == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid bytes per sector.",
		 function );

		return( -1 );
	}
	*bytes_per_sector = track_value->bytes_per_sector;

	return( 1 );
}

