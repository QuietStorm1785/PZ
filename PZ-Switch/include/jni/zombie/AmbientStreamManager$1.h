#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/fmod/FMOD_STUDIO_EVENT_CALLBACK.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/iso/IsoWorld.h"

namespace zombie {


class AmbientStreamManager {
:
   AmbientStreamManager$1(AmbientStreamManager var1) {
      this.this$0 = var1;
   }

    void timelineMarker(long var1, const std::string& var3, int var4) {
      DebugLog.Sound.debugln("timelineMarker %s %d", var3, var4);
      if ("ElectricityOff" == var3)) {
         IsoWorld.instance.setHydroPowerOn(false);
         this.this$0.checkHaveElectricity();
      }
   }
}
} // namespace zombie
