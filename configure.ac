AC_PREREQ( 2.59 )

AC_INIT(
 [libodraw],
 [20170217],
 [joachim.metz@gmail.com])

AC_CONFIG_SRCDIR(
 [include/libodraw.h.in])

AM_INIT_AUTOMAKE([gnu 1.6 tar-ustar])

AC_CONFIG_MACRO_DIR([m4])

dnl Check for host type
AC_CANONICAL_HOST

dnl Check for large file support
AC_SYS_LARGEFILE

dnl Check for libtool DLL support
AC_LIBTOOL_WIN32_DLL

dnl Checks for programs
AC_PROG_CC
AC_PROG_GCC_TRADITIONAL
AC_PROG_MAKE_SET
AC_PROG_INSTALL

dnl Check for libtool
AC_PROG_LIBTOOL
AC_SUBST(LIBTOOL_DEPS)

dnl Check for pkg-config
AC_PATH_PROG(PKGCONFIG,[pkg-config])

dnl Support of internationalization (i18n)
AM_GNU_GETTEXT([external])
AM_GNU_GETTEXT_VERSION([0.18.1])

dnl Check for compiler language support
AC_C_CONST
AC_C_VOLATILE

dnl Check if WINAPI support should be enabled
AX_COMMON_CHECK_ENABLE_WINAPI

dnl Check if wide character type should be enabled
AX_COMMON_CHECK_ENABLE_WIDE_CHARACTER_TYPE

dnl Check for type definitions
AX_TYPES_CHECK_LOCAL

dnl Checks for libraries and library functions
AX_COMMON_CHECK_LOCAL

dnl Check for enabling libcerror for cross-platform C error functions
AX_LIBCERROR_CHECK_ENABLE

dnl Check for enabling libcthreads for cross-platform C threads functions
AX_LIBCTHREADS_CHECK_ENABLE

dnl Check for enabling libcdata for cross-platform C generic data functions
AX_LIBCDATA_CHECK_ENABLE

dnl Check for enabling libclocale for cross-platform C locale functions
AX_LIBCLOCALE_CHECK_ENABLE

dnl Check for enabling libcnotify for cross-platform C notification functions
AX_LIBCNOTIFY_CHECK_ENABLE

dnl Check for enabling libcsplit for cross-platform C split string functions
AX_LIBCSPLIT_CHECK_ENABLE

dnl Check for enabling libuna for Unicode string support
AX_LIBUNA_CHECK_ENABLE

dnl Check for enabling libcfile for cross-platform C file functions
AX_LIBCFILE_CHECK_ENABLE

dnl Check for enabling libcpath for cross-platform C path functions
AX_LIBCPATH_CHECK_ENABLE

dnl Check for enabling libbfio for basic file IO support
AX_LIBBFIO_CHECK_ENABLE

dnl Check for library function support
AX_LIBODRAW_CHECK_LOCAL

dnl Check for enabling libhmac for message digest hash function support
AX_LIBHMAC_CHECK_ENABLE

dnl Check for odrawtools function support
AX_ODRAWTOOLS_CHECK_LOCAL

dnl Check for headers and functions used in tools

