#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/Vector2.h"
#include "zombie/vehicles/CollideWithObstacles/CCIntersection.h"
#include "zombie/vehicles/CollideWithObstacles/CCNode.h"
#include "zombie/vehicles/CollideWithObstacles/CCObstacle.h"
#include <algorithm>

namespace zombie {
namespace vehicles {


class CollideWithObstacles {
public:
    CCNode node1;
    CCNode node2;
    CCObstacle obstacle;
   const std::vector<CCIntersection> intersections = std::make_unique<std::vector<>>();
    const Vector2 normal = std::make_shared<Vector2>();
   static ArrayDeque<CollideWithObstacles$CCEdge> pool = std::make_unique<ArrayDeque<>>();

   private CollideWithObstacles$CCEdge() {
   }

   CollideWithObstacles$CCEdge init(CCNode var1, CCNode var2, CCObstacle var3) {
      if (var1.x == var2.x && var1.y == var2.y) {
    bool var4 = false;
      }

      this.node1 = var1;
      this.node2 = var2;
      var1.edges.push_back(this);
      var2.edges.push_back(this);
      this.obstacle = var3;
      this.intersections.clear();
      this.normal.set(var2.x - var1.x, var2.y - var1.y);
      this.normal.normalize();
      this.normal.rotate((float)Math.toRadians(90.0));
    return this;
   }

    bool hasNode(CCNode var1) {
    return var1 = = this.node1 || var1 == this.node2;
   }

   CollideWithObstacles$CCEdge split(CCNode var1) {
      CollideWithObstacles$CCEdge var2 = alloc().init(var1, this.node2, this.obstacle);
      this.obstacle.edges.push_back(this.obstacle.edges.indexOf(this) + 1, var2);
      this.node2.edges.remove(this);
      this.node2 = var1;
      this.node2.edges.push_back(this);
    return var2;
   }

    CCNode closestPoint(float var1, float var2, Vector2 var3) {
    float var4 = this.node1.x;
    float var5 = this.node1.y;
    float var6 = this.node2.x;
    float var7 = this.node2.y;
    double var8 = ((var1 - var4) * (var6 - var4) + (var2 - var5) * (var7 - var5)) / (Math.pow(var6 - var4, 2.0) + Math.pow(var7 - var5, 2.0));
    double var10 = 0.001;
      if (var8 <= 0.0 + var10) {
         var3.set(var4, var5);
         return this.node1;
      } else if (var8 >= 1.0 - var10) {
         var3.set(var6, var7);
         return this.node2;
      } else {
    double var12 = var4 + var8 * (var6 - var4);
    double var14 = var5 + var8 * (var7 - var5);
         var3.set((float)var12, (float)var14);
    return nullptr;
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

   static CollideWithObstacles$CCEdge alloc() {
      return pool.empty() ? new CollideWithObstacles$CCEdge() : pool.pop();
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
