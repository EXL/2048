Binary Information
==================

Dependencies were obtained:

1. By using `ldd` command on Fedora and QNX.
2. By `arm-linux-gnueabi-objdump` for MotoMAGX platform.
3. By `otool -L` command on NeXTSTEP and Mac OS X.

### Sizes

```
ls -lh 2048-*
-rwxrwxr-x. 1 exl exl  15K Jun 30 07:18 2048-Gtk1
-rwxrwxr-x. 1 exl exl  15K Jun 30 07:18 2048-Gtk2
-rwxrwxr-x. 1 exl exl  15K Jun 30 07:18 2048-Gtk3
-rwxrwxr-x. 1 exl exl 3.6M Oct  5 18:42 2048-JUCE
-rwxrwxr-x. 1 exl exl  15K Jun 30 07:20 2048-Motif
-rwxrwxr-x. 1 exl exl  40K Jun 29 02:56 2048-MotoMAGX_E8
-rwxrwxr-x. 1 exl exl  40K Jun 29 02:56 2048-MotoMAGX_EM30
-rwxrwxr-x. 1 exl exl  40K Jun 29 02:58 2048-MotoMAGX_EM35
-rwxrwxr-x. 1 exl exl  40K Jun 29 02:57 2048-MotoMAGX_U9
-rwxrwxr-x. 1 exl exl  40K Jun 29 02:57 2048-MotoMAGX_V8
-rwxrwxr-x. 1 exl exl  40K Jun 29 02:57 2048-MotoMAGX_VE66
-rwxrwxr-x. 1 exl exl  40K Jun 29 02:57 2048-MotoMAGX_Z6
-rwxrwxr-x. 1 exl exl  40K Jun 29 02:57 2048-MotoMAGX_Z6W
-rwxrwxr-x. 1 exl exl  40K Jun 29 02:57 2048-MotoMAGX_ZN5
-rwxrwxr-x. 1 exl exl  40K Sep 26 01:41 2048-Photon
-rwxrwxr-x. 1 exl exl  23K Jun 30 07:19 2048-Qt1
-rwxrwxr-x. 1 exl exl  32K Jun 30 07:19 2048-Qt2
-rwxrwxr-x. 1 exl exl  32K Jun 30 07:19 2048-Qt3
-rwxrwxr-x. 1 exl exl  23K Jun 30 07:19 2048-Qt4
-rwxrwxr-x. 1 exl exl  23K Jun 30 07:19 2048-Qt5
-rwxrwxr-x. 1 exl exl 759K Sep 27 09:18 2048-Serenity
-rwxrwxr-x. 1 exl exl  15K Jun 30 07:20 2048-Xaw
-rwxrwxr-x. 1 exl exl  15K Jun 30 07:20 2048-Xcb
-rwxrwxr-x. 1 exl exl  15K Jun 30 07:20 2048-Xlib

ls -lh MotoMAGX/
total 2.9M
-rw-rw-r--. 1 exl exl  15K Jun 29 02:58 2048_MotoMAGX_ZN5_v1.0_28-Jul-2020.mgx
-rw-rw-r--. 1 exl exl 2.9M Jun 27 05:01 2048_MotoMAGX_ZN5.webm

ls -lh NeXTSTEP/*
NeXTSTEP/2048-NeXTSTEP.app:
total 276K
-rwxr-xr-x. 1 exl exl 200K Nov 15  1994 2048-NeXTSTEP
-rw-r--r--. 1 exl exl  50K Nov 15  1994 avatar.tiff
drwxr-xr-x. 4 exl exl 4.0K Nov 15  1994 English.lproj
-rw-r--r--. 1 exl exl  16K Nov 15  1994 icon150.tiff
-rw-r--r--. 1 exl exl 3.2K Nov 15  1994 icon48.tiff
NeXTSTEP/2048-NeXTSTEP.pkg:
total 200K
-rw-r--r--. 1 exl exl  16K Nov 15  1994 2048-NeXTSTEP.bom
-r--r--r--. 1 exl exl  798 Nov 15  1994 2048-NeXTSTEP.info
-rw-r--r--. 1 exl exl   49 Nov 15  1994 2048-NeXTSTEP.sizes
-r--r--r--. 1 exl exl 169K Nov 15  1994 2048-NeXTSTEP.tar.Z
-r--r--r--. 1 exl exl 3.2K Nov 15  1994 2048-NeXTSTEP.tiff

ls -lhR MacOS/
MacOS/:
total 16K
drwxr-xr-x. 3 exl exl 4.0K Oct 25 05:04 10.0
drwxr-xr-x. 3 exl exl 4.0K Oct 25 06:54 10.13
drwxr-xr-x. 3 exl exl 4.0K Oct 25 06:53 10.6
drwxr-xr-x. 3 exl exl 4.0K Oct 25 06:55 10.8
MacOS/10.0:
total 4.0K
drwxr-xr-x. 3 exl exl 4.0K Oct 25 04:14 2048-Cocoa.app
MacOS/10.0/2048-Cocoa.app:
total 4.0K
drwxr-xr-x. 4 exl exl 4.0K Oct 25 04:14 Contents
MacOS/10.0/2048-Cocoa.app/Contents:
total 20K
-rw-r--r--. 1 exl exl  760 Oct 25 04:13 Info.plist
drwxr-xr-x. 2 exl exl 4.0K Oct 25 04:14 MacOS
-rw-r--r--. 1 exl exl  275 Oct 25 04:13 pbdevelopment.plist
-rw-r--r--. 1 exl exl    8 Oct 25 04:13 PkgInfo
drwxr-xr-x. 3 exl exl 4.0K Oct 25 04:13 Resources
MacOS/10.0/2048-Cocoa.app/Contents/MacOS:
total 40K
-rwxr-xr-x. 1 exl exl 37K Oct 25 04:14 2048-Cocoa
MacOS/10.0/2048-Cocoa.app/Contents/Resources:
total 60K
-rw-r--r--. 1 exl exl  49K Oct 25 04:13 2048-Cocoa.icns
drwxr-xr-x. 3 exl exl 4.0K Oct 25 04:13 English.lproj
-rw-r--r--. 1 exl exl 1.8K Oct 25 04:13 ReadMe.md
MacOS/10.0/2048-Cocoa.app/Contents/Resources/English.lproj:
total 12K
drwxr-xr-x. 2 exl exl 4.0K Oct 25 04:13 2048-Cocoa.nib
-rw-r--r--. 1 exl exl  530 Oct 25 04:13 InfoPlist.strings
-rw-r--r--. 1 exl exl  413 Oct 25 04:13 Localizable.strings
MacOS/10.0/2048-Cocoa.app/Contents/Resources/English.lproj/2048-Cocoa.nib:
total 12K
-rw-r--r--. 1 exl exl  688 Oct 25 04:13 classes.nib
-rw-r--r--. 1 exl exl  500 Oct 25 04:13 info.nib
-rw-r--r--. 1 exl exl 3.0K Oct 25 04:13 objects.nib
MacOS/10.13:
total 4.0K
drwxr-xr-x. 3 exl exl 4.0K Oct 25 06:30 2048-Cocoa.app
MacOS/10.13/2048-Cocoa.app:
total 4.0K
drwxr-xr-x. 5 exl exl 4.0K Oct 25 06:29 Contents
MacOS/10.13/2048-Cocoa.app/Contents:
total 20K
drwxr-xr-x. 2 exl exl 4.0K Oct 25 06:54 _CodeSignature
-rw-r--r--. 1 exl exl 1.7K Oct 25 06:29 Info.plist
drwxr-xr-x. 2 exl exl 4.0K Oct 25 06:54 MacOS
-rw-r--r--. 1 exl exl    8 Oct 25 06:29 PkgInfo
drwxr-xr-x. 4 exl exl 4.0K Oct 25 06:29 Resources
MacOS/10.13/2048-Cocoa.app/Contents/_CodeSignature:
total 4.0K
-rw-r--r--. 1 exl exl 3.9K Oct 25 06:29 CodeResources
MacOS/10.13/2048-Cocoa.app/Contents/MacOS:
total 44K
-rwxr-xr-x. 1 exl exl 42K Oct 25 06:30 2048-Cocoa
MacOS/10.13/2048-Cocoa.app/Contents/Resources:
total 1.2M
-rw-r--r--. 1 exl exl 628K Oct 25 06:29 AppIcon.icns
-rw-r--r--. 1 exl exl 509K Oct 25 06:29 Assets.car
drwxr-xr-x. 2 exl exl 4.0K Oct 25 06:54 Base.lproj
drwxr-xr-x. 2 exl exl 4.0K Oct 25 06:54 English.lproj
-rw-r--r--. 1 exl exl 1.7K Oct 25 06:29 ReadMe.md
MacOS/10.13/2048-Cocoa.app/Contents/Resources/Base.lproj:
total 12K
-rw-r--r--. 1 exl exl 8.9K Oct 25 06:29 2048-Cocoa.nib
MacOS/10.13/2048-Cocoa.app/Contents/Resources/English.lproj:
total 4.0K
-rw-r--r--. 1 exl exl 828 Oct 25 06:29 Localizable.strings
MacOS/10.6:
total 4.0K
drwxr-xr-x. 3 exl exl 4.0K Oct 25 05:26 2048-Cocoa.app
MacOS/10.6/2048-Cocoa.app:
total 4.0K
drwxr-xr-x. 4 exl exl 4.0K Oct 25 05:26 Contents
MacOS/10.6/2048-Cocoa.app/Contents:
total 16K
-rw-r--r--. 1 exl exl 1.6K Oct 25 05:26 Info.plist
drwxr-xr-x. 2 exl exl 4.0K Oct 25 06:53 MacOS
-rw-r--r--. 1 exl exl    8 Oct 25 05:26 PkgInfo
drwxr-xr-x. 3 exl exl 4.0K Oct 25 05:26 Resources
MacOS/10.6/2048-Cocoa.app/Contents/MacOS:
total 56K
-rwxr-xr-x. 1 exl exl 54K Oct 25 05:26 2048-Cocoa
MacOS/10.6/2048-Cocoa.app/Contents/Resources:
total 148K
-rw-r--r--. 1 exl exl 140K Oct 25 05:26 2048-Cocoa-modern.icns
drwxr-xr-x. 2 exl exl 4.0K Oct 25 06:53 en.lproj
-rw-r--r--. 1 exl exl 1.3K Oct 25 05:26 ReadMe.md
MacOS/10.6/2048-Cocoa.app/Contents/Resources/en.lproj:
total 20K
-rw-r--r--. 1 exl exl 8.5K Oct 25 05:26 2048-Cocoa.nib
-rw-r--r--. 1 exl exl 1.1K Oct 25 05:26 Credits.rtf
-rw-r--r--. 1 exl exl  828 Oct 25 05:26 Localizable.strings
MacOS/10.8:
total 4.0K
drwxr-xr-x. 3 exl exl 4.0K Oct 25 06:00 2048-Cocoa.app
MacOS/10.8/2048-Cocoa.app:
total 4.0K
drwxr-xr-x. 5 exl exl 4.0K Oct 25 06:00 Contents
MacOS/10.8/2048-Cocoa.app/Contents:
total 20K
drwxr-xr-x. 2 exl exl 4.0K Oct 25 06:55 _CodeSignature
-rw-r--r--. 1 exl exl 1.6K Oct 25 06:00 Info.plist
drwxr-xr-x. 2 exl exl 4.0K Oct 25 06:55 MacOS
-rw-r--r--. 1 exl exl    8 Oct 25 06:00 PkgInfo
drwxr-xr-x. 3 exl exl 4.0K Oct 25 06:01 Resources
MacOS/10.8/2048-Cocoa.app/Contents/_CodeSignature:
total 4.0K
-rw-r--r--. 1 exl exl 1.4K Oct 25 06:00 CodeResources
MacOS/10.8/2048-Cocoa.app/Contents/MacOS:
total 40K
-rwxr-xr-x. 1 exl exl 39K Oct 25 06:00 2048-Cocoa
MacOS/10.8/2048-Cocoa.app/Contents/Resources:
total 636K
-rw-r--r--. 1 exl exl 628K Oct 25 06:00 AppIcon.icns
drwxr-xr-x. 2 exl exl 4.0K Oct 25 06:55 en.lproj
-rw-r--r--. 1 exl exl 1.3K Oct 25 06:00 ReadMe.md
MacOS/10.8/2048-Cocoa.app/Contents/Resources/en.lproj:
total 16K
-rw-r--r--. 1 exl exl 7.4K Oct 25 06:00 2048-Cocoa.nib
-rw-r--r--. 1 exl exl 1.1K Oct 25 06:00 Credits.rtf
-rw-r--r--. 1 exl exl  828 Oct 25 06:00 Localizable.strings
```

