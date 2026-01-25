#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/javafmod.h"

namespace zombie {
namespace audio {


class FMODGlobalParameter : public FMODParameter {
public:
  FMODGlobalParameter(const std::string& name)
    : FMODParameter(name) {
    if (getParameterDescription() && !getParameterDescription()->isGlobal()) {
      // Optionally log or handle non-global parameter
    }
  }

  void setCurrentValue(float value) {
    javafmod::FMOD_Studio_System_SetParameterByID(getParameterID(), value, false);
  }

  void startEventInstance(int64_t /*id*/) {}
  void stopEventInstance(int64_t /*id*/) {}
};
} // namespace audio
} // namespace zombie
