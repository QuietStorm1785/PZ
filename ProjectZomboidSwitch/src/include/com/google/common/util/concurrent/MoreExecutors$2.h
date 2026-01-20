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
   MoreExecutors$2(Executor var1, Supplier var2) {
      this.val$executor = var1;
      this.val$nameSupplier = var2;
   }

    void execute(Runnable command) {
      this.val$executor.execute(Callables.threadRenaming(command, this.val$nameSupplier));
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