### File Types

```
file 2048-*
2048-Gtk1:          ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 2.6.32, BuildID[sha1]=7184adff443baf648bb1a08061fc2003b8f8265a, stripped
2048-Gtk2:          ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 2.6.32, BuildID[sha1]=8664c4f62a320b321831474b86d84743d58a1378, stripped
2048-Gtk3:          ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 2.6.32, BuildID[sha1]=465a678a0e5a28faf80a3a9149acc3d3408f29da, stripped
2048-Motif:         ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 2.6.32, BuildID[sha1]=ee11f72f2c732b4f2b348bf4d772ac20647d3dd3, stripped
2048-MotoMAGX_E8:   ELF 32-bit LSB executable, ARM, EABI4 version 1 (SYSV), dynamically linked, interpreter /lib/ld-linux.so.3, for GNU/Linux 2.4.17, stripped
2048-MotoMAGX_EM30: ELF 32-bit LSB executable, ARM, EABI4 version 1 (SYSV), dynamically linked, interpreter /lib/ld-linux.so.3, for GNU/Linux 2.4.17, stripped
2048-MotoMAGX_EM35: ELF 32-bit LSB executable, ARM, EABI4 version 1 (SYSV), dynamically linked, interpreter /lib/ld-linux.so.3, for GNU/Linux 2.4.17, stripped
2048-MotoMAGX_U9:   ELF 32-bit LSB executable, ARM, EABI4 version 1 (SYSV), dynamically linked, interpreter /lib/ld-linux.so.3, for GNU/Linux 2.4.17, stripped
2048-MotoMAGX_V8:   ELF 32-bit LSB executable, ARM, EABI4 version 1 (SYSV), dynamically linked, interpreter /lib/ld-linux.so.3, for GNU/Linux 2.4.17, stripped
2048-MotoMAGX_VE66: ELF 32-bit LSB executable, ARM, EABI4 version 1 (SYSV), dynamically linked, interpreter /lib/ld-linux.so.3, for GNU/Linux 2.4.17, stripped
2048-MotoMAGX_Z6:   ELF 32-bit LSB executable, ARM, EABI4 version 1 (SYSV), dynamically linked, interpreter /lib/ld-linux.so.3, for GNU/Linux 2.4.17, stripped
2048-MotoMAGX_Z6W:  ELF 32-bit LSB executable, ARM, EABI4 version 1 (SYSV), dynamically linked, interpreter /lib/ld-linux.so.3, for GNU/Linux 2.4.17, stripped
2048-MotoMAGX_ZN5:  ELF 32-bit LSB executable, ARM, EABI4 version 1 (SYSV), dynamically linked, interpreter /lib/ld-linux.so.3, for GNU/Linux 2.4.17, stripped
2048-Photon:        ELF 32-bit LSB executable, Intel 80386, version 1 (SYSV), dynamically linked, interpreter /usr/lib/ldqnx.so.2, stripped
2048-Qt1:           ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 2.6.32, BuildID[sha1]=881e5f8c0db33bf72acee46b37bfc2b5adfbdaad, stripped
2048-Qt2:           ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 2.6.32, BuildID[sha1]=d7738df97853dafcedd43754d760f035317956a6, stripped
2048-Qt3:           ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 2.6.32, BuildID[sha1]=7a5c4b4aa286d5ecde2f183a0a8ba1431eb05f9d, stripped
2048-Qt4:           ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 2.6.32, BuildID[sha1]=fd454656289bc8f07a1740f9fca73e3e6b303d62, stripped
2048-Qt5:           ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 2.6.32, BuildID[sha1]=f63cb42651afdcf8dd866d2d9ed5cea08ef8bfb7, stripped
2048-Serenity:      ELF 32-bit LSB executable, Intel 80386, version 1 (SYSV), statically linked, stripped
2048-Xaw:           ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 2.6.32, BuildID[sha1]=566076a8373ccfa7cf64ff73a4b4385b18bce7a7, stripped
2048-Xcb:           ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 2.6.32, BuildID[sha1]=1f45dde2f5c9aac70b8bcad872f45d8f962451ea, stripped
2048-Xlib:          ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 2.6.32, BuildID[sha1]=55e80fe0e4e139ef18c9bee96bcd9f5d66545294, stripped

file MotoMAGX/*
MotoMAGX/2048_MotoMAGX_ZN5_v1.0_28-Jul-2020.mgx: 7-zip archive data, version 0.4
MotoMAGX/2048_MotoMAGX_ZN5.webm:                 WebM

find NeXTSTEP/ -type f -exec file {} \;
NeXTSTEP/2048-NeXTSTEP.app/icon150.tiff: TIFF image data, little-endian, direntries=19, height=150, bps=15744, compression=LZW, PhotometricIntepretation=RGB, name=/home/exl/Projects/2048/image/icon/avatar.tiff, orientation=upper-left, width=150
NeXTSTEP/2048-NeXTSTEP.app/avatar.tiff: TIFF image data, little-endian, direntries=18, height=150, bps=50592, compression=LZW, PhotometricIntepretation=RGB, name=/home/exl/Projects/2048/image/icon/avatar.tiff, orientation=upper-left, width=150
NeXTSTEP/2048-NeXTSTEP.app/English.lproj/2048-NeXTSTEP.nib/data.nib: NeXT/Apple typedstream data, little endian, version 4, system 930
NeXTSTEP/2048-NeXTSTEP.app/English.lproj/2048-NeXTSTEP.nib/data.classes: ASCII text
NeXTSTEP/2048-NeXTSTEP.app/English.lproj/2048-Info.nib/data.nib: NeXT/Apple typedstream data, little endian, version 4, system 930
NeXTSTEP/2048-NeXTSTEP.app/English.lproj/2048-Info.nib/data.classes: ASCII text
NeXTSTEP/2048-NeXTSTEP.app/icon48.tiff: TIFF image data, little-endian, direntries=19, height=48, bps=3154, compression=LZW, PhotometricIntepretation=RGB, name=/home/exl/Projects/2048/image/icon/icon48_1.tiff, orientation=upper-left, width=48
NeXTSTEP/2048-NeXTSTEP.app/2048-NeXTSTEP: Mach-O universal binary with 4 architectures: [m68k:Mach-O m68k executable, flags:<NOUNDEFS>] [i386:Mach-O i386 executable, flags:<NOUNDEFS>] [hppa 7100:Mach-O hppa 7100 executable, flags:<NOUNDEFS>] [SPARC:Mach-O SPARC executable, flags:<NOUNDEFS>]
NeXTSTEP/2048-NeXTSTEP.pkg/2048-NeXTSTEP.bom: data
NeXTSTEP/2048-NeXTSTEP.pkg/2048-NeXTSTEP.sizes: ASCII text
NeXTSTEP/2048-NeXTSTEP.pkg/2048-NeXTSTEP.tar.Z: compress'd data 16 bits
NeXTSTEP/2048-NeXTSTEP.pkg/2048-NeXTSTEP.info: ASCII text
NeXTSTEP/2048-NeXTSTEP.pkg/2048-NeXTSTEP.tiff: TIFF image data, little-endian, direntries=19, height=48, bps=3154, compression=LZW, PhotometricIntepretation=RGB, name=/home/exl/Projects/2048/image/icon/icon48_1.tiff, orientation=upper-left, width=48

find MacOS/ -type f -exec file {} \;
MacOS/10.6/2048-Cocoa.app/Contents/Info.plist: XML 1.0 document, UTF-8 Unicode text
MacOS/10.6/2048-Cocoa.app/Contents/Resources/en.lproj/2048-Cocoa.nib: Apple binary property list
MacOS/10.6/2048-Cocoa.app/Contents/Resources/en.lproj/Credits.rtf: Rich Text Format data, version 1, ANSI
MacOS/10.6/2048-Cocoa.app/Contents/Resources/en.lproj/Localizable.strings: Little-endian UTF-16 Unicode text
MacOS/10.6/2048-Cocoa.app/Contents/Resources/ReadMe.md: ASCII text
MacOS/10.6/2048-Cocoa.app/Contents/Resources/2048-Cocoa-modern.icns: Mac OS X icon, 142338 bytes, "is32" type
MacOS/10.6/2048-Cocoa.app/Contents/PkgInfo: ASCII text, with no line terminators
MacOS/10.6/2048-Cocoa.app/Contents/MacOS/2048-Cocoa: Mach-O universal binary with 2 architectures: [x86_64:Mach-O 64-bit x86_64 executable, flags:<NOUNDEFS|DYLDLINK|TWOLEVEL>] [i386:Mach-O i386 executable, flags:<NOUNDEFS|DYLDLINK|TWOLEVEL|NO_HEAP_EXECUTION>]
MacOS/10.13/2048-Cocoa.app/Contents/Info.plist: XML 1.0 document, UTF-8 Unicode text
MacOS/10.13/2048-Cocoa.app/Contents/Resources/AppIcon.icns: Mac OS X icon, 642518 bytes, "TOC " type
MacOS/10.13/2048-Cocoa.app/Contents/Resources/Base.lproj/2048-Cocoa.nib: Apple binary property list
MacOS/10.13/2048-Cocoa.app/Contents/Resources/ReadMe.md: ASCII text
MacOS/10.13/2048-Cocoa.app/Contents/Resources/English.lproj/Localizable.strings: Little-endian UTF-16 Unicode text
MacOS/10.13/2048-Cocoa.app/Contents/Resources/Assets.car: Mac OS X bill of materials (BOM) file
MacOS/10.13/2048-Cocoa.app/Contents/PkgInfo: ASCII text, with no line terminators
MacOS/10.13/2048-Cocoa.app/Contents/_CodeSignature/CodeResources: XML 1.0 document, ASCII text
MacOS/10.13/2048-Cocoa.app/Contents/MacOS/2048-Cocoa: Mach-O 64-bit x86_64 executable, flags:<NOUNDEFS|DYLDLINK|TWOLEVEL|PIE>
MacOS/10.8/2048-Cocoa.app/Contents/Info.plist: XML 1.0 document, UTF-8 Unicode text
MacOS/10.8/2048-Cocoa.app/Contents/Resources/AppIcon.icns: Mac OS X icon, 642414 bytes, "TOC " type
MacOS/10.8/2048-Cocoa.app/Contents/Resources/en.lproj/2048-Cocoa.nib: Apple binary property list
MacOS/10.8/2048-Cocoa.app/Contents/Resources/en.lproj/Credits.rtf: Rich Text Format data, version 1, ANSI
MacOS/10.8/2048-Cocoa.app/Contents/Resources/en.lproj/Localizable.strings: Little-endian UTF-16 Unicode text
MacOS/10.8/2048-Cocoa.app/Contents/Resources/ReadMe.md: ASCII text
MacOS/10.8/2048-Cocoa.app/Contents/PkgInfo: ASCII text, with no line terminators
MacOS/10.8/2048-Cocoa.app/Contents/_CodeSignature/CodeResources: XML 1.0 document, ASCII text
MacOS/10.8/2048-Cocoa.app/Contents/MacOS/2048-Cocoa: Mach-O 64-bit x86_64 executable, flags:<NOUNDEFS|DYLDLINK|TWOLEVEL>
MacOS/10.0/2048-Cocoa.app/Contents/pbdevelopment.plist: XML 1.0 document, ASCII text
MacOS/10.0/2048-Cocoa.app/Contents/Info.plist: XML 1.0 document, ASCII text
MacOS/10.0/2048-Cocoa.app/Contents/Resources/ReadMe.md: ReStructuredText file, ASCII text
MacOS/10.0/2048-Cocoa.app/Contents/Resources/English.lproj/InfoPlist.strings: Big-endian UTF-16 Unicode text
MacOS/10.0/2048-Cocoa.app/Contents/Resources/English.lproj/2048-Cocoa.nib/info.nib: XML 1.0 document, ASCII text
MacOS/10.0/2048-Cocoa.app/Contents/Resources/English.lproj/2048-Cocoa.nib/classes.nib: ASCII text
MacOS/10.0/2048-Cocoa.app/Contents/Resources/English.lproj/2048-Cocoa.nib/objects.nib: NeXT/Apple typedstream data, big endian, version 4, system 1000
MacOS/10.0/2048-Cocoa.app/Contents/Resources/English.lproj/Localizable.strings: ASCII text
MacOS/10.0/2048-Cocoa.app/Contents/Resources/2048-Cocoa.icns: Mac OS X icon, 49253 bytes, "ics#" type
MacOS/10.0/2048-Cocoa.app/Contents/PkgInfo: ASCII text, with no line terminators
MacOS/10.0/2048-Cocoa.app/Contents/MacOS/2048-Cocoa: Mach-O ppc executable, flags:<NOUNDEFS|DYLDLINK|PREBOUND>
```

