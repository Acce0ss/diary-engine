include(../common.pri)

SOURCES += \
   runner.cc

LIBS += -L../src -ldiary-engine

HEADERS += \
    firsttestsuite.h

system(cxxtestgen --error-printer --root -o runner.cc $$HEADERS)
