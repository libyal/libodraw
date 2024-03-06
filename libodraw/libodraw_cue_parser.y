%{
/*
 * CUE parser functions
 *
 * Copyright (C) 2010-2024, Joachim Metz <joachim.metz@gmail.com>
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

#define YYMALLOC	libodraw_cue_scanner_alloc
#define YYREALLOC	libodraw_cue_scanner_realloc
#define YYFREE		libodraw_cue_scanner_free

#define YYLEX_PARAM	NULL
#define YYPARSE_PARAM	parser_state

#if defined( HAVE_DEBUG_OUTPUT )
#define libodraw_cue_parser_rule_print( string ) \
	if( libcnotify_verbose != 0 ) libcnotify_printf( "libodraw_cue_parser: rule: %s\n", string )
#else
#define libodraw_cue_parser_rule_print( string )
#endif

#if !defined( CD_SECS )
/* seconds per minute */
#define CD_SECS			60
#endif

#if !defined( CD_FRAMES )
/* frames per second */
#define CD_FRAMES		75
#endif

%}

/* %name-prefix="libodraw_cue_scanner_" replaced by -p libodraw_cue_scanner_ */
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

typedef struct libodraw_cue_parser_state libodraw_cue_parser_state_t;

struct libodraw_cue_parser_state
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
int libodraw_cue_scanner_suppress_error;

extern \
int libodraw_cue_scanner_lex_destroy(
     void );

extern \
void *libodraw_cue_scanner_alloc(
       yy_size_t size );

extern \
void *libodraw_cue_scanner_realloc(
       void *buffer,
       yy_size_t size );

extern \
void libodraw_cue_scanner_free(
      void *buffer );

extern \
int libodraw_cue_scanner_lex(
     void *user_data );

extern \
void libodraw_cue_scanner_error(
      void *parser_state,
      const char *error_string );

extern \
YY_BUFFER_STATE libodraw_cue_scanner__scan_buffer(
                 char *buffer,
                 yy_size_t buffer_size );

extern \
void libodraw_cue_scanner__delete_buffer(
      YY_BUFFER_STATE buffer_state );

extern \
size_t libodraw_cue_scanner_buffer_offset;

static char *libodraw_cue_parser_function = "libodraw_cue_parser";

int libodraw_cue_parser_parse_number(
     const char *token,
     size_t token_size,
     int *number,
     libcerror_error_t **error );

int libodraw_cue_parser_parse_msf(
     const char *token,
     size_t token_size,
     uint64_t *lba,
     libcerror_error_t **error );

int libodraw_cue_parser_parse_track_type(
     const char *token,
     size_t token_size,
     uint8_t *track_type,
     libcerror_error_t **error );

