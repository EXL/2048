#!/usr/bin/env bash

date=`date "+%d-%b-%Y"`

function clean {
	cd 2048-EZX/
	make clean
	cd -
}

function build_mpkg {
	cd 2048-EZX/
	make mpkg
	mv 2048-EZX.pkg "../2048_MotoEZX_E6_v1.0_$date.pkg"
	mv 2048-EZX.mpkg "../2048_MotoEZX_E6_v1.0_$date.mpkg"
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
