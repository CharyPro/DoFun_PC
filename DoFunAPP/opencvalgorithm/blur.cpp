#include "blur.h"

using namespace cv;

Blur::Blur()
{

}


Mat Blur::process(Mat currentframe)
{
    Mat resultframe;
#if 1
    //--2.转换灰度图
    cv::Mat gray;
    cv::cvtColor(currentframe,gray,CV_RGB2GRAY);

    //--3.二值化灰度图
    cv::Mat binary;
    cv::threshold(gray,binary,60,255,cv::THRESH_BINARY_INV);
    //平滑处理(平滑/高斯平滑两种)
    //cv::blur(dst,dst,cv::Size(3,3));
    //cv::GaussianBlur(dst,dst,cv::Size(3,3),0,0); //高斯平滑

    //形态学操作（此处效果不好，只用来展示加强理解）
    //cv::erode(dst,dst,cv::Mat(),cv::Point(-1,-1),1);
    //cv::dilate(dst,dst,cv::Mat(),cv::Point(-1,-1),1);


    //--4.寻找轮廓
    std::vector<std::vector<cv::Point> > contours;
    cv::Mat binary_copy; //因为findcontours函数会改变输入的图像，所以复制一个图像作为函数的输入
    binary.copyTo(binary_copy);
    cv::findContours(binary_copy,contours,CV_RETR_EXTERNAL/*获取外轮廓*/,CV_CHAIN_APPROX_NONE/*获取每个轮廓的每个像素*/);

    //遍历每一个轮廓，把多余的轮廓去掉
    std::vector<std::vector<cv::Point> >::const_iterator it=contours.begin();
    while(it!=contours.end()){
        if(it->size()<500||cv::boundingRect(*it).width>0.5*currentframe.cols)
            it = contours.erase(it);
        else
            ++it;
    }

    //重新绘制轮廓
    cv::Mat mask(currentframe.size(),CV_8U,cv::Scalar(0));
    cv::drawContours(mask,contours,-1/*绘制所有轮廓*/,cv::Scalar(255)/*绘制为白色*/,CV_FILLED/*轮廓全部填充*/);

    cv::Mat dst;

    //对图像进行模糊处理
    cv::blur(currentframe,dst,cv::Size(9,9));

    //对目标部分做锐化处理
    cv::Mat horse;
    currentframe.copyTo(horse);
    cv::Mat kernel = (cv::Mat_<float>(3,3) << 0,-1,0,-1,5,-1,0,-1,0);
    cv::filter2D(horse,horse,currentframe.depth(),kernel);

    //合成画面，把锐化后的目标部分复制到dst对应的位置
    horse.copyTo(dst,mask);
#else
    //--2.转换灰度图
    cv::Mat gray;
    cv::cvtColor(currentframe,gray,CV_RGB2GRAY);

    //--3.二值化灰度图
    cv::Mat binary;
    cv::threshold(gray,binary,60,255,cv::THRESH_BINARY_INV);
    //平滑处理(平滑/高斯平滑两种)
    //cv::blur(dst,dst,cv::Size(3,3));
    //cv::GaussianBlur(dst,dst,cv::Size(3,3),0,0); //高斯平滑

    //形态学操作（此处效果不好，只用来展示加强理解）
    //cv::erode(dst,dst,cv::Mat(),cv::Point(-1,-1),1);
    //cv::dilate(dst,dst,cv::Mat(),cv::Point(-1,-1),1);


    //--4.寻找轮廓
    std::vector<std::vector<cv::Point> > contours;
    cv::Mat binary_copy; //因为findcontours函数会改变输入的图像，所以复制一个图像作为函数的输入
    binary.copyTo(binary_copy);
    cv::findContours(binary_copy,contours,CV_RETR_EXTERNAL/*获取外轮廓*/,CV_CHAIN_APPROX_NONE/*获取每个轮廓的每个像素*/);

    //遍历每一个轮廓，把多余的轮廓去掉
    std::vector<std::vector<cv::Point> >::const_iterator it=contours.begin();
    while(it!=contours.end()){
        if(it->size()<500)
            it = contours.erase(it);
        else
            ++it;
    }

    //重新绘制轮廓
    cv::Mat dst(currentframe.size(),CV_8U,cv::Scalar(0));
    cv::drawContours(dst,contours,-1/*绘制所有轮廓*/,cv::Scalar(255)/*绘制为白色*/,CV_FILLED/*轮廓全部填充*/);
#endif
    return dst;
}
