dnl Function to detect if libodraw dependencies are available
AC_DEFUN([AX_LIBODRAW_CHECK_LOCAL],
 [dnl Check for internationalization functions in libodraw/libodraw_i18n.c
 AC_CHECK_FUNCS([bindtextdomain])

 AM_PROG_LEX
 AC_PROG_YACC])

