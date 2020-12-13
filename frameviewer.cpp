#include "frameviewer.h"
#include "ui_frameviewer.h"
#include <QFileDialog>
#include <QDebug>
#include <QDesktopWidget>
#include <iostream>
#include <chrono>
#include <QCloseEvent>
#include <QDockWidget>


using namespace std::chrono;
using namespace cv;

FrameViewer::FrameViewer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FrameViewer)
{
    ui->setupUi(this);
    this->setWindowModality(Qt::ApplicationModal);

//    ui->ctrlwidget->setFixedWidth(200);
    ui->viewlabel->setStyleSheet("QLabel{background:#000000;}");



    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(readFrame()));

    initwidgets();
    initframe();
}

FrameViewer::~FrameViewer()
{
    delete ui;
}

void FrameViewer::initframe()
{
    _frame.totalFrame=1.0;     //视频总帧数
    _frame.currentFrame=1.0;    //当前播放帧
    _frame.trackbarValue=1;    //trackbar控制量
    _frame.trackbarMax=255;   //trackbar控制条最大值
    _frame.frameRate=1.0;
    _frame.controlRate=1;
    _frame.pauseTime = 30;

}

void FrameViewer::initwidgets()
{
    ui->processslider->setOrientation(Qt::Horizontal);
    ui->processslider->setRange(1, 1);  //设置范围[0,1000]
    ui->processslider->setSingleStep(1);   //增加步长；
    ui->processslider->setValue(1);		//设置初始值

    ctrlwidget = new CtrlWidget();
    QDockWidget *ctrldock = new QDockWidget("CtrlWidget", this);
    ctrldock->setWidget(ctrlwidget);
    ctrldock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    addDockWidget(Qt::RightDockWidgetArea, ctrldock);

    connect(ui->openbtn, &QPushButton::clicked, this, &FrameViewer::openVideo);
//    connect(ui->ctrlwidget, &CtrlWidget::updateframe, this, &FrameViewer::updateFrame);
    connect(ui->processslider, SIGNAL(valueChanged(int)), this, SLOT(trackProcessFunc(int)));

    connect(ui->replaybtn, &QPushButton::clicked, this, &FrameViewer::replayVideo);
    connect(ui->psbtn, &QPushButton::clicked, this, &FrameViewer::playandstopVideo);


    ui->psbtn->setText("play/stop");
}

bool FrameViewer::openVideo()
{
    QString file_name = QFileDialog::getOpenFileName(this, tr("Open Video"), ".", tr("Video File(*.avi *.mp4)"));
    capture.open(file_name.toStdString());
    if(!capture.isOpened())
        return false;

    qDebug() << "Open Success";

    _frame.totalFrame=capture.get(CV_CAP_PROP_FRAME_COUNT);  //获取总帧数
    _frame.frameRate=capture.get(CV_CAP_PROP_FPS);   //获取帧率
    _frame.pauseTime= 1000/_frame.frameRate; // 由帧率计算两幅图像间隔时间
    qDebug() << "_frame.pauseTime:" << _frame.pauseTime;
    ui->processslider->setRange(1, _frame.totalFrame);

    //get first frame ,set size
    int currentScreenWidth = QApplication::desktop()->width();
    int currentScreenHeight = QApplication::desktop()->height();
    qDebug() << "currentScreenWidth:" << currentScreenWidth << " " << currentScreenHeight;
    Mat tempframe;
    capture >> tempframe;
    isResize = false;
    if(!tempframe.empty())
    {
        frameSize.setWidth(tempframe.cols);
        frameSize.setHeight(tempframe.rows);
        if(tempframe.cols > currentScreenWidth/10 * 8)
        {
            frameSize.setWidth(currentScreenWidth/10 * 8);
            isResize = true;
        }
        if(tempframe.rows > currentScreenHeight/10 * 8)
        {
            frameSize.setHeight(currentScreenHeight/10 * 8);
            isResize = true;
        }
        qDebug() << "frameSize:" << frameSize;
        ui->viewlabel->resize(frameSize);    //  将label控件resize到farme的尺寸
        this->setFixedSize(QSize(frameSize.width() + ctrlwidget->width(), frameSize.height() + ui->btnwidget->height()));
//        qDebug() << "frameSize:" << ui->ctrlwidget->width() << " " <<ui->btnwidget->height();

        this->move((currentScreenWidth - this->width())/2, (currentScreenHeight - this->height())/2);
    }


    timer->start(_frame.pauseTime);
    statusPlay = true;
    ui->psbtn->setText("stop");
}

