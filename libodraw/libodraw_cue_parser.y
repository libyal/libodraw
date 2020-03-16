%{
/*
 * CUE parser functions
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
#include <narrow_string.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "libodraw_definitions.h"
#include "libodraw_handle.h"
#include "libodraw_libcerror.h"
#include "libodraw_libcnotify.h"
#include "libodraw_types.h"

#define YYMALLOC	cue_scanner_alloc
#define YYREALLOC	cue_scanner_realloc
#define YYFREE		cue_scanner_free

#define YYLEX_PARAM	NULL
#define YYPARSE_PARAM	parser_state

#if defined( HAVE_DEBUG_OUTPUT )
#define cue_parser_rule_print( string ) \
	if( libcnotify_verbose != 0 ) libcnotify_printf( "cue_parser: rule: %s\n", string )
#else
#define cue_parser_rule_print( string )
#endif

#if !defined( CD_SECS )
/* seconds per minute */
#define CD_SECS			60
#endif

#if !defined( CD_FRAMES )
/* frames per second */
#define CD_FRAMES		75
#endif

/* Note that the MSF are relative, so there is no need for the MSF offset correction
 */
#define cue_parser_copy_relative_msf_to_lba( msf_string, lba ) \
        lba  = ( ( msf_string[ 0 ] - '0' ) * 10 ) + ( msf_string[ 1 ] - '0' ); \
        lba *= CD_SECS; \
        lba += ( ( msf_string[ 3 ] - '0' ) * 10 ) + ( msf_string[ 4 ] - '0' ); \
        lba *= CD_FRAMES; \
        lba += ( ( msf_string[ 6 ] - '0' ) * 10 ) + ( msf_string[ 7 ] - '0' );
%}

/* %name-prefix="cue_scanner_" replaced by -p cue_scanner_ */
/* %no-lines replaced by -l */

%lex-param { (void *) NULL }
%parse-param { void *parser_state }

%start cue_main

%union
{
        /* The numeric value
         */
        uint32_t numeric_value;

        /* The string value
         */
	struct cue_string_value
	{
		/* The string data
		 */
	        const char *data;

		/* The string length
		 */
		size_t length;

	} string_value;
}

%{

typedef struct cue_parser_state cue_parser_state_t;

struct cue_parser_state
{
	/* The file
	 */
	libodraw_handle_t *handle;

	/* The error
	 */
	libcerror_error_t **error;

	/* The previous file index
	 */
	int previous_file_index;

	/* The current file index
	 */
	int current_file_index;

	/* The file type
	 */
	uint8_t file_type;

	/* Value to indicate a new file command was issued
	 */
	uint8_t new_file;

	/* The previous file sector
	 */
	uint64_t previous_file_sector;

	/* The file sector
	 */
	uint64_t file_sector;

	/* The previous session start sector
	 */
	uint64_t previous_session_start_sector;

	/* The previous lead-out start sector
	 */
	uint64_t previous_lead_out_start_sector;

	/* The previous track start sector
	 */
	uint64_t previous_track_start_sector;

	/* The current start sector
	 */
	uint64_t current_start_sector;

	/* The session number of sectors
	 */
	uint64_t session_number_of_sectors;

	/* The lead-out number of sectors
	 */
	uint64_t lead_out_number_of_sectors;

	/* The track number of sectors
	 */
	uint64_t track_number_of_sectors;

	/* The previous track type
	 */
	uint8_t previous_track_type;

	/* The current track type
	 */
	uint8_t current_track_type;

	/* The previous session
	 */
	int previous_session;

	/* The current session
	 */
	int current_session;

	/* The previous lead-out
	 */
	int previous_lead_out;

	/* The current lead-out
	 */
	int current_lead_out;

	/* The previous track
	 */
	int previous_track;

	/* The current track
	 */
	int current_track;

	/* The previous index
	 */
	int previous_index;

	/* The current index
	 */
	int current_index;
};

typedef size_t yy_size_t;
typedef struct yy_buffer_state* YY_BUFFER_STATE;

extern \
int cue_scanner_suppress_error;

extern \
int cue_scanner_lex_destroy(
     void );

extern \
void *cue_scanner_alloc(
       yy_size_t size );

extern \
void *cue_scanner_realloc(
       void *buffer,
       yy_size_t size );

extern \
void cue_scanner_free(
      void *buffer );

extern \
int cue_scanner_lex(
     void *user_data );

extern \
void cue_scanner_error(
      void *parser_state,
      const char *error_string );

extern \
YY_BUFFER_STATE cue_scanner__scan_buffer(
                 char *buffer,
                 yy_size_t buffer_size );

extern \
void cue_scanner__delete_buffer(
      YY_BUFFER_STATE buffer_state );

extern \
size_t cue_scanner_buffer_offset;

static char *cue_parser_function = "cue_parser";

int cue_parser_parse_buffer(
     libodraw_handle_t *handle,
     const uint8_t *buffer,
     size_t buffer_size,
     libcerror_error_t **error );

%}

/* Associativity rules
 */

/* Token definitions
 */
%token CUE_END_OF_LINE
%token CUE_SEMI_COLON

