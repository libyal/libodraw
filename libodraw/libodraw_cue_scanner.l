%option prefix="cue_scanner_" outfile="lex.yy.c"
%option never-interactive 8bit
%option noinput nounput noyylineno nounistd
%option noyyalloc noyyrealloc noyyfree

%{
/*
 * CUE scanner functions
 *
 * Copyright (C) 2010-2022, Joachim Metz <joachim.metz@gmail.com>
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

#include "libodraw_cue_parser.h"
#include "libodraw_libcnotify.h"
#include "libodraw_unused.h"

#define YYLEX_PARAM	NULL

int cue_scanner_suppress_error   = 0;
size_t cue_scanner_buffer_offset = 0;

#define YY_USER_ACTION	cue_scanner_buffer_offset += (size_t) cue_scanner_leng;

#if defined( HAVE_DEBUG_OUTPUT )
#define cue_scanner_token_print( string ) \
	if( libcnotify_verbose != 0 ) libcnotify_printf( "cue_scanner: offset: %" PRIzd " token: %s\n", cue_scanner_buffer_offset, string )
#else
#define cue_scanner_token_print( string )
#endif

%}

cue_2digit		[0-9][0-9]

/* The catalog number is a 13 digit number */
cue_catalog_number	[0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9]

cue_comments		([;]|[/][/])[ ][^\r\n]*

/* The ISRC code is a 12 character value, first 5 are alpha numeric, last 7 are numeric */
cue_isrc_code		[A-Za-z0-9][A-Za-z0-9][A-Za-z0-9][A-Za-z0-9][A-Za-z0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9]

cue_keyword		[A-Z0-9/_]+

/* The MSF consists of mm:ss:ff (minutes:seconds:frames) */
cue_msf			[0-9][0-9]:[0-9][0-9]:[0-9][0-9]

end_of_line		[\r\n|\n|\r]

string_double_quoted	["]([^"\x00-\x08\x0a-\x1f\x7f]|\\["]){0,256}["]
string_single_quoted	[']([^'\x00-\x08\x0a-\x1f\x7f]|\\[']){0,256}[']
string_unquoted		[^\x00-\x20\x7f]+

white_space		[\a\b\c\e\f\t\v ]+

%%

CATALOG {
	cue_scanner_token_print(
	 "CUE_CATALOG" );

	return( CUE_CATALOG );
}

CD_DA {
	cue_scanner_token_print(
	 "CUE_CD_DA" );

	return( CUE_CD_DA );
}

CD_ROM {
	cue_scanner_token_print(
	 "CUE_CD_ROM" );

	return( CUE_CD_ROM );
}

CD_ROM_XA {
	cue_scanner_token_print(
	 "CUE_CD_ROM_XA" );

	return( CUE_CD_ROM_XA );
}

CD_TEXT {
	cue_scanner_token_print(
	 "CUE_CD_TEXT" );

	return( CUE_CD_TEXT );
}

CDTEXTFILE {
	cue_scanner_token_print(
	 "CUE_CDTEXTFILE" );

	return( CUE_CDTEXTFILE );
}

COPY {
	cue_scanner_token_print(
	 "CUE_COPY" );

	return( CUE_COPY );
}

DATAFILE {
	cue_scanner_token_print(
	 "CUE_DATAFILE" );

	return( CUE_DATAFILE );
}

FILE {
	cue_scanner_token_print(
	 "CUE_FILE" );

	return( CUE_FILE );
}

FLAGS {
	cue_scanner_token_print(
	 "CUE_FLAGS" );

	return( CUE_FLAGS );
}

FOUR_CHANNEL_AUDIO {
	cue_scanner_token_print(
	 "CUE_FOUR_CHANNEL_AUDIO" );

	return( CUE_FOUR_CHANNEL_AUDIO );
}

INDEX {
	cue_scanner_token_print(
	 "CUE_INDEX" );

	return( CUE_INDEX );
}

ISRC {
	cue_scanner_token_print(
	 "CUE_ISRC" );

	return( CUE_ISRC );
}

NO[ ]COPY {
	cue_scanner_token_print(
	 "CUE_NO_COPY" );

	return( CUE_NO_COPY );
}

NO[ ]PRE_EMPHASIS {
	cue_scanner_token_print(
	 "CUE_NO_PRE_EMPHASIS" );

	return( CUE_NO_PRE_EMPHASIS );
}

POSTGAP {
	cue_scanner_token_print(
	 "CUE_POSTGAP" );

	return( CUE_POSTGAP );
}

PRE_EMPHASIS {
	cue_scanner_token_print(
	 "CUE_PRE_EMPHASIS" );

	return( CUE_PRE_EMPHASIS );
}

PREGAP {
	cue_scanner_token_print(
	 "CUE_PREGAP" );

	return( CUE_PREGAP );
}

TRACK {
	cue_scanner_token_print(
	 "CUE_TRACK" );

	return( CUE_TRACK );
}

TWO_CHANNEL_AUDIO {
	cue_scanner_token_print(
	 "CUE_TWO_CHANNEL_AUDIO" );

	return( CUE_TWO_CHANNEL_AUDIO );
}

ARRANGER {
	cue_scanner_token_print(
	 "CUE_CDTEXT_ARRANGER" );

	return( CUE_CDTEXT_ARRANGER );
}

COMPOSER {
	cue_scanner_token_print(
	 "CUE_CDTEXT_COMPOSER" );

	return( CUE_CDTEXT_COMPOSER );
}

DISC_ID {
	cue_scanner_token_print(
	 "CUE_CDTEXT_DISC_ID" );

	return( CUE_CDTEXT_DISC_ID );
}

GENRE {
	cue_scanner_token_print(
	 "CUE_CDTEXT_GENRE" );

	return( CUE_CDTEXT_GENRE );
}

MESSAGE {
	cue_scanner_token_print(
	 "CUE_CDTEXT_MESSAGE" );

	return( CUE_CDTEXT_MESSAGE );
}

PERFORMER {
	cue_scanner_token_print(
	 "CUE_CDTEXT_PERFORMER" );

	return( CUE_CDTEXT_PERFORMER );
}

SIZE_INFO {
	cue_scanner_token_print(
	 "CUE_CDTEXT_SIZE_INFO" );

	return( CUE_CDTEXT_SIZE_INFO );
}

SONGWRITER {
	cue_scanner_token_print(
	 "CUE_CDTEXT_SONGWRITER" );

	return( CUE_CDTEXT_SONGWRITER );
}

TITLE {
	cue_scanner_token_print(
	 "CUE_CDTEXT_TITLE" );

	return( CUE_CDTEXT_TITLE );
}

TOC_INFO1 {
	cue_scanner_token_print(
	 "CUE_CDTEXT_TOC_INFO1" );

	return( CUE_CDTEXT_TOC_INFO1 );
}

TOC_INFO2 {
	cue_scanner_token_print(
	 "CUE_CDTEXT_TOC_INFO2" );

	return( CUE_CDTEXT_TOC_INFO2 );
}

UPC_EAN {
	cue_scanner_token_print(
	 "CUE_CDTEXT_UPC_EAN" );

	return( CUE_CDTEXT_UPC_EAN );
}

REM[ \t]+LEAD-OUT {
	cue_scanner_token_print(
	 "CUE_REMARK_LEAD_OUT" );

	return( CUE_REMARK_LEAD_OUT );
}

REM[ \t]+ORIGINAL[ \t]+MEDIA-TYPE: {
	cue_scanner_token_print(
	 "CUE_REMARK_ORIGINAL_MEDIA_TYPE" );

	return( CUE_REMARK_ORIGINAL_MEDIA_TYPE );
}

REM[ \t]+RUN-OUT {
	cue_scanner_token_print(
	 "CUE_REMARK_RUN_OUT" );

	return( CUE_REMARK_RUN_OUT );
}

REM[ \t]+SESSION {
	cue_scanner_token_print(
	 "CUE_REMARK_SESSION" );

	return( CUE_REMARK_SESSION );
}

REM[ \t]+ {
	/* BEGIN( REM ); */

	cue_scanner_token_print(
	 "CUE_REMARK" );

	return( CUE_REMARK );
}

{cue_catalog_number} {
	cue_scanner_token_print(
	 "CUE_CATALOG_NUMBER" );

	cue_scanner_lval.string_value.data   = cue_scanner_text;
	cue_scanner_lval.string_value.length = (size_t) cue_scanner_leng;

	return( CUE_CATALOG_NUMBER );
}

{cue_isrc_code} {
	cue_scanner_token_print(
	 "CUE_ISRC_CODE" );

	cue_scanner_lval.string_value.data   = cue_scanner_text;
	cue_scanner_lval.string_value.length = (size_t) cue_scanner_leng;

	return( CUE_ISRC_CODE );
}

{cue_msf} {
	cue_scanner_token_print(
	 "CUE_MSF" );

	cue_scanner_lval.string_value.data   = cue_scanner_text;
	cue_scanner_lval.string_value.length = (size_t) cue_scanner_leng;

	return( CUE_MSF );
}

{cue_2digit} {
	cue_scanner_token_print(
	 "CUE_2DIGIT" );

	cue_scanner_lval.string_value.data   = cue_scanner_text;
	cue_scanner_lval.string_value.length = (size_t) cue_scanner_leng;

	return( CUE_2DIGIT );
}

{cue_keyword} {
	cue_scanner_token_print(
	 "CUE_KEYWORD_STRING" );

	cue_scanner_lval.string_value.data   = cue_scanner_text;
	cue_scanner_lval.string_value.length = (size_t) cue_scanner_leng;

	return( CUE_KEYWORD_STRING );
}

{cue_comments} ;

{end_of_line} {
	return( CUE_END_OF_LINE );
}

{string_double_quoted}|{string_single_quoted} {
	cue_scanner_token_print(
	 "CUE_STRING" );

	if( cue_scanner_leng > 2 )
	{
		cue_scanner_lval.string_value.data   = &( cue_scanner_text[ 1 ] );
		cue_scanner_lval.string_value.length = (size_t) cue_scanner_leng - 2;
	}
	else
	{
		cue_scanner_lval.string_value.data   = NULL;
		cue_scanner_lval.string_value.length = 0;
	}
	return( CUE_STRING );
}

{string_unquoted} {
	cue_scanner_token_print(
	 "CUE_STRING" );

	cue_scanner_lval.string_value.data   = cue_scanner_text;
	cue_scanner_lval.string_value.length = (size_t) cue_scanner_leng;

	return( CUE_STRING );
}

{white_space} ;

. {
	cue_scanner_token_print(
	 "CUE_UNDEFINED" );

	return( CUE_UNDEFINED );
}

%%

void *cue_scanner_alloc(
       yy_size_t size )
{
	return( memory_allocate(
	         size ) );
}

void *cue_scanner_realloc(
       void *buffer,
       yy_size_t size )
{
	return( memory_reallocate(
	         buffer,
	         size ) );
}

void cue_scanner_free(
      void *buffer )
{
	memory_free(
	 buffer );
}

int cue_scanner_wrap(
     void )
{
	return( 1 );
}

void cue_scanner_error(
      void *parser_state LIBODRAW_ATTRIBUTE_UNUSED,
      const char *error_string )
{
	LIBODRAW_UNREFERENCED_PARAMETER( parser_state )

	if( cue_scanner_suppress_error == 0 )
	{
	        fprintf(
        	 stderr,
	         "%s at token: %s (offset: %" PRIzd " size: %" PRIzd ")\n",
        	 error_string,
	         cue_scanner_text,
	         cue_scanner_buffer_offset - (size_t) cue_scanner_leng,
	         (size_t) cue_scanner_leng );
	}
}

