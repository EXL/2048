Porting 2048 Game to EZX Platform
=================================

To create correct Makefiles, the configuration file of the `tmake` utility needs to be patched. See this document for patching information and [2048-EZX/ReadMe.md](../2048-EZX/ReadMe.md) document for general building information. The 2048-EZX project contains a ready-to-build and fixed Makefiles already, so the patching step can be skipped.

## Task List

1. [x] Add some information about `tmake` and `progen` utilites.
2. [x] Add memory stats.
3. [x] Improve title bar widget: show game score via changing `QLabel` text.
4. [x] Disable touch clicks sound option.
5. [x] Create touch event controls.
6. [x] Implement basic game functionality.
7. [x] Add Telnet environment & run recipe.
8. [x] Test building on clean EZX SDK.
9. [x] Add PKG-package files.
10. [x] Create ReadMe.md files, screens, photos, etc.
11. [x] Create PKG-package building script.
12. [x] Add executable file/package information.
13. [x] Adapt code for Motorola E680.
14. [x] Adapt code for Motorola E680i.
15. [x] Adapt code for Motorola ROKR E2.
16. [ ] TODO: Adapt code for Motorola A760.

## EZX SDK & Toolchain patches (A1200, E6)

1. Fix typo in `ZMainWidget.h` header file:

```diff
--- motoezx-old/a1200/ezx2/include/ZMainWidget.h	2008-03-04 10:47:54.000000000 +0600
+++ motoezx/a1200/ezx2/include/ZMainWidget.h	2021-11-23 11:08:01.604360408 +0700
@@ -138,7 +138,7 @@
	  */
	 virtual bool setCSTWidget( QWidget* w = NULL );           //fox v: m8
	 virtual int setTitleBarWidget(QWidget*); //fox v: m$C add
-	QWidget* getTitleBarWiget(void); //add by eakrin
+	QWidget* getTitleBarWidget(void); //add by eakrin, fixed typo by EXL
	virtual int setFullScreenMode(bool, bool);  //fox v: m$10 add
```

2. Edit `tmake.conf` file:

```diff
--- motoezx-old/a1200/qt2/tmake/lib/qws/linux-gnu-ezx-g++/tmake.conf	2008-01-12 18:44:10.000000000 +0600
+++ motoezx/a1200/qt2/tmake/lib/qws/linux-gnu-ezx-g++/tmake.conf	2021-11-23 11:15:10.063079065 +0700
@@ -9,7 +9,7 @@
 
 TMAKE_CC		= arm-linux-gnu-gcc
 TMAKE_DASHCROSS		= -arm
-TMAKE_CFLAGS		= -pipe 
+TMAKE_CFLAGS		= -pipe -DEZX_E6
 TMAKE_CFLAGS_WARN_ON	= -Wall -W
 TMAKE_CFLAGS_WARN_OFF	=
 TMAKE_CFLAGS_RELEASE	= -O2 -mcpu=iwmmxt -mtune=iwmmxt
@@ -32,14 +32,14 @@
 TMAKE_LIBDIR		=
 TMAKE_INCDIR_X11	= 
 TMAKE_LIBDIR_X11	= 
-TMAKE_INCDIR_QT		= $(QTDIR)/include
+TMAKE_INCDIR_QT		= $(QTDIR)/include $(EZXDIR)/include
 TMAKE_LIBDIR_QT		= $(QTDIR)/lib
 TMAKE_INCDIR_OPENGL	= /usr/X11R6/include
 TMAKE_LIBDIR_OPENGL	= /usr/X11R6/lib
 
 TMAKE_LINK		= arm-linux-gnu-g++
 TMAKE_LINK_SHLIB	= arm-linux-gnu-g++
-TMAKE_LFLAGS		= -Wl,-rpath-link,$(QTDIR)/lib
+TMAKE_LFLAGS		= -Wl,-rpath-link,$(QTDIR)/lib,-rpath-link,$(EZXDIR)/lib
 TMAKE_LFLAGS_RELEASE	=
 TMAKE_LFLAGS_DEBUG	=
 TMAKE_LFLAGS_SHLIB	= -shared
@@ -47,7 +47,7 @@
 TMAKE_LFLAGS_THREAD	=
 TMAKE_RPATH		= -Wl,-rpath-link,$(QTDIR)/lib
 
-TMAKE_LIBS		= 
+TMAKE_LIBS		= -L$(EZXDIR)/lib -L$(EZXDIR)/lib/ezx/lib -lezxappbase
 TMAKE_LIBS_X11		= 
 TMAKE_LIBS_X11SM	= 
 TMAKE_LIBS_QT		= -lqte
```

