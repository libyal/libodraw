/*
 * Input/Output (IO) handle functions
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
#include "libodraw_codepage.h"
#include "libodraw_io_handle.h"
#include "libodraw_libcerror.h"
#include "libodraw_libcnotify.h"

#define libodraw_optical_disk_copy_msf_to_lba( minutes, seconds, frames, lba ) \
	lba  = minutes; \
	lba *= 60; \
	lba += seconds; \
	lba *= 75; \
	lba += frames; \
	lba -= 150;

static uint8_t libodraw_sector_synchronisation_data[ 12 ] = \
	{ 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00 };

/* Creates an IO handle
 * Make sure the value io_handle is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libodraw_io_handle_initialize(
     libodraw_io_handle_t **io_handle,
     libcerror_error_t **error )
{
	static char *function = "libodraw_io_handle_initialize";

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( *io_handle != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid IO handle value already set.",
		 function );

		return( -1 );
	}
	*io_handle = memory_allocate_structure(
	              libodraw_io_handle_t );

	if( *io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create IO handle.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *io_handle,
	     0,
	     sizeof( libodraw_io_handle_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear file.",
		 function );

		goto on_error;
	}
	( *io_handle )->bytes_per_sector = 2048;
	( *io_handle )->ascii_codepage   = LIBODRAW_CODEPAGE_WINDOWS_1252;

	return( 1 );

on_error:
	if( *io_handle != NULL )
	{
		memory_free(
		 *io_handle );

		*io_handle = NULL;
	}
	return( -1 );
}

/* Frees an IO handle
 * Returns 1 if successful or -1 on error
 */
int libodraw_io_handle_free(
     libodraw_io_handle_t **io_handle,
     libcerror_error_t **error )
{
	static char *function = "libodraw_io_handle_free";

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( *io_handle != NULL )
	{
		memory_free(
		 *io_handle );

		*io_handle = NULL;
	}
	return( 1 );
}

/* Clears the IO handle
 * Returns 1 if successful or -1 on error
 */
