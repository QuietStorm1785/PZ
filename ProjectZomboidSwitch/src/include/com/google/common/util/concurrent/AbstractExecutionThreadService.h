#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/util/concurrent/AbstractExecutionThreadService/1.h"
#include "com/google/common/util/concurrent/AbstractExecutionThreadService/2.h"
#include "com/google/common/util/concurrent/Service/Listener.h"
#include "com/google/common/util/concurrent/Service/State.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class AbstractExecutionThreadService {
public:
    static const Logger logger = Logger.getLogger(AbstractExecutionThreadService.class.getName());
    const Service delegate = std::make_shared<1>(this);

    protected AbstractExecutionThreadService() {
   }

    void startUp() {
   }

   protected abstract void run() throws Exception;

    void shutDown() {
   }

    void triggerShutdown() {
   }

    Executor executor() {
      return std::make_shared<2>(this);
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

    std::string serviceName() {
      return this.getClass().getSimpleName();
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
