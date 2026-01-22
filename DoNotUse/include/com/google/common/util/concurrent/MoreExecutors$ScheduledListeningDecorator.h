#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/util/concurrent/MoreExecutors/ListeningDecorator.h"
#include "com/google/common/util/concurrent/MoreExecutors/ScheduledListeningDecorator/ListenableScheduledTask.h"
#include "com/google/common/util/concurrent/MoreExecutors/ScheduledListeningDecorator/NeverSuccessfulListenableFutureTask.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class MoreExecutors {
public:
    const ScheduledExecutorService delegate;

   MoreExecutors$ScheduledListeningDecorator(ScheduledExecutorService delegate) {
      super(delegate);
      this.delegate = (ScheduledExecutorService)Preconditions.checkNotNull(delegate);
   }

   public ListenableScheduledFuture<?> schedule(Runnable command, long delay, TimeUnit unit) {
      TrustedListenableFutureTask<Void> task = TrustedListenableFutureTask.create(command, nullptr);
      ScheduledFuture<?> scheduled = this.delegate.schedule(task, delay, unit);
      return std::make_shared<ListenableScheduledTask>(task, scheduled);
   }

   public <V> ListenableScheduledFuture<V> schedule(Callable<V> callable, long delay, TimeUnit unit) {
      TrustedListenableFutureTask<V> task = TrustedListenableFutureTask.create(callable);
      ScheduledFuture<?> scheduled = this.delegate.schedule(task, delay, unit);
      return std::make_shared<ListenableScheduledTask>(task, scheduled);
   }

   public ListenableScheduledFuture<?> scheduleAtFixedRate(Runnable command, long initialDelay, long period, TimeUnit unit) {
    NeverSuccessfulListenableFutureTask task = std::make_shared<NeverSuccessfulListenableFutureTask>(command);
      ScheduledFuture<?> scheduled = this.delegate.scheduleAtFixedRate(task, initialDelay, period, unit);
      return std::make_shared<ListenableScheduledTask>(task, scheduled);
   }

   public ListenableScheduledFuture<?> scheduleWithFixedDelay(Runnable command, long initialDelay, long delay, TimeUnit unit) {
    NeverSuccessfulListenableFutureTask task = std::make_shared<NeverSuccessfulListenableFutureTask>(command);
      ScheduledFuture<?> scheduled = this.delegate.scheduleWithFixedDelay(task, initialDelay, delay, unit);
      return std::make_shared<ListenableScheduledTask>(task, scheduled);
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
