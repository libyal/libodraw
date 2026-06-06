dnl Checks for required headers and functions
dnl
dnl Version: 20260606

dnl Function to detect if libodraw dependencies are available
AC_DEFUN([AX_LIBODRAW_CHECK_LOCAL],
  [AC_PROG_LEX(noyywrap)
  AC_PROG_YACC

  dnl Check for internationalization functions in libodraw/libodraw_i18n.c
  AC_CHECK_FUNCS([bindtextdomain])
])

dnl Function to check if DLL support is needed
AC_DEFUN([AX_LIBODRAW_CHECK_DLL_SUPPORT],
  [AS_IF(
    [test "x$enable_shared" = xyes && test "x$ac_cv_enable_static_executables" = xno],
    [AS_CASE(
      [$host],
      [*cygwin* | *mingw* | *msys*],
      [AC_DEFINE(
        [HAVE_DLLMAIN],
        [1],
        [Define to 1 to enable the DllMain function.])
      AC_SUBST(
        [HAVE_DLLMAIN],
        [1])

      AC_SUBST(
        [LIBODRAW_DLL_EXPORT],
        ["-DLIBODRAW_DLL_EXPORT"])

      AC_SUBST(
        [LIBODRAW_DLL_IMPORT],
        ["-DLIBODRAW_DLL_IMPORT"])
      ])
    ])
  ])

