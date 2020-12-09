#-------------------------------------------------
#
# Project created by QtCreator 2012-10-03T15:11:53
#
#-------------------------------------------------

QT       += core gui

TARGET = world
TEMPLATE = lib
CONFIG += c++14
DEFINES += WORLD_LIBRARY

SOURCES += world.cpp

HEADERS += world.h\
        world_global.h

#place where library will be put on deployment, replace this by your own operating system and map
linux-g++ {
  target.path = /ext/qtprojects/world_v3
  INSTALLS += target
}

RESOURCES +=
