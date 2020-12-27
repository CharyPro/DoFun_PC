QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += console
TEMPLATE = app
TARGET = app
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Common/common.cpp \
    OpenCVExample/cartoon.cpp \
    dlcv_ncnn.cpp \
    main.cpp \
    mainwindow.cpp \
    videoprocess.cpp \
    viewer.cpp

HEADERS += \
    Common/common.h \
    FrameProcess.h \
    FrameprocessInterface.h \
    OpenCVExample/cartoon.h \
    VideoInterface.h \
    ViewerInterface.h \
    dlcv_ncnn.h \
    mainwindow.h \
    videoprocess.h \
    viewer.h

FORMS += \
    mainwindow.ui

INCLUDEPATH += $$PWD/..

win32 {
    debug:DESTDIR = ../debug/
    release:DESTDIR = ../release/
} else {
    DESTDIR = ../
}

INCLUDEPATH += $$PWD/../../../../3thlibrary/opencv/build/include
LIBS += -L$$PWD/../../../../3thlibrary/opencv/build/x64/vc15/lib/ -lopencv_world342
