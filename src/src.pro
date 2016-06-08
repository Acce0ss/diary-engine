

include(../common.pri)

TARGET = diary-engine
TEMPLATE = lib

HEADERS += \
    entry.h \
    manager.h \
    book.h

SOURCES += \
    entry.cc \
    manager.cc \
    book.cc
