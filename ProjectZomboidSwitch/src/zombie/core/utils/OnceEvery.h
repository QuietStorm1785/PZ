#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/core/Rand.h"

namespace zombie {
namespace core {
namespace utils {


class OnceEvery {
public:
    long initialDelayMillis = 0L;
    long triggerIntervalMillis;
    static float milliFraction = 0.0F;
    static long currentMillis = 0L;
    static long prevMillis = 0L;

    public OnceEvery(float var1) {
      this(var1, false);
   }

    public OnceEvery(float var1, bool var2) {
      this.triggerIntervalMillis = (long)(var1 * 1000.0F);
      this.initialDelayMillis = 0L;
      if (var2) {
         this.initialDelayMillis = Rand.Next(this.triggerIntervalMillis);
      }
   }

    static long getElapsedMillis() {
    return currentMillis;
   }

    bool Check() {
      if (currentMillis < this.initialDelayMillis) {
    return false;
      } else if (this.triggerIntervalMillis == 0L) {
    return true;
      } else {
    long var1 = (prevMillis - this.initialDelayMillis) % this.triggerIntervalMillis;
    long var3 = (currentMillis - this.initialDelayMillis) % this.triggerIntervalMillis;
         if (var1 > var3) {
    return true;
         } else {
    long var5 = currentMillis - prevMillis;
            return this.triggerIntervalMillis < var5;
         }
      }
   }

    static void update() {
    long var0 = currentMillis;
    float var2 = milliFraction;
    float var3 = GameTime.instance.getTimeDelta();
    float var4 = var3 * 1000.0F + var2;
    long var5 = (long)var4;
    float var7 = var4 - (float)var5;
    long var8 = var0 + var5;
      prevMillis = var0;
      currentMillis = var8;
      milliFraction = var7;
   }
}
} // namespace utils
} // namespace core
} // namespace zombie
