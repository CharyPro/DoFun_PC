#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <opencv2/opencv.hpp>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    view = 0;

    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    if(view)   delete view;
    delete ui;
}

void MainWindow::on_pushButton_clicked(bool checked)
{
    qDebug() << "clicked";
    if(view)
        delete view;

    view = new FrameViewer();
    view->show();
}
