#ifndef DLCV_LIST_H
#define DLCV_LIST_H

#include "ncnn_yolact.h"

DEFINE_MODEL_CREATOR(yolact)

std::vector<model_registry_entry> modellist = {
    {"yolact", MODEL_NAME(yolact)}
};


#endif // DLCV_LIST_H