int libodraw_cue_parser_parse_buffer(
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
%token CUE_CD_DA
%token CUE_CD_ROM
%token CUE_CD_ROM_XA
%token CUE_CD_TEXT
%token CUE_CDTEXTFILE
%token CUE_COPY
%token CUE_DATAFILE
%token CUE_FLAGS
%token CUE_FOUR_CHANNEL_AUDIO
%token CUE_FILE
%token CUE_INDEX
%token CUE_ISRC
%token CUE_NO_COPY
%token CUE_NO_PRE_EMPHASIS
%token CUE_POSTGAP
%token CUE_PRE_EMPHASIS
%token CUE_PREGAP
%token CUE_REMARK
%token CUE_TRACK
%token CUE_TWO_CHANNEL_AUDIO

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

/* Other tokens
 */
%token CUE_UNDEFINED

%%

/* Parser rules
 */

cue_main
	: cue_header_item cue_session_type cue_main_items cue_main_tracks
	| cue_header_item cue_main_items cue_file cue_main_items cue_main_tracks
	;

cue_header_item
	: /* empty */
	| cue_catalog
	;

cue_session_type
	: /* empty */
	| cue_cd_da
	| cue_cd_rom
	| cue_cd_rom_xa
	;

cue_main_items
	: /* empty */
	| cue_main_item cue_main_items
	;

/* TODO add support for cue_cd_text */
cue_main_item
	: cue_cdtextfile
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

/* TODO add support for cue_cd_text */
cue_main_track_trailing_item
	: cue_cdtext
	| cue_copy
	| cue_datafile
	| cue_four_channel_audio
	| cue_no_copy
	| cue_no_pre_emphasis
	| cue_postgap
	| cue_pre_emphasis
	| cue_two_channel_audio
	| cue_remark_item
	| cue_empty_line
	;

cue_catalog
	: CUE_CATALOG CUE_CATALOG_NUMBER CUE_END_OF_LINE
	{
		libodraw_cue_parser_rule_print(
		 "cue_catalog" );
	}
	;

cue_cdtext
	: cue_cdtext_type CUE_STRING CUE_END_OF_LINE
	{
		libodraw_cue_parser_rule_print(
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

cue_cd_da
	: CUE_CD_DA CUE_END_OF_LINE
	{
		libodraw_cue_parser_rule_print(
		 "cue_cd_da" );
	}
	;

cue_cd_rom
	: CUE_CD_ROM CUE_END_OF_LINE
	{
		libodraw_cue_parser_rule_print(
		 "cue_cd_rom" );
	}
	;

cue_cd_rom_xa
	: CUE_CD_ROM_XA CUE_END_OF_LINE
	{
		libodraw_cue_parser_rule_print(
		 "cue_cd_rom_xa" );
	}
	;

cue_cdtextfile
	: CUE_CDTEXTFILE CUE_STRING CUE_END_OF_LINE
	{
		libodraw_cue_parser_rule_print(
		 "cue_cdtextfile" );
	}
	;

cue_file
	: CUE_FILE CUE_STRING CUE_KEYWORD_STRING CUE_END_OF_LINE
	{
		libodraw_cue_parser_rule_print(
		 "cue_file" );

		if( $2.data == NULL )
		{
			libcerror_error_set(
			 ( (libodraw_cue_parser_state_t *) parser_state )->error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
			 "%s: invalid filename.",
			 libodraw_cue_parser_function );

			YYABORT;
		}
		if( $3.data == NULL )
		{
			libcerror_error_set(
			 ( (libodraw_cue_parser_state_t *) parser_state )->error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
			 "%s: invalid file type.",
			 libodraw_cue_parser_function );

			YYABORT;
		}
		( (libodraw_cue_parser_state_t *) parser_state )->file_type = LIBODRAW_FILE_TYPE_UNKNOWN;

		if( $3.length == 3 )
		{
			if( narrow_string_compare(
			     $3.data,
			     "MP3",
			     3 ) == 0 )
			{
				( (libodraw_cue_parser_state_t *) parser_state )->file_type = LIBODRAW_FILE_TYPE_AUDIO_MPEG1_LAYER3;
			}
		}
		else if( $3.length == 4 )
		{
			if( narrow_string_compare(
			     $3.data,
			     "AIFF",
			     4 ) == 0 )
			{
				( (libodraw_cue_parser_state_t *) parser_state )->file_type = LIBODRAW_FILE_TYPE_AUDIO_AIFF;
			}
			else if( narrow_string_compare(
			          $3.data,
			          "WAVE",
			          4 ) == 0 )
			{
				( (libodraw_cue_parser_state_t *) parser_state )->file_type = LIBODRAW_FILE_TYPE_AUDIO_WAVE;
			}
		}
		else if( $3.length == 6 )
		{
			if( narrow_string_compare(
			     $3.data,
			     "BINARY",
			     6 ) == 0 )
			{
				( (libodraw_cue_parser_state_t *) parser_state )->file_type = LIBODRAW_FILE_TYPE_BINARY_LITTLE_ENDIAN;
			}
		}
		else if( $3.length == 8 )
		{
			if( narrow_string_compare(
			     $3.data,
			     "MOTOROLA",
			     8 ) == 0 )
			{
				( (libodraw_cue_parser_state_t *) parser_state )->file_type = LIBODRAW_FILE_TYPE_BINARY_BIG_ENDIAN;
			}
		}
		if( libodraw_handle_append_data_file(
		     ( (libodraw_cue_parser_state_t *) parser_state )->handle,
		     $2.data,
		     $2.length,
		     ( (libodraw_cue_parser_state_t *) parser_state )->file_type,
		     ( (libodraw_cue_parser_state_t *) parser_state )->error ) != 1 )
		{
			libcerror_error_set(
			 ( (libodraw_cue_parser_state_t *) parser_state )->error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to append data file.",
			 libodraw_cue_parser_function );

			YYABORT;
		}
		( (libodraw_cue_parser_state_t *) parser_state )->current_file_index += 1;
	}
	;

cue_flags
	: CUE_FLAGS cue_flags_types CUE_END_OF_LINE
	{
		libodraw_cue_parser_rule_print(
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
		libodraw_cue_parser_rule_print(
		 "cue_index" );

		( (libodraw_cue_parser_state_t *) parser_state )->previous_index = ( (libodraw_cue_parser_state_t *) parser_state )->current_index;

		if( libodraw_cue_parser_parse_number(
		     $2.data,
		     $2.length,
		     &( ( (libodraw_cue_parser_state_t *) parser_state )->current_index ),
		     ( (libodraw_cue_parser_state_t *) parser_state )->error ) != 1 )
		{
			libcerror_error_set(
			 ( (libodraw_cue_parser_state_t *) parser_state )->error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to parse index number.",
			 libodraw_cue_parser_function );

			YYABORT;
		}
		if( ( ( (libodraw_cue_parser_state_t *) parser_state )->current_index != 0 )
		 && ( ( (libodraw_cue_parser_state_t *) parser_state )->current_index != ( ( (libodraw_cue_parser_state_t *) parser_state )->previous_index + 1 ) ) )
		{
			libcerror_error_set(
			 ( (libodraw_cue_parser_state_t *) parser_state )->error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported index number - values are not sequential.",
			 libodraw_cue_parser_function );

			YYABORT;
		}
		if( libodraw_cue_parser_parse_msf(
		     $3.data,
		     $3.length,
		     &( ( (libodraw_cue_parser_state_t *) parser_state )->current_start_sector ),
		     ( (libodraw_cue_parser_state_t *) parser_state )->error ) != 1 )
		{
			libcerror_error_set(
			 ( (libodraw_cue_parser_state_t *) parser_state )->error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to parse index MSF.",
			 libodraw_cue_parser_function );

			YYABORT;
		}
		/* The MSF can be relative to the start of the file
		 */
		if( ( (libodraw_cue_parser_state_t *) parser_state )->current_start_sector != 0 )
		{
			if( ( ( (libodraw_cue_parser_state_t *) parser_state )->current_index == 0 )
			 || ( ( (libodraw_cue_parser_state_t *) parser_state )->current_index == 1 ) )
			{
				if( ( ( (libodraw_cue_parser_state_t *) parser_state )->session_number_of_sectors == 0 )
				 || ( ( (libodraw_cue_parser_state_t *) parser_state )->previous_track_type == LIBODRAW_TRACK_TYPE_AUDIO ) )
				{
					if( ( (libodraw_cue_parser_state_t *) parser_state )->current_start_sector < ( (libodraw_cue_parser_state_t *) parser_state )->previous_session_start_sector )
					{
						libcerror_error_set(
						 ( (libodraw_cue_parser_state_t *) parser_state )->error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
						 "%s: invalid session start sector value precedes previous.",
						 libodraw_cue_parser_function );

						YYABORT;
					}
					( (libodraw_cue_parser_state_t *) parser_state )->session_number_of_sectors = ( (libodraw_cue_parser_state_t *) parser_state )->current_start_sector
					                                                                            - ( (libodraw_cue_parser_state_t *) parser_state )->previous_session_start_sector;
				}
				if( ( ( (libodraw_cue_parser_state_t *) parser_state )->lead_out_number_of_sectors == 0 )
				 || ( ( (libodraw_cue_parser_state_t *) parser_state )->previous_track_type == LIBODRAW_TRACK_TYPE_AUDIO ) )
				{
					if( ( (libodraw_cue_parser_state_t *) parser_state )->current_start_sector < ( (libodraw_cue_parser_state_t *) parser_state )->previous_lead_out_start_sector )
					{
						libcerror_error_set(
						 ( (libodraw_cue_parser_state_t *) parser_state )->error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
						 "%s: invalid lead-out start sector value precedes previous.",
						 libodraw_cue_parser_function );

						YYABORT;
					}
					( (libodraw_cue_parser_state_t *) parser_state )->lead_out_number_of_sectors = ( (libodraw_cue_parser_state_t *) parser_state )->current_start_sector
					                                                                             - ( (libodraw_cue_parser_state_t *) parser_state )->previous_lead_out_start_sector;
				}
			}
			if( ( (libodraw_cue_parser_state_t *) parser_state )->current_index == 1 )
			{
				if( ( (libodraw_cue_parser_state_t *) parser_state )->track_number_of_sectors == 0 )
				{
					if( ( (libodraw_cue_parser_state_t *) parser_state )->current_start_sector < ( (libodraw_cue_parser_state_t *) parser_state )->previous_track_start_sector )
					{
						libcerror_error_set(
						 ( (libodraw_cue_parser_state_t *) parser_state )->error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
						 "%s: invalid track start sector value precedes previous.",
						 libodraw_cue_parser_function );

						YYABORT;
					}
					( (libodraw_cue_parser_state_t *) parser_state )->track_number_of_sectors = ( (libodraw_cue_parser_state_t *) parser_state )->current_start_sector
					                                                                          - ( (libodraw_cue_parser_state_t *) parser_state )->previous_track_start_sector;
				}
			}
		}
		if( ( (libodraw_cue_parser_state_t *) parser_state )->current_index == 1 )
		{
			if( ( (libodraw_cue_parser_state_t *) parser_state )->current_session > 1 )
			{
				if( libodraw_handle_append_session(
				     ( (libodraw_cue_parser_state_t *) parser_state )->handle,
				     ( (libodraw_cue_parser_state_t *) parser_state )->previous_session_start_sector,
				     ( (libodraw_cue_parser_state_t *) parser_state )->session_number_of_sectors,
				     ( (libodraw_cue_parser_state_t *) parser_state )->error ) != 1 )
				{
					libcerror_error_set(
					 ( (libodraw_cue_parser_state_t *) parser_state )->error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
					 "%s: unable to append session.",
					 libodraw_cue_parser_function );

					YYABORT;
				}
				( (libodraw_cue_parser_state_t *) parser_state )->previous_session_start_sector = ( (libodraw_cue_parser_state_t *) parser_state )->current_start_sector;
				( (libodraw_cue_parser_state_t *) parser_state )->session_number_of_sectors     = 0;
			}
			if( ( (libodraw_cue_parser_state_t *) parser_state )->current_lead_out > ( (libodraw_cue_parser_state_t *) parser_state )->previous_lead_out )
			{
				if( libodraw_handle_append_lead_out(
				     ( (libodraw_cue_parser_state_t *) parser_state )->handle,
				     ( (libodraw_cue_parser_state_t *) parser_state )->previous_lead_out_start_sector,
				     ( (libodraw_cue_parser_state_t *) parser_state )->lead_out_number_of_sectors,
				     ( (libodraw_cue_parser_state_t *) parser_state )->error ) != 1 )
				{
					libcerror_error_set(
					 ( (libodraw_cue_parser_state_t *) parser_state )->error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
					 "%s: unable to append lead-out.",
					 libodraw_cue_parser_function );

					YYABORT;
				}
				( (libodraw_cue_parser_state_t *) parser_state )->previous_lead_out          = ( (libodraw_cue_parser_state_t *) parser_state )->current_lead_out;
				( (libodraw_cue_parser_state_t *) parser_state )->lead_out_number_of_sectors = 0;
			}
			if( ( (libodraw_cue_parser_state_t *) parser_state )->current_track > 1 )
			{
				if( ( (libodraw_cue_parser_state_t *) parser_state )->previous_file_index < 0 )
				{
					( (libodraw_cue_parser_state_t *) parser_state )->file_sector = ( (libodraw_cue_parser_state_t *) parser_state )->previous_track_start_sector;

					( (libodraw_cue_parser_state_t *) parser_state )->previous_file_index += 1;
				}
				( (libodraw_cue_parser_state_t *) parser_state )->previous_file_sector = ( (libodraw_cue_parser_state_t *) parser_state )->previous_track_start_sector
				                                                                       - ( (libodraw_cue_parser_state_t *) parser_state )->file_sector;

				if( libodraw_handle_append_track(
				     ( (libodraw_cue_parser_state_t *) parser_state )->handle,
				     ( (libodraw_cue_parser_state_t *) parser_state )->previous_track_start_sector,
				     ( (libodraw_cue_parser_state_t *) parser_state )->track_number_of_sectors,
				     ( (libodraw_cue_parser_state_t *) parser_state )->previous_track_type,
				     ( (libodraw_cue_parser_state_t *) parser_state )->previous_file_index,
				     ( (libodraw_cue_parser_state_t *) parser_state )->previous_file_sector,
				     ( (libodraw_cue_parser_state_t *) parser_state )->error ) != 1 )
				{
					libcerror_error_set(
					 ( (libodraw_cue_parser_state_t *) parser_state )->error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
					 "%s: unable to append track.",
					 libodraw_cue_parser_function );

					YYABORT;
				}
				if( ( (libodraw_cue_parser_state_t *) parser_state )->previous_file_index < ( (libodraw_cue_parser_state_t *) parser_state )->current_file_index )
				{
					( (libodraw_cue_parser_state_t *) parser_state )->file_sector = ( (libodraw_cue_parser_state_t *) parser_state )->current_start_sector;

					( (libodraw_cue_parser_state_t *) parser_state )->previous_file_index += 1;
				}
				( (libodraw_cue_parser_state_t *) parser_state )->previous_track_start_sector = ( (libodraw_cue_parser_state_t *) parser_state )->current_start_sector;
				( (libodraw_cue_parser_state_t *) parser_state )->track_number_of_sectors     = 0;
			}
		}
	}
	;

cue_copy
	: CUE_COPY CUE_END_OF_LINE
	{
		libodraw_cue_parser_rule_print(
		 "cue_copy" );
	}
	;

cue_datafile
	: CUE_DATAFILE CUE_STRING CUE_MSF CUE_END_OF_LINE
	{
		libodraw_cue_parser_rule_print(
		 "cue_datafile" );

		if( $2.data == NULL )
		{
			libcerror_error_set(
			 ( (libodraw_cue_parser_state_t *) parser_state )->error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
			 "%s: invalid filename.",
			 libodraw_cue_parser_function );

			YYABORT;
		}
		if( libodraw_cue_parser_parse_msf(
		     $3.data,
		     $3.length,
		     &( ( (libodraw_cue_parser_state_t *) parser_state )->track_number_of_sectors ),
		     ( (libodraw_cue_parser_state_t *) parser_state )->error ) != 1 )
		{
			libcerror_error_set(
			 ( (libodraw_cue_parser_state_t *) parser_state )->error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to parse datafile MSF.",
			 libodraw_cue_parser_function );

			YYABORT;
		}
		( (libodraw_cue_parser_state_t *) parser_state )->file_type = LIBODRAW_FILE_TYPE_BINARY_LITTLE_ENDIAN;

		if( libodraw_handle_append_data_file(
		     ( (libodraw_cue_parser_state_t *) parser_state )->handle,
		     $2.data,
		     $2.length,
		     ( (libodraw_cue_parser_state_t *) parser_state )->file_type,
		     ( (libodraw_cue_parser_state_t *) parser_state )->error ) != 1 )
		{
			libcerror_error_set(
			 ( (libodraw_cue_parser_state_t *) parser_state )->error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to append data file.",
			 libodraw_cue_parser_function );

			YYABORT;
		}
		if( ( (libodraw_cue_parser_state_t *) parser_state )->previous_file_index < 0 )
		{
			( (libodraw_cue_parser_state_t *) parser_state )->file_sector = ( (libodraw_cue_parser_state_t *) parser_state )->previous_track_start_sector;

			( (libodraw_cue_parser_state_t *) parser_state )->previous_file_index += 1;
		}
		( (libodraw_cue_parser_state_t *) parser_state )->previous_file_sector = ( (libodraw_cue_parser_state_t *) parser_state )->previous_track_start_sector
		                                                                       - ( (libodraw_cue_parser_state_t *) parser_state )->file_sector;

		if( libodraw_handle_append_track(
		     ( (libodraw_cue_parser_state_t *) parser_state )->handle,
		     ( (libodraw_cue_parser_state_t *) parser_state )->previous_track_start_sector,
		     ( (libodraw_cue_parser_state_t *) parser_state )->track_number_of_sectors,
		     ( (libodraw_cue_parser_state_t *) parser_state )->current_track_type,
		     ( (libodraw_cue_parser_state_t *) parser_state )->previous_file_index,
		     ( (libodraw_cue_parser_state_t *) parser_state )->previous_file_sector,
		     ( (libodraw_cue_parser_state_t *) parser_state )->error ) != 1 )
		{
			libcerror_error_set(
			 ( (libodraw_cue_parser_state_t *) parser_state )->error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to append track.",
			 libodraw_cue_parser_function );

			YYABORT;
		}
		( (libodraw_cue_parser_state_t *) parser_state )->current_file_index += 1;
	}
	;

cue_four_channel_audio
	: CUE_FOUR_CHANNEL_AUDIO CUE_END_OF_LINE
	{
		libodraw_cue_parser_rule_print(
		 "cue_four_channel_audio" );
	}
	;

cue_isrc
	: CUE_ISRC CUE_ISRC_CODE CUE_END_OF_LINE
	{
		libodraw_cue_parser_rule_print(
		 "cue_isrc" );
	}
	;

cue_no_copy
	: CUE_NO_COPY CUE_END_OF_LINE
	{
		libodraw_cue_parser_rule_print(
		 "cue_no_copy" );
	}
	;

cue_no_pre_emphasis
	: CUE_NO_PRE_EMPHASIS CUE_END_OF_LINE
	{
		libodraw_cue_parser_rule_print(
		 "cue_no_pre_emphasis" );
	}
	;

cue_postgap
	: CUE_POSTGAP CUE_MSF CUE_END_OF_LINE
	{
		libodraw_cue_parser_rule_print(
		 "cue_postgap" );
	}
	;

cue_pre_emphasis
	: CUE_PRE_EMPHASIS CUE_END_OF_LINE
	{
		libodraw_cue_parser_rule_print(
		 "cue_pre_emphasis" );
	}
	;

cue_pregap
	: CUE_PREGAP CUE_MSF CUE_END_OF_LINE
	{
		libodraw_cue_parser_rule_print(
		 "cue_pregap" );
	}
	;

cue_two_channel_audio
	: CUE_TWO_CHANNEL_AUDIO CUE_END_OF_LINE
	{
		libodraw_cue_parser_rule_print(
		 "cue_two_channel_audio" );
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
		libodraw_cue_parser_rule_print(
		 "cue_lead_out" );

		if( libodraw_cue_parser_parse_msf(
		     $2.data,
		     $2.length,
		     &( ( (libodraw_cue_parser_state_t *) parser_state )->previous_lead_out_start_sector ),
		     ( (libodraw_cue_parser_state_t *) parser_state )->error ) != 1 )
		{
			libcerror_error_set(
			 ( (libodraw_cue_parser_state_t *) parser_state )->error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to parse lead-out MSF.",
			 libodraw_cue_parser_function );

			YYABORT;
		}
		if( ( (libodraw_cue_parser_state_t *) parser_state )->track_number_of_sectors == 0 )
		{
			if( ( (libodraw_cue_parser_state_t *) parser_state )->previous_lead_out_start_sector < ( (libodraw_cue_parser_state_t *) parser_state )->previous_track_start_sector )
			{
				libcerror_error_set(
				 ( (libodraw_cue_parser_state_t *) parser_state )->error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: invalid lead-out start sector value precedes previous track start sector.",
				 libodraw_cue_parser_function );

				YYABORT;
			}
			( (libodraw_cue_parser_state_t *) parser_state )->track_number_of_sectors = ( (libodraw_cue_parser_state_t *) parser_state )->previous_lead_out_start_sector
			                                                                          - ( (libodraw_cue_parser_state_t *) parser_state )->previous_track_start_sector;
		}
		( (libodraw_cue_parser_state_t *) parser_state )->current_lead_out += 1;
	}
	;

cue_original_media_type
	: CUE_REMARK_ORIGINAL_MEDIA_TYPE CUE_KEYWORD_STRING CUE_END_OF_LINE
	{
		libodraw_cue_parser_rule_print(
		 "cue_original_media_type" );
	}
	;

cue_remark
	: cue_remark_start error CUE_END_OF_LINE
	{
		libodraw_cue_parser_rule_print(
		 "cue_remark" );

		libodraw_cue_scanner_suppress_error = 0;
	}
	;

cue_remark_start
	: CUE_REMARK
	{
		/* The build-in rule error will gobble up all the tokens until the end-of-line
		 * because these are no syntax errors suppress the error output
		 */
		libodraw_cue_scanner_suppress_error = 1;
	}
	;

cue_run_out
	: CUE_REMARK_RUN_OUT CUE_MSF CUE_END_OF_LINE
	{
		libodraw_cue_parser_rule_print(
		 "cue_run_out" );

		if( libodraw_cue_parser_parse_msf(
		     $2.data,
		     $2.length,
		     &( ( (libodraw_cue_parser_state_t *) parser_state )->current_start_sector ),
		     ( (libodraw_cue_parser_state_t *) parser_state )->error ) != 1 )
		{
			libcerror_error_set(
			 ( (libodraw_cue_parser_state_t *) parser_state )->error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to parse run-out MSF.",
			 libodraw_cue_parser_function );

			YYABORT;
		}
		if( ( (libodraw_cue_parser_state_t *) parser_state )->track_number_of_sectors == 0 )
		{
			if( ( (libodraw_cue_parser_state_t *) parser_state )->current_start_sector < ( (libodraw_cue_parser_state_t *) parser_state )->previous_track_start_sector )
			{
				libcerror_error_set(
				 ( (libodraw_cue_parser_state_t *) parser_state )->error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: invalid track start sector value precedes previous.",
				 libodraw_cue_parser_function );

				YYABORT;
			}
			( (libodraw_cue_parser_state_t *) parser_state )->track_number_of_sectors = ( (libodraw_cue_parser_state_t *) parser_state )->current_start_sector
									                          - ( (libodraw_cue_parser_state_t *) parser_state )->previous_track_start_sector;
		}
	}
	;

cue_session
	: CUE_REMARK_SESSION CUE_2DIGIT CUE_END_OF_LINE
	{
		libodraw_cue_parser_rule_print(
		 "cue_session" );

		( (libodraw_cue_parser_state_t *) parser_state )->previous_session = ( (libodraw_cue_parser_state_t *) parser_state )->current_session;

		if( libodraw_cue_parser_parse_number(
		     $2.data,
		     $2.length,
		     &( ( (libodraw_cue_parser_state_t *) parser_state )->current_session ),
		     ( (libodraw_cue_parser_state_t *) parser_state )->error ) != 1 )
		{
			libcerror_error_set(
			 ( (libodraw_cue_parser_state_t *) parser_state )->error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to parse session number.",
			 libodraw_cue_parser_function );

			YYABORT;
		}
		if( ( ( (libodraw_cue_parser_state_t *) parser_state )->current_session != 0 )
		 && ( ( (libodraw_cue_parser_state_t *) parser_state )->current_session != ( ( (libodraw_cue_parser_state_t *) parser_state )->previous_session + 1 ) ) )
		{
			libcerror_error_set(
			 ( (libodraw_cue_parser_state_t *) parser_state )->error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported session number - values are not sequential.",
			 libodraw_cue_parser_function );

			YYABORT;
		}
	}
	;

cue_track
	: CUE_TRACK CUE_KEYWORD_STRING CUE_END_OF_LINE
	{
		libodraw_cue_parser_rule_print(
		 "cue_track" );

		if( ( (libodraw_cue_parser_state_t *) parser_state )->current_track != 0 )
		{
			libcerror_error_set(
			 ( (libodraw_cue_parser_state_t *) parser_state )->error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported track number - only single track supported.",
			 libodraw_cue_parser_function );

			YYABORT;
		}
		( (libodraw_cue_parser_state_t *) parser_state )->previous_track_type = ( (libodraw_cue_parser_state_t *) parser_state )->current_track_type;

		if( libodraw_cue_parser_parse_track_type(
		     $2.data,
		     $2.length,
		     &( ( (libodraw_cue_parser_state_t *) parser_state )->current_track_type ),
		     ( (libodraw_cue_parser_state_t *) parser_state )->error ) != 1 )
		{
			libcerror_error_set(
			 ( (libodraw_cue_parser_state_t *) parser_state )->error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to parse track type.",
			 libodraw_cue_parser_function );

			YYABORT;
		}
		( (libodraw_cue_parser_state_t *) parser_state )->previous_index = 0;
		( (libodraw_cue_parser_state_t *) parser_state )->current_index  = 0;
	}
	| CUE_TRACK CUE_2DIGIT CUE_KEYWORD_STRING CUE_END_OF_LINE
	{
		libodraw_cue_parser_rule_print(
		 "cue_track" );

		( (libodraw_cue_parser_state_t *) parser_state )->previous_track = ( (libodraw_cue_parser_state_t *) parser_state )->current_track;

		if( libodraw_cue_parser_parse_number(
		     $2.data,
		     $2.length,
		     &( ( (libodraw_cue_parser_state_t *) parser_state )->current_track ),
		     ( (libodraw_cue_parser_state_t *) parser_state )->error ) != 1 )
		{
			libcerror_error_set(
			 ( (libodraw_cue_parser_state_t *) parser_state )->error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to parse track number.",
			 libodraw_cue_parser_function );

			YYABORT;
		}
		if( ( ( (libodraw_cue_parser_state_t *) parser_state )->current_track != 0 )
		 && ( ( (libodraw_cue_parser_state_t *) parser_state )->current_track != ( ( (libodraw_cue_parser_state_t *) parser_state )->previous_track + 1 ) ) )
		{
			libcerror_error_set(
			 ( (libodraw_cue_parser_state_t *) parser_state )->error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported track number - values are not sequential.",
			 libodraw_cue_parser_function );

			YYABORT;
		}
		( (libodraw_cue_parser_state_t *) parser_state )->previous_track_type = ( (libodraw_cue_parser_state_t *) parser_state )->current_track_type;

		if( libodraw_cue_parser_parse_track_type(
		     $3.data,
		     $3.length,
		     &( ( (libodraw_cue_parser_state_t *) parser_state )->current_track_type ),
		     ( (libodraw_cue_parser_state_t *) parser_state )->error ) != 1 )
		{
			libcerror_error_set(
			 ( (libodraw_cue_parser_state_t *) parser_state )->error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to parse track type.",
			 libodraw_cue_parser_function );

			YYABORT;
		}
		( (libodraw_cue_parser_state_t *) parser_state )->previous_index = 0;
		( (libodraw_cue_parser_state_t *) parser_state )->current_index  = 0;
	}
	;

cue_empty_line
	: CUE_END_OF_LINE
	;

%%

/* Parses a number
 * Returns 1 if successful or -1 on error
 */
int libodraw_cue_parser_parse_number(
     const char *token,
     size_t token_size,
     int *number,
     libcerror_error_t **error )
{
	static char *function = "libodraw_cue_parser_parse_number";
	int safe_number       = 0;

	if( token == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid token.",
		 function );

		return( -1 );
	}
	if( ( token_size < 1 )
	 || ( token_size > 2 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid token size value out of bounds.",
		 function );

		return( -1 );
	}
	if( number == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid number.",
		 function );

		return( -1 );
	}
	if( ( token[ 0 ] < '0' )
	 || ( token[ 0 ] > '9' ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported first digit of number token.",
		 function );

		return( -1 );
	}
	safe_number = token[ 0 ] - '0';

	if( token_size == 2 )
	{
		safe_number *= 10;

		if( ( token[ 1 ] < '0' )
		 || ( token[ 1 ] > '9' ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported second digit of number token.",
			 function );

			return( -1 );
		}
		safe_number += token[ 1 ] - '0';
	}
	*number = safe_number;

	return( 1 );
}

/* Parses a MFS (minutes:seconds:frames) value and converts it into a logical block address (LBA)
 * Returns 1 if successful or -1 on error
 */
int libodraw_cue_parser_parse_msf(
     const char *token,
     size_t token_size,
     uint64_t *lba,
     libcerror_error_t **error )
{
	static char *function = "libodraw_cue_parser_parse_msf";
	uint64_t safe_lba     = 0;

	if( token == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid token.",
		 function );

		return( -1 );
	}
	if( token_size != 8 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid token size value out of bounds.",
		 function );

		return( -1 );
	}
	if( lba == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid LBA.",
		 function );

		return( -1 );
	}
	if( ( token[ 0 ] < '0' )
	 || ( token[ 0 ] > '9' )
	 || ( token[ 1 ] < '0' )
	 || ( token[ 1 ] > '9' )
	 || ( token[ 2 ] != ':' )
	 || ( token[ 3 ] < '0' )
	 || ( token[ 3 ] > '9' )
	 || ( token[ 4 ] < '0' )
	 || ( token[ 4 ] > '9' )
	 || ( token[ 5 ] != ':' )
	 || ( token[ 6 ] < '0' )
	 || ( token[ 6 ] > '9' )
	 || ( token[ 7 ] < '0' )
	 || ( token[ 7 ] > '9' ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported MSF token.",
		 function );

		return( -1 );
	}
	/* Note that the MSF are relative, so there is no need for the MSF offset correction
	 */
        safe_lba  = ( ( token[ 0 ] - '0' ) * 10 ) + ( token[ 1 ] - '0' ); \
        safe_lba *= CD_SECS; \
        safe_lba += ( ( token[ 3 ] - '0' ) * 10 ) + ( token[ 4 ] - '0' ); \
        safe_lba *= CD_FRAMES; \
        safe_lba += ( ( token[ 6 ] - '0' ) * 10 ) + ( token[ 7 ] - '0' );

	*lba = safe_lba;

	return( 1 );
}

