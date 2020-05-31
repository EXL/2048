2048 Notes
==========

# Porting 2048 on MotoMAGX

First building on various MotoMAGX platforms:

* Z6

    All Ok!

* V8

    All Ok!

* Z6W

    Link error:

    ```
    undefined reference to `QPainter::drawRoundRect(int, int, int, int, int, int)'
    ```

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

* ZN5

    Link error:

    ```
    undefined reference to `QPainter::drawRoundRect(int, int, int, int, int, int)'
    ```

* E8

    All Ok!

* EM30

    All Ok!

* VE66

    All Ok!

* EM35

    All Ok!
