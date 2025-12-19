QT       += core
QT       -= gui
CONFIG += console
QT += multimedia

TARGET = helloworld
TEMPLATE = app

HEADERS += audiodeviceutils.h
SOURCES += main.cpp \
           audiodeviceutils.cpp
