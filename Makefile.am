AM_CPPFLAGS = \
			-I$(top_builddir)/protocol/tizen \
			-I$(top_builddir)/protocol/unstable \
			-I$(top_builddir)/protocol/stable \
			-I$(top_srcdir)/src \
			$(NULL)

pkgconfigdir = $(libdir)/pkgconfig
protocoldir = $(libdir)
protocolincludedir = $(includedir)/wayland-extension

pkgconfig_DATA =
protocolinclude_HEADERS = src/wayland-extension-version.h
protocol_LTLIBRARIES =

### protocol/tizen/protocol.[ch]
protocol/tizen/%-protocol.c : $(top_srcdir)/protocol/tizen/%.xml
	$(wayland_scanner) code < $< > $@
protocol/tizen/%-server-protocol.h : $(top_srcdir)/protocol/tizen/%.xml
	$(wayland_scanner) server-header < $< > $@
protocol/tizen/%-client-protocol.h : $(top_srcdir)/protocol/tizen/%.xml
	$(wayland_scanner) client-header < $< > $@

### protocol/unstable/protocol.[ch]
protocol/unstable/%-protocol.c : $(top_srcdir)/protocol/unstable/*/%.xml
	$(wayland_scanner) code < $< > $@
protocol/unstable/%-server-protocol.h : $(top_srcdir)/protocol/unstable/*/%.xml
	$(wayland_scanner) server-header < $< > $@
protocol/unstable/%-client-protocol.h : $(top_srcdir)/protocol/unstable/*/%.xml
	$(wayland_scanner) client-header < $< > $@

### protocol/stable/protocol.[ch]
protocol/stable/%-protocol.c : $(top_srcdir)/protocol/stable/*/%.xml
	$(wayland_scanner) code < $< > $@
protocol/stable/%-server-protocol.h : $(top_srcdir)/protocol/stable/*/%.xml
	$(wayland_scanner) server-header < $< > $@
protocol/stable/%-client-protocol.h : $(top_srcdir)/protocol/stable/*/%.xml
	$(wayland_scanner) client-header < $< > $@

### protocol.pc
src/%-server.pc : $(top_srcdir)/src/template-server.pc
	$(cp) $< $@ && $(perl) -pi -e 's|template|$*|g' $@
src/%-client.pc : $(top_srcdir)/src/template-client.pc
	$(cp) $< $@ && $(perl) -pi -e 's|template|$*|g' $@

### xdg-shell (unstable v5)
protocol_LTLIBRARIES += \
	libxdg-shell-unstable-v5-server.la \
	libxdg-shell-unstable-v5-client.la
pkgconfig_DATA += \
	src/xdg-shell-unstable-v5-server.pc \
	src/xdg-shell-unstable-v5-client.pc
protocolinclude_HEADERS += \
	protocol/unstable/xdg-shell-unstable-v5-server-protocol.h \
	protocol/unstable/xdg-shell-unstable-v5-client-protocol.h
libxdg_shell_unstable_v5_server_la_SOURCES = protocol/unstable/xdg-shell-unstable-v5-protocol.c
libxdg_shell_unstable_v5_server_la_CFLAGS  = @WAYLAND_SERVER_CFLAGS@
libxdg_shell_unstable_v5_server_la_LIBADD  = @WAYLAND_SERVER_LIBS@
libxdg_shell_unstable_v5_client_la_SOURCES = protocol/unstable/xdg-shell-unstable-v5-protocol.c
libxdg_shell_unstable_v5_client_la_CFLAGS  = @WAYLAND_CLIENT_CFLAGS@
libxdg_shell_unstable_v5_client_la_LIBADD  = @WAYLAND_CLIENT_LIBS@

### xdg-shell (unstable v6)
protocol_LTLIBRARIES += \
	libxdg-shell-unstable-v6-server.la \
	libxdg-shell-unstable-v6-client.la
pkgconfig_DATA += \
	src/xdg-shell-unstable-v6-server.pc \
	src/xdg-shell-unstable-v6-client.pc
protocolinclude_HEADERS += \
	protocol/unstable/xdg-shell-unstable-v6-server-protocol.h \
	protocol/unstable/xdg-shell-unstable-v6-client-protocol.h
libxdg_shell_unstable_v6_server_la_SOURCES = protocol/unstable/xdg-shell-unstable-v6-protocol.c
libxdg_shell_unstable_v6_server_la_CFLAGS  = @WAYLAND_SERVER_CFLAGS@
libxdg_shell_unstable_v6_server_la_LIBADD  = @WAYLAND_SERVER_LIBS@
libxdg_shell_unstable_v6_client_la_SOURCES = protocol/unstable/xdg-shell-unstable-v6-protocol.c
libxdg_shell_unstable_v6_client_la_CFLAGS  = @WAYLAND_CLIENT_CFLAGS@
libxdg_shell_unstable_v6_client_la_LIBADD  = @WAYLAND_CLIENT_LIBS@

