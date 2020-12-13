#include "ctrlwidget.h"
#include <QPushButton>
#include <QSlider>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QLabel>

CtrlWidget::CtrlWidget(QWidget *parent) : QWidget(parent)
{
    this->setFixedWidth(200);
    QVBoxLayout *vlay1 = new QVBoxLayout(this);
    QHBoxLayout *hlay1 = new QHBoxLayout(this);
    QSlider *slider1 = new QSlider();
    QSpinBox *spinBox1 = new QSpinBox();
    QLabel *label = new QLabel("value:");
    hlay1->addWidget(label);
    hlay1->addWidget(slider1);
    hlay1->addWidget(spinBox1);
    //***设置QSpinBox设置：
    slider1->setOrientation(Qt::Horizontal);
    slider1->setRange(0, 1000);  //设置范围[0,1000]
    slider1->setSingleStep(5);   //增加步长；
    slider1->setValue(100);		//设置初始值
    slider1->setTickInterval(100);  // 设置刻度间隔
    slider1->setTickPosition(QSlider::TicksAbove);  //刻度在上方

    spinBox1->setRange(0, 1000);  //设置范围[0,1000]
    spinBox1->setSingleStep(5);   //增加步长；
    spinBox1->setValue(100);		//设置初始值
//    spinBox1->setSuffix(QString::fromLocal8Bit("个")); //设置后缀


    //*** 连接信号槽（相互改变）
    connect(spinBox1, SIGNAL(valueChanged(int)), slider1, SLOT(setValue(int)));
    connect(slider1, SIGNAL(valueChanged(int)), spinBox1, SLOT(setValue(int)));
    connect(spinBox1, SIGNAL(valueChanged(int)), this, SLOT(setNewValue(int)));
    QPushButton *btn = new QPushButton(this);
    btn->setText("TEST");

    vlay1->addLayout(hlay1);
    vlay1->addWidget(btn);

    this->setLayout(vlay1);

}

void CtrlWidget::setNewValue(int value)
{
    currentValue.value = value;

//    emit updateframe(currentValue);
}
