#ifndef DLCV_H
#define DLCV_H

#include "dlcvplugininterface.h"
#include "dlcv_global.h"

class DLCV_PLUGINSHARED_EXPORT DLCV : public QObject, DLCV_INTERFACE
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID DLCV_iid FILE "dlcv.json")
    Q_INTERFACES(DLCV_INTERFACE)

public:
//    DLCV();

    virtual QString name() Q_DECL_OVERRIDE;
    virtual cv::Mat getresult(cv::Mat srcimage, std::string type) Q_DECL_OVERRIDE;
};

#endif // DLCV_H
