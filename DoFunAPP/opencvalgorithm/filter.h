#ifndef FILTER_H
#define FILTER_H

#include "type.h"

class Filter
{
public:
    Filter();

    std::vector<cv::Mat> process(cv::Mat);
};

#endif // FILTER_H
