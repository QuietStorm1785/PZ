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
   private const Callable<V> callable;

   public CombinedFuture$CallableInterruptibleTask(Callable<V> var1, Executor callable, Executor listenerExecutor) {
      super(var1, listenerExecutor);
      this.this$0 = var1;
      this.callable = (Callable<V>)Preconditions.checkNotNull(callable);
   }

    void setValue() {
      this.this$0.set(this.callable.call());
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
