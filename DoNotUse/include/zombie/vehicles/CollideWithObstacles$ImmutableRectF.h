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


class CollideWithObstacles {
public:
    float x;
    float y;
    float w;
    float h;
   static ArrayDeque<CollideWithObstacles$ImmutableRectF> pool = std::make_unique<ArrayDeque<>>();

   private CollideWithObstacles$ImmutableRectF() {
   }

   CollideWithObstacles$ImmutableRectF init(float var1, float var2, float var3, float var4) {
      this.x = var1;
      this.y = var2;
      this.w = var3;
      this.h = var4;
    return this;
   }

    float left() {
      return this.x;
   }

    float top() {
      return this.y;
   }

    float right() {
      return this.x + this.w;
   }

    float bottom() {
      return this.y + this.h;
   }

    float width() {
      return this.w;
   }

    float height() {
      return this.h;
   }

    bool containsPoint(float var1, float var2) {
      return var1 >= this.left() && var1 < this.right() && var2 >= this.top() && var2 < this.bottom();
   }

    bool intersects(CollideWithObstacles$ImmutableRectF var1) {
      return this.left() < var1.right() && this.right() > var1.left() && this.top() < var1.bottom() && this.bottom() > var1.top();
   }

   static CollideWithObstacles$ImmutableRectF alloc() {
      return pool.empty() ? new CollideWithObstacles$ImmutableRectF() : pool.pop();
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
