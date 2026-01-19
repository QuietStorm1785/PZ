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


class FMODGlobalParameter :  FMODParameter {
:
     FMODGlobalParameter(const std::string& var1) {
      super(var1);
      if (this.getParameterDescription() != nullptr && !this.getParameterDescription().isGlobal()) {
    bool var2 = true;
      }
   }

    void setCurrentValue(float var1) {
      javafmod.FMOD_Studio_System_SetParameterByID(this.getParameterID(), var1, false);
   }

    void startEventInstance(long var1) {
   }

    void stopEventInstance(long var1) {
   }
}
} // namespace audio
} // namespace zombie
