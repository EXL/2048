#!/usr/bin/env bash

func_build() {
	make clean
	make PLATFORM=EZX-Z6; make rmobj
	make PLATFORM=EZX-V8; make rmobj
	make PLATFORM=EZX-Z6W; make rmobj
	make PLATFORM=EZX-U9; make rmobj
	make PLATFORM=EZX-ZN5; make rmobj
	make PLATFORM=EZX-EM30; make rmobj
	make PLATFORM=EZX-E8; make rmobj
	make PLATFORM=EZX-VE66; make rmobj
	make PLATFORM=EZX-EM35; make rmobj
	make PLATFORM=EZX-VA76R; make rmobj
	make PLATFORM=EZX-AURA; make rmobj
}

func_build;
exit 1
