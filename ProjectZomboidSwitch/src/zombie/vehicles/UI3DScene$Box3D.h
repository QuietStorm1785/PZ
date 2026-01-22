#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace vehicles {

class UI3DScene {
public:
    float x;
    float y;
    float z;
    float w;
    float h;
    float L;
    float rx;
    float ry;
    float rz;
    float r;
    float g;
    float b;

   private UI3DScene$Box3D() {
   }

   UI3DScene$Box3D set(UI3DScene$Box3D var1) {
      return this.set(var1.x, var1.y, var1.z, var1.w, var1.h, var1.L, var1.rx, var1.ry, var1.rz, var1.r, var1.g, var1.b);
   }

   UI3DScene$Box3D set(
      float var1, float var2, float var3, float var4, float var5, float var6, float var7, float var8, float var9, float var10, float var11, float var12
   ) {
      this.x = var1;
      this.y = var2;
      this.z = var3;
      this.w = var4;
      this.h = var5;
      this.L = var6;
      this.rx = var7;
      this.ry = var8;
      this.rz = var9;
      this.r = var10;
      this.g = var11;
      this.b = var12;
    return this;
   }
}
} // namespace vehicles
} // namespace zombie
