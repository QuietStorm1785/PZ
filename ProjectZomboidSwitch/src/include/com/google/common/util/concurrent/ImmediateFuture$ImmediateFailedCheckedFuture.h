#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Preconditions.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class ImmediateFuture {
public:
    const X thrown;

   ImmediateFuture$ImmediateFailedCheckedFuture(X thrown) {
      this.thrown = thrown;
   }

    V get() {
      throw ExecutionException(this.thrown);
   }

    V checkedGet() {
      throw this.thrown;
   }

    V checkedGet(long timeout, TimeUnit unit) {
      Preconditions.checkNotNull(unit);
      throw this.thrown;
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
