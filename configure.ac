AC_PREREQ([2.64])

m4_define([wayland_extension_major_version], [1])
m4_define([wayland_extension_minor_version], [0])
m4_define([wayland_extension_micro_version], [0])
m4_define([wayland_extension_version],
          [wayland_extension_major_version.wayland_extension_minor_version.wayland_extension_micro_version])

m4_define([wayland_protocols_major_version], [1])
m4_define([wayland_protocols_minor_version], [11])
m4_define([wayland_protocols_version],
          [wayland_protocols_major_version.wayland_protocols_minor_version])

AC_INIT([wayland-extension],
        [wayland_extension_version],
        [https://bugs.tizen.org/jira],
        [wayland-extension])

AC_SUBST([WAYLAND_EXTENSION_VERSION_MAJOR], [wayland_extension_major_version])
AC_SUBST([WAYLAND_EXTENSION_VERSION_MINOR], [wayland_extension_minor_version])
AC_SUBST([WAYLAND_EXTENSION_VERSION_MICRO], [wayland_extension_micro_version])
AC_SUBST([WAYLAND_EXTENSION_VERSION], [wayland_extension_version])
AC_SUBST([WAYLAND_PROTOCOLS_VERSION], [wayland_protocols_version])

AC_CONFIG_HEADERS([config.h])
#AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([1.11 foreign no-dist-gzip dist-xz subdir-objects])

AM_SILENT_RULES([yes])

# Check for programs
AC_PROG_CC
AC_PROG_CXX
#AC_PROG_GREP
AC_PATH_PROG([wayland_scanner], [wayland-scanner])
if test x$wayland_scanner = x; then
   AC_MSG_ERROR([wayland-scanner is needed to compile])
fi
AC_PATH_PROG([cp], [cp])
if test x$cp = x; then
   AC_MSG_ERROR([cp is needed to compile])
fi
AC_PATH_PROG([perl], [perl])
if test x$perl = x; then
   AC_MSG_ERROR([perl is needed to compile])
fi

# Initialize libtool
LT_PREREQ([2.2])
LT_INIT

PKG_PROG_PKG_CONFIG()

PKG_CHECK_MODULES(WAYLAND_SERVER, wayland-server >= 1.7.0)
AC_SUBST(WAYLAND_SERVER_CFLAGS)
AC_SUBST(WAYLAND_SERVER_LIBS)

PKG_CHECK_MODULES(WAYLAND_CLIENT, wayland-client >= 1.7.0)
AC_SUBST(WAYLAND_CLIENT_CFLAGS)
AC_SUBST(WAYLAND_CLIENT_LIBS)

PKG_CHECK_MODULES(WAYLAND_SCANNER, wayland-scanner >= 1.7.0)

AC_CONFIG_FILES([
	Makefile
	src/wayland-extension-version.h
	src/template-server.pc
	src/template-client.pc
	src/tizen-remote-surface-server.pc
	src/tizen-remote-surface-client.pc
	src/wayland-protocols.pc
])
AC_OUTPUT
