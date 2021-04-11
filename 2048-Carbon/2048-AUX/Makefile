# TODO: Comment for Makefile
# TODO: Comment about both application file

CC               = cc
LD               = ld
STRIP            = strip
FCNVT            = /mac/bin/fcnvt -f -d
REZ              = /mac/bin/rez -i /:mac:lib:rincludes
CFLAGS           = -I/usr/include -B /usr/lib/big/ -O

AUX_CFLAGS       = -I/usr/include -I/usr/include/mac -B /usr/lib/big/ -O
AUX_LDFLAGS_PRE  = /usr/lib/maccrt0.o /lib/crt2.o
AUX_LDFLAGS_POST = /usr/lib/low.o -lmac_s -lat -lld -lmr -lc_s /lib/crtn.o /usr/lib/low.ld
AUX_RESOURCE     = %2048-AUX
AUX_TARGET       = 2048-AUX

XLIB_CFLAGS      = -I/usr/include -I/usr/include/X11 -B /usr/lib/big/ -O
XLIB_LIBS        = -lX11
XLIB_TARGET      = 2048-Xlib

XAW_CFLAGS       = -I/usr/include -I/usr/include/X11 -B /usr/lib/big/ -O
XAW_LIBS         = -lXaw -lXmu -lXt -lX11
XAW_TARGET       = 2048-Xaw

all: $(AUX_TARGET) $(XLIB_TARGET) $(XAW_TARGET)

release: all purge
	$(STRIP) $(AUX_TARGET)
	$(STRIP) $(XLIB_TARGET)
	$(STRIP) $(XAW_TARGET)

clean: purge
	rm -f $(AUX_TARGET) $(XLIB_TARGET) $(XAW_TARGET) $(AUX_RESOURCE)

purge:
	rm -f core *.out *.o

$(AUX_TARGET): 2048.o 2048-AUX.o $(AUX_RESOURCE)
	$(LD) $(AUX_LDFLAGS_PRE) 2048.o 2048-AUX.o -o $(AUX_TARGET) $(AUX_LDFLAGS_POST)

$(AUX_RESOURCE): 2048-AUX.r
	$(REZ) 2048-AUX.r
	$(FCNVT) Rez.out $(AUX_TARGET)

$(XLIB_TARGET): 2048.o 2048-Xlib.o
	$(CC) 2048.o 2048-Xlib.o -o $(XLIB_TARGET) $(XLIB_LIBS)

$(XAW_TARGET): 2048.o 2048-Xaw.o
	$(CC) 2048.o 2048-Xaw.o -o $(XAW_TARGET) $(XAW_LIBS)

2048.o: 2048.c 2048.h Makefile
	$(CC) $(CFLAGS) -c 2048.c -o 2048.o

2048-AUX.o: 2048-AUX.c 2048.h Makefile
	$(CC) $(AUX_CFLAGS) -c 2048-AUX.c -o 2048-AUX.o

2048-Xlib.o: 2048-Xlib.c 2048.h Makefile
	$(CC) $(XLIB_CFLAGS) -c 2048-Xlib.c -o 2048-Xlib.o

2048-Xaw.o: 2048-Xaw.c 2048.h Makefile
	$(CC) $(XAW_CFLAGS) -c 2048-Xaw.c -o 2048-Xaw.o
