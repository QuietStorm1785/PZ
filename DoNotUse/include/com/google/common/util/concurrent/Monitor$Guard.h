#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/j2objc/annotations/Weak.h"
#include "javax/annotation/concurrent/GuardedBy.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class Monitor {
public:
    const Monitor monitor;
    const Condition condition;
    int waiterCount = 0;
   Monitor$Guard next;

   protected Monitor$Guard(Monitor monitor) {
      this.monitor = (Monitor)Preconditions.checkNotNull(monitor, "monitor");
      this.condition = Monitor.access$000(monitor).newCondition();
   }

   public abstract boolean isSatisfied();
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
