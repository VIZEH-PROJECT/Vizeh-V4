
Debian
====================
This directory contains files used to package vizehd/vizeh-qt
for Debian-based Linux systems. If you compile vizehd/vizeh-qt yourself, there are some useful files here.

## vizeh: URI support ##


vizeh-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install vizeh-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your vizehqt binary to `/usr/bin`
and the `../../share/pixmaps/vizeh128.png` to `/usr/share/pixmaps`

vizeh-qt.protocol (KDE)

