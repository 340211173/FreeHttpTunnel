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
    dispatcher.cpp \
    singleManager.cpp \
    singleHandler.cpp
HEADERS += dispatcher.h \
    singleManager.h \
    stuConnectionConfig.h \
    singleHandler.h
DESTDIR = ../bin/
