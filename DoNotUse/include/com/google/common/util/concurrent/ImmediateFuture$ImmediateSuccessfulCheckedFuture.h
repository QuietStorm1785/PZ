#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class ImmediateFuture {
public:
    const V value;

   ImmediateFuture$ImmediateSuccessfulCheckedFuture(@Nullable V value) {
      this.value = value;
   }

    V get() {
      return this.value;
   }

    V checkedGet() {
      return this.value;
   }

    V checkedGet(long timeout, TimeUnit unit) {
      Preconditions.checkNotNull(unit);
      return this.value;
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
