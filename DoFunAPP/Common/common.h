#ifndef COMMON_H
#define COMMON_H

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <QImage>

namespace Utils {

extern cv::Mat QImageToMat(QImage image);

extern QImage MatToQImage(const cv::Mat& mat);

}
#endif // COMMON_H
