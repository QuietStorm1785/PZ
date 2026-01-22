#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/FMODGlobalParameter.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/iso/NearestWalls.h"

namespace zombie {
namespace audio {
namespace parameters {


class ParameterClosestWallDistance : public FMODGlobalParameter {
public:
    public ParameterClosestWallDistance() {
      super("ClosestWallDistance");
   }

    float calculateCurrentValue() {
    IsoGameCharacter var1 = this.getCharacter();
    return var1 = = nullptr ? 127.0F : NearestWalls.ClosestWallDistance(var1.getCurrentSquare());
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
