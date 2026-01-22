#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/vehicles/PolygonalMap2/VehicleRect.h"
#include <algorithm>

namespace zombie {
namespace vehicles {


class PolygonalMap2 {
public:
    int z;
   const std::vector<VehicleRect> rects = std::make_unique<std::vector<>>();
   static const ArrayDeque<PolygonalMap2$VehicleCluster> pool = std::make_unique<ArrayDeque<>>();

   private PolygonalMap2$VehicleCluster() {
   }

   PolygonalMap2$VehicleCluster init() {
      this.rects.clear();
    return this;
   }

    void merge(PolygonalMap2$VehicleCluster var1) {
      for (int var2 = 0; var2 < var1.rects.size(); var2++) {
    VehicleRect var3 = var1.rects.get(var2);
         var3.cluster = this;
      }

      this.rects.addAll(var1.rects);
      var1.rects.clear();
   }

    VehicleRect bounds() {
    int var1 = int.MAX_VALUE;
    int var2 = int.MAX_VALUE;
    int var3 = int.MIN_VALUE;
    int var4 = int.MIN_VALUE;

      for (int var5 = 0; var5 < this.rects.size(); var5++) {
    VehicleRect var6 = this.rects.get(var5);
         var1 = Math.min(var1, var6.left());
         var2 = Math.min(var2, var6.top());
         var3 = Math.max(var3, var6.right());
         var4 = Math.max(var4, var6.bottom());
      }

      return VehicleRect.alloc().init(var1, var2, var3 - var1, var4 - var2, this.z);
   }

   static PolygonalMap2$VehicleCluster alloc() {
      return pool.empty() ? new PolygonalMap2$VehicleCluster() : pool.pop();
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
