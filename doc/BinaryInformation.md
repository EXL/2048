Binary Information
==================

Dependencies were obtained by using `ldd` command.

### Sizes

```
$ ls -lh 2048-*
-rwxrwxr-x. 1 exl exl 27K Jun  5 19:48 2048-Gtk1
-rwxrwxr-x. 1 exl exl 31K Jun  5 15:09 2048-Gtk2
-rwxrwxr-x. 1 exl exl 31K Jun  5 15:09 2048-Gtk3
-rwxrwxr-x. 1 exl exl 36K Jun  5 15:11 2048-Qt1
-rwxrwxr-x. 1 exl exl 44K Jun  5 15:14 2048-Qt2
-rwxrwxr-x. 1 exl exl 48K Jun  5 20:48 2048-Qt3
-rwxrwxr-x. 1 exl exl 36K Jun  5 15:11 2048-Qt4
-rwxrwxr-x. 1 exl exl 35K Jun  5 15:10 2048-Qt5
```

### 2048-Qt5

```
$ ldd 2048-Qt5
	linux-vdso.so.1 (0x00007ffc3a107000)
	libQt5Widgets.so.5 => /lib64/libQt5Widgets.so.5 (0x00007fa7106ab000)
	libQt5Gui.so.5 => /lib64/libQt5Gui.so.5 (0x00007fa71016c000)
	libQt5Core.so.5 => /lib64/libQt5Core.so.5 (0x00007fa70fc38000)
	libstdc++.so.6 => /lib64/libstdc++.so.6 (0x00007fa70fa3e000)
	libm.so.6 => /lib64/libm.so.6 (0x00007fa70f8f8000)
	libgcc_s.so.1 => /lib64/libgcc_s.so.1 (0x00007fa70f8de000)
	libc.so.6 => /lib64/libc.so.6 (0x00007fa70f713000)
	libpthread.so.0 => /lib64/libpthread.so.0 (0x00007fa70f6f1000)
	libGL.so.1 => /lib64/libGL.so.1 (0x00007fa70f65d000)
	libpng16.so.16 => /lib64/libpng16.so.16 (0x00007fa70f627000)
	libz.so.1 => /lib64/libz.so.1 (0x00007fa70f60d000)
	libharfbuzz.so.0 => /lib64/libharfbuzz.so.0 (0x00007fa70f515000)
	libsystemd.so.0 => /lib64/libsystemd.so.0 (0x00007fa70f460000)
	libicui18n.so.63 => /lib64/libicui18n.so.63 (0x00007fa70f17d000)
	libicuuc.so.63 => /lib64/libicuuc.so.63 (0x00007fa70efaa000)
	libdl.so.2 => /lib64/libdl.so.2 (0x00007fa70efa3000)
	libpcre2-16.so.0 => /lib64/libpcre2-16.so.0 (0x00007fa70ef1f000)
	libglib-2.0.so.0 => /lib64/libglib-2.0.so.0 (0x00007fa70edf7000)
	/lib64/ld-linux-x86-64.so.2 (0x00007fa710d7c000)
	libGLX.so.0 => /lib64/libGLX.so.0 (0x00007fa70edc1000)
	libX11.so.6 => /lib64/libX11.so.6 (0x00007fa70ec7b000)
	libXext.so.6 => /lib64/libXext.so.6 (0x00007fa70ec66000)
	libGLdispatch.so.0 => /lib64/libGLdispatch.so.0 (0x00007fa70eba9000)
	libfreetype.so.6 => /lib64/libfreetype.so.6 (0x00007fa70eae8000)
	libgraphite2.so.3 => /lib64/libgraphite2.so.3 (0x00007fa70eac3000)
	librt.so.1 => /lib64/librt.so.1 (0x00007fa70eab6000)
	liblzma.so.5 => /lib64/liblzma.so.5 (0x00007fa70ea8d000)
	liblz4.so.1 => /lib64/liblz4.so.1 (0x00007fa70ea6c000)
	libgcrypt.so.20 => /lib64/libgcrypt.so.20 (0x00007fa70e94e000)
	libicudata.so.63 => /lib64/libicudata.so.63 (0x00007fa70cf5d000)
	libpcre.so.1 => /lib64/libpcre.so.1 (0x00007fa70cee9000)
	libxcb.so.1 => /lib64/libxcb.so.1 (0x00007fa70cebc000)
	libbz2.so.1 => /lib64/libbz2.so.1 (0x00007fa70cea8000)
	libgpg-error.so.0 => /lib64/libgpg-error.so.0 (0x00007fa70ce85000)
	libXau.so.6 => /lib64/libXau.so.6 (0x00007fa70ce7f000)
$ ldd 2048-Qt5 | wc -l
	36
```

