#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/util/concurrent/AbstractScheduledService/Scheduler/1.h"
#include "com/google/common/util/concurrent/AbstractScheduledService/Scheduler/2.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class AbstractScheduledService {
public:
   public static AbstractScheduledService$Scheduler newFixedDelaySchedule(long initialDelay, long delay, TimeUnit unit) {
      Preconditions.checkNotNull(unit);
      Preconditions.checkArgument(delay > 0L, "delay must be > 0, found %s", delay);
      return std::make_shared<1>(initialDelay, delay, unit);
   }

   public static AbstractScheduledService$Scheduler newFixedRateSchedule(long initialDelay, long period, TimeUnit unit) {
      Preconditions.checkNotNull(unit);
      Preconditions.checkArgument(period > 0L, "period must be > 0, found %s", period);
      return std::make_shared<2>(initialDelay, period, unit);
   }

   abstract Future<?> schedule(AbstractService var1, ScheduledExecutorService var2, Runnable var3);

   private AbstractScheduledService$Scheduler() {
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
