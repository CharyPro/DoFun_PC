#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/opencv.hpp>
#include "videoprocess.h"
#include <QPushButton>
#include <QSlider>
#include "viewer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow;}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void action_picture_clicked(bool checked);
    void action_video_clicked(bool checked);
    void action_camera_clicked(bool checked);

    void exampleprocess();
    void normaldisplay();
    void trackProcessFunc(int);

    void playVideo();

protected:
    void closeEvent(QCloseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    Ui::MainWindow *ui;

    QSize frameSize;
    bool isResize;
    bool isVisable;
    bool shouldStop;
    bool statusPlay;
    cv::Mat frame;

    Viewer* view;

    QTimer timer;
    QTimer *timervideo;

    struct framestruct {
        double totalFrame;     //视频总帧数
        double currentFrame;    //当前播放帧
        double frameRate;  //视频帧率
        double controlRate;
        double pauseTime;
        int trackbarValue;    //trackbar控制量
        int trackbarMax;   //trackbar控制条最大值
    } _frame;

    struct CtrlVideo {
        QPushButton *playbtn;
        QPushButton *replaybtn;
        QPushButton *stopbtn;
        QSlider *slider;
    }ctrlvideo;

    enum DISPLAYMODE {
        PHOTO_MODE,
        VIDEO_MODE,
        CAMERA_MODEL
    }DISPLAYTYPE;

    void initValue();
    void setWindowSize(cv::Mat tempframe);
    void setStatusBar();
    void updateFrame();
    QImage updateViewr(cv::Mat f);
    void initWidget();
    void clearStatus();

    // Ctrl
    void playandstopVideo();
    void replayVideo();
    void stopVideo();

    VideoProcess *videoprocess;



};
#endif // MAINWINDOW_H
