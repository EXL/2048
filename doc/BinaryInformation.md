Binary Information
==================

Dependencies were obtained:

1. By using `ldd` command on Fedora and QNX.
2. By `arm-linux-gnueabi-objdump` for MotoMAGX platform.
3. By `arm-linux-gnu-objdump` for EZX platform.
4. By `otool -L` command on NeXTSTEP and Mac OS X.
5. By CodeWarrior and ThinkC settings on classic Mac OS.
6. By Makefile on A/UX.

### Sizes and Rights

```
tree -phD --timefmt "%d-%b-%Y %H:%M:%S" 2048-Release/
2048-Release/
├── [-rwxrwxr-x   39K 05-May-2021 15:38:29]  2048-EZX
├── [-rwxrwxr-x   14K 30-Jun-2020 07:18:44]  2048-Gtk1
├── [-rwxrwxr-x   14K 30-Jun-2020 07:18:51]  2048-Gtk2
├── [-rwxrwxr-x   14K 30-Jun-2020 07:18:58]  2048-Gtk3
├── [-rwxrwxr-x  3.6M 05-Oct-2020 18:42:18]  2048-JUCE
├── [-rw-rw-r--  2.0M 26-Apr-2021 06:16:50]  2048-MAC.dsk
├── [-rwxrwxr-x   14K 30-Jun-2020 07:20:56]  2048-Motif
├── [-rwxrwxr-x   39K 26-Feb-2021 00:24:45]  2048-MotoMAGX_E8
├── [-rwxrwxr-x   39K 26-Feb-2021 00:24:43]  2048-MotoMAGX_EM30
├── [-rwxrwxr-x   39K 26-Feb-2021 00:24:49]  2048-MotoMAGX_EM35
├── [-rwxrwxr-x   39K 26-Feb-2021 00:24:39]  2048-MotoMAGX_U9
├── [-rwxrwxr-x   39K 26-Feb-2021 00:24:34]  2048-MotoMAGX_V8
├── [-rwxrwxr-x   39K 26-Feb-2021 00:24:47]  2048-MotoMAGX_VE66
├── [-rwxrwxr-x   39K 26-Feb-2021 00:24:32]  2048-MotoMAGX_Z6
├── [-rwxrwxr-x   39K 26-Feb-2021 00:24:37]  2048-MotoMAGX_Z6W
├── [-rwxrwxr-x   39K 26-Feb-2021 00:24:41]  2048-MotoMAGX_ZN5
├── [-rwxrwxr-x   40K 26-Sep-2020 01:41:35]  2048-Photon
├── [-rwxrwxr-x   23K 30-Jun-2020 07:19:20]  2048-Qt1
├── [-rwxrwxr-x   31K 30-Jun-2020 07:19:26]  2048-Qt2
├── [-rwxrwxr-x   31K 30-Jun-2020 07:19:32]  2048-Qt3
├── [-rwxrwxr-x   23K 30-Jun-2020 07:19:39]  2048-Qt4
├── [-rwxrwxr-x   23K 30-Jun-2020 07:19:45]  2048-Qt5
├── [-rwxrwxr-x   23K 14-Nov-2020 21:38:30]  2048-QtQuick
├── [-rwxrwxr-x  759K 27-Sep-2020 09:18:12]  2048-Serenity
├── [-rw-rw-r--  128K 26-Feb-2021 05:09:46]  2048-SMD.bin
├── [-rwxrwxr-x   19K 15-Nov-2020 17:57:07]  2048-Vala
├── [-rwxrwxr-x   14K 30-Jun-2020 07:20:20]  2048-Xaw
├── [-rwxrwxr-x   14K 30-Jun-2020 07:20:27]  2048-Xcb
├── [-rwxrwxr-x   14K 30-Jun-2020 07:20:36]  2048-Xlib
├── [drwxrwxr-x  4.0K 26-Apr-2021 06:18:53]  AUX
│   ├── [-rw-r--r--  4.0K 26-Apr-2021 12:34:20]  %2048-AUX
│   ├── [-rwxr-xr-x   58K 26-Apr-2021 12:34:28]  2048-AUX
│   ├── [-rwxr-xr-x  345K 26-Apr-2021 12:34:28]  2048-Xaw
│   └── [-rwxr-xr-x   96K 26-Apr-2021 12:34:28]  2048-Xlib
├── [drwxr-xr-x  4.0K 05-May-2021 15:40:14]  EZX
│   └── [-rw-rw-r--   23K 05-May-2021 15:39:37]  2048_MotoEZX_A1200_E6_v1.0_05-May-2021.pkg
├── [drwxr-xr-x  4.0K 26-Apr-2021 06:19:17]  MacOS
│   ├── [drwxr-xr-x  4.0K 24-Apr-2021 04:36:06]  10.0
│   │   ├── [drwxr-xr-x  4.0K 24-Apr-2021 04:06:02]  2048-Carbon.app
│   │   │   └── [drwxr-xr-x  4.0K 24-Apr-2021 04:05:53]  Contents
│   │   │       ├── [-rw-r--r--   690 24-Apr-2021 04:04:55]  Info.plist
│   │   │       ├── [drwxr-xr-x  4.0K 24-Apr-2021 04:05:59]  MacOS
│   │   │       │   └── [-rwxr-xr-x   64K 24-Apr-2021 04:06:02]  2048-Carbon
│   │   │       ├── [-rw-r--r--   292 24-Apr-2021 04:04:55]  pbdevelopment.plist
│   │   │       ├── [-rw-r--r--     8 24-Apr-2021 04:04:55]  PkgInfo
│   │   │       └── [drwxr-xr-x  4.0K 24-Apr-2021 04:06:00]  Resources
│   │   │           ├── [-rw-r--r--   31K 24-Apr-2021 04:04:48]  2048-Carbon.icns
│   │   │           ├── [-rw-r--r--  4.1K 24-Apr-2021 04:06:01]  2048-Carbon.rsrc
│   │   │           ├── [drwxr-xr-x  4.0K 24-Apr-2021 04:04:52]  English.lproj
│   │   │           │   └── [-rw-r--r--   462 24-Apr-2021 04:04:52]  InfoPlist.strings
│   │   │           └── [-rw-r--r--  1.7K 24-Apr-2021 04:04:45]  ReadMe.md
│   │   └── [drwxr-xr-x  4.0K 25-Oct-2020 04:14:56]  2048-Cocoa.app
│   │       └── [drwxr-xr-x  4.0K 25-Oct-2020 04:14:47]  Contents
│   │           ├── [-rw-r--r--   760 25-Oct-2020 04:13:58]  Info.plist
│   │           ├── [drwxr-xr-x  4.0K 25-Oct-2020 04:14:55]  MacOS
│   │           │   └── [-rwxr-xr-x   36K 25-Oct-2020 04:14:55]  2048-Cocoa
│   │           ├── [-rw-r--r--   275 25-Oct-2020 04:13:59]  pbdevelopment.plist
│   │           ├── [-rw-r--r--     8 25-Oct-2020 04:13:59]  PkgInfo
│   │           └── [drwxr-xr-x  4.0K 25-Oct-2020 04:13:45]  Resources
│   │               ├── [-rw-r--r--   48K 25-Oct-2020 04:13:39]  2048-Cocoa.icns
│   │               ├── [drwxr-xr-x  4.0K 25-Oct-2020 04:13:53]  English.lproj
│   │               │   ├── [drwxr-xr-x  4.0K 25-Oct-2020 04:13:53]  2048-Cocoa.nib
│   │               │   │   ├── [-rw-r--r--   688 25-Oct-2020 04:13:53]  classes.nib
│   │               │   │   ├── [-rw-r--r--   500 25-Oct-2020 04:13:53]  info.nib
│   │               │   │   └── [-rw-r--r--  2.9K 25-Oct-2020 04:13:54]  objects.nib
│   │               │   ├── [-rw-r--r--   530 25-Oct-2020 04:13:49]  InfoPlist.strings
│   │               │   └── [-rw-r--r--   413 25-Oct-2020 04:13:46]  Localizable.strings
│   │               └── [-rw-r--r--  1.7K 25-Oct-2020 04:13:43]  ReadMe.md
│   ├── [drwxr-xr-x  4.0K 13-Nov-2020 18:19:06]  10.13
│   │   ├── [drwxr-xr-x  4.0K 25-Oct-2020 06:30:01]  2048-Cocoa.app
│   │   │   └── [drwxr-xr-x  4.0K 25-Oct-2020 06:29:57]  Contents
│   │   │       ├── [drwxr-xr-x  4.0K 25-Oct-2020 06:54:32]  _CodeSignature
│   │   │       │   └── [-rw-r--r--  3.8K 25-Oct-2020 06:29:57]  CodeResources
│   │   │       ├── [-rw-r--r--  1.6K 25-Oct-2020 06:29:57]  Info.plist
│   │   │       ├── [drwxr-xr-x  4.0K 25-Oct-2020 06:54:32]  MacOS
│   │   │       │   └── [-rwxr-xr-x   42K 25-Oct-2020 06:30:01]  2048-Cocoa
│   │   │       ├── [-rw-r--r--     8 25-Oct-2020 06:29:57]  PkgInfo
│   │   │       └── [drwxr-xr-x  4.0K 25-Oct-2020 06:29:57]  Resources
│   │   │           ├── [-rw-r--r--  627K 25-Oct-2020 06:29:55]  AppIcon.icns
│   │   │           ├── [-rw-r--r--  509K 25-Oct-2020 06:29:57]  Assets.car
│   │   │           ├── [drwxr-xr-x  4.0K 25-Oct-2020 06:54:32]  Base.lproj
│   │   │           │   └── [-rw-r--r--  8.9K 25-Oct-2020 06:29:55]  2048-Cocoa.nib
│   │   │           ├── [drwxr-xr-x  4.0K 25-Oct-2020 06:54:32]  English.lproj
│   │   │           │   └── [-rw-r--r--   828 25-Oct-2020 06:29:54]  Localizable.strings
│   │   │           └── [-rw-r--r--  1.6K 25-Oct-2020 06:29:54]  ReadMe.md
│   │   └── [drwxr-xr-x  4.0K 13-Nov-2020 16:59:23]  2048-Swift.app
│   │       └── [drwxr-xr-x  4.0K 13-Nov-2020 16:59:23]  Contents
│   │           ├── [drwxr-xr-x  4.0K 13-Nov-2020 16:59:23]  _CodeSignature
│   │           │   └── [-rw-r--r--  9.8K 13-Nov-2020 16:59:33]  CodeResources
│   │           ├── [drwxr-xr-x  4.0K 13-Nov-2020 16:59:33]  Frameworks
│   │           │   ├── [-rwxr-xr-x  236K 13-Nov-2020 16:59:30]  libswiftAppKit.dylib
│   │           │   ├── [-rwxr-xr-x   96K 13-Nov-2020 16:59:31]  libswiftCoreData.dylib
│   │           │   ├── [-rwxr-xr-x  6.2M 13-Nov-2020 16:59:30]  libswiftCore.dylib
│   │           │   ├── [-rwxr-xr-x   41K 13-Nov-2020 16:59:31]  libswiftCoreFoundation.dylib
│   │           │   ├── [-rwxr-xr-x  198K 13-Nov-2020 16:59:31]  libswiftCoreGraphics.dylib
│   │           │   ├── [-rwxr-xr-x   49K 13-Nov-2020 16:59:31]  libswiftCoreImage.dylib
│   │           │   ├── [-rwxr-xr-x  104K 13-Nov-2020 16:59:31]  libswiftDarwin.dylib
│   │           │   ├── [-rwxr-xr-x  338K 13-Nov-2020 16:59:31]  libswiftDispatch.dylib
│   │           │   ├── [-rwxr-xr-x  2.9M 13-Nov-2020 16:59:32]  libswiftFoundation.dylib
│   │           │   ├── [-rwxr-xr-x   44K 13-Nov-2020 16:59:32]  libswiftIOKit.dylib
│   │           │   ├── [-rwxr-xr-x   91K 13-Nov-2020 16:59:32]  libswiftMetal.dylib
│   │           │   ├── [-rwxr-xr-x   60K 13-Nov-2020 16:59:32]  libswiftObjectiveC.dylib
│   │           │   ├── [-rwxr-xr-x   73K 13-Nov-2020 16:59:33]  libswiftos.dylib
│   │           │   ├── [-rwxr-xr-x   57K 13-Nov-2020 16:59:32]  libswiftQuartzCore.dylib
│   │           │   └── [-rwxr-xr-x   44K 13-Nov-2020 16:59:32]  libswiftXPC.dylib
│   │           ├── [-rw-r--r--  1.6K 13-Nov-2020 16:59:19]  Info.plist
│   │           ├── [drwxr-xr-x  4.0K 13-Nov-2020 16:59:33]  MacOS
│   │           │   └── [-rwxr-xr-x   88K 13-Nov-2020 16:59:33]  2048-Swift
│   │           ├── [-rw-r--r--     8 13-Nov-2020 16:59:19]  PkgInfo
│   │           └── [drwxr-xr-x  4.0K 13-Nov-2020 16:59:19]  Resources
│   │               ├── [-rw-r--r--  627K 13-Nov-2020 16:59:17]  AppIcon.icns
│   │               ├── [-rw-r--r--  509K 13-Nov-2020 16:59:19]  Assets.car
│   │               ├── [drwxr-xr-x  4.0K 13-Nov-2020 16:59:17]  Base.lproj
│   │               │   └── [-rw-r--r--  8.9K 13-Nov-2020 16:59:17]  2048-Swift.nib
│   │               ├── [drwxr-xr-x  4.0K 13-Nov-2020 16:59:15]  English.lproj
│   │               │   └── [-rw-r--r--   828 13-Nov-2020 16:59:15]  Localizable.strings
│   │               └── [-rw-r--r--  1.8K 13-Nov-2020 16:59:15]  ReadMe.md
│   ├── [drwxr-xr-x  4.0K 24-Apr-2021 04:25:27]  10.4
│   │   └── [dr-xr-xr-x  4.0K 24-Apr-2021 01:28:06]  2048-Carbon.app
│   │       └── [dr-xr-xr-x  4.0K 24-Apr-2021 01:28:06]  Contents
│   │           ├── [-r--r--r--   854 24-Apr-2021 01:28:00]  Info.plist
│   │           ├── [dr-xr-xr-x  4.0K 24-Apr-2021 04:25:27]  MacOS
│   │           │   └── [-r-xr-xr-x   42K 24-Apr-2021 01:28:06]  2048-Carbon
│   │           ├── [-r--r--r--     8 24-Apr-2021 01:28:01]  PkgInfo
│   │           └── [dr-xr-xr-x  4.0K 24-Apr-2021 01:28:01]  Resources
│   │               ├── [-r--r--r--   31K 24-Apr-2021 01:28:01]  2048-Carbon.icns
│   │               ├── [dr-xr-xr-x  4.0K 24-Apr-2021 04:25:27]  English.lproj
│   │               │   ├── [dr-xr-xr-x  4.0K 24-Apr-2021 04:25:27]  2048-Carbon.nib
│   │               │   │   ├── [-r--r--r--    35 24-Apr-2021 01:28:01]  classes.nib
│   │               │   │   ├── [-r--r--r--   770 24-Apr-2021 01:28:01]  info.nib
│   │               │   │   └── [-r--r--r--  7.4K 24-Apr-2021 01:28:01]  objects.xib
│   │               │   └── [-r--r--r--   176 24-Apr-2021 01:28:01]  InfoPlist.strings
│   │               └── [-r--r--r--  2.3K 24-Apr-2021 01:28:01]  ReadMe.md
│   ├── [drwxr-xr-x  4.0K 24-Apr-2021 01:50:07]  10.5
│   │   ├── [drwxr-xr-x  4.0K 24-Apr-2021 04:25:27]  2048-Carbon.app
│   │   │   └── [drwxr-xr-x  4.0K 24-Apr-2021 00:09:33]  Contents
│   │   │       ├── [-rw-r--r--   784 24-Apr-2021 00:09:30]  Info.plist
│   │   │       ├── [drwxr-xr-x  4.0K 24-Apr-2021 04:25:27]  MacOS
│   │   │       │   └── [-rwxr-xr-x   42K 24-Apr-2021 00:09:34]  2048-Carbon
│   │   │       ├── [-rw-r--r--     8 24-Apr-2021 00:09:30]  PkgInfo
│   │   │       └── [drwxr-xr-x  4.0K 24-Apr-2021 00:09:30]  Resources
│   │   │           ├── [-rw-r--r--   31K 24-Apr-2021 00:09:30]  2048-Carbon.icns
│   │   │           ├── [drwxr-xr-x  4.0K 24-Apr-2021 04:25:27]  English.lproj
│   │   │           │   └── [drwxr-xr-x  4.0K 24-Apr-2021 00:09:31]  2048-Carbon.nib
│   │   │           │       └── [-rw-r--r--  6.6K 24-Apr-2021 00:09:31]  objects.xib
│   │   │           └── [-rw-r--r--  2.2K 24-Apr-2021 00:09:30]  ReadMe.md
│   │   └── [drwxr-xr-x  4.0K 24-Apr-2021 00:10:07]  2048-Cocoa.app
│   │       └── [drwxr-xr-x  4.0K 24-Apr-2021 00:10:06]  Contents
│   │           ├── [-rw-r--r--   852 24-Apr-2021 00:09:58]  Info.plist
│   │           ├── [drwxr-xr-x  4.0K 24-Apr-2021 04:25:27]  MacOS
│   │           │   └── [-rwxr-xr-x  114K 24-Apr-2021 00:10:07]  2048-Cocoa
│   │           ├── [-rw-r--r--     8 24-Apr-2021 00:09:58]  PkgInfo
│   │           └── [drwxr-xr-x  4.0K 24-Apr-2021 00:09:58]  Resources
│   │               ├── [-rw-r--r--  139K 24-Apr-2021 00:09:58]  2048-Cocoa-modern.icns
│   │               ├── [drwxr-xr-x  4.0K 24-Apr-2021 04:25:27]  English.lproj
│   │               │   ├── [-rw-r--r--  8.6K 24-Apr-2021 00:09:58]  2048-Cocoa.nib
│   │               │   └── [-rw-r--r--   828 24-Apr-2021 00:09:58]  Localizable.strings
│   │               └── [-rw-r--r--  1.9K 24-Apr-2021 00:09:58]  ReadMe.md
│   ├── [drwxr-xr-x  4.0K 25-Oct-2020 06:53:54]  10.6
│   │   └── [drwxr-xr-x  4.0K 25-Oct-2020 05:26:56]  2048-Cocoa.app
│   │       └── [drwxr-xr-x  4.0K 25-Oct-2020 05:26:53]  Contents
│   │           ├── [-rw-r--r--  1.5K 25-Oct-2020 05:26:45]  Info.plist
│   │           ├── [drwxr-xr-x  4.0K 25-Oct-2020 06:53:49]  MacOS
│   │           │   └── [-rwxr-xr-x   53K 25-Oct-2020 05:26:56]  2048-Cocoa
│   │           ├── [-rw-r--r--     8 25-Oct-2020 05:26:45]  PkgInfo
│   │           └── [drwxr-xr-x  4.0K 25-Oct-2020 05:26:56]  Resources
│   │               ├── [-rw-r--r--  139K 25-Oct-2020 05:26:56]  2048-Cocoa-modern.icns
│   │               ├── [drwxr-xr-x  4.0K 25-Oct-2020 06:53:00]  en.lproj
│   │               │   ├── [-rw-r--r--  8.5K 25-Oct-2020 05:26:56]  2048-Cocoa.nib
│   │               │   ├── [-rw-r--r--  1.0K 25-Oct-2020 05:26:53]  Credits.rtf
│   │               │   └── [-rw-r--r--   828 25-Oct-2020 05:26:53]  Localizable.strings
│   │               └── [-rw-r--r--  1.3K 25-Oct-2020 05:26:53]  ReadMe.md
│   └── [drwxr-xr-x  4.0K 25-Oct-2020 06:55:54]  10.8
│       └── [drwxr-xr-x  4.0K 25-Oct-2020 06:00:28]  2048-Cocoa.app
│           └── [drwxr-xr-x  4.0K 25-Oct-2020 06:00:28]  Contents
│               ├── [drwxr-xr-x  4.0K 25-Oct-2020 06:55:42]  _CodeSignature
│               │   └── [-rw-r--r--  1.4K 25-Oct-2020 06:00:28]  CodeResources
│               ├── [-rw-r--r--  1.5K 25-Oct-2020 06:00:28]  Info.plist
│               ├── [drwxr-xr-x  4.0K 25-Oct-2020 06:55:42]  MacOS
│               │   └── [-rwxr-xr-x   38K 25-Oct-2020 06:00:28]  2048-Cocoa
│               ├── [-rw-r--r--     8 25-Oct-2020 06:00:28]  PkgInfo
│               └── [drwxr-xr-x  4.0K 25-Oct-2020 06:01:09]  Resources
│                   ├── [-rw-r--r--  627K 25-Oct-2020 06:00:27]  AppIcon.icns
│                   ├── [drwxr-xr-x  4.0K 25-Oct-2020 06:55:42]  en.lproj
│                   │   ├── [-rw-r--r--  7.3K 25-Oct-2020 06:00:26]  2048-Cocoa.nib
│                   │   ├── [-rw-r--r--  1.0K 25-Oct-2020 06:00:26]  Credits.rtf
│                   │   └── [-rw-r--r--   828 25-Oct-2020 06:00:26]  Localizable.strings
│                   └── [-rw-r--r--  1.3K 25-Oct-2020 06:00:26]  ReadMe.md
├── [drwxrwxr-x  4.0K 26-Feb-2021 05:11:35]  MotoMAGX
│   ├── [-rw-rw-r--   14K 26-Feb-2021 03:02:35]  2048_MotoMAGX_ZN5_v1.0_26-Feb-2021.mgx
│   └── [-rw-rw-r--   14K 29-Jun-2020 02:58:16]  2048_MotoMAGX_ZN5_v1.0_28-Jul-2020.mgx
├── [drwxrwxr-x  4.0K 26-Feb-2021 05:12:58]  NeXTSTEP
│   ├── [drwxr-xr-x  4.0K 15-Nov-1994 09:08:22]  2048-NeXTSTEP.app
│   │   ├── [-rwxr-xr-x  192K 15-Nov-1994 09:08:16]  2048-NeXTSTEP
│   │   ├── [-rw-r--r--   49K 15-Nov-1994 09:07:11]  avatar.tiff
│   │   ├── [drwxr-xr-x  4.0K 15-Nov-1994 09:07:57]  English.lproj
│   │   │   ├── [drwxr-xr-x  4.0K 15-Nov-2020 13:29:37]  2048-Info.nib
│   │   │   │   ├── [-rw-r--r--    56 15-Nov-1994 09:07:11]  data.classes
│   │   │   │   └── [-rw-r--r--  1.4K 15-Nov-1994 09:07:11]  data.nib
│   │   │   └── [drwxr-xr-x  4.0K 15-Nov-2020 13:29:37]  2048-NeXTSTEP.nib
│   │   │       ├── [-rw-r--r--   598 15-Nov-1994 09:07:11]  data.classes
│   │   │       └── [-rw-r--r--  2.5K 15-Nov-1994 09:07:11]  data.nib
│   │   ├── [-rw-r--r--   15K 15-Nov-1994 09:07:11]  icon150.tiff
│   │   └── [-rw-r--r--  3.2K 15-Nov-1994 09:07:11]  icon48.tiff
│   └── [drwxr-xr-x  4.0K 15-Nov-1994 09:09:59]  2048-NeXTSTEP.pkg
│       ├── [-rw-r--r--   16K 15-Nov-1994 09:09:59]  2048-NeXTSTEP.bom
│       ├── [-r--r--r--   798 15-Nov-1994 09:09:58]  2048-NeXTSTEP.info
│       ├── [-rw-r--r--    49 15-Nov-1994 09:09:59]  2048-NeXTSTEP.sizes
│       ├── [-r--r--r--  169K 15-Nov-1994 09:09:58]  2048-NeXTSTEP.tar.Z
│       └── [-r--r--r--  3.2K 15-Nov-1994 09:09:58]  2048-NeXTSTEP.tiff
└── [drwxr-xr-x  4.0K 26-Feb-2021 05:12:07]  Videos
    ├── [-rw-rw-r--  2.9M 27-Jun-2020 05:01:59]  2048-MotoMAGX_ZN5.webm
    └── [-rw-r--r--   69M 26-Feb-2021 04:51:36]  2048-SMD.mp4

71 directories, 142 files
```