%token <string_value> CUE_2DIGIT
%token <string_value> CUE_CATALOG_NUMBER
%token <string_value> CUE_ISRC_CODE
%token <string_value> CUE_KEYWORD_STRING
%token <string_value> CUE_MSF
%token <string_value> CUE_STRING

/* Reserved words
 */
%token CUE_CATALOG
%token CUE_CDTEXTFILE
%token CUE_FLAGS
%token CUE_FILE
%token CUE_INDEX
%token CUE_ISRC
%token CUE_POSTGAP
%token CUE_PREGAP
%token CUE_REMARK
%token CUE_TRACK

/* CD-text reserved words
 */
%token CUE_CDTEXT_ARRANGER
%token CUE_CDTEXT_COMPOSER
%token CUE_CDTEXT_DISC_ID
%token CUE_CDTEXT_GENRE

%token CUE_CDTEXT_MESSAGE
%token CUE_CDTEXT_PERFORMER
%token CUE_CDTEXT_SIZE_INFO
%token CUE_CDTEXT_SONGWRITER
%token CUE_CDTEXT_TITLE
%token CUE_CDTEXT_TOC_INFO1
%token CUE_CDTEXT_TOC_INFO2
%token CUE_CDTEXT_UPC_EAN

/* Remark reserved words
 */
%token CUE_REMARK_LEAD_OUT
%token CUE_REMARK_ORIGINAL_MEDIA_TYPE
%token CUE_REMARK_RUN_OUT
%token CUE_REMARK_SESSION

%%

/* Parser rules
 */

cue_main
	: cue_main_items cue_file cue_main_items cue_main_tracks
	;

cue_main_items
	: /* empty */
	| cue_main_item cue_main_items
	;

cue_main_item
	: cue_catalog
	| cue_cdtextfile
	| cue_cdtext
	| cue_remark_item
	| cue_empty_line
	;

cue_main_tracks
	: /* empty */
	| cue_main_track cue_main_tracks
	;

cue_main_track
	: cue_main_track_preceding_items cue_track cue_main_track_leading_items cue_main_track_index_items cue_main_track_trailing_items
	;

cue_main_track_preceding_items
	: /* empty */
	| cue_main_track_preceding_item cue_main_track_preceding_items
	;

cue_main_track_preceding_item
	: cue_file
	| cue_remark_item
	| cue_empty_line
	;

cue_main_track_leading_items
	: /* empty */
	| cue_main_track_leading_item cue_main_track_leading_items
	;

cue_main_track_leading_item
	: cue_cdtext
	| cue_flags
	| cue_isrc
	| cue_pregap
	| cue_remark_item
	| cue_empty_line
	;

cue_main_track_index_items
	: /* empty */
	| cue_main_track_index_item cue_main_track_index_items
	;

cue_main_track_index_item
	: cue_index
	| cue_remark_item
	| cue_empty_line
	;

cue_main_track_trailing_items
	: /* empty */
	| cue_main_track_trailing_item cue_main_track_trailing_items
	;

cue_main_track_trailing_item
	: cue_cdtext
	| cue_postgap
	| cue_remark_item
	| cue_empty_line
	;

cue_catalog
	: CUE_CATALOG CUE_CATALOG_NUMBER CUE_END_OF_LINE
	{
		cue_parser_rule_print(
		 "cue_catalog" );
	}
	;

cue_cdtext
	: cue_cdtext_type CUE_STRING CUE_END_OF_LINE
	{
		cue_parser_rule_print(
		 "cue_cdtext" );
	}
	;

cue_cdtext_type
        : CUE_CDTEXT_ARRANGER
        | CUE_CDTEXT_COMPOSER
        | CUE_CDTEXT_DISC_ID
        | CUE_CDTEXT_GENRE
        | CUE_CDTEXT_MESSAGE
	| CUE_CDTEXT_PERFORMER
        | CUE_CDTEXT_SIZE_INFO
	| CUE_CDTEXT_SONGWRITER
	| CUE_CDTEXT_TITLE
        | CUE_CDTEXT_TOC_INFO1
        | CUE_CDTEXT_TOC_INFO2
        | CUE_CDTEXT_UPC_EAN
/* TODO IRSC definition */
	;

cue_cdtextfile
	: CUE_CDTEXTFILE CUE_STRING CUE_END_OF_LINE
	{
		cue_parser_rule_print(
		 "cue_cdtextfile" );
	}
	;

