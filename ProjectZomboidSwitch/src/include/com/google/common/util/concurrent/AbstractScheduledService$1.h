#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/util/concurrent/Service/Listener.h"
#include "com/google/common/util/concurrent/Service/State.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class AbstractScheduledService {
public:
   AbstractScheduledService$1(AbstractScheduledService var1, ScheduledExecutorService var2) {
      this.this$0 = var1;
      this.val$executor = var2;
   }

    void terminated(State from) {
      this.val$executor.shutdown();
   }

    void failed(State from, std::exception failure) {
      this.val$executor.shutdown();
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
