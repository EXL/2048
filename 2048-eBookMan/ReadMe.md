2048-eBookMan
=============

The [Franklin eBookMan](https://en.wikipedia.org/wiki/Franklin_eBookMan) is a discontinued handheld device made to read ebooks. This gadget, made from 1999 until 2002, has standard PDA functions and can play MP3 and record sounds. It has a black on green touchscreen, contains 8 or 16 MB of RAM, and uses its own proprietary eBookMan OS. Its handwriting recognition system accepts nearly natural handwriting.

![2048-eBookMan Screenshot 1](../image/2048-eBookMan-ScreenshotP1.png) ![2048-eBookMan Screenshot 2](../image/2048-eBookMan-ScreenshotP2.png) ![2048-eBookMan Screenshot 3](../image/2048-eBookMan-ScreenshotP3.png)

![2048-eBookMan Screenshot 4](../image/2048-eBookMan-ScreenshotP4.png) ![2048-eBookMan Screenshot 5](../image/2048-eBookMan-ScreenshotP5.png) ![2048-eBookMan Screenshot 6](../image/2048-eBookMan-ScreenshotP6.png)


The device uses a unique RISC architecture on CPU/MCU side called Sneak32 (Snk32), about which there is very little information available on the Internet. The Sneak32 CPU is a proprietary 32-bit CPU developed by Franklin, and based on Franklin's earlier 24-bit CPU called Sneak8 (and sometimes, Sneak24).

![2048-eBookMan Screenshot Landscape 1](../image/2048-eBookMan-ScreenshotL1.png) ![2048-eBookMan Screenshot Landscape 2](../image/2048-eBookMan-ScreenshotL2.png) ![2048-eBookMan Screenshot Landscape 3](../image/2048-eBookMan-ScreenshotL3.png)

![2048-eBookMan Screenshot Landscape 4](../image/2048-eBookMan-ScreenshotL4.png) ![2048-eBookMan Screenshot Landscape 5](../image/2048-eBookMan-ScreenshotL5.png) ![2048-eBookMan Screenshot Landscape 6](../image/2048-eBookMan-ScreenshotL6.png)

## Build SEB Package

Download building tools from copy of the official [Franklin Developer site](https://web.archive.org/web/20030104060658/http://download.franklin.com/franklin/ebookman/developer/) on WebArchive and install them using Installing guide: 

* [Cygwin 1.1.2](https://web.archive.org/web/20030104060658/http://download.franklin.com/franklin/ebookman/publisher/cygwin-1.1.2.exe)
* [SDK Tools for Windows/Cygwin 020419](https://web.archive.org/web/20030104060658/http://download.franklin.com/franklin/ebookman/developer/ebsdk_tool_cyg_020419.tgz)
* [INSTALL.020419](https://web.archive.org/web/20030104060658/http://download.franklin.com/franklin/ebookman/developer/INSTALL.020419)

Run *Cygwin Bash Shell* and execute following commands:

```sh
cd 2048/2048-eBookMan
make clean
make
make seb
```

## Gallery

eBookMan OS 020419: [[Download]](https://web.archive.org/web/20030104060658/http://download.franklin.com/franklin/ebookman/developer/ebsdk_ebm_020419.tgz)

![eBookMan OS Screenshot 1](../image/eBookMan-OS-Screenshot1.png) ![eBookMan OS Screenshot 2](../image/eBookMan-OS-Screenshot2.png) ![eBookMan OS Screenshot 3](../image/eBookMan-OS-Screenshot3.png)

// eBookMan Photos

![Hardware Photo 1](../image/hw/Franklin-eBookMan-EBM-911_HW_Photo1.jpg) ![Hardware Photo 1](../image/hw/Franklin-eBookMan-EBM-911_HW_Photo2.jpg)
*Note: Thanks to SHBEN.*

## Versions

```sh
$ /franklin/SDK/winXX/bin/sneak32-g++ -v
Reading specs from /franklin/SDK/winXX/lib/gcc-lib/sneak32/2.95.2/specs
gcc version 2.95.2 19991024 (release)

$ /franklin/SDK/winXX/bin/sneak32-gcc -v
Reading specs from /franklin/SDK/winXX/lib/gcc-lib/sneak32/2.95.2/specs
gcc version 2.95.2 19991024 (release)
```

## Thanks

* amix (@amix307)
* SHBEN (@SHU8IT)

## Archive Links

* [Franklin eBookMan® SDK Download Library](https://web.archive.org/web/20030104060658/http://download.franklin.com/franklin/ebookman/developer/)
* [FAQ for the Franklin eBookMan® SDK](https://web.archive.org/web/20030206183611/http://download.franklin.com/franklin/ebookman/developer/sdkfaq.html)
* [Software Development Kit Documentation](https://web.archive.org/web/20051120134937/http://download.franklin.com/franklin/ebookman/developer/doc/index.html)

    Note: It's better to use the one version that comes with the SDK. It's more up-to-date.

* [Bookman Archive](https://bookmanarchive.com/)
* [eBookman SDK release 2002-04-19](https://archive.org/details/eBookMan-sdk-020419)
* [github.com/bookmanarchive](https://github.com/bookmanarchive)
* [r/franklinbookman](https://www.reddit.com/r/franklinbookman/)
* [The worst thing that ever happened to the PDA](https://www.pvsm.ru/news/383236) (in Russian)
