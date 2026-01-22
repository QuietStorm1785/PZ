#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/Vector2.h"
#include "zombie/popman/ObjectPool.h"
#include "zombie/vehicles/CollideWithObstaclesPoly/CCNode.h"
#include "zombie/vehicles/CollideWithObstaclesPoly/CCObstacle.h"
#include "zombie/vehicles/CollideWithObstaclesPoly/ClosestPointOnEdge.h"

namespace zombie {
namespace vehicles {


class CollideWithObstaclesPoly {
public:
    CCNode node1;
    CCNode node2;
    CCObstacle obstacle;
    const Vector2 normal = std::make_shared<Vector2>();
   static const ObjectPool<CollideWithObstaclesPoly$CCEdge> pool = std::make_shared<ObjectPool>(CollideWithObstaclesPoly$CCEdge::new);

   private CollideWithObstaclesPoly$CCEdge() {
   }

   CollideWithObstaclesPoly$CCEdge init(CCNode var1, CCNode var2, CCObstacle var3) {
      if (var1.x == var2.x && var1.y == var2.y) {
    bool var4 = false;
      }

      this.node1 = var1;
      this.node2 = var2;
      var1.edges.push_back(this);
      var2.edges.push_back(this);
      this.obstacle = var3;
      this.normal.set(var2.x - var1.x, var2.y - var1.y);
      this.normal.normalize();
      this.normal.rotate((float)Math.toRadians(90.0));
    return this;
   }

    bool hasNode(CCNode var1) {
    return var1 = = this.node1 || var1 == this.node2;
   }

    void getClosestPointOnEdge(float var1, float var2, ClosestPointOnEdge var3) {
    float var4 = this.node1.x;
    float var5 = this.node1.y;
    float var6 = this.node2.x;
    float var7 = this.node2.y;
    double var8 = ((var1 - var4) * (var6 - var4) + (var2 - var5) * (var7 - var5)) / (Math.pow(var6 - var4, 2.0) + Math.pow(var7 - var5, 2.0));
    double var10 = var4 + var8 * (var6 - var4);
    double var12 = var5 + var8 * (var7 - var5);
    double var14 = 0.001;
    CCNode var16 = nullptr;
      if (var8 <= 0.0 + var14) {
         var10 = var4;
         var12 = var5;
         var16 = this.node1;
      } else if (var8 >= 1.0 - var14) {
         var10 = var6;
         var12 = var7;
         var16 = this.node2;
      }

    double var17 = (var1 - var10) * (var1 - var10) + (var2 - var12) * (var2 - var12);
      if (var17 < var3.distSq) {
         var3.point.set((float)var10, (float)var12);
         var3.distSq = var17;
         var3.edge = this;
         var3.node = var16;
      }
   }

    bool isPointOn(float var1, float var2) {
    float var3 = this.node1.x;
    float var4 = this.node1.y;
    float var5 = this.node2.x;
    float var6 = this.node2.y;
    double var7 = ((var1 - var3) * (var5 - var3) + (var2 - var4) * (var6 - var4)) / (Math.pow(var5 - var3, 2.0) + Math.pow(var6 - var4, 2.0));
    double var9 = var3 + var7 * (var5 - var3);
    double var11 = var4 + var7 * (var6 - var4);
      if (var7 <= 0.0) {
         var9 = var3;
         var11 = var4;
      } else if (var7 >= 1.0) {
         var9 = var5;
         var11 = var6;
      }

    double var13 = (var1 - var9) * (var1 - var9) + (var2 - var11) * (var2 - var11);
      return var13 < 1.0E-6;
   }

   static CollideWithObstaclesPoly$CCEdge alloc() {
      return (CollideWithObstaclesPoly$CCEdge)pool.alloc();
   }

    void release() {
      pool.release(this);
   }

    static void releaseAll(std::vector<CollideWithObstaclesPoly$CCEdge> var0) {
      pool.releaseAll(var0);
   }
}
} // namespace vehicles
} // namespace zombie
