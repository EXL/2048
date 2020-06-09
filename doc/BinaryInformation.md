Binary Information
==================

Dependencies were obtained by using `ldd` command.

### Sizes

```
$ ls -lh 2048-*
-rwxrwxr-x. 1 exl exl 19K Jun  9 01:47 2048-Gtk1
-rwxrwxr-x. 1 exl exl 19K Jun  9 01:46 2048-Gtk2
-rwxrwxr-x. 1 exl exl 19K Jun  9 01:46 2048-Gtk3
-rwxrwxr-x. 1 exl exl 28K Jun  9 01:45 2048-Qt1
-rwxrwxr-x. 1 exl exl 36K Jun  9 01:44 2048-Qt2
-rwxrwxr-x. 1 exl exl 45K Jun  9 01:44 2048-Qt3
-rwxrwxr-x. 1 exl exl 28K Jun  9 01:43 2048-Qt4
-rwxrwxr-x. 1 exl exl 28K Jun  9 01:42 2048-Qt5
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
	linux-vdso.so.1 (0x00007ffd04171000)
	libgtk-3.so.0 => /lib64/libgtk-3.so.0 (0x00007f9f7cf43000)
	libgdk-3.so.0 => /lib64/libgdk-3.so.0 (0x00007f9f7ce3b000)
	libpangocairo-1.0.so.0 => /lib64/libpangocairo-1.0.so.0 (0x00007f9f7ce29000)
	libpango-1.0.so.0 => /lib64/libpango-1.0.so.0 (0x00007f9f7cdda000)
	libharfbuzz.so.0 => /lib64/libharfbuzz.so.0 (0x00007f9f7ccf8000)
	libatk-1.0.so.0 => /lib64/libatk-1.0.so.0 (0x00007f9f7ccce000)
	libcairo-gobject.so.2 => /lib64/libcairo-gobject.so.2 (0x00007f9f7ccc0000)
	libcairo.so.2 => /lib64/libcairo.so.2 (0x00007f9f7cb98000)
	libgdk_pixbuf-2.0.so.0 => /lib64/libgdk_pixbuf-2.0.so.0 (0x00007f9f7cb6d000)
	libgio-2.0.so.0 => /lib64/libgio-2.0.so.0 (0x00007f9f7c989000)
	libgobject-2.0.so.0 => /lib64/libgobject-2.0.so.0 (0x00007f9f7c930000)
	libglib-2.0.so.0 => /lib64/libglib-2.0.so.0 (0x00007f9f7c805000)
	libm.so.6 => /lib64/libm.so.6 (0x00007f9f7c6bd000)
	libc.so.6 => /lib64/libc.so.6 (0x00007f9f7c4f3000)
	libgmodule-2.0.so.0 => /lib64/libgmodule-2.0.so.0 (0x00007f9f7c4ed000)
	libX11.so.6 => /lib64/libX11.so.6 (0x00007f9f7c3a6000)
	libXi.so.6 => /lib64/libXi.so.6 (0x00007f9f7c394000)
	libXfixes.so.3 => /lib64/libXfixes.so.3 (0x00007f9f7c38b000)
	libatk-bridge-2.0.so.0 => /lib64/libatk-bridge-2.0.so.0 (0x00007f9f7c350000)
	libwayland-client.so.0 => /lib64/libwayland-client.so.0 (0x00007f9f7c33f000)
	libepoxy.so.0 => /lib64/libepoxy.so.0 (0x00007f9f7c20c000)
	libfribidi.so.0 => /lib64/libfribidi.so.0 (0x00007f9f7c1ed000)
	libpangoft2-1.0.so.0 => /lib64/libpangoft2-1.0.so.0 (0x00007f9f7c1d4000)
	libfontconfig.so.1 => /lib64/libfontconfig.so.1 (0x00007f9f7c189000)
	libfreetype.so.6 => /lib64/libfreetype.so.6 (0x00007f9f7c0c5000)
	libpthread.so.0 => /lib64/libpthread.so.0 (0x00007f9f7c0a3000)
	libXinerama.so.1 => /lib64/libXinerama.so.1 (0x00007f9f7c09e000)
	libXrandr.so.2 => /lib64/libXrandr.so.2 (0x00007f9f7c091000)
	libXcursor.so.1 => /lib64/libXcursor.so.1 (0x00007f9f7c084000)
	libXcomposite.so.1 => /lib64/libXcomposite.so.1 (0x00007f9f7c07f000)
	libXdamage.so.1 => /lib64/libXdamage.so.1 (0x00007f9f7c078000)
	libxkbcommon.so.0 => /lib64/libxkbcommon.so.0 (0x00007f9f7c035000)
	libwayland-cursor.so.0 => /lib64/libwayland-cursor.so.0 (0x00007f9f7c02a000)
	libwayland-egl.so.1 => /lib64/libwayland-egl.so.1 (0x00007f9f7c025000)
	libXext.so.6 => /lib64/libXext.so.6 (0x00007f9f7c010000)
	librt.so.1 => /lib64/librt.so.1 (0x00007f9f7c005000)
	libthai.so.0 => /lib64/libthai.so.0 (0x00007f9f7bff7000)
	libgraphite2.so.3 => /lib64/libgraphite2.so.3 (0x00007f9f7bfd3000)
	libpixman-1.so.0 => /lib64/libpixman-1.so.0 (0x00007f9f7bf27000)
	libpng16.so.16 => /lib64/libpng16.so.16 (0x00007f9f7bef0000)
	libxcb-shm.so.0 => /lib64/libxcb-shm.so.0 (0x00007f9f7beeb000)
	libxcb.so.1 => /lib64/libxcb.so.1 (0x00007f9f7bebf000)
	libxcb-render.so.0 => /lib64/libxcb-render.so.0 (0x00007f9f7bead000)
	libXrender.so.1 => /lib64/libXrender.so.1 (0x00007f9f7bea0000)
	libz.so.1 => /lib64/libz.so.1 (0x00007f9f7be86000)
	libmount.so.1 => /lib64/libmount.so.1 (0x00007f9f7be26000)
	libselinux.so.1 => /lib64/libselinux.so.1 (0x00007f9f7bdf9000)
	libresolv.so.2 => /lib64/libresolv.so.2 (0x00007f9f7bddd000)
	libffi.so.6 => /lib64/libffi.so.6 (0x00007f9f7bdd2000)
	libpcre.so.1 => /lib64/libpcre.so.1 (0x00007f9f7bd59000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f9f7d737000)
	libdl.so.2 => /lib64/libdl.so.2 (0x00007f9f7bd52000)
	libdbus-1.so.3 => /lib64/libdbus-1.so.3 (0x00007f9f7bcfb000)
	libatspi.so.0 => /lib64/libatspi.so.0 (0x00007f9f7bcc0000)
	libexpat.so.1 => /lib64/libexpat.so.1 (0x00007f9f7bc91000)
	libbz2.so.1 => /lib64/libbz2.so.1 (0x00007f9f7bc7e000)
	libdatrie.so.1 => /lib64/libdatrie.so.1 (0x00007f9f7bc74000)
	libXau.so.6 => /lib64/libXau.so.6 (0x00007f9f7bc6e000)
	libblkid.so.1 => /lib64/libblkid.so.1 (0x00007f9f7bc19000)
	libpcre2-8.so.0 => /lib64/libpcre2-8.so.0 (0x00007f9f7bb80000)
	libsystemd.so.0 => /lib64/libsystemd.so.0 (0x00007f9f7bac9000)
	liblzma.so.5 => /lib64/liblzma.so.5 (0x00007f9f7ba9f000)
	liblz4.so.1 => /lib64/liblz4.so.1 (0x00007f9f7ba7e000)
	libgcrypt.so.20 => /lib64/libgcrypt.so.20 (0x00007f9f7b95b000)
	libgcc_s.so.1 => /lib64/libgcc_s.so.1 (0x00007f9f7b940000)
	libgpg-error.so.0 => /lib64/libgpg-error.so.0 (0x00007f9f7b91c000)
$ ldd 2048-Gtk3 | wc -l
	67
```