int libodraw_io_handle_clear(
     libodraw_io_handle_t *io_handle,
     libcerror_error_t **error )
{
	static char *function = "libodraw_io_handle_clear";

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( memory_set(
	     io_handle,
	     0,
	     sizeof( libodraw_io_handle_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear IO handle.",
		 function );

		return( -1 );
	}
	io_handle->bytes_per_sector = 2048;
	io_handle->ascii_codepage   = LIBODRAW_CODEPAGE_WINDOWS_1252;

	return( 1 );
}

/* Copies the sector data to the buffer
 * Returns the number of bytes copied if successful or -1 on error
 */
ssize_t libodraw_io_handle_copy_sector_data_to_buffer(
         libodraw_io_handle_t *io_handle,
         const uint8_t *sector_data,
         size_t sector_data_size,
         uint32_t bytes_per_sector,
         uint8_t track_type,
         uint8_t *buffer,
         size_t buffer_size,
         uint32_t sector_index,
         uint32_t sector_offset,
         libcerror_error_t **error )
{
	static char *function     = "libodraw_io_handle_copy_sector_data_to_buffer";
	size_t buffer_offset      = 0;
	size_t read_size          = 0;
	size_t sector_data_offset = 0;
	uint32_t sector_lba       = 0;

#if defined( HAVE_DEBUG_OUTPUT ) || defined( HAVE_VERBOSE_OUTPUT )
	uint8_t sector_mode       = 0;
#endif

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( sector_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid sector data.",
		 function );

		return( -1 );
	}
	if( sector_data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid sector data size value exceeds maximum.",
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
	if( buffer_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid buffer size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( ( (size_t) sector_offset >= sector_data_size )
	 || ( sector_offset >= io_handle->bytes_per_sector ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid sector offset value out of bounds.",
		 function );

		return( -1 );
	}
	while( sector_data_offset < sector_data_size )
	{
		if( io_handle->bytes_per_sector == 2048 )
		{
			if( ( track_type == LIBODRAW_TRACK_TYPE_MODE1_2352 )
			 || ( track_type == LIBODRAW_TRACK_TYPE_MODE2_2352 ) )
			{
				if( ( sector_data_offset + 16 ) >= sector_data_size )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
					 "%s: sector data too small.",
					 function );

					return( -1 );
				}
#if defined( HAVE_DEBUG_OUTPUT )
				if( libcnotify_verbose != 0 )
				{
					libcnotify_printf(
				 	 "%s: sector: %" PRIu32 " header:\n",
					 function,
					 sector_index );
					libcnotify_print_data(
					 &( sector_data[ sector_data_offset ] ),
					 16,
					 0 );
				}
#endif
				if( memory_compare(
				     &( sector_data[ sector_data_offset ] ),
				     libodraw_sector_synchronisation_data,
				     12 ) != 0 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_INPUT,
					 LIBCERROR_INPUT_ERROR_VALUE_MISMATCH,
					 "%s: unsupported sector synchronisation data.",
					 function );

					return( -1 );
				}
#if defined( HAVE_DEBUG_OUTPUT )
				if( libcnotify_verbose != 0 )
				{
					libcnotify_printf(
				 	 "%s: sector: %" PRIu32 " synchronisation data:\n",
					 function,
					 sector_index );
					libcnotify_print_data(
					 &( sector_data[ sector_data_offset ] ),
					 12,
					 0 );
				}
#endif
				sector_data_offset += 12;

				libodraw_optical_disk_copy_msf_to_lba(
				 sector_data[ sector_data_offset ],
				 sector_data[ sector_data_offset + 1 ],
				 sector_data[ sector_data_offset + 2 ],
				 sector_lba );

#if defined( HAVE_DEBUG_OUTPUT ) || defined( HAVE_VERBOSE_OUTPUT )
				sector_mode = sector_data[ sector_data_offset + 3 ] & 0x03;
#endif
#if defined( HAVE_DEBUG_OUTPUT )
				if( libcnotify_verbose != 0 )
				{
					libcnotify_printf(
				 	 "%s: sector: %" PRIu32 " MSF\t\t: %02" PRIu8 ":%02" PRIu8 ":%02" PRIu8 " (%" PRIu32 ")\n",
					 function,
					 sector_index,
					 sector_data[ sector_data_offset ],
					 sector_data[ sector_data_offset + 1 ],
					 sector_data[ sector_data_offset + 2 ],
					 sector_lba );

					libcnotify_printf(
				 	 "%s: sector: %" PRIu32 " mode bits\t: 0x%02" PRIx8 "\n",
					 function,
					 sector_index,
					 sector_data[ sector_data_offset + 3 ] );
				}
#endif
#if defined( HAVE_VERBOSE_OUTPUT )
				if( sector_lba != sector_index )
				{
					libcnotify_printf(
					 "%s: sector MSF (LBA) does not match current.\n",
					 function );
				}
				if( ( ( track_type == LIBODRAW_TRACK_TYPE_MODE1_2352 )
				  &&  ( sector_mode != 1 ) )
				 || ( ( track_type == LIBODRAW_TRACK_TYPE_MODE2_2352 )
				  &&  ( sector_mode != 2 ) ) )
				{
					libcnotify_printf(
					 "%s: sector mode does not match table of contents.\n",
					 function );
				}
#endif
				sector_data_offset += 4;
			}
			else if( bytes_per_sector == 2352 )
			{
				sector_data_offset += 16;
			}
			if( ( track_type == LIBODRAW_TRACK_TYPE_MODE2_2336 )
			 || ( track_type == LIBODRAW_TRACK_TYPE_MODE2_2352 ) )
			{
				if( ( sector_data[ sector_data_offset     ] != sector_data[ sector_data_offset + 4 ] )
				 || ( sector_data[ sector_data_offset + 1 ] != sector_data[ sector_data_offset + 5 ] )
				 || ( sector_data[ sector_data_offset + 2 ] != sector_data[ sector_data_offset + 6 ] )
				 || ( sector_data[ sector_data_offset + 3 ] != sector_data[ sector_data_offset + 7 ] ) )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_INPUT,
					 LIBCERROR_INPUT_ERROR_VALUE_MISMATCH,
					 "%s: unsupported or corrupt XA sub-header.",
					 function );

					return( -1 );
				}
				if( sector_data[ sector_data_offset + 1 ] >= 32 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_INPUT,
					 LIBCERROR_INPUT_ERROR_VALUE_MISMATCH,
					 "%s: unsupported XA sub-header channel number.",
					 function );

					return( -1 );
				}