### File Types

```
file 2048-*
2048-EZX:           ELF 32-bit LSB executable, ARM, version 1 (ARM), dynamically linked, interpreter /lib/ld-linux.so.2, for GNU/Linux 2.4.3, stripped
2048-Gtk1:          ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 2.6.32, BuildID[sha1]=7184adff443baf648bb1a08061fc2003b8f8265a, stripped
2048-Gtk2:          ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 2.6.32, BuildID[sha1]=8664c4f62a320b321831474b86d84743d58a1378, stripped
2048-Gtk3:          ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 2.6.32, BuildID[sha1]=465a678a0e5a28faf80a3a9149acc3d3408f29da, stripped
2048-JUCE:          ELF 64-bit LSB executable, x86-64, version 1 (GNU/Linux), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, BuildID[sha1]=4d1fa100e2f9bd25732ec8f17f4533fe35417614, for GNU/Linux 3.2.0, stripped
2048-MAC.dsk:       Macintosh HFS data block size: 512, number of blocks: 4090, volume name: 2048-MAC
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
2048-QtQuick:       ELF 64-bit LSB executable, x86-64, version 1 (GNU/Linux), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 2.6.32, BuildID[sha1]=d32c249c8e7321857431a0ccd8c9190f3b7487c0, stripped
2048-Serenity:      ELF 32-bit LSB executable, Intel 80386, version 1 (SYSV), statically linked, stripped
2048-SMD.bin:       Sega Mega Drive / Genesis ROM image: "2048-SMD        " (GM 00000000-00, (C) EXL 2021    )
2048-Vala:          ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 2.6.32, BuildID[sha1]=d4d916ea867d9dcb54bf071fbd0c87622d6fbed4, stripped
2048-Xaw:           ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 2.6.32, BuildID[sha1]=566076a8373ccfa7cf64ff73a4b4385b18bce7a7, stripped
2048-Xcb:           ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 2.6.32, BuildID[sha1]=1f45dde2f5c9aac70b8bcad872f45d8f962451ea, stripped
2048-Xlib:          ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 2.6.32, BuildID[sha1]=55e80fe0e4e139ef18c9bee96bcd9f5d66545294, stripped

file MotoMAGX/*
MotoMAGX/2048_MotoMAGX_ZN5_v1.0_26-Feb-2021.mgx: 7-zip archive data, version 0.4
MotoMAGX/2048_MotoMAGX_ZN5_v1.0_28-Jul-2020.mgx: 7-zip archive data, version 0.4

file EZX/*
EZX/2048_MotoEZX_A1200_E6_v1.0_05-May-2021.pkg: gzip compressed data, was "2048_EZX.uncompressed", last modified: Wed May  5 08:39:37 2021, max compression, from Unix, original size modulo 2^32 61440

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
MacOS/10.6/2048-Cocoa.app/Contents/Resources/en.lproj/Credits.rtf: Rich Text Format data, version 1, ANSI, code page 1252
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
MacOS/10.13/2048-Swift.app/Contents/Info.plist: XML 1.0 document, UTF-8 Unicode text
MacOS/10.13/2048-Swift.app/Contents/Resources/AppIcon.icns: Mac OS X icon, 642518 bytes, "TOC " type
MacOS/10.13/2048-Swift.app/Contents/Resources/Base.lproj/2048-Swift.nib: Apple binary property list
MacOS/10.13/2048-Swift.app/Contents/Resources/ReadMe.md: ASCII text
MacOS/10.13/2048-Swift.app/Contents/Resources/English.lproj/Localizable.strings: Little-endian UTF-16 Unicode text
MacOS/10.13/2048-Swift.app/Contents/Resources/Assets.car: Mac OS X bill of materials (BOM) file
MacOS/10.13/2048-Swift.app/Contents/PkgInfo: ASCII text, with no line terminators
MacOS/10.13/2048-Swift.app/Contents/_CodeSignature/CodeResources: XML 1.0 document, ASCII text
MacOS/10.13/2048-Swift.app/Contents/MacOS/2048-Swift: Mach-O 64-bit x86_64 executable, flags:<NOUNDEFS|DYLDLINK|TWOLEVEL|PIE>
MacOS/10.13/2048-Swift.app/Contents/Frameworks/libswiftIOKit.dylib: Mach-O 64-bit x86_64 dynamically linked shared library, flags:<NOUNDEFS|DYLDLINK|TWOLEVEL|NO_REEXPORTED_DYLIBS|APP_EXTENSION_SAFE>
MacOS/10.13/2048-Swift.app/Contents/Frameworks/libswiftObjectiveC.dylib: Mach-O 64-bit x86_64 dynamically linked shared library, flags:<NOUNDEFS|DYLDLINK|TWOLEVEL|NO_REEXPORTED_DYLIBS|APP_EXTENSION_SAFE>
MacOS/10.13/2048-Swift.app/Contents/Frameworks/libswiftDispatch.dylib: Mach-O 64-bit x86_64 dynamically linked shared library, flags:<NOUNDEFS|DYLDLINK|TWOLEVEL|NO_REEXPORTED_DYLIBS|APP_EXTENSION_SAFE>
MacOS/10.13/2048-Swift.app/Contents/Frameworks/libswiftCoreData.dylib: Mach-O 64-bit x86_64 dynamically linked shared library, flags:<NOUNDEFS|DYLDLINK|TWOLEVEL|NO_REEXPORTED_DYLIBS|APP_EXTENSION_SAFE>
MacOS/10.13/2048-Swift.app/Contents/Frameworks/libswiftDarwin.dylib: Mach-O 64-bit x86_64 dynamically linked shared library, flags:<NOUNDEFS|DYLDLINK|TWOLEVEL|NO_REEXPORTED_DYLIBS|APP_EXTENSION_SAFE>
MacOS/10.13/2048-Swift.app/Contents/Frameworks/libswiftCoreFoundation.dylib: Mach-O 64-bit x86_64 dynamically linked shared library, flags:<NOUNDEFS|DYLDLINK|TWOLEVEL|NO_REEXPORTED_DYLIBS|APP_EXTENSION_SAFE>
MacOS/10.13/2048-Swift.app/Contents/Frameworks/libswiftCoreImage.dylib: Mach-O 64-bit x86_64 dynamically linked shared library, flags:<NOUNDEFS|DYLDLINK|TWOLEVEL|NO_REEXPORTED_DYLIBS|APP_EXTENSION_SAFE>
MacOS/10.13/2048-Swift.app/Contents/Frameworks/libswiftCore.dylib: Mach-O 64-bit x86_64 dynamically linked shared library, flags:<NOUNDEFS|DYLDLINK|TWOLEVEL|BINDS_TO_WEAK|NO_REEXPORTED_DYLIBS|HAS_TLV_DESCRIPTORS|APP_EXTENSION_SAFE>
MacOS/10.13/2048-Swift.app/Contents/Frameworks/libswiftMetal.dylib: Mach-O 64-bit x86_64 dynamically linked shared library, flags:<NOUNDEFS|DYLDLINK|TWOLEVEL|NO_REEXPORTED_DYLIBS|APP_EXTENSION_SAFE>
MacOS/10.13/2048-Swift.app/Contents/Frameworks/libswiftXPC.dylib: Mach-O 64-bit x86_64 dynamically linked shared library, flags:<NOUNDEFS|DYLDLINK|TWOLEVEL|NO_REEXPORTED_DYLIBS|APP_EXTENSION_SAFE>
MacOS/10.13/2048-Swift.app/Contents/Frameworks/libswiftos.dylib: Mach-O 64-bit x86_64 dynamically linked shared library, flags:<NOUNDEFS|DYLDLINK|TWOLEVEL|NO_REEXPORTED_DYLIBS|APP_EXTENSION_SAFE>
MacOS/10.13/2048-Swift.app/Contents/Frameworks/libswiftFoundation.dylib: Mach-O 64-bit x86_64 dynamically linked shared library, flags:<NOUNDEFS|DYLDLINK|TWOLEVEL|NO_REEXPORTED_DYLIBS|APP_EXTENSION_SAFE>
MacOS/10.13/2048-Swift.app/Contents/Frameworks/libswiftCoreGraphics.dylib: Mach-O 64-bit x86_64 dynamically linked shared library, flags:<NOUNDEFS|DYLDLINK|TWOLEVEL|NO_REEXPORTED_DYLIBS|APP_EXTENSION_SAFE>
MacOS/10.13/2048-Swift.app/Contents/Frameworks/libswiftQuartzCore.dylib: Mach-O 64-bit x86_64 dynamically linked shared library, flags:<NOUNDEFS|DYLDLINK|TWOLEVEL|NO_REEXPORTED_DYLIBS|APP_EXTENSION_SAFE>
MacOS/10.13/2048-Swift.app/Contents/Frameworks/libswiftAppKit.dylib: Mach-O 64-bit x86_64 dynamically linked shared library, flags:<NOUNDEFS|DYLDLINK|TWOLEVEL|NO_REEXPORTED_DYLIBS|APP_EXTENSION_SAFE>
MacOS/10.8/2048-Cocoa.app/Contents/Info.plist: XML 1.0 document, UTF-8 Unicode text
MacOS/10.8/2048-Cocoa.app/Contents/Resources/AppIcon.icns: Mac OS X icon, 642414 bytes, "TOC " type
MacOS/10.8/2048-Cocoa.app/Contents/Resources/en.lproj/2048-Cocoa.nib: Apple binary property list
MacOS/10.8/2048-Cocoa.app/Contents/Resources/en.lproj/Credits.rtf: Rich Text Format data, version 1, ANSI, code page 1252
MacOS/10.8/2048-Cocoa.app/Contents/Resources/en.lproj/Localizable.strings: Little-endian UTF-16 Unicode text
MacOS/10.8/2048-Cocoa.app/Contents/Resources/ReadMe.md: ASCII text
MacOS/10.8/2048-Cocoa.app/Contents/PkgInfo: ASCII text, with no line terminators
MacOS/10.8/2048-Cocoa.app/Contents/_CodeSignature/CodeResources: XML 1.0 document, ASCII text
MacOS/10.8/2048-Cocoa.app/Contents/MacOS/2048-Cocoa: Mach-O 64-bit x86_64 executable, flags:<NOUNDEFS|DYLDLINK|TWOLEVEL>
MacOS/10.4/2048-Carbon.app/Contents/Info.plist: XML 1.0 document, ASCII text
MacOS/10.4/2048-Carbon.app/Contents/Resources/ReadMe.md: ASCII text, with very long lines
MacOS/10.4/2048-Carbon.app/Contents/Resources/English.lproj/InfoPlist.strings: Little-endian UTF-16 Unicode text
MacOS/10.4/2048-Carbon.app/Contents/Resources/English.lproj/2048-Carbon.nib/info.nib: XML 1.0 document, ASCII text
MacOS/10.4/2048-Carbon.app/Contents/Resources/English.lproj/2048-Carbon.nib/classes.nib: ASCII text
MacOS/10.4/2048-Carbon.app/Contents/Resources/English.lproj/2048-Carbon.nib/objects.xib: XML 1.0 document, ASCII text
MacOS/10.4/2048-Carbon.app/Contents/Resources/2048-Carbon.icns: Mac OS X icon, 31376 bytes, "ics#" type
MacOS/10.4/2048-Carbon.app/Contents/PkgInfo: ASCII text, with no line terminators
MacOS/10.4/2048-Carbon.app/Contents/MacOS/2048-Carbon: Mach-O universal binary with 2 architectures: [ppc:Mach-O ppc executable, flags:<NOUNDEFS|DYLDLINK|TWOLEVEL>] [i386:Mach-O i386 executable, flags:<NOUNDEFS|DYLDLINK|TWOLEVEL|SUBSECTIONS_VIA_SYMBOLS>]
MacOS/10.0/2048-Cocoa.app/Contents/pbdevelopment.plist: XML 1.0 document, ASCII text
MacOS/10.0/2048-Cocoa.app/Contents/Info.plist: XML 1.0 document, ASCII text
MacOS/10.0/2048-Cocoa.app/Contents/Resources/ReadMe.md: ASCII text
MacOS/10.0/2048-Cocoa.app/Contents/Resources/English.lproj/InfoPlist.strings: Big-endian UTF-16 Unicode text
MacOS/10.0/2048-Cocoa.app/Contents/Resources/English.lproj/2048-Cocoa.nib/info.nib: XML 1.0 document, ASCII text
MacOS/10.0/2048-Cocoa.app/Contents/Resources/English.lproj/2048-Cocoa.nib/classes.nib: ASCII text
MacOS/10.0/2048-Cocoa.app/Contents/Resources/English.lproj/2048-Cocoa.nib/objects.nib: NeXT/Apple typedstream data, big endian, version 4, system 1000
MacOS/10.0/2048-Cocoa.app/Contents/Resources/English.lproj/Localizable.strings: ASCII text
MacOS/10.0/2048-Cocoa.app/Contents/Resources/2048-Cocoa.icns: Mac OS X icon, 49253 bytes, "ics#" type
MacOS/10.0/2048-Cocoa.app/Contents/PkgInfo: ASCII text, with no line terminators
MacOS/10.0/2048-Cocoa.app/Contents/MacOS/2048-Cocoa: Mach-O ppc executable, flags:<NOUNDEFS|DYLDLINK|PREBOUND>
MacOS/10.0/2048-Carbon.app/Contents/pbdevelopment.plist: XML 1.0 document, ASCII text
MacOS/10.0/2048-Carbon.app/Contents/Info.plist: XML 1.0 document, ASCII text
MacOS/10.0/2048-Carbon.app/Contents/Resources/2048-Carbon.rsrc: Apple HFS/HFS+ resource fork
MacOS/10.0/2048-Carbon.app/Contents/Resources/ReadMe.md: ASCII text
MacOS/10.0/2048-Carbon.app/Contents/Resources/English.lproj/InfoPlist.strings: Big-endian UTF-16 Unicode text
MacOS/10.0/2048-Carbon.app/Contents/Resources/2048-Carbon.icns: Mac OS X icon, 31376 bytes, "ics#" type
MacOS/10.0/2048-Carbon.app/Contents/PkgInfo: ASCII text, with no line terminators
MacOS/10.0/2048-Carbon.app/Contents/MacOS/2048-Carbon: Mach-O ppc executable, flags:<NOUNDEFS|DYLDLINK|PREBOUND>
MacOS/10.5/2048-Cocoa.app/Contents/Info.plist: XML 1.0 document, ASCII text
MacOS/10.5/2048-Cocoa.app/Contents/Resources/ReadMe.md: ASCII text, with very long lines
MacOS/10.5/2048-Cocoa.app/Contents/Resources/English.lproj/2048-Cocoa.nib: Apple binary property list
MacOS/10.5/2048-Cocoa.app/Contents/Resources/English.lproj/Localizable.strings: Big-endian UTF-16 Unicode text
MacOS/10.5/2048-Cocoa.app/Contents/Resources/2048-Cocoa-modern.icns: Mac OS X icon, 142338 bytes, "is32" type
MacOS/10.5/2048-Cocoa.app/Contents/PkgInfo: ASCII text, with no line terminators
MacOS/10.5/2048-Cocoa.app/Contents/MacOS/2048-Cocoa: Mach-O universal binary with 4 architectures: [i386:Mach-O i386 executable, flags:<NOUNDEFS|DYLDLINK|TWOLEVEL>] [x86_64:Mach-O 64-bit x86_64 executable, flags:<NOUNDEFS|DYLDLINK|TWOLEVEL>] [ppc_7400:Mach-O ppc_7400 executable, flags:<NOUNDEFS|DYLDLINK|TWOLEVEL>] [ppc64:Mach-O ppc64 executable, flags:<NOUNDEFS|DYLDLINK|TWOLEVEL>]
MacOS/10.5/2048-Carbon.app/Contents/Info.plist: XML 1.0 document, ASCII text
MacOS/10.5/2048-Carbon.app/Contents/Resources/ReadMe.md: ASCII text, with very long lines
MacOS/10.5/2048-Carbon.app/Contents/Resources/English.lproj/2048-Carbon.nib/objects.xib: XML 1.0 document, ASCII text
MacOS/10.5/2048-Carbon.app/Contents/Resources/2048-Carbon.icns: Mac OS X icon, 31376 bytes, "ics#" type
MacOS/10.5/2048-Carbon.app/Contents/PkgInfo: ASCII text, with no line terminators
MacOS/10.5/2048-Carbon.app/Contents/MacOS/2048-Carbon: Mach-O universal binary with 2 architectures: [i386:Mach-O i386 executable, flags:<NOUNDEFS|DYLDLINK|TWOLEVEL>] [ppc_7400:Mach-O ppc_7400 executable, flags:<NOUNDEFS|DYLDLINK|TWOLEVEL>]

file AUX/*
AUX/%2048-AUX: AppleDouble encoded Macintosh file
AUX/2048-AUX:  mc68k COFF object (demand paged)
AUX/2048-Xaw:  mc68k COFF object (demand paged)
AUX/2048-Xlib: mc68k COFF object (demand paged)

file Videos/*
Videos/2048-MotoMAGX_ZN5.webm: WebM
Videos/2048-SMD.mp4:           ISO Media, MP4 Base Media v1 [IS0 14496-12:2003]
```

