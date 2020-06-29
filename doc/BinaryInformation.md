Binary Information
==================

Dependencies were obtained:

1. By using `ldd` command on Fedora 32.
2. By `arm-linux-gnueabi-objdump` for MotoMAGX platform.

### Sizes

```sh
ls -lh 2048-*
-rwxrwxr-x. 1 exl exl 15K Jun 29 02:11 2048-Gtk1
-rwxrwxr-x. 1 exl exl 15K Jun 29 02:20 2048-Gtk2
-rwxrwxr-x. 1 exl exl 15K Jun 29 02:30 2048-Gtk3
-rwxrwxr-x. 1 exl exl 15K Jun 29 02:41 2048-Motif
-rwxrwxr-x. 1 exl exl 40K Jun 29 02:56 2048-MotoMAGX_E8
-rwxrwxr-x. 1 exl exl 40K Jun 29 02:56 2048-MotoMAGX_EM30
-rwxrwxr-x. 1 exl exl 40K Jun 29 02:58 2048-MotoMAGX_EM35
-rwxrwxr-x. 1 exl exl 40K Jun 29 02:57 2048-MotoMAGX_U9
-rwxrwxr-x. 1 exl exl 40K Jun 29 02:57 2048-MotoMAGX_V8
-rwxrwxr-x. 1 exl exl 40K Jun 29 02:57 2048-MotoMAGX_VE66
-rwxrwxr-x. 1 exl exl 40K Jun 29 02:57 2048-MotoMAGX_Z6
-rwxrwxr-x. 1 exl exl 40K Jun 29 02:57 2048-MotoMAGX_Z6W
-rwxrwxr-x. 1 exl exl 40K Jun 29 02:57 2048-MotoMAGX_ZN5
-rwxrwxr-x. 1 exl exl 23K Jun 29 03:12 2048-Qt1
-rwxrwxr-x. 1 exl exl 32K Jun 29 03:27 2048-Qt2
-rwxrwxr-x. 1 exl exl 32K Jun 29 03:37 2048-Qt3
-rwxrwxr-x. 1 exl exl 23K Jun 29 03:56 2048-Qt4
-rwxrwxr-x. 1 exl exl 23K Jun 29 04:41 2048-Qt5
-rwxrwxr-x. 1 exl exl 15K Jun 29 04:56 2048-Xaw
-rwxrwxr-x. 1 exl exl 15K Jun 29 05:32 2048-Xcb
-rwxrwxr-x. 1 exl exl 15K Jun 29 05:14 2048-Xlib
```

### File Types

```sh
file 2048-*
2048-Gtk1:          ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 2.6.32, BuildID[sha1]=1e4b438308e0e20df58f3ebe9a03c31a462ab52f, stripped
2048-Gtk2:          ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 2.6.32, BuildID[sha1]=cefc0e830081019ceb4fcc105ddf8917eb0cb5d5, stripped
2048-Gtk3:          ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 2.6.32, BuildID[sha1]=a45a0c539c402532f76a8a0eef273a78c19323af, stripped
2048-Motif:         ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 2.6.32, BuildID[sha1]=b498d93eb27163a26b76f26e8bd6f8b8d3400d22, stripped
2048-MotoMAGX_E8:   ELF 32-bit LSB executable, ARM, EABI4 version 1 (SYSV), dynamically linked, interpreter /lib/ld-linux.so.3, for GNU/Linux 2.4.17, stripped
2048-MotoMAGX_EM30: ELF 32-bit LSB executable, ARM, EABI4 version 1 (SYSV), dynamically linked, interpreter /lib/ld-linux.so.3, for GNU/Linux 2.4.17, stripped
2048-MotoMAGX_EM35: ELF 32-bit LSB executable, ARM, EABI4 version 1 (SYSV), dynamically linked, interpreter /lib/ld-linux.so.3, for GNU/Linux 2.4.17, stripped
2048-MotoMAGX_U9:   ELF 32-bit LSB executable, ARM, EABI4 version 1 (SYSV), dynamically linked, interpreter /lib/ld-linux.so.3, for GNU/Linux 2.4.17, stripped
2048-MotoMAGX_V8:   ELF 32-bit LSB executable, ARM, EABI4 version 1 (SYSV), dynamically linked, interpreter /lib/ld-linux.so.3, for GNU/Linux 2.4.17, stripped
2048-MotoMAGX_VE66: ELF 32-bit LSB executable, ARM, EABI4 version 1 (SYSV), dynamically linked, interpreter /lib/ld-linux.so.3, for GNU/Linux 2.4.17, stripped
2048-MotoMAGX_Z6:   ELF 32-bit LSB executable, ARM, EABI4 version 1 (SYSV), dynamically linked, interpreter /lib/ld-linux.so.3, for GNU/Linux 2.4.17, stripped
2048-MotoMAGX_Z6W:  ELF 32-bit LSB executable, ARM, EABI4 version 1 (SYSV), dynamically linked, interpreter /lib/ld-linux.so.3, for GNU/Linux 2.4.17, stripped
2048-MotoMAGX_ZN5:  ELF 32-bit LSB executable, ARM, EABI4 version 1 (SYSV), dynamically linked, interpreter /lib/ld-linux.so.3, for GNU/Linux 2.4.17, stripped
2048-Qt1:           ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 2.6.32, BuildID[sha1]=95e71f013f8ccbb9de61e726b1fe8e97b095b448, stripped
2048-Qt2:           ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 2.6.32, BuildID[sha1]=d92b94df02f72018055423fcca93154059ab233b, stripped
2048-Qt3:           ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 2.6.32, BuildID[sha1]=edd129ee866c83866462f000a2a5306a3bbe0589, stripped
2048-Qt4:           ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 2.6.32, BuildID[sha1]=d324b2fe03d109808de3ff90f47553475975d95a, stripped
2048-Qt5:           ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 2.6.32, BuildID[sha1]=7da9d6ccf943837f4959848ec48627af8ca48057, stripped
2048-Xaw:           ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 2.6.32, BuildID[sha1]=ba5a835587570124bd83fa6817037a7a41cc08ca, stripped
2048-Xcb:           ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 2.6.32, BuildID[sha1]=61678390a147614615efb014f2a77a244005c859, stripped
2048-Xlib:          ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 2.6.32, BuildID[sha1]=5f2e9cd754c409602721b83f018139c9545348b1, stripped
```

