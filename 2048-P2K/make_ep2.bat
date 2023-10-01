:: This make.bat script was created by EXL, 15-Jan-2023.
:: Default platform is Motorola P2K, ElfPack v2.x, devkitARM release 26 (GCC 4.4.0) on Windows.

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
set ARM_PATH=C:\devkitARM

:: SDK path.
set SDK_PATH=%ARM_PATH%\SDK

:: Libraries path.
set LIB_PATH=%ARM_PATH%\lib

:: Main link library.
set LIB_MAIN=std.sa

:: Libc link library.
set LIB_LIBC=libc.a

:: Defines.
set DEFINES=-D__P2K__ -DEP2 -DUSE_MME
:: set DEFINES=-D__P2K__ -DEP2 -DUSE_MME -DFTR_L7E

:: Includes.
set INCLUDES=-I..\src\ -I..\image\icon\precompiled\

:: Optimization.
set OPTIM=-O2

:: Project/ELF name.
set ELF_NAME=2048-UIS

:: Compiling step.
%ARM_PATH%\bin\arm-eabi-gcc -c -Wall -mbig-endian -mthumb -mthumb-interwork -nostdlib ^
	-fshort-wchar -fshort-enums -fpack-struct=4 -fno-builtin -fvisibility=hidden ^
	-I%SDK_PATH% %INCLUDES% %DEFINES% %OPTIM% ..\src\2048.c -o 2048.o
%ARM_PATH%\bin\arm-eabi-gcc -c -Wall -mbig-endian -mthumb -mthumb-interwork -nostdlib ^
	-fshort-wchar -fshort-enums -fpack-struct=4 -fno-builtin -fvisibility=hidden ^
	-I%SDK_PATH% %INCLUDES% %DEFINES% %OPTIM% %ELF_NAME%.c -o %ELF_NAME%.o

:: HACK:
:: Highly intelligent GCC compiler optimizes struct arguments in variadic functions
:: using the explicit `memcpy()` call and this feature can't be disabled.
%ARM_PATH%\bin\arm-eabi-objcopy --redefine-sym memcpy=__rt_memcpy %ELF_NAME%.o

:: Linking step.
%ARM_PATH%\bin\arm-eabi-ld -pie -EB %OPTIM% -nostdlib 2048.o %ELF_NAME%.o ^
	%LIB_PATH%\%LIB_MAIN% %LIB_PATH%\%LIB_LIBC% -o %ELF_NAME%.elfp

:: Post linking step.
%ARM_PATH%\libgen\postlink.exe %ELF_NAME%.elfp -o %ELF_NAME%.elf
