Mac OS Notes
============

## Mac OS X 10.0 "Cheetah"

### QEMU install and run recipes

```bash
qemu-system-ppc -L pc-bios -boot d -M mac99 -m 1024 -hda os_x10_0.img -cdrom osx_100_4k78_install.iso
qemu-system-ppc -L pc-bios -boot c -M mac99 -m 1024 -hda os_x10_0.img
```

## Mac OS X 10.4.11 "Tiger"

Patch EFI firmwares by [efi-unlocker](https://github.com/sakurayz/efi-unlocker) utility.

### VMX hacks

```
efi32.filename = "EFI32-MACOS.ROM"
cpuid.1.eax = "00000000000000000000011011111010"
cpuid.2.eax = "00000101101100001011000100000001"
cpuid.2.ebx = "00000000010101100101011111110000"
cpuid.2.ecx = "00000000000000000000000000000000"
cpuid.2.edx = "00101100101101000011000001001000"
```

### Registration Information

```
First Name: EXL
Last Name: Unknown
Address: Unknown
City: New York
State: NY
Zip Code: 10000
Area Code: 845
Phone Number: 5555555
```

## Proper Screen Resolution

Use "VMsvga2.kext" by Zenith432 with patches by d3vi1 from [VMsvga2-Darwin-Tiger](https://github.com/d3vi1/VMsvga2-Darwin-Tiger/) project.

```bash
curl -O https://github.com/d3vi1/VMsvga2-Darwin-Tiger/releases/download/1.1.0-Tiger/VMsvga2-1.1.0-Tiger-Universal.tar.gz # Modern HTTPS doesn't work on Mac OS 10.4 Tiger.
curl -O http://baat.z-lab.me/~exl_lab/software/VMsvga2-1.1.0-Tiger-Universal.tar.gz # HTTP mirror.
tar -xvzf VMsvga2-1.1.0-Tiger-Universal.tar.gz
cd ReleaseTiger/
sudo mv VMsvga2.kext /System/Library/Extensions/
cd /System/Library/Extensions/
sudo chown -R root VMsvga2.kext
sudo chgrp -R wheel VMsvga2.kext
sudo kextcache -u /
```

Restart virtual machine.

## Mac OS X 10.5.8 "Leopard"

Patch EFI firmwares by [efi-unlocker](https://github.com/sakurayz/efi-unlocker) utility.

### VMX hacks

```
efi32.filename = "EFI32-MACOS.ROM"
efi64.filename = "EFI64-MACOS.ROM"
```

## Mac OS X 10.6.8 "Snow Leopard"

Patch EFI firmwares by [efi-unlocker](https://github.com/sakurayz/efi-unlocker) utility.

### VMX hacks

```
efi32.filename = "EFI32-MACOS.ROM"
efi64.filename = "EFI64-MACOS.ROM"
```

### Problem with `NSFont *` instance variables.

#### Affected environment

* Mac OS X "Snow Leopard" at least 10.6.8 version.
* Xcode 3 and 4 major versions.

#### Minimal reproducible example

```objc
// MyView.h

@interface MyView : NSView {
	NSFont *largeFont;
}
```

```objc
// MyView.m

@implementation MyView

- (void)awakeFromNib {
	largeFont = [NSFont systemFontOfSize:28.0f];
}

- (void)drawRect:(NSRect)rect {
	if (largeFont)
		NSLog(@"%p:%@", largeFont, largeFont);
}

@end
```

#### Description

On the first rendering frame everything is fine and information about the font is displayed in the log but the second redraw frame causes the application to crash. It seems that the `largeFont` pointer is being invalidated somewhere. The pointer in this case isn't reset to `nil` and `EXC_BAD_ACCESS` error occurs directly in `NSLog()` function.

```
(gdb) bt
#0  0x00007fff8580dd05 in -[NSFont description] ()
#1  0x00007fff81eaa492 in _NSDescriptionWithLocaleFunc ()
#2  0x00007fff89c88ded in _CFStringAppendFormatAndArgumentsAux ()
#3  0x00007fff89c8826d in _CFStringCreateWithFormatAndArgumentsAux ()
#4  0x00007fff89d079bf in _CFLogvEx ()
#5  0x00007fff81f0bd70 in NSLogv ()
#6  0x00007fff81f0bd08 in NSLog ()
#7  0x00000001000017e8 in -[GameView drawRect:] (self=0x100173880, _cmd=0x7fff85ba3560) at /Users/exl/Projects/TestNsFontBug/GameView.m:20
...
```

The backtrace shows that the crash occurs on the `- [NSFont description]` method inside the Cocoa (AppKit) framework.

#### Additional research

Modification the draw-method as follows shows that `largeFont` pointer changes its address after first rendered frame.

```objc
- (void)drawRect:(NSRect)rect {
	NSFont *largeFont = [NSFont systemFontOfSize:28.0f];
	NSLog(@"%p:%@", largeFont, largeFont);
}
```

Mac OS X 10.6.8 output:

```
0x100166a30:"LucidaGrande 28.00 pt. P [] (0x100166a30) fobj=0x100166cc0, spc=8.86"
0x100144210:"LucidaGrande 28.00 pt. P [] (0x100144210) fobj=0x10016ae20, spc=8.86"
0x100144210:"LucidaGrande 28.00 pt. P [] (0x100144210) fobj=0x10016afe0, spc=8.86"
0x100144210:"LucidaGrande 28.00 pt. P [] (0x100144210) fobj=0x10015bcd0, spc=8.86"
0x100144210:"LucidaGrande 28.00 pt. P [] (0x100144210) fobj=0x10018f380, spc=8.86"
...
```

macOS X 10.13.6 output:

```
0x604000245880:".SFNSDisplay 28.00 pt. P [] (0x604000245880) fobj=0x1028269e0, spc=6.10"
0x604000245880:".SFNSDisplay 28.00 pt. P [] (0x604000245880) fobj=0x10052ef30, spc=6.10"
0x604000245880:".SFNSDisplay 28.00 pt. P [] (0x604000245880) fobj=0x100605770, spc=6.10"
0x604000245880:".SFNSDisplay 28.00 pt. P [] (0x604000245880) fobj=0x10282fa00, spc=6.10"
0x604000245880:".SFNSDisplay 28.00 pt. P [] (0x604000245880) fobj=0x10282fa00, spc=6.10"
...
```

Modern and some older versions of Mac OS are not affected by this issue.

#### Fix

Don't use instance variables for `NSFont` objects.

```objc
#define largeFont [NSFont systemFontOfSize:28.0f]
```

The problem can be solved by local calls or defines. See 97b57132b8df8c66841e96452f02cdf9cecfbc9e commit for more information.

## Xcode Notes

Useful service to download various versions of Xcode IDE: [Xcode Releases](https://xcodereleases.com/). Compatibility notes available.
