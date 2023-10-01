:: This make.bat script was created by EXL, 19-Sep-2023.
:: Default platform is Motorola P2K, ElfPack v1.x, ADS1.2 [Build 848] on Windows.
:: Warning: `-nodebug` flag option for `armlink` is buggy.

:: Uncomment it for disable verbose output.
:: @echo off

if /I "%1"=="clean" (
	if exist *.o    del *.o
	if exist *.obj  del *.obj
	if exist *.elfp del *.elfp
	if exist *.elf  del *.elf
	exit /b 0
)

:: Compiler path.
set ARM_PATH=C:\ARM

:: SDK path.
set SDK_PATH=%ARM_PATH%\SDK

:: Libraries path.
set LIB_PATH=%ARM_PATH%\lib

:: Main link library.
set LIB_MAIN=Lib.o

:: Defines.
set DEFINES=-D__P2K__ -DEP1 -DUSE_MME
:: set DEFINES=-D__P2K__ -DEP1 -DUSE_MME -DFTR_V600
:: set DEFINES=-D__P2K__ -DEP1 -DUSE_MME -DFTR_L7E

:: Includes.
set INCLUDES=-I..\..\src\ -I..\..\image\icon\precompiled\ -I..\..\image\gfx\

:: Optimization.
set OPTIM=-O2

:: Project/ELF name.
set ELF_NAME=2048-AHI

:: Compiling step.
%ARM_PATH%\tcc -I%SDK_PATH% %INCLUDES% %DEFINES% %OPTIM% -bigend -apcs /interwork ^
	-c ..\..\src\2048.c -o 2048.o
%ARM_PATH%\tcc -I%SDK_PATH% %INCLUDES% %DEFINES% %OPTIM% -bigend -apcs /interwork ^
	-c %ELF_NAME%.c -o %ELF_NAME%.o

:: Linking step.
%ARM_PATH%\armlink -nolocals -reloc -first %LIB_MAIN%(Lib) 2048.o %ELF_NAME%.o ^
	%LIB_PATH%\%LIB_MAIN% -o %ELF_NAME%.elf
