#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/util/concurrent/RateLimiter/SleepingStopwatch.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class SmoothRateLimiter {
public:
    const double maxBurstSeconds;

   SmoothRateLimiter$SmoothBursty(SleepingStopwatch stopwatch, double maxBurstSeconds) {
      super(stopwatch, nullptr);
      this.maxBurstSeconds = maxBurstSeconds;
   }

    void doSetRate(double permitsPerSecond, double stableIntervalMicros) {
    double oldMaxPermits = this.maxPermits;
      this.maxPermits = this.maxBurstSeconds * permitsPerSecond;
      if (oldMaxPermits == double.POSITIVE_INFINITY) {
         this.storedPermits = this.maxPermits;
      } else {
         this.storedPermits = oldMaxPermits == 0.0 ? 0.0 : this.storedPermits * this.maxPermits / oldMaxPermits;
      }
   }

    long storedPermitsToWaitTime(double storedPermits, double permitsToTake) {
    return 0L;
   }

    double coolDownIntervalMicros() {
      return this.stableIntervalMicros;
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
