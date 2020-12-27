#ifndef VIDEOPROCESS_H
#define VIDEOPROCESS_H

#include <VideoInterface.h>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <VideoInterface.h>

class VideoProcess : public VideoInterface
{

public:
    static VideoProcess* GetInstance()
    {
        static VideoProcess vp;
        return &vp;
    }

    bool openVC(char *, int);
    bool closeVC();
    bool getFrame(cv::Mat &);

    void setCurrentFrame(int);
    int getFrameTotal();
    int getFrameRate();

private:
    VideoProcess();

    cv::VideoCapture capture;

};

#endif // VIDEOPROCESS_H
