#-------------------------------------------------
#
# Project created by QtCreator 2016-02-16T09:45:18
#
#-------------------------------------------------

QT     += core gui
CONFIG += c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BigBrowser
TEMPLATE = app

SOURCES += main.cpp \
    GUnzipDevice.cpp

LIBS+=-lz



include("core/core.pri")
include("gui/gui.pri")
include("quazip-0.7.1/quazip.pri")

HEADERS += \
    GUnzipDevice.h