### 2048-QtQuick

```
ldd 2048-QtQuick
	linux-vdso.so.1 (0x00007ffc08370000)
	libQt5Quick.so.5 => /lib64/libQt5Quick.so.5 (0x00007f2014465000)
	libQt5Qml.so.5 => /lib64/libQt5Qml.so.5 (0x00007f2014072000)
	libQt5Network.so.5 => /lib64/libQt5Network.so.5 (0x00007f2013eef000)
	libQt5Gui.so.5 => /lib64/libQt5Gui.so.5 (0x00007f2013928000)
	libQt5Core.so.5 => /lib64/libQt5Core.so.5 (0x00007f2013408000)
	libstdc++.so.6 => /lib64/libstdc++.so.6 (0x00007f2013220000)
	libm.so.6 => /lib64/libm.so.6 (0x00007f20130d8000)
	libgcc_s.so.1 => /lib64/libgcc_s.so.1 (0x00007f20130bd000)
	libc.so.6 => /lib64/libc.so.6 (0x00007f2012ef1000)
	libQt5QmlModels.so.5 => /lib64/libQt5QmlModels.so.5 (0x00007f2012e72000)
	libpthread.so.0 => /lib64/libpthread.so.0 (0x00007f2012e50000)
	libz.so.1 => /lib64/libz.so.1 (0x00007f2012e36000)
	libdl.so.2 => /lib64/libdl.so.2 (0x00007f2012e2d000)
	libgssapi_krb5.so.2 => /lib64/libgssapi_krb5.so.2 (0x00007f2012dd9000)
	libssl.so.1.1 => /lib64/libssl.so.1.1 (0x00007f2012d3d000)
	libcrypto.so.1.1 => /lib64/libcrypto.so.1.1 (0x00007f2012a51000)
	libGL.so.1 => /lib64/libGL.so.1 (0x00007f20129ca000)
	libpng16.so.16 => /lib64/libpng16.so.16 (0x00007f2012991000)
	libharfbuzz.so.0 => /lib64/libharfbuzz.so.0 (0x00007f20128c1000)
	libsystemd.so.0 => /lib64/libsystemd.so.0 (0x00007f2012805000)
	libicui18n.so.67 => /lib64/libicui18n.so.67 (0x00007f20124fc000)
	libicuuc.so.67 => /lib64/libicuuc.so.67 (0x00007f2012311000)
	libpcre2-16.so.0 => /lib64/libpcre2-16.so.0 (0x00007f2012288000)
	libglib-2.0.so.0 => /lib64/libglib-2.0.so.0 (0x00007f2012159000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f20149ae000)
	libkrb5.so.3 => /lib64/libkrb5.so.3 (0x00007f2012081000)
	libk5crypto.so.3 => /lib64/libk5crypto.so.3 (0x00007f2012069000)
	libcom_err.so.2 => /lib64/libcom_err.so.2 (0x00007f2012063000)
	libkrb5support.so.0 => /lib64/libkrb5support.so.0 (0x00007f2012052000)
	libkeyutils.so.1 => /lib64/libkeyutils.so.1 (0x00007f201204b000)
	libresolv.so.2 => /lib64/libresolv.so.2 (0x00007f2012031000)
	libGLX.so.0 => /lib64/libGLX.so.0 (0x00007f2011ffd000)
	libX11.so.6 => /lib64/libX11.so.6 (0x00007f2011eb6000)
	libXext.so.6 => /lib64/libXext.so.6 (0x00007f2011ea1000)
	libGLdispatch.so.0 => /lib64/libGLdispatch.so.0 (0x00007f2011de9000)
	libfreetype.so.6 => /lib64/libfreetype.so.6 (0x00007f2011d26000)
	libgraphite2.so.3 => /lib64/libgraphite2.so.3 (0x00007f2011d05000)
	librt.so.1 => /lib64/librt.so.1 (0x00007f2011cf8000)
	liblzma.so.5 => /lib64/liblzma.so.5 (0x00007f2011ccc000)
	libzstd.so.1 => /lib64/libzstd.so.1 (0x00007f2011c16000)
	liblz4.so.1 => /lib64/liblz4.so.1 (0x00007f2011bf8000)
	libgcrypt.so.20 => /lib64/libgcrypt.so.20 (0x00007f2011ad4000)
	libicudata.so.67 => /lib64/libicudata.so.67 (0x00007f200ffbb000)
	libpcre.so.1 => /lib64/libpcre.so.1 (0x00007f200ff40000)
	libselinux.so.1 => /lib64/libselinux.so.1 (0x00007f200ff13000)
	libxcb.so.1 => /lib64/libxcb.so.1 (0x00007f200fee9000)
	libbz2.so.1 => /lib64/libbz2.so.1 (0x00007f200fed6000)
	libbrotlidec.so.1 => /lib64/libbrotlidec.so.1 (0x00007f200fec8000)
	libgpg-error.so.0 => /lib64/libgpg-error.so.0 (0x00007f200fea5000)
	libpcre2-8.so.0 => /lib64/libpcre2-8.so.0 (0x00007f200fe0f000)
	libXau.so.6 => /lib64/libXau.so.6 (0x00007f200fe0a000)
	libbrotlicommon.so.1 => /lib64/libbrotlicommon.so.1 (0x00007f200fde7000)
ldd 2048-QtQuick | wc -l
	53
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

### 2048-Vala

```
ldd 2048-Vala
	linux-vdso.so.1 (0x00007ffe6e799000)
	libgtk-3.so.0 => /lib64/libgtk-3.so.0 (0x00007f7311fc3000)
	libcairo.so.2 => /lib64/libcairo.so.2 (0x00007f7311ea8000)
	libgobject-2.0.so.0 => /lib64/libgobject-2.0.so.0 (0x00007f7311e4f000)
	libglib-2.0.so.0 => /lib64/libglib-2.0.so.0 (0x00007f7311d20000)
	libc.so.6 => /lib64/libc.so.6 (0x00007f7311b55000)
	libgdk-3.so.0 => /lib64/libgdk-3.so.0 (0x00007f7311a57000)
	libgmodule-2.0.so.0 => /lib64/libgmodule-2.0.so.0 (0x00007f7311a4f000)
	libpangocairo-1.0.so.0 => /lib64/libpangocairo-1.0.so.0 (0x00007f7311a3d000)
	libX11.so.6 => /lib64/libX11.so.6 (0x00007f73118f6000)
	libXi.so.6 => /lib64/libXi.so.6 (0x00007f73118e4000)
	libXfixes.so.3 => /lib64/libXfixes.so.3 (0x00007f73118db000)
	libcairo-gobject.so.2 => /lib64/libcairo-gobject.so.2 (0x00007f73118cf000)
	libgdk_pixbuf-2.0.so.0 => /lib64/libgdk_pixbuf-2.0.so.0 (0x00007f73118a2000)
	libatk-1.0.so.0 => /lib64/libatk-1.0.so.0 (0x00007f7311879000)
	libatk-bridge-2.0.so.0 => /lib64/libatk-bridge-2.0.so.0 (0x00007f7311842000)
	libwayland-client.so.0 => /lib64/libwayland-client.so.0 (0x00007f7311832000)
	libepoxy.so.0 => /lib64/libepoxy.so.0 (0x00007f73116fd000)
	libfribidi.so.0 => /lib64/libfribidi.so.0 (0x00007f73116df000)
	libgio-2.0.so.0 => /lib64/libgio-2.0.so.0 (0x00007f7311518000)
	libm.so.6 => /lib64/libm.so.6 (0x00007f73113d2000)
	libpangoft2-1.0.so.0 => /lib64/libpangoft2-1.0.so.0 (0x00007f73113b8000)
	libpango-1.0.so.0 => /lib64/libpango-1.0.so.0 (0x00007f7311366000)
	libharfbuzz.so.0 => /lib64/libharfbuzz.so.0 (0x00007f7311298000)
	libfontconfig.so.1 => /lib64/libfontconfig.so.1 (0x00007f731124d000)
	libfreetype.so.6 => /lib64/libfreetype.so.6 (0x00007f7311188000)
	libpthread.so.0 => /lib64/libpthread.so.0 (0x00007f7311166000)
	libpixman-1.so.0 => /lib64/libpixman-1.so.0 (0x00007f73110b9000)
	libpng16.so.16 => /lib64/libpng16.so.16 (0x00007f7311080000)
	libxcb-shm.so.0 => /lib64/libxcb-shm.so.0 (0x00007f731107b000)
	libxcb.so.1 => /lib64/libxcb.so.1 (0x00007f7311051000)
	libxcb-render.so.0 => /lib64/libxcb-render.so.0 (0x00007f7311040000)
	libXrender.so.1 => /lib64/libXrender.so.1 (0x00007f7311033000)
	libXext.so.6 => /lib64/libXext.so.6 (0x00007f731101e000)
	libz.so.1 => /lib64/libz.so.1 (0x00007f7311004000)
	librt.so.1 => /lib64/librt.so.1 (0x00007f7310ff9000)
	libffi.so.6 => /lib64/libffi.so.6 (0x00007f7310fee000)
	libpcre.so.1 => /lib64/libpcre.so.1 (0x00007f7310f73000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f731278b000)
	libXinerama.so.1 => /lib64/libXinerama.so.1 (0x00007f7310f6e000)
	libXrandr.so.2 => /lib64/libXrandr.so.2 (0x00007f7310f61000)
	libXcursor.so.1 => /lib64/libXcursor.so.1 (0x00007f7310f54000)
	libXcomposite.so.1 => /lib64/libXcomposite.so.1 (0x00007f7310f4f000)
	libXdamage.so.1 => /lib64/libXdamage.so.1 (0x00007f7310f4a000)
	libxkbcommon.so.0 => /lib64/libxkbcommon.so.0 (0x00007f7310f03000)
	libwayland-cursor.so.0 => /lib64/libwayland-cursor.so.0 (0x00007f7310ef9000)
	libwayland-egl.so.1 => /lib64/libwayland-egl.so.1 (0x00007f7310ef4000)
	libdl.so.2 => /lib64/libdl.so.2 (0x00007f7310eed000)
	libdbus-1.so.3 => /lib64/libdbus-1.so.3 (0x00007f7310e9c000)
	libatspi.so.0 => /lib64/libatspi.so.0 (0x00007f7310e63000)
	libmount.so.1 => /lib64/libmount.so.1 (0x00007f7310e21000)
	libselinux.so.1 => /lib64/libselinux.so.1 (0x00007f7310df4000)
	libresolv.so.2 => /lib64/libresolv.so.2 (0x00007f7310dda000)
	libthai.so.0 => /lib64/libthai.so.0 (0x00007f7310dcf000)
	libgraphite2.so.3 => /lib64/libgraphite2.so.3 (0x00007f7310dac000)
	libxml2.so.2 => /lib64/libxml2.so.2 (0x00007f7310c21000)
	libbz2.so.1 => /lib64/libbz2.so.1 (0x00007f7310c0e000)
	libbrotlidec.so.1 => /lib64/libbrotlidec.so.1 (0x00007f7310c00000)
	libXau.so.6 => /lib64/libXau.so.6 (0x00007f7310bfb000)
	libsystemd.so.0 => /lib64/libsystemd.so.0 (0x00007f7310b3d000)
	libblkid.so.1 => /lib64/libblkid.so.1 (0x00007f7310b09000)
	libpcre2-8.so.0 => /lib64/libpcre2-8.so.0 (0x00007f7310a73000)
	libdatrie.so.1 => /lib64/libdatrie.so.1 (0x00007f7310a6a000)
	liblzma.so.5 => /lib64/liblzma.so.5 (0x00007f7310a3e000)
	libbrotlicommon.so.1 => /lib64/libbrotlicommon.so.1 (0x00007f7310a19000)
	libzstd.so.1 => /lib64/libzstd.so.1 (0x00007f7310963000)
	liblz4.so.1 => /lib64/liblz4.so.1 (0x00007f7310945000)
	libgcrypt.so.20 => /lib64/libgcrypt.so.20 (0x00007f7310821000)
	libgcc_s.so.1 => /lib64/libgcc_s.so.1 (0x00007f7310806000)
	libgpg-error.so.0 => /lib64/libgpg-error.so.0 (0x00007f73107e3000)
