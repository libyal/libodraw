/*
 * Metadata functions
 *
 * Copyright (c) 2010-2014, Joachim Metz <joachim.metz@gmail.com>
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
#include <types.h>

#include "libodraw_handle.h"
#include "libodraw_libcdata.h"
#include "libodraw_libcerror.h"
#include "libodraw_sector_range.h"
#include "libodraw_track_value.h"
#include "libodraw_types.h"

/* Retrieves the number of media size
 * Returns 1 if successful or -1 on error
 */
int libodraw_handle_get_media_size(
     libodraw_handle_t *handle,
     size64_t *media_size,
     libcerror_error_t **error )
{
	libodraw_internal_handle_t *internal_handle = NULL;
	static char *function                       = "libodraw_handle_get_media_size";

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
	internal_handle = (libodraw_internal_handle_t *) handle;

	if( media_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid media size.",
		 function );

		return( -1 );
	}
	*media_size = internal_handle->media_size;

	return( 1 );
}

/* Retrieves the number of bytes per sector
 * Returns 1 if successful or -1 on error
 */
int libodraw_handle_get_bytes_per_sector(
     libodraw_handle_t *handle,
     uint32_t *bytes_per_sector,
     libcerror_error_t **error )
{
	libodraw_internal_handle_t *internal_handle = NULL;
	static char *function                       = "libodraw_handle_get_bytes_per_sector";

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
	internal_handle = (libodraw_internal_handle_t *) handle;

	if( internal_handle->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing IO handle.",
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
	*bytes_per_sector = internal_handle->io_handle->bytes_per_sector;

	return( 1 );
}

/* Sets the number of bytes per sector
 * Returns 1 if successful or -1 on error
 */
int libodraw_handle_set_bytes_per_sector(
     libodraw_handle_t *handle,
     uint32_t bytes_per_sector,
     libcerror_error_t **error )
{
	libodraw_internal_handle_t *internal_handle = NULL;
	static char *function                       = "libodraw_handle_set_bytes_per_sector";

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
	internal_handle = (libodraw_internal_handle_t *) handle;

	if( internal_handle->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing IO handle.",
		 function );

		return( -1 );
	}
/* TODO add support for 2352 */
	if( bytes_per_sector != 2048 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported bytes per sector.",
		 function );

		return( -1 );
	}
	internal_handle->io_handle->bytes_per_sector = bytes_per_sector;

	return( 1 );
}

/* Retrieves the number of sectors
 * Returns 1 if successful or -1 on error
 */
int libodraw_handle_get_number_of_sectors(
     libodraw_handle_t *handle,
     uint64_t *number_of_sectors,
     libcerror_error_t **error )
{
	libodraw_internal_handle_t *internal_handle = NULL;
	static char *function                       = "libodraw_handle_get_number_of_sectors";

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
	internal_handle = (libodraw_internal_handle_t *) handle;

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
	*number_of_sectors = internal_handle->number_of_sectors;

	return( 1 );
}

/* Retrieves the number of sessions
 * Returns 1 if successful or -1 on error
 */
