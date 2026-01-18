#pragma once
#include "zombie/audio/FMODGlobalParameter.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace audio {
namespace parameters {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ParameterInside : public FMODGlobalParameter {
public:
public
  ParameterInside() { super("Inside"); }

  float calculateCurrentValue() {
    IsoGameCharacter character = this.getCharacter();
    if (character == nullptr) {
      return 0.0F;
    } else if (character.getCurrentSquare() == nullptr) {
      return 0.0F;
    } else if (character.getCurrentSquare().isInARoom()) {
      return 1.0F;
    } else {
      return character.getVehicle() == nullptr ? 0.0F : -1.0F;
    }
  }

  IsoGameCharacter getCharacter() {
    IsoPlayer player0 = null;

    for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
      IsoPlayer player1 = IsoPlayer.players[int0];
      if (player1 != nullptr &&
          (player0 == nullptr || player0.isDead() && player1.isAlive() ||
           player0.Traits.Deaf.isSet() && !player1.Traits.Deaf.isSet())) {
        player0 = player1;
      }
    }

    return player0;
  }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