ldd 2048-Vala | wc -l
	70
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

```
/opt/toolchains/motoezx/crosstool/bin/arm-linux-gnu-objdump -x 2048-EZX | grep NEEDED
  NEEDED      libqte-mt.so.2
  NEEDED      libezxappbase.so.1
  NEEDED      libstdc++.so.5
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

Mac OS X 10.0:

```
otool -L 2048-Cocoa
2048-Cocoa:
	/System/Library/Frameworks/Cocoa.framework/Versions/A/Cocoa (compatibility version 1.0.0, current version 5.0.0)
	/usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 50.0.0)
```

Mac OS X 10.5.8:

```
otool -L 2048-Cocoa
2048-Cocoa:
	/System/Library/Frameworks/Cocoa.framework/Versions/A/Cocoa (compatibility version 1.0.0, current version 12.0.0)
	/usr/lib/libgcc_s.1.dylib (compatibility version 1.0.0, current version 1.0.0)
	/usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 111.0.0)
	/usr/lib/libobjc.A.dylib (compatibility version 1.0.0, current version 227.0.0)
	/System/Library/Frameworks/CoreFoundation.framework/Versions/A/CoreFoundation (compatibility version 150.0.0, current version 476.0.0)
	/System/Library/Frameworks/AppKit.framework/Versions/C/AppKit (compatibility version 45.0.0, current version 949.0.0)
	/System/Library/Frameworks/Foundation.framework/Versions/C/Foundation (compatibility version 300.0.0, current version 677.12.0)
