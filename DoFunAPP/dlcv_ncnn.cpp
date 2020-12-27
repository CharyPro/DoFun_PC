#include "dlcv_ncnn.h"
#include "Common/common.h"

DLCV_NCNN::DLCV_NCNN(DLCV_INTERFACE *ncnnmodel, QString name)
{
    modelname = name;
    model = ncnnmodel;
}

void DLCV_NCNN::processFrame(QImage &imgdata)
{
    QImage img = imgdata.copy();

    cv::Mat src = Utils::QImageToMat(img);

    if (model != Q_NULLPTR)
    {
        cv::Mat res = model->getresult(src, modelname.toStdString());
//        cv::imwrite("result.png", res);
        imgdata = Utils::MatToQImage(res);
    }
}
