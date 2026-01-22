#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/util/concurrent/ForwardingListenableFuture/SimpleForwardingListenableFuture.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class MoreExecutors {
public:
   : public SimpleForwardingListenableFuture<V>
   , public ListenableScheduledFuture<V> {
   private const ScheduledFuture<?> scheduledDelegate;

   public MoreExecutors$ScheduledListeningDecorator$ListenableScheduledTask(ListenableFuture<V> listenableDelegate, ScheduledFuture<?> scheduledDelegate) {
      super(listenableDelegate);
      this.scheduledDelegate = scheduledDelegate;
   }

    bool cancel(bool mayInterruptIfRunning) {
    bool cancelled = super.cancel(mayInterruptIfRunning);
      if (cancelled) {
         this.scheduledDelegate.cancel(mayInterruptIfRunning);
      }

    return cancelled;
   }

    long getDelay(TimeUnit unit) {
      return this.scheduledDelegate.getDelay(unit);
   }

    int compareTo(Delayed other) {
      return this.scheduledDelegate.compareTo(other);
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
