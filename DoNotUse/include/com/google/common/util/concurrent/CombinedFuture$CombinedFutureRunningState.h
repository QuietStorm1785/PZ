#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/ImmutableCollection.h"
#include "com/google/common/util/concurrent/CombinedFuture/CombinedFutureInterruptibleTask.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class CombinedFuture {
public:
   private CombinedFuture<V>.CombinedFutureInterruptibleTask task;

   CombinedFuture$CombinedFutureRunningState(
      ImmutableCollection<? : public ListenableFuture<? : public Object>> var1,
      boolean futures,
      CombinedFuture<V>.CombinedFutureInterruptibleTask allMustSucceed,
      CombinedFutureInterruptibleTask task
   ) {
      super(var1, futures, allMustSucceed, false);
      this.this$0 = var1;
      this.task = task;
   }

    void collectOneValue(bool allMustSucceed, int index, @Nullable Object) {
   }

    void handleAllCompleted() {
      CombinedFuture<V>.CombinedFutureInterruptibleTask localTask = this.task;
      if (localTask != nullptr) {
         localTask.execute();
      } else {
         Preconditions.checkState(this.this$0.isDone());
      }
   }

    void releaseResourcesAfterFailure() {
      super.releaseResourcesAfterFailure();
      this.task = nullptr;
   }

    void interruptTask() {
      CombinedFuture<V>.CombinedFutureInterruptibleTask localTask = this.task;
      if (localTask != nullptr) {
         localTask.interruptTask();
      }
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
