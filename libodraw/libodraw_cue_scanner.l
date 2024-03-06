%option prefix="libodraw_cue_scanner_" outfile="lex.yy.c"
%option never-interactive 8bit
%option noinput nounput noyylineno nounistd
%option noyyalloc noyyrealloc noyyfree

%{
/*
 * CUE scanner functions
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
#include <memory.h>
#include <types.h>

#include "libodraw_cue_parser.h"
#include "libodraw_libcnotify.h"
#include "libodraw_unused.h"

#define YYLEX_PARAM	NULL

int libodraw_cue_scanner_suppress_error   = 0;
size_t libodraw_cue_scanner_buffer_offset = 0;

#define YY_USER_ACTION	libodraw_cue_scanner_buffer_offset += (size_t) libodraw_cue_scanner_leng;

#if defined( HAVE_DEBUG_OUTPUT )
#define libodraw_cue_scanner_token_print( string ) \
	if( libcnotify_verbose != 0 ) libcnotify_printf( "libodraw_cue_scanner: offset: %" PRIzd " token: %s\n", libodraw_cue_scanner_buffer_offset, string )
#else
#define libodraw_cue_scanner_token_print( string )
#endif

%}

cue_2digit		[0-9][0-9]

/* The catalog number is a 13 digit number */
cue_catalog_number	[0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9]

cue_comments		([;]|[/][/])[ ][^\x00-\x08\x0a-\x1f\x7f]*

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
	libodraw_cue_scanner_token_print(
	 "CUE_CATALOG" );

	return( CUE_CATALOG );
}

CD_DA {
	libodraw_cue_scanner_token_print(
	 "CUE_CD_DA" );

	return( CUE_CD_DA );
}

CD_ROM {
	libodraw_cue_scanner_token_print(
	 "CUE_CD_ROM" );

	return( CUE_CD_ROM );
}

CD_ROM_XA {
	libodraw_cue_scanner_token_print(
	 "CUE_CD_ROM_XA" );

	return( CUE_CD_ROM_XA );
}

CD_TEXT {
	libodraw_cue_scanner_token_print(
	 "CUE_CD_TEXT" );

	return( CUE_CD_TEXT );
}

CDTEXTFILE {
	libodraw_cue_scanner_token_print(
	 "CUE_CDTEXTFILE" );

	return( CUE_CDTEXTFILE );
}

COPY {
	libodraw_cue_scanner_token_print(
	 "CUE_COPY" );

	return( CUE_COPY );
}

DATAFILE {
	libodraw_cue_scanner_token_print(
	 "CUE_DATAFILE" );

	return( CUE_DATAFILE );
}

FILE {
	libodraw_cue_scanner_token_print(
	 "CUE_FILE" );

	return( CUE_FILE );
}

FLAGS {
	libodraw_cue_scanner_token_print(
	 "CUE_FLAGS" );

	return( CUE_FLAGS );
}

FOUR_CHANNEL_AUDIO {
	libodraw_cue_scanner_token_print(
	 "CUE_FOUR_CHANNEL_AUDIO" );

	return( CUE_FOUR_CHANNEL_AUDIO );
}

INDEX {
	libodraw_cue_scanner_token_print(
	 "CUE_INDEX" );

	return( CUE_INDEX );
}

ISRC {
	libodraw_cue_scanner_token_print(
	 "CUE_ISRC" );

	return( CUE_ISRC );
}

NO[ ]COPY {
	libodraw_cue_scanner_token_print(
	 "CUE_NO_COPY" );

	return( CUE_NO_COPY );
}

NO[ ]PRE_EMPHASIS {
	libodraw_cue_scanner_token_print(
	 "CUE_NO_PRE_EMPHASIS" );

	return( CUE_NO_PRE_EMPHASIS );
}

POSTGAP {
	libodraw_cue_scanner_token_print(
	 "CUE_POSTGAP" );

	return( CUE_POSTGAP );
}

PRE_EMPHASIS {
	libodraw_cue_scanner_token_print(
	 "CUE_PRE_EMPHASIS" );

	return( CUE_PRE_EMPHASIS );
}