### 2048-Qt5

```
ldd 2048-Qt5
	linux-vdso.so.1 (0x00007ffcf2194000)
	libQt5Widgets.so.5 => /lib64/libQt5Widgets.so.5 (0x00007fe6acc41000)
	libQt5Gui.so.5 => /lib64/libQt5Gui.so.5 (0x00007fe6ac6d8000)
	libQt5Core.so.5 => /lib64/libQt5Core.so.5 (0x00007fe6ac1bd000)
	libstdc++.so.6 => /lib64/libstdc++.so.6 (0x00007fe6abfcd000)
	libm.so.6 => /lib64/libm.so.6 (0x00007fe6abe87000)
	libgcc_s.so.1 => /lib64/libgcc_s.so.1 (0x00007fe6abe6c000)
	libc.so.6 => /lib64/libc.so.6 (0x00007fe6abca0000)
	libpthread.so.0 => /lib64/libpthread.so.0 (0x00007fe6abc7e000)
	libGL.so.1 => /lib64/libGL.so.1 (0x00007fe6abbf6000)
	libpng16.so.16 => /lib64/libpng16.so.16 (0x00007fe6abbbf000)
	libz.so.1 => /lib64/libz.so.1 (0x00007fe6abba5000)
	libharfbuzz.so.0 => /lib64/libharfbuzz.so.0 (0x00007fe6abac3000)
	libsystemd.so.0 => /lib64/libsystemd.so.0 (0x00007fe6aba0a000)
	libicui18n.so.65 => /lib64/libicui18n.so.65 (0x00007fe6ab703000)
	libicuuc.so.65 => /lib64/libicuuc.so.65 (0x00007fe6ab51b000)
	libdl.so.2 => /lib64/libdl.so.2 (0x00007fe6ab514000)
	libpcre2-16.so.0 => /lib64/libpcre2-16.so.0 (0x00007fe6ab489000)
	libglib-2.0.so.0 => /lib64/libglib-2.0.so.0 (0x00007fe6ab35e000)
	/lib64/ld-linux-x86-64.so.2 (0x00007fe6ad30f000)
	libGLX.so.0 => /lib64/libGLX.so.0 (0x00007fe6ab328000)
	libX11.so.6 => /lib64/libX11.so.6 (0x00007fe6ab1e1000)
	libXext.so.6 => /lib64/libXext.so.6 (0x00007fe6ab1cc000)
	libGLdispatch.so.0 => /lib64/libGLdispatch.so.0 (0x00007fe6ab113000)
	libfreetype.so.6 => /lib64/libfreetype.so.6 (0x00007fe6ab051000)
	libgraphite2.so.3 => /lib64/libgraphite2.so.3 (0x00007fe6ab02d000)
	librt.so.1 => /lib64/librt.so.1 (0x00007fe6ab020000)
	liblzma.so.5 => /lib64/liblzma.so.5 (0x00007fe6aaff6000)
	liblz4.so.1 => /lib64/liblz4.so.1 (0x00007fe6aafd5000)
	libgcrypt.so.20 => /lib64/libgcrypt.so.20 (0x00007fe6aaeb4000)
	libicudata.so.65 => /lib64/libicudata.so.65 (0x00007fe6a9401000)
	libpcre.so.1 => /lib64/libpcre.so.1 (0x00007fe6a9388000)
	libxcb.so.1 => /lib64/libxcb.so.1 (0x00007fe6a935a000)
	libbz2.so.1 => /lib64/libbz2.so.1 (0x00007fe6a9347000)
	libgpg-error.so.0 => /lib64/libgpg-error.so.0 (0x00007fe6a9323000)
	libXau.so.6 => /lib64/libXau.so.6 (0x00007fe6a931d000)
ldd 2048-Qt5 | wc -l
	36
```

