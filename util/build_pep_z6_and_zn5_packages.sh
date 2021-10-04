#!/usr/bin/env bash

date=`date "+%d-%b-%Y"`

function clean {
	cd 2048-MotoMAGX/
	make clean
	rm -Rf 2048-MotoMAGX/
	cd -
}

function build_pep_Z6 {
	cd 2048-MotoMAGX
	make PLATFORM=EZX-Z6
	mkdir -p 2048-MotoMAGX/app
	cp 2048-MotoMAGX_Z6 2048-MotoMAGX/app/
	cp pep/description.ini 2048-MotoMAGX/
	sed -i "s/EXECUTABLE_FILE/2048-MotoMAGX_Z6/g" 2048-MotoMAGX/description.ini
	cp ../image/icon/ic_launcher0.png 2048-MotoMAGX/app/icon_usr.png
	cp ../image/icon/ic_launcher0.png 2048-MotoMAGX/icon_usr.png
	cp ../image/icon/app-2048-Serenity-16.png 2048-MotoMAGX/icon_small_usr.png
	tar -cvf 2048-MotoMAGX.tar 2048-MotoMAGX/
	gzip -9 2048-MotoMAGX.tar
	mv 2048-MotoMAGX.tar.gz "../2048_MotoMAGX_Z6_v1.0_$date.pep"
	cd -
}

function build_pep_ZN5 {
	cd 2048-MotoMAGX
	make PLATFORM=EZX-ZN5
	mkdir -p 2048-MotoMAGX/app
	cp 2048-MotoMAGX_ZN5 2048-MotoMAGX/app/
	cp pep/description.ini 2048-MotoMAGX/
	sed -i "s/EXECUTABLE_FILE/2048-MotoMAGX_ZN5/g" 2048-MotoMAGX/description.ini
	cp ../image/icon/ic_launcher0.png 2048-MotoMAGX/app/icon_usr.png
	cp ../image/icon/ic_launcher0.png 2048-MotoMAGX/icon_usr.png
	cp ../image/icon/app-2048-Serenity-16.png 2048-MotoMAGX/icon_small_usr.png
	tar -cvf 2048-MotoMAGX.tar 2048-MotoMAGX/
	gzip -9 2048-MotoMAGX.tar
	mv 2048-MotoMAGX.tar.gz "../2048_MotoMAGX_ZN5_v1.0_$date.pep"
	cd -
}

function main {
	cd "`dirname $0`/../"
	build_pep_Z6
	clean
	build_pep_ZN5
	clean
	cd -
	exit
}

main
