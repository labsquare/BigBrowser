#-------------------------------------------------
#
# Project created by QtCreator 2016-02-15T13:31:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BigListViewer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    biglistmodel.cpp

HEADERS  += mainwindow.h \
    biglistmodel.h

FORMS    += mainwindow.ui
