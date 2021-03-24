https://en.wikipedia.org/wiki/Fork_(file_system)
https://en.wikipedia.org/wiki/Resource_fork

(limitations)

https://github.com/steventroughtonsmith/BitPaint/


2048-Carbon
===========

The "2048" game for the [classic Mac OS](https://en.wikipedia.org/wiki/Classic_Mac_OS) (System 7-9) and early [Mac OS X](https://en.wikipedia.org/wiki/MacOS) (10.0-10.6.8) platforms based on [PowerPC](https://en.wikipedia.org/wiki/PowerPC) architecture with using [Carbon API](https://en.wikipedia.org/wiki/Carbon_(API)) which using under the hood [Macintosh Toolbox](https://en.wikipedia.org/wiki/Macintosh_Toolbox) and [QuickDraw](https://en.wikipedia.org/wiki/QuickDraw) technologies.

*Note.* The [QuickDraw GX](https://en.wikipedia.org/wiki/QuickDraw_GX) 2D graphics engine [isn't supported](http://mirror.informatimago.com/next/developer.apple.com/documentation/Carbon/Reference/Carbon_Spec_Porting/QuickDraw_GX.html) in Carbon API.

## Setup Sheep Shaver Development Environment

1. Install [Mac OS 9.0](https://winworldpc.com/product/mac-os-9/90) into [Sheep Shaver](https://en.wikipedia.org/wiki/SheepShaver) emulator through [Sheep Shaver Setup](https://www.emaculation.com/doku.php/sheepshaver_setup) installation guide.

    *Note.* If you are using Linux, please disable SELinux for the current session and run Sheep Shaver from root to rid off "Cannot map Low Memory Globals: Operation not permitted." Sheep Shaver error.

    ```bash
    sudo setenforce 0
    sudo SheepShaver
    ```

2. Install [CodeWarrior Pro 8](https://macintoshgarden.org/apps/codewarrior-pro-8x) Tools and IDE which requires at least 1 GB for installation.

    Be sure to read the "Installation Notes" from "CW Tools 8.0" CD disk before run "Install CodeWarrior 8.0" program.

    1. Go to the "CW Tools 8.0:System Folder Items:For Classic Mac OS Development:INTO System Folder" directory.
    2. Copy the "MacsBugs" program to the "Mac OS 9:System Folder" directory by drag and drop.
    3. Copy all other files from CD to their respective system directories in the same way.
    4. Reboot machine and now you can run "Install CodeWarrior 8.0" program without these errors:

    ```
    Illegal instruction at 40810000, opcode = 4cdf1808
    Illegal instruction at 40810004, opcode = 4e7591c8
    Illegal instruction at 40810018, opcode = 00184a42
    Illegal instruction at 40810024, opcode = 00000000
    Illegal instruction at 40810028, opcode = 00000000
    Illegal instruction at 4081002c, opcode = 00000000
    Illegal instruction at 40810030, opcode = 4e56ffe0
    Segmentation fault
    ```

    *Note.* The "Mac OS 9" is name of storage drive with installed Mac OS 9.

3. Install [ResEdit 2.1.3](https://macintoshgarden.org/apps/resedit) by Apple.

## Building CFM/PEF executable using Metrowerks CodeWarrior IDE

1. Attach "TODO" floppy disk image on "Volumes" tab in the Basilisk II emulator and start Mac OS 8.1 with it.
2. Copy "2048-MCW" folder from floppy disk to the storage drive.
3. Open "2048-MCW:2048-MCW.μ" project file with Metrowerks CodeWarrior IDE.
4. Set "FAT MacOS Toolbox" instead of "68K Debug MacOS Toolbox" target.
5. In the main menu choose "Project" => "Make", wait for the compilation process to complete.
6. Get resulted executable files in the "2048-MCW" directory with following names:

   - **2048-MCW 68K** - Final (release) version for [Motorola 68000](https://en.wikipedia.org/wiki/Motorola_68000) architecture.
   - **2048-MCW PPC** - Final (release) version for [PowerPC](https://en.wikipedia.org/wiki/PowerPC) architecture.
   - **2048-MCW** - Final (release) FAT version for both architectures.

## Building using Metrowerks CodeWarrior MPW

*Note.* This instructions aren't recommended, use CodeWarrior IDE instead.

Please use Metrowerks CodeWarrior MPW instead of vanilla [Macintosh Programmer's Workshop](https://en.wikipedia.org/wiki/Macintosh_Programmer%27s_Workshop) by Apple.

### Configure CodeWarrior MPW

1. Go to the "CodeWarrior Pro 4:CodeWarrior MPW:MPW:" directory, open "MW Read Me" file and read it.
2. Go to the "CodeWarrior Pro 4:CodeWarrior MPW:MPW:Scripts" directory, open "CW_Max_Dup_Update" script in the MPW Shell.
3. Select all text by `Command + A` then push `Command + Enter` to execute selected script lines.
4. In the file dialog that opens, select "CodeWarrior Pro 4:Metrowerks CodeWarrior" directory but not open it, then click "Directory" button.
5. The script will generate many `Duplicate` commands, click "OK" button, then select all these commands by using `Shift + Arrows` keys.
6. Push `Command + Enter` to execute all `Dublicate` commands, press "No" button when dialog appears.
7. When copying is completed the mouse cursor becomes normal. Now exit "MPW Shell" using `Command + Q` or select "File" => "Quit" in the main menu, then click "Don't Save" button.

### Build and Run

#### 1st way

1. Go to the "2048-MCW" directory, open "Makefile" using MPW Shell by double click on it.
2. Push `Command + B` or select "Build" => "Build..." in the main menu.
3. Type "2048-MCW" without double quotes in the "Program Name?" window and click "OK" button.
4. Wait for the compilation process and push `Command + Enter` to run application.

#### 2nd way

1. Go to the "CodeWarrior Pro 4:CodeWarrior MPW:MPW" directory and run "MPW Shell" program.
2. Type and execute by `Command + Enter` following commands for building application:

    ```
    Directory "Mac OS 8.1:2048-MCW"
    Files
    BuildProgram "2048-MCW"
    ```
    *Note.* "Mac OS 8.1" is name of storage drive.

3. Push `Command + Enter` to run application.

## Additional Information

The old Apple Developer site had some interesting publications in the [develop Articles on QuickDraw GX](http://web.archive.org/web/20041012004904/http://developer.apple.com/dev/techsupport/develop/bysubject/quickdrawgx.html) section about QuickDraw GX rendering, e.g. useful [Flicker-Free Drawing With QuickDraw GX](http://web.archive.org/web/20041029052644/http://developer.apple.com/dev/techsupport/develop/issue25/ayala.html) article.

This repository contains the source files with the Unix **LR** [line breaks](https://en.wikipedia.org/wiki/Newline) for convenience. Don't forget to change line breaks to **CR**, which are used in classic macOS. This can be easily done using the `unix2mac` utility which is included in the "dos2unix" package.

```sh
unix2mac 2048.c
unix2mac 2048.h
unix2mac 2048-MCW.cp
unix2mac 2048-MCW.r
unix2mac Makefile
unix2mac ReadMe.md
```

The reverse process can be done with `mac2unix` utility.

See [NotesClassicMacOS.md](../../doc/NotesClassicMacOS.md) document for some additional information.

## Classic Mac OS Development Environment

Metrowerks CodeWarrior IDE 3.2 (part of Metrowerks CodeWarrior Pro 4 distribution):

![Metrowerks CodeWarrior IDE application, classic Mac OS 8.1 Screenshot 1](../../image/MCW-MacOS-8_1-Screenshot_1.png)

![Metrowerks CodeWarrior IDE application, classic Mac OS 8.1 Screenshot 2](../../image/MCW-MacOS-8_1-Screenshot_2.png)

Apple MPW 3.4.2:

![Apple MPW, Metrowerks CodeWarrior MPW programming shell, classic Mac OS 8.1 Screenshot](../../image/MPW-MacOS-8_1-Screenshot.png)

## Versions

1. [Basilisk II 1.0](https://github.com/cebix/macemu)
2. [Apple Mac OS 8.1](https://winworldpc.com/download/7724c394-e280-9362-c382-11c3a6e28094)
3. [Metrowerks CodeWarrior Pro 4](https://macintoshgarden.org/sites/macintoshgarden.org/files/apps/CWPro4Tools.cdr_.zip) (with Metrowerks CodeWarrior IDE version 3.2 build 0158)
4. [Apple ResEdit 2.1.3](https://en.wikipedia.org/wiki/ResEdit)
5. [Apple MPW 3.4.2](https://en.wikipedia.org/wiki/Macintosh_Programmer%27s_Workshop) (with Metrowerks CodeWarrior MPW extensions and tools)

## Additional Screenshots

The 2048-MCW application running on Mac OS System 6.0.8.1 with a different number of colors:

| "256" Colors | "Thousands" Colors | "Millions" Colors |
|--------------|--------------------|-------------------|
| ![2048-MCW Classic Mac OS System 6.0.8.1 + 32-bit QuickDraw + "256" Colors Screenshot](../../image/2048-MCW-MacOS-6-QD-256-Screenshot-7.png) | ![2048-MCW Classic Mac OS System 6.0.8.1 + 32-bit QuickDraw + "Thousands" Colors Screenshot](../../image/2048-MCW-MacOS-6-QD-Thousands-Screenshot-8.png) | ![2048-MCW Classic Mac OS System 6.0.8.1 + 32-bit QuickDraw + "Millions" Colors Screenshot](../../image/2048-MCW-MacOS-6-QD-Millions-Screenshot-9.png) |
