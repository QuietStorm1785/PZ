#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/ObjectAmbientEmitters/PerObjectLogic.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/iso/IsoWorld.h"

namespace zombie {
namespace audio {


class ObjectAmbientEmitters {
:
    bool shouldPlaySound() {
    ItemContainer var1 = this.object.getContainerByEitherType("fridge", "freezer");
      return var1 != nullptr && var1.isPowered();
   }

    std::string getSoundName() const {
      return "FridgeHum";
   }

    void startPlaying(BaseSoundEmitter var1, long var2) {
   }

    void stopPlaying(BaseSoundEmitter var1, long var2) {
      this.parameterValue1 = Float.NaN;
   }

    void checkParameters(BaseSoundEmitter var1, long var2) {
      this.setParameterValue1(var1, var2, "Generator", IsoWorld.instance.isHydroPowerOn() ? 0.0F : 1.0F);
   }
}
} // namespace audio
} // namespace zombie