### 2048-Qt5

```sh
ldd 2048-Qt5
	linux-vdso.so.1 (0x00007fffa35de000)
	libQt5Widgets.so.5 => /lib64/libQt5Widgets.so.5 (0x00007f3010048000)
	libQt5Gui.so.5 => /lib64/libQt5Gui.so.5 (0x00007f300fadf000)
	libQt5Core.so.5 => /lib64/libQt5Core.so.5 (0x00007f300f5c4000)
	libstdc++.so.6 => /lib64/libstdc++.so.6 (0x00007f300f3d4000)
	libm.so.6 => /lib64/libm.so.6 (0x00007f300f28e000)
	libgcc_s.so.1 => /lib64/libgcc_s.so.1 (0x00007f300f273000)
	libc.so.6 => /lib64/libc.so.6 (0x00007f300f0a7000)
	libpthread.so.0 => /lib64/libpthread.so.0 (0x00007f300f085000)
	libGL.so.1 => /lib64/libGL.so.1 (0x00007f300effd000)
	libpng16.so.16 => /lib64/libpng16.so.16 (0x00007f300efc6000)
	libz.so.1 => /lib64/libz.so.1 (0x00007f300efac000)
	libharfbuzz.so.0 => /lib64/libharfbuzz.so.0 (0x00007f300eeca000)
	libsystemd.so.0 => /lib64/libsystemd.so.0 (0x00007f300ee11000)
	libicui18n.so.65 => /lib64/libicui18n.so.65 (0x00007f300eb0a000)
	libicuuc.so.65 => /lib64/libicuuc.so.65 (0x00007f300e922000)
	libdl.so.2 => /lib64/libdl.so.2 (0x00007f300e91b000)
	libpcre2-16.so.0 => /lib64/libpcre2-16.so.0 (0x00007f300e890000)
	libglib-2.0.so.0 => /lib64/libglib-2.0.so.0 (0x00007f300e765000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f3010716000)
	libGLX.so.0 => /lib64/libGLX.so.0 (0x00007f300e72f000)
	libX11.so.6 => /lib64/libX11.so.6 (0x00007f300e5e8000)
	libXext.so.6 => /lib64/libXext.so.6 (0x00007f300e5d3000)
	libGLdispatch.so.0 => /lib64/libGLdispatch.so.0 (0x00007f300e51a000)
	libfreetype.so.6 => /lib64/libfreetype.so.6 (0x00007f300e458000)
	libgraphite2.so.3 => /lib64/libgraphite2.so.3 (0x00007f300e434000)
	librt.so.1 => /lib64/librt.so.1 (0x00007f300e427000)
	liblzma.so.5 => /lib64/liblzma.so.5 (0x00007f300e3fd000)
	liblz4.so.1 => /lib64/liblz4.so.1 (0x00007f300e3dc000)
	libgcrypt.so.20 => /lib64/libgcrypt.so.20 (0x00007f300e2bb000)
	libicudata.so.65 => /lib64/libicudata.so.65 (0x00007f300c808000)
	libpcre.so.1 => /lib64/libpcre.so.1 (0x00007f300c78f000)
	libxcb.so.1 => /lib64/libxcb.so.1 (0x00007f300c761000)
	libbz2.so.1 => /lib64/libbz2.so.1 (0x00007f300c74e000)
	libgpg-error.so.0 => /lib64/libgpg-error.so.0 (0x00007f300c72a000)
	libXau.so.6 => /lib64/libXau.so.6 (0x00007f300c724000)
ldd 2048-Qt5 | wc -l
	36
```

### 2048-Qt4

