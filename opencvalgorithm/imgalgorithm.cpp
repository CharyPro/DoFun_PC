#include "imgalgorithm.h"
#include "blur.h"
#include "filter.h"

ImgAlgorithm::ImgAlgorithm()
{

//    blur.process(mat);
}

cv::Mat ImgAlgorithm::getResult(cv::Mat frame)
{
    Blur blur;
    cv::Mat result = blur.process(frame);
//    Filter filter;
//    std::vector<cv::Mat> resultVec = filter.process(frame);
//    cv::Mat result = resultVec[1];
//    cv::Mat kernel = (cv::Mat_<float>(3,3) << 0,-1,0,-1,5,-1,0,-1,0);
//    cv::Mat sharpen_laplace;
//    cv::filter2D(frame,result,frame.depth(),kernel);


    return result;
}
