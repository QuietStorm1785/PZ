#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/worldMap/Rasterize/Edge.h"
#include <algorithm>

namespace zombie {
namespace worldMap {


class Rasterize {
public:
    const Edge edge1 = new Edge();
    const Edge edge2 = new Edge();
    const Edge edge3 = new Edge();

    void scanLine(int var1, int var2, int var3, Integer> var4) {
      for (int var5 = var1; var5 < var2; var5++) {
         var4.accept(var5, var3);
      }
   }

    void scanSpan(Edge var1, Edge var2, int var3, int var4, Integer> var5) {
    int var6 = (int)Math.max((double)var3, Math.floor(var2.y0));
    int var7 = (int)Math.min((double)var4, Math.ceil(var2.y1));
      if (var1.x0 == var2.x0 && var1.y0 == var2.y0) {
         if (var1.x0 + var2.dy / var1.dy * var1.dx < var2.x1) {
    Edge var21 = var1;
            var1 = var2;
            var2 = var21;
         }
      } else if (var1.x1 - var2.dy / var1.dy * var1.dx < var2.x0) {
    Edge var8 = var1;
         var1 = var2;
         var2 = var8;
      }

    double var22 = var1.dx / var1.dy;
    double var10 = var2.dx / var2.dy;
    double var12 = var1.dx > 0.0F ? 1.0 : 0.0;
    double var14 = var2.dx < 0.0F ? 1.0 : 0.0;

      for (int var16 = var6; var16 < var7; var16++) {
    double var17 = var22 * Math.max(0.0, Math.min((double)var1.dy, var16 + var12 - var1.y0)) + var1.x0;
    double var19 = var10 * Math.max(0.0, Math.min((double)var2.dy, var16 + var14 - var2.y0)) + var2.x0;
         this.scanLine((int)Math.floor(var19), (int)Math.ceil(var17), var16, var5);
      }
   }

    void scanTriangle(float var1, float var2, float var3, float var4, float var5, float var6, int var7, int var8, Integer> var9) {
    Edge var10 = this.edge1.init(var1, var2, var3, var4);
    Edge var11 = this.edge2.init(var3, var4, var5, var6);
    Edge var12 = this.edge3.init(var5, var6, var1, var2);
      if (var10.dy > var12.dy) {
    Edge var13 = var10;
         var10 = var12;
         var12 = var13;
      }

      if (var11.dy > var12.dy) {
    Edge var14 = var11;
         var11 = var12;
         var12 = var14;
      }

      if (var10.dy > 0.0F) {
         this.scanSpan(var12, var10, var7, var8, var9);
      }

      if (var11.dy > 0.0F) {
         this.scanSpan(var12, var11, var7, var8, var9);
      }
   }
}
} // namespace worldMap
} // namespace zombie
