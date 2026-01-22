#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace vehicles {

class PolygonalMap2 {
public:
    int fps = 20;
    long period = 1000000000L / this.fps;
    long excess;
    long beforeTime = System.nanoTime();
    long overSleepTime = 0L;

   private PolygonalMap2$Sync() {
   }

    void begin() {
      this.beforeTime = System.nanoTime();
      this.overSleepTime = 0L;
   }

    void startFrame() {
      this.excess = 0L;
   }

    void endFrame() {
    long var1 = System.nanoTime();
    long var3 = var1 - this.beforeTime;
    long var5 = this.period - var3 - this.overSleepTime;
      if (var5 > 0L) {
         try {
            Thread.sleep(var5 / 1000000L);
         } catch (InterruptedException var8) {
         }

         this.overSleepTime = System.nanoTime() - var1 - var5;
      } else {
         this.excess -= var5;
         this.overSleepTime = 0L;
      }

      this.beforeTime = System.nanoTime();
   }
}
} // namespace vehicles
} // namespace zombie