### xdg-shell (stable v1)
protocol_LTLIBRARIES += \
	libxdg-shell-server.la \
	libxdg-shell-client.la
pkgconfig_DATA += \
	src/xdg-shell-server.pc \
	src/xdg-shell-client.pc
protocolinclude_HEADERS += \
	protocol/stable/xdg-shell-server-protocol.h \
	protocol/stable/xdg-shell-client-protocol.h
libxdg_shell_server_la_SOURCES = protocol/stable/xdg-shell-protocol.c
libxdg_shell_server_la_CFLAGS  = @WAYLAND_SERVER_CFLAGS@
libxdg_shell_server_la_LIBADD  = @WAYLAND_SERVER_LIBS@
libxdg_shell_client_la_SOURCES = protocol/stable/xdg-shell-protocol.c
libxdg_shell_client_la_CFLAGS  = @WAYLAND_CLIENT_CFLAGS@
libxdg_shell_client_la_LIBADD  = @WAYLAND_CLIENT_LIBS@

### input-method
protocol_LTLIBRARIES += \
	libinput-method-server.la \
	libinput-method-client.la
pkgconfig_DATA += \
	src/input-method-server.pc \
	src/input-method-client.pc
protocolinclude_HEADERS += \
	protocol/tizen/input-method-server-protocol.h \
	protocol/tizen/input-method-client-protocol.h
libinput_method_server_la_SOURCES = protocol/tizen/input-method-protocol.c
libinput_method_server_la_CFLAGS  = @WAYLAND_SERVER_CFLAGS@
libinput_method_server_la_LIBADD  = @WAYLAND_SERVER_LIBS@
libinput_method_client_la_SOURCES = protocol/tizen/input-method-protocol.c
libinput_method_client_la_CFLAGS  = @WAYLAND_CLIENT_CFLAGS@
libinput_method_client_la_LIBADD  = @WAYLAND_CLIENT_LIBS@

### fullscreen-shell
protocol_LTLIBRARIES += \
	libfullscreen-shell-server.la \
	libfullscreen-shell-client.la
pkgconfig_DATA += \
	src/fullscreen-shell-server.pc \
	src/fullscreen-shell-client.pc
protocolinclude_HEADERS += \
	protocol/tizen/fullscreen-shell-server-protocol.h \
	protocol/tizen/fullscreen-shell-client-protocol.h
libfullscreen_shell_server_la_SOURCES = protocol/tizen/fullscreen-shell-protocol.c
libfullscreen_shell_server_la_CFLAGS  = @WAYLAND_SERVER_CFLAGS@
libfullscreen_shell_server_la_LIBADD  = @WAYLAND_SERVER_LIBS@
libfullscreen_shell_client_la_SOURCES = protocol/tizen/fullscreen-shell-protocol.c
libfullscreen_shell_client_la_CFLAGS  = @WAYLAND_CLIENT_CFLAGS@
libfullscreen_shell_client_la_LIBADD  = @WAYLAND_CLIENT_LIBS@

### scaler
protocol_LTLIBRARIES += \
	libscaler-server.la \
	libscaler-client.la
pkgconfig_DATA += \
	src/scaler-server.pc \
	src/scaler-client.pc
protocolinclude_HEADERS += \
	protocol/tizen/scaler-server-protocol.h \
	protocol/tizen/scaler-client-protocol.h
libscaler_server_la_SOURCES = protocol/tizen/scaler-protocol.c
libscaler_server_la_CFLAGS  = @WAYLAND_SERVER_CFLAGS@
libscaler_server_la_LIBADD  = @WAYLAND_SERVER_LIBS@
libscaler_client_la_SOURCES = protocol/tizen/scaler-protocol.c
libscaler_client_la_CFLAGS  = @WAYLAND_CLIENT_CFLAGS@
libscaler_client_la_LIBADD  = @WAYLAND_CLIENT_LIBS@

### transformer
protocol_LTLIBRARIES += \
	libtransform-server.la \
	libtransform-client.la
pkgconfig_DATA += \
	src/transform-server.pc \
	src/transform-client.pc
protocolinclude_HEADERS += \
	protocol/tizen/transform-server-protocol.h \
	protocol/tizen/transform-client-protocol.h
libtransform_server_la_SOURCES = protocol/tizen/transform-protocol.c
libtransform_server_la_CFLAGS  = @WAYLAND_SERVER_CFLAGS@
libtransform_server_la_LIBADD  = @WAYLAND_SERVER_LIBS@
libtransform_client_la_SOURCES = protocol/tizen/transform-protocol.c
libtransform_client_la_CFLAGS  = @WAYLAND_CLIENT_CFLAGS@
libtransform_client_la_LIBADD  = @WAYLAND_CLIENT_LIBS@

