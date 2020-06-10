Binary Information
==================

Dependencies were obtained by using `ldd` command.

### Sizes

```
$ ls -lh 2048-*
-rwxrwxr-x. 1 exl exl 19K Jun 10 23:06 2048-Gtk1
-rwxrwxr-x. 1 exl exl 19K Jun 10 23:08 2048-Gtk2
-rwxrwxr-x. 1 exl exl 19K Jun 10 23:09 2048-Gtk3
-rwxrwxr-x. 1 exl exl 34K Jun 10 23:12 2048-MotoMAGX_E8
-rwxrwxr-x. 1 exl exl 34K Jun 10 23:12 2048-MotoMAGX_EM30
-rwxrwxr-x. 1 exl exl 34K Jun 10 23:12 2048-MotoMAGX_EM35
-rwxrwxr-x. 1 exl exl 33K Jun 10 23:12 2048-MotoMAGX_U9
-rwxrwxr-x. 1 exl exl 33K Jun 10 23:12 2048-MotoMAGX_V8
-rwxrwxr-x. 1 exl exl 34K Jun 10 23:12 2048-MotoMAGX_VE66
-rwxrwxr-x. 1 exl exl 33K Jun 10 23:12 2048-MotoMAGX_Z6
-rwxrwxr-x. 1 exl exl 33K Jun 10 23:12 2048-MotoMAGX_Z6W
-rwxrwxr-x. 1 exl exl 33K Jun 10 23:12 2048-MotoMAGX_ZN5
-rwxrwxr-x. 1 exl exl 28K Jun 10 23:09 2048-Qt1
-rwxrwxr-x. 1 exl exl 36K Jun 10 23:09 2048-Qt2
-rwxrwxr-x. 1 exl exl 45K Jun 10 23:09 2048-Qt3
-rwxrwxr-x. 1 exl exl 28K Jun 10 23:11 2048-Qt4
-rwxrwxr-x. 1 exl exl 28K Jun 10 23:11 2048-Qt5
```

### 2048-Qt5

