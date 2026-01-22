#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace zombie {
namespace vehicles {


class PolygonalMap2 {
public:
    static int nextID = 1;
    int ID = nextID++;
    int x;
    int y;
    int z;
    int bits;
    short cost;
   static const ArrayDeque<PolygonalMap2$Square> pool = std::make_unique<ArrayDeque<>>();

   PolygonalMap2$Square init(int var1, int var2, int var3) {
      this.x = var1;
      this.y = var2;
      this.z = var3;
    return this;
   }

    bool has(int var1) {
      return (this.bits & var1) != 0;
   }

    bool isReallySolid() {
      return this.has(1) || this.has(1024) && !this.isAdjacentToWindow();
   }

    bool isNonThumpableSolid() {
      return this.isReallySolid() && !this.has(131072);
   }

    bool isCanPathW() {
      if (this.has(8192)) {
    return true;
      } else {
         PolygonalMap2$Square var1 = PolygonalMap2.instance.getSquare(this.x - 1, this.y, this.z);
         return var1 != nullptr && (var1.has(131072) || var1.has(262144));
      }
   }

    bool isCanPathN() {
      if (this.has(16384)) {
    return true;
      } else {
         PolygonalMap2$Square var1 = PolygonalMap2.instance.getSquare(this.x, this.y - 1, this.z);
         return var1 != nullptr && (var1.has(131072) || var1.has(524288));
      }
   }

    bool isCollideW() {
      if (this.has(2)) {
    return true;
      } else {
         PolygonalMap2$Square var1 = PolygonalMap2.instance.getSquare(this.x - 1, this.y, this.z);
         return var1 != nullptr && (var1.has(262144) || var1.has(448) || var1.isReallySolid());
      }
   }

    bool isCollideN() {
      if (this.has(4)) {
    return true;
      } else {
         PolygonalMap2$Square var1 = PolygonalMap2.instance.getSquare(this.x, this.y - 1, this.z);
         return var1 != nullptr && (var1.has(524288) || var1.has(56) || var1.isReallySolid());
      }
   }

    bool isThumpW() {
      if (this.has(32768)) {
    return true;
      } else {
         PolygonalMap2$Square var1 = PolygonalMap2.instance.getSquare(this.x - 1, this.y, this.z);
         return var1 != nullptr && var1.has(131072);
      }
   }

    bool isThumpN() {
      if (this.has(65536)) {
    return true;
      } else {
         PolygonalMap2$Square var1 = PolygonalMap2.instance.getSquare(this.x, this.y - 1, this.z);
         return var1 != nullptr && var1.has(131072);
      }
   }

    bool isAdjacentToWindow() {
      if (!this.has(2048) && !this.has(4096)) {
         PolygonalMap2$Square var1 = PolygonalMap2.instance.getSquare(this.x, this.y + 1, this.z);
         if (var1 != nullptr && var1.has(4096)) {
    return true;
         } else {
            PolygonalMap2$Square var2 = PolygonalMap2.instance.getSquare(this.x + 1, this.y, this.z);
            return var2 != nullptr && var2.has(2048);
         }
      } else {
    return true;
      }
   }

   static PolygonalMap2$Square alloc() {
      return pool.empty() ? new PolygonalMap2$Square() : pool.pop();
   }

    void release() {
      if (!$assertionsDisabled && pool.contains(this)) {
         throw std::make_unique<AssertionError>();
      } else {
         pool.push(this);
      }
   }
}
} // namespace vehicles
} // namespace zombie
