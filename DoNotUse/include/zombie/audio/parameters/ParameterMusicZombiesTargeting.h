#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/FMODGlobalParameter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/math/PZMath.h"

namespace zombie {
namespace audio {
namespace parameters {


class ParameterMusicZombiesTargeting : public FMODGlobalParameter {
public:
    int m_playerIndex = -1;

    public ParameterMusicZombiesTargeting() {
      super("MusicZombiesTargeting");
   }

    float calculateCurrentValue() {
    IsoPlayer var1 = this.choosePlayer();
      return var1 != nullptr ? PZMath.clamp(var1.getStats().MusicZombiesTargeting, 0, 50) : 0.0F;
   }

    IsoPlayer choosePlayer() {
      if (this.m_playerIndex != -1) {
    IsoPlayer var1 = IsoPlayer.players[this.m_playerIndex];
         if (var1 == nullptr || var1.isDead()) {
            this.m_playerIndex = -1;
         }
      }

      if (this.m_playerIndex != -1) {
         return IsoPlayer.players[this.m_playerIndex];
      } else {
         for (int var3 = 0; var3 < IsoPlayer.numPlayers; var3++) {
    IsoPlayer var2 = IsoPlayer.players[var3];
            if (var2 != nullptr && !var2.isDead()) {
               this.m_playerIndex = var3;
    return var2;
            }
         }

    return nullptr;
      }
   }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