```
$ ldd 2048-Qt5
	linux-vdso.so.1 (0x00007ffcfebf1000)
	libQt5Widgets.so.5 => /lib64/libQt5Widgets.so.5 (0x00007ff1a5797000)
	libQt5Gui.so.5 => /lib64/libQt5Gui.so.5 (0x00007ff1a52a8000)
	libQt5Core.so.5 => /lib64/libQt5Core.so.5 (0x00007ff1a4db5000)
	libstdc++.so.6 => /lib64/libstdc++.so.6 (0x00007ff1a4bc5000)
	libm.so.6 => /lib64/libm.so.6 (0x00007ff1a4a7f000)
	libgcc_s.so.1 => /lib64/libgcc_s.so.1 (0x00007ff1a4a64000)
	libc.so.6 => /lib64/libc.so.6 (0x00007ff1a4898000)
	libpthread.so.0 => /lib64/libpthread.so.0 (0x00007ff1a4876000)
	libGL.so.1 => /lib64/libGL.so.1 (0x00007ff1a47ee000)
	libpng16.so.16 => /lib64/libpng16.so.16 (0x00007ff1a47b7000)
	libz.so.1 => /lib64/libz.so.1 (0x00007ff1a479d000)
	libharfbuzz.so.0 => /lib64/libharfbuzz.so.0 (0x00007ff1a46bb000)
	libsystemd.so.0 => /lib64/libsystemd.so.0 (0x00007ff1a4602000)
	libicui18n.so.65 => /lib64/libicui18n.so.65 (0x00007ff1a42fb000)
	libicuuc.so.65 => /lib64/libicuuc.so.65 (0x00007ff1a4113000)
	libdl.so.2 => /lib64/libdl.so.2 (0x00007ff1a410c000)
	libpcre2-16.so.0 => /lib64/libpcre2-16.so.0 (0x00007ff1a4081000)
	libglib-2.0.so.0 => /lib64/libglib-2.0.so.0 (0x00007ff1a3f56000)
	/lib64/ld-linux-x86-64.so.2 (0x00007ff1a5e5a000)
	libGLX.so.0 => /lib64/libGLX.so.0 (0x00007ff1a3f20000)
	libX11.so.6 => /lib64/libX11.so.6 (0x00007ff1a3dd9000)
	libXext.so.6 => /lib64/libXext.so.6 (0x00007ff1a3dc4000)
	libGLdispatch.so.0 => /lib64/libGLdispatch.so.0 (0x00007ff1a3d0b000)
	libfreetype.so.6 => /lib64/libfreetype.so.6 (0x00007ff1a3c49000)
	libgraphite2.so.3 => /lib64/libgraphite2.so.3 (0x00007ff1a3c25000)
	librt.so.1 => /lib64/librt.so.1 (0x00007ff1a3c18000)
	liblzma.so.5 => /lib64/liblzma.so.5 (0x00007ff1a3bee000)
	liblz4.so.1 => /lib64/liblz4.so.1 (0x00007ff1a3bcd000)
	libgcrypt.so.20 => /lib64/libgcrypt.so.20 (0x00007ff1a3aac000)
	libicudata.so.65 => /lib64/libicudata.so.65 (0x00007ff1a1ff9000)
	libpcre.so.1 => /lib64/libpcre.so.1 (0x00007ff1a1f80000)
	libxcb.so.1 => /lib64/libxcb.so.1 (0x00007ff1a1f52000)
	libbz2.so.1 => /lib64/libbz2.so.1 (0x00007ff1a1f3f000)
	libgpg-error.so.0 => /lib64/libgpg-error.so.0 (0x00007ff1a1f1b000)
	libXau.so.6 => /lib64/libXau.so.6 (0x00007ff1a1f15000)
$ ldd 2048-Qt5 | wc -l
	36
```

### 2048-Qt4

```
$ ldd 2048-Qt4
	linux-vdso.so.1 (0x00007ffd3cf90000)
	libQtGui.so.4 => /lib64/libQtGui.so.4 (0x00007f36d9c1b000)
	libQtCore.so.4 => /lib64/libQtCore.so.4 (0x00007f36d9903000)
	libstdc++.so.6 => /lib64/libstdc++.so.6 (0x00007f36d9713000)
	libm.so.6 => /lib64/libm.so.6 (0x00007f36d95cd000)
	libgcc_s.so.1 => /lib64/libgcc_s.so.1 (0x00007f36d95b2000)
	libc.so.6 => /lib64/libc.so.6 (0x00007f36d93e8000)
	libpthread.so.0 => /lib64/libpthread.so.0 (0x00007f36d93c4000)
	libglib-2.0.so.0 => /lib64/libglib-2.0.so.0 (0x00007f36d9299000)
	libpng16.so.16 => /lib64/libpng16.so.16 (0x00007f36d9262000)
	libz.so.1 => /lib64/libz.so.1 (0x00007f36d9248000)
	libfreetype.so.6 => /lib64/libfreetype.so.6 (0x00007f36d9186000)
	libgobject-2.0.so.0 => /lib64/libgobject-2.0.so.0 (0x00007f36d912d000)
	libSM.so.6 => /lib64/libSM.so.6 (0x00007f36d9120000)
	libICE.so.6 => /lib64/libICE.so.6 (0x00007f36d9102000)
	libXi.so.6 => /lib64/libXi.so.6 (0x00007f36d90f0000)
	libXrender.so.1 => /lib64/libXrender.so.1 (0x00007f36d90e3000)
	libXrandr.so.2 => /lib64/libXrandr.so.2 (0x00007f36d90d6000)
	libXfixes.so.3 => /lib64/libXfixes.so.3 (0x00007f36d90cd000)
	libXcursor.so.1 => /lib64/libXcursor.so.1 (0x00007f36d90be000)
	libXinerama.so.1 => /lib64/libXinerama.so.1 (0x00007f36d90b9000)
	libfontconfig.so.1 => /lib64/libfontconfig.so.1 (0x00007f36d906e000)
	libXext.so.6 => /lib64/libXext.so.6 (0x00007f36d9059000)
	libX11.so.6 => /lib64/libX11.so.6 (0x00007f36d8f12000)
	libdl.so.2 => /lib64/libdl.so.2 (0x00007f36d8f0b000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f36da810000)
	libpcre.so.1 => /lib64/libpcre.so.1 (0x00007f36d8e90000)
	libbz2.so.1 => /lib64/libbz2.so.1 (0x00007f36d8e7d000)
	libffi.so.6 => /lib64/libffi.so.6 (0x00007f36d8e72000)
	libuuid.so.1 => /lib64/libuuid.so.1 (0x00007f36d8e69000)
	libexpat.so.1 => /lib64/libexpat.so.1 (0x00007f36d8e3a000)
	libxcb.so.1 => /lib64/libxcb.so.1 (0x00007f36d8e0c000)
	libXau.so.6 => /lib64/libXau.so.6 (0x00007f36d8e06000)
$ ldd 2048-Qt4 | wc -l
	33
```