cue_file
	: CUE_FILE CUE_STRING CUE_KEYWORD_STRING CUE_END_OF_LINE
	{
		cue_parser_rule_print(
		 "cue_file" );

		if( $2.data == NULL )
		{
			libcerror_error_set(
			 ( (cue_parser_state_t *) parser_state )->error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
			 "%s: invalid filename.",
			 cue_parser_function );

			YYABORT;
		}
/* TODO what about the string quotation marks */
		if( $3.data == NULL )
		{
			libcerror_error_set(
			 ( (cue_parser_state_t *) parser_state )->error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
			 "%s: invalid file type.",
			 cue_parser_function );

			YYABORT;
		}
		( (cue_parser_state_t *) parser_state )->file_type = LIBODRAW_FILE_TYPE_UNKNOWN;

		if( $3.length == 3 )
		{
			if( narrow_string_compare(
			     $3.data,
			     "MP3",
			     3 ) == 0 )
			{
				( (cue_parser_state_t *) parser_state )->file_type = LIBODRAW_FILE_TYPE_AUDIO_MPEG1_LAYER3;
			}
		}
		else if( $3.length == 4 )
		{
			if( narrow_string_compare(
			     $3.data,
			     "AIFF",
			     4 ) == 0 )
			{
				( (cue_parser_state_t *) parser_state )->file_type = LIBODRAW_FILE_TYPE_AUDIO_AIFF;
			}
			else if( narrow_string_compare(
			          $3.data,
			          "WAVE",
			          4 ) == 0 )
			{
				( (cue_parser_state_t *) parser_state )->file_type = LIBODRAW_FILE_TYPE_AUDIO_WAVE;
			}
		}
		else if( $3.length == 6 )
		{
			if( narrow_string_compare(
			     $3.data,
			     "BINARY",
			     6 ) == 0 )
			{
				( (cue_parser_state_t *) parser_state )->file_type = LIBODRAW_FILE_TYPE_BINARY_LITTLE_ENDIAN;
			}
		}
		else if( $3.length == 8 )
		{
			if( narrow_string_compare(
			     $3.data,
			     "MOTOROLA",
			     8 ) == 0 )
			{
				( (cue_parser_state_t *) parser_state )->file_type = LIBODRAW_FILE_TYPE_BINARY_BIG_ENDIAN;
			}
		}
		if( libodraw_handle_append_data_file(
		     ( (cue_parser_state_t *) parser_state )->handle,
		     $2.data,
		     $2.length,
		     ( (cue_parser_state_t *) parser_state )->file_type,
		     ( (cue_parser_state_t *) parser_state )->error ) != 1 )
		{
			libcerror_error_set(
			 ( (cue_parser_state_t *) parser_state )->error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to append data file.",
			 cue_parser_function );

			YYABORT;
		}
		( (cue_parser_state_t *) parser_state )->current_file_index += 1;
	}
	;

cue_flags
	: CUE_FLAGS cue_flags_types CUE_END_OF_LINE
	{
		cue_parser_rule_print(
		 "cue_flags" );
	}
	;

cue_flags_types
	: /* empty */
	| CUE_KEYWORD_STRING cue_flags_types
	;