### 2048-Qt4

```
ldd 2048-Qt4
	linux-vdso.so.1 (0x00007ffea8372000)
	libQtGui.so.4 => /lib64/libQtGui.so.4 (0x00007f1c7ac4d000)
	libQtCore.so.4 => /lib64/libQtCore.so.4 (0x00007f1c7a935000)
	libstdc++.so.6 => /lib64/libstdc++.so.6 (0x00007f1c7a745000)
	libm.so.6 => /lib64/libm.so.6 (0x00007f1c7a5ff000)
	libgcc_s.so.1 => /lib64/libgcc_s.so.1 (0x00007f1c7a5e4000)
	libc.so.6 => /lib64/libc.so.6 (0x00007f1c7a41a000)
	libpthread.so.0 => /lib64/libpthread.so.0 (0x00007f1c7a3f6000)
	libglib-2.0.so.0 => /lib64/libglib-2.0.so.0 (0x00007f1c7a2cb000)
	libpng16.so.16 => /lib64/libpng16.so.16 (0x00007f1c7a294000)
	libz.so.1 => /lib64/libz.so.1 (0x00007f1c7a27a000)
	libfreetype.so.6 => /lib64/libfreetype.so.6 (0x00007f1c7a1b8000)
	libgobject-2.0.so.0 => /lib64/libgobject-2.0.so.0 (0x00007f1c7a15f000)
	libSM.so.6 => /lib64/libSM.so.6 (0x00007f1c7a152000)
	libICE.so.6 => /lib64/libICE.so.6 (0x00007f1c7a134000)
	libXi.so.6 => /lib64/libXi.so.6 (0x00007f1c7a122000)
	libXrender.so.1 => /lib64/libXrender.so.1 (0x00007f1c7a115000)
	libXrandr.so.2 => /lib64/libXrandr.so.2 (0x00007f1c7a108000)
	libXfixes.so.3 => /lib64/libXfixes.so.3 (0x00007f1c7a0ff000)
	libXcursor.so.1 => /lib64/libXcursor.so.1 (0x00007f1c7a0f0000)
	libXinerama.so.1 => /lib64/libXinerama.so.1 (0x00007f1c7a0eb000)
	libfontconfig.so.1 => /lib64/libfontconfig.so.1 (0x00007f1c7a0a0000)
	libXext.so.6 => /lib64/libXext.so.6 (0x00007f1c7a08b000)
	libX11.so.6 => /lib64/libX11.so.6 (0x00007f1c79f44000)
	libdl.so.2 => /lib64/libdl.so.2 (0x00007f1c79f3d000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f1c7b843000)
	libpcre.so.1 => /lib64/libpcre.so.1 (0x00007f1c79ec2000)
	libbz2.so.1 => /lib64/libbz2.so.1 (0x00007f1c79eaf000)
	libffi.so.6 => /lib64/libffi.so.6 (0x00007f1c79ea4000)
	libuuid.so.1 => /lib64/libuuid.so.1 (0x00007f1c79e9b000)
	libexpat.so.1 => /lib64/libexpat.so.1 (0x00007f1c79e6c000)
	libxcb.so.1 => /lib64/libxcb.so.1 (0x00007f1c79e3e000)
	libXau.so.6 => /lib64/libXau.so.6 (0x00007f1c79e38000)
ldd 2048-Qt4 | wc -l
	33
```

### 2048-Qt3

```
ldd 2048-Qt3
	linux-vdso.so.1 (0x00007ffd62de7000)
	libqt-mt.so.3 => /usr/lib64/qt-3.3/lib/libqt-mt.so.3 (0x00007fd02c2aa000)
	libstdc++.so.6 => /lib64/libstdc++.so.6 (0x00007fd02c094000)
	libm.so.6 => /lib64/libm.so.6 (0x00007fd02bf4e000)
	libgcc_s.so.1 => /lib64/libgcc_s.so.1 (0x00007fd02bf33000)
	libc.so.6 => /lib64/libc.so.6 (0x00007fd02bd69000)
	libmng.so.2 => /lib64/libmng.so.2 (0x00007fd02bcf4000)
	libjpeg.so.62 => /lib64/libjpeg.so.62 (0x00007fd02bc6d000)
	libpng16.so.16 => /lib64/libpng16.so.16 (0x00007fd02bc36000)
	libz.so.1 => /lib64/libz.so.1 (0x00007fd02bc1c000)
	libXi.so.6 => /lib64/libXi.so.6 (0x00007fd02bc0a000)
	libXrender.so.1 => /lib64/libXrender.so.1 (0x00007fd02bbfd000)
	libXrandr.so.2 => /lib64/libXrandr.so.2 (0x00007fd02bbf0000)
	libXcursor.so.1 => /lib64/libXcursor.so.1 (0x00007fd02bbe1000)
	libXinerama.so.1 => /lib64/libXinerama.so.1 (0x00007fd02bbdc000)
	libXft.so.2 => /lib64/libXft.so.2 (0x00007fd02bbc2000)
	libfreetype.so.6 => /lib64/libfreetype.so.6 (0x00007fd02bb00000)
	libfontconfig.so.1 => /lib64/libfontconfig.so.1 (0x00007fd02bab5000)
	libXext.so.6 => /lib64/libXext.so.6 (0x00007fd02baa0000)
	libX11.so.6 => /lib64/libX11.so.6 (0x00007fd02b957000)
	libSM.so.6 => /lib64/libSM.so.6 (0x00007fd02b94c000)
	libICE.so.6 => /lib64/libICE.so.6 (0x00007fd02b92e000)
	libdl.so.2 => /lib64/libdl.so.2 (0x00007fd02b927000)
	libpthread.so.0 => /lib64/libpthread.so.0 (0x00007fd02b905000)
	/lib64/ld-linux-x86-64.so.2 (0x00007fd02cba6000)
	liblcms2.so.2 => /lib64/liblcms2.so.2 (0x00007fd02b8a5000)
	libXfixes.so.3 => /lib64/libXfixes.so.3 (0x00007fd02b89a000)
	libbz2.so.1 => /lib64/libbz2.so.1 (0x00007fd02b887000)
	libexpat.so.1 => /lib64/libexpat.so.1 (0x00007fd02b858000)
	libxcb.so.1 => /lib64/libxcb.so.1 (0x00007fd02b82c000)
	libuuid.so.1 => /lib64/libuuid.so.1 (0x00007fd02b823000)
	libXau.so.6 => /lib64/libXau.so.6 (0x00007fd02b81b000)
ldd 2048-Qt3 | wc -l
	32
```

### 2048-Qt2

