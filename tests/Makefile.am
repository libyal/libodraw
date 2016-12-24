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
	@LIBCSYSTEM_CPPFLAGS@ \
	@PTHREAD_CPPFLAGS@ \
	@LIBODRAW_DLL_IMPORT@

TESTS = \
	test_api_functions.sh \
	test_api_types.sh \
	test_odrawinfo.sh \
	test_odrawverify.sh

check_SCRIPTS = \
	test_api_functions.sh \
	test_api_types.sh \
	test_odrawinfo.sh \
	test_odrawverify.sh \
	test_runner.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	odraw_test_data_file \
	odraw_test_error \
	odraw_test_handle \
	odraw_test_notify \
	odraw_test_read \
	odraw_test_seek \
	odraw_test_support \
	odraw_test_track_value

odraw_test_data_file_SOURCES = \
	odraw_test_data_file.c \
	odraw_test_libcerror.h \
	odraw_test_libodraw.h \
	odraw_test_macros.h \
	odraw_test_memory.c odraw_test_memory.h \
	odraw_test_unused.h

odraw_test_data_file_LDADD = \
	../libodraw/libodraw.la \
	@LIBCERROR_LIBADD@

odraw_test_error_SOURCES = \
	odraw_test_error.c \
	odraw_test_libodraw.h \
	odraw_test_macros.h \
	odraw_test_unused.h

odraw_test_error_LDADD = \
	../libodraw/libodraw.la

odraw_test_handle_SOURCES = \
	odraw_test_getopt.c odraw_test_getopt.h \
	odraw_test_handle.c \
	odraw_test_libcerror.h \
	odraw_test_libclocale.h \
	odraw_test_libcnotify.h \
	odraw_test_libodraw.h \
	odraw_test_libuna.h \
	odraw_test_memory.c odraw_test_memory.h \
	odraw_test_unused.h

odraw_test_handle_LDADD = \
	@LIBUNA_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libodraw/libodraw.la \
	@LIBCERROR_LIBADD@

odraw_test_notify_SOURCES = \
	odraw_test_libodraw.h \
	odraw_test_macros.h \
	odraw_test_notify.c \
	odraw_test_unused.h

odraw_test_notify_LDADD = \
	../libodraw/libodraw.la

odraw_test_read_SOURCES = \
	odraw_test_libcerror.h \
	odraw_test_libodraw.h \
	odraw_test_read.c \
	odraw_test_unused.h

odraw_test_read_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	../libodraw/libodraw.la \
	@LIBCTHREADS_LIBADD@ \
	@LIBCERROR_LIBADD@
	@PTHREAD_LIBADD@

odraw_test_seek_SOURCES = \
	odraw_test_libcerror.h \
	odraw_test_libodraw.h \
	odraw_test_seek.c \
	odraw_test_unused.h

odraw_test_seek_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	../libodraw/libodraw.la \
	@LIBCERROR_LIBADD@
	@PTHREAD_LIBADD@

odraw_test_support_SOURCES = \
	odraw_test_libcerror.h \
	odraw_test_libodraw.h \
	odraw_test_macros.h \
	odraw_test_support.c \
	odraw_test_unused.h

odraw_test_support_LDADD = \
	../libodraw/libodraw.la \
	@LIBCERROR_LIBADD@

odraw_test_track_value_SOURCES = \
	odraw_test_libcerror.h \
	odraw_test_libodraw.h \
	odraw_test_macros.h \
	odraw_test_memory.c odraw_test_memory.h \
	odraw_test_track_value.c \
	odraw_test_unused.h

odraw_test_track_value_LDADD = \
	../libodraw/libodraw.la \
	@LIBCERROR_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

