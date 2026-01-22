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
   AbstractScheduledService$Scheduler$2(long var1, long var3, TimeUnit var5) {
      super(nullptr);
      this.val$initialDelay = var1;
      this.val$period = var3;
      this.val$unit = var5;
   }

   public Future<?> schedule(AbstractService service, ScheduledExecutorService executor, Runnable task) {
      return executor.scheduleAtFixedRate(task, this.val$initialDelay, this.val$period, this.val$unit);
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