cue_index
	: CUE_INDEX CUE_2DIGIT CUE_MSF CUE_END_OF_LINE
	{
		cue_parser_rule_print(
		 "cue_index" );

		if( $2.data == NULL )
		{
			libcerror_error_set(
			 ( (cue_parser_state_t *) parser_state )->error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
			 "%s: invalid index number.",
			 cue_parser_function );

			YYABORT;
		}
		( (cue_parser_state_t *) parser_state )->previous_index = ( (cue_parser_state_t *) parser_state )->current_index;

		if( ( ( $2.data )[ 0 ] < '0' )
		 || ( ( $2.data )[ 0 ] > '9' ) )
		{
			libcerror_error_set(
			 ( (cue_parser_state_t *) parser_state )->error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported index number.",
			 cue_parser_function );

			YYABORT;
		}
		( (cue_parser_state_t *) parser_state )->current_index = ( $2.data )[ 0 ] - '0';

		if( $2.length == 2 )
		{
			( (cue_parser_state_t *) parser_state )->current_index *= 10;

			if( ( ( $2.data )[ 1 ] < '0' )
			 || ( ( $2.data )[ 1 ] > '9' ) )
			{
				libcerror_error_set(
				 ( (cue_parser_state_t *) parser_state )->error,
				 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
				 "%s: unsupported index number.",
				 cue_parser_function );

				YYABORT;
			}
			( (cue_parser_state_t *) parser_state )->current_index += ( $2.data )[ 1 ] - '0';
		}
		if( ( ( (cue_parser_state_t *) parser_state )->current_index != 0 )
		 && ( ( (cue_parser_state_t *) parser_state )->current_index != ( ( (cue_parser_state_t *) parser_state )->previous_index + 1 ) ) )
		{
			libcerror_error_set(
			 ( (cue_parser_state_t *) parser_state )->error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported index number - values are not sequential.",
			 cue_parser_function );

			YYABORT;
		}
		if( ( $3.data == NULL )
		 || ( $3.length != 8 ) )
		{
			libcerror_error_set(
			 ( (cue_parser_state_t *) parser_state )->error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
			 "%s: invalid index MSF.",
			 cue_parser_function );

			YYABORT;
		}
		if( ( ( $3.data )[ 0 ] < '0' )
		 || ( ( $3.data )[ 0 ] > '9' )
		 || ( ( $3.data )[ 1 ] < '0' )
		 || ( ( $3.data )[ 1 ] > '9' )
		 || ( ( $3.data )[ 2 ] != ':' )
		 || ( ( $3.data )[ 3 ] < '0' )
		 || ( ( $3.data )[ 3 ] > '9' )
		 || ( ( $3.data )[ 4 ] < '0' )
		 || ( ( $3.data )[ 4 ] > '9' )
		 || ( ( $3.data )[ 5 ] != ':' )
		 || ( ( $3.data )[ 6 ] < '0' )
		 || ( ( $3.data )[ 6 ] > '9' )
		 || ( ( $3.data )[ 7 ] < '0' )
		 || ( ( $3.data )[ 7 ] > '9' ) )
		{
			libcerror_error_set(
			 ( (cue_parser_state_t *) parser_state )->error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported index MSF.",
			 cue_parser_function );

			YYABORT;
		}
		cue_parser_copy_relative_msf_to_lba(
		 $3.data,
		 ( (cue_parser_state_t *) parser_state )->current_start_sector );

		/* The MSF can be relative to the start of the file
		 */
		if( ( (cue_parser_state_t *) parser_state )->current_start_sector != 0 )
		{
			if( ( ( (cue_parser_state_t *) parser_state )->current_index == 0 )
			 || ( ( (cue_parser_state_t *) parser_state )->current_index == 1 ) )
			{
				if( ( ( (cue_parser_state_t *) parser_state )->session_number_of_sectors == 0 )
				 || ( ( (cue_parser_state_t *) parser_state )->previous_track_type == LIBODRAW_TRACK_TYPE_AUDIO ) )
				{
					if( ( (cue_parser_state_t *) parser_state )->current_start_sector < ( (cue_parser_state_t *) parser_state )->previous_session_start_sector )
					{
						libcerror_error_set(
						 ( (cue_parser_state_t *) parser_state )->error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
						 "%s: invalid session start sector value preceeds previous.",
						 cue_parser_function );

						YYABORT;
					}
					( (cue_parser_state_t *) parser_state )->session_number_of_sectors = ( (cue_parser_state_t *) parser_state )->current_start_sector
					                                                                   - ( (cue_parser_state_t *) parser_state )->previous_session_start_sector;
				}
				if( ( ( (cue_parser_state_t *) parser_state )->lead_out_number_of_sectors == 0 )
				 || ( ( (cue_parser_state_t *) parser_state )->previous_track_type == LIBODRAW_TRACK_TYPE_AUDIO ) )
				{
					if( ( (cue_parser_state_t *) parser_state )->current_start_sector < ( (cue_parser_state_t *) parser_state )->previous_lead_out_start_sector )
					{
						libcerror_error_set(
						 ( (cue_parser_state_t *) parser_state )->error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
						 "%s: invalid lead-out start sector value preceeds previous.",
						 cue_parser_function );

						YYABORT;
					}
					( (cue_parser_state_t *) parser_state )->lead_out_number_of_sectors = ( (cue_parser_state_t *) parser_state )->current_start_sector
					                                                                    - ( (cue_parser_state_t *) parser_state )->previous_lead_out_start_sector;
				}
			}
			if( ( (cue_parser_state_t *) parser_state )->current_index == 1 )
			{
				if( ( (cue_parser_state_t *) parser_state )->track_number_of_sectors == 0 )
				{
					if( ( (cue_parser_state_t *) parser_state )->current_start_sector < ( (cue_parser_state_t *) parser_state )->previous_track_start_sector )
					{
						libcerror_error_set(
						 ( (cue_parser_state_t *) parser_state )->error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
						 "%s: invalid track start sector value preceeds previous.",
						 cue_parser_function );

						YYABORT;
					}
					( (cue_parser_state_t *) parser_state )->track_number_of_sectors = ( (cue_parser_state_t *) parser_state )->current_start_sector
					                                                                 - ( (cue_parser_state_t *) parser_state )->previous_track_start_sector;
				}
			}
		}
		if( ( (cue_parser_state_t *) parser_state )->current_index == 1 )
		{
			if( ( (cue_parser_state_t *) parser_state )->current_session > 1 )
			{
				if( libodraw_handle_append_session(
				     ( (cue_parser_state_t *) parser_state )->handle,
				     ( (cue_parser_state_t *) parser_state )->previous_session_start_sector,
				     ( (cue_parser_state_t *) parser_state )->session_number_of_sectors,
				     ( (cue_parser_state_t *) parser_state )->error ) != 1 )
				{
					libcerror_error_set(
					 ( (cue_parser_state_t *) parser_state )->error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
					 "%s: unable to append session.",
					 cue_parser_function );

					YYABORT;
				}
				( (cue_parser_state_t *) parser_state )->previous_session_start_sector = ( (cue_parser_state_t *) parser_state )->current_start_sector;
				( (cue_parser_state_t *) parser_state )->session_number_of_sectors     = 0;
			}
			if( ( (cue_parser_state_t *) parser_state )->current_lead_out > ( (cue_parser_state_t *) parser_state )->previous_lead_out )
			{
				if( libodraw_handle_append_lead_out(
				     ( (cue_parser_state_t *) parser_state )->handle,
				     ( (cue_parser_state_t *) parser_state )->previous_lead_out_start_sector,
				     ( (cue_parser_state_t *) parser_state )->lead_out_number_of_sectors,
				     ( (cue_parser_state_t *) parser_state )->error ) != 1 )
				{
					libcerror_error_set(
					 ( (cue_parser_state_t *) parser_state )->error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
					 "%s: unable to append lead-out.",
					 cue_parser_function );

					YYABORT;
				}
				( (cue_parser_state_t *) parser_state )->previous_lead_out          = ( (cue_parser_state_t *) parser_state )->current_lead_out;
				( (cue_parser_state_t *) parser_state )->lead_out_number_of_sectors = 0;
			}
			if( ( (cue_parser_state_t *) parser_state )->current_track > 1 )
			{
				if( ( (cue_parser_state_t *) parser_state )->previous_file_index < 0 )
				{
					( (cue_parser_state_t *) parser_state )->file_sector = ( (cue_parser_state_t *) parser_state )->previous_track_start_sector;

					( (cue_parser_state_t *) parser_state )->previous_file_index += 1;
				}
				( (cue_parser_state_t *) parser_state )->previous_file_sector = ( (cue_parser_state_t *) parser_state )->previous_track_start_sector
				                                                              - ( (cue_parser_state_t *) parser_state )->file_sector;

				if( libodraw_handle_append_track(
				     ( (cue_parser_state_t *) parser_state )->handle,
				     ( (cue_parser_state_t *) parser_state )->previous_track_start_sector,
				     ( (cue_parser_state_t *) parser_state )->track_number_of_sectors,
				     ( (cue_parser_state_t *) parser_state )->previous_track_type,
				     ( (cue_parser_state_t *) parser_state )->previous_file_index,
				     ( (cue_parser_state_t *) parser_state )->previous_file_sector,
				     ( (cue_parser_state_t *) parser_state )->error ) != 1 )
				{
					libcerror_error_set(
					 ( (cue_parser_state_t *) parser_state )->error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
					 "%s: unable to append track.",
					 cue_parser_function );

					YYABORT;
				}
				if( ( (cue_parser_state_t *) parser_state )->previous_file_index < ( (cue_parser_state_t *) parser_state )->current_file_index )
				{
					( (cue_parser_state_t *) parser_state )->file_sector = ( (cue_parser_state_t *) parser_state )->current_start_sector;

					( (cue_parser_state_t *) parser_state )->previous_file_index += 1;
				}
				( (cue_parser_state_t *) parser_state )->previous_track_start_sector = ( (cue_parser_state_t *) parser_state )->current_start_sector;
				( (cue_parser_state_t *) parser_state )->track_number_of_sectors     = 0;
			}
		}
	}
	;

