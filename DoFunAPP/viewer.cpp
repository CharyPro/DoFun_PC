#include "viewer.h"
#include <QDebug>

Viewer::Viewer()
{
    setColor();
}

void Viewer::drawPixmap()
{
    this->setPixmap(imgpix);
}

void Viewer::reset()
{
    this->clear();
}

void Viewer::setColor()
{
    this->setStyleSheet("QLabel{background:#000000;}");
}

void Viewer::setPix(const QImage f)
{
    this->imgpix = QPixmap::fromImage(f);
}

void Viewer::setSize(QSize size)
{
    this->resize(size);
}

void Viewer::setStub(FrameprocessInterface *st)
{
    // 1.set stub
    if(st == NULL)
        return;
    DISPLAY_MODE = PROCESSMODEL;
    stub = st;
}


void Viewer::displayFrame(QImage data)
{
    if(DISPLAY_MODE == PROCESSMODEL)
        stub->processFrame(data);
    setPix(data);
    drawPixmap();
}


