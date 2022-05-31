qtopia_project(qtopia app)
TARGET = 2048-Qt4-Qtopia4

CONFIG += qtopia_main
CONFIG += no_quicklaunch
CONFIG += no_singleexec

AVAILABLE_LANGUAGES = en_US
LANGUAGES           = $$AVAILABLE_LANGUAGES

INCLUDEPATH += ../src/

FORMS     += 2048-Qt4-Qtopia4.ui
HEADERS   += ../src/2048.h
SOURCES   += ../src/2048.c
SOURCES   += 2048-Qt4-Qtopia4.cpp

desktop.files    = 2048-Qt4-Qtopia4.desktop
desktop.path     = /apps/Games
desktop.trtarget = 2048-nct
desktop.hint     = nct desktop
INSTALLS        += desktop

pics.files = pics/*
pics.path  = /pics/2048-Qt4-Qtopia4
pics.hint  = pics
INSTALLS  += pics

help.source = help
help.files  = 2048-Qt4-Qtopia4.html
help.hint   = help
INSTALLS   += help

target.hint   = sxe
target.domain = untrusted

pkg.name       = 2048-Qt4-Qtopia4
pkg.desc       = A simple implementation of the 2048 puzzle game for Qtopia 4 using Qt 4.
pkg.version    = 1.0.0-1
pkg.maintainer = EXL (https://exlmoto.ru, https://github.com/EXL/2048)
pkg.license    = MIT
