AM_CPPFLAGS = \
	-I../include -I$(top_srcdir)/include \
	-I../common -I$(top_srcdir)/common \
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
	@LIBODRAW_DLL_IMPORT@

BUILT_SOURCES = package.m4

check_AUTOTESTS = \
	test_library \
	test_manpages \
	test_tools

check_PROGRAMS = \
	odraw_test_cue_parser \
	odraw_test_data_file \
	odraw_test_data_file_descriptor \
	odraw_test_error \
	odraw_test_handle \
	odraw_test_io_handle \
	odraw_test_notify \
	odraw_test_sector_range \
	odraw_test_support \
	odraw_test_track_value

odraw_test_cue_parser_SOURCES = \
	odraw_test_cue_parser.c \
	odraw_test_libcerror.h \
	odraw_test_libodraw.h \
	odraw_test_macros.h \
	odraw_test_memory.c odraw_test_memory.h \
	odraw_test_unused.h

odraw_test_cue_parser_LDADD = \
	../libodraw/libodraw.la \
	@LIBCERROR_LIBADD@

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

odraw_test_data_file_descriptor_SOURCES = \
	odraw_test_data_file_descriptor.c \
	odraw_test_libcerror.h \
	odraw_test_libodraw.h \
	odraw_test_macros.h \
	odraw_test_memory.c odraw_test_memory.h \
	odraw_test_unused.h

odraw_test_data_file_descriptor_LDADD = \
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
	odraw_test_functions.c odraw_test_functions.h \
	odraw_test_getopt.c odraw_test_getopt.h \
	odraw_test_handle.c \
	odraw_test_libbfio.h \
	odraw_test_libcerror.h \
	odraw_test_libclocale.h \
	odraw_test_libcnotify.h \
	odraw_test_libodraw.h \
	odraw_test_libuna.h \
	odraw_test_macros.h \
	odraw_test_memory.c odraw_test_memory.h \
	odraw_test_unused.h

odraw_test_handle_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libodraw/libodraw.la \
	@LIBCTHREADS_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@PTHREAD_LIBADD@

odraw_test_io_handle_SOURCES = \
	odraw_test_io_handle.c \
	odraw_test_libcerror.h \
	odraw_test_libodraw.h \
	odraw_test_macros.h \
	odraw_test_memory.c odraw_test_memory.h \
	odraw_test_unused.h

odraw_test_io_handle_LDADD = \
	../libodraw/libodraw.la \
	@LIBCERROR_LIBADD@

odraw_test_notify_SOURCES = \
	odraw_test_libcerror.h \
	odraw_test_libodraw.h \
	odraw_test_macros.h \
	odraw_test_notify.c \
	odraw_test_unused.h

odraw_test_notify_LDADD = \
	../libodraw/libodraw.la \
	@LIBCERROR_LIBADD@

odraw_test_sector_range_SOURCES = \
	odraw_test_libcerror.h \
	odraw_test_libodraw.h \
	odraw_test_macros.h \
	odraw_test_memory.c odraw_test_memory.h \
	odraw_test_sector_range.c \
	odraw_test_unused.h

odraw_test_sector_range_LDADD = \
	../libodraw/libodraw.la \
	@LIBCERROR_LIBADD@

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

AUTOM4TE = autom4te
AUTOTEST = $(AUTOM4TE) --language=autotest

SUFFIXES = .at

.at:
	$(AM_V_GEN)rm -f $@ $@.tmp; \
	$(AUTOTEST) -I '$(srcdir)' -o $@.tmp $< && \
	mv $@.tmp $@

atconfig: $(top_builddir)/config.status
	cd $(top_builddir) && $(SHELL) ./config.status tests/$@

check-build: $(check_PROGRAMS)

check-local: $(check_AUTOTESTS)
	@fail=0; \
	for test_suite in $(check_AUTOTESTS); do \
		$(AM_TESTS_ENVIRONMENT) $(SHELL) "./$$test_suite" $(TESTSUITEFLAGS) || fail=1; \
		echo ""; \
	done; \
	exit $$fail

clean-local:
	for test_suite in $(check_AUTOTESTS); do \
		test ! -f "$$test_suite" || $(SHELL) "./$$test_suite" --clean; \
	done

package.m4: $(top_srcdir)/configure.ac
	$(AM_V_GEN):; \
	{ \
	  echo 'm4_define([AT_PACKAGE_NAME], [$(PACKAGE_NAME)])' ; \
	  echo 'm4_define([AT_PACKAGE_TARNAME], [$(PACKAGE_TARNAME)])' ; \
	  echo 'm4_define([AT_PACKAGE_VERSION], [$(PACKAGE_VERSION)])' ; \
	  echo 'm4_define([AT_PACKAGE_STRING], [$(PACKAGE_STRING)])' ; \
	  echo 'm4_define([AT_PACKAGE_BUGREPORT], [$(PACKAGE_BUGREPORT)])' ; \
	} > $@

test_inputs_libodraw.at: generate_test_inputs.sh
	$(SHELL) $(srcdir)/generate_test_inputs.sh $(PACKAGE_NAME) libodraw

test_inputs_odrawinfo.at: generate_test_inputs.sh
	$(SHELL) $(srcdir)/generate_test_inputs.sh $(PACKAGE_NAME) odrawinfo

test_inputs_odrawverify.at: generate_test_inputs.sh
	$(SHELL) $(srcdir)/generate_test_inputs.sh $(PACKAGE_NAME) odrawverify

test_library: \
	package.m4 \
	test_inputs_libodraw.at \
	test_library.at \
	test_macros.at

test_manpages: \
	package.m4 \
	test_manpages.at

test_tools: \
	package.m4 \
	test_inputs_odrawinfo.at \
	test_inputs_odrawverify.at \
	test_macros.at \
	test_tools.at

EXTRA_DIST = \
	generate_test_inputs.sh \
	package.m4 \
	test_library.at \
	test_macros.at \
	test_manpages.at \
	test_tools.at

CLEANFILES = \
	$(check_AUTOTESTS) \
	*.exe \
	*.tmp \
	notify_stream.log \
	test_inputs_*.at

DISTCLEANFILES = \
	*.log \
	atconfig \
	Makefile \
	Makefile.in