### 2048-Qt4

```
$ ldd 2048-Qt4
	linux-vdso.so.1 (0x00007ffd189ff000)
	libQtGui.so.4 => /lib64/libQtGui.so.4 (0x00007f5c3b74f000)
	libQtCore.so.4 => /lib64/libQtCore.so.4 (0x00007f5c3b41e000)
	libstdc++.so.6 => /lib64/libstdc++.so.6 (0x00007f5c3b224000)
	libm.so.6 => /lib64/libm.so.6 (0x00007f5c3b0de000)
	libgcc_s.so.1 => /lib64/libgcc_s.so.1 (0x00007f5c3b0c4000)
	libc.so.6 => /lib64/libc.so.6 (0x00007f5c3aefb000)
	libpthread.so.0 => /lib64/libpthread.so.0 (0x00007f5c3aed7000)
	libglib-2.0.so.0 => /lib64/libglib-2.0.so.0 (0x00007f5c3adaf000)
	libpng16.so.16 => /lib64/libpng16.so.16 (0x00007f5c3ad79000)
	libz.so.1 => /lib64/libz.so.1 (0x00007f5c3ad5f000)
	libfreetype.so.6 => /lib64/libfreetype.so.6 (0x00007f5c3ac9e000)
	libgobject-2.0.so.0 => /lib64/libgobject-2.0.so.0 (0x00007f5c3ac42000)
	libSM.so.6 => /lib64/libSM.so.6 (0x00007f5c3ac35000)
	libICE.so.6 => /lib64/libICE.so.6 (0x00007f5c3ac17000)
	libXi.so.6 => /lib64/libXi.so.6 (0x00007f5c3ac05000)
	libXrender.so.1 => /lib64/libXrender.so.1 (0x00007f5c3abf8000)
	libXrandr.so.2 => /lib64/libXrandr.so.2 (0x00007f5c3abeb000)
	libXfixes.so.3 => /lib64/libXfixes.so.3 (0x00007f5c3abe2000)
	libXcursor.so.1 => /lib64/libXcursor.so.1 (0x00007f5c3abd3000)
	libXinerama.so.1 => /lib64/libXinerama.so.1 (0x00007f5c3abce000)
	libfontconfig.so.1 => /lib64/libfontconfig.so.1 (0x00007f5c3ab86000)
	libXext.so.6 => /lib64/libXext.so.6 (0x00007f5c3ab71000)
	libX11.so.6 => /lib64/libX11.so.6 (0x00007f5c3aa2b000)
	libdl.so.2 => /lib64/libdl.so.2 (0x00007f5c3aa24000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f5c3c35b000)
	libpcre.so.1 => /lib64/libpcre.so.1 (0x00007f5c3a9ae000)
	libbz2.so.1 => /lib64/libbz2.so.1 (0x00007f5c3a99a000)
	libffi.so.6 => /lib64/libffi.so.6 (0x00007f5c3a98f000)
	libuuid.so.1 => /lib64/libuuid.so.1 (0x00007f5c3a985000)
	libexpat.so.1 => /lib64/libexpat.so.1 (0x00007f5c3a957000)
	libxcb.so.1 => /lib64/libxcb.so.1 (0x00007f5c3a92a000)
	libXau.so.6 => /lib64/libXau.so.6 (0x00007f5c3a924000)
$ ldd 2048-Qt4 | wc -l
	33
```

### 2048-Qt3

