2048-P2K-UIS
============

The "2048" puzzle game for the Motorola P2K platform written using AFW and UIS frameworks and implemented as ELF-application.

*Motorola SLVR L6 Screenshots:*

![2048-UIS Motorola SLVR L6 Screenshot 1](../image/2048-P2K-L6-Screenshot1.png) ![2048-UIS Motorola SLVR L6 Screenshot 2](../image/2048-P2K-L6-Screenshot2.png) ![2048-UIS Motorola SLVR L6 Screenshot 3](../image/2048-P2K-L6-Screenshot3.png) ![2048-UIS Motorola SLVR L6 Screenshot 4](../image/2048-P2K-L6-Screenshot4.png) ![2048-UIS Motorola SLVR L6 Screenshot 5](../image/2048-P2K-L6-Screenshot5.png)

![2048-UIS Motorola SLVR L6 Screenshot 6](../image/2048-P2K-L6-Screenshot6.png) ![2048-UIS Motorola SLVR L6 Screenshot 7](../image/2048-P2K-L6-Screenshot7.png) ![2048-UIS Motorola SLVR L6 Screenshot 8](../image/2048-P2K-L6-Screenshot8.png) ![2048-UIS Motorola SLVR L6 Screenshot 9](../image/2048-P2K-L6-Screenshot9.png) ![2048-UIS Motorola SLVR L6 Screenshot 10](../image/2048-P2K-L6-Screenshot10.png)

![2048-UIS Motorola SLVR L6 Screenshot 11](../image/2048-P2K-L6-Screenshot11.png) ![2048-UIS Motorola SLVR L6 Screenshot 12](../image/2048-P2K-L6-Screenshot12.png) ![2048-UIS Motorola SLVR L6 Screenshot 13](../image/2048-P2K-L6-Screenshot13.png) ![2048-UIS Motorola SLVR L6 Screenshot 14](../image/2048-P2K-L6-Screenshot14.png) ![2048-UIS Motorola SLVR L6 Screenshot 15](../image/2048-P2K-L6-Screenshot15.png)

*Motorola ROKR E1 Screenshots:*

![2048-UIS Motorola ROKR E1 Screenshot 1](../image/2048-P2K-E1-Screenshot1.png) ![2048-UIS Motorola ROKR E1 Screenshot 2](../image/2048-P2K-E1-Screenshot2.png) ![2048-UIS Motorola ROKR E1 Screenshot 3](../image/2048-P2K-E1-Screenshot3.png) ![2048-UIS Motorola ROKR E1 Screenshot 4](../image/2048-P2K-E1-Screenshot4.png) ![2048-UIS Motorola ROKR E1 Screenshot 5](../image/2048-P2K-E1-Screenshot5.png)

![2048-UIS Motorola ROKR E1 Screenshot 6](../image/2048-P2K-E1-Screenshot6.png) ![2048-UIS Motorola ROKR E1 Screenshot 7](../image/2048-P2K-E1-Screenshot7.png) ![2048-UIS Motorola ROKR E1 Screenshot 8](../image/2048-P2K-E1-Screenshot8.png) ![2048-UIS Motorola ROKR E1 Screenshot 9](../image/2048-P2K-E1-Screenshot9.png) ![2048-UIS Motorola ROKR E1 Screenshot 10](../image/2048-P2K-E1-Screenshot10.png)

![2048-UIS Motorola ROKR E1 Screenshot 11](../image/2048-P2K-E1-Screenshot11.png) ![2048-UIS Motorola ROKR E1 Screenshot 12](../image/2048-P2K-E1-Screenshot12.png) ![2048-UIS Motorola ROKR E1 Screenshot 13](../image/2048-P2K-E1-Screenshot13.png) ![2048-UIS Motorola ROKR E1 Screenshot 14](../image/2048-P2K-E1-Screenshot14.png) ![2048-UIS Motorola ROKR E1 Screenshot 15](../image/2048-P2K-E1-Screenshot15.png)

The ability to run ELF applications on Motorola phones was implemented by enthusiasts of the MotoFan.Ru forum: Andy51, Vilko, tim_apple, G-XaD, om2804, kadukmm, baat, z3DD3r, Chik_v, fkoder, DmT, motoprogger, etc.

