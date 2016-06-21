QMAKE_CXXFLAGS += -std=c++11

CONFIG += console
CONFIG -= app_bundle

INCLUDEPATH += $$PWD/src
SRC_DIR = $$PWD

DEFINES += DIARYENGINE_VERSION=\\\"0.1\\\"
