include(../common.pri)

SOURCES += \
   runner.cc

LIBS += -L../src -llaskenta

HEADERS += \
    firsttestsuite.h

system(cxxtestgen --error-printer -o runner.cc $$HEADERS)
