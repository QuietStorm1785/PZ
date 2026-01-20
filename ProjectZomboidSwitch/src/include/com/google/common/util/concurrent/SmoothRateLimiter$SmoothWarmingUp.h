#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/util/concurrent/RateLimiter/SleepingStopwatch.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class SmoothRateLimiter {
public:
    const long warmupPeriodMicros;
    double slope;
    double thresholdPermits;
    double coldFactor;

   SmoothRateLimiter$SmoothWarmingUp(SleepingStopwatch stopwatch, long warmupPeriod, TimeUnit timeUnit, double coldFactor) {
      super(stopwatch, nullptr);
      this.warmupPeriodMicros = timeUnit.toMicros(warmupPeriod);
      this.coldFactor = coldFactor;
   }

    void doSetRate(double permitsPerSecond, double stableIntervalMicros) {
    double oldMaxPermits = this.maxPermits;
    double coldIntervalMicros = stableIntervalMicros * this.coldFactor;
      this.thresholdPermits = 0.5 * this.warmupPeriodMicros / stableIntervalMicros;
      this.maxPermits = this.thresholdPermits + 2.0 * this.warmupPeriodMicros / (stableIntervalMicros + coldIntervalMicros);
      this.slope = (coldIntervalMicros - stableIntervalMicros) / (this.maxPermits - this.thresholdPermits);
      if (oldMaxPermits == double.POSITIVE_INFINITY) {
         this.storedPermits = 0.0;
      } else {
         this.storedPermits = oldMaxPermits == 0.0 ? this.maxPermits : this.storedPermits * this.maxPermits / oldMaxPermits;
      }
   }

    long storedPermitsToWaitTime(double storedPermits, double permitsToTake) {
    double availablePermitsAboveThreshold = storedPermits - this.thresholdPermits;
    long micros = 0L;
      if (availablePermitsAboveThreshold > 0.0) {
    double permitsAboveThresholdToTake = Math.min(availablePermitsAboveThreshold, permitsToTake);
    double length = this.permitsToTime(availablePermitsAboveThreshold) + this.permitsToTime(availablePermitsAboveThreshold - permitsAboveThresholdToTake);
         micros = (long)(permitsAboveThresholdToTake * length / 2.0);
         permitsToTake -= permitsAboveThresholdToTake;
      }

      return (long)(micros + this.stableIntervalMicros * permitsToTake);
   }

    double permitsToTime(double permits) {
      return this.stableIntervalMicros + permits * this.slope;
   }

    double coolDownIntervalMicros() {
      return this.warmupPeriodMicros / this.maxPermits;
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
