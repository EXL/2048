Motorola P2K Notes
==================

Developers from the MotoFan.Ru forum have made the possibility of running custom applications on Motorola P2K phones a reality with using ElfLoaders and ElfPacks. It became possible to run various ELF applications by applying several patches to the phone's firmware and increase its functionality. There are four versions of ElfPacks in total:

1. ElfPack v1.x: The first version, which contained some restrictions and used the ADS compiler to build ELF applications.
2. ElfPack v2.x: The second version, with support for shared libraries and process manager, GCC compiler was used to build ELF applications.
3. ElfPack v1.x M·CORE: The first version of ElfPack for phones that use [M·CORE](https://en.wikipedia.org/wiki/M%C2%B7CORE) microprocessor architecture instead of ARM.
4. ElfPack v2.x M·CORE: The second version of ElfPack for phones that use [M·CORE](https://en.wikipedia.org/wiki/M%C2%B7CORE) microprocessor architecture instead of ARM.

Installing ElfLoader and ElfPack on the phone is described in detail in the appropriate section on the forum:

* [ELFs development and porting](https://forum.motofan.ru/index.php?showforum=184).

## Icon resolution

* 96x65, 128x160 (Old P2K like C350, C350L, T720, T720i, T722i):
  * 15x15: GIF small, static.
  * 23x23: GIF big, static.
  * 23x23: GIF big, animation.

* 128x128, 128x160 (New P2K):
  * 15x15: GIF small, static.
  * 25x25: GIF big, static.
  * 29x29: GIF big, animation.

* 176x220 (Old P2K like A820, A830):
  * 15x15: GIF small, static.
  * 25x25: GIF big, static.
  * 25x25: GIF big, animation.

* 176x220 (New P2K):
  * 15x15: GIF small, static.
  * 33x33: GIF big, static.
  * 41x41: GIF big, animation.

* 240x320:
  * 19x19: GIF small, static.
  * 49x49: GIF big, static.
  * 57x57: GIF big, animation.
