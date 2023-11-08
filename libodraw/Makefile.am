AM_LFLAGS = -Cf
AM_YFLAGS = -d -v -l -p libodraw_cue_scanner_

AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCTHREADS_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@PTHREAD_CPPFLAGS@ \
	@LIBODRAW_DLL_EXPORT@

BUILT_SOURCES = libodraw_cue_parser.h

lib_LTLIBRARIES = libodraw.la

libodraw_la_SOURCES = \
	libodraw.c \
	libodraw_codepage.h \
	libodraw_cue_parser.y \
	libodraw_cue_scanner.l \
	libodraw_data_file.c libodraw_data_file.h \
	libodraw_data_file_descriptor.c libodraw_data_file_descriptor.h \
	libodraw_debug.c libodraw_debug.h \
	libodraw_definitions.h \
	libodraw_error.c libodraw_error.h \
	libodraw_extern.h \
	libodraw_handle.c libodraw_handle.h \
	libodraw_io_handle.c libodraw_io_handle.h \
	libodraw_libbfio.h \
	libodraw_libcdata.h \
	libodraw_libcerror.h \
	libodraw_libclocale.h \
	libodraw_libcnotify.h \
	libodraw_libcpath.h \
	libodraw_libuna.h \
	libodraw_notify.c libodraw_notify.h \
	libodraw_sector_range.c libodraw_sector_range.h \
	libodraw_support.c libodraw_support.h \
	libodraw_track_value.c libodraw_track_value.h \
	libodraw_types.h \
	libodraw_unused.h

libodraw_la_LIBADD = \
	@LIBCERROR_LIBADD@ \
	@LIBCTHREADS_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBBFIO_LIBADD@ \
	@PTHREAD_LIBADD@

libodraw_la_LDFLAGS = -no-undefined -version-info 1:0:0

EXTRA_DIST = \
	libodraw_definitions.h.in \
	libodraw_cue_parser.c libodraw_cue_parser.h \
	libodraw_cue_scanner.c \
	libodraw.rc \
	libodraw.rc.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	-rm -f libodraw_definitions.h
	-rm -f libodraw.rc
	-rm -f libodraw_cue_parser.c
	-rm -f libodraw_cue_parser.h
	-rm -f libodraw_cue_parser.output
	-rm -f libodraw_cue_scanner.c
	-rm -f Makefile

sources-local: $(BUILT_SOURCES)

splint-local:
	@echo "Running splint on libodraw ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(libodraw_la_SOURCES)

