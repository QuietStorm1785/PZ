#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Vector2f.h"

namespace zombie {
namespace iso {


class RoomDef {
public:
    int x;
    int y;
    int w;
    int h;

   public RoomDef$RoomRect(int var1, int var2, int var3, int var4) {
      this.x = var1;
      this.y = var2;
      this.w = var3;
      this.h = var4;
   }

    int getX() {
      return this.x;
   }

    int getY() {
      return this.y;
   }

    int getX2() {
      return this.x + this.w;
   }

    int getY2() {
      return this.y + this.h;
   }

    int getW() {
      return this.w;
   }

    int getH() {
      return this.h;
   }

    float getClosestPoint(float var1, float var2, Vector2f var3) {
    float var4 = float.MAX_VALUE;
      var4 = this.getClosestPointOnEdge(this.x + 0.5F, this.y + 0.5F, this.x + this.w - 0.5F, this.y + 0.5F, var1, var2, var4, var3);
      var4 = this.getClosestPointOnEdge(this.x + this.w - 0.5F, this.y + 0.5F, this.x + this.w - 0.5F, this.y + this.h - 0.5F, var1, var2, var4, var3);
      var4 = this.getClosestPointOnEdge(this.x + this.w - 0.5F, this.y + this.h - 0.5F, this.x + 0.5F, this.y + this.h - 0.5F, var1, var2, var4, var3);
      return this.getClosestPointOnEdge(this.x + 0.5F, this.y + this.h - 0.5F, this.x + 0.5F, this.y + 0.5F, var1, var2, var4, var3);
   }

    float getClosestPointOnEdge(float var1, float var2, float var3, float var4, float var5, float var6, float var7, Vector2f var8) {
    double var9 = ((var5 - var1) * (var3 - var1) + (var6 - var2) * (var4 - var2)) / (Math.pow(var3 - var1, 2.0) + Math.pow(var4 - var2, 2.0));
    double var11 = var1 + var9 * (var3 - var1);
    double var13 = var2 + var9 * (var4 - var2);
      if (var9 <= 0.0) {
         var11 = var1;
         var13 = var2;
      } else if (var9 >= 1.0) {
         var11 = var3;
         var13 = var4;
      }

    double var15 = (var5 - var11) * (var5 - var11) + (var6 - var13) * (var6 - var13);
      if (var15 < var7) {
         if (var1 == var3) {
            var13 = (int)var13 + 0.5F;
         } else {
            var11 = (int)var11 + 0.5F;
         }

         var8.set(var11, var13);
         return (float)var15;
      } else {
    return var7;
      }
   }
}
} // namespace iso
} // namespace zombie
