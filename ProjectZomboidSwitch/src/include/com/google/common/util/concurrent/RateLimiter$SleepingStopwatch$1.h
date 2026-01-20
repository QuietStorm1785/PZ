#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Stopwatch.h"
#include "com/google/common/util/concurrent/RateLimiter/SleepingStopwatch.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class RateLimiter {
public:
    const Stopwatch stopwatch = Stopwatch.createStarted();

    long readMicros() {
      return this.stopwatch.elapsed(TimeUnit.MICROSECONDS);
   }

    void sleepMicrosUninterruptibly(long micros) {
      if (micros > 0L) {
         Uninterruptibles.sleepUninterruptibly(micros, TimeUnit.MICROSECONDS);
      }
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