```

Mac OS X 10.6.8:

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

OS X 10.8.5:

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

macOS 10.13.6:

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

### 2048-Swift

macOS 10.13.6:

```
otool -L 2048-Swift
2048-Swift:
	/System/Library/Frameworks/Cocoa.framework/Versions/A/Cocoa (compatibility version 1.0.0, current version 23.0.0)
	/System/Library/Frameworks/Foundation.framework/Versions/C/Foundation (compatibility version 300.0.0, current version 1560.12.0)
	/usr/lib/libobjc.A.dylib (compatibility version 1.0.0, current version 228.0.0)
	/usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 1252.200.5)
	/System/Library/Frameworks/AppKit.framework/Versions/C/AppKit (compatibility version 45.0.0, current version 1671.10.106)
	/System/Library/Frameworks/CoreFoundation.framework/Versions/A/CoreFoundation (compatibility version 150.0.0, current version 1560.12.0)
	@rpath/libswiftAppKit.dylib (compatibility version 1.0.0, current version 1000.11.42)
	@rpath/libswiftCore.dylib (compatibility version 1.0.0, current version 1000.11.42)
	@rpath/libswiftCoreData.dylib (compatibility version 1.0.0, current version 1000.11.42)
	@rpath/libswiftCoreFoundation.dylib (compatibility version 1.0.0, current version 1000.11.42)
	@rpath/libswiftCoreGraphics.dylib (compatibility version 1.0.0, current version 1000.11.42)
	@rpath/libswiftCoreImage.dylib (compatibility version 1.0.0, current version 1000.11.42)
	@rpath/libswiftDarwin.dylib (compatibility version 1.0.0, current version 1000.11.42)
	@rpath/libswiftDispatch.dylib (compatibility version 1.0.0, current version 1000.11.42)
	@rpath/libswiftFoundation.dylib (compatibility version 1.0.0, current version 1000.11.42)
	@rpath/libswiftIOKit.dylib (compatibility version 1.0.0, current version 1000.11.42)
	@rpath/libswiftMetal.dylib (compatibility version 1.0.0, current version 1000.11.42)
	@rpath/libswiftObjectiveC.dylib (compatibility version 1.0.0, current version 1000.11.42)
	@rpath/libswiftQuartzCore.dylib (compatibility version 1.0.0, current version 1000.11.42)
	@rpath/libswiftXPC.dylib (compatibility version 1.0.0, current version 1000.11.42)
