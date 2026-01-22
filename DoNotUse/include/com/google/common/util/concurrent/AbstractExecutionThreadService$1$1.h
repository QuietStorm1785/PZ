#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Supplier.h"
#include "com/google/common/util/concurrent/AbstractExecutionThreadService/1.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class AbstractExecutionThreadService {
public:
   AbstractExecutionThreadService$1$1(1 var1) {
      this.this$1 = var1;
   }

    std::string get() {
      return this.this$1.this$0.serviceName();
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
