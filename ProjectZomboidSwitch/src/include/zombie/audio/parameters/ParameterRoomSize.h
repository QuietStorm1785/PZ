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
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/RoomDef.h"

namespace zombie {
namespace audio {
namespace parameters {


class ParameterRoomSize : public FMODGlobalParameter {
public:
    public ParameterRoomSize() {
      super("RoomSize");
   }

    float calculateCurrentValue() {
    IsoGameCharacter var1 = this.getCharacter();
      if (var1 == nullptr) {
         return 0.0F;
      } else {
    RoomDef var2 = var1.getCurrentRoomDef();
         if (var2 != nullptr) {
            return var2.getArea();
         } else {
    IsoGridSquare var3 = var1.getCurrentSquare();
            return var3 != nullptr && var3.isInARoom() ? var3.getRoomSize() : 0.0F;
         }
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
