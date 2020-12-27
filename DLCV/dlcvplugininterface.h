#ifndef DLCVPLUGININTERFACE_H
#define DLCVPLUGININTERFACE_H

#include <QtPlugin>
#include <QString>
#include <opencv2/core.hpp>

class DLCV_INTERFACE
{
public:
    virtual ~DLCV_INTERFACE() {}
    virtual QString name() = 0;  // 人有名字
    virtual cv::Mat getresult(cv::Mat, std::string) = 0;

};

#define DLCV_iid "org.qt-project.Qt.Examples.DLCV_INTERFACE"

Q_DECLARE_INTERFACE(DLCV_INTERFACE, DLCV_iid)

#endif // DLCVPLUGININTERFACE_H
