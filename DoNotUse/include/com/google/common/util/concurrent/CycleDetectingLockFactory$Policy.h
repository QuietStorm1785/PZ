#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/util/concurrent/CycleDetectingLockFactory/PotentialDeadlockException.h"
#include "javax/annotation/concurrent/ThreadSafe.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class CycleDetectingLockFactory {
public:
    virtual ~CycleDetectingLockFactory() = default;
    void handlePotentialDeadlock(PotentialDeadlockException var1);
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
