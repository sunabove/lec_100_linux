#-------------------------------------------------
#
# Project created by QtCreator 2018-06-09T08:57:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Chat
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    OpCode.cpp \
    OpCodeMsg.cpp \
    zf_log.c \
    Client.cpp \
    Socket.cpp \
    ChatRoom.cpp \
    OpCodeExit.cpp \
    OpCodeSysInfo.cpp \
    OpCodeAck.cpp \
    OpCodeNack.cpp \
    OpCodeFile.cpp

HEADERS += \
        mainwindow.h \
    Socket.h \
    Client.h \
    ChatRoom.h \
    Server.h \
    OpCode.h \
    OpCodeMsg.h \
    zf_log.h \
    OpCodeExit.h \
    OpCodeSysInfo.h \
    OpCodeAck.h \
    OpCodeNack.h \
    OpCodeFile.h

FORMS += \
        mainwindow.ui
