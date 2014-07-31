/*
 * The internal type definitions
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

#if !defined( _LIBODRAW_INTERNAL_TYPES_H )
#define _LIBODRAW_INTERNAL_TYPES_H

#include <common.h>
#include <types.h>

/* Define HAVE_LOCAL_LIBODRAW for local use of libodraw
 * The definitions in <libodraw/types.h> are copied here
 * for local use of libodraw
 */
#if defined( HAVE_LOCAL_LIBODRAW )

/* The following type definitions hide internal data structures
 */
typedef intptr_t libodraw_data_file_t;
typedef intptr_t libodraw_handle_t;

#endif

#endif

