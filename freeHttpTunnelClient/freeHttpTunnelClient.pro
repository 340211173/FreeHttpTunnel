# -------------------------------------------------
# Project created by QtCreator 2011-03-19T19:52:17
# -------------------------------------------------
QT += network
TARGET = freeHttpTunnelClient
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
SOURCES += main.cpp \
    clsClientDispatcher.cpp \
    clsClientHandler.cpp
HEADERS += clsClientDispatcher.h \
    clsClientHandler.h
INCLUDEPATH += ../
LIBS += -L../lib/ \
    -lfreeHttpTunnelCommon
DESTDIR = ../bin/
