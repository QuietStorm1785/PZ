#include <string>
#include "zombie/audio/FMODLocalParameter.h"

namespace zombie {
namespace audio {

FMODLocalParameter::FMODLocalParameter(const std::string& name)
    : m_name(name), m_currentValue(0.0f) {}
}

float FMODLocalParameter::calculateCurrentValue() {
    return m_currentValue;
}

void FMODLocalParameter::setCurrentValue(float value) {
    m_currentValue = value;
}

void FMODLocalParameter::startEventInstance(long /*eventId*/) {
    // Dummy implementation: does nothing
}

void FMODLocalParameter::stopEventInstance(long /*eventId*/) {
    // Dummy implementation: does nothing
}

} // namespace audio
} // namespace zombie
