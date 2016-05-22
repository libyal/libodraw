AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCSTRING_CPPFLAGS@ \
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
	test_set_ascii_codepage.sh \
	test_odrawinfo.sh \
	test_odrawverify.sh

check_SCRIPTS = \
	test_api_functions.sh \
	test_odrawinfo.sh \
	test_odrawverify.sh \
	test_runner.sh \
	test_set_ascii_codepage.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	odraw_test_get_version \
	odraw_test_open_close \
	odraw_test_read \
	odraw_test_seek \
	odraw_test_set_ascii_codepage

odraw_test_get_version_SOURCES = \
	odraw_test_get_version.c \
	odraw_test_libcstring.h \
	odraw_test_libodraw.h \
	odraw_test_unused.h

odraw_test_get_version_LDADD = \
	../libodraw/libodraw.la \
	@LIBCSTRING_LIBADD@

odraw_test_open_close_SOURCES = \
	odraw_test_libcerror.h \
	odraw_test_libcstring.h \
	odraw_test_libodraw.h \
	odraw_test_open_close.c \
	odraw_test_unused.h

odraw_test_open_close_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	../libodraw/libodraw.la \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@ \
	@PTHREAD_LIBADD@

odraw_test_read_SOURCES = \
	odraw_test_libcerror.h \
	odraw_test_libcstring.h \
	odraw_test_libodraw.h \
	odraw_test_read.c \
	odraw_test_unused.h

odraw_test_read_LDADD = \
	../libodraw/libodraw.la \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@ \
	@PTHREAD_LIBADD@

odraw_test_seek_SOURCES = \
	odraw_test_libcerror.h \
	odraw_test_libcstring.h \
	odraw_test_libodraw.h \
	odraw_test_seek.c \
	odraw_test_unused.h

odraw_test_seek_LDADD = \
	../libodraw/libodraw.la \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@ \
	@PTHREAD_LIBADD@

odraw_test_set_ascii_codepage_SOURCES = \
	odraw_test_libcerror.h \
	odraw_test_libclocale.h \
	odraw_test_libodraw.h \
	odraw_test_libcstring.h \
	odraw_test_set_ascii_codepage.c \
	odraw_test_unused.h

odraw_test_set_ascii_codepage_LDADD = \
	../libodraw/libodraw.la \
	@LIBCLOCALE_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@ \
	@PTHREAD_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

