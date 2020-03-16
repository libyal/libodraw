/*
 * Sector range functions
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

#if !defined( _LIBODRAW_SECTOR_RANGE_H )
#define _LIBODRAW_SECTOR_RANGE_H

#include <common.h>
#include <types.h>

#include "libodraw_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libodraw_sector_range libodraw_sector_range_t;

struct libodraw_sector_range
{
	/* The start sector
	 */
	uint64_t start_sector;

	/* The end sector
	 */
	uint64_t end_sector;

	/* The number of sectors
	 */
	uint64_t number_of_sectors;
};

int libodraw_sector_range_initialize(
     libodraw_sector_range_t **sector_range,
     libcerror_error_t **error );

int libodraw_sector_range_free(
     libodraw_sector_range_t **sector_range,
     libcerror_error_t **error );

int libodraw_sector_range_get(
     libodraw_sector_range_t *sector_range,
     uint64_t *start_sector,
     uint64_t *number_of_sectors,
     libcerror_error_t **error );

int libodraw_sector_range_set(
     libodraw_sector_range_t *sector_range,
     uint64_t start_sector,
     uint64_t number_of_sectors,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBODRAW_SECTOR_RANGE_H ) */

