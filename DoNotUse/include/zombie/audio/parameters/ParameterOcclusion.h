#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/fmod/FMODSoundEmitter.h"
#include "zombie/audio/FMODLocalParameter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoWorld.h"

namespace zombie {
namespace audio {
namespace parameters {


class ParameterOcclusion : public FMODLocalParameter {
public:
    const FMODSoundEmitter emitter;
    float currentValue = float.NaN;

    public ParameterOcclusion(FMODSoundEmitter var1) {
      super("Occlusion");
      this.emitter = var1;
   }

    float calculateCurrentValue() {
    float var1 = 1.0F;

      for (int var2 = 0; var2 < 4; var2++) {
    float var3 = this.calculateValueForPlayer(var2);
         var1 = PZMath.min(var1, var3);
      }

      this.currentValue = var1;
      return (int)(this.currentValue * 1000.0F) / 1000.0F;
   }

    void resetToDefault() {
      this.currentValue = float.NaN;
   }

    float calculateValueForPlayer(int var1) {
    IsoPlayer var2 = IsoPlayer.players[var1];
      if (var2 == nullptr) {
         return 1.0F;
      } else {
    IsoGridSquare var3 = var2.getCurrentSquare();
    IsoGridSquare var4 = IsoWorld.instance.getCell().getGridSquare(this.emitter.x, this.emitter.y, this.emitter.z);
         if (var4 == nullptr) {
    bool var5 = true;
         }

    float var6 = 0.0F;
         if (var3 != nullptr && var4 != nullptr && !var4.isCouldSee(var1)) {
            var6 = 1.0F;
         }

    return var6;
      }
   }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
