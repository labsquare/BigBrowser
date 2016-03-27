#-------------------------------------------------
#
# Project created by QtCreator 2016-02-16T09:45:18
#
#-------------------------------------------------

QT     += core gui network
CONFIG += c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET     = BigBrowser
TEMPLATE   = app
SOURCES += main.cpp


## QUAZIP AND ZLIB DEPENDENCY

unix{
LIBS+=-lz
include("libs/quazip-0.7.1/quazip/quazip.pri")
}

win32{
LIBS += -L$$PWD/libs/win32 -lquazip
INCLUDEPATH += $$PWD/libs/quazip-0.7.1/quazip
}




include("core/core.pri")
include("gui/gui.pri")
include("libs/QtAwesome/QtAwesome.pri")

RESOURCES += \
    icons/icons.qrc


