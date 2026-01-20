#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class AbstractFuture {
public:
    V get() {
      return (V)super.get();
   }

    V get(long timeout, TimeUnit unit) {
      return (V)super.get(timeout, unit);
   }

    bool isDone() {
      return super.isDone();
   }

    bool isCancelled() {
      return super.isCancelled();
   }

    void addListener(Runnable listener, Executor executor) {
      super.addListener(listener, executor);
   }

    bool cancel(bool mayInterruptIfRunning) {
      return super.cancel(mayInterruptIfRunning);
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
