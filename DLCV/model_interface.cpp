#include "model_interface.h"

namespace modelmanager {

std::vector<model_entry> *modelVec = new std::vector<model_entry>();

void register_model(const model_entry entry)
{
    modelVec->push_back(entry);
}

}
