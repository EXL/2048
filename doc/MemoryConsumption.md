Memory Consumption on Various Platform
======================================

Information were obtained:

1. By using `cat /proc/$PID/status` command on Fedora, MotoMAGX, and EZX platform.
2. By using `top` command and "System Monitor" application on Serenity OS.
3. By using `showmem -P $PID` command on QNX.
4. By using `ps aux` command on NeXTSTEP.
5. By using `ps aux` and `top` commands on Mac OS X.
6. In the "Apple Menu" => "About This Computer..." monitor on classic Mac OS and A/UX.
7. By using "TaskMan" (UID: 0x101F9D66) program from SymbianWare on Symbian UIQ2 platform.

*Note: `$PID` is Process Identifier of the executable file.*

### 2048-QtQuick

GNOME System Monitor: 21.6 MiB

```
cat /proc/`pidof 2048-QtQuick`/status
...
VmPeak:  1344916 kB
VmSize:  1280392 kB
VmLck:         0 kB
VmPin:         0 kB
VmHWM:     77492 kB
VmRSS:     76776 kB
RssAnon:   22152 kB
RssFile:   54108 kB
RssShmem:    516 kB
VmData:   145240 kB
VmStk:       136 kB
VmExe:        20 kB
VmLib:     52648 kB
VmPTE:       408 kB
VmSwap:        0 kB
HugetlbPages:  0 kB
```

### 2048-Qt5

GNOME System Monitor: 9.8 MiB

```
cat /proc/`pidof 2048-Qt5`/status
...
VmPeak:  1063488 kB
VmSize:  1002036 kB
VmLck:         0 kB
VmPin:         0 kB
VmHWM:     50984 kB
VmRSS:     50984 kB
RssAnon:   10036 kB
RssFile:   40412 kB
RssShmem:    536 kB
VmData:    84656 kB
VmStk:       132 kB
VmExe:        20 kB
VmLib:     42540 kB
VmPTE:       328 kB
VmSwap:        0 kB
HugetlbPages:  0 kB
```

### 2048-Qt4

GNOME System Monitor: 3.0 MiB

```
cat /proc/`pidof 2048-Qt4`/status
...
VmPeak:   289748 kB
VmSize:   289748 kB
VmLck:         0 kB
VmPin:         0 kB
VmHWM:     25204 kB
VmRSS:     25204 kB
RssAnon:    3080 kB
RssFile:   21592 kB
RssShmem:    532 kB
VmData:     2556 kB
VmStk:       132 kB
VmExe:        20 kB
VmLib:     20540 kB
VmPTE:       156 kB
VmSwap:        0 kB
HugetlbPages:  0 kB
```

### 2048-Qt3

GNOME System Monitor: 2.1 MiB

```
cat /proc/`pidof 2048-Qt3`/status
...
VmPeak:   245084 kB
VmSize:   245084 kB
VmLck:         0 kB
VmPin:         0 kB
VmHWM:     15216 kB
VmRSS:     15216 kB
RssAnon:    2144 kB
RssFile:   13072 kB
RssShmem:      0 kB
VmData:     1748 kB
VmStk:       132 kB
VmExe:        28 kB
VmLib:     10460 kB
VmPTE:       116 kB
VmSwap:        0 kB
HugetlbPages:  0 kB
```

### 2048-Qt2

GNOME System Monitor: 1.2 MiB

```
cat /proc/`pidof 2048-Qt2`/status
...
VmPeak:   240780 kB
VmSize:   240780 kB
VmLck:         0 kB
VmPin:         0 kB
VmHWM:     11900 kB
VmRSS:     11816 kB
RssAnon:    1248 kB
RssFile:   10568 kB
RssShmem:      0 kB
VmData:      884 kB
VmStk:       132 kB
VmExe:        28 kB
VmLib:      9744 kB
VmPTE:       112 kB
VmSwap:        0 kB
HugetlbPages:  0 kB
```

### 2048-Qt1

GNOME System Monitor: 512.0 KiB