int libodraw_handle_get_number_of_sessions(
     libodraw_handle_t *handle,
     int *number_of_sessions,
     libcerror_error_t **error )
{
	libodraw_internal_handle_t *internal_handle = NULL;
	static char *function                       = "libodraw_handle_get_number_of_sessions";

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
	internal_handle = (libodraw_internal_handle_t *) handle;

	if( libcdata_array_get_number_of_entries(
	     internal_handle->sessions_array,
	     number_of_sessions,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of elements in sessions array.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a session
 * Returns 1 if successful or -1 on error
 */
int libodraw_handle_get_session(
     libodraw_handle_t *handle,
     int index,
     uint64_t *start_sector,
     uint64_t *number_of_sectors,
     libcerror_error_t **error )
{
	libodraw_internal_handle_t *internal_handle = NULL;
	libodraw_sector_range_t *sector_range       = NULL;
	static char *function                       = "libodraw_handle_get_session";

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
	internal_handle = (libodraw_internal_handle_t *) handle;

	if( libcdata_array_get_entry_by_index(
	     internal_handle->sessions_array,
	     index,
	     (intptr_t **) &sector_range,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve session sector range: %d from array.",
		 function,
		 index );

		return( -1 );
	}
	if( libodraw_sector_range_get(
	     sector_range,
	     start_sector,
	     number_of_sectors,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve sector range.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Appends a session
 * Returns 1 if successful or -1 on error
 */
int libodraw_handle_append_session(
     libodraw_handle_t *handle,
     uint64_t start_sector,
     uint64_t number_of_sectors,
     libcerror_error_t **error )
{
	libodraw_internal_handle_t *internal_handle = NULL;
	libodraw_sector_range_t *sector_range       = NULL;
	static char *function                       = "libodraw_handle_append_session";
	int entry_index                             = 0;

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
	internal_handle = (libodraw_internal_handle_t *) handle;

	if( libodraw_sector_range_initialize(
	     &sector_range,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create sector range.",
		 function );

		goto on_error;
	}
	if( libodraw_sector_range_set(
	     sector_range,
	     start_sector,
	     number_of_sectors,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set sector range.",
		 function );

		goto on_error;
	}
	if( libcdata_array_append_entry(
	     internal_handle->sessions_array,
	     &entry_index,
	     (intptr_t *) sector_range,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
		 "%s: unable to append session sector range to array.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( sector_range != NULL )
	{
		libodraw_sector_range_free(
		 &sector_range,
		 NULL );
	}
	return( -1 );
}

/* Retrieves the number of lead-outs
 * Returns 1 if successful or -1 on error
 */
int libodraw_handle_get_number_of_lead_outs(
     libodraw_handle_t *handle,
     int *number_of_lead_outs,
     libcerror_error_t **error )
{
	libodraw_internal_handle_t *internal_handle = NULL;
	static char *function                       = "libodraw_handle_get_number_of_lead_outs";

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
	internal_handle = (libodraw_internal_handle_t *) handle;

	if( libcdata_array_get_number_of_entries(
	     internal_handle->lead_outs_array,
	     number_of_lead_outs,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of elements in lead-outs array.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a lead-out
 * Returns 1 if successful or -1 on error
 */
int libodraw_handle_get_lead_out(
     libodraw_handle_t *handle,
     int index,
     uint64_t *start_sector,
     uint64_t *number_of_sectors,
     libcerror_error_t **error )
{
	libodraw_internal_handle_t *internal_handle = NULL;
	libodraw_sector_range_t *sector_range       = NULL;
	static char *function                       = "libodraw_handle_get_lead_out";

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
	internal_handle = (libodraw_internal_handle_t *) handle;

	if( libcdata_array_get_entry_by_index(
	     internal_handle->lead_outs_array,
	     index,
	     (intptr_t **) &sector_range,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve lead-out sector range: %d from array.",
		 function,
		 index );

		return( -1 );
	}
	if( libodraw_sector_range_get(
	     sector_range,
	     start_sector,
	     number_of_sectors,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve sector range.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Appends a lead-out
 * Returns 1 if successful or -1 on error
 */
int libodraw_handle_append_lead_out(
     libodraw_handle_t *handle,
     uint64_t start_sector,
     uint64_t number_of_sectors,
     libcerror_error_t **error )
{
	libodraw_internal_handle_t *internal_handle = NULL;
	libodraw_sector_range_t *sector_range       = NULL;
	static char *function                       = "libodraw_handle_append_lead_out";
	int entry_index                             = 0;

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
	internal_handle = (libodraw_internal_handle_t *) handle;

	if( libodraw_sector_range_initialize(
	     &sector_range,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create sector range.",
		 function );

		goto on_error;
	}
	if( libodraw_sector_range_set(
	     sector_range,
	     start_sector,
	     number_of_sectors,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set sector range.",
		 function );

		goto on_error;
	}
	if( libcdata_array_append_entry(
	     internal_handle->lead_outs_array,
	     &entry_index,
	     (intptr_t *) sector_range,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
		 "%s: unable to append lead-out sector range to array.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( sector_range != NULL )
	{
		libodraw_sector_range_free(
		 &sector_range,
		 NULL );
	}
	return( -1 );
}

/* Retrieves the number of tracks
 * Returns 1 if successful or -1 on error
 */
int libodraw_handle_get_number_of_tracks(
     libodraw_handle_t *handle,
     int *number_of_tracks,
     libcerror_error_t **error )
{
	libodraw_internal_handle_t *internal_handle = NULL;
	static char *function                       = "libodraw_handle_get_number_of_tracks";

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
	internal_handle = (libodraw_internal_handle_t *) handle;

	if( libcdata_array_get_number_of_entries(
	     internal_handle->tracks_array,
	     number_of_tracks,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of elements in tracks array.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a track
 * Returns 1 if successful or -1 on error
 */
int libodraw_handle_get_track(
     libodraw_handle_t *handle,
     int index,
     uint64_t *start_sector,
     uint64_t *number_of_sectors,
     uint8_t *type,
     int *data_file_index,
     uint64_t *data_file_start_sector,
     libcerror_error_t **error )
{
	libodraw_internal_handle_t *internal_handle = NULL;
	libodraw_track_value_t *track_value         = NULL;
	static char *function                       = "libodraw_handle_get_track";

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
	internal_handle = (libodraw_internal_handle_t *) handle;

	if( libcdata_array_get_entry_by_index(
	     internal_handle->tracks_array,
	     index,
	     (intptr_t **) &track_value,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve track value: %d from array.",
		 function,
		 index );

		return( -1 );
	}
	if( libodraw_track_value_get(
	     track_value,
	     start_sector,
	     number_of_sectors,
	     type,
	     data_file_index,
	     data_file_start_sector,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve track value.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Appends a track
 * Returns 1 if successful or -1 on error
 */
int libodraw_handle_append_track(
     libodraw_handle_t *handle,
     uint64_t start_sector,
     uint64_t number_of_sectors,
     uint8_t type,
     int data_file_index,
     uint64_t data_file_start_sector,
     libcerror_error_t **error )
{
	libodraw_internal_handle_t *internal_handle = NULL;
	libodraw_track_value_t *track_value         = NULL;
	static char *function                       = "libodraw_handle_append_track";
	int entry_index                             = 0;

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
	internal_handle = (libodraw_internal_handle_t *) handle;

	if( libodraw_track_value_initialize(
	     &track_value,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create track value.",
		 function );

		goto on_error;
	}
	if( libodraw_track_value_set(
	     track_value,
	     start_sector,
	     number_of_sectors,
	     type,
	     data_file_index,
	     data_file_start_sector,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set track value.",
		 function );

		goto on_error;
	}
	if( libcdata_array_append_entry(
	     internal_handle->tracks_array,
	     &entry_index,
	     (intptr_t *) track_value,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
		 "%s: unable to append track to array.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( track_value != NULL )
	{
		libodraw_track_value_free(
		 &track_value,
		 NULL );
	}
	return( -1 );
}

