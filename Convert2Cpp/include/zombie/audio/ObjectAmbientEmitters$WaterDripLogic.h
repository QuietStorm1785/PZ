#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/ObjectAmbientEmitters/PerObjectLogic.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"

namespace zombie {
namespace audio {


class ObjectAmbientEmitters {
public:
    bool shouldPlaySound() {
      return this.object.sprite != nullptr && this.object.sprite.getProperties().Is(IsoFlagType.waterPiped) && this.object.getWaterAmount() > 0.0F;
   }

    std::string getSoundName() {
      return "WaterDrip";
   }

    void startPlaying(BaseSoundEmitter var1, long var2) {
      if (this.object.sprite != nullptr && this.object.sprite.getProperties().Is("SinkType")) {
    std::string var4 = this.object.sprite.getProperties().Val("SinkType");

         byte var5 = switch (var4) {
            case "Ceramic" -> 1;
            case "Metal" -> 2;
            default -> 0;
         };
         this.setParameterValue1(var1, var2, "SinkType", var5);
      }
   }

    void stopPlaying(BaseSoundEmitter var1, long var2) {
      this.parameterValue1 = Float.NaN;
   }

    void checkParameters(BaseSoundEmitter var1, long var2) {
   }
}
} // namespace audio
} // namespace zombie
