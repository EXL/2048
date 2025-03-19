# This Makefile was created by EXL, 19-Sep-2023.
# Default platform is Motorola P2K, ElfPack v1.0, ADS1.2 [Build 848] on Linux.
# Warning: `-nodebug` flag option for `armlink` is buggy.

# Compiler path.
ARM_PATH = /opt/arm

# SDK path.
SDK_PATH = $(ARM_PATH)/SDK

# Libraries path.
LIB_PATH = $(ARM_PATH)/lib

# Main link library.
LIB_MAIN = Lib.o

# Defines.
DEFINES = -D__P2K__ -DEP1 -DUSE_MME
#DEFINES = -D__P2K__ -DEP1 -DUSE_MME -DFTR_V600
#DEFINES = -D__P2K__ -DEP1 -DUSE_MME -DFTR_V635
#DEFINES = -D__P2K__ -DEP1 -DUSE_MME -DFTR_L7E

# Includes.
INCLUDES = -I../../src/ -I../../image/icon/precompiled/ -I../../image/gfx/

# Optimization.
OPTIM = -O2

# Project/ELF name.
ELF_NAME = 2048-AHI

all:
	$(ARM_PATH)/bin/tcc -I$(SDK_PATH) $(INCLUDES) $(DEFINES) $(OPTIM) -bigend -apcs /interwork \
		-c ../../src/2048.c -o 2048.o
	$(ARM_PATH)/bin/tcc -I$(SDK_PATH) $(INCLUDES) $(DEFINES) $(OPTIM) -bigend -apcs /interwork \
		-c $(ELF_NAME).c -o $(ELF_NAME).o
	$(ARM_PATH)/bin/armlink -nolocals -reloc -first $(LIB_MAIN)\(Lib\) 2048.o $(ELF_NAME).o \
		$(LIB_PATH)/$(LIB_MAIN) -o $(ELF_NAME).elf

clean:
	-rm -f *.o
	-rm -f *.obj
	-rm -f *.elfp
	-rm -f *.elf
