:: This make.bat script was created by EXL, 17-Jan-2023.
:: Default platform is Motorola P2K, EM2 ElfPack M*CORE, mcore-elf-gcc (GCC) 3.4.6 on Windows.

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
set MCORE_PATH=C:\MCORE_EM2

:: SDK path.
set SDK_PATH=%MCORE_PATH%\SDK

:: Defines.
set DEFINES=-D__P2K__ -DEM2 -DUSE_MME

:: Includes.
set INCLUDES=-I..\src\ -I..\image\icon\precompiled\

:: Optimization.
set OPTIM=-O2

:: Project/ELF name.
set ELF_NAME=2048-UIS

:: Compiling step.
%MCORE_PATH%\bin\mcore-elf-gcc -fshort-wchar -funsigned-char -fomit-frame-pointer -fno-builtin ^
	-m340 -m4align -mbig-endian -nostdinc -nostdlib -I%SDK_PATH% %INCLUDES% %DEFINES% ^
	-c ..\src\2048.c -o 2048.o
%MCORE_PATH%\bin\mcore-elf-gcc -fshort-wchar -funsigned-char -fomit-frame-pointer -fno-builtin ^
	-m340 -m4align -mbig-endian -nostdinc -nostdlib -I%SDK_PATH% %INCLUDES% %DEFINES% ^
	-c %ELF_NAME%.c -o %ELF_NAME%.o

:: Linking step.
%MCORE_PATH%\bin\mcore-elf-ld -d -EB -N -r -s -Bstatic -Bsymbolic -Bsymbolic-functions ^
	--gc-sections -nostdinc -nostdlib --unresolved-symbols=report-all -z muldefs -z combreloc -z nodefaultlib ^
	2048.o %ELF_NAME%.o -T%MCORE_PATH%\mcore-elf\lib\linker_elf.ld -o %ELF_NAME%.elf
