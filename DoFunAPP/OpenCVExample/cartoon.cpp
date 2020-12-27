#include "cartoon.h"
#include <Common/common.h>
#include <iostream>

using namespace cv;

Cartoon::Cartoon()
{

}

void Cartoon::cartoonImage(Mat src, Mat& dist)
{
    Mat gray;
    cvtColor(src, gray, CV_BGR2GRAY);
    const int MEDIAN_BLUR_FILTER_SIZE = 7;
    medianBlur(gray, gray, MEDIAN_BLUR_FILTER_SIZE);//滤波

    Mat edges;
    const int  LAPLACIAN_FILTER_SIZE = 5;
    Laplacian(gray, edges, CV_8U, LAPLACIAN_FILTER_SIZE);//边缘

    Mat mask;
    const int EDGES_THRESHOLD = 80;
    threshold(edges, mask, EDGES_THRESHOLD, 255, THRESH_BINARY_INV);

    Size size = src.size();
    Size smallSize;
    smallSize.width = size.width/2;
    smallSize.height = size.height/2;
    Mat smallImg = Mat(smallSize, CV_8UC3);
    resize(src, smallImg, smallSize, 0,0, INTER_LINEAR);

    Mat tmp = Mat(smallSize, CV_8UC3);
    int repetitions = 7; // Repetitions for strong cartoon effect.
    for (int i=0; i<repetitions; i++) {
        int ksize = 9; // Filter size. Has a large effect on speed.
        double sigmaColor = 9; // Filter color strength.
        double sigmaSpace = 7; // Spatial strength. Affects speed.
        bilateralFilter(smallImg, tmp, ksize, sigmaColor, sigmaSpace);
        bilateralFilter(tmp, smallImg, ksize, sigmaColor, sigmaSpace);
    }

    Mat bigImg;
    resize(smallImg, bigImg, size, 0,0, INTER_LINEAR);
    dist.setTo(0);
    bigImg.copyTo(dist, mask);
}

void Cartoon::processFrame(QImage &imgdata)
{
    QImage img = imgdata.copy();

    Mat src = Utils::QImageToMat(img);
    Mat dst;

    cartoonImage(src, dst);

    imgdata = Utils::MatToQImage(dst);
//    std::cout << __FUNCTION__ << "dst:" << imgdata->width << " "  << imgdata->channels << std::endl;

}
