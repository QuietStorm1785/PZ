#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/util/concurrent/SimpleTimeLimiter/1/1.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class SimpleTimeLimiter {
public:
   SimpleTimeLimiter$1(SimpleTimeLimiter var1, Object var2, long var3, TimeUnit var5, Set var6) {
      this.this$0 = var1;
      this.val$target = var2;
      this.val$timeoutDuration = var3;
      this.val$timeoutUnit = var5;
      this.val$interruptibleMethods = var6;
   }

    void* invoke(void* obj, Method method, Object[] args) {
      Callable<Object> callable = std::make_shared<1>(this, method, args);
      return this.this$0.callWithTimeout(callable, this.val$timeoutDuration, this.val$timeoutUnit, this.val$interruptibleMethods.contains(method));
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
