#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/Vector2.h"
#include "zombie/vehicles/CollideWithObstacles/CCEdge.h"
#include "zombie/vehicles/CollideWithObstacles/CCObstacle.h"
#include <algorithm>

namespace zombie {
namespace vehicles {


class CollideWithObstacles {
public:
    float x;
    float y;
    int z;
    bool ignore;
   const std::vector<CCEdge> edges = std::make_unique<std::vector<>>();
   const std::vector<CollideWithObstacles$CCNode> visible = std::make_unique<std::vector<>>();
   static std::vector<CCObstacle> tempObstacles = std::make_unique<std::vector<>>();
   static ArrayDeque<CollideWithObstacles$CCNode> pool = std::make_unique<ArrayDeque<>>();

   private CollideWithObstacles$CCNode() {
   }

   CollideWithObstacles$CCNode init(float var1, float var2, int var3) {
      this.x = var1;
      this.y = var2;
      this.z = var3;
      this.ignore = false;
      this.edges.clear();
      this.visible.clear();
    return this;
   }

   CollideWithObstacles$CCNode setXY(float var1, float var2) {
      this.x = var1;
      this.y = var2;
    return this;
   }

    bool sharesEdge(CollideWithObstacles$CCNode var1) {
      for (int var2 = 0; var2 < this.edges.size(); var2++) {
    CCEdge var3 = this.edges.get(var2);
         if (var3.hasNode(var1)) {
    return true;
         }
      }

    return false;
   }

    bool sharesShape(CollideWithObstacles$CCNode var1) {
      for (int var2 = 0; var2 < this.edges.size(); var2++) {
    CCEdge var3 = this.edges.get(var2);

         for (int var4 = 0; var4 < var1.edges.size(); var4++) {
    CCEdge var5 = var1.edges.get(var4);
            if (var3.obstacle != nullptr && var3.obstacle == var5.obstacle) {
    return true;
            }
         }
      }

    return false;
   }

    void getObstacles(std::vector<CCObstacle> var1) {
      for (int var2 = 0; var2 < this.edges.size(); var2++) {
    CCEdge var3 = this.edges.get(var2);
         if (!var1.contains(var3.obstacle)) {
            var1.push_back(var3.obstacle);
         }
      }
   }

    bool onSameShapeButDoesNotShareAnEdge(CollideWithObstacles$CCNode var1) {
      tempObstacles.clear();
      this.getObstacles(tempObstacles);

      for (int var2 = 0; var2 < tempObstacles.size(); var2++) {
    CCObstacle var3 = tempObstacles.get(var2);
         if (var3.hasNode(var1) && !var3.hasAdjacentNodes(this, var1)) {
    return true;
         }
      }

    return false;
   }

    bool getNormalAndEdgeVectors(Vector2 var1, Vector2 var2) {
    CCEdge var3 = nullptr;
    CCEdge var4 = nullptr;

      for (int var5 = 0; var5 < this.edges.size(); var5++) {
    CCEdge var6 = this.edges.get(var5);
         if (var6.node1.visible.contains(var6.node2)) {
            if (var3 == nullptr) {
               var3 = var6;
            } else if (!var3.hasNode(var6.node1) || !var3.hasNode(var6.node2)) {
               var4 = var6;
            }
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

   static CollideWithObstacles$CCNode alloc() {
      if (pool.empty()) {
    bool var0 = false;
      } else {
    bool var1 = false;
      }

      return pool.empty() ? new CollideWithObstacles$CCNode() : pool.pop();
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
