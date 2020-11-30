#!/bin/sh
# Script to run tests
#
# Version: 20201121

if test -f ${PWD}/libodraw/.libs/libodraw.1.dylib && test -f ./pyodraw/.libs/pyodraw.so;
then
	install_name_tool -change /usr/local/lib/libodraw.1.dylib ${PWD}/libodraw/.libs/libodraw.1.dylib ./pyodraw/.libs/pyodraw.so;
fi

make check CHECK_WITH_STDERR=1;
RESULT=$?;

if test ${RESULT} -ne 0 && test -f tests/test-suite.log;
then
	cat tests/test-suite.log;
fi
exit ${RESULT};

