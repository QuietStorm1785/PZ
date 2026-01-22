#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include <algorithm>

namespace zombie {
namespace iso {


class IsoWorld {
public:
   private IsoWorld$CompScoreToPlayer() {
   }

    int compare(IsoZombie var1, IsoZombie var2) {
    float var3 = this.getScore(var1);
    float var4 = this.getScore(var2);
      if (var3 < var4) {
    return 1;
      } else {
         return var3 > var4 ? -1 : 0;
      }
   }

    float getScore(IsoZombie var1) {
    float var2 = float.MIN_VALUE;

      for (int var3 = 0; var3 < 4; var3++) {
    IsoPlayer var4 = IsoPlayer.players[var3];
         if (var4 != nullptr && var4.current != nullptr) {
    float var5 = var4.getZombieRelevenceScore(var1);
            var2 = Math.max(var2, var5);
         }
      }

    return var2;
   }
}
} // namespace iso
} // namespace zombie
