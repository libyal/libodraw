AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBCSYSTEM_CPPFLAGS@ \
	@LIBHMAC_CPPFLAGS@ \
	@LIBCRYPTO_CPPFLAGS@ \
	@LIBODRAW_DLL_IMPORT@

AM_LDFLAGS = @STATIC_LDFLAGS@

bin_PROGRAMS = \
	odrawinfo \
	odrawverify

odrawinfo_SOURCES = \
	info_handle.c info_handle.h \
	odrawinfo.c \
	odrawoutput.c odrawoutput.h \
	odrawtools_libbfio.h \
	odrawtools_libcerror.h \
	odrawtools_libclocale.h \
	odrawtools_libcnotify.h \
	odrawtools_libcsystem.h \
	odrawtools_libodraw.h \
	odrawtools_libuna.h

odrawinfo_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	../libodraw/libodraw.la \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBINTL@

odrawverify_SOURCES = \
	byte_size_string.c byte_size_string.h \
	digest_hash.c digest_hash.h \
	log_handle.c log_handle.h \
	process_status.c process_status.h \
	odrawverify.c \
	odrawoutput.c odrawoutput.h \
	odrawtools_libcerror.h \
	odrawtools_libclocale.h \
	odrawtools_libcnotify.h \
	odrawtools_libcsplit.h \
	odrawtools_libcsystem.h \
	odrawtools_libhmac.h \
	odrawtools_libodraw.h \
	odrawtools_libuna.h \
	storage_media_buffer.c storage_media_buffer.h \
	verification_handle.c verification_handle.h

odrawverify_LDADD = \
	@LIBHMAC_LIBADD@ \
	@LIBCRYPTO_LIBADD@ \
	@LIBCSYSTEM_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	../libodraw/libodraw.la \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBINTL@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

splint:
	@echo "Running splint on odrawinfo ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(odrawinfo_SOURCES)
	@echo "Running splint on odrawverify ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(odrawverify_SOURCES)