## Toolchain & SDK

* ElfPack v1.x Windows ELFKIT download link. // TODO:
* ElfPack v1.x Linux ELFKIT download link. // TODO:
* ElfPack v2.x Windows ELFKIT download link. // TODO:
* ElfPack M*CORE Windows ELFKIT download link. // TODO:

## Install Tools & Build & Run

Windows recipe:

```bat
> cd 2048\2048-P2K\
> make_ep1.bat clean
> make_ep1.bat
> make_ep2.bat clean
> make_ep2.bat
> make_epmcore.bat clean
> make_epmcore.bat
```

Linux recipe (ElfPack 1.x build only):

```bash
$ cd 2048/2048-P2K/
$ make clean
$ make
```

The ELF-application has been tested on the following phones and firmware:

* Motorola SLVR L6: R3443H1_G_0A.65.0BR
* Motorola ROKR E1: R373_G_0E.30.49R

Application type: GUI.

## Additional Stuff

The P2K OS screenshots from Motorola SLVR L6:

![P2K Motorola L6 Screenshot 1 Main Desktop Screen](../image/P2K-L6-Screenshot1.png) ![P2K Motorola L6 Screenshot 2 Main Menu](../image/P2K-L6-Screenshot2.png) ![P2K Motorola L6 Screenshot 3 Multimedia Menu](../image/P2K-L6-Screenshot3.png) ![P2K Motorola L6 Screenshot 4 S/W Version](../image/P2K-L6-Screenshot4.png) ![P2K Motorola L6 Screenshot 5 Flex Version](../image/P2K-L6-Screenshot5.png)

![P2K Motorola L6 Screenshot 6 Main Desktop Screen](../image/P2K-L6-Screenshot6.png) ![P2K Motorola L6 Screenshot 7 Main Menu](../image/P2K-L6-Screenshot7.png) ![P2K Motorola L6 Screenshot 8 Multimedia Menu](../image/P2K-L6-Screenshot8.png) ![P2K Motorola L6 Screenshot 9 S/W Version](../image/P2K-L6-Screenshot9.png) ![P2K Motorola L6 Screenshot 10 Flex Version](../image/P2K-L6-Screenshot10.png)

![P2K Motorola L6 Screenshot 11 Main Desktop Screen](../image/P2K-L6-Screenshot11.png) ![P2K Motorola L6 Screenshot 12 Main Menu](../image/P2K-L6-Screenshot12.png) ![P2K Motorola L6 Screenshot 13 Multimedia Menu](../image/P2K-L6-Screenshot13.png) ![P2K Motorola L6 Screenshot 14 S/W Version](../image/P2K-L6-Screenshot14.png) ![P2K Motorola L6 Screenshot 15 Flex Version](../image/P2K-L6-Screenshot15.png)

The P2K OS screenshots from Motorola ROKR E1:

![P2K Motorola E1 Screenshot 1 Main Desktop Screen](../image/P2K-E1-Screenshot1.png) ![P2K Motorola E1 Screenshot 2 Main Menu](../image/P2K-E1-Screenshot2.png) ![P2K Motorola E1 Screenshot 3 Multimedia Menu](../image/P2K-E1-Screenshot3.png) ![P2K Motorola E1 Screenshot 4 S/W Version](../image/P2K-E1-Screenshot4.png) ![P2K Motorola E1 Screenshot 5 Flex Version](../image/P2K-E1-Screenshot5.png)

![P2K Motorola E1 Screenshot 6 Main Desktop Screen](../image/P2K-E1-Screenshot6.png) ![P2K Motorola E1 Screenshot 7 Main Menu](../image/P2K-E1-Screenshot7.png) ![P2K Motorola E1 Screenshot 8 Multimedia Menu](../image/P2K-E1-Screenshot8.png) ![P2K Motorola E1 Screenshot 9 S/W Version](../image/P2K-E1-Screenshot9.png) ![P2K Motorola E1 Screenshot 10 Flex Version](../image/P2K-E1-Screenshot10.png)

