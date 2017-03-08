#-------------------------------------------------
#
# Project created by QtCreator 2016-10-26T11:05:20
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Student
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    sendfile.cpp \
    blackscreen.cpp \
    callname.cpp

HEADERS  += widget.h \
    sendfile.h \
    transferdata.h \
    blackscreen.h \
    callname.h

FORMS    += widget.ui \
    callname.ui \
    sendfile.ui

DISTFILES +=

RESOURCES += \
    resource.qrc