/* Parses a track type
 * Returns 1 if successful or -1 on error
 */
int libodraw_cue_parser_parse_track_type(
     const char *token,
     size_t token_size,
     uint8_t *track_type,
     libcerror_error_t **error )
{
	static char *function = "libodraw_cue_parser_parse_track_type";

	if( token == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid token.",
		 function );

		return( -1 );
	}
	if( token_size < 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid token size value out of bounds.",
		 function );

		return( -1 );
	}
	if( track_type == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid track type.",
		 function );

		return( -1 );
	}
	*track_type = LIBODRAW_TRACK_TYPE_UNKNOWN;

	if( token_size == 3 )
	{
		if( narrow_string_compare(
		     token,
		     "CDG",
		     3 ) == 0 )
		{
			*track_type = LIBODRAW_TRACK_TYPE_CDG;
		}
	}
	else if( token_size == 5 )
	{
		if( narrow_string_compare(
		     token,
		     "AUDIO",
		     5 ) == 0 )
		{
			*track_type = LIBODRAW_TRACK_TYPE_AUDIO;
		}
	}
	else if( token_size == 8 )
	{
		if( narrow_string_compare(
		     token,
		     "CDI",
		     3 ) == 0 )
		{
			if( token[ 3 ] == '/' )
			{
				if( narrow_string_compare(
				     &( token[ 4 ] ),
				     "2336",
				     4 ) == 0 )
				{
					 *track_type = LIBODRAW_TRACK_TYPE_CDI_2336;
				}
				else if( narrow_string_compare(
					  &( token[ 4 ] ),
					  "2352",
					  4 ) == 0 )
				{
					 *track_type = LIBODRAW_TRACK_TYPE_CDI_2352;
				}
			}
		}
	}
	else if( token_size == 9 )
	{
		if( narrow_string_compare(
		     token,
		     "MODE1_RAW",
		     9 ) == 0 )
		{
			*track_type = LIBODRAW_TRACK_TYPE_MODE1_2352;
		}
		else if( narrow_string_compare(
		          token,
		          "MODE2_RAW",
		          9 ) == 0 )
		{
			*track_type = LIBODRAW_TRACK_TYPE_MODE2_2352;
		}
	}
	else if( token_size == 10 )
	{
		if( narrow_string_compare(
		     token,
		     "MODE",
		     4 ) == 0 )
		{
			if( token[ 5 ] == '/' )
			{
				if( token[ 4 ] == '1' )
				{
					if( narrow_string_compare(
					     &( token[ 6 ] ),
					     "2048",
					     4 ) == 0 )
					{
						 *track_type = LIBODRAW_TRACK_TYPE_MODE1_2048;
					}
					else if( narrow_string_compare(
						  &( token[ 6 ] ),
						  "2352",
						  4 ) == 0 )
					{
						 *track_type = LIBODRAW_TRACK_TYPE_MODE1_2352;
					}
				}
				else if( token[ 4 ] == '2' )
				{
					if( narrow_string_compare(
					     &( token[ 6 ] ),
					     "2048",
					     4 ) == 0 )
					{
						 *track_type = LIBODRAW_TRACK_TYPE_MODE2_2048;
					}
					else if( narrow_string_compare(
						  &( token[ 6 ] ),
						  "2324",
						  4 ) == 0 )
					{
						 *track_type = LIBODRAW_TRACK_TYPE_MODE2_2324;
					}
					else if( narrow_string_compare(
						  &( token[ 6 ] ),
						  "2336",
						  4 ) == 0 )
					{
						 *track_type = LIBODRAW_TRACK_TYPE_MODE2_2336;
					}
					else if( narrow_string_compare(
						  &( token[ 6 ] ),
						  "2352",
						  4 ) == 0 )
					{
						 *track_type = LIBODRAW_TRACK_TYPE_MODE2_2352;
					}
				}
			}
		}
	}
	return( 1 );
}

