#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/Vector2.h"
#include "zombie/popman/ObjectPool.h"
#include "zombie/vehicles/CollideWithObstaclesPoly/CCEdge.h"

namespace zombie {
namespace vehicles {


class CollideWithObstaclesPoly {
public:
    float x;
    float y;
    int z;
   const std::vector<CCEdge> edges = std::make_unique<std::vector<>>();
   static const ObjectPool<CollideWithObstaclesPoly$CCNode> pool = std::make_shared<ObjectPool>(CollideWithObstaclesPoly$CCNode::new);

   private CollideWithObstaclesPoly$CCNode() {
   }

   CollideWithObstaclesPoly$CCNode init(float var1, float var2, int var3) {
      this.x = var1;
      this.y = var2;
      this.z = var3;
      this.edges.clear();
    return this;
   }

   CollideWithObstaclesPoly$CCNode setXY(float var1, float var2) {
      this.x = var1;
      this.y = var2;
    return this;
   }

    bool getNormalAndEdgeVectors(Vector2 var1, Vector2 var2) {
    CCEdge var3 = nullptr;
    CCEdge var4 = nullptr;

      for (int var5 = 0; var5 < this.edges.size(); var5++) {
    CCEdge var6 = this.edges.get(var5);
         if (var3 == nullptr) {
            var3 = var6;
         } else if (!var3.hasNode(var6.node1) || !var3.hasNode(var6.node2)) {
            var4 = var6;
         }
      }

      if (var3 != nullptr && var4 != nullptr) {
    float var7 = var3.normal.x + var4.normal.x;
    float var8 = var3.normal.y + var4.normal.y;
         var1.set(var7, var8);
         var1.normalize();
         if (var3.node1 == this) {
            var2.set(var3.node2.x - var3.node1.x, var3.node2.y - var3.node1.y);
         } else {
            var2.set(var3.node1.x - var3.node2.x, var3.node1.y - var3.node2.y);
         }

         var2.normalize();
    return true;
      } else {
    return false;
      }
   }

   static CollideWithObstaclesPoly$CCNode alloc() {
      return (CollideWithObstaclesPoly$CCNode)pool.alloc();
   }

    void release() {
      pool.release(this);
   }

    static void releaseAll(std::vector<CollideWithObstaclesPoly$CCNode> var0) {
      pool.releaseAll(var0);
   }
}
} // namespace vehicles
} // namespace zombie
