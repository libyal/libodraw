dnl Checks for tools required headers and functions
dnl
dnl Version: 20260601

dnl Function to determine how to link with MinGW binmode
AC_DEFUN([AX_TOOLS_CHECK_MINGW_BINMODE],
  [MINGW_BINMODE_LDFLAGS=""

  case "$host_os" in
    *mingw* | *cygwin*)
      AC_LANG_PUSH(C)

      AC_MSG_CHECKING([how to link with MinGW binmode])

      BACKUP_LDFLAGS="$LDFLAGS"

      LDFLAGS="$LDFLAGS -lbinmode"

      AC_LINK_IFELSE(
        [AC_LANG_PROGRAM([], [])],
        [MINGW_BINMODE_LDFLAGS="-lbinmode"],
        [MINGW_BINMODE_LDFLAGS=""])

      LDFLAGS="$BACKUP_LDFLAGS"

      AS_IF(
        [test "x$MINGW_BINMODE_LDFLAGS" = "x"],
        [PATH_BINMODE_O=`$CC -print-file-name=binmode.o`

        AS_IF(
          [test -f "$PATH_BINMODE_O"],
          [MINGW_BINMODE_LDFLAGS="-Wl,$PATH_BINMODE_O"],
          [MINGW_BINMODE_LDFLAGS=""])

        AS_IF(
          [test "x$MINGW_BINMODE_LDFLAGS" = "x"],
          [AC_MSG_RESULT([undetermined])],
          [AC_MSG_RESULT([$MINGW_BINMODE_LDFLAGS])])
      ])
      ;;
    *)
      ;;
  esac
])

dnl Function to detect whether MinGW binmode support should be enabled
AC_DEFUN([AX_TOOLS_CHECK_ENABLE_MINGW_BINMODE],
  [AX_COMMON_ARG_ENABLE(
    [mingw-binmode],
    [mingw_binmode],
    [build with MinGW binmode],
    [no])

  AS_IF(
    [test "x$ac_cv_enable_mingw_binmode" != xno],
    [AX_TOOLS_CHECK_MINGW_BINMODE

    AS_IF(
      [test "x$MINGW_BINMODE_LDFLAGS" = xno],
      [AC_MSG_FAILURE(
        [Unable to build with functional MinGW binmode],
        [1])
      ])

    AC_DEFINE(
      [HAVE_MINGW_BINMODE],
      [1],
      [Define to 1 if MinGW binmode should be used.])

    LDFLAGS="$LDFLAGS $MINGW_BINMODE_LDFLAGS"
  ])
])

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

dnl Function to detect if odrawtools dependencies are available
AC_DEFUN([AX_ODRAWTOOLS_CHECK_LOCAL],
  [AC_CHECK_HEADERS([signal.h sys/signal.h unistd.h])

  AC_CHECK_FUNCS([close getopt setvbuf])

  AS_IF(
   [test "x$ac_cv_func_close" != xyes],
   [AC_MSG_FAILURE(
     [Missing function: close],
     [1])
  ])

  dnl Headers included in odrawtools/log_handle.c
  AC_CHECK_HEADERS([stdarg.h varargs.h])

  AS_IF(
    [test "x$ac_cv_header_stdarg_h" != xyes && test "x$ac_cv_header_varargs_h" != xyes],
    [AC_MSG_FAILURE(
      [Missing headers: stdarg.h and varargs.h],
      [1])
  ])

  dnl Headers included in odrawtools/process_status.c
  AC_CHECK_HEADERS([sys/time.h])

  dnl Functions included in odrawtools/process_status.c
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

  AX_TOOLS_CHECK_ENABLE_MINGW_BINMODE
])

