#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/base/Preconditions.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class AbstractScheduledService {
public:
    const long delay;
    const TimeUnit unit;

   public AbstractScheduledService$CustomScheduler$Schedule(long delay, TimeUnit unit) {
      this.delay = delay;
      this.unit = (TimeUnit)Preconditions.checkNotNull(unit);
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
