#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/util/concurrent/AbstractScheduledService/Scheduler.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class AbstractScheduledService {
public:
   AbstractScheduledService$Scheduler$1(long var1, long var3, TimeUnit var5) {
      super(nullptr);
      this.val$initialDelay = var1;
      this.val$delay = var3;
      this.val$unit = var5;
   }

   public Future<?> schedule(AbstractService service, ScheduledExecutorService executor, Runnable task) {
      return executor.scheduleWithFixedDelay(task, this.val$initialDelay, this.val$delay, this.val$unit);
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
