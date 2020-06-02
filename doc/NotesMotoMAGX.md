Porting 2048 Game on MotoMAGX Platform
======================================

### First building on various MotoMAGX platforms

* Z6

    All Ok!

* V8

    All Ok!

* Z6W

    Link error:

    ```
    undefined reference to `QPainter::drawRoundRect(int, int, int, int, int, int)'
    ```

    Dirty Fix: use `drawRect()` method instead.

    Fix: Emulate `drawRoundRect()` method with `drawPie()` and `drawRect()` methods.

* U9

    Broken SDK:

    ```
    /arm-eabi/lib/qt-zn5/include/qwidget.h:70:27: morphing_mode.h: No such file or directory
    /opt/toolchains/motomagx/arm-eabi/bin/../lib/gcc/arm-linux-gnueabi/3.4.3/../../../../arm-linux-gnueabi/bin/ld: cannot find -llighting
    ```

    Fixing:

    ```
    sudo cp /opt/toolchains/motomagx/arm-eabi/lib/ezx-zn5/include/morphing_mode.h /opt/toolchains/motomagx/arm-eabi/lib/ezx-u9/include/
    sudo ln -sf /opt/toolchains/motomagx/arm-eabi/lib/ezx-zn5/lib/liblighting.so /opt/toolchains/motomagx/arm-eabi/lib/ezx-u9/lib/liblighting.so
    ```

    After fixing:

    ```
    undefined reference to `QPainter::drawRoundRect(int, int, int, int, int, int)'
    ```

    Dirty Fix: use `drawRect()` method instead.

    Fix: Emulate `drawRoundRect()` method with `drawPie()` and `drawRect()` methods.

* ZN5

    Link error:

    ```
    undefined reference to `QPainter::drawRoundRect(int, int, int, int, int, int)'
    ```

    Dirty Fix: use `drawRect()` method instead.

    Fix: Emulate `drawRoundRect()` method with `drawPie()` and `drawRect()` methods.

* E8

    All Ok!

* EM30

    All Ok!

* VE66

    All Ok!

* EM35

    All Ok!

### Some fixes for old MotoMAGX phones like Z6 and V8

1. Inconsistent keycodes.

    ```
    2048-MotoMAGX.cpp: In member function `virtual void Board::keyPressEvent(QKeyEvent*)':
    2048-MotoMAGX.cpp:248: error: `KEYCODE_0' undeclared (first use this function)
    2048-MotoMAGX.cpp:248: error: (Each undeclared identifier is reported only once for each function it appears in.)
    2048-MotoMAGX.cpp:254: error: `KEYCODE_UP' undeclared (first use this function)
    2048-MotoMAGX.cpp:254: error: `KEYCODE_2' undeclared (first use this function)
    2048-MotoMAGX.cpp:255: error: `KEYCODE_DOWN' undeclared (first use this function)
    2048-MotoMAGX.cpp:255: error: `KEYCODE_8' undeclared (first use this function)
    2048-MotoMAGX.cpp:256: error: `KEYCODE_LEFT' undeclared (first use this function)
    2048-MotoMAGX.cpp:256: error: `KEYCODE_4' undeclared (first use this function)
    2048-MotoMAGX.cpp:257: error: `KEYCODE_RIGHT' undeclared (first use this function)
    2048-MotoMAGX.cpp:257: error: `KEYCODE_6' undeclared (first use this function)
    ```

    Fix:

    ```
    #if defined(EZX_Z6) || defined (EZX_V8)
    #define KEYCODE_0                              EZX_KEY_0
    #define KEYCODE_2                              EZX_KEY_2
    #define KEYCODE_4                              EZX_KEY_4
    #define KEYCODE_6                              EZX_KEY_6
    #define KEYCODE_8                              EZX_KEY_8
    #define KEYCODE_UP                             EZX_KEY_UP
    #define KEYCODE_DOWN                           EZX_KEY_DOWN
    #define KEYCODE_LEFT                           EZX_KEY_LEFT
    #define KEYCODE_RIGHT                          EZX_KEY_RIGHT
    #endif
    ```

2. ZPanel constructor error:

    ```
    2048-MotoMAGX.cpp: In constructor `Board::Board(QWidget*, const char*)':
    2048-MotoMAGX.cpp:239: error: no matching function for call to `ZPanel::ZPanel(QWidget*&, const char*&)'
    /arm-eabi/lib/ezx-z6/include/ZPanel.h:9: note: candidates are: ZPanel::ZPanel(const ZPanel&)
    /arm-eabi/lib/ezx-z6/include/ZPanel.h:13: note:                 ZPanel::ZPanel(QWidget*, const char*, unsigned int, ZSkinService::WidgetClsID)
    ```

    Fix, add zero WFlags:

    ```cpp
    Board(QWidget *parent = 0, const char *name = 0) : ZPanel(parent, name, /* WFlags */ 0) {
    ```

3. Linking ZPanel problem:

    ```
    2048-MotoMAGX.o: In function `Board::staticMetaObject()':
    2048-MotoMAGX.cpp:(.text+0x160): undefined reference to `ZPanel::staticMetaObject()'
    2048-MotoMAGX.o: In function `Board::initMetaObject()':
    2048-MotoMAGX.cpp:(.text+0x21c): undefined reference to `ZPanel::className() const'
    ```

    Fix: Use just `QWidget` instead of `ZPanel` class.

4. ZHeader inconsistent error:

    ```
    2048-MotoMAGX.cpp: In constructor `MainWidget::MainWidget(QWidget*, const char*, uint)':
    2048-MotoMAGX.cpp:292: error: `MAINDISPLAY_HEADER' is not a member of `ZHeader'
    ```

    Fix:

    ```
    #ifdef EZX_V8
    #define MAINDISPLAY_HEADER                     TINY_TYPE
    #endif
    ```
