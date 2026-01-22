#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/util/concurrent/AbstractScheduledService/ServiceDelegate/1.h"
#include "com/google/common/util/concurrent/AbstractScheduledService/ServiceDelegate/2.h"
#include "com/google/common/util/concurrent/AbstractScheduledService/ServiceDelegate/3.h"
#include "com/google/common/util/concurrent/AbstractScheduledService/ServiceDelegate/Task.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class AbstractScheduledService {
public:
   private volatile Future<?> runningTask;
   private volatile ScheduledExecutorService executorService;
    const ReentrantLock lock;
    const Runnable task;

   private AbstractScheduledService$ServiceDelegate(AbstractScheduledService var1) {
      this.this$0 = var1;
      this.lock = std::make_unique<ReentrantLock>();
      this.task = std::make_shared<Task>(this);
   }

    void doStart() {
      this.executorService = MoreExecutors.renamingDecorator(this.this$0.executor(), std::make_shared<1>(this));
      this.executorService.execute(std::make_shared<2>(this));
   }

    void doStop() {
      this.runningTask.cancel(false);
      this.executorService.execute(std::make_shared<3>(this));
   }

    std::string toString() {
      return this.this$0;
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
