Some information about Motorola ROKR E2
=======================================

See additional information in [doc/NotesMotoEZX.md](NotesMotoEZX.md) and [2048-EZX/ReadMe.md](../2048-EZX/ReadMe.md) document files.

## Telnet & Samba & FTP

Unpack [E2_Telnet_Samba_FTP.zip]() archive to the `/mmc/mmca1/` (memory card), reboot phone and choose "Telnet" in main menu. Connect phone via USB in the "Modem" mode to PC, determine modem COM port and send `AT+MODE=13` command to modem with using [PuTTY](https://www.putty.org/), Command Prompt `echo AT+MODE=13 > COM5`, or a similar program. Now you can use Samba file transfer on `\\192.168.16.2\` path in Explorer and can connect to the Motorola ROKR E2 via `telnet 192.168.16.2` command. Use the `bftpd.sh` script to start an FTP server and access files at `ftp://192.168.16.2` address. 

// TODO: Add proper link to the E2_Telnet_Samba_FTP.zip archive.

## System information

```sh
# cat /etc/ap_version.txt
R564_G_12.00.4AP

# mount
rootfs on / type rootfs (rw)
/dev/root on / type cramfs (rw)
none on /ram type ramfs (rw)
proc on /ram/proc type proc (rw)
/dev/roflash1 on /usr/language type cramfs (rw)
/dev/roflash2 on /usr/data_resource type cramfs (rw)
/dev/roflash3 on /usr/setup type cramfs (rw)
/dev/roflash4 on /usr/securesetup type cramfs (rw)
none on /dev/pts type devpts (rw)
/dev/mtdblock8 on /ezx_user type jffs2 (rw,noatime)
/dev/mtdblock9 on /ezxlocal type jffs2 (rw,noatime)
/dev/mmca1 on /mmc/mmca1 type vfat (rw,noatime)

# cat /proc/cmdline
root=3e00 rootfstype=cramfs ip=off paniclog=on

# cat /proc/cpuinfo
Processor       : Intel XScale-PXA27x rev 7 (v5l)
BogoMIPS        : 311.28
Features        : swp half thumb fastmult edsp
CPU implementor : 0x69
CPU architecture: 5TE
CPU variant     : 0x0
CPU part        : 0x411
CPU revision    : 7
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
Mem:  47374336 43900928  3473408        0   606208 23207936
Swap:        0        0        0
MemTotal:        46264 kB
MemFree:          3392 kB
MemShared:           0 kB
Buffers:           592 kB
Cached:          22664 kB
SwapCached:          0 kB
Active:          20372 kB
Inactive:        12296 kB
HighTotal:           0 kB
HighFree:            0 kB
LowTotal:        46264 kB
LowFree:          3392 kB
SwapTotal:           0 kB
SwapFree:            0 kB
Committed_AS:    40664 kB

# cat /proc/version
Linux version 2.4.20_mvlcee31-mainstone_pxa27x (BJDC@LINUX) (GCC 3.x for XSCALE) #1 Jan 1,2003

# cat /proc/fb
0
1

# cat /proc/iomem
a0000000-a0ffffff : System RAM
  a0019000-a01d5363 : Kernel code
  a01d5364-a025a083 : Kernel data
a1000000-a1ffffff : System RAM
ac000000-acffffff : System RAM

# cat /proc/mtd
dev:    size   erasesize  name
mtd0: 00008000 00008000 "CADDO_SECOND"
mtd1: 00008000 00008000 "ITUNES"
mtd2: 00008000 00008000 "CADDO_PRIMARY"
mtd3: 00008000 00008000 "FOTA_REV"
mtd4: 00040000 00020000 "MBM"
mtd5: 00020000 00020000 "CONFIG"
mtd6: 00020000 00020000 "BLOB"
mtd7: 00100000 00020000 "KERNEL"
mtd8: 00600000 00020000 "USERFS_DB"
mtd9: 00be0000 00020000 "USERFS_GENERAL"
mtd10: 00020000 00020000 "TEST_CMD"
mtd11: 00020000 00020000 "LOGO"
mtd12: 000c0000 00020000 "FOTA"
mtd13: 00020000 00020000 "RESERVE"

# cat /proc/partitions
major minor  #blocks  name

 243     0      60544 mmca
 243     1      60528 mmca1
  31     0         32 mtdblocka
  31     1         32 mtdblockb
  31     2         32 mtdblockc
  31     3         32 mtdblockd
  31     4        256 mtdblocke
  31     5        128 mtdblockf
  31     6        128 mtdblockg
  31     7       1024 mtdblockh
  31     8       6144 mtdblocki
  31     9      12160 mtdblockj
  31    10        128 mtdblockk
  31    11        128 mtdblockl
  31    12        768 mtdblockm
  31    13        128 mtdblockn

# cat /proc/roflash_info
ROFLASH Driver status: Ready

ROFLASH area name is rootfs
ROFLASH area size = 27258880 bytes
ROFLASH area offset = 6295552 bytes
ROFLASH area l_x_b(10)
ROFLASH area name is language
ROFLASH area size = 8388608 bytes
ROFLASH area offset = 31326208 bytes
ROFLASH area l_x_b(1000)
ROFLASH area name is data_resource
ROFLASH area size = 9437184 bytes
ROFLASH area offset = 1703936 bytes
ROFLASH area l_x_b(1000)
ROFLASH area name is setup
ROFLASH area size = 131072 bytes
ROFLASH area offset = 6160384 bytes
ROFLASH area l_x_b(10)
ROFLASH area name is secure_setup
ROFLASH area size = 126976 bytes
ROFLASH area offset = 30019584 bytes
ROFLASH area l_x_b(1000)
```
