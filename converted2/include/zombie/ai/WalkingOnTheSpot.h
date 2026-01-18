#pragma once
#include "zombie/GameTime.h"
#include "zombie/iso/IsoUtils.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace ai {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class WalkingOnTheSpot {
public:
  float x;
  float y;
  float time;

  bool check(float x1, float y1) {
    if (IsoUtils.DistanceToSquared(this.x, this.y, x1, y1) < 0.010000001F) {
      this.time = this.time + GameTime.getInstance().getMultiplier();
    } else {
      this.x = x1;
      this.y = y1;
      this.time = 0.0F;
    }

    return this.time > 400.0F;
  }

  void reset(float x1, float y1) {
    this.x = x1;
    this.y = y1;
    this.time = 0.0F;
  }
}
} // namespace ai
} // namespace zombie
