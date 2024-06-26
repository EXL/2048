2048-BREW
============

The "2048" puzzle game for the Qualcomm BREW platform written using AEE framework and implemented as native BREW-application.

*Motorola RAZR2 V9m Screenshots:*

![2048-BREW Motorola RAZR2 V9m Screenshot 1](../image/2048-BREW-V9m-Screenshot1.png) ![2048-BREW Motorola RAZR2 V9m Screenshot 2](../image/2048-BREW-V9m-Screenshot2.png) ![2048-BREW Motorola RAZR2 V9m Screenshot 3](../image/2048-BREW-V9m-Screenshot3.png) ![2048-BREW Motorola RAZR2 V9m Screenshot 4](../image/2048-BREW-V9m-Screenshot4.png)

## Toolchain & SDK

* [brew-cmake-toolchain](https://github.com/usernameak/brew-cmake-toolchain) by [@usernameak](https://github.com/usernameak/).

## Install Tools & Build & Run

Install BREW SDK first.

Windows recipe:

```bat
> cd 2048\2048-BREW\
> md build
> cd build
> cmake .. -DCMAKE_TOOLCHAIN_FILE=brew-cmake-toolchain\brew.cmake -DCMAKE_BUILD_TYPE=Release -G Ninja
> cmake --build . --clean-first --verbose
```

Linux recipe:

```bash
$ cd 2048/2048-BREW/
$ mkdir build
$ cd build
$ cmake .. -DCMAKE_TOOLCHAIN_FILE=brew-cmake-toolchain/brew.cmake -DCMAKE_BUILD_TYPE=Release -DUSE_SYSTEM_TOOLCHAIN=Yes -G Ninja
$ cmake --build . --clean-first --verbose
```

## Application structure

```
2048-BREW/
├── brew_2048              # Application directory.
│   ├── brew_2048.bar      # Data resource archive.
│   ├── brew_2048.mod      # Executable file.
│   └── brew_2048.sig      # Test signature.
└── brew_2048.mif          # Application manifest, parameters, and icons.
```

## Additional Stuff

The P2K/Synergy + BREW platform screenshots from Motorola RAZR V9m (Alltel carrier branded):

![P2K Motorola RAZR2 V9m Main Desktop Screen](../image/P2K-V9m-Screenshot1.png) ![P2K Motorola RAZR2 V9m Main Menu](../image/P2K-V9m-Screenshot2.png) ![P2K Motorola RAZR2 V9m Multimedia Menu](../image/P2K-V9m-Screenshot3.png) ![P2K Motorola RAZR2 V9m S/W Version](../image/P2K-V9m-Screenshot4.png)

Photos of 2048 game running on Motorola RAZR V9m (Alltel carrier branded):

![2048-BREW application running on Motorola RAZR V9m Photo](../image/2048-BREW-V9m-Photo.jpg)

## Icon Sizes

* 16x16: Small
* 26x26: Medium
* 65x42: Large

## Versions

```
$ arm-none-eabi-gcc --version
arm-none-eabi-gcc (15:10.3-2021.07-4) 10.3.1 20210621 (release)

arm-none-eabi-g++ --version
arm-none-eabi-g++ (15:10.3-2021.07-4) 10.3.1 20210621 (release)
```

## Information

* [Motorola CDMA: A840, E815, Е685, V710, V950, L7c, V3c, V3m, K1m, V9m, Z6c, Z6m, Z6tv](https://forum.motofan.ru/index.php?showforum=104): A section of the MotoFan.Ru forum dedicated to the Motorola CDMA phones.
