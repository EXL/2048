:: This make.bat script was edited by EXL, 15-Jan-2023.
:: Default platform is Motorola P2K, ElfPack v2.x, devkitARM release 26 (GCC 4.4.0) on Windows.

:: Uncomment it for disable verbose output.
:: @echo off

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

:: Output names.
set ENG_NAME=2048
set ELF_NAME=2048-UIS
set FINAL_NAME=2048-P2K-UIS_EP2

:: Compiling step.
%ARM_PATH%\bin\arm-eabi-gcc -c -Wall -mbig-endian -mthumb -mthumb-interwork -nostdlib ^
	-fshort-wchar -fshort-enums -fpack-struct=4 -fno-builtin -fvisibility=hidden ^
	-I%SDK_PATH% %INCLUDES% %DEFINES% %OPTIM% ..\src\%ENG_NAME%.c -o %ENG_NAME%.o
%ARM_PATH%\bin\arm-eabi-gcc -c -Wall -mbig-endian -mthumb -mthumb-interwork -nostdlib ^
	-fshort-wchar -fshort-enums -fpack-struct=4 -fno-builtin -fvisibility=hidden ^
	-I%SDK_PATH% %INCLUDES% %DEFINES% %OPTIM% %ELF_NAME%.c -o %ELF_NAME%.o

:: HACK:
:: Highly intelligent GCC compiler optimizes struct arguments in variadic functions
:: using the explicit `memcpy()` call and this feature can't be disabled.
%ARM_PATH%\bin\arm-eabi-objcopy --redefine-sym memcpy=__rt_memcpy %ELF_NAME%.o

:: Linking step.
%ARM_PATH%\bin\arm-eabi-ld -pie -EB %OPTIM% -nostdlib %ENG_NAME%.o %ELF_NAME%.o ^
	%LIB_PATH%\%LIB_MAIN% %LIB_PATH%\%LIB_LIBC% -o %ELF_NAME%_p.elf

:: Post linking step.
%ARM_PATH%\libgen\postlink.exe %ELF_NAME%_p.elf -o %ELF_NAME%.elf

:: Renaming step.
move /y %ELF_NAME%.elf %FINAL_NAME%.elf

if /I "%1"=="clean" (
	del *.o
	del *.elf
)