### screenshooter
protocol_LTLIBRARIES += \
	libscreenshooter-server.la \
	libscreenshooter-client.la
pkgconfig_DATA += \
	src/screenshooter-server.pc \
	src/screenshooter-client.pc
protocolinclude_HEADERS += \
	protocol/tizen/screenshooter-server-protocol.h \
	protocol/tizen/screenshooter-client-protocol.h
libscreenshooter_server_la_SOURCES = protocol/tizen/screenshooter-protocol.c
libscreenshooter_server_la_CFLAGS  = @WAYLAND_SERVER_CFLAGS@
libscreenshooter_server_la_LIBADD  = @WAYLAND_SERVER_LIBS@
libscreenshooter_client_la_SOURCES = protocol/tizen/screenshooter-protocol.c
libscreenshooter_client_la_CFLAGS  = @WAYLAND_CLIENT_CFLAGS@
libscreenshooter_client_la_LIBADD  = @WAYLAND_CLIENT_LIBS@

### text-cursor-position
protocol_LTLIBRARIES += \
	libtext-cursor-position-server.la \
	libtext-cursor-position-client.la
pkgconfig_DATA += \
	src/text-cursor-position-server.pc \
	src/text-cursor-position-client.pc
protocolinclude_HEADERS += \
	protocol/tizen/text-cursor-position-server-protocol.h \
	protocol/tizen/text-cursor-position-client-protocol.h
libtext_cursor_position_server_la_SOURCES = protocol/tizen/text-cursor-position-protocol.c
libtext_cursor_position_server_la_CFLAGS  = @WAYLAND_SERVER_CFLAGS@
libtext_cursor_position_server_la_LIBADD  = @WAYLAND_SERVER_LIBS@
libtext_cursor_position_client_la_SOURCES = protocol/tizen/text-cursor-position-protocol.c
libtext_cursor_position_client_la_CFLAGS  = @WAYLAND_CLIENT_CFLAGS@
libtext_cursor_position_client_la_LIBADD  = @WAYLAND_CLIENT_LIBS@

### text
protocol_LTLIBRARIES += \
	libtext-server.la \
	libtext-client.la
pkgconfig_DATA += \
	src/text-server.pc \
	src/text-client.pc
protocolinclude_HEADERS += \
	protocol/tizen/text-server-protocol.h \
	protocol/tizen/text-client-protocol.h
libtext_server_la_SOURCES = protocol/tizen/text-protocol.c
libtext_server_la_CFLAGS  = @WAYLAND_SERVER_CFLAGS@
libtext_server_la_LIBADD  = @WAYLAND_SERVER_LIBS@
libtext_client_la_SOURCES = protocol/tizen/text-protocol.c
libtext_client_la_CFLAGS  = @WAYLAND_CLIENT_CFLAGS@
libtext_client_la_LIBADD  = @WAYLAND_CLIENT_LIBS@

### tizen-extension
protocol_LTLIBRARIES += \
	libtizen-extension-server.la \
	libtizen-extension-client.la
pkgconfig_DATA += \
	src/tizen-extension-server.pc \
	src/tizen-extension-client.pc
protocolinclude_HEADERS += \
	protocol/tizen/tizen-extension-server-protocol.h \
	protocol/tizen/tizen-extension-client-protocol.h
libtizen_extension_server_la_SOURCES = protocol/tizen/tizen-extension-protocol.c
libtizen_extension_server_la_CFLAGS  = @WAYLAND_SERVER_CFLAGS@
libtizen_extension_server_la_LIBADD  = @WAYLAND_SERVER_LIBS@
libtizen_extension_client_la_SOURCES = protocol/tizen/tizen-extension-protocol.c
libtizen_extension_client_la_CFLAGS  = @WAYLAND_CLIENT_CFLAGS@
libtizen_extension_client_la_LIBADD  = @WAYLAND_CLIENT_LIBS@

### tizen-remote-surface
protocol_LTLIBRARIES += \
	libtizen-remote-surface-server.la \
	libtizen-remote-surface-client.la
pkgconfig_DATA += \
	src/tizen-remote-surface-server.pc \
	src/tizen-remote-surface-client.pc
protocolinclude_HEADERS += \
	protocol/tizen/tizen-remote-surface-server-protocol.h \
	protocol/tizen/tizen-remote-surface-client-protocol.h
libtizen_remote_surface_server_la_SOURCES = protocol/tizen/tizen-remote-surface-protocol.c
libtizen_remote_surface_server_la_CFLAGS  = @WAYLAND_SERVER_CFLAGS@
libtizen_remote_surface_server_la_LIBADD  = @WAYLAND_SERVER_LIBS@
libtizen_remote_surface_client_la_SOURCES = protocol/tizen/tizen-remote-surface-protocol.c
libtizen_remote_surface_client_la_CFLAGS  = @WAYLAND_CLIENT_CFLAGS@
libtizen_remote_surface_client_la_LIBADD  = @WAYLAND_CLIENT_LIBS@

