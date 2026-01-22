#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Throwables.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class WrappingExecutorService {
public:
   WrappingExecutorService$1(WrappingExecutorService var1, Callable var2) {
      this.this$0 = var1;
      this.val$wrapped = var2;
   }

    void run() {
      try {
         this.val$wrapped.call();
      } catch (Exception var2) {
         Throwables.throwIfUnchecked(var2);
         throw RuntimeException(var2);
      }
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
