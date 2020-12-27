#ifndef CARTOON_H
#define CARTOON_H

#include <opencv2/imgproc.hpp>
#include "FrameprocessInterface.h"

class Cartoon : public FrameprocessInterface
{
public:
    Cartoon();


    void cartoonImage(cv::Mat src, cv::Mat& dist);

    // FrameprocessInterface interface
    void processFrame(QImage &);
};

#endif // CARTOON_H