### 2048-Qt3

```
$ ldd 2048-Qt3
	linux-vdso.so.1 (0x00007ffca01a0000)
	libqt-mt.so.3 => /usr/lib64/qt-3.3/lib/libqt-mt.so.3 (0x00007f0b0f2c4000)
	libstdc++.so.6 => /lib64/libstdc++.so.6 (0x00007f0b0f0af000)
	libm.so.6 => /lib64/libm.so.6 (0x00007f0b0ef69000)
	libgcc_s.so.1 => /lib64/libgcc_s.so.1 (0x00007f0b0ef4e000)
	libc.so.6 => /lib64/libc.so.6 (0x00007f0b0ed84000)
	libmng.so.2 => /lib64/libmng.so.2 (0x00007f0b0ed0f000)
	libjpeg.so.62 => /lib64/libjpeg.so.62 (0x00007f0b0ec88000)
	libpng16.so.16 => /lib64/libpng16.so.16 (0x00007f0b0ec51000)
	libz.so.1 => /lib64/libz.so.1 (0x00007f0b0ec37000)
	libXi.so.6 => /lib64/libXi.so.6 (0x00007f0b0ec25000)
	libXrender.so.1 => /lib64/libXrender.so.1 (0x00007f0b0ec18000)
	libXrandr.so.2 => /lib64/libXrandr.so.2 (0x00007f0b0ec0b000)
	libXcursor.so.1 => /lib64/libXcursor.so.1 (0x00007f0b0ebfc000)
	libXinerama.so.1 => /lib64/libXinerama.so.1 (0x00007f0b0ebf7000)
	libXft.so.2 => /lib64/libXft.so.2 (0x00007f0b0ebdd000)
	libfreetype.so.6 => /lib64/libfreetype.so.6 (0x00007f0b0eb1b000)
	libfontconfig.so.1 => /lib64/libfontconfig.so.1 (0x00007f0b0ead0000)
	libXext.so.6 => /lib64/libXext.so.6 (0x00007f0b0eabb000)
	libX11.so.6 => /lib64/libX11.so.6 (0x00007f0b0e972000)
	libSM.so.6 => /lib64/libSM.so.6 (0x00007f0b0e967000)
	libICE.so.6 => /lib64/libICE.so.6 (0x00007f0b0e949000)
	libdl.so.2 => /lib64/libdl.so.2 (0x00007f0b0e942000)
	libpthread.so.0 => /lib64/libpthread.so.0 (0x00007f0b0e920000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f0b0fbc0000)
	liblcms2.so.2 => /lib64/liblcms2.so.2 (0x00007f0b0e8c0000)
	libXfixes.so.3 => /lib64/libXfixes.so.3 (0x00007f0b0e8b5000)
	libbz2.so.1 => /lib64/libbz2.so.1 (0x00007f0b0e8a2000)
	libexpat.so.1 => /lib64/libexpat.so.1 (0x00007f0b0e873000)
	libxcb.so.1 => /lib64/libxcb.so.1 (0x00007f0b0e847000)
	libuuid.so.1 => /lib64/libuuid.so.1 (0x00007f0b0e83e000)
	libXau.so.6 => /lib64/libXau.so.6 (0x00007f0b0e836000)
$ ldd 2048-Qt3 | wc -l
	32
```