cue_isrc
	: CUE_ISRC CUE_ISRC_CODE CUE_END_OF_LINE
	{
		cue_parser_rule_print(
		 "cue_isrc" );
	}
	;

cue_postgap
	: CUE_POSTGAP CUE_MSF CUE_END_OF_LINE
	{
		cue_parser_rule_print(
		 "cue_postgap" );
	}
	;

cue_pregap
	: CUE_PREGAP CUE_MSF CUE_END_OF_LINE
	{
		cue_parser_rule_print(
		 "cue_pregap" );
	}
	;

cue_remark_item
	: cue_lead_out
	| cue_original_media_type
	| cue_remark
	| cue_run_out
	| cue_session
	;

cue_lead_out
	: CUE_REMARK_LEAD_OUT CUE_MSF CUE_END_OF_LINE
	{
		cue_parser_rule_print(
		 "cue_lead_out" );

		if( ( $2.data == NULL )
		 || ( $2.length != 8 ) )
		{
			libcerror_error_set(
			 ( (cue_parser_state_t *) parser_state )->error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
			 "%s: invalid index MSF.",
			 cue_parser_function );

			YYABORT;
		}
		if( ( ( $2.data )[ 0 ] < '0' )
		 || ( ( $2.data )[ 0 ] > '9' )
		 || ( ( $2.data )[ 1 ] < '0' )
		 || ( ( $2.data )[ 1 ] > '9' )
		 || ( ( $2.data )[ 2 ] != ':' )
		 || ( ( $2.data )[ 3 ] < '0' )
		 || ( ( $2.data )[ 3 ] > '9' )
		 || ( ( $2.data )[ 4 ] < '0' )
		 || ( ( $2.data )[ 4 ] > '9' )
		 || ( ( $2.data )[ 5 ] != ':' )
		 || ( ( $2.data )[ 6 ] < '0' )
		 || ( ( $2.data )[ 6 ] > '9' )
		 || ( ( $2.data )[ 7 ] < '0' )
		 || ( ( $2.data )[ 7 ] > '9' ) )
		{
			libcerror_error_set(
			 ( (cue_parser_state_t *) parser_state )->error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported index MSF.",
			 cue_parser_function );

			YYABORT;
		}
		cue_parser_copy_relative_msf_to_lba(
		 $2.data,
		 ( (cue_parser_state_t *) parser_state )->previous_lead_out_start_sector );

		if( ( (cue_parser_state_t *) parser_state )->track_number_of_sectors == 0 )
		{
			if( ( (cue_parser_state_t *) parser_state )->previous_lead_out_start_sector < ( (cue_parser_state_t *) parser_state )->previous_track_start_sector )
			{
				libcerror_error_set(
				 ( (cue_parser_state_t *) parser_state )->error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: invalid lead-out start sector value preceeds previous track start sector.",
				 cue_parser_function );

				YYABORT;
			}
			( (cue_parser_state_t *) parser_state )->track_number_of_sectors = ( (cue_parser_state_t *) parser_state )->previous_lead_out_start_sector
			                                                                 - ( (cue_parser_state_t *) parser_state )->previous_track_start_sector;
		}
		( (cue_parser_state_t *) parser_state )->current_lead_out += 1;
	}
	;