```sh
ldd 2048-Qt4
	linux-vdso.so.1 (0x00007ffc9478e000)
	libQtGui.so.4 => /lib64/libQtGui.so.4 (0x00007f9d5cf92000)
	libQtCore.so.4 => /lib64/libQtCore.so.4 (0x00007f9d5cc7a000)
	libstdc++.so.6 => /lib64/libstdc++.so.6 (0x00007f9d5ca8a000)
	libm.so.6 => /lib64/libm.so.6 (0x00007f9d5c944000)
	libgcc_s.so.1 => /lib64/libgcc_s.so.1 (0x00007f9d5c929000)
	libc.so.6 => /lib64/libc.so.6 (0x00007f9d5c75f000)
	libpthread.so.0 => /lib64/libpthread.so.0 (0x00007f9d5c73b000)
	libglib-2.0.so.0 => /lib64/libglib-2.0.so.0 (0x00007f9d5c610000)
	libpng16.so.16 => /lib64/libpng16.so.16 (0x00007f9d5c5d9000)
	libz.so.1 => /lib64/libz.so.1 (0x00007f9d5c5bf000)
	libfreetype.so.6 => /lib64/libfreetype.so.6 (0x00007f9d5c4fd000)
	libgobject-2.0.so.0 => /lib64/libgobject-2.0.so.0 (0x00007f9d5c4a4000)
	libSM.so.6 => /lib64/libSM.so.6 (0x00007f9d5c497000)
	libICE.so.6 => /lib64/libICE.so.6 (0x00007f9d5c479000)
	libXi.so.6 => /lib64/libXi.so.6 (0x00007f9d5c467000)
	libXrender.so.1 => /lib64/libXrender.so.1 (0x00007f9d5c45a000)
	libXrandr.so.2 => /lib64/libXrandr.so.2 (0x00007f9d5c44d000)
	libXfixes.so.3 => /lib64/libXfixes.so.3 (0x00007f9d5c444000)
	libXcursor.so.1 => /lib64/libXcursor.so.1 (0x00007f9d5c435000)
	libXinerama.so.1 => /lib64/libXinerama.so.1 (0x00007f9d5c430000)
	libfontconfig.so.1 => /lib64/libfontconfig.so.1 (0x00007f9d5c3e5000)
	libXext.so.6 => /lib64/libXext.so.6 (0x00007f9d5c3d0000)
	libX11.so.6 => /lib64/libX11.so.6 (0x00007f9d5c289000)
	libdl.so.2 => /lib64/libdl.so.2 (0x00007f9d5c282000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f9d5db88000)
	libpcre.so.1 => /lib64/libpcre.so.1 (0x00007f9d5c207000)
	libbz2.so.1 => /lib64/libbz2.so.1 (0x00007f9d5c1f4000)
	libffi.so.6 => /lib64/libffi.so.6 (0x00007f9d5c1e9000)
	libuuid.so.1 => /lib64/libuuid.so.1 (0x00007f9d5c1e0000)
	libexpat.so.1 => /lib64/libexpat.so.1 (0x00007f9d5c1b1000)
	libxcb.so.1 => /lib64/libxcb.so.1 (0x00007f9d5c183000)
	libXau.so.6 => /lib64/libXau.so.6 (0x00007f9d5c17d000)
ldd 2048-Qt4 | wc -l
	33
```

### 2048-Qt3

```sh
ldd 2048-Qt3
	linux-vdso.so.1 (0x00007ffe536aa000)
	libqt-mt.so.3 => /usr/lib64/qt-3.3/lib/libqt-mt.so.3 (0x00007fe34db19000)
	libstdc++.so.6 => /lib64/libstdc++.so.6 (0x00007fe34d903000)
	libm.so.6 => /lib64/libm.so.6 (0x00007fe34d7bd000)
	libgcc_s.so.1 => /lib64/libgcc_s.so.1 (0x00007fe34d7a2000)
	libc.so.6 => /lib64/libc.so.6 (0x00007fe34d5d8000)
	libmng.so.2 => /lib64/libmng.so.2 (0x00007fe34d563000)
	libjpeg.so.62 => /lib64/libjpeg.so.62 (0x00007fe34d4dc000)
	libpng16.so.16 => /lib64/libpng16.so.16 (0x00007fe34d4a5000)
	libz.so.1 => /lib64/libz.so.1 (0x00007fe34d48b000)
	libXi.so.6 => /lib64/libXi.so.6 (0x00007fe34d479000)
	libXrender.so.1 => /lib64/libXrender.so.1 (0x00007fe34d46c000)
	libXrandr.so.2 => /lib64/libXrandr.so.2 (0x00007fe34d45f000)
	libXcursor.so.1 => /lib64/libXcursor.so.1 (0x00007fe34d450000)
	libXinerama.so.1 => /lib64/libXinerama.so.1 (0x00007fe34d44b000)
	libXft.so.2 => /lib64/libXft.so.2 (0x00007fe34d431000)
	libfreetype.so.6 => /lib64/libfreetype.so.6 (0x00007fe34d36f000)
	libfontconfig.so.1 => /lib64/libfontconfig.so.1 (0x00007fe34d324000)
	libXext.so.6 => /lib64/libXext.so.6 (0x00007fe34d30f000)
	libX11.so.6 => /lib64/libX11.so.6 (0x00007fe34d1c6000)
	libSM.so.6 => /lib64/libSM.so.6 (0x00007fe34d1bb000)
	libICE.so.6 => /lib64/libICE.so.6 (0x00007fe34d19d000)
	libdl.so.2 => /lib64/libdl.so.2 (0x00007fe34d196000)
	libpthread.so.0 => /lib64/libpthread.so.0 (0x00007fe34d174000)
	/lib64/ld-linux-x86-64.so.2 (0x00007fe34e415000)
	liblcms2.so.2 => /lib64/liblcms2.so.2 (0x00007fe34d114000)
	libXfixes.so.3 => /lib64/libXfixes.so.3 (0x00007fe34d109000)
	libbz2.so.1 => /lib64/libbz2.so.1 (0x00007fe34d0f6000)
	libexpat.so.1 => /lib64/libexpat.so.1 (0x00007fe34d0c7000)
	libxcb.so.1 => /lib64/libxcb.so.1 (0x00007fe34d09b000)
	libuuid.so.1 => /lib64/libuuid.so.1 (0x00007fe34d092000)
	libXau.so.6 => /lib64/libXau.so.6 (0x00007fe34d08a000)
ldd 2048-Qt3 | wc -l
	32
```