#if defined( HAVE_VERBOSE_OUTPUT )
				if( libcnotify_verbose != 0 )
				{
					if( ( sector_data[ sector_data_offset + 2 ] & 0x08 ) != 0 )
					{
						libcnotify_printf(
						 "%s: data flag not set in XA sub-header sub-mode flags.\n",
						 function );
					}
				}
#endif

/* TODO some writers seem to ignore these flags
				if( ( sector_data[ sector_data_offset + 2 ] & 0x08 ) != 0 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_INPUT,
					 LIBCERROR_INPUT_ERROR_VALUE_MISMATCH,
					 "%s: unsupported XA sub-header sub-mode flags - data flag not set.",
					 function );

					return( -1 );
				}
*/
				sector_data_offset += 8;
			}
		}
		else if( io_handle->bytes_per_sector == 2352 )
		{
			if( sector_offset == 0 )
			{
/* TODO what about run-out and lead-out data (have argument indicate non-track data) */
				if( ( io_handle->mode == 1 )
				 || ( io_handle->mode == 2 ) )
				{
					read_size = 12;

					if( ( read_size + buffer_offset ) > buffer_size )
					{
						read_size = buffer_size - buffer_offset;
					}
					if( memory_copy(
					     &( buffer[ buffer_offset ] ),
					     libodraw_sector_synchronisation_data,
					     read_size ) != 0 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
						 "%s: unsupported copy sector synchronisation data to buffer.",
						 function );

						return( -1 );
					}
					buffer_offset += read_size;

					if( buffer_offset >= buffer_size )
					{
						break;
					}
/* TODO set MSF requires current sector */
					buffer[ buffer_offset++ ] = 0;

					if( buffer_offset >= buffer_size )
					{
						break;
					}
					buffer[ buffer_offset++ ] = 0;

					if( buffer_offset >= buffer_size )
					{
						break;
					}
					buffer[ buffer_offset++ ] = 0;

					if( buffer_offset >= buffer_size )
					{
						break;
					}
					if( io_handle->mode == 1 )
					{
						buffer[ buffer_offset++ ] = 1;
					}
					else if ( io_handle->mode == 2 )
					{
						buffer[ buffer_offset++ ] = 2;
					}
					if( buffer_offset >= buffer_size )
					{
						break;
					}
				}
				else
				{
					read_size = 16;

					if( ( read_size + buffer_offset ) > buffer_size )
					{
						read_size = buffer_size - buffer_offset;
					}
					if( memory_set(
					     &( buffer[ buffer_offset ] ),
					     0,
					     read_size ) == NULL )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_MEMORY,
						 LIBCERROR_MEMORY_ERROR_SET_FAILED,
						 "%s: unable to set sector data in buffer.",
						 function );

						return( -1 );
					}
					buffer_offset += read_size;

					if( buffer_offset >= buffer_size )
					{
						break;
					}
				}
				if( io_handle->mode == 2 )
				{
/* TODO what about XA sub-header */
				}
			}
		}
		read_size = io_handle->bytes_per_sector;

		if( sector_offset != 0 )
		{
			sector_data_offset += sector_offset;
			read_size          -= (size_t) sector_offset;
			sector_offset       = 0;
		}
		if( ( read_size + buffer_offset ) > buffer_size )
		{
			read_size = buffer_size - buffer_offset;
		}
		if( ( track_type == LIBODRAW_TRACK_TYPE_AUDIO )
		 && ( io_handle->bytes_per_sector != 2352 ) )
		{
			/* If the sector size is not 2352 just return 0 bytes
			 * for audio data
			 */
			if( memory_set(
			     &( buffer[ buffer_offset ] ),
			     0,
			     read_size ) == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
				 "%s: unable to set sector data to buffer.",
				 function );

				return( -1 );
			}
		}
		else
		{
			if( memory_copy(
			     &( buffer[ buffer_offset ] ),
			     &( sector_data[ sector_data_offset ] ),
			     read_size ) == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
				 "%s: unable to copy sector data to buffer.",
				 function );

				return( -1 );
			}
		}
		buffer_offset      += read_size;
		sector_data_offset += read_size;

		if( buffer_offset >= buffer_size )
		{
			break;
		}
		if( io_handle->bytes_per_sector == 2048 )
		{
			if( track_type == LIBODRAW_TRACK_TYPE_MODE1_2352 )
			{
/* TODO calculate checksum, what about read errors ?*/
				sector_data_offset += 4;

/* TODO check padding */
				sector_data_offset += 8;

/* TODO check ECC data if necessary, what about read errors ? */
				sector_data_offset += 276;
			}
			else if( ( track_type == LIBODRAW_TRACK_TYPE_MODE2_2336 )
			      || ( track_type == LIBODRAW_TRACK_TYPE_MODE2_2352 ) )
			{
/* TODO calculate checksum, what about read errors ?*/
				sector_data_offset += 4;

/* TODO check ECC data if necessary, what about read errors ? */
				sector_data_offset += 276;
			}
			else if( bytes_per_sector == 2352 )
			{
				sector_data_offset += 288;
			}
		}
		else if( io_handle->bytes_per_sector == 2352 )
		{
/* TODO what about run-out and lead-out data (have argument indicate non-track data) */
			if( ( io_handle->mode == 1 )
			 || ( io_handle->mode == 2 ) )
			{
				read_size = 4;

				if( ( read_size + buffer_offset ) > buffer_size )
				{
					read_size = buffer_size - buffer_offset;
				}
/* TODO determine missing data instead of 0 fill */
				if( memory_set(
				     &( buffer[ buffer_offset ] ),
				     0,
				     read_size ) == NULL )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_MEMORY,
					 LIBCERROR_MEMORY_ERROR_SET_FAILED,
					 "%s: unable to set sector checksum in buffer.",
					 function );

					return( -1 );
				}
				buffer_offset += read_size;

				if( buffer_offset >= buffer_size )
				{
					break;
				}
			}
			if( io_handle->mode == 1 )
			{
				read_size = 8;

				if( ( read_size + buffer_offset ) > buffer_size )
				{
					read_size = buffer_size - buffer_offset;
				}
				if( memory_set(
				     &( buffer[ buffer_offset ] ),
				     0,
				     read_size ) == NULL )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_MEMORY,
					 LIBCERROR_MEMORY_ERROR_SET_FAILED,
					 "%s: unable to set sector reserved in buffer.",
					 function );

					return( -1 );
				}
				buffer_offset += read_size;

				if( buffer_offset >= buffer_size )
				{
					break;
				}
			}
			if( ( io_handle->mode == 1 )
			 || ( io_handle->mode == 2 ) )
			{
				read_size = 276;

				if( ( read_size + buffer_offset ) > buffer_size )
				{
					read_size = buffer_size - buffer_offset;
				}
/* TODO determine missing data instead of 0 fill */
				if( memory_set(
				     &( buffer[ buffer_offset ] ),
				     0,
				     read_size ) == NULL )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_MEMORY,
					 LIBCERROR_MEMORY_ERROR_SET_FAILED,
					 "%s: unable to set sector error correction data in buffer.",
					 function );

					return( -1 );
				}
				buffer_offset += read_size;

				if( buffer_offset >= buffer_size )
				{
					break;
				}
			}
			else
			{
				read_size = 288;

				if( ( read_size + buffer_offset ) > buffer_size )
				{
					read_size = buffer_size - buffer_offset;
				}
				if( memory_set(
				     &( buffer[ buffer_offset ] ),
				     0,
				     read_size ) == NULL )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_MEMORY,
					 LIBCERROR_MEMORY_ERROR_SET_FAILED,
					 "%s: unable to set sector data in buffer.",
					 function );

					return( -1 );
				}
				buffer_offset += read_size;

				if( buffer_offset >= buffer_size )
				{
					break;
				}
			}
		}
		sector_index++;
	}
	return( (ssize_t) buffer_offset );
}

