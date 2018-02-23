#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([FULL-PACKAGE-NAME],[VERSION],[BUG-REPORT-ADDRESS])
AC_CONFIG_SRCDIR([main.c])
AM_CONFIG_HEADER([config.h])
AM_INIT_AUTOMAKE([subdir-objects])

# Checks for programs.

AC_PROG_CXX
AC_PROG_CC

# FIXME: Replace `main' with a function in `-lpthread':
AC_CHECK_LIB([pthread], [pthread_rwlock_init])

# Checks for libraries.
AC_PROG_RANLIB

#Checks for header files.
AC_CHECK_HEADERS([stddef.h stdlib.h string.h syslog.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_PID_T
AC_TYPE_SIZE_T

LT_INIT

# Checks for library functions.
AC_FUNC_FORK
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([memset strdup strerror])

AC_CONFIG_FILES([Makefile epplib/Makefile])
AC_OUTPUT