```
cat /proc/`pidof 2048-Qt1`/status
...
VmPeak:   222656 kB
VmSize:   222504 kB
VmLck:         0 kB
VmPin:         0 kB
VmHWM:      6100 kB
VmRSS:      6028 kB
RssAnon:     512 kB
RssFile:    5516 kB
RssShmem:      0 kB
VmData:      456 kB
VmStk:       132 kB
VmExe:        20 kB
VmLib:      4804 kB
VmPTE:        80 kB
VmSwap:        0 kB
HugetlbPages:  0 kB
```

### 2048-Vala

GNOME System Monitor: 5.7 MiB

```
cat /proc/`pidof 2048-Vala`/status
...
VmPeak:   612144 kB
VmSize:   556396 kB
VmLck:         0 kB
VmPin:         0 kB
VmHWM:     29848 kB
VmRSS:     29848 kB
RssAnon:    5844 kB
RssFile:   22744 kB
RssShmem:   1260 kB
VmData:    38480 kB
VmStk:       132 kB
VmExe:        16 kB
VmLib:     18168 kB
VmPTE:       180 kB
VmSwap:        0 kB
HugetlbPages:  0 kB
```

### 2048-Gtk3

GNOME System Monitor: 4.6 MiB

```
cat /proc/`pidof 2048-Gtk3`/status
...
VmPeak:   458176 kB
VmSize:   398432 kB
VmLck:         0 kB
VmPin:         0 kB
VmHWM:     25536 kB
VmRSS:     25536 kB
RssAnon:    4696 kB
RssFile:   20840 kB
RssShmem:      0 kB
VmData:    20832 kB
VmStk:       132 kB
VmExe:        12 kB
VmLib:     17284 kB
VmPTE:       152 kB
VmSwap:        0 kB
HugetlbPages:  0 kB
```

### 2048-Gtk2

GNOME System Monitor: 2.2 MiB

```
cat /proc/`pidof 2048-Gtk2`/status
...
VmPeak:   240204 kB
VmSize:   240204 kB
VmLck:         0 kB
VmPin:         0 kB
VmHWM:     17116 kB
VmRSS:     17116 kB
RssAnon:    2268 kB
RssFile:   14848 kB
RssShmem:      0 kB
VmData:     1888 kB
VmStk:       132 kB
VmExe:        12 kB
VmLib:     13616 kB
VmPTE:       112 kB
VmSwap:        0 kB
HugetlbPages:  0 kB
```

### 2048-Gtk1

GNOME System Monitor: 480.0 KiB

```
cat /proc/`pidof 2048-Gtk1`/status
...
VmPeak:    15980 kB
VmSize:    15980 kB
VmLck:         0 kB
VmPin:         0 kB
VmHWM:      4776 kB
VmRSS:      4668 kB
RssAnon:     480 kB
RssFile:    4188 kB
RssShmem:      0 kB
VmData:      540 kB
VmStk:       132 kB
VmExe:        12 kB
VmLib:      4192 kB
VmPTE:        60 kB
VmSwap:        0 kB
HugetlbPages:  0 kB
```

### 2048-Motif

GNOME System Monitor: 832.0 KiB

```
cat /proc/`pidof 2048-Motif`/status
...
VmPeak:   225024 kB
VmSize:   224872 kB
VmLck:         0 kB
VmPin:         0 kB
VmHWM:      7140 kB
VmRSS:      7040 kB
RssAnon:     832 kB
RssFile:    6208 kB
RssShmem:      0 kB
VmData:      812 kB
VmStk:       132 kB
VmExe:        12 kB
VmLib:      6620 kB
VmPTE:        92 kB
VmSwap:        0 kB
HugetlbPages:  0 kB
```

### 2048-Xaw

GNOME System Monitor: 332.0 KiB

```
cat /proc/`pidof 2048-Xaw`/status
...
VmPeak:     5380 kB
VmSize:     5380 kB
VmLck:         0 kB
VmPin:         0 kB
VmHWM:      3576 kB
VmRSS:      3576 kB
RssAnon:     332 kB
RssFile:    3244 kB
RssShmem:      0 kB
VmData:      472 kB
VmStk:       132 kB
VmExe:        12 kB
VmLib:      2900 kB
VmPTE:        48 kB
VmSwap:        0 kB
HugetlbPages:  0 kB
```

