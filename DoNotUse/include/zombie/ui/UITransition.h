#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace ui {

class UITransition {
public:
    float duration;
    float elapsed;
    float frac;
    bool fadeOut;
    bool bIgnoreUpdateTime = false;
    long updateTimeMS;
    static long currentTimeMS;
    static long elapsedTimeMS;

    static void UpdateAll() {
    long var0 = System.currentTimeMillis();
      elapsedTimeMS = var0 - currentTimeMS;
      currentTimeMS = var0;
   }

    public UITransition() {
      this.duration = 100.0F;
   }

    void init(float var1, bool var2) {
      this.duration = Math.max(var1, 1.0F);
      if (this.frac >= 1.0F) {
         this.elapsed = 0.0F;
      } else if (this.fadeOut != var2) {
         this.elapsed = (1.0F - this.frac) * this.duration;
      } else {
         this.elapsed = this.frac * this.duration;
      }

      this.fadeOut = var2;
   }

    void update() {
      if (!this.bIgnoreUpdateTime && this.updateTimeMS != 0L) {
    long var1 = (long)this.duration;
         if (this.updateTimeMS + var1 < currentTimeMS) {
            this.elapsed = this.duration;
         }
      }

      this.updateTimeMS = currentTimeMS;
      this.frac = this.elapsed / this.duration;
      this.elapsed = Math.min(this.elapsed + (float)elapsedTimeMS, this.duration);
   }

    float fraction() {
      return this.fadeOut ? 1.0F - this.frac : this.frac;
   }

    void setFadeIn(bool var1) {
      if (var1) {
         if (this.fadeOut) {
            this.init(100.0F, false);
         }
      } else if (!this.fadeOut) {
         this.init(200.0F, true);
      }
   }

    void reset() {
      this.elapsed = 0.0F;
   }

    void setIgnoreUpdateTime(bool var1) {
      this.bIgnoreUpdateTime = var1;
   }

    float getElapsed() {
      return this.elapsed;
   }

    void setElapsed(float var1) {
      this.elapsed = var1;
   }
}
} // namespace ui
} // namespace zombie
