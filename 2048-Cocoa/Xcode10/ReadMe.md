2048-Cocoa
==========

![2048-Cocoa Mac OS X 10.13 Screenshot](../image/2048-Cocoa-Screenshot-10_13.png)

## Building application via Xcode 10

1. Open **2048-Cocoa.xproj** project.
2. Choose **Product** => **Clean Build Folder** in the global menu then choose **Product** => **Archive** item.
3. Select in the window that opens **Distribute App** button.
4. Choose **Copy App** option then set directory and click export.
5. Get **2048-Cocoa.app** package from selected directory.

## Building application via Command-Line tools

```bash
xcodebuild -scheme 2048-Cocoa archive -archivePath 2048-Cocoa
xcodebuild -exportArchive -archivePath 2048-Cocoa.xcarchive -exportPath build -exportOptionsPlist 2048-Cocoa.xcarchive/Info.plist
```

## Building application via Travis-CI

Travis-CI recipe:

```yml
```

## Versions

* macOS 10.13.6 (Build 17G14033)
* Xcode 10.1 (Build 10B61)

Compiler on macOS 10.13.6 and x86_64 platform:

```
cc -v
Apple LLVM version 10.0.0 (clang-1000.11.45.5)
Target: x86_64-apple-darwin17.7.0
Thread model: posix
InstalledDir: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin
```
