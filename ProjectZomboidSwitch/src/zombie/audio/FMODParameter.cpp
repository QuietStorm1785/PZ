#include <string>
#include "zombie/audio/FMODParameter.h"

namespace zombie {
namespace audio {

FMODParameter::FMODParameter(const std::string& name)
    : m_name(name),
      m_parameterDescription(FMODManager::instance().getParameterDescription(name) ? *FMODManager::instance().getParameterDescription(name) : FMOD_STUDIO_PARAMETER_DESCRIPTION{}),
      m_currentValue(std::numeric_limits<float>::quiet_NaN())
{}

std::string FMODParameter::getName() {
    return m_name;
}

FMOD_STUDIO_PARAMETER_DESCRIPTION FMODParameter::getParameterDescription() {
    return m_parameterDescription;
}

FMOD_STUDIO_PARAMETER_ID FMODParameter::getParameterID() {
    // Return the parameter ID from the parameter description
    return m_parameterDescription.id;
}

float FMODParameter::getCurrentValue() {
    // Return the current value of the parameter
    return m_currentValue;
}

void FMODParameter::update() {
    // Update the current value from FMODManager
    float value = FMODManager::instance().getParameterValue(m_name);
    m_currentValue = value;
}

void FMODParameter::resetToDefault() {
    // Reset the parameter to its default value using FMODManager
    float defaultValue = m_parameterDescription.defaultvalue;
    FMODManager::instance().setParameterValue(m_name, defaultValue);
    m_currentValue = defaultValue;
}

} // namespace audio
} // namespace zombie
