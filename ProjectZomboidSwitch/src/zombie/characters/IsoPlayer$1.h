#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/IsoUtils.h"
#include <algorithm>

namespace zombie {
namespace characters {


class IsoPlayer {
public:
   IsoPlayer$1(IsoPlayer var1) {
      this.this$0 = var1;
   }

    int compare(IsoGameCharacter var1, IsoGameCharacter var2) {
    float var3 = IsoUtils.DistanceTo(var1.x, var1.y, IsoPlayer.testHitPosition.x, IsoPlayer.testHitPosition.y);
    float var4 = IsoUtils.DistanceTo(var2.x, var2.y, IsoPlayer.testHitPosition.x, IsoPlayer.testHitPosition.y);
      if (var3 > var4) {
    return 1;
      } else {
         return var4 > var3 ? -1 : 0;
      }
   }
}
} // namespace characters
} // namespace zombie
