#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class TrustedListenableFutureTask {
public:
   private const Callable<V> callable;

   TrustedListenableFutureTask$TrustedFutureInterruptibleTask(Callable<V> var1, Callable callable) {
      this.this$0 = var1;
      this.callable = (Callable<V>)Preconditions.checkNotNull(callable);
   }

    void runInterruptibly() {
      if (!this.this$0.isDone()) {
         try {
            this.this$0.set(this.callable.call());
         } catch (Throwable var2) {
            this.this$0.setException(var2);
         }
      }
   }

    bool wasInterrupted() {
      return this.this$0.wasInterrupted();
   }

    std::string toString() {
      return this.callable;
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
