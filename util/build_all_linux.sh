#!/usr/bin/env bash

CMakeLinuxPorts="
	2048-Gtk1
	2048-Gtk2
	2048-Gtk3
	2048-Motif
	2048-Qt1
	2048-Qt2
	2048-Qt3
	2048-Qt4
	2048-Qt5
	2048-QtQuick
	2048-Xaw
	2048-Xcb
	2048-Xlib
"

function cmake_determine {
	if [ -x "$(command -v cmake3)" ]; then
		cmake3 $*
	else
		cmake $*
	fi
}

function clean {
	git clean -fdx
	git checkout -- .
}

function build_port {
	cd $1
	cmake_determine -DCMAKE_BUILD_TYPE=Release .
	make VERBOSE=1
	strip -s $1
	mv $1 ../build
	cd -
}

function build_juce_port {
	cd 2048-JUCE/Builds/LinuxMakefile/
	make CONFIG=Release V=1
	strip -s build/2048-JUCE
	mv build/2048-JUCE ../../../build
	cd -
}

function build_all {
	build_juce_port
	for port in $CMakeLinuxPorts; do
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
