#!/usr/bin/env bash

date=`date "+%d-%b-%Y"`

function clean {
	cd 2048-MotoMAGX/
	make clean
	cd -
}

function build_mpkg {
	cd 2048-MotoMAGX/
	make PLATFORM=EZX-Z6
	make mpkg
	mv 2048-MotoMAGX_Z6.mpkg "../2048-MotoMAGX_Z6_v1.0_$date.mpkg"
	cd -
}

function main {
	cd "`dirname $0`/../"
	build_mpkg
	clean
	cd -
	exit
}

main
