#include "zombie/audio/FMODParameterList.h"

namespace zombie {
namespace audio {

void FMODParameterList::add(const std::shared_ptr<FMODParameter>& param) {
    parameterList.push_back(param);
    if (param && param->getParameterDescription()) {
        size_t idx = param->getParameterDescription()->globalIndex;
        if (idx < parameterArray.size()) {
            parameterArray[idx] = param;
        }
    }
}

std::shared_ptr<FMODParameter> FMODParameterList::get(const FMOD_STUDIO_PARAMETER_DESCRIPTION* desc) {
    if (!desc) return nullptr;
    size_t idx = desc->globalIndex;
    if (idx < parameterArray.size()) {
        return parameterArray[idx];
    }
    return nullptr;
}

void FMODParameterList::update() {
    for (auto& param : parameterList) {
        if (param) param->update();
    }
}

} // namespace audio
} // namespace zombie
