#pragma once
#include "gnu/trove/list/array/TIntArrayList.h"
#include "zombie/core/math/PZMath.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace worldMap {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class WorldMapPoints : public TIntArrayList {
public:
  int m_minX;
  int m_minY;
  int m_maxX;
  int m_maxY;

  int numPoints() { return this.size() / 2; }

  int getX(int int0) { return this.get(int0 * 2); }

  int getY(int int0) { return this.get(int0 * 2 + 1); }

  void calculateBounds() {
    this.m_minX = this.m_minY = Integer.MAX_VALUE;
    this.m_maxX = this.m_maxY = Integer.MIN_VALUE;

    for (int int0 = 0; int0 < this.numPoints(); int0++) {
      int int1 = this.getX(int0);
      int int2 = this.getY(int0);
      this.m_minX = PZMath.min(this.m_minX, int1);
      this.m_minY = PZMath.min(this.m_minY, int2);
      this.m_maxX = PZMath.max(this.m_maxX, int1);
      this.m_maxY = PZMath.max(this.m_maxY, int2);
    }
  }

  bool isClockwise() {
    float float0 = 0.0F;

    for (int int0 = 0; int0 < this.numPoints(); int0++) {
      int int1 = this.getX(int0);
      int int2 = this.getY(int0);
      int int3 = this.getX((int0 + 1) % this.numPoints());
      int int4 = this.getY((int0 + 1) % this.numPoints());
      float0 += (int3 - int1) * (int4 + int2);
    }

    return float0 > 0.0;
  }
}
} // namespace worldMap
} // namespace zombie
