#-------------------------------------------------
#
# Project created by QtCreator 2015-04-19T10:08:07
#
#-------------------------------------------------

QT       += network

QT       -= gui

CONFIG  += c++11

TARGET = cpp-yamusic
TEMPLATE = lib
CONFIG += staticlib

SOURCES += yandexmusicapi.cpp \
    filedownloader.cpp

HEADERS += yandexmusicapi.h \
    filedownloader.h \
    cpp-yamusic.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
