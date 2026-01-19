#pragma once
#include <string>
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
public:
    const std::string m_name;
    const FMOD_STUDIO_PARAMETER_DESCRIPTION m_parameterDescription;
    float m_currentValue = Float.NaN;

    public FMODParameter(const std::string& var1) {
      this.m_name = var1;
      this.m_parameterDescription = FMODManager.instance.getParameterDescription(var1);
   }

    std::string getName() {
      return this.m_name;
   }

    FMOD_STUDIO_PARAMETER_DESCRIPTION getParameterDescription() {
      return this.m_parameterDescription;
   }

    FMOD_STUDIO_PARAMETER_ID getParameterID() {
      return this.m_parameterDescription == nullptr ? nullptr : this.m_parameterDescription.id;
   }

    float getCurrentValue() {
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

   public abstract float calculateCurrentValue();

   public abstract void setCurrentValue(float var1);

   public abstract void startEventInstance(long var1);

   public abstract void stopEventInstance(long var1);
}
} // namespace audio
} // namespace zombie
