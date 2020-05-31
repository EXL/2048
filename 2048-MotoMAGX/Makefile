# This Makefile edited by EXL, 31-May-2020
#
# App can compile for platform:
#    PLATFORM=EZX-Z6
#    PLATFORM=EZX-V8
#    PLATFORM=EZX-Z6W
#    PLATFORM=EZX-U9
#    PLATFORM=EZX-ZN5 (default)
#    PLATFORM=EZX-E8
#    PLATFORM=EZX-EM30
#    PLATFORM=EZX-VE66
#    PLATFORM=EZX-EM35
#
# For example - compile this source for Motorla ZN5:
#
# cd /PROJECT_FOLDER/
# make clean
# make PLATFORM=EZX-ZN5
#

####### Config
APPNAME     := 2048-MotoMAGX
UPLOAD_PATH := /mmc/mmca1/
#APP_DEFINES := -DDEBUG_LOG -DCONFIG_APPWRITE

####### SDK and Toolchains
TOOLPREFIX  := /arm-eabi
ARMLIB      := $(TOOLPREFIX)/arm-linux-gnueabi/lib

####### Default Platform
ifeq ($(PLATFORM),)
PLATFORM     = EZX-ZN5
endif

####### Platforms
ifeq ($(PLATFORM),EZX-Z6)
QTDIR       := $(TOOLPREFIX)/lib/qt-2.3.8
EZXDIR      := $(TOOLPREFIX)/lib/ezx-z6
LINKLIB     := -lm -lqte-mt -lezxpm -ljpeg -lezxappbase -lezxtapi-xscale-r -llog_util -llighting
DIRECTIV    := -DEZX_Z6 $(APP_DEFINES)
TARGET       = $(APPNAME)_Z6
endif
ifeq ($(PLATFORM),EZX-V8)
QTDIR       := $(TOOLPREFIX)/lib/qt-v8
EZXDIR      := $(TOOLPREFIX)/lib/ezx-v8
LINKLIB     := -lm -lqte-mt -lezxpm -lezxappbase
DIRECTIV    := -DEZX_V8 $(APP_DEFINES)
TARGET       = $(APPNAME)_V8
ZNEWCHECKBOX = 1
endif
ifeq ($(PLATFORM),EZX-E8)
ARMLIB      := $(TOOLPREFIX)/arm-linux-gnueabi/lib_E8
QTDIR       := $(TOOLPREFIX)/lib/qt-e8
EZXDIR      := $(TOOLPREFIX)/lib/ezx-e8
LINKLIB     := -lm -lqte-mt -lezxappbase
DIRECTIV    := -DEZX_E8 $(APP_DEFINES)
TARGET       = $(APPNAME)_E8
endif
ifeq ($(PLATFORM),EZX-EM30)
ARMLIB      := $(TOOLPREFIX)/arm-linux-gnueabi/lib_E8
QTDIR       := $(TOOLPREFIX)/lib/qt-em30
EZXDIR      := $(TOOLPREFIX)/lib/ezx-em30
EZXDIR2     := $(TOOLPREFIX)/lib/ezx-e8
LINKLIB     := -lm -lqte-mt -lezxappbase
DIRECTIV    := -DEZX_EM30 $(APP_DEFINES)
TARGET       = $(APPNAME)_EM30
endif
ifeq ($(PLATFORM),EZX-U9)
QTDIR       := $(TOOLPREFIX)/lib/qt-zn5
EZXDIR      := $(TOOLPREFIX)/lib/ezx-u9
EZXDIR2     := $(TOOLPREFIX)/lib/ezx-zn5
LINKLIB     := -lm -lqte-mt -lezxappbase -llighting
DIRECTIV    := -DEZX_U9 $(APP_DEFINES)
TARGET       = $(APPNAME)_U9
endif
ifeq ($(PLATFORM),EZX-Z6W)
QTDIR       := $(TOOLPREFIX)/lib/qt-z6w
EZXDIR      := $(TOOLPREFIX)/lib/ezx-z6w
LINKLIB     := -lm -lqte-mt -lezxappbase
DIRECTIV    := -DEZX_Z6W $(APP_DEFINES)
TARGET       = $(APPNAME)_Z6W
endif
ifeq ($(PLATFORM),EZX-ZN5)
QTDIR       := $(TOOLPREFIX)/lib/qt-zn5
EZXDIR      := $(TOOLPREFIX)/lib/ezx-zn5
LINKLIB     := -lm -lqte-mt -lezxappbase
DIRECTIV    := -DEZX_ZN5 $(APP_DEFINES)
TARGET       = $(APPNAME)_ZN5
endif
ifeq ($(PLATFORM),EZX-EM35)
ARMLIB      := $(TOOLPREFIX)/arm-linux-gnueabi/lib_E8
QTDIR       := $(TOOLPREFIX)/lib/qt-em35
EZXDIR      := $(TOOLPREFIX)/lib/ezx-em35
LINKLIB     := -lm -lqte-mt -lezxappbase
DIRECTIV    := -DEZX_EM35 $(APP_DEFINES)
TARGET       = $(APPNAME)_EM35
endif
ifeq ($(PLATFORM),EZX-VE66)
ARMLIB      := $(TOOLPREFIX)/arm-linux-gnueabi/lib_E8
QTDIR       := $(TOOLPREFIX)/lib/qt-em35
EZXDIR      := $(TOOLPREFIX)/lib/ezx-ve66
LINKLIB     := -lm -lqte-mt -lezxappbase
DIRECTIV    := -DEZX_VE66 $(APP_DEFINES)
TARGET       = $(APPNAME)_VE66
endif

