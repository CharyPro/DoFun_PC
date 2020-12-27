#ifndef VIEWER_INTERFACE_H
#define VIEWER_INTERFACE_H

class ViewerInterface {

public:

    virtual void drawPixmap() = 0;

    virtual void reset() = 0;

    virtual void setColor() = 0;

protected:
//    virtual void rendFrame() = 0;

};

#endif // VIEWER_INTERFACE_H
