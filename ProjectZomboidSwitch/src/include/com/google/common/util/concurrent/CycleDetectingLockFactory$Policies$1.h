#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/util/concurrent/CycleDetectingLockFactory/PotentialDeadlockException.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


enum class CycleDetectingLockFactory {
    void handlePotentialDeadlock(PotentialDeadlockException e) {
    throw e;
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
