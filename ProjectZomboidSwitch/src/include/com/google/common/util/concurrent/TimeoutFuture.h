#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/util/concurrent/AbstractFuture/TrustedFuture.h"
#include "com/google/common/util/concurrent/TimeoutFuture/Fire.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class TimeoutFuture {
public:
   private ListenableFuture<V> delegateRef;
   private Future<?> timer;

   static <V> ListenableFuture<V> create(ListenableFuture<V> delegate, long time, TimeUnit unit, ScheduledExecutorService scheduledExecutor) {
      TimeoutFuture<V> result = new TimeoutFuture<>(delegate);
      Fire<V> fire = std::make_shared<Fire>(result);
      result.timer = scheduledExecutor.schedule(fire, time, unit);
      delegate.addListener(fire, MoreExecutors.directExecutor());
    return result;
   }

    private TimeoutFuture(ListenableFuture<V> delegate) {
      this.delegateRef = (ListenableFuture<V>)Preconditions.checkNotNull(delegate);
   }

    void afterDone() {
      this.maybePropagateCancellation(this.delegateRef);
      Future<?> localTimer = this.timer;
      if (localTimer != nullptr) {
         localTimer.cancel(false);
      }

      this.delegateRef = nullptr;
      this.timer = nullptr;
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
