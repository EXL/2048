#!/bin/bash ../.port_include.sh
port=2048
version=git
files="http://esxi.z-lab.me:666/~exl_lab/software/2048.zip 2048-${version}.zip"
workdir=2048
makeopts="-C 2048-Serenity/port -f Makefile.port"
installopts="-C 2048-Serenity/port -f Makefile.port"
