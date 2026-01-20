#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/util/concurrent/CycleDetectingLockFactory/Policy.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


enum class CycleDetectingLockFactory {
   THROW,
   WARN,
   DISABLED;

   private CycleDetectingLockFactory$Policies() {
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
