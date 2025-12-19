QT += core testlib widgets
QT -= gui

CONFIG += qt warn_on depend_includepath testcase
CONFIG += c++11 link_pkgconfig
PKGCONFIG += gsettings-qt

TARGET = test_mainwindow
TEMPLATE = app

SOURCES += test_mainwindow.cpp \
           mainwindow.cpp

HEADERS += mainwindow.h

