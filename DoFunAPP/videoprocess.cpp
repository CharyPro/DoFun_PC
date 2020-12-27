#include "videoprocess.h"
#include <QDebug>



bool VideoProcess::openVC(char *name, int mode)
{
    if(mode == VIDEOMODEL)
        capture.open(name);
    else if(mode == CAMEAMODE)
        capture.open(atoi(name));

    if(!capture.isOpened())
        return false;

    if(mode == CAMEAMODE)
    {
        capture.set(CV_CAP_PROP_FRAME_WIDTH, 640);
        capture.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
    }

    return true;
}

bool VideoProcess::closeVC()
{
    if(capture.isOpened())
        capture.release();

    return true;
}

bool VideoProcess::getFrame(cv::Mat& mat)
{
    capture >> mat;
    if(mat.empty())
        return false;

    return true;
}

void VideoProcess::setCurrentFrame(int num)
{
    capture.set(CV_CAP_PROP_POS_FRAMES, num);
}

int VideoProcess::getFrameTotal()
{
    return capture.get(CV_CAP_PROP_FRAME_COUNT);
}

int VideoProcess::getFrameRate()
{
    return capture.get(CV_CAP_PROP_FPS);
}

VideoProcess::VideoProcess()
{

}