### 2048-Qt2

```sh
ldd 2048-Qt2
	linux-vdso.so.1 (0x00007ffc65b59000)
	libqt2.so.2 => /home/exl/Projects/qt2/src/libqt2.so.2 (0x00007faab64a8000)
	libstdc++.so.6 => /lib64/libstdc++.so.6 (0x00007faab6292000)
	libm.so.6 => /lib64/libm.so.6 (0x00007faab614c000)
	libgcc_s.so.1 => /lib64/libgcc_s.so.1 (0x00007faab6131000)
	libc.so.6 => /lib64/libc.so.6 (0x00007faab5f67000)
	libfontconfig.so.1 => /lib64/libfontconfig.so.1 (0x00007faab5f1c000)
	libSM.so.6 => /lib64/libSM.so.6 (0x00007faab5f0f000)
	libICE.so.6 => /lib64/libICE.so.6 (0x00007faab5ef1000)
	libX11.so.6 => /lib64/libX11.so.6 (0x00007faab5daa000)
	libXext.so.6 => /lib64/libXext.so.6 (0x00007faab5d95000)
	libjpeg.so.62 => /lib64/libjpeg.so.62 (0x00007faab5d10000)
	libXft.so.2 => /lib64/libXft.so.2 (0x00007faab5cf6000)
	libmng.so.2 => /lib64/libmng.so.2 (0x00007faab5c7f000)
	libGL.so.1 => /lib64/libGL.so.1 (0x00007faab5bf7000)
	libpng16.so.16 => /lib64/libpng16.so.16 (0x00007faab5bc0000)
	libz.so.1 => /lib64/libz.so.1 (0x00007faab5ba6000)
	libXmu.so.6 => /lib64/libXmu.so.6 (0x00007faab5b89000)
	libpthread.so.0 => /lib64/libpthread.so.0 (0x00007faab5b67000)
	/lib64/ld-linux-x86-64.so.2 (0x00007faab6abc000)
	libfreetype.so.6 => /lib64/libfreetype.so.6 (0x00007faab5aa3000)
	libexpat.so.1 => /lib64/libexpat.so.1 (0x00007faab5a74000)
	libuuid.so.1 => /lib64/libuuid.so.1 (0x00007faab5a6b000)
	libxcb.so.1 => /lib64/libxcb.so.1 (0x00007faab5a3f000)
	libdl.so.2 => /lib64/libdl.so.2 (0x00007faab5a38000)
	libXrender.so.1 => /lib64/libXrender.so.1 (0x00007faab5a2b000)
	liblcms2.so.2 => /lib64/liblcms2.so.2 (0x00007faab59c9000)
	libGLX.so.0 => /lib64/libGLX.so.0 (0x00007faab5995000)
	libGLdispatch.so.0 => /lib64/libGLdispatch.so.0 (0x00007faab58dc000)
	libXt.so.6 => /lib64/libXt.so.6 (0x00007faab586f000)
	libbz2.so.1 => /lib64/libbz2.so.1 (0x00007faab585c000)
	libXau.so.6 => /lib64/libXau.so.6 (0x00007faab5854000)
ldd 2048-Qt2 | wc -l
	32
```

### 2048-Qt1

```sh
ldd 2048-Qt1
	linux-vdso.so.1 (0x00007ffea5df5000)
	libqt1.so.1 => /home/exl/Projects/qt1/src/libqt1.so.1 (0x00007fdaa7454000)
	libstdc++.so.6 => /lib64/libstdc++.so.6 (0x00007fdaa723e000)
	libm.so.6 => /lib64/libm.so.6 (0x00007fdaa70f8000)
	libgcc_s.so.1 => /lib64/libgcc_s.so.1 (0x00007fdaa70dd000)
	libc.so.6 => /lib64/libc.so.6 (0x00007fdaa6f13000)
	libX11.so.6 => /lib64/libX11.so.6 (0x00007fdaa6dcc000)
	libXext.so.6 => /lib64/libXext.so.6 (0x00007fdaa6db5000)
	/lib64/ld-linux-x86-64.so.2 (0x00007fdaa7634000)
	libxcb.so.1 => /lib64/libxcb.so.1 (0x00007fdaa6d89000)
	libdl.so.2 => /lib64/libdl.so.2 (0x00007fdaa6d82000)
	libXau.so.6 => /lib64/libXau.so.6 (0x00007fdaa6d7c000)
ldd 2048-Qt1 | wc -l
	12
```

### 2048-Gtk3

