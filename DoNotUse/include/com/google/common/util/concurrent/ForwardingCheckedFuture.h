#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class ForwardingCheckedFuture {
public:
    V checkedGet() {
      return (V)this.delegate().checkedGet();
   }

    V checkedGet(long timeout, TimeUnit unit) {
      return (V)this.delegate().checkedGet(timeout, unit);
   }

   protected abstract CheckedFuture<V, X> delegate();
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