![P2K Motorola E1 Screenshot 11 Main Desktop Screen](../image/P2K-E1-Screenshot11.png) ![P2K Motorola E1 Screenshot 12 Main Menu](../image/P2K-E1-Screenshot12.png) ![P2K Motorola E1 Screenshot 13 Multimedia Menu](../image/P2K-E1-Screenshot13.png) ![P2K Motorola E1 Screenshot 14 S/W Version](../image/P2K-E1-Screenshot14.png) ![P2K Motorola E1 Screenshot 15 Flex Version](../image/P2K-E1-Screenshot15.png)

The 2048 game running on Motorola SLVR L6 and Motorola ROKR E1:

TODO: Photos.

## Versions

ElfPack v1.x Tools:

```bat
> tcc
Thumb C Compiler, ADS1.2 [Build 848]
> armcc
ARM C Compiler, ADS1.2 [Build 848]
> tcpp
Thumb C++ Compiler, ADS1.2 [Build 848]
> armcpp
ARM C++ Compiler, ADS1.2 [Build 848]
> armlink
ARM Linker, ADS1.2 [Build 848]
```

ElfPack v2.x Tools:

```bat
> arm-eabi-gcc -v
Target: arm-eabi
Configured with: ../../gcc-4.4.0/configure --enable-languages=c,c++,objc --with-cpu=arm7tdmi --enable-interwork --enable-multilib --with-gcc --with-gnu-ld --with-gnu-as --disable-shared --disable-threads --disable-win32-registry --disable-nls --disable-debug --disable-libmudflap --disable-libssp --disable-libgomp --disable-libstdcxx-pch --target=arm-eabi --with-newlib --prefix=c:/devkitPro/devkitARM --with-bugurl=http://wiki.devkitpro.org/index.php/Bug_Reports --with-pkgversion='devkitARM release 26'
Thread model: single
gcc version 4.4.0 (devkitARM release 26)
> arm-eabi-g++ -v
Target: arm-eabi
Configured with: ../../gcc-4.4.0/configure --enable-languages=c,c++,objc --with-cpu=arm7tdmi --enable-interwork --enable-multilib --with-gcc --with-gnu-ld --with-gnu-as --disable-shared --disable-threads --disable-win32-registry --disable-nls --disable-debug --disable-libmudflap --disable-libssp --disable-libgomp --disable-libstdcxx-pch --target=arm-eabi --with-newlib --prefix=c:/devkitPro/devkitARM --with-bugurl=http://wiki.devkitpro.org/index.php/Bug_Reports --with-pkgversion='devkitARM release 26'
Thread model: single
gcc version 4.4.0 (devkitARM release 26)
> arm-eabi-ld -V
GNU ld (GNU Binutils) 2.19.1
  Supported emulations:
   armelf
```

ElfPack M*CORE Tools:

```bat
> mcore-elf-gcc -v
Configured with: /usr/local/src/gnu/gcc-3.4.6/configure --target=mcore-elf --host=i686-pc-cygwin --build=i686-pc-cygwin
Thread model: single
gcc version 3.4.6
> mcore-elf-g++ -v
Configured with: /usr/local/src/gnu/gcc-3.4.6/configure --target=mcore-elf --host=i686-pc-cygwin --build=i686-pc-cygwin
Thread model: single
gcc version 3.4.6
> mcore-elf-ld -V
GNU ld (GNU Binutils) 2.18.50.20080711
  Supported emulations:
   elf32mcore
```

## Information

* [NotesMotoP2K.md](../doc/NotesMotoP2K.md): Document contains additional information about ElfPacks on Motorola P2K phones.
* [ELFs development and porting](https://forum.motofan.ru/index.php?showforum=184): A section of the MotoFan.Ru forum dedicated to the development and porting of ELFs.
* [ElfPack 1.x](https://wiki.motofan.ru/ElfPack): Page on MotoWiki site about first version of ElfPack for Motorola P2K phones.
* [ElfPack 2.x](https://wiki.motofan.ru/ElfPack2): Page on MotoWiki site about second version of ElfPack for Motorola P2K phones.
* [ElfPack M*CORE](https://forum.motofan.ru/index.php?showtopic=176195): A thread on the MotoFan.Ru forum dedicated to the development and porting of ELFs to M*CORE architecture and Rainbow POG platform.