/* Parses a CUE file
 * Returns 1 if successful or -1 on error
 */
int libodraw_cue_parser_parse_buffer(
     libodraw_handle_t *handle,
     const uint8_t *buffer,
     size_t buffer_size,
     libcerror_error_t **error )
{
	libodraw_cue_parser_state_t parser_state;
	
	static char *function        = "libodraw_cue_parser_parse_buffer";
	YY_BUFFER_STATE buffer_state = NULL;
	size_t buffer_offset         = 0;
	int result                   = -1;

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
	if( buffer_size >= 3 )
	{
		if( ( buffer[ 0 ] == 0x0ef )
		 && ( buffer[ 1 ] == 0x0bb )
		 && ( buffer[ 2 ] == 0x0bf ) )
		{
			buffer_offset = 3;
		}
	}
	buffer_state = libodraw_cue_scanner__scan_buffer(
	                (char *) &( buffer[ buffer_offset ] ),
	                buffer_size - buffer_offset );

	libodraw_cue_scanner_buffer_offset = (size_t) buffer_offset;

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

		if( libodraw_cue_scanner_parse(
		     &parser_state ) == 0 )
		{
			result = 1;
		}
		libodraw_cue_scanner__delete_buffer(
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
				 function );

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
				 function );

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
				 function );

				result = -1;
			}
		}
	}
	libodraw_cue_scanner_lex_destroy();

	return( result );
}

