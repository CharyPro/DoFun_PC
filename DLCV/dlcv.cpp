#include "dlcv.h"
#include "dlcv_list.h"

QString DLCV::name()
{
    return "";
}

cv::Mat DLCV::getresult(cv::Mat srcimage, std::string type)
{
    cv::Mat result;
//    std::cout << imagepath << " " << type << std::endl;
    MODE_INTERFACE *model;

    std::vector<model_entry>::iterator it = modellist.begin();
    for(; it != modellist.end(); it++)
    {
        if((*it).name == type)
        {
            model = (*it).creator();
        }
    }

    if(model)
        model->getresult(srcimage, result);
    return result;
}

