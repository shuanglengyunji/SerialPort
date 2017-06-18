#-------------------------------------------------
#
# Project created by QtCreator 2016-01-27T13:35:50
#
#-------------------------------------------------

QT       += core gui
QT       += serialport
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SerialPort
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mainwindow_serialport.cpp \
    mainwindow_tcp.cpp \
    mainwindow_image.cpp \
    mainwindow_datadisplay.cpp \
    mainwindow_tools.cpp \
    mainwindow_setting.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