cue_original_media_type
	: CUE_REMARK_ORIGINAL_MEDIA_TYPE CUE_KEYWORD_STRING CUE_END_OF_LINE
	{
		cue_parser_rule_print(
		 "cue_original_media_type" );
	}
	;

cue_remark
	: cue_remark_start error CUE_END_OF_LINE
	{
		cue_parser_rule_print(
		 "cue_remark" );

		cue_scanner_suppress_error = 0;
	}
	;

cue_remark_start
	: CUE_REMARK
	{
		/* The build-in rule error will gobble up all the tokens until the end-of-line
		 * because these are no syntax errors suppress the error output
		 */
		cue_scanner_suppress_error = 1;
	}
	;

cue_run_out
	: CUE_REMARK_RUN_OUT CUE_MSF CUE_END_OF_LINE
	{
		cue_parser_rule_print(
		 "cue_run_out" );

		if( ( $2.data == NULL )
		 || ( $2.length != 8 ) )
		{
			libcerror_error_set(
			 ( (cue_parser_state_t *) parser_state )->error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
			 "%s: invalid index MSF.",
			 cue_parser_function );

			YYABORT;
		}
		if( ( ( $2.data )[ 0 ] < '0' )
		 || ( ( $2.data )[ 0 ] > '9' )
		 || ( ( $2.data )[ 1 ] < '0' )
		 || ( ( $2.data )[ 1 ] > '9' )
		 || ( ( $2.data )[ 2 ] != ':' )
		 || ( ( $2.data )[ 3 ] < '0' )
		 || ( ( $2.data )[ 3 ] > '9' )
		 || ( ( $2.data )[ 4 ] < '0' )
		 || ( ( $2.data )[ 4 ] > '9' )
		 || ( ( $2.data )[ 5 ] != ':' )
		 || ( ( $2.data )[ 6 ] < '0' )
		 || ( ( $2.data )[ 6 ] > '9' )
		 || ( ( $2.data )[ 7 ] < '0' )
		 || ( ( $2.data )[ 7 ] > '9' ) )
		{
			libcerror_error_set(
			 ( (cue_parser_state_t *) parser_state )->error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported index MSF.",
			 cue_parser_function );

			YYABORT;
		}
		cue_parser_copy_relative_msf_to_lba(
		 $2.data,
		 ( (cue_parser_state_t *) parser_state )->current_start_sector );

		if( ( (cue_parser_state_t *) parser_state )->track_number_of_sectors == 0 )
		{
			if( ( (cue_parser_state_t *) parser_state )->current_start_sector < ( (cue_parser_state_t *) parser_state )->previous_track_start_sector )
			{
				libcerror_error_set(
				 ( (cue_parser_state_t *) parser_state )->error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: invalid track start sector value preceeds previous.",
				 cue_parser_function );

				YYABORT;
			}
			( (cue_parser_state_t *) parser_state )->track_number_of_sectors = ( (cue_parser_state_t *) parser_state )->current_start_sector
									                 - ( (cue_parser_state_t *) parser_state )->previous_track_start_sector;
		}
	}
	;

cue_session
	: CUE_REMARK_SESSION CUE_2DIGIT CUE_END_OF_LINE
	{
		cue_parser_rule_print(
		 "cue_session" );

		if( $2.data == NULL )
		{
			libcerror_error_set(
			 ( (cue_parser_state_t *) parser_state )->error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
			 "%s: invalid session number.",
			 cue_parser_function );

			YYABORT;
		}
		( (cue_parser_state_t *) parser_state )->previous_session = ( (cue_parser_state_t *) parser_state )->current_session;

		if( ( ( $2.data )[ 0 ] < '0' )
		 || ( ( $2.data )[ 0 ] > '9' ) )
		{
			libcerror_error_set(
			 ( (cue_parser_state_t *) parser_state )->error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported session number.",
			 cue_parser_function );

			YYABORT;
		}
		( (cue_parser_state_t *) parser_state )->current_session = ( $2.data )[ 0 ] - '0';

		if( $2.length == 2 )
		{
			( (cue_parser_state_t *) parser_state )->current_session *= 10;

			if( ( ( $2.data )[ 1 ] < '0' )
			 || ( ( $2.data )[ 1 ] > '9' ) )
			{
				libcerror_error_set(
				 ( (cue_parser_state_t *) parser_state )->error,
				 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
				 "%s: unsupported session number.",
				 cue_parser_function );

				YYABORT;
			}
			( (cue_parser_state_t *) parser_state )->current_session += ( $2.data )[ 1 ] - '0';
		}
		if( ( ( (cue_parser_state_t *) parser_state )->current_session != 0 )
		 && ( ( (cue_parser_state_t *) parser_state )->current_session != ( ( (cue_parser_state_t *) parser_state )->previous_session + 1 ) ) )
		{
			libcerror_error_set(
			 ( (cue_parser_state_t *) parser_state )->error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported session number - values are not sequential.",
			 cue_parser_function );

			YYABORT;
		}
	}
	;

