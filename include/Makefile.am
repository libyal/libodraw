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
	/bin/rm -f libodraw.h
	/bin/rm -f libodraw/definitions.h
	/bin/rm -f libodraw/features.h
	/bin/rm -f libodraw/types.h
	/bin/rm -f Makefile

