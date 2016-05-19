QMAKE_CXXFLAGS += -std=c++11

CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

CONFIG += link_pkgconfig

PKGCONFIG += opencv

INCLUDEPATH += $$PWD/src
SRC_DIR = $$PWD
