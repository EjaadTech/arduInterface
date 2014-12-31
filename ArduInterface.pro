#-------------------------------------------------
#
# Project created by QtCreator 2014-12-29T23:44:44
#
#-------------------------------------------------

QT       += core gui
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ArduInterface
TEMPLATE = app


SOURCES += main.cpp\
        arduinterface.cpp

HEADERS  += arduinterface.h

FORMS    += arduinterface.ui

CONFIG += qwt
include ( /usr/local/qwt-6.1.2/features/qwt.prf )
