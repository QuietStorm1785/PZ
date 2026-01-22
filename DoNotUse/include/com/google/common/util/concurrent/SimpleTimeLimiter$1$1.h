#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/util/concurrent/SimpleTimeLimiter/1.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class SimpleTimeLimiter {
public:
   SimpleTimeLimiter$1$1(1 var1, Method var2, Object[] var3) {
      this.this$1 = var1;
      this.val$method = var2;
      this.val$args = var3;
   }

    void* call() {
      try {
         return this.val$method.invoke(this.this$1.val$target, this.val$args);
      } catch (InvocationTargetException var2) {
         throw SimpleTimeLimiter.access$000(var2, false);
      }
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
