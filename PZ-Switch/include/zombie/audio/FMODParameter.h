#pragma once
#include "fmod/fmod/FMODManager.h"
#include "fmod/fmod/FMOD_STUDIO_PARAMETER_DESCRIPTION.h"
#include "fmod/fmod/FMOD_STUDIO_PARAMETER_ID.h"
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace audio {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class FMODParameter {
public:
 const std::string m_name;
 const FMOD_STUDIO_PARAMETER_DESCRIPTION m_parameterDescription;
 float m_currentValue = Float.NaN;

public
 FMODParameter(std::string_view name) {
 this->m_name = name;
 this->m_parameterDescription =
 FMODManager.instance.getParameterDescription(name);
 }

 std::string getName() { return this->m_name; }

 FMOD_STUDIO_PARAMETER_DESCRIPTION getParameterDescription() {
 return this->m_parameterDescription;
 }

 FMOD_STUDIO_PARAMETER_ID getParameterID() {
 return this->m_parameterDescription.empty()
 ? nullptr
 : this->m_parameterDescription.id;
 }

 float getCurrentValue() { return this->m_currentValue; }

 void update() {
 float float0 = this->calculateCurrentValue();
 if (float0 != this->m_currentValue) {
 this->m_currentValue = float0;
 this->setCurrentValue(this->m_currentValue);
 }
 }

 void resetToDefault() {}

public
 float calculateCurrentValue();

public
 void setCurrentValue(float value);

public
 void startEventInstance(long eventInstance);

public
 void stopEventInstance(long eventInstance);
}
} // namespace audio
} // namespace zombie
