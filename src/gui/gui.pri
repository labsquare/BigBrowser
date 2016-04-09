INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/mainwindow.h \
    $$PWD/chromosomwidget.h \
    $$PWD/statusbar.h \
    $$PWD/app.h \
    $$PWD/selectionrouter.h \
    $$PWD/selecttoolbar.h \
    $$PWD/trackswidget.h \
    $$PWD/unit.h

SOURCES += \
    $$PWD/mainwindow.cpp \
    $$PWD/chromosomwidget.cpp \
    $$PWD/statusbar.cpp \
    $$PWD/app.cpp \
    $$PWD/selectionrouter.cpp \
    $$PWD/selecttoolbar.cpp \
    $$PWD/trackswidget.cpp \
    $$PWD/unit.cpp


include(settings/settings.pri)
include(tracks/tracks.pri)
include("models/models.pri")

