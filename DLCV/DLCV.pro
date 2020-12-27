QT -= gui

TEMPLATE = lib
CONFIG += c++11
TARGET = dlcv

DEFINES += DLCV_PLUGIN_LIBRARY

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dlcv.cpp \
    model_interface.cpp \
    ncnn_yolact.cpp

HEADERS += \
    dlcv.h \
    dlcv_global.h \
    dlcv_list.h \
    dlcvplugininterface.h \
    model_interface.h \
    ncnn_yolact.h

win32 {
    CONFIG(debug, release|debug):DESTDIR = ../debug/plugins/
    CONFIG(release, release|debug):DESTDIR = ../release/plugins/
} else {
    DESTDIR = ../plugins/
}

DISTFILES += \
    dlcv.json


# opencv
include($$PWD/../3rdparty.pri)
