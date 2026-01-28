#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/OpenALParameterStub.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"

namespace zombie {
namespace audio {
namespace parameters {


class ParameterInside : public OpenALParameterStub {
public:
    public ParameterInside() {
      super("Inside");
   }

    float calculateCurrentValue() {
    IsoGameCharacter var1 = this.getCharacter();
      if (var1 == nullptr) {
         return 0.0F;
      } else if (var1.getCurrentSquare() == nullptr) {
         return 0.0F;
      } else if (var1.getCurrentSquare().isInARoom()) {
         return 1.0F;
      } else {
         return var1.getVehicle() == nullptr ? 0.0F : -1.0F;
      }
   }

    IsoGameCharacter getCharacter() {
    IsoPlayer var1 = nullptr;

      for (int var2 = 0; var2 < IsoPlayer.numPlayers; var2++) {
    IsoPlayer var3 = IsoPlayer.players[var2];
         if (var3 != nullptr && (var1 == nullptr || var1.isDead() && var3.isAlive() || var1.Traits.Deaf.isSet() && !var3.Traits.Deaf.isSet())) {
            var1 = var3;
         }
      }

    return var1;
   }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
