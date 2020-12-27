#ifndef IMGPROCESSINTERFACE_H
#define IMGPROCESSINTERFACE_H

#include <QImage>

class FrameprocessInterface {

public:
    virtual void processFrame(QImage &) = 0;

};

#endif // IMGPROCESSINTERFACE_H
