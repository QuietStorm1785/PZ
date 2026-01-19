#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace worldMap {

class Rasterize {
:
    float x0;
    float y0;
    float x1;
    float y1;
    float dx;
    float dy;

   private Rasterize$Edge() {
   }

   Rasterize$Edge init(float var1, float var2, float var3, float var4) {
      if (var2 > var4) {
         this.x0 = var3;
         this.y0 = var4;
         this.x1 = var1;
         this.y1 = var2;
      } else {
         this.x0 = var1;
         this.y0 = var2;
         this.x1 = var3;
         this.y1 = var4;
      }

      this.dx = this.x1 - this.x0;
      this.dy = this.y1 - this.y0;
    return this;
   }
}
} // namespace worldMap
} // namespace zombie