### 2048-Xlib

GNOME System Monitor: 116.0 KiB

```
cat /proc/`pidof 2048-Xlib`/status
...
VmPeak:     3896 kB
VmSize:     3876 kB
VmLck:         0 kB
VmPin:         0 kB
VmHWM:       932 kB
VmRSS:       932 kB
RssAnon:     116 kB
RssFile:     816 kB
RssShmem:      0 kB
VmData:      216 kB
VmStk:       132 kB
VmExe:        12 kB
VmLib:      2160 kB
VmPTE:        48 kB
VmSwap:        0 kB
HugetlbPages:  0 kB
```

### 2048-Xcb

GNOME System Monitor: 96.0 KiB

```
cat /proc/`pidof 2048-Xcb`/status
...
VmPeak:     2608 kB
VmSize:     2588 kB
VmLck:         0 kB
VmPin:         0 kB
VmHWM:       744 kB
VmRSS:       744 kB
RssAnon:      96 kB
RssFile:     648 kB
RssShmem:      0 kB
VmData:      204 kB
VmStk:       132 kB
VmExe:        12 kB
VmLib:      1588 kB
VmPTE:        48 kB
VmSwap:        0 kB
HugetlbPages:  0 kB
```

### 2048-MotoMAGX_ZN5

```
cat /proc/`pidof 2048-MotoMAGX_ZN5`/status
...
VmSize:    28748 kB
VmLck:         0 kB
VmRSS:      5556 kB
VmData:     1148 kB
VmStk:        84 kB
VmExe:        36 kB
VmLib:      9508 kB
VmPTE:        26 kB
```

### 2048-EZX

```
cat /proc/`pidof 2048-EZX`/status
...
VmSize:    25552 kB
VmLck:         0 kB
VmRSS:      4996 kB
VmData:      736 kB
VmStk:        12 kB
VmExe:        40 kB
VmLib:      8220 kB
```

```
cat /proc/`pidof 2048-EZX_E2`/status
...
VmSize:    25328 kB
VmLck:         0 kB
VmRSS:      5388 kB
VmData:      704 kB
VmStk:        24 kB
VmExe:        36 kB
VmLib:      9848 kB
```

### 2048-Serenity

```
top
...
   PID TID PRI  USER       STATE         VIRT    PHYS  %CPU  NAME
    84  84 30   anon       Selecting     6164    1732   0.0  2048-Serenity
```

```
Virtual:    6164 kB
Physical:   1732 kB
DirtyP:      712 kB
CleanI:      480 kB
PurgV:       164 kB
PurgN:      1048 kB
```

### 2048-NeXTSTEP

```
ps aux | head -1 && ps aux | grep 2048
USER       PID  %CPU %MEM VSIZE RSIZE TT STAT  TIME COMMAND
root       223   0.0  1.2 4.31M 1.52M ?  SW    0:00 /me/Apps/2048-NeXTSTEP.app/
```

### 2048-Photon

```
showmem -P `ps -A | grep 2048-Photon | head -1 | awk {print $1}`
...
Process listing (Total, Code, Data, Heap, Stack, Other)
  2183168    1855488     102400     200704      24576          0      765987 2048-Photon
Shared shared objects (Total, Code, Data, Heap, Stack, Other)
```

### 2048-JUCE

GNOME System Monitor: 1.7 MiB

```
cat /proc/`pidof 2048-JUCE`/status
...
VmPeak:   311380 kB
VmSize:   310808 kB
VmLck:         0 kB
VmPin:         0 kB
VmHWM:     13976 kB
VmRSS:     13872 kB
RssAnon:    1700 kB
RssFile:   12172 kB
RssShmem:      0 kB
VmData:     9616 kB
VmStk:       132 kB
VmExe:      2800 kB
VmLib:      9712 kB
VmPTE:       108 kB
VmSwap:        0 kB
HugetlbPages:  0 kB
```

### 2048-Cocoa

Mac OS X 10.0:

