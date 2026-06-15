#!/bin/sh
# Script to run tests
#
# Version: 20260609

if test -f ${PWD}/libodraw/.libs/libodraw.1.dylib && test -f ./pyodraw/.libs/pyodraw.so
then
	install_name_tool -change /usr/local/lib/libodraw.1.dylib ${PWD}/libodraw/.libs/libodraw.1.dylib ./pyodraw/.libs/pyodraw.so
fi

make check-build > /dev/null

make check $@
RESULT=$?

if test ${RESULT} -ne 0
then
	find . -name \*.log -path \*.dir/\*/\*.log -print -exec cat {} \;
fi
exit ${RESULT}

