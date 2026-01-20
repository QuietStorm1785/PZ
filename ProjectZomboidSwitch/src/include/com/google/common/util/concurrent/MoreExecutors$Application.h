#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/annotations/VisibleForTesting.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/util/concurrent/MoreExecutors/Application/1.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class MoreExecutors {
public:
    ExecutorService getExitingExecutorService(ThreadPoolExecutor executor, long terminationTimeout, TimeUnit timeUnit) {
      MoreExecutors.access$000(executor);
    ExecutorService service = Executors.unconfigurableExecutorService(executor);
      this.addDelayedShutdownHook(service, terminationTimeout, timeUnit);
    return service;
   }

    ScheduledExecutorService getExitingScheduledExecutorService(ScheduledThreadPoolExecutor executor, long terminationTimeout, TimeUnit timeUnit) {
      MoreExecutors.access$000(executor);
    ScheduledExecutorService service = Executors.unconfigurableScheduledExecutorService(executor);
      this.addDelayedShutdownHook(service, terminationTimeout, timeUnit);
    return service;
   }

    void addDelayedShutdownHook(ExecutorService service, long terminationTimeout, TimeUnit timeUnit) {
      Preconditions.checkNotNull(service);
      Preconditions.checkNotNull(timeUnit);
      this.addShutdownHook(MoreExecutors.newThread("DelayedShutdownHook-for-" + service, std::make_shared<1>(this, service, terminationTimeout, timeUnit)));
   }

    ExecutorService getExitingExecutorService(ThreadPoolExecutor executor) {
      return this.getExitingExecutorService(executor, 120L, TimeUnit.SECONDS);
   }

    ScheduledExecutorService getExitingScheduledExecutorService(ScheduledThreadPoolExecutor executor) {
      return this.getExitingScheduledExecutorService(executor, 120L, TimeUnit.SECONDS);
   }

    void addShutdownHook(Thread hook) {
      Runtime.getRuntime().addShutdownHook(hook);
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
