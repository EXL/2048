:: This make.bat script was edited by EXL, 15-Jan-2023.
:: Default platform is Motorola P2K, ElfPack v1.0, ADS1.2 [Build 848] on Windows.
:: Warning: `-nodebug` flag option for `armlink` is buggy.

:: Uncomment it for verbose output.
:: @echo off

:: Compiler path.
set ARM_PATH=C:\ARM

:: SDK path.
set SDK_PATH=%ARM_PATH%\SDK

:: Libraries path.
set LIB_PATH=%ARM_PATH%\lib

:: Main link library.
set LIB_MAIN=Lib.o
:: set LIB_MAIN=Lib_L2_L6.o

:: Defines.
set DEFINES=-D__P2K__ -DEP1 -DUSE_MME

:: Includes.
set INCLUDES=-I..\src\ -I..\image\icon\precompiled\

:: Optimization.
set OPTIM=-O2

:: Output names.
set O_NAME=2048
set ELF_NAME=2048-UIS

:: Compiling step.
%ARM_PATH%\tcc -I%SDK_PATH% %INCLUDES% %DEFINES% %OPTIM% -bigend -apcs /interwork -O2 -c ..\src\%O_NAME%.c -o %O_NAME%.o
%ARM_PATH%\tcc -I%SDK_PATH% %INCLUDES% %DEFINES% %OPTIM% -bigend -apcs /interwork -O2 -c %ELF_NAME%.c -o %ELF_NAME%.o

:: Linking step.
%ARM_PATH%\armlink -nolocals -reloc -first %LIB_MAIN%(Lib) %ELF_NAME%.o %O_NAME%.o %LIB_PATH%\%LIB_MAIN% -o %ELF_NAME%.elf

if /I "%1"=="clean" (
	del %O_NAME%.o
	del %ELF_NAME%.o
	del %ELF_NAME%.elf
)
