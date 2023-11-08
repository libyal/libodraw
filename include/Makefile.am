include_HEADERS = \
	libodraw.h

pkginclude_HEADERS = \
	libodraw/codepage.h \
	libodraw/definitions.h \
	libodraw/error.h \
	libodraw/extern.h \
	libodraw/features.h \
	libodraw/types.h

EXTRA_DIST = \
	libodraw.h.in \
	libodraw/definitions.h.in \
	libodraw/features.h.in \
	libodraw/types.h.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	-rm -f libodraw.h
	-rm -f libodraw/definitions.h
	-rm -f libodraw/features.h
	-rm -f libodraw/types.h
	-rm -f Makefile