## EZX SDK & Toolchain patches (E2)

1. Edit `tmake.conf` file:

```sh
rm /opt/toolchains/motoezx/e2/qt/tmake
cp -avR /opt/toolchains/motoezx/a1200/qt/tmake /opt/toolchains/motoezx/e2/qt/tmake
```

```diff
--- motoezx-old/e2/qt/tmake/lib/qws/linux-gnu-ezx-g++/tmake.conf	2008-01-12 18:44:10.000000000 +0600
+++ motoezx/e2/qt/tmake/lib/qws/linux-gnu-ezx-g++/tmake.conf	2021-11-23 11:23:40.459701145 +0700
@@ -9,7 +9,7 @@
 
 TMAKE_CC		= arm-linux-gnu-gcc
 TMAKE_DASHCROSS		= -arm
-TMAKE_CFLAGS		= -pipe 
+TMAKE_CFLAGS		= -pipe -DEZX_E2
 TMAKE_CFLAGS_WARN_ON	= -Wall -W
 TMAKE_CFLAGS_WARN_OFF	=
 TMAKE_CFLAGS_RELEASE	= -O2 -mcpu=iwmmxt -mtune=iwmmxt
@@ -32,14 +32,14 @@
 TMAKE_LIBDIR		=
 TMAKE_INCDIR_X11	= 
 TMAKE_LIBDIR_X11	= 
-TMAKE_INCDIR_QT		= $(QTDIR)/include
+TMAKE_INCDIR_QT		= $(QTDIR)/include $(EZXDIR)/include
 TMAKE_LIBDIR_QT		= $(QTDIR)/lib
 TMAKE_INCDIR_OPENGL	= /usr/X11R6/include
 TMAKE_LIBDIR_OPENGL	= /usr/X11R6/lib
 
 TMAKE_LINK		= arm-linux-gnu-g++
 TMAKE_LINK_SHLIB	= arm-linux-gnu-g++
-TMAKE_LFLAGS		= -Wl,-rpath-link,$(QTDIR)/lib
+TMAKE_LFLAGS		= -Wl,-rpath-link,$(QTDIR)/lib,-rpath-link,$(EZXDIR)/lib
 TMAKE_LFLAGS_RELEASE	=
 TMAKE_LFLAGS_DEBUG	=
 TMAKE_LFLAGS_SHLIB	= -shared
@@ -47,7 +47,7 @@
 TMAKE_LFLAGS_THREAD	=
 TMAKE_RPATH		= -Wl,-rpath-link,$(QTDIR)/lib
 
-TMAKE_LIBS		= 
+TMAKE_LIBS		= -L$(EZXDIR)/lib -L$(EZXDIR)/lib/ezx/lib -lezxappbase -lezxrichedit
 TMAKE_LIBS_X11		= 
 TMAKE_LIBS_X11SM	= 
 TMAKE_LIBS_QT		= -lqte
```

2. Copy all modern header files from Z6 directory of MotoMAGX EZX Toolchain to E2 directory:
// TODO: Link to MotoMAGX EZX Toolchain