```
$ ldd 2048-Qt3
	linux-vdso.so.1 (0x00007ffcbffa4000)
	libqt-mt.so.3 => /usr/lib64/qt-3.3/lib/libqt-mt.so.3 (0x00007feec2cba000)
	libstdc++.so.6 => /lib64/libstdc++.so.6 (0x00007feec2a9b000)
	libm.so.6 => /lib64/libm.so.6 (0x00007feec2955000)
	libgcc_s.so.1 => /lib64/libgcc_s.so.1 (0x00007feec293b000)
	libc.so.6 => /lib64/libc.so.6 (0x00007feec2772000)
	libmng.so.2 => /lib64/libmng.so.2 (0x00007feec26fd000)
	libjpeg.so.62 => /lib64/libjpeg.so.62 (0x00007feec2676000)
	libpng16.so.16 => /lib64/libpng16.so.16 (0x00007feec2640000)
	libz.so.1 => /lib64/libz.so.1 (0x00007feec2626000)
	libXi.so.6 => /lib64/libXi.so.6 (0x00007feec2614000)
	libXrender.so.1 => /lib64/libXrender.so.1 (0x00007feec2607000)
	libXrandr.so.2 => /lib64/libXrandr.so.2 (0x00007feec25fa000)
	libXcursor.so.1 => /lib64/libXcursor.so.1 (0x00007feec25eb000)
	libXinerama.so.1 => /lib64/libXinerama.so.1 (0x00007feec25e6000)
	libXft.so.2 => /lib64/libXft.so.2 (0x00007feec25cd000)
	libfreetype.so.6 => /lib64/libfreetype.so.6 (0x00007feec250c000)
	libfontconfig.so.1 => /lib64/libfontconfig.so.1 (0x00007feec24c4000)
	libXext.so.6 => /lib64/libXext.so.6 (0x00007feec24af000)
	libX11.so.6 => /lib64/libX11.so.6 (0x00007feec2367000)
	libSM.so.6 => /lib64/libSM.so.6 (0x00007feec235c000)
	libICE.so.6 => /lib64/libICE.so.6 (0x00007feec233e000)
	libdl.so.2 => /lib64/libdl.so.2 (0x00007feec2337000)
	libpthread.so.0 => /lib64/libpthread.so.0 (0x00007feec2315000)
	/lib64/ld-linux-x86-64.so.2 (0x00007feec35c9000)
	liblcms2.so.2 => /lib64/liblcms2.so.2 (0x00007feec22b6000)
	libXfixes.so.3 => /lib64/libXfixes.so.3 (0x00007feec22ab000)
	libbz2.so.1 => /lib64/libbz2.so.1 (0x00007feec2297000)
	libexpat.so.1 => /lib64/libexpat.so.1 (0x00007feec2269000)
	libxcb.so.1 => /lib64/libxcb.so.1 (0x00007feec223e000)
	libuuid.so.1 => /lib64/libuuid.so.1 (0x00007feec2234000)
	libXau.so.6 => /lib64/libXau.so.6 (0x00007feec222c000)
$ ldd 2048-Qt3 | wc -l
	32
```

### 2048-Qt2

```
$ ldd 2048-Qt2
	linux-vdso.so.1 (0x00007fffe49ee000)
	libqt2.so.2 => /home/exl/Projects/qt2/src/libqt2.so.2 (0x00007f6a23df1000)
	libstdc++.so.6 => /lib64/libstdc++.so.6 (0x00007f6a23bd2000)
	libm.so.6 => /lib64/libm.so.6 (0x00007f6a23a8c000)
	libgcc_s.so.1 => /lib64/libgcc_s.so.1 (0x00007f6a23a72000)
	libc.so.6 => /lib64/libc.so.6 (0x00007f6a238a9000)
	libfontconfig.so.1 => /lib64/libfontconfig.so.1 (0x00007f6a23861000)
	libSM.so.6 => /lib64/libSM.so.6 (0x00007f6a23854000)
	libICE.so.6 => /lib64/libICE.so.6 (0x00007f6a23836000)
	libX11.so.6 => /lib64/libX11.so.6 (0x00007f6a236f0000)
	libXext.so.6 => /lib64/libXext.so.6 (0x00007f6a236db000)
	libjpeg.so.62 => /lib64/libjpeg.so.62 (0x00007f6a23656000)
	libXft.so.2 => /lib64/libXft.so.2 (0x00007f6a2363d000)
	libmng.so.2 => /lib64/libmng.so.2 (0x00007f6a235c6000)
	libGL.so.1 => /lib64/libGL.so.1 (0x00007f6a23532000)
	libpng16.so.16 => /lib64/libpng16.so.16 (0x00007f6a234fc000)
	libz.so.1 => /lib64/libz.so.1 (0x00007f6a234e2000)
	libXmu.so.6 => /lib64/libXmu.so.6 (0x00007f6a234c5000)
	libpthread.so.0 => /lib64/libpthread.so.0 (0x00007f6a234a3000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f6a24405000)
	libfreetype.so.6 => /lib64/libfreetype.so.6 (0x00007f6a233e0000)
	libexpat.so.1 => /lib64/libexpat.so.1 (0x00007f6a233b2000)
	libuuid.so.1 => /lib64/libuuid.so.1 (0x00007f6a233a8000)
	libxcb.so.1 => /lib64/libxcb.so.1 (0x00007f6a2337d000)
	libdl.so.2 => /lib64/libdl.so.2 (0x00007f6a23376000)
	libXrender.so.1 => /lib64/libXrender.so.1 (0x00007f6a23369000)
	liblcms2.so.2 => /lib64/liblcms2.so.2 (0x00007f6a23308000)
	libGLX.so.0 => /lib64/libGLX.so.0 (0x00007f6a232d4000)
	libGLdispatch.so.0 => /lib64/libGLdispatch.so.0 (0x00007f6a23217000)
	libXt.so.6 => /lib64/libXt.so.6 (0x00007f6a231aa000)
	libbz2.so.1 => /lib64/libbz2.so.1 (0x00007f6a23196000)
	libXau.so.6 => /lib64/libXau.so.6 (0x00007f6a2318e000)
$ ldd 2048-Qt2 | wc -l
	32
```

