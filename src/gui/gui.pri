INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/mainwindow.h \
    $$PWD/maintoolbar.h \
    $$PWD/chromosomwidget.h \
    $$PWD/tracklistwidget.h \
    $$PWD/statusbar.h

SOURCES += \
    $$PWD/mainwindow.cpp \
    $$PWD/maintoolbar.cpp \
    $$PWD/chromosomwidget.cpp \
    $$PWD/tracklistwidget.cpp \
    $$PWD/statusbar.cpp


include(settings/settings.pri)
