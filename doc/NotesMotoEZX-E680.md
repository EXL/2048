Some information about Motorola E680
====================================

See additional information in [doc/NotesMotoEZX.md](NotesMotoEZX.md) and [2048-EZX/ReadMe.md](../2048-EZX/ReadMe.md) document files.

## Telnet & Samba

Install [Belcarra USBLAN for Windows]() drivers before. To activate Telnet and Samba on the Motorola E680, connect it via USB in modem mode, determine modem COM port and send `AT+MODE=99` command to modem with using [PuTTY](https://www.putty.org/) or a similar program. Now you can use Samba file transfer on `\\169.254.142.2\` path in Explorer and can connect to the Motorola E680 via `telnet 169.254.142.2` command.

// TODO: Add proper link to the Belcarra USBLAN for Windows.

## System information

```sh
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
```