cue_track
	: CUE_TRACK CUE_2DIGIT CUE_KEYWORD_STRING CUE_END_OF_LINE
	{
		cue_parser_rule_print(
		 "cue_track" );

		if( $2.data == NULL )
		{
			libcerror_error_set(
			 ( (cue_parser_state_t *) parser_state )->error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
			 "%s: invalid track number.",
			 cue_parser_function );

			YYABORT;
		}
		( (cue_parser_state_t *) parser_state )->previous_track = ( (cue_parser_state_t *) parser_state )->current_track;

		if( ( ( $2.data )[ 0 ] < '0' )
		 || ( ( $2.data )[ 0 ] > '9' ) )
		{
			libcerror_error_set(
			 ( (cue_parser_state_t *) parser_state )->error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported track number.",
			 cue_parser_function );

			YYABORT;
		}
		( (cue_parser_state_t *) parser_state )->current_track = ( $2.data )[ 0 ] - '0';

		if( $2.length == 2 )
		{
			( (cue_parser_state_t *) parser_state )->current_track *= 10;

			if( ( ( $2.data )[ 1 ] < '0' )
			 || ( ( $2.data )[ 1 ] > '9' ) )
			{
				libcerror_error_set(
				 ( (cue_parser_state_t *) parser_state )->error,
				 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
				 "%s: unsupported track number.",
				 cue_parser_function );

				YYABORT;
			}
			( (cue_parser_state_t *) parser_state )->current_track += ( $2.data )[ 1 ] - '0';
		}
		if( ( ( (cue_parser_state_t *) parser_state )->current_track != 0 )
		 && ( ( (cue_parser_state_t *) parser_state )->current_track != ( ( (cue_parser_state_t *) parser_state )->previous_track + 1 ) ) )
		{
			libcerror_error_set(
			 ( (cue_parser_state_t *) parser_state )->error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported track number - values are not sequential.",
			 cue_parser_function );

			YYABORT;
		}
		if( $3.data == NULL )
		{
			libcerror_error_set(
			 ( (cue_parser_state_t *) parser_state )->error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
			 "%s: invalid track number.",
			 cue_parser_function );

			YYABORT;
		}
		( (cue_parser_state_t *) parser_state )->previous_track_type = ( (cue_parser_state_t *) parser_state )->current_track_type;

		( (cue_parser_state_t *) parser_state )->previous_index     = 0;
		( (cue_parser_state_t *) parser_state )->current_index      = 0;
		( (cue_parser_state_t *) parser_state )->current_track_type = LIBODRAW_TRACK_TYPE_UNKNOWN;

		if( $3.length == 3 )
		{
			if( narrow_string_compare(
			     $3.data,
			     "CDG",
			     3 ) == 0 )
			{
				( (cue_parser_state_t *) parser_state )->current_track_type = LIBODRAW_TRACK_TYPE_CDG;
			}
		}
		else if( $3.length == 5 )
		{
			if( narrow_string_compare(
			     $3.data,
			     "AUDIO",
			     5 ) == 0 )
			{
				( (cue_parser_state_t *) parser_state )->current_track_type = LIBODRAW_TRACK_TYPE_AUDIO;
			}
		}
		else if( $3.length == 8 )
		{
			if( narrow_string_compare(
			     $3.data,
			     "CDI",
			     3 ) == 0 )
			{
				if( ( $3.data )[ 3 ] == '/' )
				{
					if( narrow_string_compare(
					     &( ( $3.data )[ 4 ] ),
					     "2336",
					     4 ) == 0 )
					{
						 ( (cue_parser_state_t *) parser_state )->current_track_type = LIBODRAW_TRACK_TYPE_CDI_2336;
					}
					else if( narrow_string_compare(
						  &( ( $3.data )[ 4 ] ),
						  "2352",
						  4 ) == 0 )
					{
						 ( (cue_parser_state_t *) parser_state )->current_track_type = LIBODRAW_TRACK_TYPE_CDI_2352;
					}
				}
			}
		}
		else if( $3.length == 10 )
		{
			if( narrow_string_compare(
			     $3.data,
			     "MODE",
			     4 ) == 0 )
			{
				if( ( $3.data )[ 5 ] == '/' )
				{
					if( ( $3.data )[ 4 ] == '1' )
					{
						if( narrow_string_compare(
						     &( ( $3.data )[ 6 ] ),
						     "2048",
						     4 ) == 0 )
						{
							 ( (cue_parser_state_t *) parser_state )->current_track_type = LIBODRAW_TRACK_TYPE_MODE1_2048;
						}
						else if( narrow_string_compare(
						          &( ( $3.data )[ 6 ] ),
						          "2352",
						          4 ) == 0 )
						{
							 ( (cue_parser_state_t *) parser_state )->current_track_type = LIBODRAW_TRACK_TYPE_MODE1_2352;
						}
					}
					else if( ( $3.data )[ 4 ] == '2' )
					{
						if( narrow_string_compare(
						     &( ( $3.data )[ 6 ] ),
						     "2048",
						     4 ) == 0 )
						{
							 ( (cue_parser_state_t *) parser_state )->current_track_type = LIBODRAW_TRACK_TYPE_MODE2_2048;
						}
						else if( narrow_string_compare(
						          &( ( $3.data )[ 6 ] ),
						          "2324",
						          4 ) == 0 )
						{
							 ( (cue_parser_state_t *) parser_state )->current_track_type = LIBODRAW_TRACK_TYPE_MODE2_2324;
						}
						else if( narrow_string_compare(
						          &( ( $3.data )[ 6 ] ),
						          "2336",
						          4 ) == 0 )
						{
							 ( (cue_parser_state_t *) parser_state )->current_track_type = LIBODRAW_TRACK_TYPE_MODE2_2336;
						}
						else if( narrow_string_compare(
						          &( ( $3.data )[ 6 ] ),
						          "2352",
						          4 ) == 0 )
						{
							 ( (cue_parser_state_t *) parser_state )->current_track_type = LIBODRAW_TRACK_TYPE_MODE2_2352;
						}
					}
				}
			}
		}
	}
	;

