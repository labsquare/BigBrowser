INCLUDEPATH += $$PWD


include("reader/reader.pri")

HEADERS += \
    $$PWD/app.h \
    $$PWD/sequence.h \
    $$PWD/genom.h \
    $$PWD/selector.h

SOURCES += \
    $$PWD/app.cpp \
    $$PWD/sequence.cpp \
    $$PWD/genom.cpp \
    $$PWD/selector.cpp

