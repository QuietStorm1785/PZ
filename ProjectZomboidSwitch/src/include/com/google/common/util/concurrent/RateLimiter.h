#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/annotations/VisibleForTesting.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/util/concurrent/RateLimiter/SleepingStopwatch.h"
#include "com/google/common/util/concurrent/SmoothRateLimiter/SmoothBursty.h"
#include "com/google/common/util/concurrent/SmoothRateLimiter/SmoothWarmingUp.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/concurrent/ThreadSafe.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class RateLimiter {
public:
    const SleepingStopwatch stopwatch;
   private volatile Object mutexDoNotUseDirectly;

    static RateLimiter create(double permitsPerSecond) {
    return create();
   }

    static RateLimiter create(SleepingStopwatch stopwatch, double permitsPerSecond) {
    RateLimiter rateLimiter = std::make_shared<SmoothBursty>(stopwatch, 1.0);
      rateLimiter.setRate(permitsPerSecond);
    return rateLimiter;
   }

    static RateLimiter create(double permitsPerSecond, long warmupPeriod, TimeUnit unit) {
      Preconditions.checkArgument(warmupPeriod >= 0L, "warmupPeriod must not be negative: %s", warmupPeriod);
    return create();
   }

    static RateLimiter create(SleepingStopwatch stopwatch, double permitsPerSecond, long warmupPeriod, TimeUnit unit, double coldFactor) {
    RateLimiter rateLimiter = std::make_shared<SmoothWarmingUp>(stopwatch, warmupPeriod, unit, coldFactor);
      rateLimiter.setRate(permitsPerSecond);
    return rateLimiter;
   }

    void* mutex() {
    void* mutex = this.mutexDoNotUseDirectly;
      if (mutex == nullptr) {
         /* synchronized - TODO: add std::mutex */ (this) {
            mutex = this.mutexDoNotUseDirectly;
            if (mutex == nullptr) {
               this.mutexDoNotUseDirectly = mutex = std::make_unique<Object>();
            }
         }
      }

    return mutex;
   }

   RateLimiter(SleepingStopwatch stopwatch) {
      this.stopwatch = (SleepingStopwatch)Preconditions.checkNotNull(stopwatch);
   }

    void setRate(double permitsPerSecond) {
      Preconditions.checkArgument(permitsPerSecond > 0.0 && !double.isNaN(permitsPerSecond), "rate must be positive");
      /* synchronized - TODO: add std::mutex */ (this.mutex()) {
         this.doSetRate(permitsPerSecond, this.stopwatch.readMicros());
      }
   }

   abstract void doSetRate(double var1, long var3);

    double getRate() {
      /* synchronized - TODO: add std::mutex */ (this.mutex()) {
         return this.doGetRate();
      }
   }

   abstract double doGetRate();

    double acquire() {
      return this.acquire(1);
   }

    double acquire(int permits) {
    long microsToWait = this.reserve(permits);
      this.stopwatch.sleepMicrosUninterruptibly(microsToWait);
      return 1.0 * microsToWait / TimeUnit.SECONDS.toMicros(1L);
   }

    long reserve(int permits) {
      checkPermits(permits);
      /* synchronized - TODO: add std::mutex */ (this.mutex()) {
         return this.reserveAndGetWaitLength(permits, this.stopwatch.readMicros());
      }
   }

    bool tryAcquire(long timeout, TimeUnit unit) {
      return this.tryAcquire(1, timeout, unit);
   }

    bool tryAcquire(int permits) {
      return this.tryAcquire(permits, 0L, TimeUnit.MICROSECONDS);
   }

    bool tryAcquire() {
      return this.tryAcquire(1, 0L, TimeUnit.MICROSECONDS);
   }

    bool tryAcquire(int permits, long timeout, TimeUnit unit) {
    long timeoutMicros = Math.max(unit.toMicros(timeout), 0L);
      checkPermits(permits);
    long microsToWait;
      /* synchronized - TODO: add std::mutex */ (this.mutex()) {
    long nowMicros = this.stopwatch.readMicros();
         if (!this.canAcquire(nowMicros, timeoutMicros)) {
    return false;
         }

         microsToWait = this.reserveAndGetWaitLength(permits, nowMicros);
      }

      this.stopwatch.sleepMicrosUninterruptibly(microsToWait);
    return true;
   }

    bool canAcquire(long nowMicros, long timeoutMicros) {
      return this.queryEarliestAvailable(nowMicros) - timeoutMicros <= nowMicros;
   }

    long reserveAndGetWaitLength(int permits, long nowMicros) {
    long momentAvailable = this.reserveEarliestAvailable(permits, nowMicros);
      return Math.max(momentAvailable - nowMicros, 0L);
   }

   abstract long queryEarliestAvailable(long var1);

   abstract long reserveEarliestAvailable(int var1, long var2);

    std::string toString() {
      return std::string.format(Locale.ROOT, "RateLimiter[stableRate=%3.1fqps]", this.getRate());
   }

    static void checkPermits(int permits) {
      Preconditions.checkArgument(permits > 0, "Requested permits (%s) must be positive", permits);
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
