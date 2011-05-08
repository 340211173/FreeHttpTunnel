# -------------------------------------------------
# Project created by QtCreator 2011-03-19T19:52:17
# -------------------------------------------------
QT += network
QT -= gui
TARGET = freeHttpTunnelServer
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
SOURCES += main.cpp \
    clsServerHandler.cpp \
    clsServerDistpacher.cpp
HEADERS += stuConnectionConfig.h \
    clsServerHandler.h \
    clsServerDistpacher.h
INCLUDEPATH += ../
LIBS += -L../lib/ \
    -lfreeHttpTunnelCommon
DESTDIR = ../bin/
