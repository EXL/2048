# use 'vmake' (not 'make'!) to run this script!

# set this to where Cybiko SDK actually resides
# CYBIKO_SDK = C:\Program Files\Cybiko\Cybiko SDK

RM = vrm
VCC = vcc

APP_NAME = 2048-CyOS
APP_CLASSIC = $(APP_NAME).app
APP_XTREME = $(APP_NAME)_X.app

LIBS = highscore.o

all:
	2pic res/0.ico res/0.bmp
	2pic res/1.ico res/1.bmp
	2pic res/root.ico res/root.bmp
	2pic res/intro.pic res/intro.bmp
	2pic res/score.pic res/score_1.bmp res/score_2.bmp

	$(VCC) -DCYOS -O -c 2048.c -o 2048.o
	$(VCC) -DCYOS -O -c 2048-CyOS.cc -o 2048-CyOS.o
	$(VCC) $(LIBS) 2048.o 2048-CyOS.o -o bytecode.bin

	$(VCC) -R0 @res/filer_classic.list bytecode.bin -o $(APP_CLASSIC)
	$(VCC) -R0 @res/filer_xtreme.list bytecode.bin -o $(APP_XTREME)

clean:
	$(RM) -f res/*.ico
	$(RM) -f res/*.pic
	$(RM) -f *.o
	$(RM) -f *.bin
	$(RM) -f *.app

new: clean all
