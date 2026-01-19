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


class FMODLocalParameter :  FMODParameter {
:
    const TLongArrayList m_instances = new TLongArrayList();

     FMODLocalParameter(const std::string& var1) {
      super(var1);
      if (this.getParameterDescription() != nullptr && this.getParameterDescription().isGlobal()) {
    bool var2 = true;
      }
   }

    float calculateCurrentValue() {
      return 0.0F;
   }

    void setCurrentValue(float var1) {
      for (int var2 = 0; var2 < this.m_instances.size(); var2++) {
    long var3 = this.m_instances.get(var2);
         javafmod.FMOD_Studio_EventInstance_SetParameterByID(var3, this.getParameterID(), var1, false);
      }
   }

    void startEventInstance(long var1) {
      this.m_instances.add(var1);
      javafmod.FMOD_Studio_EventInstance_SetParameterByID(var1, this.getParameterID(), this.getCurrentValue(), false);
   }

    void stopEventInstance(long var1) {
      this.m_instances.remove(var1);
   }
}
} // namespace audio
} // namespace zombie
