#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class AbstractScheduledService {
public:
   AbstractScheduledService$1ThreadFactoryImpl(AbstractScheduledService var1) {
      this.this$0 = var1;
   }

    Thread newThread(Runnable runnable) {
      return MoreExecutors.newThread(this.this$0.serviceName(), runnable);
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
