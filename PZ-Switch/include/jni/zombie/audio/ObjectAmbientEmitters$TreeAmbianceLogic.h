#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/fmod/FMODSoundEmitter.h"
#include "zombie/audio/ObjectAmbientEmitters/PerObjectLogic.h"
#include "zombie/audio/parameters/ParameterCurrentZone.h"
#include "zombie/util/Type.h"

namespace zombie {
namespace audio {


class ObjectAmbientEmitters {
:
    bool shouldPlaySound() {
    return true;
   }

    std::string getSoundName() const {
      return "TreeAmbiance";
   }

    void startPlaying(BaseSoundEmitter var1, long var2) {
    FMODSoundEmitter var4 = (FMODSoundEmitter)Type.tryCastTo(var1, FMODSoundEmitter.class);
      if (var4 != nullptr) {
         var4.addParameter(new ParameterCurrentZone(this.object));
      }

      var1.playAmbientLoopedImpl("BirdInTree");
   }

    void stopPlaying(BaseSoundEmitter var1, long var2) {
      var1.stopOrTriggerSoundByName("BirdInTree");
   }

    void checkParameters(BaseSoundEmitter var1, long var2) {
   }
}
} // namespace audio
} // namespace zombie
