/*
 * Verifies the integrity of optical disc (split) RAW file(s)
 *
 * Copyright (C) 2010-2026, Joachim Metz <joachim.metz@gmail.com>
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
#include <system_string.h>
#include <types.h>

#if defined( HAVE_FCNTL_H ) || defined( WINAPI )
#include <fcntl.h>
#endif

#if defined( HAVE_IO_H ) || defined( WINAPI )
#include <io.h>
#endif

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "byte_size_string.h"
#include "digest_hash.h"
#include "log_handle.h"
#include "odrawtools_getopt.h"
#include "odrawtools_libcerror.h"
#include "odrawtools_libclocale.h"
#include "odrawtools_libcnotify.h"
#include "odrawtools_libodraw.h"
#include "odrawtools_output.h"
#include "odrawtools_signal.h"
#include "odrawtools_unused.h"
#include "verification_handle.h"

verification_handle_t *odrawverify_verification_handle = NULL;
int odrawverify_abort                                  = 0;

/* Signal handler for odrawverify
 */
void odrawverify_signal_handler(
      odrawtools_signal_t signal ODRAWTOOLS_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	static char *function   = "odrawverify_signal_handler";

	ODRAWTOOLS_UNREFERENCED_PARAMETER( signal )

	odrawverify_abort = 1;

	if( odrawverify_verification_handle != NULL )
	{
		if( verification_handle_signal_abort(
		     odrawverify_verification_handle,
		     &error ) != 1 )
		{
			libcnotify_printf(
			 "%s: unable to signal verification handle to abort.\n",
			 function );

			libcnotify_print_error_backtrace(
			 error );
			libcerror_error_free(
			 &error );
		}
	}
	/* Force stdin to close otherwise any function reading it will remain blocked
	 */
#if defined( WINAPI ) && !defined( __CYGWIN__ )
	if( _close(
	     0 ) != 0 )
#else
	if( close(
	     0 ) != 0 )
#endif
	{
		libcnotify_printf(
		 "%s: unable to close stdin.\n",
		 function );
	}
}

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain( int argc, wchar_t * const argv[] )
#else
int main( int argc, char * const argv[] )
#endif
{
	const char *description = \
		"Use odrawverify to verify data stored in the optical disc (split) RAW image file format.";

	odrawtools_option_t options[ ] = {
		{ 'd', "digest_type", "calculate additional digest (hash) types besides md5, options: sha1, sha256" },
		{ 'h', NULL, "shows this help" },
		{ 'l', "log_file", "logs verification errors and the digest (hash) to a file" },
		{ 'p', "buffer_size", "specify the process buffer size (default is the 32768)" },
		{ 'q', NULL, "quiet shows minimal status information" },
		{ 'v', NULL, "verbose output to stderr" },
		{ 'V', NULL, "print version" },
		{ 0, "source", "the source image" },
	};
	system_character_t options_string[ 32 ];

	libcerror_error_t *error                           = NULL;
	log_handle_t *log_handle                           = NULL;
	system_character_t *log_filename                   = NULL;
	system_character_t *option_additional_digest_types = NULL;
	system_character_t *option_process_buffer_size     = NULL;
	system_character_t *source                         = NULL;
	system_integer_t option                            = 0;
	char *program                                      = "odrawverify";
	uint8_t calculate_md5                              = 1;
	int number_of_options                              = (int) ( sizeof( options ) / sizeof( odrawtools_option_t ) );
	uint8_t print_status_information                   = 1;
	uint8_t verbose                                    = 0;
	int result                                         = 0;

#if defined( __MINGW32__ ) && defined( HAVE_MINGW_BINMODE )
	_setmode( _fileno( stdout ), _O_BINARY );
	_setmode( _fileno( stderr ), _O_BINARY );
#endif

	libcnotify_stream_set(
	 stderr,
	 NULL );
	libcnotify_verbose_set(
	 1 );

	if( libclocale_initialize(
             "odrawtools",
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to initialize locale values.\n" );

		goto on_error;
	}
	if( odrawtools_output_initialize(
	     _IONBF,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to initialize output settings.\n" );

		goto on_error;
	}
	odrawtools_output_version_fprint(
	 stdout,
	 program );

	if( odrawtools_getopt_get_options_string(
	     options,
	     number_of_options,
	     options_string,
	     32 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to determine options string.\n" );

		goto on_error;
	}
	while( ( option = odrawtools_getopt(
	                   argc,
	                   argv,
	                   options_string ) ) != (system_integer_t) -1 )
	{
		switch( option )
		{
			case (system_integer_t) '?':
			default:
				fprintf(
				 stderr,
				 "Invalid argument: %" PRIs_SYSTEM "\n",
				 argv[ optind - 1 ] );

				odrawtools_getopt_usage_fprint(
				 stdout,
				 program,
				 description,
				 options,
				 number_of_options );

				goto on_error;

			case (system_integer_t) 'd':
				option_additional_digest_types = optarg;

				break;

			case (system_integer_t) 'h':
				odrawtools_getopt_usage_fprint(
				 stdout,
				 program,
				 description,
				 options,
				 number_of_options );

				return( EXIT_SUCCESS );

			case (system_integer_t) 'l':
				log_filename = optarg;

				break;

			case (system_integer_t) 'p':
				option_process_buffer_size = optarg;

				break;

			case (system_integer_t) 'q':
				print_status_information = 0;

				break;

			case (system_integer_t) 'v':
				verbose = 1;

				break;

			case (system_integer_t) 'V':
				odrawtools_output_copyright_fprint(
				 stdout );

				return( EXIT_SUCCESS );
		}
	}
	if( optind == argc )
	{
		fprintf(
		 stderr,
		 "Missing source file.\n" );

		odrawtools_getopt_usage_fprint(
		 stdout,
		 program,
		 description,
		 options,
		 number_of_options );

		return( EXIT_FAILURE );
	}
	source = argv[ optind ];

	libcnotify_verbose_set(
	 verbose );

#if !defined( HAVE_LOCAL_LIBODRAW )
	libodraw_notify_set_verbose(
	 verbose );
	libodraw_notify_set_stream(
	 stderr,
	 NULL );
#endif

	if( verification_handle_initialize(
	     &odrawverify_verification_handle,
	     calculate_md5,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to create verification handle.\n" );

		goto on_error;
	}
#if defined( __clang_analyzer__ )
	__builtin_assume( odrawverify_verification_handle != NULL );
#endif
	if( option_process_buffer_size != NULL )
	{
		result = verification_handle_set_process_buffer_size(
			  odrawverify_verification_handle,
			  option_process_buffer_size,
			  &error );

		if( result == -1 )
		{
			fprintf(
			 stderr,
			 "Unable to set process buffer size.\n" );

			goto on_error;
		}
		else if( ( result == 0 )
		      || ( odrawverify_verification_handle->process_buffer_size > (size_t) SSIZE_MAX ) )
		{
			odrawverify_verification_handle->process_buffer_size = 0;

			fprintf(
			 stderr,
			 "Unsupported process buffer size defaulting to: 32768.\n" );
		}
	}
	if( option_additional_digest_types != NULL )
	{
		result = verification_handle_set_additional_digest_types(
			  odrawverify_verification_handle,
			  option_additional_digest_types,
			  &error );

		if( result == -1 )
		{
			fprintf(
			 stderr,
			 "Unable to set additional digest types.\n" );

			goto on_error;
		}
	}
	if( odrawtools_signal_attach(
	     odrawverify_signal_handler,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to attach signal handler.\n" );

		libcnotify_print_error_backtrace(
		 error );
		libcerror_error_free(
		 &error );
	}
	if( verification_handle_open_input(
	     odrawverify_verification_handle,
	     source,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to open file: %" PRIs_SYSTEM ".\n",
		 source );

		goto on_error;
	}
	if( log_filename != NULL )
	{
		if( log_handle_initialize(
		     &log_handle,
		     &error ) != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to create log handle.\n" );

			goto on_error;
		}
		if( log_handle_open(
		     log_handle,
		     log_filename,
		     &error ) != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to open log file: %" PRIs_SYSTEM ".\n",
			 log_filename );

			goto on_error;
		}
	}
	result = verification_handle_verify_input(
		  odrawverify_verification_handle,
		  print_status_information,
		  log_handle,
		  &error );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to verify input.\n" );

		libcnotify_print_error_backtrace(
		 error );
		libcerror_error_free(
		 &error );
	}
	if( log_handle != NULL )
	{
		if( log_handle_close(
		     log_handle,
		     &error ) != 0 )
		{
			fprintf(
			 stderr,
			 "Unable to close log handle.\n" );

			goto on_error;
		}
		if( log_handle_free(
		     &log_handle,
		     &error ) != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to free log handle.\n" );

			goto on_error;
		}
	}
	if( odrawtools_signal_detach(
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to detach signal handler.\n" );

		libcnotify_print_error_backtrace(
		 error );
		libcerror_error_free(
		 &error );
	}
	if( verification_handle_close(
	     odrawverify_verification_handle,
	     &error ) != 0 )
	{
		fprintf(
		 stderr,
		 "Unable to close verification handle.\n" );

		goto on_error;

	}
	if( verification_handle_free(
	     &odrawverify_verification_handle,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to free verification handle.\n" );

		goto on_error;
	}
	if( odrawverify_abort != 0 )
	{
		fprintf(
		 stdout,
		 "%" PRIs_SYSTEM ": ABORTED\n",
		 program );

		return( EXIT_FAILURE );
	}
	if( result != 1 )
	{
		fprintf(
		 stdout,
		 "%" PRIs_SYSTEM ": FAILURE\n",
		 program );

		return( EXIT_FAILURE );
	}
	fprintf(
	 stdout,
	 "%" PRIs_SYSTEM ": SUCCESS\n",
	 program );

	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libcnotify_print_error_backtrace(
		 error );
		libcerror_error_free(
		 &error );
	}
	if( log_handle != NULL )
	{
		log_handle_close(
		 log_handle,
		 NULL );
		log_handle_free(
		 &log_handle,
		 NULL );
	}
	if( odrawverify_verification_handle != NULL )
	{
		verification_handle_close(
		 odrawverify_verification_handle,
		 NULL );
		verification_handle_free(
		 &odrawverify_verification_handle,
		 NULL );
	}
	return( EXIT_FAILURE );
}

