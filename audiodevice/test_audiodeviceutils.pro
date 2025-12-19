QT += core testlib multimedia
QT -= gui

CONFIG += qt warn_on depend_includepath testcase
CONFIG += c++11 console

TARGET = test_audiodeviceutils
TEMPLATE = app

SOURCES += test_audiodeviceutils.cpp \
           audiodeviceutils.cpp

HEADERS += audiodeviceutils.h