```sh
rm -Rf /opt/toolchains/motoezx/e2/qt/include
cp -avR /arm-eabi/lib/qt-z6/include /opt/toolchains/motoezx/e2/qt

cp /arm-eabi/lib/ezx-z6/include/ZApplication.h /opt/toolchains/motoezx/e2/ezx/include/
cp /arm-eabi/lib/ezx-z6/include/ZKbMainWidget.h /opt/toolchains/motoezx/e2/ezx/include/
cp /arm-eabi/lib/ezx-z6/include/ZHeader.h /opt/toolchains/motoezx/e2/ezx/include/
cp /arm-eabi/lib/ezx-z6/include/ZKeyDef.h /opt/toolchains/motoezx/e2/ezx/include/
cp /arm-eabi/lib/ezx-z6/include/ZMessageDlg.h /opt/toolchains/motoezx/e2/ezx/include/
cp /arm-eabi/lib/ezx-z6/include/ZOptionsMenu.h /opt/toolchains/motoezx/e2/ezx/include/
cp /arm-eabi/lib/ezx-z6/include/ZGlobal.h /opt/toolchains/motoezx/e2/ezx/include/
cp /arm-eabi/lib/ezx-z6/include/ZNoticeDlg.h /opt/toolchains/motoezx/e2/ezx/include/
cp /arm-eabi/lib/ezx-z6/include/RES_ICON_Reader.h /opt/toolchains/motoezx/e2/ezx/include/
cp /arm-eabi/lib/ezx-z6/include/ZWidget.h /opt/toolchains/motoezx/e2/ezx/include/
cp /arm-eabi/lib/ezx-z6/include/ZMainWidget.h /opt/toolchains/motoezx/e2/ezx/include/
cp /arm-eabi/lib/ezx-z6/include/ZSkinBase.h /opt/toolchains/motoezx/e2/ezx/include/
cp /arm-eabi/lib/ezx-z6/include/ZPopup.h /opt/toolchains/motoezx/e2/ezx/include/
cp /arm-eabi/lib/ezx-z6/include/ZConfig.h /opt/toolchains/motoezx/e2/ezx/include/
cp /arm-eabi/lib/ezx-z6/include/ZIMethod.h /opt/toolchains/motoezx/e2/ezx/include/
cp /arm-eabi/lib/ezx-z6/include/ZFormContainer.h /opt/toolchains/motoezx/e2/ezx/include/
cp /arm-eabi/lib/ezx-z6/include/ZKbInputField.h /opt/toolchains/motoezx/e2/ezx/include/
cp /arm-eabi/lib/ezx-z6/include/ZDetailView.h /opt/toolchains/motoezx/e2/ezx/include/
cp /arm-eabi/lib/ezx-z6/include/ZMultiLineEdit.h /opt/toolchains/motoezx/e2/ezx/include/
cp /arm-eabi/lib/ezx-z6/include/ZGroupBox.h /opt/toolchains/motoezx/e2/ezx/include/
cp /arm-eabi/lib/ezx-z6/include/ZCheckBox.h /opt/toolchains/motoezx/e2/ezx/include/
cp /arm-eabi/lib/ezx-z6/include/ZExhibitButton.h /opt/toolchains/motoezx/e2/ezx/include/
cp /arm-eabi/lib/ezx-z6/include/ZScrollPanel.h /opt/toolchains/motoezx/e2/ezx/include/
cp /arm-eabi/lib/ezx-z6/include/ZLineEdit.h /opt/toolchains/motoezx/e2/ezx/include/
cp /arm-eabi/lib/ezx-z6/include/ZSeparator.h /opt/toolchains/motoezx/e2/ezx/include/
cp /arm-eabi/lib/ezx-z6/include/ZFormItem.h /opt/toolchains/motoezx/e2/ezx/include/
cp /arm-eabi/lib/ezx-z6/include/ZLabel.h /opt/toolchains/motoezx/e2/ezx/include/
cp /arm-eabi/lib/ezx-z6/include/ZFmwItem.h /opt/toolchains/motoezx/e2/ezx/include/
cp /arm-eabi/lib/ezx-z6/include/ZPressButton.h /opt/toolchains/motoezx/e2/ezx/include/
cp /arm-eabi/lib/ezx-z6/include/ZScrollBar.h /opt/toolchains/motoezx/e2/ezx/include/
cp /arm-eabi/lib/ezx-z6/include/ZWrapLine.h /opt/toolchains/motoezx/e2/ezx/include/
cp /arm-eabi/lib/ezx-z6/include/ZTableView.h /opt/toolchains/motoezx/e2/ezx/include/
cp /arm-eabi/lib/ezx-z6/include/ZBaseButton.h /opt/toolchains/motoezx/e2/ezx/include/
```

