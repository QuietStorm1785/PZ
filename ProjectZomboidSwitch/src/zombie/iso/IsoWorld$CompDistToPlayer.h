#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoZombie.h"
#include <algorithm>

namespace zombie {
namespace iso {


class IsoWorld {
public:
    float px;
    float py;

   private IsoWorld$CompDistToPlayer() {
   }

    int compare(IsoZombie var1, IsoZombie var2) {
    float var3 = IsoUtils.DistanceManhatten((int)var1.x, (int)var1.y, this.px, this.py);
    float var4 = IsoUtils.DistanceManhatten((int)var2.x, (int)var2.y, this.px, this.py);
      if (var3 < var4) {
         return -1;
      } else {
         return var3 > var4 ? 1 : 0;
      }
   }
}
} // namespace iso
} // namespace zombie
