#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoZombie.h"
#include "zombie/network/packets/hit/HitInfo.h"
#include "zombie/util/Type.h"
#include <algorithm>

namespace zombie {
namespace ai {
namespace states {


class SwipeStatePlayer {
public:
    int compare(HitInfo var1, HitInfo var2) {
    float var3 = var1.distSq;
    float var4 = var2.distSq;
    IsoZombie var5 = (IsoZombie)Type.tryCastTo(var1.getObject(), IsoZombie.class);
    IsoZombie var6 = (IsoZombie)Type.tryCastTo(var2.getObject(), IsoZombie.class);
      if (var5 != nullptr && var6 != nullptr) {
    bool var7 = SwipeStatePlayer.isProne(var5);
    bool var8 = SwipeStatePlayer.isProne(var6);
    bool var9 = var5.isCurrentState(ZombieGetUpState.instance());
    bool var10 = var6.isCurrentState(ZombieGetUpState.instance());
         if (var9 && !var10 && var8) {
            return -1;
         }

         if (!var9 && var7 && var10) {
    return 1;
         }

         if (var7 && var8) {
            if (var5.isCrawling() && !var6.isCrawling()) {
               return -1;
            }

            if (!var5.isCrawling() && var6.isCrawling()) {
    return 1;
            }
         }
      }

      if (var3 > var4) {
    return 1;
      } else {
         return var4 > var3 ? -1 : 0;
      }
   }
}
} // namespace states
} // namespace ai
} // namespace zombie
