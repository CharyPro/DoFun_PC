#ifndef DLCV_NCNN_H
#define DLCV_NCNN_H

#include "FrameprocessInterface.h"
#include <DLCV/dlcv.h>


class DLCV_NCNN : public FrameprocessInterface
{
public:
    DLCV_NCNN(DLCV_INTERFACE *, QString);

    void processFrame(QImage &);

private:
    DLCV_INTERFACE *model;
    QString modelname;
};

#endif // DLCV_NCNN_H
