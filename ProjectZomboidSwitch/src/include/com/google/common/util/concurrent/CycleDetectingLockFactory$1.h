#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Lists.h"
#include "com/google/common/util/concurrent/CycleDetectingLockFactory/LockGraphNode.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class CycleDetectingLockFactory {
public:
   protected std::vector<LockGraphNode> initialValue() {
      return Lists.newArrayListWithCapacity(3);
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
