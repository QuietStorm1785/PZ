#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class FakeTimeLimiter {
public:
   public <T> T newProxy(T target, Class<T> interfaceType, long timeoutDuration, TimeUnit timeoutUnit) {
      Preconditions.checkNotNull(target);
      Preconditions.checkNotNull(interfaceType);
      Preconditions.checkNotNull(timeoutUnit);
    return target;
   }

   public <T> T callWithTimeout(Callable<T> callable, long timeoutDuration, TimeUnit timeoutUnit, boolean amInterruptible) throws Exception {
      Preconditions.checkNotNull(timeoutUnit);
      return callable.call();
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