```sh
ldd 2048-Gtk3
	linux-vdso.so.1 (0x00007fff8bfd4000)
	libgtk-3.so.0 => /lib64/libgtk-3.so.0 (0x00007f0cddd98000)
	libgdk-3.so.0 => /lib64/libgdk-3.so.0 (0x00007f0cddc90000)
	libatk-1.0.so.0 => /lib64/libatk-1.0.so.0 (0x00007f0cddc66000)
	libgio-2.0.so.0 => /lib64/libgio-2.0.so.0 (0x00007f0cdda82000)
	libpangocairo-1.0.so.0 => /lib64/libpangocairo-1.0.so.0 (0x00007f0cdda70000)
	libgdk_pixbuf-2.0.so.0 => /lib64/libgdk_pixbuf-2.0.so.0 (0x00007f0cdda45000)
	libcairo-gobject.so.2 => /lib64/libcairo-gobject.so.2 (0x00007f0cdda37000)
	libpango-1.0.so.0 => /lib64/libpango-1.0.so.0 (0x00007f0cdd9e8000)
	libcairo.so.2 => /lib64/libcairo.so.2 (0x00007f0cdd8c0000)
	libgobject-2.0.so.0 => /lib64/libgobject-2.0.so.0 (0x00007f0cdd867000)
	libglib-2.0.so.0 => /lib64/libglib-2.0.so.0 (0x00007f0cdd73c000)
	libc.so.6 => /lib64/libc.so.6 (0x00007f0cdd572000)
	libgmodule-2.0.so.0 => /lib64/libgmodule-2.0.so.0 (0x00007f0cdd56a000)
	libX11.so.6 => /lib64/libX11.so.6 (0x00007f0cdd423000)
	libXi.so.6 => /lib64/libXi.so.6 (0x00007f0cdd411000)
	libXfixes.so.3 => /lib64/libXfixes.so.3 (0x00007f0cdd408000)
	libatk-bridge-2.0.so.0 => /lib64/libatk-bridge-2.0.so.0 (0x00007f0cdd3cf000)
	libwayland-client.so.0 => /lib64/libwayland-client.so.0 (0x00007f0cdd3be000)
	libepoxy.so.0 => /lib64/libepoxy.so.0 (0x00007f0cdd289000)
	libfribidi.so.0 => /lib64/libfribidi.so.0 (0x00007f0cdd26a000)
	libm.so.6 => /lib64/libm.so.6 (0x00007f0cdd124000)
	libpangoft2-1.0.so.0 => /lib64/libpangoft2-1.0.so.0 (0x00007f0cdd10b000)
	libharfbuzz.so.0 => /lib64/libharfbuzz.so.0 (0x00007f0cdd029000)
	libfontconfig.so.1 => /lib64/libfontconfig.so.1 (0x00007f0cdcfde000)
	libfreetype.so.6 => /lib64/libfreetype.so.6 (0x00007f0cdcf1a000)
	libpthread.so.0 => /lib64/libpthread.so.0 (0x00007f0cdcef8000)
	libXinerama.so.1 => /lib64/libXinerama.so.1 (0x00007f0cdcef3000)
	libXrandr.so.2 => /lib64/libXrandr.so.2 (0x00007f0cdcee6000)
	libXcursor.so.1 => /lib64/libXcursor.so.1 (0x00007f0cdced9000)
	libXcomposite.so.1 => /lib64/libXcomposite.so.1 (0x00007f0cdced4000)
	libXdamage.so.1 => /lib64/libXdamage.so.1 (0x00007f0cdcecd000)
	libxkbcommon.so.0 => /lib64/libxkbcommon.so.0 (0x00007f0cdce8a000)
	libwayland-cursor.so.0 => /lib64/libwayland-cursor.so.0 (0x00007f0cdce7f000)
	libwayland-egl.so.1 => /lib64/libwayland-egl.so.1 (0x00007f0cdce7a000)
	libXext.so.6 => /lib64/libXext.so.6 (0x00007f0cdce65000)
	librt.so.1 => /lib64/librt.so.1 (0x00007f0cdce5a000)
	libz.so.1 => /lib64/libz.so.1 (0x00007f0cdce3e000)
	libmount.so.1 => /lib64/libmount.so.1 (0x00007f0cdcdde000)
	libselinux.so.1 => /lib64/libselinux.so.1 (0x00007f0cdcdb1000)
	libresolv.so.2 => /lib64/libresolv.so.2 (0x00007f0cdcd97000)
	libpng16.so.16 => /lib64/libpng16.so.16 (0x00007f0cdcd60000)
	libpixman-1.so.0 => /lib64/libpixman-1.so.0 (0x00007f0cdccb4000)
	libxcb-shm.so.0 => /lib64/libxcb-shm.so.0 (0x00007f0cdccad000)
	libxcb.so.1 => /lib64/libxcb.so.1 (0x00007f0cdcc81000)
	libxcb-render.so.0 => /lib64/libxcb-render.so.0 (0x00007f0cdcc71000)
	libXrender.so.1 => /lib64/libXrender.so.1 (0x00007f0cdcc64000)
	libthai.so.0 => /lib64/libthai.so.0 (0x00007f0cdcc58000)
	libffi.so.6 => /lib64/libffi.so.6 (0x00007f0cdcc4b000)
	libpcre.so.1 => /lib64/libpcre.so.1 (0x00007f0cdcbd2000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f0cde58d000)
	libdl.so.2 => /lib64/libdl.so.2 (0x00007f0cdcbcb000)
	libdbus-1.so.3 => /lib64/libdbus-1.so.3 (0x00007f0cdcb74000)
	libatspi.so.0 => /lib64/libatspi.so.0 (0x00007f0cdcb3b000)
	libgraphite2.so.3 => /lib64/libgraphite2.so.3 (0x00007f0cdcb15000)
	libexpat.so.1 => /lib64/libexpat.so.1 (0x00007f0cdcae6000)
	libbz2.so.1 => /lib64/libbz2.so.1 (0x00007f0cdcad3000)
	libblkid.so.1 => /lib64/libblkid.so.1 (0x00007f0cdca80000)
	libpcre2-8.so.0 => /lib64/libpcre2-8.so.0 (0x00007f0cdc9e7000)
	libXau.so.6 => /lib64/libXau.so.6 (0x00007f0cdc9df000)
	libdatrie.so.1 => /lib64/libdatrie.so.1 (0x00007f0cdc9d5000)
	libsystemd.so.0 => /lib64/libsystemd.so.0 (0x00007f0cdc91e000)
	liblzma.so.5 => /lib64/liblzma.so.5 (0x00007f0cdc8f4000)
	liblz4.so.1 => /lib64/liblz4.so.1 (0x00007f0cdc8d3000)
	libgcrypt.so.20 => /lib64/libgcrypt.so.20 (0x00007f0cdc7b0000)
	libgcc_s.so.1 => /lib64/libgcc_s.so.1 (0x00007f0cdc795000)
	libgpg-error.so.0 => /lib64/libgpg-error.so.0 (0x00007f0cdc771000)
ldd 2048-Gtk3 | wc -l
	67
```

