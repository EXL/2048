#!/usr/bin/env bash

date=`date "+%d-%b-%Y"`

function clean {
	rm -Rf util/2048/
}

function build_all {
	cd 2048-MotoMAGX/
	./build.sh
	cd -
}

function build_mgx {
	mkdir -p util/2048
	cp 2048-MotoMAGX/2048-MotoMAGX_ZN5 util/2048
	cp 2048-MotoMAGX/mgx/2048.cfg util/2048
	cp image/icon/ic_launcher0.png util/2048/icon_usr.png
	cd util/
	7za a -t7z -m0=lzma -mx=9 -mfb=64 -md=32m -ms=on 2048.7z 2048/
	mv 2048.7z "../2048_MotoMAGX_ZN5_v1.0_$date.mgx"
	cd -
}

function main {
	cd "`dirname $0`/../"
	build_all
	build_mgx
	clean
	cd -
	exit
}

main
