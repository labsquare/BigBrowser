INCLUDEPATH += $$PWD

include("reader/reader.pri")

HEADERS += \
    $$PWD/sequence.h \
    $$PWD/genom.h \
    $$PWD/region.h \
    $$PWD/regionlist.h \
    $$PWD/alphabet.h \
    $$PWD/nucleotidalphabet.h \
    $$PWD/proteinalphabet.h

SOURCES += \
    $$PWD/sequence.cpp \
    $$PWD/genom.cpp \
    $$PWD/region.cpp \
    $$PWD/regionlist.cpp \
    $$PWD/alphabet.cpp \
    $$PWD/nucleotidalphabet.cpp \
    $$PWD/proteinalphabet.cpp