```
ldd 2048-Qt2
	linux-vdso.so.1 (0x00007fff0c2eb000)
	libqt2.so.2 => /home/exl/Projects/qt2/src/libqt2.so.2 (0x00007f4be7159000)
	libstdc++.so.6 => /lib64/libstdc++.so.6 (0x00007f4be6f43000)
	libm.so.6 => /lib64/libm.so.6 (0x00007f4be6dfd000)
	libgcc_s.so.1 => /lib64/libgcc_s.so.1 (0x00007f4be6de2000)
	libc.so.6 => /lib64/libc.so.6 (0x00007f4be6c18000)
	libfontconfig.so.1 => /lib64/libfontconfig.so.1 (0x00007f4be6bcd000)
	libSM.so.6 => /lib64/libSM.so.6 (0x00007f4be6bc0000)
	libICE.so.6 => /lib64/libICE.so.6 (0x00007f4be6ba2000)
	libX11.so.6 => /lib64/libX11.so.6 (0x00007f4be6a5b000)
	libXext.so.6 => /lib64/libXext.so.6 (0x00007f4be6a46000)
	libjpeg.so.62 => /lib64/libjpeg.so.62 (0x00007f4be69c1000)
	libXft.so.2 => /lib64/libXft.so.2 (0x00007f4be69a7000)
	libmng.so.2 => /lib64/libmng.so.2 (0x00007f4be6930000)
	libGL.so.1 => /lib64/libGL.so.1 (0x00007f4be68a8000)
	libpng16.so.16 => /lib64/libpng16.so.16 (0x00007f4be6871000)
	libz.so.1 => /lib64/libz.so.1 (0x00007f4be6857000)
	libXmu.so.6 => /lib64/libXmu.so.6 (0x00007f4be683a000)
	libpthread.so.0 => /lib64/libpthread.so.0 (0x00007f4be6818000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f4be776d000)
	libfreetype.so.6 => /lib64/libfreetype.so.6 (0x00007f4be6754000)
	libexpat.so.1 => /lib64/libexpat.so.1 (0x00007f4be6725000)
	libuuid.so.1 => /lib64/libuuid.so.1 (0x00007f4be671c000)
	libxcb.so.1 => /lib64/libxcb.so.1 (0x00007f4be66f0000)
	libdl.so.2 => /lib64/libdl.so.2 (0x00007f4be66e9000)
	libXrender.so.1 => /lib64/libXrender.so.1 (0x00007f4be66dc000)
	liblcms2.so.2 => /lib64/liblcms2.so.2 (0x00007f4be667a000)
	libGLX.so.0 => /lib64/libGLX.so.0 (0x00007f4be6646000)
	libGLdispatch.so.0 => /lib64/libGLdispatch.so.0 (0x00007f4be658d000)
	libXt.so.6 => /lib64/libXt.so.6 (0x00007f4be6520000)
	libbz2.so.1 => /lib64/libbz2.so.1 (0x00007f4be650d000)
	libXau.so.6 => /lib64/libXau.so.6 (0x00007f4be6505000)
ldd 2048-Qt2 | wc -l
	32
```

### 2048-Qt1

```
ldd 2048-Qt1
	linux-vdso.so.1 (0x00007ffe55797000)
	libqt1.so.1 => /home/exl/Projects/qt1/src/libqt1.so.1 (0x00007fe40439f000)
	libstdc++.so.6 => /lib64/libstdc++.so.6 (0x00007fe404189000)
	libm.so.6 => /lib64/libm.so.6 (0x00007fe404043000)
	libgcc_s.so.1 => /lib64/libgcc_s.so.1 (0x00007fe404028000)
	libc.so.6 => /lib64/libc.so.6 (0x00007fe403e5e000)
	libX11.so.6 => /lib64/libX11.so.6 (0x00007fe403d17000)
	libXext.so.6 => /lib64/libXext.so.6 (0x00007fe403d00000)
	/lib64/ld-linux-x86-64.so.2 (0x00007fe40457f000)
	libxcb.so.1 => /lib64/libxcb.so.1 (0x00007fe403cd4000)
	libdl.so.2 => /lib64/libdl.so.2 (0x00007fe403ccd000)
	libXau.so.6 => /lib64/libXau.so.6 (0x00007fe403cc7000)
ldd 2048-Qt1 | wc -l
	12
```

### 2048-Gtk3

```
ldd 2048-Gtk3
	linux-vdso.so.1 (0x00007fff191af000)
	libgtk-3.so.0 => /lib64/libgtk-3.so.0 (0x00007f9e5d363000)
	libgdk-3.so.0 => /lib64/libgdk-3.so.0 (0x00007f9e5d25b000)
	libatk-1.0.so.0 => /lib64/libatk-1.0.so.0 (0x00007f9e5d231000)
	libgio-2.0.so.0 => /lib64/libgio-2.0.so.0 (0x00007f9e5d04d000)
	libpangocairo-1.0.so.0 => /lib64/libpangocairo-1.0.so.0 (0x00007f9e5d03b000)
	libgdk_pixbuf-2.0.so.0 => /lib64/libgdk_pixbuf-2.0.so.0 (0x00007f9e5d010000)
	libcairo-gobject.so.2 => /lib64/libcairo-gobject.so.2 (0x00007f9e5d002000)
	libpango-1.0.so.0 => /lib64/libpango-1.0.so.0 (0x00007f9e5cfb3000)
	libcairo.so.2 => /lib64/libcairo.so.2 (0x00007f9e5ce8b000)
	libgobject-2.0.so.0 => /lib64/libgobject-2.0.so.0 (0x00007f9e5ce32000)
	libglib-2.0.so.0 => /lib64/libglib-2.0.so.0 (0x00007f9e5cd07000)
	libc.so.6 => /lib64/libc.so.6 (0x00007f9e5cb3d000)
	libgmodule-2.0.so.0 => /lib64/libgmodule-2.0.so.0 (0x00007f9e5cb35000)
	libX11.so.6 => /lib64/libX11.so.6 (0x00007f9e5c9ee000)
	libXi.so.6 => /lib64/libXi.so.6 (0x00007f9e5c9dc000)
	libXfixes.so.3 => /lib64/libXfixes.so.3 (0x00007f9e5c9d3000)
	libatk-bridge-2.0.so.0 => /lib64/libatk-bridge-2.0.so.0 (0x00007f9e5c99a000)
	libwayland-client.so.0 => /lib64/libwayland-client.so.0 (0x00007f9e5c989000)
	libepoxy.so.0 => /lib64/libepoxy.so.0 (0x00007f9e5c854000)
	libfribidi.so.0 => /lib64/libfribidi.so.0 (0x00007f9e5c835000)
	libm.so.6 => /lib64/libm.so.6 (0x00007f9e5c6ef000)
	libpangoft2-1.0.so.0 => /lib64/libpangoft2-1.0.so.0 (0x00007f9e5c6d6000)
	libharfbuzz.so.0 => /lib64/libharfbuzz.so.0 (0x00007f9e5c5f4000)
	libfontconfig.so.1 => /lib64/libfontconfig.so.1 (0x00007f9e5c5a9000)
	libfreetype.so.6 => /lib64/libfreetype.so.6 (0x00007f9e5c4e5000)
	libpthread.so.0 => /lib64/libpthread.so.0 (0x00007f9e5c4c3000)
	libXinerama.so.1 => /lib64/libXinerama.so.1 (0x00007f9e5c4be000)
	libXrandr.so.2 => /lib64/libXrandr.so.2 (0x00007f9e5c4b1000)
	libXcursor.so.1 => /lib64/libXcursor.so.1 (0x00007f9e5c4a4000)
	libXcomposite.so.1 => /lib64/libXcomposite.so.1 (0x00007f9e5c49f000)
	libXdamage.so.1 => /lib64/libXdamage.so.1 (0x00007f9e5c498000)
	libxkbcommon.so.0 => /lib64/libxkbcommon.so.0 (0x00007f9e5c455000)
	libwayland-cursor.so.0 => /lib64/libwayland-cursor.so.0 (0x00007f9e5c44a000)
	libwayland-egl.so.1 => /lib64/libwayland-egl.so.1 (0x00007f9e5c445000)
	libXext.so.6 => /lib64/libXext.so.6 (0x00007f9e5c430000)
	librt.so.1 => /lib64/librt.so.1 (0x00007f9e5c425000)
	libz.so.1 => /lib64/libz.so.1 (0x00007f9e5c409000)
	libmount.so.1 => /lib64/libmount.so.1 (0x00007f9e5c3a9000)
	libselinux.so.1 => /lib64/libselinux.so.1 (0x00007f9e5c37c000)
	libresolv.so.2 => /lib64/libresolv.so.2 (0x00007f9e5c362000)
	libpng16.so.16 => /lib64/libpng16.so.16 (0x00007f9e5c32b000)
	libpixman-1.so.0 => /lib64/libpixman-1.so.0 (0x00007f9e5c27f000)
	libxcb-shm.so.0 => /lib64/libxcb-shm.so.0 (0x00007f9e5c278000)
	libxcb.so.1 => /lib64/libxcb.so.1 (0x00007f9e5c24c000)
	libxcb-render.so.0 => /lib64/libxcb-render.so.0 (0x00007f9e5c23c000)
	libXrender.so.1 => /lib64/libXrender.so.1 (0x00007f9e5c22f000)
	libthai.so.0 => /lib64/libthai.so.0 (0x00007f9e5c223000)
	libffi.so.6 => /lib64/libffi.so.6 (0x00007f9e5c216000)
	libpcre.so.1 => /lib64/libpcre.so.1 (0x00007f9e5c19d000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f9e5db58000)
	libdl.so.2 => /lib64/libdl.so.2 (0x00007f9e5c196000)
	libdbus-1.so.3 => /lib64/libdbus-1.so.3 (0x00007f9e5c13f000)
	libatspi.so.0 => /lib64/libatspi.so.0 (0x00007f9e5c106000)
	libgraphite2.so.3 => /lib64/libgraphite2.so.3 (0x00007f9e5c0e0000)
	libexpat.so.1 => /lib64/libexpat.so.1 (0x00007f9e5c0b1000)
	libbz2.so.1 => /lib64/libbz2.so.1 (0x00007f9e5c09e000)
	libblkid.so.1 => /lib64/libblkid.so.1 (0x00007f9e5c04b000)
	libpcre2-8.so.0 => /lib64/libpcre2-8.so.0 (0x00007f9e5bfb2000)
	libXau.so.6 => /lib64/libXau.so.6 (0x00007f9e5bfaa000)
	libdatrie.so.1 => /lib64/libdatrie.so.1 (0x00007f9e5bfa0000)
	libsystemd.so.0 => /lib64/libsystemd.so.0 (0x00007f9e5bee9000)
	liblzma.so.5 => /lib64/liblzma.so.5 (0x00007f9e5bebf000)
	liblz4.so.1 => /lib64/liblz4.so.1 (0x00007f9e5be9e000)
	libgcrypt.so.20 => /lib64/libgcrypt.so.20 (0x00007f9e5bd7b000)
	libgcc_s.so.1 => /lib64/libgcc_s.so.1 (0x00007f9e5bd60000)
	libgpg-error.so.0 => /lib64/libgpg-error.so.0 (0x00007f9e5bd3c000)
ldd 2048-Gtk3 | wc -l
	67
```

