#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/fmod/FMODManager.h"
#include "fmod/fmod/FMOD_STUDIO_PARAMETER_DESCRIPTION.h"
#include "fmod/fmod/FMOD_STUDIO_PARAMETER_ID.h"

namespace zombie {
namespace audio {


class FMODParameter {
:
    const std::string m_name;
    const FMOD_STUDIO_PARAMETER_DESCRIPTION m_parameterDescription;
    float m_currentValue = Float.NaN;

     FMODParameter(std::string_view var1) {
      this.m_name = var1;
      this.m_parameterDescription = FMODManager.instance.getParameterDescription(var1);
   }

    std::string getName() const {
      return this.m_name;
   }

    FMOD_STUDIO_PARAMETER_DESCRIPTION getParameterDescription() const {
      return this.m_parameterDescription;
   }

    FMOD_STUDIO_PARAMETER_ID getParameterID() const {
      return this.m_parameterDescription == nullptr ? nullptr : this.m_parameterDescription.id;
   }

    float getCurrentValue() const {
      return this.m_currentValue;
   }

    void update() {
    float var1 = this.calculateCurrentValue();
      if (var1 != this.m_currentValue) {
         this.m_currentValue = var1;
         this.setCurrentValue(this.m_currentValue);
      }
   }

    void resetToDefault() {
   }

    abstract float calculateCurrentValue();

    abstract void setCurrentValue(float var1);

    abstract void startEventInstance(long var1);

    abstract void stopEventInstance(long var1);
}
} // namespace audio
} // namespace zombie