```
ps aux | head -1 && ps aux | grep 2048
USER       PID %CPU %MEM      VSZ    RSS  TT  STAT      TIME COMMAND
happymac   421   0.0  0.3    54940   3112  ??  S      2:08.30 /Users/happymac/Projects/2048-Cocoa.app/Contents/MacOS/2048-Cocoa -psn_0_786433

top
PID COMMAND      %CPU   TIME   #TH #PRTS #MREGS RPRVT  RSHRD  RSIZE  VSIZE
421 2048-Cocoa   0.0%  0:02.95   1    64    43   872K  4.01M  3.04M  53.7M
```

Mac OS X 10.5.8:

```
ps aux | head -1 && ps aux | grep 2048
USER       PID %CPU %MEM      VSZ    RSS   TT  STAT STARTED      TIME COMMAND
exl        764   0.0  0.4  2913736   8604   ??  S    10:26AM   0:02.37 /Users/exl/Projects/2048-Cocoa.app/Contents/MacOS/2048-Cocoa -psn_0_176171

top
PID COMMAND      %CPU   TIME   #TH #PRTS #MREGS RPRVT  RSHRD  RSIZE  VSIZE
764 2048-Cocoa   0.0%  0:02.37   1    70     98 2256K    12M  8604K   231M
```

Mac OS X 10.6.8:

```
ps aux | head -1 && ps aux | grep 2048
USER       PID  %CPU %MEM      VSZ    RSS   TT  STAT STARTED      TIME COMMAND
exl        315   0.0  0.6  2550784   6700   ??  S     5:35PM   0:01.21 /Users/exl/Projects/2048-Cocoa.app/Contents/MacOS/2048-Cocoa -psn_0_118813

top
PID  COMMAND      %CPU TIME     #TH  #WQ  #POR #MRE RPRVT  RSHRD  RSIZE  VPRVT  VSIZE  PGRP PPID STATE    UID  FAULTS  COW   MSGSENT  MSGRECV
315  2048-Cocoa   0.0  00:01.21 2    1    72   76   1628K  12M    6700K  19M    2491M  315  97   sleeping 502  2169    171   9285     4838
```

OS X 10.8.5:

```
ps aux | head -1 && ps aux | grep 2048
USER             PID  %CPU %MEM      VSZ    RSS   TT  STAT STARTED      TIME COMMAND
exl              340   0.0  0.5  2506596   9860   ??  S     4:02PM   0:00.27 /Users/exl/Projects/2048-Cocoa.app/Contents/MacOS/2048-Cocoa -psn_0_172074

top
PID  COMMAND      %CPU TIME     #TH  #WQ  #POR #MRE RPRVT  RSHRD  RSIZE  VPRVT  VSIZE  PGRP PPID STATE    UID
340  2048-Cocoa   0.0  00:00.27 2    1    98   95   2372K+ 9868K  9860K  15M+   2448M  340  149  sleeping 501
```

macOS 10.13.6:

```
ps aux | head -1 && ps aux | grep 2048
USER               PID  %CPU %MEM      VSZ    RSS   TT  STAT STARTED      TIME COMMAND
exl                957   0.0  0.4  4405976  27504   ??  S     6:20AM   0:00.64 /Users/exl/Projects/2048-Cocoa.app/Contents/MacOS/2048-Cocoa

top
PID  COMMAND      %CPU TIME     #TH   #WQ  #PORT MEM    PURG   CMPRS  PGRP PPID STATE    BOOSTS         %CPU_ME %CPU_OTHRS UID  FAULTS  COW    MSGSENT  MSGRECV  SYSBSD    SYSMACH  CSW
957  2048-Cocoa   0.0  00:00.82 3     1    202   10M    592K   0B     957  1    sleeping *0[19]         0.00000 0.00000    501  9238    349    7531     1594     6445      15123    6033
```

### 2048-Swift

macOS 10.13.6:

