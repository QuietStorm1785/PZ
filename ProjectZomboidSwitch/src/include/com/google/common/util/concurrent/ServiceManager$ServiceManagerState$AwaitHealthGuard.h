#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/util/concurrent/Monitor/Guard.h"
#include "com/google/common/util/concurrent/Service/State.h"
#include "com/google/common/util/concurrent/ServiceManager/ServiceManagerState.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class ServiceManager {
public:
   ServiceManager$ServiceManagerState$AwaitHealthGuard(ServiceManagerState var1) {
      super(var1.monitor);
      this.this$0 = var1;
   }

    bool isSatisfied() {
      return this.this$0.states.count(State.RUNNING) == this.this$0.numberOfServices
         || this.this$0.states.contains(State.STOPPING)
         || this.this$0.states.contains(State.TERMINATED)
         || this.this$0.states.contains(State.FAILED);
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
