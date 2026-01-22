#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Supplier.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class MoreExecutors {
public:
   MoreExecutors$4(ScheduledExecutorService x0, Supplier var2) {
      super(x0);
      this.val$nameSupplier = var2;
   }

   protected <T> Callable<T> wrapTask(Callable<T> callable) {
      return Callables.threadRenaming(callable, this.val$nameSupplier);
   }

    Runnable wrapTask(Runnable command) {
      return Callables.threadRenaming(command, this.val$nameSupplier);
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