### 2048-Qt2

```
$ ldd 2048-Qt2
	linux-vdso.so.1 (0x00007ffe5fbf4000)
	libqt2.so.2 => /home/exl/Projects/qt2/src/libqt2.so.2 (0x00007fb42321e000)
	libstdc++.so.6 => /lib64/libstdc++.so.6 (0x00007fb423009000)
	libm.so.6 => /lib64/libm.so.6 (0x00007fb422ec3000)
	libgcc_s.so.1 => /lib64/libgcc_s.so.1 (0x00007fb422ea8000)
	libc.so.6 => /lib64/libc.so.6 (0x00007fb422cde000)
	libfontconfig.so.1 => /lib64/libfontconfig.so.1 (0x00007fb422c93000)
	libSM.so.6 => /lib64/libSM.so.6 (0x00007fb422c86000)
	libICE.so.6 => /lib64/libICE.so.6 (0x00007fb422c68000)
	libX11.so.6 => /lib64/libX11.so.6 (0x00007fb422b21000)
	libXext.so.6 => /lib64/libXext.so.6 (0x00007fb422b0c000)
	libjpeg.so.62 => /lib64/libjpeg.so.62 (0x00007fb422a87000)
	libXft.so.2 => /lib64/libXft.so.2 (0x00007fb422a6d000)
	libmng.so.2 => /lib64/libmng.so.2 (0x00007fb4229f6000)
	libGL.so.1 => /lib64/libGL.so.1 (0x00007fb42296e000)
	libpng16.so.16 => /lib64/libpng16.so.16 (0x00007fb422937000)
	libz.so.1 => /lib64/libz.so.1 (0x00007fb42291d000)
	libXmu.so.6 => /lib64/libXmu.so.6 (0x00007fb422900000)
	libpthread.so.0 => /lib64/libpthread.so.0 (0x00007fb4228de000)
	/lib64/ld-linux-x86-64.so.2 (0x00007fb423832000)
	libfreetype.so.6 => /lib64/libfreetype.so.6 (0x00007fb42281a000)
	libexpat.so.1 => /lib64/libexpat.so.1 (0x00007fb4227eb000)
	libuuid.so.1 => /lib64/libuuid.so.1 (0x00007fb4227e2000)
	libxcb.so.1 => /lib64/libxcb.so.1 (0x00007fb4227b6000)
	libdl.so.2 => /lib64/libdl.so.2 (0x00007fb4227af000)
	libXrender.so.1 => /lib64/libXrender.so.1 (0x00007fb4227a2000)
	liblcms2.so.2 => /lib64/liblcms2.so.2 (0x00007fb422740000)
	libGLX.so.0 => /lib64/libGLX.so.0 (0x00007fb42270c000)
	libGLdispatch.so.0 => /lib64/libGLdispatch.so.0 (0x00007fb422653000)
	libXt.so.6 => /lib64/libXt.so.6 (0x00007fb4225e6000)
	libbz2.so.1 => /lib64/libbz2.so.1 (0x00007fb4225d3000)
	libXau.so.6 => /lib64/libXau.so.6 (0x00007fb4225cb000)
$ ldd 2048-Qt2 | wc -l
	32
```