### 2048-Qt1

```
$ ldd 2048-Qt1
	linux-vdso.so.1 (0x00007ffc089df000)
	libqt1.so.1 => /home/exl/Projects/qt1/src/libqt1.so.1 (0x00007fb641555000)
	libstdc++.so.6 => /lib64/libstdc++.so.6 (0x00007fb641336000)
	libm.so.6 => /lib64/libm.so.6 (0x00007fb6411f0000)
	libgcc_s.so.1 => /lib64/libgcc_s.so.1 (0x00007fb6411d6000)
	libc.so.6 => /lib64/libc.so.6 (0x00007fb64100d000)
	libX11.so.6 => /lib64/libX11.so.6 (0x00007fb640ec7000)
	libXext.so.6 => /lib64/libXext.so.6 (0x00007fb640eb0000)
	/lib64/ld-linux-x86-64.so.2 (0x00007fb641735000)
	libxcb.so.1 => /lib64/libxcb.so.1 (0x00007fb640e85000)
	libdl.so.2 => /lib64/libdl.so.2 (0x00007fb640e7e000)
	libXau.so.6 => /lib64/libXau.so.6 (0x00007fb640e78000)
$ ldd 2048-Qt1 | wc -l
	12
```

### 2048-Gtk3

```
$ ldd 2048-Gtk3
	linux-vdso.so.1 (0x00007ffdeb5f0000)
	libgtk-3.so.0 => /lib64/libgtk-3.so.0 (0x00007f7b9b41c000)
	libgdk-3.so.0 => /lib64/libgdk-3.so.0 (0x00007f7b9b318000)
	libpangocairo-1.0.so.0 => /lib64/libpangocairo-1.0.so.0 (0x00007f7b9b307000)
	libpango-1.0.so.0 => /lib64/libpango-1.0.so.0 (0x00007f7b9b2b9000)
	libharfbuzz.so.0 => /lib64/libharfbuzz.so.0 (0x00007f7b9b1c1000)
	libatk-1.0.so.0 => /lib64/libatk-1.0.so.0 (0x00007f7b9b198000)
	libcairo-gobject.so.2 => /lib64/libcairo-gobject.so.2 (0x00007f7b9b18a000)
	libcairo.so.2 => /lib64/libcairo.so.2 (0x00007f7b9b067000)
	libgdk_pixbuf-2.0.so.0 => /lib64/libgdk_pixbuf-2.0.so.0 (0x00007f7b9b03b000)
	libgio-2.0.so.0 => /lib64/libgio-2.0.so.0 (0x00007f7b9ae5f000)
	libgobject-2.0.so.0 => /lib64/libgobject-2.0.so.0 (0x00007f7b9ae03000)
	libglib-2.0.so.0 => /lib64/libglib-2.0.so.0 (0x00007f7b9acdb000)
	libstdc++.so.6 => /lib64/libstdc++.so.6 (0x00007f7b9aadf000)
	libm.so.6 => /lib64/libm.so.6 (0x00007f7b9a999000)
	libgcc_s.so.1 => /lib64/libgcc_s.so.1 (0x00007f7b9a97f000)
	libc.so.6 => /lib64/libc.so.6 (0x00007f7b9a7b6000)
	libgmodule-2.0.so.0 => /lib64/libgmodule-2.0.so.0 (0x00007f7b9a7b0000)
	libX11.so.6 => /lib64/libX11.so.6 (0x00007f7b9a66a000)
	libXi.so.6 => /lib64/libXi.so.6 (0x00007f7b9a656000)
	libXfixes.so.3 => /lib64/libXfixes.so.3 (0x00007f7b9a64d000)
	libatk-bridge-2.0.so.0 => /lib64/libatk-bridge-2.0.so.0 (0x00007f7b9a615000)
	libwayland-client.so.0 => /lib64/libwayland-client.so.0 (0x00007f7b9a604000)
	libepoxy.so.0 => /lib64/libepoxy.so.0 (0x00007f7b9a4d0000)
	libfribidi.so.0 => /lib64/libfribidi.so.0 (0x00007f7b9a4b1000)
	libpangoft2-1.0.so.0 => /lib64/libpangoft2-1.0.so.0 (0x00007f7b9a496000)
	libfontconfig.so.1 => /lib64/libfontconfig.so.1 (0x00007f7b9a44e000)
	libfreetype.so.6 => /lib64/libfreetype.so.6 (0x00007f7b9a38d000)
	libpthread.so.0 => /lib64/libpthread.so.0 (0x00007f7b9a36b000)
	libXinerama.so.1 => /lib64/libXinerama.so.1 (0x00007f7b9a366000)
	libXrandr.so.2 => /lib64/libXrandr.so.2 (0x00007f7b9a359000)
	libXcursor.so.1 => /lib64/libXcursor.so.1 (0x00007f7b9a34a000)
	libXcomposite.so.1 => /lib64/libXcomposite.so.1 (0x00007f7b9a345000)
	libXdamage.so.1 => /lib64/libXdamage.so.1 (0x00007f7b9a340000)
	libxkbcommon.so.0 => /lib64/libxkbcommon.so.0 (0x00007f7b9a2fd000)
	libwayland-cursor.so.0 => /lib64/libwayland-cursor.so.0 (0x00007f7b9a2f3000)
	libwayland-egl.so.1 => /lib64/libwayland-egl.so.1 (0x00007f7b9a2ee000)
	libXext.so.6 => /lib64/libXext.so.6 (0x00007f7b9a2d7000)
	librt.so.1 => /lib64/librt.so.1 (0x00007f7b9a2cc000)
	libthai.so.0 => /lib64/libthai.so.0 (0x00007f7b9a2c0000)
	libgraphite2.so.3 => /lib64/libgraphite2.so.3 (0x00007f7b9a29b000)
	libpixman-1.so.0 => /lib64/libpixman-1.so.0 (0x00007f7b9a1f3000)
	libpng16.so.16 => /lib64/libpng16.so.16 (0x00007f7b9a1bb000)
	libxcb-shm.so.0 => /lib64/libxcb-shm.so.0 (0x00007f7b9a1b6000)
	libxcb.so.1 => /lib64/libxcb.so.1 (0x00007f7b9a18b000)
	libxcb-render.so.0 => /lib64/libxcb-render.so.0 (0x00007f7b9a17b000)
	libXrender.so.1 => /lib64/libXrender.so.1 (0x00007f7b9a16e000)
	libz.so.1 => /lib64/libz.so.1 (0x00007f7b9a154000)
	libmount.so.1 => /lib64/libmount.so.1 (0x00007f7b9a0ef000)
	libselinux.so.1 => /lib64/libselinux.so.1 (0x00007f7b9a0c2000)
	libresolv.so.2 => /lib64/libresolv.so.2 (0x00007f7b9a0a9000)
	libffi.so.6 => /lib64/libffi.so.6 (0x00007f7b9a09e000)
	libpcre.so.1 => /lib64/libpcre.so.1 (0x00007f7b9a02a000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f7b9bb57000)
	libdl.so.2 => /lib64/libdl.so.2 (0x00007f7b9a021000)
	libdbus-1.so.3 => /lib64/libdbus-1.so.3 (0x00007f7b99fcb000)
	libatspi.so.0 => /lib64/libatspi.so.0 (0x00007f7b99f93000)
	libexpat.so.1 => /lib64/libexpat.so.1 (0x00007f7b99f65000)
	libbz2.so.1 => /lib64/libbz2.so.1 (0x00007f7b99f51000)
	libdatrie.so.1 => /lib64/libdatrie.so.1 (0x00007f7b99f45000)
	libXau.so.6 => /lib64/libXau.so.6 (0x00007f7b99f3f000)
	libblkid.so.1 => /lib64/libblkid.so.1 (0x00007f7b99ee8000)
	libpcre2-8.so.0 => /lib64/libpcre2-8.so.0 (0x00007f7b99e56000)
	libsystemd.so.0 => /lib64/libsystemd.so.0 (0x00007f7b99da3000)
	liblzma.so.5 => /lib64/liblzma.so.5 (0x00007f7b99d78000)
	liblz4.so.1 => /lib64/liblz4.so.1 (0x00007f7b99d57000)
	libgcrypt.so.20 => /lib64/libgcrypt.so.20 (0x00007f7b99c39000)
	libgpg-error.so.0 => /lib64/libgpg-error.so.0 (0x00007f7b99c16000)
$ ldd 2048-Gtk3 | wc -l
	68
```

