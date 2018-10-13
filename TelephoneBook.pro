#-------------------------------------------------
#
# Project created by QtCreator 2018-05-27T06:54:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TelephoneBook
TEMPLATE = app
#CONFIG   += console
CONFIG  += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    addorremove.cpp \
    searchwindow.cpp \
    contact.cpp \
    editwindow.cpp

HEADERS  += mainwindow.h \
    addorremove.h \
    searchwindow.h \
    contact.h \
    editwindow.h
