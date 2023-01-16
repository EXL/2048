# This Makefile was edited by EXL, 15-Jan-2023.
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

# Includes.
INCLUDES = -I../src/ -I../image/icon/precompiled/

# Optimization.
OPTIM = -O2

# Output names.
ENG_NAME = 2048
ELF_NAME = 2048-UIS
FINAL_NAME = 2048-P2K-UIS_EP1

all:
	$(ARM_PATH)/bin/tcc -I$(SDK_PATH) $(INCLUDES) $(DEFINES) $(OPTIM) -bigend -apcs /interwork \
		-c ../src/$(ENG_NAME).c -o $(ENG_NAME).o
	$(ARM_PATH)/bin/tcc -I$(SDK_PATH) $(INCLUDES) $(DEFINES) $(OPTIM) -bigend -apcs /interwork \
		-c $(ELF_NAME).c -o $(ELF_NAME).o
	$(ARM_PATH)/bin/armlink -nolocals -reloc -first $(LIB_MAIN)\(Lib\) $(ENG_NAME).o $(ELF_NAME).o \
		$(LIB_PATH)/$(LIB_MAIN) -o $(ELF_NAME).elf
	-mv $(ELF_NAME).elf $(FINAL_NAME).elf

clean:
	-rm -f *.o
	-rm -f *.elf