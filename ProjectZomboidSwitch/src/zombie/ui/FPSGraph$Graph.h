#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/PerformanceSettings.h"
#include "zombie/core/SpriteRenderer.h"

namespace zombie {
namespace ui {


class FPSGraph {
public:
   private const std::vector<int64_t> times;
   private const std::vector<int> bars;

   private FPSGraph$Graph(FPSGraph var1) {
      this.this$0 = var1;
      this.times = std::make_unique<std::vector<>>();
      this.bars = std::make_unique<std::vector<>>();
   }

    void add(long var1) {
      this.times.push_back(var1);
      this.bars.clear();
    long var3 = this.times.get(0);
    int var5 = 1;

      for (int var6 = 1; var6 < this.times.size(); var6++) {
         if (var6 != this.times.size() - 1 && this.times.get(var6) - var3 <= 1000L) {
            var5++;
         } else {
    long var7 = (this.times.get(var6) - var3) / 1000L - 1L;

            for (int var9 = 0; var9 < var7; var9++) {
               this.bars.push_back(0);
            }

            this.bars.push_back(var5);
            var5 = 1;
            var3 = this.times.get(var6);
         }
      }

      while (this.bars.size() > 30) {
    int var10 = this.bars.get(0);

         for (int var11 = 0; var11 < var10; var11++) {
            this.times.remove(0);
         }

         this.bars.remove(0);
      }
   }

    void render(float var1, float var2, float var3) {
      if (!this.bars.empty()) {
    float var4 = this.this$0.getHeight().intValue() - 4;
    float var5 = this.this$0.getHeight().intValue() - 2;
    int var6 = Math.max(PerformanceSettings.getLockFPS(), PerformanceSettings.LightingFPS);
    uint8_t var7 = 8;
    float var8 = var4 * ((float)Math.min(var6, this.bars.get(0)) / var6);

         for (int var9 = 1; var9 < this.bars.size() - 1; var9++) {
    float var10 = var4 * ((float)Math.min(var6, this.bars.get(var9)) / var6);
            SpriteRenderer.instance
               .renderline(
                  nullptr,
                  this.this$0.getAbsoluteX().intValue() + var7 - 8 + 4,
                  this.this$0.getAbsoluteY().intValue() + (int)(var5 - var8),
                  this.this$0.getAbsoluteX().intValue() + var7 + 4,
                  this.this$0.getAbsoluteY().intValue() + (int)(var5 - var10),
                  var1,
                  var2,
                  var3,
                  0.35F,
                  1
               );
            var7 += 8;
            var8 = var10;
         }
      }
   }
}
} // namespace ui
} // namespace zombie