### 2048-Gtk2

```sh
ldd 2048-Gtk2
	linux-vdso.so.1 (0x00007fff85fed000)
	libglib-2.0.so.0 => /lib64/libglib-2.0.so.0 (0x00007f49eadb4000)
	libgobject-2.0.so.0 => /lib64/libgobject-2.0.so.0 (0x00007f49ead5b000)
	libatk-1.0.so.0 => /lib64/libatk-1.0.so.0 (0x00007f49ead31000)
	libgio-2.0.so.0 => /lib64/libgio-2.0.so.0 (0x00007f49eab4d000)
	libgthread-2.0.so.0 => /lib64/libgthread-2.0.so.0 (0x00007f49eab48000)
	libgmodule-2.0.so.0 => /lib64/libgmodule-2.0.so.0 (0x00007f49eab42000)
	libgdk_pixbuf-2.0.so.0 => /lib64/libgdk_pixbuf-2.0.so.0 (0x00007f49eab15000)
	libcairo.so.2 => /lib64/libcairo.so.2 (0x00007f49ea9ed000)
	libpango-1.0.so.0 => /lib64/libpango-1.0.so.0 (0x00007f49ea99e000)
	libpangocairo-1.0.so.0 => /lib64/libpangocairo-1.0.so.0 (0x00007f49ea98c000)
	libpangoft2-1.0.so.0 => /lib64/libpangoft2-1.0.so.0 (0x00007f49ea973000)
	libpangoxft-1.0.so.0 => /lib64/libpangoxft-1.0.so.0 (0x00007f49ea967000)
	libgdk-x11-2.0.so.0 => /lib64/libgdk-x11-2.0.so.0 (0x00007f49ea895000)
	libgtk-x11-2.0.so.0 => /lib64/libgtk-x11-2.0.so.0 (0x00007f49ea3e2000)
	libc.so.6 => /lib64/libc.so.6 (0x00007f49ea218000)
	libpcre.so.1 => /lib64/libpcre.so.1 (0x00007f49ea19f000)
	libpthread.so.0 => /lib64/libpthread.so.0 (0x00007f49ea17d000)
	libffi.so.6 => /lib64/libffi.so.6 (0x00007f49ea172000)
	libz.so.1 => /lib64/libz.so.1 (0x00007f49ea156000)
	libmount.so.1 => /lib64/libmount.so.1 (0x00007f49ea0f6000)
	libselinux.so.1 => /lib64/libselinux.so.1 (0x00007f49ea0c9000)
	libresolv.so.2 => /lib64/libresolv.so.2 (0x00007f49ea0af000)
	libdl.so.2 => /lib64/libdl.so.2 (0x00007f49ea0a8000)
	libm.so.6 => /lib64/libm.so.6 (0x00007f49e9f62000)
	libpng16.so.16 => /lib64/libpng16.so.16 (0x00007f49e9f29000)
	libpixman-1.so.0 => /lib64/libpixman-1.so.0 (0x00007f49e9e7d000)
	libfontconfig.so.1 => /lib64/libfontconfig.so.1 (0x00007f49e9e32000)
	libfreetype.so.6 => /lib64/libfreetype.so.6 (0x00007f49e9d70000)
	libxcb-shm.so.0 => /lib64/libxcb-shm.so.0 (0x00007f49e9d6b000)
	libxcb.so.1 => /lib64/libxcb.so.1 (0x00007f49e9d3f000)
	libxcb-render.so.0 => /lib64/libxcb-render.so.0 (0x00007f49e9d2d000)
	libXrender.so.1 => /lib64/libXrender.so.1 (0x00007f49e9d20000)
	libX11.so.6 => /lib64/libX11.so.6 (0x00007f49e9bd9000)
	libXext.so.6 => /lib64/libXext.so.6 (0x00007f49e9bc4000)
	librt.so.1 => /lib64/librt.so.1 (0x00007f49e9bb9000)
	libfribidi.so.0 => /lib64/libfribidi.so.0 (0x00007f49e9b9a000)
	libthai.so.0 => /lib64/libthai.so.0 (0x00007f49e9b8c000)
	libharfbuzz.so.0 => /lib64/libharfbuzz.so.0 (0x00007f49e9aaa000)
	libXft.so.2 => /lib64/libXft.so.2 (0x00007f49e9a90000)
	libXinerama.so.1 => /lib64/libXinerama.so.1 (0x00007f49e9a8b000)
	libXi.so.6 => /lib64/libXi.so.6 (0x00007f49e9a79000)
	libXrandr.so.2 => /lib64/libXrandr.so.2 (0x00007f49e9a6a000)
	libXcursor.so.1 => /lib64/libXcursor.so.1 (0x00007f49e9a5d000)
	libXcomposite.so.1 => /lib64/libXcomposite.so.1 (0x00007f49e9a58000)
	libXdamage.so.1 => /lib64/libXdamage.so.1 (0x00007f49e9a53000)
	libXfixes.so.3 => /lib64/libXfixes.so.3 (0x00007f49e9a4a000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f49eaf07000)
	libblkid.so.1 => /lib64/libblkid.so.1 (0x00007f49e99f7000)
	libpcre2-8.so.0 => /lib64/libpcre2-8.so.0 (0x00007f49e995c000)
	libexpat.so.1 => /lib64/libexpat.so.1 (0x00007f49e992d000)
	libbz2.so.1 => /lib64/libbz2.so.1 (0x00007f49e991a000)
	libXau.so.6 => /lib64/libXau.so.6 (0x00007f49e9914000)
	libdatrie.so.1 => /lib64/libdatrie.so.1 (0x00007f49e990a000)
	libgraphite2.so.3 => /lib64/libgraphite2.so.3 (0x00007f49e98e4000)
ldd 2048-Gtk2 | wc -l
	55
```