### 2048-Gtk2

```
ldd 2048-Gtk2
	linux-vdso.so.1 (0x00007ffe06b8a000)
	libglib-2.0.so.0 => /lib64/libglib-2.0.so.0 (0x00007f4bc7e31000)
	libgobject-2.0.so.0 => /lib64/libgobject-2.0.so.0 (0x00007f4bc7dd8000)
	libatk-1.0.so.0 => /lib64/libatk-1.0.so.0 (0x00007f4bc7dae000)
	libgio-2.0.so.0 => /lib64/libgio-2.0.so.0 (0x00007f4bc7bca000)
	libgthread-2.0.so.0 => /lib64/libgthread-2.0.so.0 (0x00007f4bc7bc5000)
	libgmodule-2.0.so.0 => /lib64/libgmodule-2.0.so.0 (0x00007f4bc7bbf000)
	libgdk_pixbuf-2.0.so.0 => /lib64/libgdk_pixbuf-2.0.so.0 (0x00007f4bc7b92000)
	libcairo.so.2 => /lib64/libcairo.so.2 (0x00007f4bc7a6a000)
	libharfbuzz.so.0 => /lib64/libharfbuzz.so.0 (0x00007f4bc7988000)
	libpango-1.0.so.0 => /lib64/libpango-1.0.so.0 (0x00007f4bc7939000)
	libpangocairo-1.0.so.0 => /lib64/libpangocairo-1.0.so.0 (0x00007f4bc7927000)
	libpangoft2-1.0.so.0 => /lib64/libpangoft2-1.0.so.0 (0x00007f4bc790e000)
	libpangoxft-1.0.so.0 => /lib64/libpangoxft-1.0.so.0 (0x00007f4bc7900000)
	libgdk-x11-2.0.so.0 => /lib64/libgdk-x11-2.0.so.0 (0x00007f4bc7830000)
	libgtk-x11-2.0.so.0 => /lib64/libgtk-x11-2.0.so.0 (0x00007f4bc737d000)
	libc.so.6 => /lib64/libc.so.6 (0x00007f4bc71b3000)
	libpcre.so.1 => /lib64/libpcre.so.1 (0x00007f4bc713a000)
	libpthread.so.0 => /lib64/libpthread.so.0 (0x00007f4bc7118000)
	libffi.so.6 => /lib64/libffi.so.6 (0x00007f4bc710b000)
	libz.so.1 => /lib64/libz.so.1 (0x00007f4bc70f1000)
	libmount.so.1 => /lib64/libmount.so.1 (0x00007f4bc7091000)
	libselinux.so.1 => /lib64/libselinux.so.1 (0x00007f4bc7064000)
	libresolv.so.2 => /lib64/libresolv.so.2 (0x00007f4bc704a000)
	libdl.so.2 => /lib64/libdl.so.2 (0x00007f4bc7043000)
	libm.so.6 => /lib64/libm.so.6 (0x00007f4bc6efb000)
	libpng16.so.16 => /lib64/libpng16.so.16 (0x00007f4bc6ec4000)
	libpixman-1.so.0 => /lib64/libpixman-1.so.0 (0x00007f4bc6e18000)
	libfontconfig.so.1 => /lib64/libfontconfig.so.1 (0x00007f4bc6dcd000)
	libfreetype.so.6 => /lib64/libfreetype.so.6 (0x00007f4bc6d0b000)
	libxcb-shm.so.0 => /lib64/libxcb-shm.so.0 (0x00007f4bc6d06000)
	libxcb.so.1 => /lib64/libxcb.so.1 (0x00007f4bc6cd8000)
	libxcb-render.so.0 => /lib64/libxcb-render.so.0 (0x00007f4bc6cc8000)
	libXrender.so.1 => /lib64/libXrender.so.1 (0x00007f4bc6cbb000)
	libX11.so.6 => /lib64/libX11.so.6 (0x00007f4bc6b74000)
	libXext.so.6 => /lib64/libXext.so.6 (0x00007f4bc6b5f000)
	librt.so.1 => /lib64/librt.so.1 (0x00007f4bc6b54000)
	libgraphite2.so.3 => /lib64/libgraphite2.so.3 (0x00007f4bc6b2e000)
	libfribidi.so.0 => /lib64/libfribidi.so.0 (0x00007f4bc6b0f000)
	libthai.so.0 => /lib64/libthai.so.0 (0x00007f4bc6b03000)
	libXft.so.2 => /lib64/libXft.so.2 (0x00007f4bc6ae9000)
	libXinerama.so.1 => /lib64/libXinerama.so.1 (0x00007f4bc6ae4000)
	libXi.so.6 => /lib64/libXi.so.6 (0x00007f4bc6ad0000)
	libXrandr.so.2 => /lib64/libXrandr.so.2 (0x00007f4bc6ac3000)
	libXcursor.so.1 => /lib64/libXcursor.so.1 (0x00007f4bc6ab6000)
	libXcomposite.so.1 => /lib64/libXcomposite.so.1 (0x00007f4bc6ab1000)
	libXdamage.so.1 => /lib64/libXdamage.so.1 (0x00007f4bc6aac000)
	libXfixes.so.3 => /lib64/libXfixes.so.3 (0x00007f4bc6aa3000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f4bc7f84000)
	libblkid.so.1 => /lib64/libblkid.so.1 (0x00007f4bc6a4e000)
	libpcre2-8.so.0 => /lib64/libpcre2-8.so.0 (0x00007f4bc69b5000)
	libexpat.so.1 => /lib64/libexpat.so.1 (0x00007f4bc6986000)
	libbz2.so.1 => /lib64/libbz2.so.1 (0x00007f4bc6973000)
	libXau.so.6 => /lib64/libXau.so.6 (0x00007f4bc696d000)
	libdatrie.so.1 => /lib64/libdatrie.so.1 (0x00007f4bc6961000)
ldd 2048-Gtk2 | wc -l
	55
```

### 2048-Gtk1

```
ldd 2048-Gtk1
	linux-vdso.so.1 (0x00007ffd49181000)
	libgtk-1.2.so.0 => /lib64/libgtk-1.2.so.0 (0x00007fc2855f1000)
	libgdk-1.2.so.0 => /lib64/libgdk-1.2.so.0 (0x00007fc2855ab000)
	libXi.so.6 => /lib64/libXi.so.6 (0x00007fc285599000)
	libXext.so.6 => /lib64/libXext.so.6 (0x00007fc285584000)
	libX11.so.6 => /lib64/libX11.so.6 (0x00007fc28543d000)
	libm.so.6 => /lib64/libm.so.6 (0x00007fc2852f7000)
	libglib-1.2.so.0 => /lib64/libglib-1.2.so.0 (0x00007fc2852c3000)
	libc.so.6 => /lib64/libc.so.6 (0x00007fc2850f9000)
	libgmodule-1.2.so.0 => /lib64/libgmodule-1.2.so.0 (0x00007fc2850f3000)
	libxcb.so.1 => /lib64/libxcb.so.1 (0x00007fc2850c7000)
	libdl.so.2 => /lib64/libdl.so.2 (0x00007fc2850c0000)
	/lib64/ld-linux-x86-64.so.2 (0x00007fc2857a7000)
	libXau.so.6 => /lib64/libXau.so.6 (0x00007fc2850b8000)
ldd 2048-Gtk1 | wc -l
	14
```

