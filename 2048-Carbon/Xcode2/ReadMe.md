2048-Carbon
===========

![2048-Carbon Mac OS X 10.4 Screenshot](../../image/2048-Carbon-Screenshot-10_4.png)

Used technologies:

* [Carbon API](https://en.wikipedia.org/wiki/Carbon_(API))
* [Quartz 2D](https://en.wikipedia.org/wiki/Quartz_2D)/[Core Graphics](https://en.wikipedia.org/wiki/Quartz_(graphics_layer))
* HIView from [HIToolbox](http://mirror.informatimago.com/next/developer.apple.com/carbon/HIToolbox_feature.html)
* NIB from [Interface Builder](https://en.wikipedia.org/wiki/Interface_Builder#Design)

Building the program is performed for the following architectures:

* x86 (i386)
* ppc

## Building application via Xcode 2

1. Open **2048-Carbon.xcodeproj** project.
2. Choose **Build** => **Clean All Targets** in the global menu and then click **Clean** button.
3. Choose **Build** => **Build** menu item.
4. Get **2048-Carbon.app** package from **build/Release/** directory.

## Building application via Command-Line tools

```bash
git clone https://github.com/EXL/2048
cd 2048/2048-Carbon/Xcode2/

xcodebuild clean install
cd /tmp/2048-Carbon.dst/Users/$USER/Applications/
tar -cvf 2048-Carbon.app.tar 2048-Carbon.app
mv 2048-Carbon.app.tar ~/Projects/
cd ~/Projects/
tar -xvf 2048-Carbon.app.tar
rm 2048-Carbon.app.tar
```

Get **2048-Carbon.app** package from `~/Projects/` directory.

## Mac OS X Development Environment

Xcode 2:

![Xcode 2 Mac OS X 10.4 Screenshot](../../image/Xcode-MacOSX-10_4-Screenshot.png)

Interface Builder 2:

![Interface Builder 2 Mac OS X 10.4 Screenshot](../../image/InterfaceBuilder-MacOSX-10_4-Screenshot.png)

## Versions

* Mac OS X 10.4.11 (Build 8S2167)
* Xcode 2.5

    * Xcode IDE: 799.0
    * Xcode Core: 798.0
    * ToolSupport: 794.0

* Interface Builder 2.5.6 (489)

Compiler on Mac OS X 10.4.11 and x86/x86_64 platform:

```
cc -v
Using built-in specs.
Target: i686-apple-darwin8
Configured with: /var/tmp/gcc/gcc-5370~2/src/configure --disable-checking -enable-werror --prefix=/usr --mandir=/share/man --enable-languages=c,objc,c++,obj-c++ --program-transform-name=/^[cg][^.-]*$/s/$/-4.0/ --with-gxx-include-dir=/include/c++/4.0.0 --with-slibdir=/usr/lib --build=i686-apple-darwin8 --with-arch=nocona --with-tune=generic --program-prefix= --host=i686-apple-darwin8 --target=i686-apple-darwin8
Thread model: posix
gcc version 4.0.1 (Apple Inc. build 5370)
```