### 2048-Gtk2

```
$ ldd 2048-Gtk2
	linux-vdso.so.1 (0x00007ffdc7dec000)
	libglib-2.0.so.0 => /lib64/libglib-2.0.so.0 (0x00007fe11bd67000)
	libgobject-2.0.so.0 => /lib64/libgobject-2.0.so.0 (0x00007fe11bd0e000)
	libatk-1.0.so.0 => /lib64/libatk-1.0.so.0 (0x00007fe11bce4000)
	libgio-2.0.so.0 => /lib64/libgio-2.0.so.0 (0x00007fe11bb00000)
	libgthread-2.0.so.0 => /lib64/libgthread-2.0.so.0 (0x00007fe11bafb000)
	libgmodule-2.0.so.0 => /lib64/libgmodule-2.0.so.0 (0x00007fe11baf5000)
	libgdk_pixbuf-2.0.so.0 => /lib64/libgdk_pixbuf-2.0.so.0 (0x00007fe11bac8000)
	libcairo.so.2 => /lib64/libcairo.so.2 (0x00007fe11b9a0000)
	libharfbuzz.so.0 => /lib64/libharfbuzz.so.0 (0x00007fe11b8be000)
	libpango-1.0.so.0 => /lib64/libpango-1.0.so.0 (0x00007fe11b86f000)
	libpangocairo-1.0.so.0 => /lib64/libpangocairo-1.0.so.0 (0x00007fe11b85d000)
	libpangoft2-1.0.so.0 => /lib64/libpangoft2-1.0.so.0 (0x00007fe11b844000)
	libpangoxft-1.0.so.0 => /lib64/libpangoxft-1.0.so.0 (0x00007fe11b836000)
	libgdk-x11-2.0.so.0 => /lib64/libgdk-x11-2.0.so.0 (0x00007fe11b766000)
	libgtk-x11-2.0.so.0 => /lib64/libgtk-x11-2.0.so.0 (0x00007fe11b2b3000)
	libm.so.6 => /lib64/libm.so.6 (0x00007fe11b16d000)
	libc.so.6 => /lib64/libc.so.6 (0x00007fe11afa3000)
	libpcre.so.1 => /lib64/libpcre.so.1 (0x00007fe11af2a000)
	libpthread.so.0 => /lib64/libpthread.so.0 (0x00007fe11af06000)
	libffi.so.6 => /lib64/libffi.so.6 (0x00007fe11aefb000)
	libz.so.1 => /lib64/libz.so.1 (0x00007fe11aee1000)
	libmount.so.1 => /lib64/libmount.so.1 (0x00007fe11ae81000)
	libselinux.so.1 => /lib64/libselinux.so.1 (0x00007fe11ae54000)
	libresolv.so.2 => /lib64/libresolv.so.2 (0x00007fe11ae3a000)
	libdl.so.2 => /lib64/libdl.so.2 (0x00007fe11ae31000)
	libpng16.so.16 => /lib64/libpng16.so.16 (0x00007fe11adfa000)
	libpixman-1.so.0 => /lib64/libpixman-1.so.0 (0x00007fe11ad4e000)
	libfontconfig.so.1 => /lib64/libfontconfig.so.1 (0x00007fe11ad03000)
	libfreetype.so.6 => /lib64/libfreetype.so.6 (0x00007fe11ac41000)
	libxcb-shm.so.0 => /lib64/libxcb-shm.so.0 (0x00007fe11ac3c000)
	libxcb.so.1 => /lib64/libxcb.so.1 (0x00007fe11ac0e000)
	libxcb-render.so.0 => /lib64/libxcb-render.so.0 (0x00007fe11abfe000)
	libXrender.so.1 => /lib64/libXrender.so.1 (0x00007fe11abf1000)
	libX11.so.6 => /lib64/libX11.so.6 (0x00007fe11aaaa000)
	libXext.so.6 => /lib64/libXext.so.6 (0x00007fe11aa95000)
	librt.so.1 => /lib64/librt.so.1 (0x00007fe11aa8a000)
	libgraphite2.so.3 => /lib64/libgraphite2.so.3 (0x00007fe11aa64000)
	libfribidi.so.0 => /lib64/libfribidi.so.0 (0x00007fe11aa45000)
	libthai.so.0 => /lib64/libthai.so.0 (0x00007fe11aa39000)
	libXft.so.2 => /lib64/libXft.so.2 (0x00007fe11aa1f000)
	libXinerama.so.1 => /lib64/libXinerama.so.1 (0x00007fe11aa1a000)
	libXi.so.6 => /lib64/libXi.so.6 (0x00007fe11aa06000)
	libXrandr.so.2 => /lib64/libXrandr.so.2 (0x00007fe11a9f9000)
	libXcursor.so.1 => /lib64/libXcursor.so.1 (0x00007fe11a9ec000)
	libXcomposite.so.1 => /lib64/libXcomposite.so.1 (0x00007fe11a9e7000)
	libXdamage.so.1 => /lib64/libXdamage.so.1 (0x00007fe11a9e2000)
	libXfixes.so.3 => /lib64/libXfixes.so.3 (0x00007fe11a9d9000)
	/lib64/ld-linux-x86-64.so.2 (0x00007fe11beb9000)
	libblkid.so.1 => /lib64/libblkid.so.1 (0x00007fe11a984000)
	libpcre2-8.so.0 => /lib64/libpcre2-8.so.0 (0x00007fe11a8eb000)
	libexpat.so.1 => /lib64/libexpat.so.1 (0x00007fe11a8bc000)
	libbz2.so.1 => /lib64/libbz2.so.1 (0x00007fe11a8a9000)
	libXau.so.6 => /lib64/libXau.so.6 (0x00007fe11a8a3000)
	libdatrie.so.1 => /lib64/libdatrie.so.1 (0x00007fe11a897000)
$ ldd 2048-Gtk2 | wc -l
	55
```

