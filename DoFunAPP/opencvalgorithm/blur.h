#ifndef BLUR_H
#define BLUR_H

#include <opencv2/imgproc/imgproc.hpp>

class Blur
{
public:
    Blur();

    cv::Mat process(cv::Mat);
};

#endif // BLUR_H
