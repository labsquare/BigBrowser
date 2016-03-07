#-------------------------------------------------
#
# Project created by QtCreator 2016-02-16T09:45:18
#
#-------------------------------------------------

QT     += core gui
CONFIG += c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET     = BigBrowser
TEMPLATE   = app
DISTFILES += ../data

SOURCES += main.cpp

unix:LIBS+=-lz





include("core/core.pri")
#include("gui/gui.pri")
include("libs/quazip-0.7.1/quazip.pri")


