#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Supplier.h"
#include "com/google/common/util/concurrent/Striped/PaddedSemaphore.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class Striped {
public:
   Striped$3(int var1) {
      this.val$permits = var1;
   }

    Semaphore get() {
      return std::make_shared<PaddedSemaphore>(this.val$permits);
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
