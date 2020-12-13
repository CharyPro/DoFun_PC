#ifndef CTRLWIDGET_H
#define CTRLWIDGET_H

#include <QWidget>

typedef struct FrameValue {
    int value;
}frameValue_t;


class CtrlWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CtrlWidget(QWidget *parent = nullptr);


    frameValue_t currentValue;

signals:
//    void updateframe(struct value);

private slots:
    void setNewValue(int);

private:
};

#endif // CTRLWIDGET_H
