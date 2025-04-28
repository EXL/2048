.PHONY: main
main:
	arm-none-eabi-gcc -Os -o bin.elf main.c ../src/2048.c -I ../src -nostartfiles -pie -fPIC -marm -march=armv5te --entry=_start