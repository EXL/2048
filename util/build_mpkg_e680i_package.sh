#!/usr/bin/env bash

date=`date "+%d-%b-%Y"`

function clean {
	cd 2048-EZX/
	make -f Makefile.e680i clean
	cd -
}

function build_mpkg {
	cd 2048-EZX/
	make -f Makefile.e680i mpkg
	mv 2048-EZX_E680i.mpkg "../2048_MotoEZX_E680i_v1.0_$date.mpkg"
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
