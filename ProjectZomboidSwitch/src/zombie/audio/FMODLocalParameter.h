#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/javafmod.h"
#include "gnu/trove/list/array/TLongArrayList.h"

namespace zombie {
namespace audio {


class FMODLocalParameter : public FMODParameter {
public:
  std::vector<int64_t> m_instances;

  FMODLocalParameter(const std::string& name)
    : FMODParameter(name) {
    if (getParameterDescription() && getParameterDescription()->isGlobal()) {
      // Optionally log or handle global parameter
    }
  }

  float calculateCurrentValue() const {
    return 0.0f;
  }

  void setCurrentValue(float value) {
    for (auto id : m_instances) {
      javafmod::FMOD_Studio_EventInstance_SetParameterByID(id, getParameterID(), value, false);
    }
  }

  void startEventInstance(int64_t id) {
    m_instances.push_back(id);
    javafmod::FMOD_Studio_EventInstance_SetParameterByID(id, getParameterID(), getCurrentValue(), false);
  }

  void stopEventInstance(int64_t id) {
    m_instances.erase(std::remove(m_instances.begin(), m_instances.end(), id), m_instances.end());
  }
};
} // namespace audio
} // namespace zombie