### 2048-Gtk1

```
$ ldd 2048-Gtk1
	linux-vdso.so.1 (0x00007fff8f140000)
	libgtk-1.2.so.0 => /lib64/libgtk-1.2.so.0 (0x00007f25fc464000)
	libgdk-1.2.so.0 => /lib64/libgdk-1.2.so.0 (0x00007f25fc41e000)
	libXi.so.6 => /lib64/libXi.so.6 (0x00007f25fc40c000)
	libXext.so.6 => /lib64/libXext.so.6 (0x00007f25fc3f7000)
	libX11.so.6 => /lib64/libX11.so.6 (0x00007f25fc2b0000)
	libm.so.6 => /lib64/libm.so.6 (0x00007f25fc16a000)
	libglib-1.2.so.0 => /lib64/libglib-1.2.so.0 (0x00007f25fc136000)
	libc.so.6 => /lib64/libc.so.6 (0x00007f25fbf6c000)
	libgmodule-1.2.so.0 => /lib64/libgmodule-1.2.so.0 (0x00007f25fbf66000)
	libxcb.so.1 => /lib64/libxcb.so.1 (0x00007f25fbf3a000)
	libdl.so.2 => /lib64/libdl.so.2 (0x00007f25fbf33000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f25fc619000)
	libXau.so.6 => /lib64/libXau.so.6 (0x00007f25fbf2b000)
$ ldd 2048-Gtk1 | wc -l
	14
```
