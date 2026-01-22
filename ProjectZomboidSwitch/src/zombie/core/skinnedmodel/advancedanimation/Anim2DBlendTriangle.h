#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/annotation/XmlIDREF.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {


class Anim2DBlendTriangle {
public:
    Anim2DBlend node1;
    Anim2DBlend node2;
    Anim2DBlend node3;

    static double sign(float var0, float var1, float var2, float var3, float var4, float var5) {
      return (var0 - var4) * (var3 - var5) - (var2 - var4) * (var1 - var5);
   }

    static bool PointInTriangle(float var0, float var1, float var2, float var3, float var4, float var5, float var6, float var7) {
    bool var8 = sign(var0, var1, var2, var3, var4, var5) < 0.0;
    bool var9 = sign(var0, var1, var4, var5, var6, var7) < 0.0;
    bool var10 = sign(var0, var1, var6, var7, var2, var3) < 0.0;
    return var8 = = var9 && var9 == var10;
   }

    bool Contains(float var1, float var2) {
    return PointInTriangle();
   }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
