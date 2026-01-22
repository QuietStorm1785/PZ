#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/popman/ObjectPool.h"
#include "zombie/vehicles/CollideWithObstaclesPoly/CCEdge.h"
#include "zombie/vehicles/CollideWithObstaclesPoly/CCEdgeRing.h"
#include "zombie/vehicles/CollideWithObstaclesPoly/CCObstacle/1.h"
#include "zombie/vehicles/CollideWithObstaclesPoly/ClosestPointOnEdge.h"
#include "zombie/vehicles/CollideWithObstaclesPoly/EdgeRingHit.h"
#include "zombie/vehicles/CollideWithObstaclesPoly/ImmutableRectF.h"

namespace zombie {
namespace vehicles {


class CollideWithObstaclesPoly {
public:
    const CCEdgeRing outer = std::make_shared<CCEdgeRing>();
   const std::vector<CCEdgeRing> inner = std::make_unique<std::vector<>>();
    BaseVehicle vehicle = nullptr;
    ImmutableRectF bounds;
   static const ObjectPool<CollideWithObstaclesPoly$CCObstacle> pool = std::make_shared<1>(CollideWithObstaclesPoly$CCObstacle::new);

   private CollideWithObstaclesPoly$CCObstacle() {
   }

   CollideWithObstaclesPoly$CCObstacle init() {
      this.outer.clear();
      this.inner.clear();
      this.vehicle = nullptr;
    return this;
   }

    bool isPointInside(float var1, float var2, int var3) {
      if (this.outer.isPointInPolygon_WindingNumber(var1, var2, var3) != EdgeRingHit.Inside) {
    return false;
      } else if (this.inner.empty()) {
    return true;
      } else {
         for (int var4 = 0; var4 < this.inner.size(); var4++) {
    CCEdgeRing var5 = this.inner.get(var4);
            if (var5.isPointInPolygon_WindingNumber(var1, var2, var3) != EdgeRingHit.Outside) {
    return false;
            }
         }

    return true;
      }
   }

    bool lineSegmentIntersects(float var1, float var2, float var3, float var4, bool var5) {
      if (this.outer.lineSegmentIntersects(var1, var2, var3, var4, var5, true)) {
    return true;
      } else {
         for (int var6 = 0; var6 < this.inner.size(); var6++) {
    CCEdgeRing var7 = this.inner.get(var6);
            if (var7.lineSegmentIntersects(var1, var2, var3, var4, var5, false)) {
    return true;
            }
         }

    return false;
      }
   }

    void lineSegmentIntersect(float var1, float var2, float var3, float var4, ClosestPointOnEdge var5, bool var6) {
      this.outer.lineSegmentIntersect(var1, var2, var3, var4, var5, var6);

      for (int var7 = 0; var7 < this.inner.size(); var7++) {
    CCEdgeRing var8 = this.inner.get(var7);
         var8.lineSegmentIntersect(var1, var2, var3, var4, var5, var6);
      }
   }

    void getClosestPointOnEdge(float var1, float var2, ClosestPointOnEdge var3) {
      this.outer.getClosestPointOnEdge(var1, var2, var3);

      for (int var4 = 0; var4 < this.inner.size(); var4++) {
    CCEdgeRing var5 = this.inner.get(var4);
         var5.getClosestPointOnEdge(var1, var2, var3);
      }
   }

    void calcBounds() {
    float var1 = float.MAX_VALUE;
    float var2 = float.MAX_VALUE;
    float var3 = float.MIN_VALUE;
    float var4 = float.MIN_VALUE;

      for (int var5 = 0; var5 < this.outer.size(); var5++) {
    CCEdge var6 = (CCEdge)this.outer.get(var5);
         var1 = Math.min(var1, var6.node1.x);
         var2 = Math.min(var2, var6.node1.y);
         var3 = Math.max(var3, var6.node1.x);
         var4 = Math.max(var4, var6.node1.y);
      }

      if (this.bounds != nullptr) {
         this.bounds.release();
      }

    float var7 = 0.01F;
      this.bounds = ImmutableRectF.alloc().init(var1 - var7, var2 - var7, var3 - var1 + var7 * 2.0F, var4 - var2 + var7 * 2.0F);
   }

    void render() {
      this.outer.render(true);

      for (int var1 = 0; var1 < this.inner.size(); var1++) {
         this.inner.get(var1).render(false);
      }
   }

   static CollideWithObstaclesPoly$CCObstacle alloc() {
      return (CollideWithObstaclesPoly$CCObstacle)pool.alloc();
   }

    void release() {
      pool.release(this);
   }

    static void releaseAll(std::vector<CollideWithObstaclesPoly$CCObstacle> var0) {
      pool.releaseAll(var0);
   }
}
} // namespace vehicles
} // namespace zombie
