#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/ObjectAmbientEmitters/PerObjectLogic.h"

namespace zombie {
namespace audio {


class ObjectAmbientEmitters {
:
    bool shouldPlaySound() {
      return this.object.sprite != nullptr
         && this.object.sprite.getName() != nullptr
         && this.object.sprite.getName().startsWith("camping_01")
         && (this.object.sprite.tileSheetIndex == 0 || this.object.sprite.tileSheetIndex == 3);
   }

    std::string getSoundName() const {
      return "TentAmbiance";
   }

    void startPlaying(BaseSoundEmitter var1, long var2) {
   }

    void stopPlaying(BaseSoundEmitter var1, long var2) {
   }

    void checkParameters(BaseSoundEmitter var1, long var2) {
   }
}
} // namespace audio
} // namespace zombie
