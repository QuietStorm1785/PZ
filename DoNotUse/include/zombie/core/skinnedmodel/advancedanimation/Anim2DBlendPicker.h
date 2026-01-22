#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Core.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/skinnedmodel/advancedanimation/Anim2DBlendPicker/Counter.h"
#include "zombie/core/skinnedmodel/advancedanimation/Anim2DBlendPicker/Edge.h"
#include "zombie/core/skinnedmodel/advancedanimation/Anim2DBlendPicker/HullComparer.h"
#include "zombie/core/skinnedmodel/advancedanimation/Anim2DBlendPicker/PickResults.h"
#include <algorithm>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {


class Anim2DBlendPicker {
public:
   private List<Anim2DBlendTriangle> m_tris;
   private List<Anim2DBlend> m_hull;
    HullComparer m_hullComparer;

    void SetPickTriangles(List<Anim2DBlendTriangle> var1) {
      this.m_tris = var1;
      this.BuildHull();
   }

    void BuildHull() {
    std::unordered_map var1 = new std::unordered_map();
    Counter var2 = std::make_shared<Counter>();

      for (Anim2DBlendTriangle var4 : this.m_tris) {
    Counter var5 = var1.putIfAbsent(std::make_shared<Edge>(var4.node1, var4.node2), var2);
         if (var5 == nullptr) {
            var5 = var2;
            var2 = std::make_unique<Counter>();
         }

         var5.Increment();
         var5 = var1.putIfAbsent(std::make_shared<Edge>(var4.node2, var4.node3), var2);
         if (var5 == nullptr) {
            var5 = var2;
            var2 = std::make_unique<Counter>();
         }

         var5.Increment();
         var5 = var1.putIfAbsent(std::make_shared<Edge>(var4.node3, var4.node1), var2);
         if (var5 == nullptr) {
            var5 = var2;
            var2 = std::make_unique<Counter>();
         }

         var5.Increment();
      }

    std::unordered_set var9 = new std::unordered_set();
      var1.forEach((var1x, var2x) -> {
         if (var2x.count == 1) {
            var9.push_back(var1x.a);
            var9.push_back(var1x.b);
         }
      });
    std::vector var10 = new std::vector(var9);
    float var13 = 0.0F;
    float var6 = 0.0F;

    for (auto& var8 : var10)         var13 += var8.m_XPos;
         var6 += var8.m_YPos;
      }

