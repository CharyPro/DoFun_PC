#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QDesktopWidget>
#include <QPushButton>
#include <QSlider>

#include <QCloseEvent>
#include "OpenCVExample/cartoon.h"
#include "Common/common.h"

using namespace std::chrono;
using namespace cv;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    this->setMouseTracking(true);


    ui->setupUi(this);

    initValue();
    initWidget();
}

MainWindow::~MainWindow()
{
    if(view)   delete view;
    delete ui;
}

void MainWindow::initValue()
{
    videoprocess = 0;
    view = 0;
    isVisable = false;
    shouldStop = false;
    statusPlay = false;


    _frame.totalFrame=1.0;     //视频总帧数
    _frame.currentFrame=1.0;    //当前播放帧
    _frame.trackbarValue=1;    //trackbar控制量
    _frame.trackbarMax=255;   //trackbar控制条最大值
    _frame.frameRate=1.0;
    _frame.controlRate=1;
    _frame.pauseTime = 30;


    timervideo = new QTimer(this);
    connect(timervideo,SIGNAL(timeout()),this,SLOT(playVideo()));

}

void MainWindow::initWidget()
{
    view = new Viewer();
    this->setCentralWidget(view);
    this->centralWidget()->setMouseTracking(true);

    setStatusBar();

    connect(ui->actionOpen_A_Picture, &QAction::triggered, this, &MainWindow::action_picture_clicked);
    connect(ui->actionOpen_A_Video, &QAction::triggered, this, &MainWindow::action_video_clicked);
    connect(ui->actionOpenCamera, &QAction::triggered, this, &MainWindow::action_camera_clicked);

    connect(ui->actionexample, &QAction::triggered, this,&MainWindow::exampleprocess);
    connect(ui->actionnormal, &QAction::triggered, this,&MainWindow::normaldisplay);
}

void MainWindow::clearStatus()
{
    view->clear();

    if(timer.isActive())
        timer.stop();

    if(timervideo->isActive())
        timervideo->stop();

    view->DISPLAY_MODE = Viewer::NORMALMODEL;//正常显示

}

void MainWindow::setStatusBar()
{

    ctrlvideo.playbtn = new QPushButton("Play/Stop");
    ctrlvideo.replaybtn = new QPushButton("Replay");
//    ctrlvideo.stopbtn = new QPushButton("Stop");
    ctrlvideo.slider = new QSlider();
    ctrlvideo.slider->setOrientation(Qt::Horizontal);

    ctrlvideo.slider->setSingleStep(1);   //增加步长；
    ctrlvideo.slider->setValue(1);		//设置初始值

    ui->statusbar->addWidget(ctrlvideo.playbtn);
    ui->statusbar->addWidget(ctrlvideo.replaybtn);
//    ui->statusbar->addWidget(ctrlvideo.stopbtn);
    ui->statusbar->addWidget(ctrlvideo.slider);
    ui->statusbar->setVisible(false);

    connect(ctrlvideo.slider, SIGNAL(valueChanged(int)), this, SLOT(trackProcessFunc(int)));
    connect(ctrlvideo.playbtn, &QPushButton::clicked, this, &MainWindow::playandstopVideo);
    connect(ctrlvideo.replaybtn, &QPushButton::clicked, this, &MainWindow::replayVideo);
//    connect(ctrlvideo.stopbtn, &QPushButton::clicked, this, &MainWindow::stopVideo);


    connect(&timer, &QTimer::timeout, [this](){
        timer.stop();
        if(!ui->statusbar->geometry().contains(this->mapFromGlobal(QCursor::pos())))
            ui->statusbar->setVisible(false);
    });


}
void MainWindow::action_picture_clicked(bool checked)
{
    qDebug() << "clicked";
    DISPLAYTYPE = PHOTO_MODE;
    clearStatus();

    QString file_name = QFileDialog::getOpenFileName(this, tr("Open a Picture"), ".", tr("Photo File(*.jpg *.png)"));
    if(file_name.isEmpty())
        return;

    frame = imread(file_name.toStdString());
    setWindowSize(frame);
    updateFrame();
}



void MainWindow::action_video_clicked(bool checked)
{
    DISPLAYTYPE = VIDEO_MODE;
    clearStatus();

    QString file_name = QFileDialog::getOpenFileName(this, tr("Open Video"), ".", tr("Video File(*.avi *.mp4)"));
    if(file_name.isEmpty())
        return;

    cv::Mat oneframe;
    videoprocess = VideoProcess::GetInstance();

    if(!videoprocess->openVC((char *)file_name.toStdString().c_str(), VideoInterface::VIDEOMODEL))
    {
        qDebug() << "video open fail";
        return;
    }

    if(!videoprocess->getFrame(oneframe))
    {
        qDebug() << "get frame fail";
        return;
    }


    _frame.totalFrame= videoprocess->getFrameTotal();  //获取总帧数
    _frame.frameRate= videoprocess->getFrameRate();   //获取帧率
    _frame.pauseTime= 1000/_frame.frameRate; // 由帧率计算两幅图像间隔时间
    ctrlvideo.slider->setRange(1, _frame.totalFrame);  //设置范围[0,0]

    qDebug() << "_frame.pauseTime:"<< _frame.pauseTime;
    setWindowSize(oneframe);
    view->setSize(frameSize);
    timervideo->start(_frame.pauseTime);
    ctrlvideo.playbtn->setText("stop");
}

