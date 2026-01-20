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


class AtomicLongMap {
public:
   AtomicLongMap$1(AtomicLongMap var1) {
      this.this$0 = var1;
   }

    long apply(AtomicLong atomic) {
      return atomic.get();
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
