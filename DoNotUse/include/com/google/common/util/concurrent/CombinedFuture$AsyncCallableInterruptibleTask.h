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


class CombinedFuture {
public:
   private const AsyncCallable<V> callable;

   public CombinedFuture$AsyncCallableInterruptibleTask(AsyncCallable<V> var1, Executor callable, Executor listenerExecutor) {
      super(var1, listenerExecutor);
      this.this$0 = var1;
      this.callable = (AsyncCallable<V>)Preconditions.checkNotNull(callable);
   }

    void setValue() {
      this.this$0.setFuture(this.callable.call());
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
