#ifndef NCNN_YOLACT_H
#define NCNN_YOLACT_H


#include "model_interface.h"



class ncnn_yolact : public MODE_INTERFACE
{

public:

    struct Object
    {
        cv::Rect_<float> rect;
        int label;
        float prob;
        std::vector<float> maskdata;
        cv::Mat mask;
    };

    ncnn_yolact();

    bool getresult(cv::Mat src, cv::Mat& resultimg);
};

#endif // NCNN_YOLACT_H
