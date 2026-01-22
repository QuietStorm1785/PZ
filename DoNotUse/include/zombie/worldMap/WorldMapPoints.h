#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <vector>
#include "zombie/core/math/PZMath.h"

namespace zombie {
namespace worldMap {


class WorldMapPoints {
public:
   std::vector<int> data;
public:
    int m_minX;
    int m_minY;
    int m_maxX;
    int m_maxY;

   int numPoints() const {
      return data.size() / 2;
   }

   int getX(int var1) const {
      return data[var1 * 2];
   }

   int getY(int var1) const {
      return data[var1 * 2 + 1];
   }

    void calculateBounds() {
      this.m_minX = this.m_minY = int.MAX_VALUE;
      this.m_maxX = this.m_maxY = int.MIN_VALUE;

         for (int var1 = 0; var1 < this->numPoints(); var1++) {
            int var2 = this->getX(var1);
            int var3 = this->getY(var1);
         this.m_minX = PZMath.min(this.m_minX, var2);
         this.m_minY = PZMath.min(this.m_minY, var3);
         this.m_maxX = PZMath.max(this.m_maxX, var2);
         this.m_maxY = PZMath.max(this.m_maxY, var3);
      }
   }

    bool isClockwise() {
    float var1 = 0.0F;

      for (int var2 = 0; var2 < this.numPoints(); var2++) {
    int var3 = this.getX(var2);
    int var4 = this.getY(var2);
    int var5 = this.getX((var2 + 1) % this.numPoints());
    int var6 = this.getY((var2 + 1) % this.numPoints());
         var1 += (var5 - var3) * (var6 + var4);
      }

      return var1 > 0.0;
   }
}
} // namespace worldMap
} // namespace zombie
