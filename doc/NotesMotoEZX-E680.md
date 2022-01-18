Some information about Motorola E680
====================================

See additional information in [doc/NotesMotoEZX.md](NotesMotoEZX.md) and [2048-EZX/ReadMe.md](../2048-EZX/ReadMe.md) document files.

## Telnet & Samba

Install [Belcarra USBLAN for Windows]() drivers before. To activate Telnet and Samba on the Motorola E680, connect it via USB in modem mode, determine modem COM port and send `AT+MODE=99` command to modem with using [PuTTY](https://www.putty.org/), Command Prompt `echo AT+MODE=99 > COM5`, or a similar program. Now you can use Samba file transfer on `\\169.254.142.2\` path in Explorer and can connect to the Motorola E680 via `telnet 169.254.142.2` command.

// TODO: Add proper link to the Belcarra USBLAN for Windows.

## System information

```sh
# cat /etc/ap_version.txt
R51_G_0F.51.A1P

# mount
rootfs on / type rootfs (rw)
/dev/root on / type cramfs (rw)
none on /ram type ramfs (rw)
proc on /ram/proc type proc (rw)
/dev/tffsa on /usr/language type cramfs (rw)
/dev/roflash2 on /usr/setup type cramfs (rw)
none on /dev/pts type devpts (rw)
/dev/mtdblock2 on /ezxlocal type vfm (rw,noatime)
/dev/tffsb1 on /diska type vfat (rw,noatime)

# cat /proc/cmdline
root=3e00 rootfstype=cramfs ip=off

# cat /proc/cpuinfo
Processor       : Intel XScale-Bulverde rev 4 (v5l)
BogoMIPS        : 291.63
Features        : swp half thumb fastmult edsp
CPU implementor : 0x69
CPU architecture: 5TE
CPU variant     : 0x0
CPU part        : 0x411
CPU revision    : 4
Cache type      : undefined 5
Cache clean     : undefined 5
Cache lockdown  : undefined 5
Cache unified   : harvard
I size          : 32768
I assoc         : 32
I line length   : 32
I sets          : 32
D size          : 32768
D assoc         : 32
D line length   : 32
D sets          : 32

Hardware        : Motorola Ezx Platform
Revision        : 0000
Serial          : 0000000000000000

# cat /proc/meminfo
        total:    used:    free:  shared: buffers:  cached:
Mem:  47734784 46616576  1118208        0  1970176 27783168
Swap:        0        0        0
MemTotal:        46616 kB
MemFree:          1092 kB
MemShared:           0 kB
Buffers:          1924 kB
Cached:          27132 kB
SwapCached:          0 kB
Active:           9848 kB
Inactive:        30636 kB
HighTotal:           0 kB
HighFree:            0 kB
LowTotal:        46616 kB
LowFree:          1092 kB
SwapTotal:           0 kB
SwapFree:            0 kB
Committed_AS:    55500 kB

# cat /proc/version
Linux version 2.4.20_mvlcee30-mainstone (BJDC@LINUX) (GCC 3.x for XSCALE) #1 Jan 1,2003

# cat /proc/fb
0 PXA
1 overlay1
2 overlay2
3 cursor

# cat /proc/iomem
08000000-08007fff : TrueFFS Device
a0000000-a0ffffff : System RAM
  a001b000-a017ea2b : Kernel code
  a017ea2c-a0204703 : Kernel data
a1000000-a1ffffff : System RAM
ac000000-acffffff : System RAM
d12d2000-d12d2003 : midi

# cat /proc/mtd
dev:    size   erasesize  name
mtd0: 00020000 00008000 "Bootloader"
mtd1: 000e0000 00020000 "Kernel"
mtd2: 00580000 00020000 "VFM_Filesystem"
mtd3: 00020000 00020000 "Logo"

# cat /proc/partitions
major minor  #blocks  name

 100     0      12288 tffsa
 100     8      49152 tffsb
 100     9      49148 tffsb1
  31     0        256 mtdblocka
  31     1       1792 mtdblockb
  31     2      11264 mtdblockc
  31     3        256 mtdblockd

# cat /proc/roflash_info
ROFLASH Driver status: Ready

ROFLASH area name is rootfs
ROFLASH area size = 26083328 bytes
ROFLASH area offset = 1179648 bytes
ROFLASH area l_x_b(10)
ROFLASH area name is NO-USE
ROFLASH area size = 0 bytes
ROFLASH area offset = 27262976 bytes
ROFLASH area l_x_b(1000)
ROFLASH area name is setup
ROFLASH area size = 131072 bytes
ROFLASH area offset = 33161216 bytes
ROFLASH area l_x_b(1000)
```