### tizen-launch
protocol_LTLIBRARIES += \
        libtizen-launch-server.la \
        libtizen-launch-client.la
pkgconfig_DATA += \
        src/tizen-launch-server.pc \
        src/tizen-launch-client.pc
protocolinclude_HEADERS += \
        protocol/tizen/tizen-launch-server-protocol.h \
        protocol/tizen/tizen-launch-client-protocol.h
libtizen_launch_server_la_SOURCES = protocol/tizen/tizen-launch-protocol.c
libtizen_launch_server_la_CFLAGS  = @WAYLAND_SERVER_CFLAGS@
libtizen_launch_server_la_LIBADD  = @WAYLAND_SERVER_LIBS@
libtizen_launch_client_la_SOURCES = protocol/tizen/tizen-launch-protocol.c
libtizen_launch_client_la_CFLAGS  = @WAYLAND_CLIENT_CFLAGS@
libtizen_launch_client_la_LIBADD  = @WAYLAND_CLIENT_LIBS@

### tizen-surface
protocol_LTLIBRARIES += \
        libtizen-surface-server.la \
        libtizen-surface-client.la
pkgconfig_DATA += \
        src/tizen-surface-server.pc \
        src/tizen-surface-client.pc
protocolinclude_HEADERS += \
        protocol/tizen-surface-server-protocol.h \
        protocol/tizen-surface-client-protocol.h
libtizen_surface_server_la_SOURCES = protocol/tizen-surface-protocol.c
libtizen_surface_server_la_CFLAGS  = @WAYLAND_SERVER_CFLAGS@
libtizen_surface_server_la_LIBADD  = @WAYLAND_SERVER_LIBS@
libtizen_surface_client_la_SOURCES = protocol/tizen-surface-protocol.c
libtizen_surface_client_la_CFLAGS  = @WAYLAND_CLIENT_CFLAGS@
libtizen_surface_client_la_LIBADD  = @WAYLAND_CLIENT_LIBS@

### wayland-protocols
unstable_protocols = \
	protocol/unstable/pointer-gestures/pointer-gestures-unstable-v1.xml \
	protocol/unstable/fullscreen-shell/fullscreen-shell-unstable-v1.xml \
	protocol/unstable/linux-dmabuf/linux-dmabuf-unstable-v1.xml \
	protocol/unstable/text-input/text-input-unstable-v1.xml \
	protocol/unstable/input-method/input-method-unstable-v1.xml \
	protocol/unstable/xdg-shell/xdg-shell-unstable-v5.xml \
	protocol/unstable/xdg-shell/xdg-shell-unstable-v6.xml \
	protocol/unstable/relative-pointer/relative-pointer-unstable-v1.xml \
	protocol/unstable/pointer-constraints/pointer-constraints-unstable-v1.xml \
	protocol/unstable/tablet/tablet-unstable-v1.xml \
	protocol/unstable/tablet/tablet-unstable-v2.xml \
	protocol/unstable/xdg-foreign/xdg-foreign-unstable-v1.xml \
	protocol/unstable/xdg-foreign/xdg-foreign-unstable-v2.xml \
	protocol/unstable/idle-inhibit/idle-inhibit-unstable-v1.xml \
	protocol/unstable/xwayland-keyboard-grab/xwayland-keyboard-grab-unstable-v1.xml \
	protocol/unstable/keyboard-shortcuts-inhibit/keyboard-shortcuts-inhibit-unstable-v1.xml \
	protocol/unstable/xdg-output/xdg-output-unstable-v1.xml \
	protocol/unstable/input-timestamps/input-timestamps-unstable-v1.xml \
	$(NULL)

stable_protocols = \
	protocol/stable/presentation-time/presentation-time.xml \
	protocol/stable/viewporter/viewporter.xml \
	protocol/stable/xdg-shell/xdg-shell.xml \
	$(NULL)

nobase_dist_pkgdata_DATA = \
	$(unstable_protocols) \
	$(stable_protocols) \
	$(NULL)

dist_noinst_DATA = \
	$(sort $(foreach p,$(unstable_protocols),$(dir $p)README)) \
	$(sort $(foreach p,$(stable_protocols),$(dir $p)README)) \
	$(NULL)

pkgconfig_DATA += src/wayland-protocols.pc

dist_check_SCRIPTS = tests/scan.sh

TESTS = $(unstable_protocols) $(stable_protocols)
TEST_EXTENSIONS = .xml
AM_TESTS_ENVIRONMENT = SCANNER='$(wayland_scanner)'; export SCANNER;
XML_LOG_COMPILER = $(srcdir)/tests/scan.sh
