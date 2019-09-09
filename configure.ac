AC_INIT([revere-vfio-demo],[0.1],[Vincent Stehlé <vincent.stehle@arm.com>])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([foreign -Wall -Werror])

# Conditionals
vfio='true'

AC_ARG_ENABLE([vfio], AS_HELP_STRING([--enable-vfio],
		[Enable vfio (the default)]))
AC_ARG_ENABLE([vfio], AS_HELP_STRING([--disable-vfio], [Disable vfio]))

if test "x$enable_vfio" = "xyes"; then
	vfio='true'
fi
if test "x$enable_vfio" = "xno"; then
	vfio='false'
fi

# Checks for programs.
AC_PROG_CC

AC_CHECK_FUNCS([memset])
AC_CHECK_FUNCS([munmap])
AC_CHECK_HEADERS([fcntl.h])
AC_CHECK_HEADERS([stddef.h])
AC_CHECK_HEADERS([stdint.h])
AC_CHECK_HEADERS([stdlib.h])
AC_CHECK_HEADERS([string.h])
AC_CHECK_HEADERS([sys/ioctl.h])
AC_CHECK_HEADERS([unistd.h])
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_FUNC_MMAP
AC_FUNC_MALLOC
AC_TYPE_SIZE_T
AC_TYPE_UINT64_T
AC_TYPE_OFF_T
AC_TYPE_SSIZE_T
AC_TYPE_UINT8_T

if test "x$vfio" = "xtrue"; then
	AC_CHECK_HEADERS([linux/vfio.h])
	AC_DEFINE([VFIO], [1], [Build for vfio])
fi
AM_CONDITIONAL([VFIO], [test x$vfio = xtrue])

CFLAGS="-Wall -Wextra -Wpedantic $CFLAGS"

AC_CONFIG_FILES([Makefile])
AC_OUTPUT

AC_MSG_NOTICE([

Options
-------
vfio		$vfio
])
