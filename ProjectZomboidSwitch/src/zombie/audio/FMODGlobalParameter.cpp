#include <string>
#include "zombie/audio/FMODGlobalParameter.h"

namespace zombie {
namespace audio {

FMODGlobalParameter::FMODGlobalParameter(const std::string& name)
    : m_name(name), m_currentValue(0.0f) {}
}

void FMODGlobalParameter::setCurrentValue(float value) {
    m_currentValue = value;
}

void FMODGlobalParameter::startEventInstance(long /*eventId*/) {
    // Dummy implementation: does nothing
}

void FMODGlobalParameter::stopEventInstance(long /*eventId*/) {
    // Dummy implementation: does nothing
}

} // namespace audio
} // namespace zombie
