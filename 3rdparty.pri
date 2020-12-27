# opencv
INCLUDEPATH += $$PWD/../../../../3thlibrary/opencv/build/include
LIBS += -L$$PWD/../../../../3thlibrary/opencv/build/x64/vc15/lib/ -lopencv_world342

# ncnn
LIBS += -L$$PWD/DLCV/ncnn/lib/ -lncnn
INCLUDEPATH += $$PWD/DLCV/ncnn/include