## EZX SDK & Toolchain patches (A780, E680i)

1. Edit `tmake.conf` file:

```diff
--- motoe680-old/e680/tmake/lib/qws/linux-e680-g++/tmake.conf	2021-09-01 09:42:21.000000000 +0700
+++ motoe680/e680/tmake/lib/qws/linux-e680-g++/tmake.conf	2021-11-21 04:28:26.097524240 +0700
@@ -9,7 +9,7 @@
 
 TMAKE_CC		= arm-linux-gcc
 TMAKE_DASHCROSS		= -arm
-TMAKE_CFLAGS		= -pipe 
+TMAKE_CFLAGS		= -pipe -DEZX_E680I
 TMAKE_CFLAGS_WARN_ON	= -Wall -W
 TMAKE_CFLAGS_WARN_OFF	=
 TMAKE_CFLAGS_RELEASE	= -O2
@@ -39,13 +39,13 @@
 
 TMAKE_LINK		= arm-linux-g++
 TMAKE_LINK_SHLIB	= arm-linux-g++
-TMAKE_LFLAGS		=
+TMAKE_LFLAGS		=-Wl,-rpath-link,$(QTDIR)/lib
 TMAKE_LFLAGS_RELEASE	=
 TMAKE_LFLAGS_DEBUG	=
 TMAKE_LFLAGS_SHLIB	= -shared
 TMAKE_LFLAGS_SONAME	= -Wl,-soname,
 TMAKE_LFLAGS_THREAD	=
-TMAKE_RPATH		= -Wl,-rpath,
+TMAKE_RPATH		= -Wl,-rpath-link,$(QTDIR)/lib
 
 TMAKE_LIBS		= 
 TMAKE_LIBS_X11		= 
```

2. Create symlink:

```sh
cd /opt/toolchains/motoe680/e680/include/ezx/
ln -s zmessagebox.h ZMessageBox.h
```

## EZX SDK & Toolchain patches (A760, E680)

1. Edit `ezxutilpushbutton.h` file:

```diff
--- motoe680-old/e680/include/ezx/ezxutilpushbutton.h	2005-11-22 05:37:22.000000000 +0600
+++ motoe680/e680/include/ezx/ezxutilpushbutton.h	2021-11-26 17:00:14.303070430 +0700
@@ -43,6 +43,7 @@
 class UTIL_PushButton : public QToolButton {
	Q_OBJECT
 public:
+	enum Flags { NoFlags = 0, JoinLeft = 1, JoinRight = 2, CSTStyle = 4, DialogCSTStyle = 8 };
	virtual void drawButton(QPainter*);
	virtual void paintEvent(QPaintEvent*);
	virtual void setPalette(QPalette const&);
```

2. Edit `ezxutilgraph.h` file:

```diff
diff -ur /home/exl/Downloads/EZX_SDK_0.3/include/ezx/ezxutilgraph.h /opt/toolchains/motoe680/e680/include/ezx/ezxutilgraph.h
--- motoe680-old/e680/include/ezx/ezxutilgraph.h	2005-11-22 05:36:44.000000000 +0600
+++ motoe680/e680/include/ezx/ezxutilgraph.h	2021-11-26 16:59:43.759738497 +0700
@@ -33,6 +33,7 @@
 #include <qpixmap.h>

 class UTIL_Graph {
+public:
	static void drawUnderLine(QPainter*, QColorGroup const&,
				  QPoint const&, QPoint const&);
	static void drawOutlineText(QPainter*, QColor, QColor, int, int,
```

3. Create symlink:

```sh
cd /opt/toolchains/motoe680/e680/include/ezx/
ln -s zglobal.h ZGlobal.h
```
