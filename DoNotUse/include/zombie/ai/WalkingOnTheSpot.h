#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/iso/IsoUtils.h"

namespace zombie {
namespace ai {


class WalkingOnTheSpot {
public:
    float x;
    float y;
    float time;

    bool check(float var1, float var2) {
      if (IsoUtils.DistanceToSquared(this.x, this.y, var1, var2) < 0.010000001F) {
         this.time = this.time + GameTime.getInstance().getMultiplier();
      } else {
         this.x = var1;
         this.y = var2;
         this.time = 0.0F;
      }

      return this.time > 400.0F;
   }

    void reset(float var1, float var2) {
      this.x = var1;
      this.y = var2;
      this.time = 0.0F;
   }
}
} // namespace ai
} // namespace zombie
