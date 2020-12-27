#ifndef MODEL_INTERFACE_H
#define MODEL_INTERFACE_H
#include <opencv2/core.hpp>
#include <iostream>

class MODE_INTERFACE {
public:
    virtual bool getresult(cv::Mat, cv::Mat& resultimg) = 0;
};


// layer factory function
typedef MODE_INTERFACE* (*model_creator_func)();

typedef struct model_registry_entry
{
    const char* name;
    model_creator_func creator;
}model_entry;

#define DEFINE_MODEL_CREATOR(name) \
    MODE_INTERFACE *name##_ncnn_creator() \
    {                                     \
        return new ncnn_##name;                  \
    }

#define MODEL_NAME(name)  name##_ncnn_creator
//#define MODE_STRING(x) #x



#endif // MODEL_INTERFACE_H