```

### 2048-ThinkC

Mac OS System 6.0.8.1 [International]:

```
2048-ThinkC: 14 K on disk (13,663 bytes):
	ANSI-Small (Static)
	MacTraps (Static)
	oops (Static)
```

### 2048-MCW

Mac OS 8.1:

```
2048-MCW 68K: 65 K on disk (47,926 bytes):
	MSL Runtime68K.Lib (Static)
	MacOS.lib (Static)
	MathLib68K (2i).Lib (Static)
	MSL C.68K (2i).Lib (Static)
	MSL C++.68K (2i).Lib (Static)
	MSL SIOUX.68K.Lib (Static)
2048-MCW PPC: 163 K on disk (115,610 bytes):
	MSL RuntimePPC.Lib (Static)
	InterfaceLib (Shared)
	MathLib (Shared)
	QuickDrawGXLib (Shared, Weak)
	MSL C.PPC.Lib (Static)
	MSL C++.PPC.Lib (Static)
	MSL SIOUX.PPC.Lib (Static)
2048-MCW: 195 K on disk (158,977 bytes), FAT executable:
	MSL Runtime68K.Lib (Static)
	MacOS.lib (Static)
	MathLib68K (2i).Lib (Static)
	MSL C.68K (2i).Lib (Static)
	MSL C++.68K (2i).Lib (Static)
	MSL SIOUX.68K.Lib (Static)
	MSL RuntimePPC.Lib (Static)
	InterfaceLib (Shared)
	MathLib (Shared)
	QuickDrawGXLib (Shared, Weak)
	MSL C.PPC.Lib (Static)
	MSL C++.PPC.Lib (Static)
	MSL SIOUX.PPC.Lib (Static)
