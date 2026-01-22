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
#include "zombie/characters/Moodles/MoodleType.h"

namespace zombie {
namespace audio {
namespace parameters {


class ParameterMoodlePanic : public FMODGlobalParameter {
public:
    public ParameterMoodlePanic() {
      super("MoodlePanic");
   }

    float calculateCurrentValue() {
    IsoGameCharacter var1 = this.getCharacter();
    return var1 = = nullptr ? 0.0F : var1.getMoodles().getMoodleLevel(MoodleType.Panic) / 4.0F;
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
