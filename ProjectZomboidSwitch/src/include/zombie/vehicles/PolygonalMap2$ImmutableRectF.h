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
    float x;
    float y;
    float w;
    float h;
   static const ArrayDeque<PolygonalMap2$ImmutableRectF> pool = std::make_unique<ArrayDeque<>>();

   private PolygonalMap2$ImmutableRectF() {
   }

   PolygonalMap2$ImmutableRectF init(float var1, float var2, float var3, float var4) {
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

    bool intersects(PolygonalMap2$ImmutableRectF var1) {
      return this.left() < var1.right() && this.right() > var1.left() && this.top() < var1.bottom() && this.bottom() > var1.top();
   }

   static PolygonalMap2$ImmutableRectF alloc() {
      return pool.empty() ? new PolygonalMap2$ImmutableRectF() : pool.pop();
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
