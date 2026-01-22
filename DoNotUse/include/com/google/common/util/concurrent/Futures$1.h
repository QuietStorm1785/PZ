#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Function.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class Futures {
public:
   Futures$1(Future var1, Function var2) {
      this.val$input = var1;
      this.val$function = var2;
   }

    bool cancel(bool mayInterruptIfRunning) {
      return this.val$input.cancel(mayInterruptIfRunning);
   }

    bool isCancelled() {
      return this.val$input.isCancelled();
   }

    bool isDone() {
      return this.val$input.isDone();
   }

    O get() {
      return (O)this.applyTransformation(this.val$input.get());
   }

    O get(long timeout, TimeUnit unit) {
      return (O)this.applyTransformation(this.val$input.get(timeout, unit));
   }

    O applyTransformation(I input) {
      try {
         return (O)this.val$function.apply(input);
      } catch (Throwable var3) {
         throw ExecutionException(var3);
      }
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