### 2048-Qt1

```
$ ldd 2048-Qt1
	linux-vdso.so.1 (0x00007ffff04fb000)
	libqt1.so.1 => /home/exl/Projects/qt1/src/libqt1.so.1 (0x00007f3582c73000)
	libstdc++.so.6 => /lib64/libstdc++.so.6 (0x00007f3582a5e000)
	libm.so.6 => /lib64/libm.so.6 (0x00007f3582918000)
	libgcc_s.so.1 => /lib64/libgcc_s.so.1 (0x00007f35828fd000)
	libc.so.6 => /lib64/libc.so.6 (0x00007f3582733000)
	libX11.so.6 => /lib64/libX11.so.6 (0x00007f35825ec000)
	libXext.so.6 => /lib64/libXext.so.6 (0x00007f35825d5000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f3582e53000)
	libxcb.so.1 => /lib64/libxcb.so.1 (0x00007f35825a9000)
	libdl.so.2 => /lib64/libdl.so.2 (0x00007f35825a2000)
	libXau.so.6 => /lib64/libXau.so.6 (0x00007f358259c000)
$ ldd 2048-Qt1 | wc -l
	12
```

### 2048-Gtk3

```
$ ldd 2048-Gtk3
	linux-vdso.so.1 (0x00007ffff9f72000)
	libgtk-3.so.0 => /lib64/libgtk-3.so.0 (0x00007f8fc35c2000)
	libgdk-3.so.0 => /lib64/libgdk-3.so.0 (0x00007f8fc34ba000)
	libpangocairo-1.0.so.0 => /lib64/libpangocairo-1.0.so.0 (0x00007f8fc34a8000)
	libpango-1.0.so.0 => /lib64/libpango-1.0.so.0 (0x00007f8fc3459000)
	libharfbuzz.so.0 => /lib64/libharfbuzz.so.0 (0x00007f8fc3377000)
	libatk-1.0.so.0 => /lib64/libatk-1.0.so.0 (0x00007f8fc334d000)
	libcairo-gobject.so.2 => /lib64/libcairo-gobject.so.2 (0x00007f8fc333f000)
	libcairo.so.2 => /lib64/libcairo.so.2 (0x00007f8fc3217000)
	libgdk_pixbuf-2.0.so.0 => /lib64/libgdk_pixbuf-2.0.so.0 (0x00007f8fc31ec000)
	libgio-2.0.so.0 => /lib64/libgio-2.0.so.0 (0x00007f8fc3008000)
	libgobject-2.0.so.0 => /lib64/libgobject-2.0.so.0 (0x00007f8fc2faf000)
	libglib-2.0.so.0 => /lib64/libglib-2.0.so.0 (0x00007f8fc2e84000)
	libm.so.6 => /lib64/libm.so.6 (0x00007f8fc2d3c000)
	libc.so.6 => /lib64/libc.so.6 (0x00007f8fc2b72000)
	libgmodule-2.0.so.0 => /lib64/libgmodule-2.0.so.0 (0x00007f8fc2b6c000)
	libX11.so.6 => /lib64/libX11.so.6 (0x00007f8fc2a25000)
	libXi.so.6 => /lib64/libXi.so.6 (0x00007f8fc2a13000)
	libXfixes.so.3 => /lib64/libXfixes.so.3 (0x00007f8fc2a0a000)
	libatk-bridge-2.0.so.0 => /lib64/libatk-bridge-2.0.so.0 (0x00007f8fc29cf000)
	libwayland-client.so.0 => /lib64/libwayland-client.so.0 (0x00007f8fc29be000)
	libepoxy.so.0 => /lib64/libepoxy.so.0 (0x00007f8fc288b000)
	libfribidi.so.0 => /lib64/libfribidi.so.0 (0x00007f8fc286c000)
	libpangoft2-1.0.so.0 => /lib64/libpangoft2-1.0.so.0 (0x00007f8fc2853000)
	libfontconfig.so.1 => /lib64/libfontconfig.so.1 (0x00007f8fc2808000)
	libfreetype.so.6 => /lib64/libfreetype.so.6 (0x00007f8fc2744000)
	libpthread.so.0 => /lib64/libpthread.so.0 (0x00007f8fc2722000)
	libXinerama.so.1 => /lib64/libXinerama.so.1 (0x00007f8fc271d000)
	libXrandr.so.2 => /lib64/libXrandr.so.2 (0x00007f8fc2710000)
	libXcursor.so.1 => /lib64/libXcursor.so.1 (0x00007f8fc2703000)
	libXcomposite.so.1 => /lib64/libXcomposite.so.1 (0x00007f8fc26fe000)
	libXdamage.so.1 => /lib64/libXdamage.so.1 (0x00007f8fc26f7000)
	libxkbcommon.so.0 => /lib64/libxkbcommon.so.0 (0x00007f8fc26b4000)
	libwayland-cursor.so.0 => /lib64/libwayland-cursor.so.0 (0x00007f8fc26a9000)
	libwayland-egl.so.1 => /lib64/libwayland-egl.so.1 (0x00007f8fc26a4000)
	libXext.so.6 => /lib64/libXext.so.6 (0x00007f8fc268f000)
	librt.so.1 => /lib64/librt.so.1 (0x00007f8fc2684000)
	libthai.so.0 => /lib64/libthai.so.0 (0x00007f8fc2676000)
	libgraphite2.so.3 => /lib64/libgraphite2.so.3 (0x00007f8fc2652000)
	libpixman-1.so.0 => /lib64/libpixman-1.so.0 (0x00007f8fc25a6000)
	libpng16.so.16 => /lib64/libpng16.so.16 (0x00007f8fc256f000)
	libxcb-shm.so.0 => /lib64/libxcb-shm.so.0 (0x00007f8fc256a000)
	libxcb.so.1 => /lib64/libxcb.so.1 (0x00007f8fc253e000)
	libxcb-render.so.0 => /lib64/libxcb-render.so.0 (0x00007f8fc252c000)
	libXrender.so.1 => /lib64/libXrender.so.1 (0x00007f8fc251f000)
	libz.so.1 => /lib64/libz.so.1 (0x00007f8fc2505000)
	libmount.so.1 => /lib64/libmount.so.1 (0x00007f8fc24a5000)
	libselinux.so.1 => /lib64/libselinux.so.1 (0x00007f8fc2478000)
	libresolv.so.2 => /lib64/libresolv.so.2 (0x00007f8fc245c000)
	libffi.so.6 => /lib64/libffi.so.6 (0x00007f8fc2451000)
	libpcre.so.1 => /lib64/libpcre.so.1 (0x00007f8fc23d8000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f8fc3db6000)
	libdl.so.2 => /lib64/libdl.so.2 (0x00007f8fc23d1000)
	libdbus-1.so.3 => /lib64/libdbus-1.so.3 (0x00007f8fc237a000)
	libatspi.so.0 => /lib64/libatspi.so.0 (0x00007f8fc233f000)
	libexpat.so.1 => /lib64/libexpat.so.1 (0x00007f8fc2310000)
	libbz2.so.1 => /lib64/libbz2.so.1 (0x00007f8fc22fd000)
	libdatrie.so.1 => /lib64/libdatrie.so.1 (0x00007f8fc22f3000)
	libXau.so.6 => /lib64/libXau.so.6 (0x00007f8fc22ed000)
	libblkid.so.1 => /lib64/libblkid.so.1 (0x00007f8fc2298000)
	libpcre2-8.so.0 => /lib64/libpcre2-8.so.0 (0x00007f8fc21ff000)
	libsystemd.so.0 => /lib64/libsystemd.so.0 (0x00007f8fc2148000)
	liblzma.so.5 => /lib64/liblzma.so.5 (0x00007f8fc211e000)
	liblz4.so.1 => /lib64/liblz4.so.1 (0x00007f8fc20fd000)
	libgcrypt.so.20 => /lib64/libgcrypt.so.20 (0x00007f8fc1fda000)
	libgcc_s.so.1 => /lib64/libgcc_s.so.1 (0x00007f8fc1fbf000)
	libgpg-error.so.0 => /lib64/libgpg-error.so.0 (0x00007f8fc1f9b000)
$ ldd 2048-Gtk3 | wc -l
	67
```

