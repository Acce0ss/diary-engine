

include(../common.pri)

TARGET = diary-engine
TEMPLATE = lib

HEADERS += \
    myclass.h \
    global_defines.h \
    entry.h \
    manager.h \
    book.h

SOURCES += \
    myclass.cc \
    entry.cc \
    manager.cc \
    book.cc
