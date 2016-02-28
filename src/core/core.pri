INCLUDEPATH += $$PWD


include("reader/reader.pri")

HEADERS += \
    $$PWD/app.h \
    $$PWD/sequence.h \
    $$PWD/genom.h

SOURCES += \
    $$PWD/app.cpp \
    $$PWD/sequence.cpp \
    $$PWD/genom.cpp