####### Build Tools and Options
CC           = $(TOOLPREFIX)/bin/arm-linux-gnueabi-gcc
CXX          = $(TOOLPREFIX)/bin/arm-linux-gnueabi-g++
LD           = $(TOOLPREFIX)/bin/arm-linux-gnueabi-g++
STRIP        = $(TOOLPREFIX)/bin/arm-linux-strip
CFLAGS       = -pipe -Wall -W -O2 -DNO_DEBUG $(INCPATH)
CXXFLAGS     = -pipe -DQWS -fno-exceptions -fno-rtti -Wall -W -O2 -DNO_DEBUG $(DIRECTIV) $(INCPATH)
INCPATH      = -I$(QTDIR)/include -I$(EZXDIR)/include -I $(TOOLPREFIX)/arm-linux-gnueabi/include
LDFLAGS      = -s
LINK         = $(TOOLPREFIX)/bin/arm-linux-gnueabi-gcc
LFLAGS       = -Wl,-rpath-link,$(EZXDIR)/lib
LIBS         = $(SUBLIBS) -L$(EZXDIR)/lib -L$(ARMLIB) -L$(QTDIR)/lib $(LINKLIB)
MOC          = $(QTDIR)/bin/moc
UIC          = $(QTDIR)/bin/uic

####### Files
HEADERS      = 2048-MotoMAGX.cpp
SOURCES      = 2048-MotoMAGX.cpp
OBJECTS      = 2048-MotoMAGX.o
SRCMOC       = 2048-MotoMAGX.moc

####### Targets
TARGETS      = $(TARGET)
INTERFACE_DECL_PATH = .

all: $(SRCMOC) $(TARGET)

$(TARGET): $(UICDECLS) $(OBJECTS) $(OBJMOC)
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJMOC) $(LIBS)
	$(STRIP) -s $(MAKETO) $(TARGET)

moc: $(SRCMOC)

rmobj:
	-rm -f $(OBJECTS) $(OBJMOC) $(SRCMOC) $(UICIMPLS) $(UICDECLS)
	-rm -f *~ core
	$(RM) *.o
	$(RM) *.moc

clean:
	-rm -f $(OBJECTS) $(OBJMOC) $(SRCMOC) $(UICIMPLS) $(UICDECLS)
	-rm -f *~ core
	$(RM) *.o
	$(RM) *.moc
	$(RM) $(TARGET) $(APPNAME)_*

#--------- moc's -----------------------------
2048-MotoMAGX.moc: 2048-MotoMAGX.cpp
	$(MOC) 2048-MotoMAGX.cpp -o 2048-MotoMAGX.moc
