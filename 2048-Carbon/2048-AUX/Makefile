all: 2048-AUX 2048-Xlib

2048-AUX:
	cc 2048.c 2048-Xlib.c -o 2048-AUX -lX11
	strip 2048-AUX

2048-Xlib:
	cc 2048.c 2048-Xlib.c -o 2048-Xlib -lX11
	strip 2048-Xlib

clean:
	rm -f 2048-AUX 2048-Xlib core *.o