```

### 2048-AUX

```
2048-AUX:
	-lmac_s -lat -lld -lmr -lc_s
2048-Xaw:
	-lXaw -lXmu -lXt -lX11
2048-Xlib
	-lX11
```

### 2048-Carbon

Mac OS 9.0.4:

```
2048-Carbon: 130 K on disk (80,526 bytes):
	MSL_All_Carbon.Lib (Static)
	CarbonLib (Shared)
```

Mac OS X 10.0:

```
otool -L 2048-Carbon
2048-Carbon:
	/System/Library/Frameworks/Carbon.framework/Versions/A/Carbon (compatibility version 2.0.0, current version 113.0.0)
	/usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 50.0.0)
```

Mac OS X 10.4.11:

```
otool -L 2048-Carbon
2048-Carbon:
	/System/Library/Frameworks/Carbon.framework/Versions/A/Carbon (compatibility version 2.0.0, current version 128.0.0)
	/usr/lib/libgcc_s.1.dylib (compatibility version 1.0.0, current version 1.0.0)
	/usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 88.3.9)
```

Mac OS X 10.5.8:

```
otool -L 2048-Carbon
2048-Carbon:
	/System/Library/Frameworks/Carbon.framework/Versions/A/Carbon (compatibility version 2.0.0, current version 136.0.0)
	/usr/lib/libgcc_s.1.dylib (compatibility version 1.0.0, current version 1.0.0)
	/usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 111.0.0)
	/System/Library/Frameworks/CoreFoundation.framework/Versions/A/CoreFoundation (compatibility version 150.0.0, current version 476.0.0)
	/System/Library/Frameworks/ApplicationServices.framework/Versions/A/ApplicationServices (compatibility version 1.0.0, current version 34.0.0)
```
