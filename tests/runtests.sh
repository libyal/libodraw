#!/bin/sh
# Script to run tests
#
# Version: 20260714

if [ -f "${PWD}/libodraw/.libs/libodraw.1.dylib" ] && [ -f ./pyodraw/.libs/pyodraw.so ]
then
    install_name_tool -change /usr/local/lib/libodraw.1.dylib "${PWD}/libodraw/.libs/libodraw.1.dylib" ./pyodraw/.libs/pyodraw.so
fi

make check-build > /dev/null

# shellcheck disable=SC2068
make check $@
RESULT=$?

if [ ${RESULT} -ne 0 ]
then
    find . -name \*.log -path \*.dir/\*/\*.log -print -exec cat {} \;
fi
exit ${RESULT}

