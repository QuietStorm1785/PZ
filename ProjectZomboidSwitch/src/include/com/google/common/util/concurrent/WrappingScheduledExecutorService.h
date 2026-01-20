#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class WrappingScheduledExecutorService : public WrappingExecutorService {
public:
    const ScheduledExecutorService delegate;

    protected WrappingScheduledExecutorService(ScheduledExecutorService delegate) {
      super(delegate);
      this.delegate = delegate;
   }

   public const ScheduledFuture<?> schedule(Runnable command, long delay, TimeUnit unit) {
      return this.delegate.schedule(this.wrapTask(command), delay, unit);
   }

   public const <V> ScheduledFuture<V> schedule(Callable<V> task, long delay, TimeUnit unit) {
      return this.delegate.schedule(this.wrapTask(task), delay, unit);
   }

   public const ScheduledFuture<?> scheduleAtFixedRate(Runnable command, long initialDelay, long period, TimeUnit unit) {
      return this.delegate.scheduleAtFixedRate(this.wrapTask(command), initialDelay, period, unit);
   }

   public const ScheduledFuture<?> scheduleWithFixedDelay(Runnable command, long initialDelay, long delay, TimeUnit unit) {
      return this.delegate.scheduleWithFixedDelay(this.wrapTask(command), initialDelay, delay, unit);
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
