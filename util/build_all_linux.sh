#!/usr/bin/env bash

LinuxPorts="
	2048-Gtk1
	2048-Gtk2
	2048-Gtk3
	2048-Motif
	2048-Qt1
	2048-Qt2
	2048-Qt3
	2048-Qt4
	2048-Qt5
	2048-Xaw
	2048-Xcb
	2048-Xlib
"

function clean {
	git clean -fdx
	git checkout -- .
}

function build_port {
	cd $1
	cmake -DCMAKE_BUILD_TYPE=Release .
	make VERBOSE=1
	strip -s $1
	mv $1 ../build
	cd -
}

function build_all {
	for port in $LinuxPorts; do
		build_port $port
	done
}

function main {
	cd "`dirname $0`/../"
	clean
	mkdir -p build
	build_all
	cd -
	exit
}

main
