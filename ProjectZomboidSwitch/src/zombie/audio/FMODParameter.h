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
      std::string m_name;
      FMOD_STUDIO_PARAMETER_DESCRIPTION m_parameterDescription;
      float m_currentValue = std::numeric_limits<float>::quiet_NaN();

      FMODParameter(const std::string& name)
            : m_name(name), m_parameterDescription(FMODManager::instance().getParameterDescription(name) ? *FMODManager::instance().getParameterDescription(name) : FMOD_STUDIO_PARAMETER_DESCRIPTION{}) {}

      virtual ~FMODParameter() = default;

      std::string getName() const { return m_name; }
      const FMOD_STUDIO_PARAMETER_DESCRIPTION* getParameterDescription() const { return &m_parameterDescription; }
      FMOD_STUDIO_PARAMETER_ID getParameterID() const { return m_parameterDescription.id; }
      float getCurrentValue() const { return m_currentValue; }

      void update() {
            float val = calculateCurrentValue();
            if (val != m_currentValue) {
                  m_currentValue = val;
                  setCurrentValue(m_currentValue);
            }
      }

      virtual void resetToDefault() {}

      virtual float calculateCurrentValue() const = 0;
      virtual void setCurrentValue(float value) = 0;
      virtual void startEventInstance(int64_t id) = 0;
      virtual void stopEventInstance(int64_t id) = 0;
}
} // namespace audio
} // namespace zombie
