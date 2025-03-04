
Debian
====================
This directory contains files used to package broccolicoind/broccolicoin-qt
for Debian-based Linux systems. If you compile broccolicoind/broccolicoin-qt yourself, there are some useful files here.

## broccolicoin: URI support ##


broccolicoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install broccolicoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your broccolicoin-qt binary to `/usr/bin`
and the `../../share/pixmaps/bitcoin128.png` to `/usr/share/pixmaps`

broccolicoin-qt.protocol (KDE)