### 2048-Gtk1

```sh
ldd 2048-Gtk1
	linux-vdso.so.1 (0x00007ffd303d9000)
	libgtk-1.2.so.0 => /lib64/libgtk-1.2.so.0 (0x00007f06a3742000)
	libgdk-1.2.so.0 => /lib64/libgdk-1.2.so.0 (0x00007f06a36fc000)
	libXi.so.6 => /lib64/libXi.so.6 (0x00007f06a36ea000)
	libXext.so.6 => /lib64/libXext.so.6 (0x00007f06a36d5000)
	libX11.so.6 => /lib64/libX11.so.6 (0x00007f06a358e000)
	libm.so.6 => /lib64/libm.so.6 (0x00007f06a3448000)
	libglib-1.2.so.0 => /lib64/libglib-1.2.so.0 (0x00007f06a3414000)
	libc.so.6 => /lib64/libc.so.6 (0x00007f06a324a000)
	libgmodule-1.2.so.0 => /lib64/libgmodule-1.2.so.0 (0x00007f06a3244000)
	libxcb.so.1 => /lib64/libxcb.so.1 (0x00007f06a3218000)
	libdl.so.2 => /lib64/libdl.so.2 (0x00007f06a3211000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f06a38f8000)
	libXau.so.6 => /lib64/libXau.so.6 (0x00007f06a3209000)
ldd 2048-Gtk1 | wc -l
	14
```

### 2048-Motif

```sh
ldd 2048-Motif
	linux-vdso.so.1 (0x00007ffc7ef79000)
	libXm.so.4 => /lib64/libXm.so.4 (0x00007f0afe733000)
	libXt.so.6 => /lib64/libXt.so.6 (0x00007f0afe6c6000)
	libX11.so.6 => /lib64/libX11.so.6 (0x00007f0afe57f000)
	libc.so.6 => /lib64/libc.so.6 (0x00007f0afe3b5000)
	libXmu.so.6 => /lib64/libXmu.so.6 (0x00007f0afe398000)
	libXext.so.6 => /lib64/libXext.so.6 (0x00007f0afe383000)
	libXp.so.6 => /lib64/libXp.so.6 (0x00007f0afe375000)
	libXft.so.2 => /lib64/libXft.so.2 (0x00007f0afe35b000)
	libjpeg.so.62 => /lib64/libjpeg.so.62 (0x00007f0afe2d6000)
	libpng16.so.16 => /lib64/libpng16.so.16 (0x00007f0afe29f000)
	libSM.so.6 => /lib64/libSM.so.6 (0x00007f0afe294000)
	libICE.so.6 => /lib64/libICE.so.6 (0x00007f0afe276000)
	libxcb.so.1 => /lib64/libxcb.so.1 (0x00007f0afe248000)
	libdl.so.2 => /lib64/libdl.so.2 (0x00007f0afe241000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f0afea44000)
	libXau.so.6 => /lib64/libXau.so.6 (0x00007f0afe23b000)
	libfontconfig.so.1 => /lib64/libfontconfig.so.1 (0x00007f0afe1f0000)
	libfreetype.so.6 => /lib64/libfreetype.so.6 (0x00007f0afe12e000)
	libXrender.so.1 => /lib64/libXrender.so.1 (0x00007f0afe121000)
	libz.so.1 => /lib64/libz.so.1 (0x00007f0afe105000)
	libm.so.6 => /lib64/libm.so.6 (0x00007f0afdfbf000)
	libuuid.so.1 => /lib64/libuuid.so.1 (0x00007f0afdfb6000)
	libexpat.so.1 => /lib64/libexpat.so.1 (0x00007f0afdf87000)
	libpthread.so.0 => /lib64/libpthread.so.0 (0x00007f0afdf65000)
	libbz2.so.1 => /lib64/libbz2.so.1 (0x00007f0afdf52000)
ldd 2048-Motif | wc -l
	26
```

