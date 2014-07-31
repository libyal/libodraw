MSVSCPP_FILES = \
	libbfio/libbfio.vcproj \
	libcdata/libcdata.vcproj \
	libcerror/libcerror.vcproj \
	libcfile/libcfile.vcproj \
	libclocale/libclocale.vcproj \
	libcnotify/libcnotify.vcproj \
	libcpath/libcpath.vcproj \
	libcsplit/libcsplit.vcproj \
	libcstring/libcstring.vcproj \
	libcsystem/libcsystem.vcproj \
	libcthreads/libcthreads.vcproj \
	libhmac/libhmac.vcproj \
	libodraw/libodraw.vcproj \
	libuna/libuna.vcproj \
	odraw_test_open_close/odraw_test_open_close.vcproj \
	odraw_test_read/odraw_test_read.vcproj \
	odraw_test_seek/odraw_test_seek.vcproj \
	odraw_test_set_ascii_codepage/odraw_test_set_ascii_codepage.vcproj \
	odrawinfo/odrawinfo.vcproj \
	odrawverify/odrawverify.vcproj \
	libodraw.sln

SCRIPT_FILES = \
	scripts/vs2008_x64.sh \
	scripts/vs2008_x64_sln.sed \
	scripts/vs2008_x64_vcproj.sed \
	scripts/vs2010_x64.sh \
	scripts/vs2010_x64_sln.sed \
	scripts/vs2010_x64_vcxproj.sed

EXTRA_DIST = \
	$(MSVSCPP_FILES) \
	$(SCRIPT_FILES)

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