PREGAP {
	libodraw_cue_scanner_token_print(
	 "CUE_PREGAP" );

	return( CUE_PREGAP );
}

TRACK {
	libodraw_cue_scanner_token_print(
	 "CUE_TRACK" );

	return( CUE_TRACK );
}

TWO_CHANNEL_AUDIO {
	libodraw_cue_scanner_token_print(
	 "CUE_TWO_CHANNEL_AUDIO" );

	return( CUE_TWO_CHANNEL_AUDIO );
}

ARRANGER {
	libodraw_cue_scanner_token_print(
	 "CUE_CDTEXT_ARRANGER" );

	return( CUE_CDTEXT_ARRANGER );
}

COMPOSER {
	libodraw_cue_scanner_token_print(
	 "CUE_CDTEXT_COMPOSER" );

	return( CUE_CDTEXT_COMPOSER );
}

DISC_ID {
	libodraw_cue_scanner_token_print(
	 "CUE_CDTEXT_DISC_ID" );

	return( CUE_CDTEXT_DISC_ID );
}

GENRE {
	libodraw_cue_scanner_token_print(
	 "CUE_CDTEXT_GENRE" );

	return( CUE_CDTEXT_GENRE );
}

MESSAGE {
	libodraw_cue_scanner_token_print(
	 "CUE_CDTEXT_MESSAGE" );

	return( CUE_CDTEXT_MESSAGE );
}

PERFORMER {
	libodraw_cue_scanner_token_print(
	 "CUE_CDTEXT_PERFORMER" );

	return( CUE_CDTEXT_PERFORMER );
}

SIZE_INFO {
	libodraw_cue_scanner_token_print(
	 "CUE_CDTEXT_SIZE_INFO" );

	return( CUE_CDTEXT_SIZE_INFO );
}

SONGWRITER {
	libodraw_cue_scanner_token_print(
	 "CUE_CDTEXT_SONGWRITER" );

	return( CUE_CDTEXT_SONGWRITER );
}

TITLE {
	libodraw_cue_scanner_token_print(
	 "CUE_CDTEXT_TITLE" );

	return( CUE_CDTEXT_TITLE );
}

TOC_INFO1 {
	libodraw_cue_scanner_token_print(
	 "CUE_CDTEXT_TOC_INFO1" );

	return( CUE_CDTEXT_TOC_INFO1 );
}

TOC_INFO2 {
	libodraw_cue_scanner_token_print(
	 "CUE_CDTEXT_TOC_INFO2" );

	return( CUE_CDTEXT_TOC_INFO2 );
}

UPC_EAN {
	libodraw_cue_scanner_token_print(
	 "CUE_CDTEXT_UPC_EAN" );

	return( CUE_CDTEXT_UPC_EAN );
}

REM[ \t]+LEAD-OUT {
	libodraw_cue_scanner_token_print(
	 "CUE_REMARK_LEAD_OUT" );

	return( CUE_REMARK_LEAD_OUT );
}

REM[ \t]+ORIGINAL[ \t]+MEDIA-TYPE: {
	libodraw_cue_scanner_token_print(
	 "CUE_REMARK_ORIGINAL_MEDIA_TYPE" );

	return( CUE_REMARK_ORIGINAL_MEDIA_TYPE );
}

REM[ \t]+RUN-OUT {
	libodraw_cue_scanner_token_print(
	 "CUE_REMARK_RUN_OUT" );

	return( CUE_REMARK_RUN_OUT );
}

REM[ \t]+SESSION {
	libodraw_cue_scanner_token_print(
	 "CUE_REMARK_SESSION" );

	return( CUE_REMARK_SESSION );
}

REM[ \t]+ {
	/* BEGIN( REM ); */

	libodraw_cue_scanner_token_print(
	 "CUE_REMARK" );

	return( CUE_REMARK );
}