### 2048-Motif

```
ldd 2048-Motif
	linux-vdso.so.1 (0x00007ffeb43f6000)
	libXm.so.4 => /lib64/libXm.so.4 (0x00007f327fe50000)
	libXt.so.6 => /lib64/libXt.so.6 (0x00007f327fde3000)
	libX11.so.6 => /lib64/libX11.so.6 (0x00007f327fc9c000)
	libc.so.6 => /lib64/libc.so.6 (0x00007f327fad2000)
	libXmu.so.6 => /lib64/libXmu.so.6 (0x00007f327fab5000)
	libXext.so.6 => /lib64/libXext.so.6 (0x00007f327faa0000)
	libXp.so.6 => /lib64/libXp.so.6 (0x00007f327fa92000)
	libXft.so.2 => /lib64/libXft.so.2 (0x00007f327fa78000)
	libjpeg.so.62 => /lib64/libjpeg.so.62 (0x00007f327f9f3000)
	libpng16.so.16 => /lib64/libpng16.so.16 (0x00007f327f9bc000)
	libSM.so.6 => /lib64/libSM.so.6 (0x00007f327f9b1000)
	libICE.so.6 => /lib64/libICE.so.6 (0x00007f327f993000)
	libxcb.so.1 => /lib64/libxcb.so.1 (0x00007f327f965000)
	libdl.so.2 => /lib64/libdl.so.2 (0x00007f327f95e000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f3280161000)
	libXau.so.6 => /lib64/libXau.so.6 (0x00007f327f958000)
	libfontconfig.so.1 => /lib64/libfontconfig.so.1 (0x00007f327f90d000)
	libfreetype.so.6 => /lib64/libfreetype.so.6 (0x00007f327f84b000)
	libXrender.so.1 => /lib64/libXrender.so.1 (0x00007f327f83e000)
	libz.so.1 => /lib64/libz.so.1 (0x00007f327f822000)
	libm.so.6 => /lib64/libm.so.6 (0x00007f327f6dc000)
	libuuid.so.1 => /lib64/libuuid.so.1 (0x00007f327f6d3000)
	libexpat.so.1 => /lib64/libexpat.so.1 (0x00007f327f6a4000)
	libpthread.so.0 => /lib64/libpthread.so.0 (0x00007f327f682000)
	libbz2.so.1 => /lib64/libbz2.so.1 (0x00007f327f66f000)
ldd 2048-Motif | wc -l
	26
```

### 2048-Xaw

```
ldd 2048-Xaw
	linux-vdso.so.1 (0x00007ffd0bb2c000)
	libXaw.so.7 => /lib64/libXaw.so.7 (0x00007f66d0458000)
	libXt.so.6 => /lib64/libXt.so.6 (0x00007f66d03eb000)
	libX11.so.6 => /lib64/libX11.so.6 (0x00007f66d02a4000)
	libc.so.6 => /lib64/libc.so.6 (0x00007f66d00da000)
	libXext.so.6 => /lib64/libXext.so.6 (0x00007f66d00c5000)
	libXmu.so.6 => /lib64/libXmu.so.6 (0x00007f66d00a8000)
	libXpm.so.4 => /lib64/libXpm.so.4 (0x00007f66d0091000)
	libSM.so.6 => /lib64/libSM.so.6 (0x00007f66d0086000)
	libICE.so.6 => /lib64/libICE.so.6 (0x00007f66d0068000)
	libxcb.so.1 => /lib64/libxcb.so.1 (0x00007f66d003c000)
	libdl.so.2 => /lib64/libdl.so.2 (0x00007f66d0035000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f66d04ea000)
	libuuid.so.1 => /lib64/libuuid.so.1 (0x00007f66d002c000)
	libXau.so.6 => /lib64/libXau.so.6 (0x00007f66d0024000)
ldd 2048-Xaw | wc -l
	15
```

### 2048-Xlib

```
ldd 2048-Xlib
	linux-vdso.so.1 (0x00007ffc653f0000)
	libX11.so.6 => /lib64/libX11.so.6 (0x00007fe456934000)
	libc.so.6 => /lib64/libc.so.6 (0x00007fe45676a000)
	libxcb.so.1 => /lib64/libxcb.so.1 (0x00007fe45673e000)
	libdl.so.2 => /lib64/libdl.so.2 (0x00007fe456737000)
	/lib64/ld-linux-x86-64.so.2 (0x00007fe456aa3000)
	libXau.so.6 => /lib64/libXau.so.6 (0x00007fe456731000)
ldd 2048-Xlib | wc -l
	7
```

### 2048-Xcb

```
ldd 2048-Xcb
	linux-vdso.so.1 (0x00007ffe28c30000)
	libxcb.so.1 => /lib64/libxcb.so.1 (0x00007f93c90b5000)
	libxcb-keysyms.so.1 => /lib64/libxcb-keysyms.so.1 (0x00007f93c90b0000)
	libxcb-icccm.so.4 => /lib64/libxcb-icccm.so.4 (0x00007f93c90a9000)
	libc.so.6 => /lib64/libc.so.6 (0x00007f93c8edf000)
	libXau.so.6 => /lib64/libXau.so.6 (0x00007f93c8ed9000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f93c9109000)
ldd 2048-Xcb | wc -l
	7
```

### 2048-MotoMAGX_Z6

```
/opt/toolchains/motomagx/arm-eabi/bin/arm-linux-gnueabi-objdump -x 2048-MotoMAGX_Z6 | grep NEEDED
  NEEDED      libqte-mt.so.2
  NEEDED      libezxpm.so.2
  NEEDED      libezxappbase.so.1
  NEEDED      liblighting.so.1
  NEEDED      libstdc++.so.6
  NEEDED      libm.so.6
  NEEDED      libgcc_s.so.1
  NEEDED      libc.so.6
```

### 2048-MotoMAGX_V8

```
/opt/toolchains/motomagx/arm-eabi/bin/arm-linux-gnueabi-objdump -x 2048-MotoMAGX_V8 | grep NEEDED
  NEEDED      libqte-mt.so.2
  NEEDED      libezxpm.so.2
  NEEDED      libezxappbase.so.1
  NEEDED      libstdc++.so.6
  NEEDED      libm.so.6
  NEEDED      libgcc_s.so.1
  NEEDED      libc.so.6
```

### 2048-MotoMAGX_Z6W

```
/opt/toolchains/motomagx/arm-eabi/bin/arm-linux-gnueabi-objdump -x 2048-MotoMAGX_Z6W | grep NEEDED
  NEEDED      libqte-mt.so.2
  NEEDED      libezxappbase.so.1
  NEEDED      libstdc++.so.6
  NEEDED      libm.so.6
  NEEDED      libgcc_s.so.1
  NEEDED      libc.so.6
```

### 2048-MotoMAGX_U9

```sh
/opt/toolchains/motomagx/arm-eabi/bin/arm-linux-gnueabi-objdump -x 2048-MotoMAGX_U9 | grep NEEDED
  NEEDED      libqte-mt.so.2
  NEEDED      libezxappbase.so.1
  NEEDED      liblighting.so.1
  NEEDED      libstdc++.so.6
  NEEDED      libm.so.6
  NEEDED      libgcc_s.so.1
  NEEDED      libc.so.6
```

### 2048-MotoMAGX_ZN5

```
/opt/toolchains/motomagx/arm-eabi/bin/arm-linux-gnueabi-objdump -x 2048-MotoMAGX_ZN5 | grep NEEDED
  NEEDED      libqte-mt.so.2
  NEEDED      libezxappbase.so.1
  NEEDED      libstdc++.so.6
  NEEDED      libm.so.6
  NEEDED      libgcc_s.so.1
  NEEDED      libc.so.6
```

### 2048-MotoMAGX_E8

```
/opt/toolchains/motomagx/arm-eabi/bin/arm-linux-gnueabi-objdump -x 2048-MotoMAGX_ZN5 | grep NEEDED
  NEEDED      libqte-mt.so.2
  NEEDED      libezxappbase.so.1
  NEEDED      libstdc++.so.6
  NEEDED      libm.so.6
  NEEDED      libgcc_s.so.1
  NEEDED      libc.so.6
```

### 2048-MotoMAGX_EM30

