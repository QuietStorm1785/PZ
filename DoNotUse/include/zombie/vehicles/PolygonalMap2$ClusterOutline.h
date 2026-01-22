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
    int x;
    int y;
    int z;
    bool w;
    bool n;
    bool e;
    bool s;
    bool tw;
    bool tn;
    bool te;
    bool ts;
    bool inner;
    bool innerCorner;
    bool start;
   static const ArrayDeque<PolygonalMap2$ClusterOutline> pool = std::make_unique<ArrayDeque<>>();

   private PolygonalMap2$ClusterOutline() {
   }

   PolygonalMap2$ClusterOutline init(int var1, int var2, int var3) {
      this.x = var1;
      this.y = var2;
      this.z = var3;
      this.w = this.n = this.e = this.s = false;
      this.tw = this.tn = this.te = this.ts = false;
      this.inner = this.innerCorner = this.start = false;
    return this;
   }

   static PolygonalMap2$ClusterOutline alloc() {
      return pool.empty() ? new PolygonalMap2$ClusterOutline() : pool.pop();
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
