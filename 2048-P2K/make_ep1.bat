:: This make.bat script was edited by EXL, 15-Jan-2023.
:: Default platform is Motorola P2K, ElfPack v1.x, ADS1.2 [Build 848] on Windows.
:: Warning: `-nodebug` flag option for `armlink` is buggy.

:: Uncomment it for disable verbose output.
:: @echo off

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
set INCLUDES=-I..\src\ -I..\image\icon\precompiled\

:: Optimization.
set OPTIM=-O2

:: Output names.
set ENG_NAME=2048
set ELF_NAME=2048-UIS
set FINAL_NAME=2048-P2K-UIS_EP1

:: Compiling step.
%ARM_PATH%\tcc -I%SDK_PATH% %INCLUDES% %DEFINES% %OPTIM% -bigend -apcs /interwork ^
	-c ..\src\%ENG_NAME%.c -o %ENG_NAME%.o
%ARM_PATH%\tcc -I%SDK_PATH% %INCLUDES% %DEFINES% %OPTIM% -bigend -apcs /interwork ^
	-c %ELF_NAME%.c -o %ELF_NAME%.o

:: Linking step.
%ARM_PATH%\armlink -nolocals -reloc -first %LIB_MAIN%(Lib) %ELF_NAME%.o %ENG_NAME%.o ^
	%LIB_PATH%\%LIB_MAIN% -o %ELF_NAME%.elf

:: Renaming step.
move /y %ELF_NAME%.elf %FINAL_NAME%.elf

if /I "%1"=="clean" (
	del *.o
	del *.elf
)
