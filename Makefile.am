INCLUDES = -I$(top_builddir)/protocol -I$(top_srcdir)/src

pkgconfigdir = $(libdir)/pkgconfig
protocoldir = $(libdir)
protocolincludedir = $(includedir)/wayland-extension

pkgconfig_DATA =
protocolinclude_HEADERS = src/wayland-extension-version.h
protocol_LTLIBRARIES =

### protocol.[ch]
protocol/%-protocol.c : $(top_srcdir)/protocol/%.xml
	$(wayland_scanner) code < $< > $@
protocol/%-server-protocol.h : $(top_srcdir)/protocol/%.xml
	$(wayland_scanner) server-header < $< > $@
protocol/%-client-protocol.h : $(top_srcdir)/protocol/%.xml
	$(wayland_scanner) client-header < $< > $@

### protocol.pc
src/%-server.pc : $(top_srcdir)/src/template-server.pc
	$(cp) $< $@ && $(perl) -pi -e 's|template|$*|g' $@
src/%-client.pc : $(top_srcdir)/src/template-client.pc
	$(cp) $< $@ && $(perl) -pi -e 's|template|$*|g' $@

### xdg-shell
protocol_LTLIBRARIES += \
	libxdg-shell-server.la \
	libxdg-shell-client.la
pkgconfig_DATA += \
	src/xdg-shell-server.pc \
	src/xdg-shell-client.pc
protocolinclude_HEADERS += \
	protocol/xdg-shell-server-protocol.h \
	protocol/xdg-shell-client-protocol.h
libxdg_shell_server_la_SOURCES = protocol/xdg-shell-protocol.c
libxdg_shell_server_la_CFLAGS  = @WAYLAND_SERVER_CFLAGS@
libxdg_shell_server_la_LIBADD  = @WAYLAND_SERVER_LIBS@
libxdg_shell_client_la_SOURCES = protocol/xdg-shell-protocol.c
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
	protocol/input-method-server-protocol.h \
	protocol/input-method-client-protocol.h
libinput_method_server_la_SOURCES = protocol/input-method-protocol.c
libinput_method_server_la_CFLAGS  = @WAYLAND_SERVER_CFLAGS@
libinput_method_server_la_LIBADD  = @WAYLAND_SERVER_LIBS@
libinput_method_client_la_SOURCES = protocol/input-method-protocol.c
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
	protocol/fullscreen-shell-server-protocol.h \
	protocol/fullscreen-shell-client-protocol.h
libfullscreen_shell_server_la_SOURCES = protocol/fullscreen-shell-protocol.c
libfullscreen_shell_server_la_CFLAGS  = @WAYLAND_SERVER_CFLAGS@
libfullscreen_shell_server_la_LIBADD  = @WAYLAND_SERVER_LIBS@
libfullscreen_shell_client_la_SOURCES = protocol/fullscreen-shell-protocol.c
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
	protocol/scaler-server-protocol.h \
	protocol/scaler-client-protocol.h
libscaler_server_la_SOURCES = protocol/scaler-protocol.c
libscaler_server_la_CFLAGS  = @WAYLAND_SERVER_CFLAGS@
libscaler_server_la_LIBADD  = @WAYLAND_SERVER_LIBS@
libscaler_client_la_SOURCES = protocol/scaler-protocol.c
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
	protocol/transform-server-protocol.h \
	protocol/transform-client-protocol.h
libtransform_server_la_SOURCES = protocol/transform-protocol.c
libtransform_server_la_CFLAGS  = @WAYLAND_SERVER_CFLAGS@
libtransform_server_la_LIBADD  = @WAYLAND_SERVER_LIBS@
libtransform_client_la_SOURCES = protocol/transform-protocol.c
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
	protocol/screenshooter-server-protocol.h \
	protocol/screenshooter-client-protocol.h
libscreenshooter_server_la_SOURCES = protocol/screenshooter-protocol.c
libscreenshooter_server_la_CFLAGS  = @WAYLAND_SERVER_CFLAGS@
libscreenshooter_server_la_LIBADD  = @WAYLAND_SERVER_LIBS@
libscreenshooter_client_la_SOURCES = protocol/screenshooter-protocol.c
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
	protocol/text-cursor-position-server-protocol.h \
	protocol/text-cursor-position-client-protocol.h
libtext_cursor_position_server_la_SOURCES = protocol/text-cursor-position-protocol.c
libtext_cursor_position_server_la_CFLAGS  = @WAYLAND_SERVER_CFLAGS@
libtext_cursor_position_server_la_LIBADD  = @WAYLAND_SERVER_LIBS@
libtext_cursor_position_client_la_SOURCES = protocol/text-cursor-position-protocol.c
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
	protocol/text-server-protocol.h \
	protocol/text-client-protocol.h
libtext_server_la_SOURCES = protocol/text-protocol.c
libtext_server_la_CFLAGS  = @WAYLAND_SERVER_CFLAGS@
libtext_server_la_LIBADD  = @WAYLAND_SERVER_LIBS@
libtext_client_la_SOURCES = protocol/text-protocol.c
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
	protocol/tizen-extension-server-protocol.h \
	protocol/tizen-extension-client-protocol.h
libtizen_extension_server_la_SOURCES = protocol/tizen-extension-protocol.c
libtizen_extension_server_la_CFLAGS  = @WAYLAND_SERVER_CFLAGS@
libtizen_extension_server_la_LIBADD  = @WAYLAND_SERVER_LIBS@
libtizen_extension_client_la_SOURCES = protocol/tizen-extension-protocol.c
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
	protocol/tizen-remote-surface-server-protocol.h \
	protocol/tizen-remote-surface-client-protocol.h
libtizen_remote_surface_server_la_SOURCES = protocol/tizen-remote-surface-protocol.c
libtizen_remote_surface_server_la_CFLAGS  = @WAYLAND_SERVER_CFLAGS@
libtizen_remote_surface_server_la_LIBADD  = @WAYLAND_SERVER_LIBS@
libtizen_remote_surface_client_la_SOURCES = protocol/tizen-remote-surface-protocol.c
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
        protocol/tizen-launch-server-protocol.h \
        protocol/tizen-launch-client-protocol.h
libtizen_launch_server_la_SOURCES = protocol/tizen-launch-protocol.c
libtizen_launch_server_la_CFLAGS  = @WAYLAND_SERVER_CFLAGS@
libtizen_launch_server_la_LIBADD  = @WAYLAND_SERVER_LIBS@
libtizen_launch_client_la_SOURCES = protocol/tizen-launch-protocol.c
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
