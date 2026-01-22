#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/util/concurrent/RateLimiter/SleepingStopwatch/1.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class RateLimiter {
public:
   protected RateLimiter$SleepingStopwatch() {
   }

   protected abstract long readMicros();

   protected abstract void sleepMicrosUninterruptibly(long var1);

   public static const RateLimiter$SleepingStopwatch createFromSystemTimer() {
      return std::make_unique<1>();
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
