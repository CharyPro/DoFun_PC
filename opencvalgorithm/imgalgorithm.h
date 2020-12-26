#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <opencv2/imgproc/imgproc.hpp>

class ImgAlgorithm
{
public:
    ImgAlgorithm();

    cv::Mat getResult(cv::Mat);
};

#endif // ALGORITHM_H