### 2048-Gtk2

```
$ ldd 2048-Gtk2
	linux-vdso.so.1 (0x00007ffd20dde000)
	libglib-2.0.so.0 => /lib64/libglib-2.0.so.0 (0x00007f1431814000)
	libgobject-2.0.so.0 => /lib64/libgobject-2.0.so.0 (0x00007f14317b8000)
	libatk-1.0.so.0 => /lib64/libatk-1.0.so.0 (0x00007f143178f000)
	libgio-2.0.so.0 => /lib64/libgio-2.0.so.0 (0x00007f14315b3000)
	libgthread-2.0.so.0 => /lib64/libgthread-2.0.so.0 (0x00007f14315ae000)
	libgmodule-2.0.so.0 => /lib64/libgmodule-2.0.so.0 (0x00007f14315a8000)
	libgdk_pixbuf-2.0.so.0 => /lib64/libgdk_pixbuf-2.0.so.0 (0x00007f143157a000)
	libcairo.so.2 => /lib64/libcairo.so.2 (0x00007f1431457000)
	libpango-1.0.so.0 => /lib64/libpango-1.0.so.0 (0x00007f1431409000)
	libpangocairo-1.0.so.0 => /lib64/libpangocairo-1.0.so.0 (0x00007f14313f8000)
	libpangoft2-1.0.so.0 => /lib64/libpangoft2-1.0.so.0 (0x00007f14313df000)
	libpangoxft-1.0.so.0 => /lib64/libpangoxft-1.0.so.0 (0x00007f14313d3000)
	libgdk-x11-2.0.so.0 => /lib64/libgdk-x11-2.0.so.0 (0x00007f1431307000)
	libgtk-x11-2.0.so.0 => /lib64/libgtk-x11-2.0.so.0 (0x00007f1430e68000)
	libstdc++.so.6 => /lib64/libstdc++.so.6 (0x00007f1430c6e000)
	libm.so.6 => /lib64/libm.so.6 (0x00007f1430b28000)
	libgcc_s.so.1 => /lib64/libgcc_s.so.1 (0x00007f1430b0e000)
	libc.so.6 => /lib64/libc.so.6 (0x00007f1430945000)
	libpcre.so.1 => /lib64/libpcre.so.1 (0x00007f14308cf000)
	libpthread.so.0 => /lib64/libpthread.so.0 (0x00007f14308ad000)
	libffi.so.6 => /lib64/libffi.so.6 (0x00007f14308a2000)
	libz.so.1 => /lib64/libz.so.1 (0x00007f1430888000)
	libmount.so.1 => /lib64/libmount.so.1 (0x00007f1430825000)
	libselinux.so.1 => /lib64/libselinux.so.1 (0x00007f14307f8000)
	libresolv.so.2 => /lib64/libresolv.so.2 (0x00007f14307dd000)
	libdl.so.2 => /lib64/libdl.so.2 (0x00007f14307d6000)
	libpng16.so.16 => /lib64/libpng16.so.16 (0x00007f14307a0000)
	libpixman-1.so.0 => /lib64/libpixman-1.so.0 (0x00007f14306f8000)
	libfontconfig.so.1 => /lib64/libfontconfig.so.1 (0x00007f14306b0000)
	libfreetype.so.6 => /lib64/libfreetype.so.6 (0x00007f14305ef000)
	libxcb-shm.so.0 => /lib64/libxcb-shm.so.0 (0x00007f14305e8000)
	libxcb.so.1 => /lib64/libxcb.so.1 (0x00007f14305bd000)
	libxcb-render.so.0 => /lib64/libxcb-render.so.0 (0x00007f14305ad000)
	libXrender.so.1 => /lib64/libXrender.so.1 (0x00007f14305a0000)
	libX11.so.6 => /lib64/libX11.so.6 (0x00007f143045a000)
	libXext.so.6 => /lib64/libXext.so.6 (0x00007f1430445000)
	librt.so.1 => /lib64/librt.so.1 (0x00007f1430438000)
	libfribidi.so.0 => /lib64/libfribidi.so.0 (0x00007f1430419000)
	libthai.so.0 => /lib64/libthai.so.0 (0x00007f143040d000)
	libharfbuzz.so.0 => /lib64/libharfbuzz.so.0 (0x00007f1430315000)
	libXft.so.2 => /lib64/libXft.so.2 (0x00007f14302fc000)
	libXinerama.so.1 => /lib64/libXinerama.so.1 (0x00007f14302f5000)
	libXi.so.6 => /lib64/libXi.so.6 (0x00007f14302e3000)
	libXrandr.so.2 => /lib64/libXrandr.so.2 (0x00007f14302d6000)
	libXcursor.so.1 => /lib64/libXcursor.so.1 (0x00007f14302c9000)
	libXcomposite.so.1 => /lib64/libXcomposite.so.1 (0x00007f14302c4000)
	libXdamage.so.1 => /lib64/libXdamage.so.1 (0x00007f14302bf000)
	libXfixes.so.3 => /lib64/libXfixes.so.3 (0x00007f14302b4000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f1431963000)
	libblkid.so.1 => /lib64/libblkid.so.1 (0x00007f143025d000)
	libpcre2-8.so.0 => /lib64/libpcre2-8.so.0 (0x00007f14301cb000)
	libexpat.so.1 => /lib64/libexpat.so.1 (0x00007f143019d000)
	libbz2.so.1 => /lib64/libbz2.so.1 (0x00007f1430189000)
	libXau.so.6 => /lib64/libXau.so.6 (0x00007f1430181000)
	libdatrie.so.1 => /lib64/libdatrie.so.1 (0x00007f1430177000)
	libgraphite2.so.3 => /lib64/libgraphite2.so.3 (0x00007f1430152000)
$ ldd 2048-Gtk2 | wc -l
	57
```

