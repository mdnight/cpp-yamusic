#-------------------------------------------------
#
# Project created by QtCreator 2015-04-19T10:08:07
#
#-------------------------------------------------

QT       += network

QT       -= gui

TARGET = cpp-yamusic
TEMPLATE = lib
CONFIG += staticlib

SOURCES += yandexmusicapi.cpp

HEADERS += yandexmusicapi.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