void MainWindow::action_camera_clicked(bool checked)
{
    DISPLAYTYPE = CAMERA_MODEL;
    clearStatus();

    qDebug() << __FUNCTION__;
    videoprocess = VideoProcess::GetInstance();
    if(!videoprocess->openVC((char *)"0", VideoInterface::CAMEAMODE))
    {
        qDebug() << "video open fail";
        return;
    }

    cv::Mat oneframe;
    videoprocess = VideoProcess::GetInstance();
    if(!videoprocess->getFrame(oneframe))
    {
        qDebug() << "get frame fail";
        return;
    }

    qDebug() << "get frame success";
    setWindowSize(oneframe);
    view->setSize(frameSize);
    timervideo->start(_frame.pauseTime);

    timer.stop();

}

void MainWindow::exampleprocess()
{
    qDebug() << __FUNCTION__;
    view->DISPLAY_MODE = Viewer::PROCESSMODEL;

    FrameprocessInterface *cartoon = new Cartoon();
    view->setStub(cartoon);
}

void MainWindow::normaldisplay()
{
    view->DISPLAY_MODE = Viewer::NORMALMODEL;
}



void MainWindow::playVideo()
{

    cv::Mat frame;
    if(videoprocess->getFrame(frame))
    {
        if(!frame.empty())
        {

            if(isResize)
                cv::resize(frame, frame, Size(frameSize.width(), frameSize.height()));

            view->displayFrame(Utils::MatToQImage(frame));

            ctrlvideo.slider->setValue(_frame.controlRate);
            _frame.controlRate++;
        }
    }
}


// Ctrl Center
void MainWindow::playandstopVideo()
{
    statusPlay =  !statusPlay;
//    qDebug() << "value:" << statusPlay;
    if(statusPlay)
    {
        timervideo->stop();
        ctrlvideo.playbtn->setText("play");
    }
    else
    {
        timervideo->start(_frame.pauseTime);
        ctrlvideo.playbtn->setText("stop");
    }
    qDebug() << "value:" << _frame.controlRate << " " << _frame.totalFrame;

    if(_frame.controlRate == _frame.totalFrame)
    {
        timervideo->start(_frame.pauseTime);
        ctrlvideo.slider->setValue(1);
        ctrlvideo.playbtn->setText("stop");
    }
}

void MainWindow::replayVideo()
{
    _frame.controlRate = 1;
    videoprocess->setCurrentFrame(_frame.controlRate);	 //设置当前播放帧
    ctrlvideo.slider->setValue((_frame.controlRate));
}

void MainWindow::stopVideo()
{

}

void MainWindow::trackProcessFunc(int value)
{
    if(value+1 == _frame.totalFrame)
    {
        timervideo->stop();
        ctrlvideo.playbtn->setText("Play");
    }

    if(value == _frame.controlRate)
        return;

    _frame.controlRate = value;
//    _frame.controlRate=(double)_frame.trackbarValue/_frame.trackbarMax*_frame.totalFrame;
    videoprocess->setCurrentFrame(_frame.controlRate);
}

void MainWindow::setWindowSize(Mat tempframe)
{
    int currentScreenWidth = QApplication::desktop()->width();
    int currentScreenHeight = QApplication::desktop()->height();

    isResize = false;

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
    this->setFixedSize(QSize(frameSize.width(), frameSize.height()));

    qDebug() << "frameSize:" << frameSize;

    //居中
    this->move((currentScreenWidth - this->width())/2, (currentScreenHeight - this->height())/2);
}

void MainWindow::updateFrame()
{

        Mat newframe;

        if(!frame.empty())
        {
//            cvtColor(frame, newframe, CV_BGR2RGB);     //  OpenCV中Mat读入的图像是BGR格式，要转换为RGB格式

            if(isResize)
                cv::resize(frame, newframe, Size(frameSize.width(), frameSize.height()));

            qDebug() << __FUNCTION__;
            view->displayFrame(Utils::MatToQImage(newframe));
        }     
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    qDebug() << "closeEvent";

    if(videoprocess)
        videoprocess->closeVC();

    if(timer.isActive())
        timer.stop();

    if(timervideo->isActive())
        timervideo->stop();

    event->accept();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(!(DISPLAYTYPE == VIDEO_MODE))
        return;

    if(ui->statusbar->geometry().contains(this->mapFromGlobal(QCursor::pos())))
        return;
//    qDebug() << QString("%1:   (%2, %3)").arg("current pos").arg(event->pos().x()).arg(event->pos().y());

    if(timer.isActive())
        timer.stop();

    if(!ui->statusbar->isVisible())
        ui->statusbar->setVisible(true);

    timer.start(1000);
}