```
/opt/toolchains/motomagx/arm-eabi/bin/arm-linux-gnueabi-objdump -x 2048-MotoMAGX_EM30 | grep NEEDED
  NEEDED      libqte-mt.so.2
  NEEDED      libezxappbase.so.1
  NEEDED      libstdc++.so.6
  NEEDED      libm.so.6
  NEEDED      libgcc_s.so.1
  NEEDED      libc.so.6
```

### 2048-MotoMAGX_VE66

```
/opt/toolchains/motomagx/arm-eabi/bin/arm-linux-gnueabi-objdump -x 2048-MotoMAGX_VE66 | grep NEEDED
  NEEDED      libqte-mt.so.2
  NEEDED      libezxappbase.so.1
  NEEDED      libstdc++.so.6
  NEEDED      libm.so.6
  NEEDED      libgcc_s.so.1
  NEEDED      libc.so.6
```

### 2048-MotoMAGX_EM35

```
/opt/toolchains/motomagx/arm-eabi/bin/arm-linux-gnueabi-objdump -x 2048-MotoMAGX_EM35 | grep NEEDED
  NEEDED      libqte-mt.so.2
  NEEDED      libezxappbase.so.1
  NEEDED      libstdc++.so.6
  NEEDED      libm.so.6
  NEEDED      libgcc_s.so.1
  NEEDED      libc.so.6
```

### 2048-NeXTSTEP

Motorola 68040 version:

```
otool -L 2048-NeXTSTEP
2048-NeXTSTEP:
	/usr/shlib/libFoundation_s.E.shlib (minor version 1)
	/usr/shlib/libNeXT_s.C.shlib (minor version 57)
	/usr/shlib/libsys_s.B.shlib (minor version 55)
```

Intel 80486 (i486) version:

```
otool -L 2048-NeXTSTEP
2048-NeXTSTEP:
	/usr/shlib/libFoundation_s.E.shlib (minor version 1)
	/usr/shlib/libNeXT_s.C.shlib (minor version 89)
	/usr/shlib/libsys_s.B.shlib (minor version 62)
```

### 2048-Serenity

Static executable, linked with `-lgui -lgfx -lcore -lipc` libraries.

### 2048-Photon

```
ldd 2048-Photon
	libAp.so.3 => /usr/lib/libAp.so.3 (0xb8200000)
	libph.so.3 => /usr/lib/libph.so.3 (0xb8211000)
	libm.so.2 => /lib/libm.so.2 (0xb8320000)
	libc.so.3 => /usr/lib/ldqnx.so.2 (0xb0300000)
	libfont.so.1 => /lib/libfont.so.1 (0xb8353000)
ldd 2048-Photon | wc -l
	5
```

### 2048-JUCE

```
ldd 2048-JUCE
	linux-vdso.so.1 (0x00007ffc3c5d4000)
	libfreetype.so.6 => /lib64/libfreetype.so.6 (0x00007f8d911f9000)
	libcurl.so.4 => /lib64/libcurl.so.4 (0x00007f8d91165000)
	librt.so.1 => /lib64/librt.so.1 (0x00007f8d9115a000)
	libdl.so.2 => /lib64/libdl.so.2 (0x00007f8d91153000)
	libpthread.so.0 => /lib64/libpthread.so.0 (0x00007f8d91131000)
	libstdc++.so.6 => /lib64/libstdc++.so.6 (0x00007f8d90f41000)
	libm.so.6 => /lib64/libm.so.6 (0x00007f8d90df9000)
	libgcc_s.so.1 => /lib64/libgcc_s.so.1 (0x00007f8d90dde000)
	libc.so.6 => /lib64/libc.so.6 (0x00007f8d90c14000)
	libbz2.so.1 => /lib64/libbz2.so.1 (0x00007f8d90c01000)
	libpng16.so.16 => /lib64/libpng16.so.16 (0x00007f8d90bca000)
	libz.so.1 => /lib64/libz.so.1 (0x00007f8d90bb0000)
	libnghttp2.so.14 => /lib64/libnghttp2.so.14 (0x00007f8d90b82000)
	libidn2.so.0 => /lib64/libidn2.so.0 (0x00007f8d90b60000)
	libssh.so.4 => /lib64/libssh.so.4 (0x00007f8d90aee000)
	libpsl.so.5 => /lib64/libpsl.so.5 (0x00007f8d90adb000)
	libssl.so.1.1 => /lib64/libssl.so.1.1 (0x00007f8d90a44000)
	libcrypto.so.1.1 => /lib64/libcrypto.so.1.1 (0x00007f8d90757000)
	libgssapi_krb5.so.2 => /lib64/libgssapi_krb5.so.2 (0x00007f8d906fe000)
	libkrb5.so.3 => /lib64/libkrb5.so.3 (0x00007f8d90613000)
	libk5crypto.so.3 => /lib64/libk5crypto.so.3 (0x00007f8d905fa000)
	libcom_err.so.2 => /lib64/libcom_err.so.2 (0x00007f8d905f3000)
	libldap-2.4.so.2 => /lib64/libldap-2.4.so.2 (0x00007f8d905a1000)
	liblber-2.4.so.2 => /lib64/liblber-2.4.so.2 (0x00007f8d9058f000)
	libbrotlidec.so.1 => /lib64/libbrotlidec.so.1 (0x00007f8d9057e000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f8d912eb000)
	libunistring.so.2 => /lib64/libunistring.so.2 (0x00007f8d903f9000)
	libkrb5support.so.0 => /lib64/libkrb5support.so.0 (0x00007f8d903e7000)
	libkeyutils.so.1 => /lib64/libkeyutils.so.1 (0x00007f8d903e0000)
	libresolv.so.2 => /lib64/libresolv.so.2 (0x00007f8d903c6000)
	libsasl2.so.3 => /lib64/libsasl2.so.3 (0x00007f8d903a4000)
	libbrotlicommon.so.1 => /lib64/libbrotlicommon.so.1 (0x00007f8d90381000)
	libselinux.so.1 => /lib64/libselinux.so.1 (0x00007f8d90354000)
	libcrypt.so.2 => /lib64/libcrypt.so.2 (0x00007f8d90319000)
	libpcre2-8.so.0 => /lib64/libpcre2-8.so.0 (0x00007f8d90280000)
ldd 2048-JUCE | wc -l
	36
```

### 2048-Cocoa

#### Mac OS X 10.0:

```
otool -L 2048-Cocoa
2048-Cocoa:
	/System/Library/Frameworks/Cocoa.framework/Versions/A/Cocoa (compatibility version 1.0.0, current version 5.0.0)
	/usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 50.0.0)
```

#### Mac OS X 10.6.8:

```
otool -L 2048-Cocoa
2048-Cocoa:
	/System/Library/Frameworks/Cocoa.framework/Versions/A/Cocoa (compatibility version 1.0.0, current version 15.0.0)
	/usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 125.2.11)
	/usr/lib/libgcc_s.1.dylib (compatibility version 1.0.0, current version 697.0.0)
	/usr/lib/libobjc.A.dylib (compatibility version 1.0.0, current version 227.0.0)
	/System/Library/Frameworks/CoreFoundation.framework/Versions/A/CoreFoundation (compatibility version 150.0.0, current version 550.43.0)
	/System/Library/Frameworks/Foundation.framework/Versions/C/Foundation (compatibility version 300.0.0, current version 751.62.0)
	/System/Library/Frameworks/AppKit.framework/Versions/C/AppKit (compatibility version 45.0.0, current version 1038.36.0)
```

#### OS X 10.8.5:

```
`xcodebuild -find otool` -L 2048-Cocoa
2048-Cocoa:
	/System/Library/Frameworks/Cocoa.framework/Versions/A/Cocoa (compatibility version 1.0.0, current version 20.0.0)
	/System/Library/Frameworks/Foundation.framework/Versions/C/Foundation (compatibility version 300.0.0, current version 1056.13.0)
	/usr/lib/libobjc.A.dylib (compatibility version 1.0.0, current version 228.0.0)
	/usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 1197.1.1)
	/System/Library/Frameworks/AppKit.framework/Versions/C/AppKit (compatibility version 45.0.0, current version 1265.19.0)
	/System/Library/Frameworks/CoreFoundation.framework/Versions/A/CoreFoundation (compatibility version 150.0.0, current version 855.14.0)
```

#### macOS 10.13.6

```
otool -L 2048-Cocoa
2048-Cocoa:
	/System/Library/Frameworks/Cocoa.framework/Versions/A/Cocoa (compatibility version 1.0.0, current version 23.0.0)
	/System/Library/Frameworks/Foundation.framework/Versions/C/Foundation (compatibility version 300.0.0, current version 1560.12.0)
	/usr/lib/libobjc.A.dylib (compatibility version 1.0.0, current version 228.0.0)
	/usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 1252.200.5)
	/System/Library/Frameworks/AppKit.framework/Versions/C/AppKit (compatibility version 45.0.0, current version 1671.10.106)
	/System/Library/Frameworks/CoreFoundation.framework/Versions/A/CoreFoundation (compatibility version 150.0.0, current version 1560.12.0)
```
