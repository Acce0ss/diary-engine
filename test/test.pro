include(../common.pri)

TARGET = test

SOURCES += \
   runner.cc

LIBS += -L../src -ldiary-engine

HEADERS += \
    firsttestsuite.h \
    entrytestsuite.h

testgen.target = $$PWD/runner.cc
testgen.commands = cxxtestgen --error-printer --root -o runner.cc $$HEADERS

QMAKE_EXTRA_TARGETS += testgen

test.depends += testgen