      var13 /= var10.size();
      var6 /= var10.size();
      this.m_hullComparer = std::make_shared<HullComparer>(var13, var6);
      var10.sort(this.m_hullComparer);
      this.m_hull = var10;
   }

   static <T> int LowerBoundIdx(List<T> var0, T var1, Comparator<? super T> var2) {
    int var3 = 0;
    int var4 = var0.size();

      while (var3 != var4) {
    int var5 = (var3 + var4) / 2;
         if (var2.compare(var1, var0.get(var5)) < 0) {
            var4 = var5;
         } else {
            var3 = var5 + 1;
         }
      }

    return var3;
   }

    static float ProjectPointToLine(float var0, float var1, float var2, float var3, float var4, float var5) {
    float var6 = var0 - var2;
    float var7 = var1 - var3;
    float var8 = var4 - var2;
    float var9 = var5 - var3;
      return (var8 * var6 + var9 * var7) / (var8 * var8 + var9 * var9);
   }

    PickResults Pick(float var1, float var2) {
    PickResults var3 = std::make_shared<PickResults>();

      for (Anim2DBlendTriangle var5 : this.m_tris) {
         if (var5.Contains(var1, var2)) {
            var3.numNodes = 3;
            var3.node1 = var5.node1;
            var3.node2 = var5.node2;
            var3.node3 = var5.node3;
    float var6 = var3.node1.m_XPos;
    float var7 = var3.node1.m_YPos;
    float var8 = var3.node2.m_XPos;
    float var9 = var3.node2.m_YPos;
    float var10 = var3.node3.m_XPos;
    float var11 = var3.node3.m_YPos;
            var3.scale1 = ((var9 - var11) * (var1 - var10) + (var10 - var8) * (var2 - var11))
               / ((var9 - var11) * (var6 - var10) + (var10 - var8) * (var7 - var11));
            var3.scale2 = ((var11 - var7) * (var1 - var10) + (var6 - var10) * (var2 - var11))
               / ((var9 - var11) * (var6 - var10) + (var10 - var8) * (var7 - var11));
            var3.scale3 = 1.0F - var3.scale1 - var3.scale2;
    return var3;
         }
      }

      var1 *= 1.1F;
      var2 *= 1.1F;
    Anim2DBlend var14 = std::make_shared<Anim2DBlend>();
      var14.m_XPos = var1;
      var14.m_YPos = var2;
    int var15 = LowerBoundIdx(this.m_hull, var14, this.m_hullComparer);
      if (var15 == this.m_hull.size()) {
         var15 = 0;
      }

    int var16 = var15 > 0 ? var15 - 1 : this.m_hull.size() - 1;
    Anim2DBlend var17 = this.m_hull.get(var15);
    Anim2DBlend var18 = this.m_hull.get(var16);
    float var19 = ProjectPointToLine(var1, var2, var17.m_XPos, var17.m_YPos, var18.m_XPos, var18.m_YPos);
      if (var19 < 0.0F) {
         var3.numNodes = 1;
         var3.node1 = var17;
         var3.scale1 = 1.0F;
      } else if (var19 > 1.0F) {
         var3.numNodes = 1;
         var3.node1 = var18;
         var3.scale1 = 1.0F;
      } else {
         var3.numNodes = 2;
         var3.node1 = var17;
         var3.node2 = var18;
         var3.scale1 = 1.0F - var19;
         var3.scale2 = var19;
      }

    return var3;
   }

    void render(float var1, float var2) {
    short var3 = 200;
    int var4 = Core.getInstance().getScreenWidth() - var3 - 100;
    int var5 = Core.getInstance().getScreenHeight() - var3 - 100;
      SpriteRenderer.instance.renderi(nullptr, var4 - 20, var5 - 20, var3 + 40, var3 + 40, 1.0F, 1.0F, 1.0F, 1.0F, nullptr);

      for (int var6 = 0; var6 < this.m_tris.size(); var6++) {
    Anim2DBlendTriangle var7 = this.m_tris.get(var6);
         SpriteRenderer.instance
            .renderline(
               nullptr,
               (int)(var4 + var3 / 2 + var7.node1.m_XPos * var3 / 2.0F),
               (int)(var5 + var3 / 2 - var7.node1.m_YPos * var3 / 2.0F),
               (int)(var4 + var3 / 2 + var7.node2.m_XPos * var3 / 2.0F),
               (int)(var5 + var3 / 2 - var7.node2.m_YPos * var3 / 2.0F),
               0.5F,
               0.5F,
               0.5F,
               1.0F
            );
         SpriteRenderer.instance
            .renderline(
               nullptr,
               (int)(var4 + var3 / 2 + var7.node2.m_XPos * var3 / 2.0F),
               (int)(var5 + var3 / 2 - var7.node2.m_YPos * var3 / 2.0F),
               (int)(var4 + var3 / 2 + var7.node3.m_XPos * var3 / 2.0F),
               (int)(var5 + var3 / 2 - var7.node3.m_YPos * var3 / 2.0F),
               0.5F,
               0.5F,
               0.5F,
               1.0F
            );
         SpriteRenderer.instance
            .renderline(
               nullptr,
               (int)(var4 + var3 / 2 + var7.node3.m_XPos * var3 / 2.0F),
               (int)(var5 + var3 / 2 - var7.node3.m_YPos * var3 / 2.0F),
               (int)(var4 + var3 / 2 + var7.node1.m_XPos * var3 / 2.0F),
               (int)(var5 + var3 / 2 - var7.node1.m_YPos * var3 / 2.0F),
               0.5F,
               0.5F,
               0.5F,
               1.0F
            );
      }

    float var8 = 8.0F;
    PickResults var10 = this.Pick(var1, var2);
      if (var10.node1 != nullptr) {
         SpriteRenderer.instance
            .render(
               nullptr,
               var4 + var3 / 2 + var10.node1.m_XPos * var3 / 2.0F - var8 / 2.0F,
               var5 + var3 / 2 - var10.node1.m_YPos * var3 / 2.0F - var8 / 2.0F,
               var8,
               var8,
               0.0F,
               1.0F,
               0.0F,
               1.0F,
               nullptr
            );
      }

      if (var10.node2 != nullptr) {
         SpriteRenderer.instance
            .render(
               nullptr,
               var4 + var3 / 2 + var10.node2.m_XPos * var3 / 2.0F - var8 / 2.0F,
               var5 + var3 / 2 - var10.node2.m_YPos * var3 / 2.0F - var8 / 2.0F,
               var8,
               var8,
               0.0F,
               1.0F,
               0.0F,
               1.0F,
               nullptr
            );
      }

      if (var10.node3 != nullptr) {
         SpriteRenderer.instance
            .render(
               nullptr,
               var4 + var3 / 2 + var10.node3.m_XPos * var3 / 2.0F - var8 / 2.0F,
               var5 + var3 / 2 - var10.node3.m_YPos * var3 / 2.0F - var8 / 2.0F,
               var8,
               var8,
               0.0F,
               1.0F,
               0.0F,
               1.0F,
               nullptr
            );
      }

      var8 = 4.0F;
      SpriteRenderer.instance
         .render(
            nullptr,
            var4 + var3 / 2 + var1 * var3 / 2.0F - var8 / 2.0F,
            var5 + var3 / 2 - var2 * var3 / 2.0F - var8 / 2.0F,
            var8,
            var8,
            0.0F,
            0.0F,
            1.0F,
            1.0F,
            nullptr
         );
   }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
