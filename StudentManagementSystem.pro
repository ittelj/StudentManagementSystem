#-------------------------------------------------
#
# Project created by QtCreator 2017-09-19T18:59:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StudentManagementSystem
TEMPLATE = app


SOURCES += main.cpp \
    AdminDialog.cpp \
    LoginDialog.cpp \
    sql.cpp \
    btnAddInfo.cpp

HEADERS  += \
    LoginDialog.h \
    AdminDialog.h \
    sql.h \
    btnAddInfo.h

FORMS    +=

RESOURCES += \
    resources.qrc

DISTFILES +=

QT += sql
