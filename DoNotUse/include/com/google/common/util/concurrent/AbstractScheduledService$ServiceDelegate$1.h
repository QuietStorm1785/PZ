#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Supplier.h"
#include "com/google/common/util/concurrent/AbstractScheduledService/ServiceDelegate.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class AbstractScheduledService {
public:
   AbstractScheduledService$ServiceDelegate$1(ServiceDelegate var1) {
      this.this$1 = var1;
   }

    std::string get() {
      return this.this$1.this$0.serviceName() + " " + this.this$1.state();
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
