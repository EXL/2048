qtopia_project(qtopia app)
TARGET=2048-Qt4-Qtopia4

# main.cpp uses the QTOPIA_ADD_APPLICATION/QTOPIA_MAIN macros
CONFIG+=qtopia_main

# Despite using the QTOPIA_MAIN macro, do not build this app as a
# quicklaunch plugin
CONFIG+=no_quicklaunch

# Do not build this app into a singleexec binary
CONFIG+=no_singleexec

# Specify the languages that make lupdate should produce .ts files for
AVAILABLE_LANGUAGES=en_US

# Specify the langauges we want to install translations for
LANGUAGES=$$AVAILABLE_LANGUAGES

# These are the source files that get built to create the application
FORMS=2048-Qt4-Qtopia4.ui
HEADERS=../src/2048.h # 2048-Qt4-Qtopia4.cpp
SOURCES=../src/2048.c 2048-Qt4-Qtopia4.cpp

INCLUDEPATH+=../src/

# Install the launcher item. The metadata comes from the .desktop file
# and the path here.
desktop.files=2048-Qt4-Qtopia4.desktop
desktop.path=/apps/Games
desktop.trtarget=2048-nct
desktop.hint=nct desktop
INSTALLS+=desktop

# Install some pictures.
pics.files=pics/*
pics.path=/pics/2048
pics.hint=pics
INSTALLS+=pics

# Install help files
help.source=help
help.files=example.html
help.hint=help
INSTALLS+=help

# SXE information
target.hint=sxe
target.domain=untrusted

# Package information (used for make packages)
pkg.name=2048-Qt4-Qtopia4
pkg.desc=A simple implementation of the 2048 puzzle game for Qtopia 4 using Qt 4.
pkg.version=1.0.0-1
pkg.maintainer=EXL (https://exlmoto.ru, https://github.com/EXL/2048)
pkg.license=MIT
