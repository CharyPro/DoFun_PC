#ifndef VIEWER_H
#define VIEWER_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <opencv2/imgcodecs.hpp>
#include "ViewerInterface.h"
#include "FrameprocessInterface.h"


class Viewer : public QLabel , public ViewerInterface
{
public:
    Viewer();

    virtual void drawPixmap();
    void reset();
    void setColor();
    void displayFrame(QImage);
    void setPix(const QImage);
    void setSize(QSize size);
    void setStub(FrameprocessInterface*);


    enum TYPE_DISPLAY {
        NORMALMODEL,
        PROCESSMODEL
    }DISPLAY_MODE;


private:
    QPixmap imgpix;
    QTimer *timer;

    FrameprocessInterface *stub;

};

#endif // VIEWER_H
