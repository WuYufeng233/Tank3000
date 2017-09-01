#-------------------------------------------------
#
# Project created by QtCreator 2017-08-15T21:15:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tank_3000
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    base.cpp \
    mapseg.cpp \
    fullmap.cpp \
    tank.cpp \
    missile.cpp \
    boss.cpp

HEADERS  += mainwindow.h \
    base.h \
    data.h \
    mapseg.h \
    fullmap.h \
    tank.h \
    missile.h \
    boss.h

RESOURCES += \
    src.qrc