void FrameViewer::replayVideo(bool)
{
    _frame.controlRate = 1;
    capture.set(CV_CAP_PROP_POS_FRAMES,_frame.controlRate);	 //设置当前播放帧
    ui->processslider->setValue((_frame.controlRate));
}

void FrameViewer::playandstopVideo(bool)
{
    statusPlay =  !statusPlay;
    qDebug() << "value:" << statusPlay;
    if(!statusPlay)
    {
        timer->stop();
        ui->psbtn->setText("play");
    }
    else
    {
        timer->start(_frame.pauseTime);
        ui->psbtn->setText("stop");
    }
    qDebug() << "value:" << _frame.controlRate << " " << _frame.totalFrame;

    if(_frame.controlRate == _frame.totalFrame)
    {
        timer->start(_frame.pauseTime);
        ui->processslider->setValue(1);
        ui->psbtn->setText("stop");
    }
}

void FrameViewer::trackProcessFunc(int value)
{
    if(value+1 == _frame.totalFrame)
    {
        timer->stop();
        ui->psbtn->setText("play");
    }

    if(value == _frame.controlRate)
        return;

    _frame.controlRate = value;
//    _frame.controlRate=(double)_frame.trackbarValue/_frame.trackbarMax*_frame.totalFrame;
    capture.set(CV_CAP_PROP_POS_FRAMES,_frame.controlRate);	 //设置当前播放帧


}

void FrameViewer::closeEvent(QCloseEvent *event)
{
    qDebug() << "FrameViewer";
    if(timer->isActive())
    {
        qDebug() << "stop";
        timer->stop();
    }
    if(capture.isOpened())
        capture.release();

    event->accept();
}

Mat FrameViewer::getFrame(Mat& currentframe)
{
    Mat frame;
    frameValue_t args;


    for(int h = 0 ; h < currentframe.rows ; ++ h)
    {
        for(int w = 0 ; w < currentframe.cols ; ++ w)
        {
            Vec3b &bgr = currentframe.at<Vec3b>(h , w) ;
//            bgr.val[0] = 0 ;
            bgr.val[1] += 20;
            if( bgr.val[1] > 255)
                 bgr.val[1] = 255;
//            bgr.val[2] = 0 ;
        }
    }

    return currentframe;
}



void FrameViewer::readFrame()
{
    static std::chrono::time_point<system_clock> lasttime = system_clock::now();;
    if(capture.isOpened())
    {
        capture >> frame;
        if(!frame.empty())
        {
            cvtColor(frame, frame, CV_BGR2RGB);     //  OpenCV中Mat读入的图像是BGR格式，要转换为RGB格式
            if(isResize)
                cv::resize(frame, frame, Size(frameSize.width(), frameSize.height()));

            getFrame(frame);

            QImage image;
            if(frame.channels() == 1)
                image = QImage((const uchar*)frame.data, frame.cols, frame.rows, QImage::Format_Grayscale8);
            else if(frame.channels() == 3)
                image = QImage((const uchar*)frame.data, frame.cols, frame.rows, QImage::Format_RGB888);

            ui->viewlabel->setPixmap(QPixmap::fromImage(image));    //  将图片显示到label上

            ui->processslider->setValue(_frame.controlRate);
            _frame.controlRate++;
        }
    }
    auto currenttime = system_clock::now();
    // do something...
    auto duration = duration_cast<microseconds>(currenttime - lasttime);
    lasttime = currenttime;
    double internal = double(duration.count()) * microseconds::period::num / microseconds::period::den;
    ui->fpslabel->setText("fps:" + QString::number(1/internal));
}

//bool FrameViewer::updateFrame(struct frameValue newargs)
//{

//}