```
ps aux | head -1 && ps aux | grep 2048
USER               PID  %CPU %MEM      VSZ    RSS   TT  STAT STARTED      TIME COMMAND
exl               9026   0.0  0.5  4430908  29188   ??  S     4:46PM   0:00.77 /Users/exl/Projects/2048-Swift.app/Contents/MacOS/2048-Swift

top
PID   COMMAND      %CPU TIME     #TH   #WQ  #PORT MEM    PURG   CMPRS  PGRP PPID STATE    BOOSTS          %CPU_ME %CPU_OTHRS UID  FAULTS    COW      MSGSENT   MSGRECV   SYSBSD     SYSMACH
9075  2048-Swift   0.0  00:00.85 5     3    214   11M    592K   0B     9075 1    sleeping *0[11]          0.00000 0.00000    501  10414     462      9858      2003      7418       19749
```

### 2048-Think C

```
Mac OS System 6.0.8.1: 384 KB
Mac OS System 7.5.3:   384 KB
Mac OS 8.1:            400 KB
Mac OS 9.0.4:          452 KB
```

### 2048-MCW

```
Mac OS System 6.0.8.1: 1024 KB
Mac OS System 7.5.3:   1024 KB
Mac OS 8.1:            1 MB
Mac OS 9.0.4:          1.2 MB
```

### 2048-AUX

```
A/UX 3.0 & System Software 7.0.1: 1024 KB
```

### 2048-Carbon

```
Mac OS 8.6:           1.6 MB
Mac OS 9.0.4:         1.6 MB
```

Mac OS X 10.0 (CFM/PEF):

```
ps aux | head -1 && ps aux | grep 2048
USER       PID %CPU %MEM      VSZ    RSS  TT  STAT      TIME COMMAND
happymac   309  14.6  0.3    52596   3508  ??  R      1:01.75 /Users/happymac/Projects/2048-Carbon/2048-Carbon /Users/happymac/Projects/2048-Carbon/

top
PID COMMAND      %CPU   TIME   #TH #PRTS #MREGS RPRVT  RSHRD  RSIZE  VSIZE
309 2048-Carbo  29.3%  1:28.26   1    56    73  1.67M  3.78M  3.43M  51.4M
```

Mac OS X 10.0 (Mach-O):

```
ps aux | head -1 && ps aux | grep 2048
USER       PID %CPU %MEM      VSZ    RSS  TT  STAT      TIME COMMAND
happymac   551  13.7  0.3    52068   2968  ??  R      0:43.72 /Users/happymac/Projects/2048-Carbon.app/Contents/MacOS/2048-Carbon -psn_0_2097153

top
PID COMMAND      %CPU   TIME   #TH #PRTS #MREGS RPRVT  RSHRD  RSIZE  VSIZE
551 2048-Carbo  26.0%  1:03.15   1    57    44  1.52M  4.21M  2.90M  50.8M
```

Mac OS X 10.4.11:

```
ps aux | head -1 && ps aux | grep 2048
USER       PID %CPU %MEM      VSZ    RSS  TT  STAT STARTED      TIME COMMAND
exl        428   0.0 -0.6   233340  12856  ??  S    11:32AM   0:01.63 /Users/exl/Projects/2048-Carbon.app/Contents/MacOS/2048-Carbon -psn_0_1310721

top
PID COMMAND      %CPU   TIME   #TH #PRTS #MREGS RPRVT  RSHRD  RSIZE  VSIZE
428 2048-Carbo   0.0%  0:01.62   1    57    81  1.02M  6.86M  12.6M   227M
```

Mac OS X 10.5.8:

```
ps aux | head -1 && ps aux | grep 2048
USER       PID %CPU %MEM      VSZ    RSS   TT  STAT STARTED      TIME COMMAND
exl        727   0.0  0.2   292168   5172   ??  S    10:22AM   0:02.41 /Users/exl/Projects/2048-Carbon.app/Contents/MacOS/2048-Carbon -psn_0_172074

top
PID COMMAND      %CPU   TIME   #TH #PRTS #MREGS RPRVT  RSHRD  RSIZE  VSIZE
727 2048-Carbo   0.0%  0:02.41   1    67     89 1180K    13M  5172K   229M
```

### 2048-UIQ2

```
2048:      64K
HeapSize:  44K
StackSize: 20K
```
