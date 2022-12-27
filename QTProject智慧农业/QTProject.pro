#-------------------------------------------------
#
# Project created by QtCreator 2022-12-14T15:27:15
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QTProject
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    signup.cpp

HEADERS  += mainwindow.h \
    signup.h


FORMS    += mainwindow.ui \
    signup.ui

RESOURCES += \
    image.qrc \
    im.qrc
