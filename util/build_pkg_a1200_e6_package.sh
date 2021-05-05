#!/usr/bin/env bash

date=`date "+%d-%b-%Y"`

function clean {
	cd 2048-EZX/
	make clean
	cd -
}

function build_pkg {
	cd 2048-EZX/
	make pkg
	mv 2048-EZX.pkg "../2048_MotoEZX_A1200_E6_v1.0_$date.pkg"
	cd -
}

function main {
	cd "`dirname $0`/../"
	build_pkg
	clean
	cd -
	exit
}

main
