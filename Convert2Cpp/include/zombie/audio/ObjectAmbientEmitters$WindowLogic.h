#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/ObjectAmbientEmitters/PerObjectLogic.h"
#include "zombie/iso/objects/IsoWindow.h"
#include "zombie/util/Type.h"

namespace zombie {
namespace audio {


class ObjectAmbientEmitters {
public:
    bool shouldPlaySound() {
    return true;
   }

    std::string getSoundName() {
      return "WindowAmbiance";
   }

    void startPlaying(BaseSoundEmitter var1, long var2) {
   }

    void stopPlaying(BaseSoundEmitter var1, long var2) {
      this.parameterValue1 = Float.NaN;
   }

    void checkParameters(BaseSoundEmitter var1, long var2) {
    IsoWindow var4 = static_cast<IsoWindow>(Type).tryCastTo(this.object, IsoWindow.class);
    float var5 = !var4.IsOpen() && !var4.isDestroyed() ? 0.0F : 1.0F;
      this.setParameterValue1(var1, var2, "DoorWindowOpen", var5);
   }
}
} // namespace audio
} // namespace zombie