dnl Function to detect if ctime_r or ctime is available
dnl Also checks how to use ctime_r
AC_DEFUN([AX_ODRAWTOOLS_CHECK_FUNC_CTIME],
 [AC_CHECK_FUNCS([ctime_r])

 AS_IF(
  [test "x$ac_cv_func_ctime_r" = xyes],
  [AC_MSG_CHECKING(
   [how to use ctime_r])

  AC_LANG_PUSH(C)

  AC_LINK_IFELSE(
   [AC_LANG_PROGRAM(
    [[#include <time.h>]],
    [[ctime_r( NULL, NULL, 0 )]] )],
    [AC_MSG_RESULT(
     [with additional size argument])
    ac_cv_cv_ctime_r_size=yes],
    [ac_cv_cv_ctime_r_size=no])

  AS_IF(
   [test "x$ac_cv_cv_ctime_r_size" = xno],
   [AC_LINK_IFELSE(
    [AC_LANG_PROGRAM(
     [[#include <time.h>]],
     [[ctime_r( NULL, NULL )]] )],
    [AC_MSG_RESULT(
     [with two arguments])
    ac_cv_cv_ctime_r_posix=yes],
    [ac_cv_cv_ctime_r_posix=no])
   ])

  AS_IF(
   [test "x$ac_cv_cv_ctime_r_posix" = xno],
   [CPPFLAGS="$CPPFLAGS -D_POSIX_PTHREAD_SEMANTICS"
   AC_LINK_IFELSE(
    [AC_LANG_PROGRAM(
     [[#include <time.h>]],
     [[ctime_r( NULL, NULL )]] )],
    [AC_MSG_RESULT(
     [with two arguments and definition _POSIX_PTHREAD_SEMANTICS])
     ac_cv_cv_ctime_r_posix=yes],
    [ac_cv_cv_ctime_r_posix=no])
   ])

  AC_LANG_POP(C)

  AS_IF(
   [test "x$ac_cv_cv_ctime_r_size" = xno && test "x$ac_cv_cv_ctime_r_posix" = xno],
   [AC_MSG_WARN(
    [unknown])
   ac_cv_func_ctime_r=no])

  AS_IF(
   [test "x$ac_cv_func_ctime_r" = xyes],
   [AC_DEFINE(
    [HAVE_CTIME_R],
    [1],
    [Define to 1 if you have the ctime_r function.])
   ])

  AS_IF(
   [test "x$ac_cv_cv_ctime_r_size" = xyes],
   [AC_DEFINE(
    [HAVE_CTIME_R_SIZE],
    [1],
    [Define to 1 if you have the ctime_r function with a third size argument.])
   ])
  ])

 AS_IF(
  [test "x$ac_cv_func_ctime_r" = xno],
  [AC_CHECK_FUNCS([ctime])

  AS_IF(
   [test "x$ac_cv_func_ctime" = xno],
   [AC_MSG_FAILURE(
    [Missing function: ctime_r and ctime],
    [1])
   ])
  ])
 ])

AS_IF(
 [test "x$ac_cv_enable_winapi" = xno],
 [AC_HEADER_TIME
 AC_CHECK_FUNCS([time])
 ])

dnl Date and time functions used in odrawtools/process_status.c
AX_ODRAWTOOLS_CHECK_FUNC_CTIME
 
AC_CHECK_FUNCS([gmtime gmtime_r time])

AS_IF(
 [test "x$ac_cv_func_gmtime" != xyes && test "x$ac_cv_func_gmtime_r" != xyes],
 [AC_MSG_FAILURE(
  [Missing functions: gmtime_r and gmtime],
  [1])
 ])
 
AS_IF(
 [test "x$ac_cv_func_time" != xyes],
 [AC_MSG_FAILURE(
  [Missing function: time],
  [1])
 ])
 
dnl Check if odrawtools should be build as static executables
AX_COMMON_CHECK_ENABLE_STATIC_EXECUTABLES

dnl Check if libodraw should be build with verbose output
AX_COMMON_CHECK_ENABLE_VERBOSE_OUTPUT

dnl Check if libodraw should be build with debug output
AX_COMMON_CHECK_ENABLE_DEBUG_OUTPUT

dnl Headers included in various places
AC_CHECK_HEADERS([stdarg.h varargs.h])

AS_IF(
 [test "x$ac_cv_header_stdarg_h" != xyes && test "x$ac_cv_header_varargs_h" != xyes],
 [AC_MSG_FAILURE(
  [Missing headers: stdarg.h and varargs.h],
  [1])
 ])

dnl Check if DLL support is needed
AS_IF(
 [test "x$enable_shared" = xyes],
 [AS_CASE(
  [$host],
  [*cygwin* | *mingw*],
  [AC_DEFINE(
   [HAVE_DLLMAIN],
   [1],
   [Define to 1 to enable the DllMain function.])
  AC_SUBST(
   [HAVE_DLLMAIN],
   [1])

  AS_IF(
   [test "x$ac_cv_enable_static_executables" = xno],
   [AC_SUBST(
    [LIBODRAW_DLL_IMPORT],
    ["-DLIBODRAW_DLL_IMPORT"])
   ])
  ])
 ])

dnl Set additional compiler flags
CFLAGS="$CFLAGS -Wall";

dnl Check if requires and build requires should be set in spec file
AS_IF(
 [test "x$ac_cv_libcerror" = xyes || test "x$ac_cv_libcthreads" = xyes || test "x$ac_cv_libcdata" = xyes || test "x$ac_cv_libclocale" = xyes || test "x$ac_cv_libcnotify" = xyes || test "x$ac_cv_libcsplit" = xyes || test "x$ac_cv_libuna" = xyes || test "x$ac_cv_libcfile" = xyes || test "x$ac_cv_libcpath" = xyes || test "x$ac_cv_libbfio" = xyes],
 [AC_SUBST(
  [libodraw_spec_requires],
  [Requires:])
 AC_SUBST(
  [libodraw_spec_build_requires],
  [BuildRequires:])
 ])

AS_IF(
 [test "x$ac_cv_libhmac" = xyes || test "x$ac_cv_libcrypto" = xyes],
 [AC_SUBST(
  [libodraw_tools_spec_build_requires],
  [BuildRequires:])
 ])

dnl Set the date for the dpkg files
AC_SUBST(
 [DPKG_DATE],
 [`date -R 2> /dev/null`])

dnl Set the date for the spec file
AC_SUBST(
 [SPEC_DATE],
 [`date +"%a %b %e %Y" 2> /dev/null`])

dnl Set the current working directory for PackageMaker files
AC_SUBST(
 [PWD],
 [`pwd`])

dnl Have configure make the Makefiles
AC_CONFIG_FILES([Makefile])
AC_CONFIG_FILES([include/Makefile])
AC_CONFIG_FILES([common/Makefile])
AC_CONFIG_FILES([libcerror/Makefile])
AC_CONFIG_FILES([libcthreads/Makefile])
AC_CONFIG_FILES([libcdata/Makefile])
AC_CONFIG_FILES([libclocale/Makefile])
AC_CONFIG_FILES([libcnotify/Makefile])
AC_CONFIG_FILES([libcsplit/Makefile])
AC_CONFIG_FILES([libuna/Makefile])
AC_CONFIG_FILES([libcfile/Makefile])
AC_CONFIG_FILES([libcpath/Makefile])
AC_CONFIG_FILES([libbfio/Makefile])
AC_CONFIG_FILES([libodraw/Makefile])
AC_CONFIG_FILES([libhmac/Makefile])
AC_CONFIG_FILES([odrawtools/Makefile])
AC_CONFIG_FILES([po/Makefile.in])
AC_CONFIG_FILES([po/Makevars])
AC_CONFIG_FILES([manuals/Makefile])
AC_CONFIG_FILES([tests/Makefile])
AC_CONFIG_FILES([msvscpp/Makefile])
dnl Have configure make the include files
AC_CONFIG_FILES([include/libodraw.h])
AC_CONFIG_FILES([include/libodraw/definitions.h])
AC_CONFIG_FILES([include/libodraw/features.h])
AC_CONFIG_FILES([include/libodraw/types.h])
AC_CONFIG_FILES([libodraw/libodraw_definitions.h])
dnl Have configure make distribution specific files
AC_CONFIG_FILES([common/types.h])
AC_CONFIG_FILES([dpkg/changelog])
AC_CONFIG_FILES([dpkg/copyright])
AC_CONFIG_FILES([libodraw/libodraw.rc])
AC_CONFIG_FILES([libodraw.pc])
AC_CONFIG_FILES([libodraw.spec])
dnl Have configure write its configuration
AC_CONFIG_HEADERS([common/config.h])

AC_OUTPUT

dnl Print a summary
AC_MSG_NOTICE([
Building:
   libcerror support:                          $ac_cv_libcerror
   libcthreads support:                        $ac_cv_libcthreads
   libcdata support:                           $ac_cv_libcdata
   libclocale support:                         $ac_cv_libclocale
   libcnotify support:                         $ac_cv_libcnotify
   libcsplit support:                          $ac_cv_libcsplit
   libuna support:                             $ac_cv_libuna
   libcfile support:                           $ac_cv_libcfile
   libcpath support:                           $ac_cv_libcpath
   libbfio support:                            $ac_cv_libbfio
   libhmac support:                            $ac_cv_libhmac
   MD5 support:                                $ac_cv_libhmac_md5
   SHA1 support:                               $ac_cv_libhmac_sha1
   SHA256 support:                             $ac_cv_libhmac_sha256

Features:
   Multi-threading support:                    $ac_cv_libcthreads_multi_threading
   Wide character type support:                $ac_cv_enable_wide_character_type
   odrawtools are build as static executables: $ac_cv_enable_static_executables
   Verbose output:                             $ac_cv_enable_verbose_output
   Debug output:                               $ac_cv_enable_debug_output
]);


