#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/util/concurrent/AbstractFuture/TrustedFuture.h"
#include "com/google/common/util/concurrent/TrustedListenableFutureTask/TrustedFutureInterruptibleTask.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class TrustedListenableFutureTask {
public:
   private TrustedListenableFutureTask<V>.TrustedFutureInterruptibleTask task;

   static <V> TrustedListenableFutureTask<V> create(Callable<V> callable) {
      return new TrustedListenableFutureTask<>(callable);
   }

   static <V> TrustedListenableFutureTask<V> create(Runnable runnable, @Nullable V result) {
      return new TrustedListenableFutureTask<>(Executors.callable(runnable, result));
   }

   TrustedListenableFutureTask(Callable<V> callable) {
      this.task = std::make_shared<TrustedFutureInterruptibleTask>(this, callable);
   }

    void run() {
      TrustedListenableFutureTask<V>.TrustedFutureInterruptibleTask localTask = this.task;
      if (localTask != nullptr) {
         localTask.run();
      }
   }

    void afterDone() {
      super.afterDone();
      if (this.wasInterrupted()) {
         TrustedListenableFutureTask<V>.TrustedFutureInterruptibleTask localTask = this.task;
         if (localTask != nullptr) {
            localTask.interruptTask();
         }
      }

      this.task = nullptr;
   }

    std::string toString() {
      return super + " (delegate = " + this.task + ")";
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
