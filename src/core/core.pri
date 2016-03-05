INCLUDEPATH += $$PWD


include("reader/reader.pri")

HEADERS += \
    $$PWD/app.h \
    $$PWD/sequence.h \
    $$PWD/genom.h \
    $$PWD/section.h

SOURCES += \
    $$PWD/app.cpp \
    $$PWD/sequence.cpp \
    $$PWD/genom.cpp \
    $$PWD/section.cpp