{cue_catalog_number} {
	libodraw_cue_scanner_token_print(
	 "CUE_CATALOG_NUMBER" );

	libodraw_cue_scanner_lval.string_value.data   = libodraw_cue_scanner_text;
	libodraw_cue_scanner_lval.string_value.length = (size_t) libodraw_cue_scanner_leng;

	return( CUE_CATALOG_NUMBER );
}

{cue_isrc_code} {
	libodraw_cue_scanner_token_print(
	 "CUE_ISRC_CODE" );

	libodraw_cue_scanner_lval.string_value.data   = libodraw_cue_scanner_text;
	libodraw_cue_scanner_lval.string_value.length = (size_t) libodraw_cue_scanner_leng;

	return( CUE_ISRC_CODE );
}

{cue_msf} {
	libodraw_cue_scanner_token_print(
	 "CUE_MSF" );

	libodraw_cue_scanner_lval.string_value.data   = libodraw_cue_scanner_text;
	libodraw_cue_scanner_lval.string_value.length = (size_t) libodraw_cue_scanner_leng;

	return( CUE_MSF );
}

{cue_2digit} {
	libodraw_cue_scanner_token_print(
	 "CUE_2DIGIT" );

	libodraw_cue_scanner_lval.string_value.data   = libodraw_cue_scanner_text;
	libodraw_cue_scanner_lval.string_value.length = (size_t) libodraw_cue_scanner_leng;

	return( CUE_2DIGIT );
}

{cue_keyword} {
	libodraw_cue_scanner_token_print(
	 "CUE_KEYWORD_STRING" );

	libodraw_cue_scanner_lval.string_value.data   = libodraw_cue_scanner_text;
	libodraw_cue_scanner_lval.string_value.length = (size_t) libodraw_cue_scanner_leng;

	return( CUE_KEYWORD_STRING );
}

{cue_comments} ;

{end_of_line} {
	return( CUE_END_OF_LINE );
}

{string_double_quoted}|{string_single_quoted} {
	libodraw_cue_scanner_token_print(
	 "CUE_STRING" );

	if( libodraw_cue_scanner_leng > 2 )
	{
		libodraw_cue_scanner_lval.string_value.data   = &( libodraw_cue_scanner_text[ 1 ] );
		libodraw_cue_scanner_lval.string_value.length = (size_t) libodraw_cue_scanner_leng - 2;
	}
	else
	{
		libodraw_cue_scanner_lval.string_value.data   = NULL;
		libodraw_cue_scanner_lval.string_value.length = 0;
	}
	return( CUE_STRING );
}

{string_unquoted} {
	libodraw_cue_scanner_token_print(
	 "CUE_STRING" );

	libodraw_cue_scanner_lval.string_value.data   = libodraw_cue_scanner_text;
	libodraw_cue_scanner_lval.string_value.length = (size_t) libodraw_cue_scanner_leng;

	return( CUE_STRING );
}

{white_space} ;

. {
	libodraw_cue_scanner_token_print(
	 "CUE_UNDEFINED" );

	return( CUE_UNDEFINED );
}

%%

void *libodraw_cue_scanner_alloc(
       yy_size_t size )
{
	return( memory_allocate(
	         size ) );
}

void *libodraw_cue_scanner_realloc(
       void *buffer,
       yy_size_t size )
{
	return( memory_reallocate(
	         buffer,
	         size ) );
}

void libodraw_cue_scanner_free(
      void *buffer )
{
	memory_free(
	 buffer );
}

int libodraw_cue_scanner_wrap(
     void )
{
	return( 1 );
}

void libodraw_cue_scanner_error(
      void *parser_state LIBODRAW_ATTRIBUTE_UNUSED,
      const char *error_string )
{
	LIBODRAW_UNREFERENCED_PARAMETER( parser_state )

	if( libodraw_cue_scanner_suppress_error == 0 )
	{
	        fprintf(
        	 stderr,
	         "%s at token: %s (offset: %" PRIzd " size: %" PRIzd ")\n",
        	 error_string,
	         libodraw_cue_scanner_text,
	         libodraw_cue_scanner_buffer_offset - (size_t) libodraw_cue_scanner_leng,
	         (size_t) libodraw_cue_scanner_leng );
	}
}

