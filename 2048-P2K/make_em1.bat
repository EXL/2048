:: This make_em1.bat script was created by EXL, 04-Jun-2023.
:: Default platform is Motorola P2K, EM1 ElfPack M*CORE, mcore-elf-gcc (GCC) 3.4.6 on Windows.

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
set MCORE_PATH=C:\MCORE_EM1

:: SDK path.
set SDK_PATH=%MCORE_PATH%\SDK

:: Defines.
set DEFINES=-D__P2K__ -DEM1

:: Includes.
set INCLUDES=-I..\src\ -I..\image\icon\precompiled\

:: Optimization.
set OPTIM=-O2

:: Project/ELF name.
set ELF_NAME=2048-UIS

:: Compiling step.
%MCORE_PATH%\GCC_MCore\bin\mcore-elf-gcc -fshort-wchar -mbig-endian -nostdinc -m340 ^
	-fomit-frame-pointer -nostdlib -fno-builtin -I%SDK_PATH% %INCLUDES% %DEFINES% %OPTIM% ^
	-c ..\src\2048.c -o 2048.o
%MCORE_PATH%\GCC_MCore\bin\mcore-elf-gcc -fshort-wchar -mbig-endian -nostdinc -m340 ^
	-fomit-frame-pointer -nostdlib -fno-builtin -I%SDK_PATH% %INCLUDES% %DEFINES% %OPTIM% ^
	-c %ELF_NAME%.c -o %ELF_NAME%.o

:: Linking step.
%MCORE_PATH%\GCC_MCore\bin\mcore-elf-ld -dn -r -no-bss-init -z muldefs ^
	2048.o %ELF_NAME%.o -T%MCORE_PATH%\GCC_MCore\mcore-elf\lib\linker_elf.ld -o %ELF_NAME%.elf