### 2048-Xaw

```sh
ldd 2048-Xaw
	linux-vdso.so.1 (0x00007ffe4071c000)
	libXaw.so.7 => /lib64/libXaw.so.7 (0x00007f2e8ad14000)
	libXt.so.6 => /lib64/libXt.so.6 (0x00007f2e8aca7000)
	libX11.so.6 => /lib64/libX11.so.6 (0x00007f2e8ab60000)
	libc.so.6 => /lib64/libc.so.6 (0x00007f2e8a996000)
	libXext.so.6 => /lib64/libXext.so.6 (0x00007f2e8a981000)
	libXmu.so.6 => /lib64/libXmu.so.6 (0x00007f2e8a964000)
	libXpm.so.4 => /lib64/libXpm.so.4 (0x00007f2e8a94d000)
	libSM.so.6 => /lib64/libSM.so.6 (0x00007f2e8a942000)
	libICE.so.6 => /lib64/libICE.so.6 (0x00007f2e8a924000)
	libxcb.so.1 => /lib64/libxcb.so.1 (0x00007f2e8a8f8000)
	libdl.so.2 => /lib64/libdl.so.2 (0x00007f2e8a8f1000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f2e8ada6000)
	libuuid.so.1 => /lib64/libuuid.so.1 (0x00007f2e8a8e8000)
	libXau.so.6 => /lib64/libXau.so.6 (0x00007f2e8a8e0000)
ldd 2048-Xaw | wc -l
	15
```

### 2048-Xlib

```sh
ldd 2048-Xlib
	linux-vdso.so.1 (0x00007ffcce57d000)
	libX11.so.6 => /lib64/libX11.so.6 (0x00007f8b4748d000)
	libc.so.6 => /lib64/libc.so.6 (0x00007f8b472c3000)
	libxcb.so.1 => /lib64/libxcb.so.1 (0x00007f8b47297000)
	libdl.so.2 => /lib64/libdl.so.2 (0x00007f8b47290000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f8b475fc000)
	libXau.so.6 => /lib64/libXau.so.6 (0x00007f8b4728a000)
ldd 2048-Xlib | wc -l
	7
```

### 2048-Xcb

```sh
ldd 2048-Xcb
	linux-vdso.so.1 (0x00007fff9b3db000)
	libxcb.so.1 => /lib64/libxcb.so.1 (0x00007fce83eb4000)
	libxcb-keysyms.so.1 => /lib64/libxcb-keysyms.so.1 (0x00007fce83eaf000)
	libc.so.6 => /lib64/libc.so.6 (0x00007fce83ce5000)
	libXau.so.6 => /lib64/libXau.so.6 (0x00007fce83cdf000)
	/lib64/ld-linux-x86-64.so.2 (0x00007fce83f08000)
ldd 2048-Xcb | wc -l
	6
```

### 2048-MotoMAGX_Z6

```sh
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

```sh
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

```sh
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

```sh
/opt/toolchains/motomagx/arm-eabi/bin/arm-linux-gnueabi-objdump -x 2048-MotoMAGX_ZN5 | grep NEEDED
  NEEDED      libqte-mt.so.2
  NEEDED      libezxappbase.so.1
  NEEDED      libstdc++.so.6
  NEEDED      libm.so.6
  NEEDED      libgcc_s.so.1
  NEEDED      libc.so.6
```

### 2048-MotoMAGX_E8

```sh
/opt/toolchains/motomagx/arm-eabi/bin/arm-linux-gnueabi-objdump -x 2048-MotoMAGX_ZN5 | grep NEEDED
  NEEDED      libqte-mt.so.2
  NEEDED      libezxappbase.so.1
  NEEDED      libstdc++.so.6
  NEEDED      libm.so.6
  NEEDED      libgcc_s.so.1
  NEEDED      libc.so.6
```

### 2048-MotoMAGX_EM30

```sh
/opt/toolchains/motomagx/arm-eabi/bin/arm-linux-gnueabi-objdump -x 2048-MotoMAGX_EM30 | grep NEEDED
  NEEDED      libqte-mt.so.2
  NEEDED      libezxappbase.so.1
  NEEDED      libstdc++.so.6
  NEEDED      libm.so.6
  NEEDED      libgcc_s.so.1
  NEEDED      libc.so.6
```

### 2048-MotoMAGX_VE66

```sh
/opt/toolchains/motomagx/arm-eabi/bin/arm-linux-gnueabi-objdump -x 2048-MotoMAGX_VE66 | grep NEEDED
  NEEDED      libqte-mt.so.2
  NEEDED      libezxappbase.so.1
  NEEDED      libstdc++.so.6
  NEEDED      libm.so.6
  NEEDED      libgcc_s.so.1
  NEEDED      libc.so.6
```

### 2048-MotoMAGX_EM35

```sh
/opt/toolchains/motomagx/arm-eabi/bin/arm-linux-gnueabi-objdump -x 2048-MotoMAGX_EM35 | grep NEEDED
  NEEDED      libqte-mt.so.2
  NEEDED      libezxappbase.so.1
  NEEDED      libstdc++.so.6
  NEEDED      libm.so.6
  NEEDED      libgcc_s.so.1
  NEEDED      libc.so.6
```
