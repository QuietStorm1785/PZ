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


class AbstractExecutionThreadService {
public:
   AbstractExecutionThreadService$2(AbstractExecutionThreadService var1) {
      this.this$0 = var1;
   }

    void execute(Runnable command) {
      MoreExecutors.newThread(this.this$0.serviceName(), command).start();
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
