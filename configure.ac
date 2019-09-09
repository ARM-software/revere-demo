AC_INIT([revere-vfio-demo],[0.1],[Vincent Stehlé <vincent.stehle@arm.com>])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([foreign -Wall -Werror])

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
AC_C_INLINE
AC_FUNC_MMAP
AC_TYPE_SIZE_T
AC_TYPE_UINT64_T
AC_TYPE_OFF_T
AC_TYPE_SSIZE_T
AC_TYPE_UINT8_T

CFLAGS="-Wall -Wextra $CFLAGS"

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
