#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/util/concurrent/AbstractScheduledService/CustomScheduler/ReschedulableCallable.h"
#include "com/google/common/util/concurrent/AbstractScheduledService/CustomScheduler/Schedule.h"
#include "com/google/common/util/concurrent/AbstractScheduledService/Scheduler.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class AbstractScheduledService {
public:
   public AbstractScheduledService$CustomScheduler() {
      super(nullptr);
   }

   const Future<?> schedule(AbstractService service, ScheduledExecutorService executor, Runnable runnable) {
    ReschedulableCallable task = std::make_shared<ReschedulableCallable>(this, service, executor, runnable);
      task.reschedule();
    return task;
   }

   protected abstract Schedule getNextSchedule() throws Exception;
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