cue_empty_line
	: CUE_END_OF_LINE
	;

%%

int cue_parser_parse_buffer(
     libodraw_handle_t *handle,
     const uint8_t *buffer,
     size_t buffer_size,
     libcerror_error_t **error )
{
	cue_parser_state_t parser_state;
	
	YY_BUFFER_STATE buffer_state = NULL;
	size_t buffer_offset         = 0;
	int result                   = -1;

	if( buffer_size >= 3 )
	{
		if( ( buffer[ 0 ] == 0x0ef )
		 && ( buffer[ 1 ] == 0x0bb )
		 && ( buffer[ 2 ] == 0x0bf ) )
		{
			buffer_offset = 3;
		}
	}
	buffer_state = cue_scanner__scan_buffer(
	                (char *) &( buffer[ buffer_offset ] ),
	                buffer_size - buffer_offset );

	cue_scanner_buffer_offset = (size_t) buffer_offset;

	if( buffer_state != NULL )
	{
		parser_state.handle                         = handle;
		parser_state.error                          = error;
		parser_state.previous_file_index            = -1;
		parser_state.current_file_index             = -1;
		parser_state.file_type                      = 0;
		parser_state.previous_file_sector           = 0;
		parser_state.file_sector                    = 0;
		parser_state.previous_session_start_sector  = 0;
		parser_state.previous_lead_out_start_sector = 0;
		parser_state.previous_track_start_sector    = 0;
		parser_state.current_start_sector           = 0;
		parser_state.session_number_of_sectors      = 0;
		parser_state.lead_out_number_of_sectors     = 0;
		parser_state.track_number_of_sectors        = 0;
		parser_state.previous_track_type            = 0;
		parser_state.current_track_type             = 0;
		parser_state.previous_session               = 0;
		parser_state.current_session                = 0;
		parser_state.previous_lead_out              = 0;
		parser_state.current_lead_out               = 0;
		parser_state.previous_track                 = 0;
		parser_state.current_track                  = 0;
		parser_state.previous_index                 = 0;
		parser_state.current_index                  = 0;

		if( cue_scanner_parse(
		     &parser_state ) == 0 )
		{
			result = 1;
		}
		cue_scanner__delete_buffer(
		 buffer_state );

		if( parser_state.current_session > 0 )
		{
			if( libodraw_handle_append_session(
			     parser_state.handle,
			     parser_state.previous_session_start_sector,
			     0,
			     parser_state.error ) != 1 )
			{
				libcerror_error_set(
				 parser_state.error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
				 "%s: unable to append session.",
				 cue_parser_function );

				result = -1;
			}
		}
		if( parser_state.current_lead_out > parser_state.previous_lead_out )
		{
			if( libodraw_handle_append_lead_out(
			     parser_state.handle,
			     parser_state.previous_lead_out_start_sector,
			     0,
			     parser_state.error ) != 1 )
			{
				libcerror_error_set(
				 parser_state.error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
				 "%s: unable to append lead-out.",
				 cue_parser_function );

				result = -1;
			}
		}
		if( parser_state.current_track > 0 )
		{
			if( parser_state.previous_file_index < 0 )
			{
				parser_state.file_sector = parser_state.previous_track_start_sector;

				parser_state.previous_file_index += 1;
			}
			parser_state.previous_file_sector = parser_state.previous_track_start_sector
			                                  - parser_state.file_sector;

			if( libodraw_handle_append_track(
			     parser_state.handle,
			     parser_state.previous_track_start_sector,
			     0,
			     parser_state.current_track_type,
			     parser_state.current_file_index,
			     parser_state.previous_file_sector,
			     parser_state.error ) != 1 )
			{
				libcerror_error_set(
				 parser_state.error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
				 "%s: unable to append track.",
				 cue_parser_function );

				result = -1;
			}
		}
	}
	cue_scanner_lex_destroy();

	return( result );
}