### 2048-Gtk2

```
$ ldd 2048-Gtk2
	linux-vdso.so.1 (0x00007ffe3d7bf000)
	libglib-2.0.so.0 => /lib64/libglib-2.0.so.0 (0x00007f51b731d000)
	libgobject-2.0.so.0 => /lib64/libgobject-2.0.so.0 (0x00007f51b72c4000)
	libatk-1.0.so.0 => /lib64/libatk-1.0.so.0 (0x00007f51b729a000)
	libgio-2.0.so.0 => /lib64/libgio-2.0.so.0 (0x00007f51b70b6000)
	libgthread-2.0.so.0 => /lib64/libgthread-2.0.so.0 (0x00007f51b70b1000)
	libgmodule-2.0.so.0 => /lib64/libgmodule-2.0.so.0 (0x00007f51b70ab000)
	libgdk_pixbuf-2.0.so.0 => /lib64/libgdk_pixbuf-2.0.so.0 (0x00007f51b707e000)
	libcairo.so.2 => /lib64/libcairo.so.2 (0x00007f51b6f56000)
	libharfbuzz.so.0 => /lib64/libharfbuzz.so.0 (0x00007f51b6e74000)
	libpango-1.0.so.0 => /lib64/libpango-1.0.so.0 (0x00007f51b6e25000)
	libpangocairo-1.0.so.0 => /lib64/libpangocairo-1.0.so.0 (0x00007f51b6e13000)
	libpangoft2-1.0.so.0 => /lib64/libpangoft2-1.0.so.0 (0x00007f51b6dfa000)
	libpangoxft-1.0.so.0 => /lib64/libpangoxft-1.0.so.0 (0x00007f51b6dec000)
	libgdk-x11-2.0.so.0 => /lib64/libgdk-x11-2.0.so.0 (0x00007f51b6d1c000)
	libgtk-x11-2.0.so.0 => /lib64/libgtk-x11-2.0.so.0 (0x00007f51b6869000)
	libm.so.6 => /lib64/libm.so.6 (0x00007f51b6723000)
	libc.so.6 => /lib64/libc.so.6 (0x00007f51b6559000)
	libpcre.so.1 => /lib64/libpcre.so.1 (0x00007f51b64e0000)
	libpthread.so.0 => /lib64/libpthread.so.0 (0x00007f51b64bc000)
	libffi.so.6 => /lib64/libffi.so.6 (0x00007f51b64b1000)
	libz.so.1 => /lib64/libz.so.1 (0x00007f51b6497000)
	libmount.so.1 => /lib64/libmount.so.1 (0x00007f51b6437000)
	libselinux.so.1 => /lib64/libselinux.so.1 (0x00007f51b640a000)
	libresolv.so.2 => /lib64/libresolv.so.2 (0x00007f51b63f0000)
	libdl.so.2 => /lib64/libdl.so.2 (0x00007f51b63e7000)
	libpng16.so.16 => /lib64/libpng16.so.16 (0x00007f51b63b0000)
	libpixman-1.so.0 => /lib64/libpixman-1.so.0 (0x00007f51b6304000)
	libfontconfig.so.1 => /lib64/libfontconfig.so.1 (0x00007f51b62b9000)
	libfreetype.so.6 => /lib64/libfreetype.so.6 (0x00007f51b61f7000)
	libxcb-shm.so.0 => /lib64/libxcb-shm.so.0 (0x00007f51b61f2000)
	libxcb.so.1 => /lib64/libxcb.so.1 (0x00007f51b61c4000)
	libxcb-render.so.0 => /lib64/libxcb-render.so.0 (0x00007f51b61b4000)
	libXrender.so.1 => /lib64/libXrender.so.1 (0x00007f51b61a7000)
	libX11.so.6 => /lib64/libX11.so.6 (0x00007f51b6060000)
	libXext.so.6 => /lib64/libXext.so.6 (0x00007f51b604b000)
	librt.so.1 => /lib64/librt.so.1 (0x00007f51b6040000)
	libgraphite2.so.3 => /lib64/libgraphite2.so.3 (0x00007f51b601a000)
	libfribidi.so.0 => /lib64/libfribidi.so.0 (0x00007f51b5ffb000)
	libthai.so.0 => /lib64/libthai.so.0 (0x00007f51b5fef000)
	libXft.so.2 => /lib64/libXft.so.2 (0x00007f51b5fd5000)
	libXinerama.so.1 => /lib64/libXinerama.so.1 (0x00007f51b5fd0000)
	libXi.so.6 => /lib64/libXi.so.6 (0x00007f51b5fbc000)
	libXrandr.so.2 => /lib64/libXrandr.so.2 (0x00007f51b5faf000)
	libXcursor.so.1 => /lib64/libXcursor.so.1 (0x00007f51b5fa2000)
	libXcomposite.so.1 => /lib64/libXcomposite.so.1 (0x00007f51b5f9d000)
	libXdamage.so.1 => /lib64/libXdamage.so.1 (0x00007f51b5f98000)
	libXfixes.so.3 => /lib64/libXfixes.so.3 (0x00007f51b5f8f000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f51b746f000)
	libblkid.so.1 => /lib64/libblkid.so.1 (0x00007f51b5f3a000)
	libpcre2-8.so.0 => /lib64/libpcre2-8.so.0 (0x00007f51b5ea1000)
	libexpat.so.1 => /lib64/libexpat.so.1 (0x00007f51b5e72000)
	libbz2.so.1 => /lib64/libbz2.so.1 (0x00007f51b5e5f000)
	libXau.so.6 => /lib64/libXau.so.6 (0x00007f51b5e59000)
	libdatrie.so.1 => /lib64/libdatrie.so.1 (0x00007f51b5e4d000)
$ ldd 2048-Gtk2 | wc -l
	55
```

