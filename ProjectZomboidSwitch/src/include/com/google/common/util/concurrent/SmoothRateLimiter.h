#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/math/LongMath.h"
#include "com/google/common/util/concurrent/RateLimiter/SleepingStopwatch.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class SmoothRateLimiter : public RateLimiter {
public:
    double storedPermits;
    double maxPermits;
    double stableIntervalMicros;
    long nextFreeTicketMicros = 0L;

    private SmoothRateLimiter(SleepingStopwatch stopwatch) {
      super(stopwatch);
   }

    void doSetRate(double permitsPerSecond, long nowMicros) {
      this.resync(nowMicros);
    double stableIntervalMicros = TimeUnit.SECONDS.toMicros(1L) / permitsPerSecond;
      this.stableIntervalMicros = stableIntervalMicros;
      this.doSetRate(permitsPerSecond, stableIntervalMicros);
   }

   abstract void doSetRate(double var1, double var3);

    double doGetRate() {
      return TimeUnit.SECONDS.toMicros(1L) / this.stableIntervalMicros;
   }

    long queryEarliestAvailable(long nowMicros) {
      return this.nextFreeTicketMicros;
   }

    long reserveEarliestAvailable(int requiredPermits, long nowMicros) {
      this.resync(nowMicros);
    long returnValue = this.nextFreeTicketMicros;
    double storedPermitsToSpend = Math.min((double)requiredPermits, this.storedPermits);
    double freshPermits = requiredPermits - storedPermitsToSpend;
    long waitMicros = this.storedPermitsToWaitTime(this.storedPermits, storedPermitsToSpend) + (long)(freshPermits * this.stableIntervalMicros);
      this.nextFreeTicketMicros = LongMath.saturatedAdd(this.nextFreeTicketMicros, waitMicros);
      this.storedPermits -= storedPermitsToSpend;
    return returnValue;
   }

   abstract long storedPermitsToWaitTime(double var1, double var3);

   abstract double coolDownIntervalMicros();

    void resync(long nowMicros) {
      if (nowMicros > this.nextFreeTicketMicros) {
    double newPermits = (nowMicros - this.nextFreeTicketMicros) / this.coolDownIntervalMicros();
         this.storedPermits = Math.min(this.maxPermits, this.storedPermits + newPermits);
         this.nextFreeTicketMicros = nowMicros;
      }
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
