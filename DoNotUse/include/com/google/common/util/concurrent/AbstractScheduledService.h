#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/util/concurrent/AbstractScheduledService/1.h"
#include "com/google/common/util/concurrent/AbstractScheduledService/1ThreadFactoryImpl.h"
#include "com/google/common/util/concurrent/AbstractScheduledService/Scheduler.h"
#include "com/google/common/util/concurrent/AbstractScheduledService/ServiceDelegate.h"
#include "com/google/common/util/concurrent/Service/Listener.h"
#include "com/google/common/util/concurrent/Service/State.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class AbstractScheduledService {
public:
    static const Logger logger = Logger.getLogger(AbstractScheduledService.class.getName());
    const AbstractService delegate = std::make_shared<ServiceDelegate>(this, nullptr);

    protected AbstractScheduledService() {
   }

   protected abstract void runOneIteration() throws Exception;

    void startUp() {
   }

    void shutDown() {
   }

   protected abstract Scheduler scheduler();

    ScheduledExecutorService executor() {
    ScheduledExecutorService executor = Executors.newSingleThreadScheduledExecutor(std::make_shared<1ThreadFactoryImpl>(this));
      this.addListener(std::make_shared<1>(this, executor), MoreExecutors.directExecutor());
    return executor;
   }

    std::string serviceName() {
      return this.getClass().getSimpleName();
   }

    std::string toString() {
      return this.serviceName() + " [" + this.state() + "]";
   }

    bool isRunning() {
      return this.delegate.isRunning();
   }

    State state() {
      return this.delegate.state();
   }

    void addListener(Listener listener, Executor executor) {
      this.delegate.addListener(listener, executor);
   }

    std::exception failureCause() {
      return this.delegate.failureCause();
   }

    Service startAsync() {
      this.delegate.startAsync();
    return this;
   }

    Service stopAsync() {
      this.delegate.stopAsync();
    return this;
   }

    void awaitRunning() {
      this.delegate.awaitRunning();
   }

    void awaitRunning(long timeout, TimeUnit unit) {
      this.delegate.awaitRunning(timeout, unit);
   }

    void awaitTerminated() {
      this.delegate.awaitTerminated();
   }

    void awaitTerminated(long timeout, TimeUnit unit) {
      this.delegate.awaitTerminated(timeout, unit);
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
