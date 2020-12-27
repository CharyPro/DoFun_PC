#ifndef CAMERAINTERFACE_H
#define CAMERAINTERFACE_H

class VideoInterface {
    virtual bool openVC(char *, int) = 0;
    virtual bool closeVC() = 0;

public:
    enum VIDEO_TYPE {
        CAMEAMODE,
        VIDEOMODEL
    };
};

#endif // CAMERAINTERFACE_H
