#ifndef FRAMEVIEWER_H
#define FRAMEVIEWER_H

#include <QMainWindow>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QTimer>
#include "ctrlwidget.h"

namespace Ui {
class FrameViewer;
}

class FrameViewer : public QMainWindow
{
    Q_OBJECT

public:
    explicit FrameViewer(QWidget *parent = nullptr);
    ~FrameViewer();

private slots:
    void readFrame();
//    bool updateFrame();
    bool openVideo();
    void replayVideo(bool);
    void playandstopVideo(bool);

    void trackProcessFunc(int);

protected:

     void closeEvent(QCloseEvent *event);

private:
    Ui::FrameViewer *ui;
    QTimer *timer;
    cv::VideoCapture capture;
    cv::Mat frame;
    QSize frameSize;
    bool isResize;

    bool statusPlay;

    CtrlWidget *ctrlwidget;

    cv::Mat getFrame(cv::Mat&);
    void initframe();
    void initwidgets();

    struct framestruct {
        double totalFrame;     //视频总帧数
        double currentFrame;    //当前播放帧
        double frameRate;  //视频帧率
        double controlRate;
        double pauseTime;
        int trackbarValue;    //trackbar控制量
        int trackbarMax;   //trackbar控制条最大值
    } _frame;

};

#endif // FRAMEVIEWER_H
