#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace utils {

class UpdateLimit {
public:
    long delay;
    long last;
    long lastPeriod;

    public UpdateLimit(long var1) {
      this.delay = var1;
      this.last = System.currentTimeMillis();
      this.lastPeriod = this.last;
   }

    public UpdateLimit(long var1, long var3) {
      this.delay = var1;
      this.last = System.currentTimeMillis() - var3;
      this.lastPeriod = this.last;
   }

    void BlockCheck() {
      this.last = System.currentTimeMillis() + this.delay;
   }

    void Reset(long var1) {
      this.delay = var1;
      this.Reset();
   }

    void Reset() {
      this.last = System.currentTimeMillis();
      this.lastPeriod = System.currentTimeMillis();
   }

    void setUpdatePeriod(long var1) {
      this.delay = var1;
   }

    void setSmoothUpdatePeriod(long var1) {
      this.delay = (long)((float)this.delay + 0.1F * (float)(var1 - this.delay));
   }

    bool Check() {
    long var1 = System.currentTimeMillis();
      if (var1 - this.last > this.delay) {
         if (var1 - this.last > 3L * this.delay) {
            this.last = var1;
         } else {
            this.last = this.last + this.delay;
         }

    return true;
      } else {
    return false;
      }
   }

    long getLast() {
      return this.last;
   }

    void updateTimePeriod() {
    long var1 = System.currentTimeMillis();
      if (var1 - this.last > this.delay) {
         if (var1 - this.last > 3L * this.delay) {
            this.last = var1;
         } else {
            this.last = this.last + this.delay;
         }
      }

      this.lastPeriod = var1;
   }

    double getTimePeriod() {
      return Math.min(((double)System.currentTimeMillis() - this.lastPeriod) / this.delay, 1.0);
   }

    long getDelay() {
      return this.delay;
   }
}
} // namespace utils
} // namespace core
} // namespace zombie
