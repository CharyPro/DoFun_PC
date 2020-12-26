QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Common/common.cpp \
    OpenCVExample/cartoon.cpp \
    attributesetting.cpp \
    opencvalgorithm/blur.cpp \
    opencvalgorithm/filter.cpp \
    opencvalgorithm/imgalgorithm.cpp \
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
    attributesetting.h \
    opencvalgorithm/blur.h \
    opencvalgorithm/filter.h \
    opencvalgorithm/imgalgorithm.h \
    opencvalgorithm/type.h \
    mainwindow.h \
    videoprocess.h \
    viewer.h
FORMS += \
    attributesetting.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += $$PWD/../../../3thlibrary/opencv/build/include
LIBS += -L$$PWD/../../../3thlibrary/opencv/build/x64/vc15/lib/ -lopencv_world342