### 2048-Gtk1

```
$ ldd 2048-Gtk1
	linux-vdso.so.1 (0x00007ffca27f7000)
	libgtk-1.2.so.0 => /lib64/libgtk-1.2.so.0 (0x00007f564ad5b000)
	libgdk-1.2.so.0 => /lib64/libgdk-1.2.so.0 (0x00007f564ad15000)
	libXi.so.6 => /lib64/libXi.so.6 (0x00007f564ad03000)
	libXext.so.6 => /lib64/libXext.so.6 (0x00007f564acee000)
	libX11.so.6 => /lib64/libX11.so.6 (0x00007f564aba8000)
	libglib-1.2.so.0 => /lib64/libglib-1.2.so.0 (0x00007f564ab76000)
	libstdc++.so.6 => /lib64/libstdc++.so.6 (0x00007f564a97a000)
	libm.so.6 => /lib64/libm.so.6 (0x00007f564a834000)
	libgcc_s.so.1 => /lib64/libgcc_s.so.1 (0x00007f564a81a000)
	libc.so.6 => /lib64/libc.so.6 (0x00007f564a651000)
	libgmodule-1.2.so.0 => /lib64/libgmodule-1.2.so.0 (0x00007f564a64b000)
	libxcb.so.1 => /lib64/libxcb.so.1 (0x00007f564a620000)
	libdl.so.2 => /lib64/libdl.so.2 (0x00007f564a617000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f564af0e000)
	libXau.so.6 => /lib64/libXau.so.6 (0x00007f564a611000)
$ ldd 2048-Gtk1 | wc -l
	16
```
