INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/mainwindow.h \
    $$PWD/chromosomwidget.h \
    $$PWD/tracklistwidget.h \
    $$PWD/statusbar.h \
    $$PWD/searchtoolbar.h \
    $$PWD/app.h \
    $$PWD/genetoolwidget.h

SOURCES += \
    $$PWD/mainwindow.cpp \
    $$PWD/chromosomwidget.cpp \
    $$PWD/tracklistwidget.cpp \
    $$PWD/statusbar.cpp \
    $$PWD/searchtoolbar.cpp \
    $$PWD/app.cpp \
    $$PWD/genetoolwidget.cpp


include(settings/settings.pri)
include(tracks/tracks.pri)
include("models/models.pri")

