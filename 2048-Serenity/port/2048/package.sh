#!/bin/bash ../.port_include.sh
port=2048
version=git
# TODO: Replace this link with github.com/EXL/2048 on public release.
files="http://esxi.z-lab.me:666/~exl_lab/software/2048.zip 2048-${version}.zip"
workdir=2048
makeopts="-C 2048-Serenity/port -f Makefile.port"
installopts="-C 2048-Serenity/port -f Makefile.port"
