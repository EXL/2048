:: This make.bat script was edited by EXL, 17-Jan-2023.
:: Default platform is Motorola P2K, EM2 ElfPack M*CORE, mcore-elf-gcc (GCC) 3.4.6 on Windows.

:: Uncomment it for disable verbose output.
:: @echo off

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

:: Output names.
set ENG_NAME=2048
set ELF_NAME=2048-UIS
set FINAL_NAME=2048-P2K-UIS_EM2

:: Compiling step.
%MCORE_PATH%\bin\mcore-elf-gcc -fshort-wchar -funsigned-char -fomit-frame-pointer -fno-builtin ^
	-m340 -m4align -mbig-endian -nostdinc -nostdlib -I%SDK_PATH% %INCLUDES% %DEFINES% ^
	-c ..\src\%ENG_NAME%.c -o %ENG_NAME%.o
%MCORE_PATH%\bin\mcore-elf-gcc -fshort-wchar -funsigned-char -fomit-frame-pointer -fno-builtin ^
	-m340 -m4align -mbig-endian -nostdinc -nostdlib -I%SDK_PATH% %INCLUDES% %DEFINES% ^
	-c %ELF_NAME%.c -o %ELF_NAME%.o

:: Linking step.
%MCORE_PATH%\bin\mcore-elf-ld -d -EB -N -r -s -Bstatic -Bsymbolic -Bsymbolic-functions ^
	--gc-sections -nostdinc -nostdlib --unresolved-symbols=report-all -z muldefs -z combreloc -z nodefaultlib ^
	%ENG_NAME%.o %ELF_NAME%.o -T%MCORE_PATH%\mcore-elf\lib\linker_elf.ld -o %ELF_NAME%.elf

:: Renaming step.
move /y %ELF_NAME%.elf %FINAL_NAME%.elf

if /I "%1"=="clean" (
	del *.o
	del *.elf
)