### 2048-Gtk1

```
$ ldd 2048-Gtk1
	linux-vdso.so.1 (0x00007ffe889d8000)
	libgtk-1.2.so.0 => /lib64/libgtk-1.2.so.0 (0x00007f390c9b1000)
	libgdk-1.2.so.0 => /lib64/libgdk-1.2.so.0 (0x00007f390c96b000)
	libXi.so.6 => /lib64/libXi.so.6 (0x00007f390c959000)
	libXext.so.6 => /lib64/libXext.so.6 (0x00007f390c944000)
	libX11.so.6 => /lib64/libX11.so.6 (0x00007f390c7fd000)
	libm.so.6 => /lib64/libm.so.6 (0x00007f390c6b7000)
	libglib-1.2.so.0 => /lib64/libglib-1.2.so.0 (0x00007f390c683000)
	libc.so.6 => /lib64/libc.so.6 (0x00007f390c4b9000)
	libgmodule-1.2.so.0 => /lib64/libgmodule-1.2.so.0 (0x00007f390c4b3000)
	libxcb.so.1 => /lib64/libxcb.so.1 (0x00007f390c487000)
	libdl.so.2 => /lib64/libdl.so.2 (0x00007f390c480000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f390cb66000)
	libXau.so.6 => /lib64/libXau.so.6 (0x00007f390c478000)
$ ldd 2048-Gtk1 | wc -l
	14
```
