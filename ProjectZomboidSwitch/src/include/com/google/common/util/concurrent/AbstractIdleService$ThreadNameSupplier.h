#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Supplier.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class AbstractIdleService {
public:
   private AbstractIdleService$ThreadNameSupplier(AbstractIdleService var1) {
      this.this$0 = var1;
   }

    std::string get() {
      return this.this$0.serviceName() + " " + this.this$0.state();
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
