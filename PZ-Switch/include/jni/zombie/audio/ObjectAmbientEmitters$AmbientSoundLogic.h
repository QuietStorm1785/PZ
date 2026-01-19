#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameSounds.h"
#include "zombie/audio/ObjectAmbientEmitters/PerObjectLogic.h"
#include "zombie/audio/ObjectAmbientEmitters/PowerPolicy.h"
#include "zombie/core/properties/PropertyContainer.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"

namespace zombie {
namespace audio {


class ObjectAmbientEmitters {
:
    PowerPolicy powerPolicy = PowerPolicy.NotRequired;
    bool bHasGeneratorParameter = false;

    PerObjectLogic init(IsoObject var1) {
      super.init(var1);
    std::string var2 = this.getSoundName();
      this.powerPolicy = ObjectAmbientEmitters.getInstance().powerPolicyMap.getOrDefault(var2, PowerPolicy.NotRequired);
      if (this.powerPolicy != PowerPolicy.NotRequired) {
    GameSound var3 = GameSounds.getSound(var2);
         this.bHasGeneratorParameter = var3 != nullptr && var3.numClipsUsingParameter("Generator") > 0;
      }

    return this;
   }

    bool shouldPlaySound() {
      if (this.powerPolicy == PowerPolicy.InteriorHydro) {
    bool var1 = this.object.square.haveElectricity() || IsoWorld.instance.isHydroPowerOn() && this.object.square.getRoom() != nullptr;
         if (!var1) {
    return false;
         }
      }

      if (this.powerPolicy == PowerPolicy.ExteriorOK) {
    bool var2 = this.object.square.haveElectricity() || IsoWorld.instance.isHydroPowerOn();
         if (!var2) {
    return false;
         }
      }

      if (this.powerPolicy != PowerPolicy.NotRequired && !IsoWorld.instance.isHydroPowerOn() && !this.bHasGeneratorParameter) {
    return false;
      } else {
    PropertyContainer var3 = this.object.getProperties();
         return var3 != nullptr && var3.Is("AmbientSound");
      }
   }

    std::string getSoundName() const {
      return this.object.getProperties().Val("AmbientSound");
   }

    void startPlaying(BaseSoundEmitter var1, long var2) {
   }

    void stopPlaying(BaseSoundEmitter var1, long var2) {
      this.parameterValue1 = Float.NaN;
   }

    void checkParameters(BaseSoundEmitter var1, long var2) {
      if (this.powerPolicy != PowerPolicy.NotRequired) {
         this.setParameterValue1(var1, var2, "Generator", IsoWorld.instance.isHydroPowerOn() ? 0.0F : 1.0F);
      }
   }
}
} // namespace audio
} // namespace zombie
