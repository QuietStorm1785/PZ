#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/util/concurrent/AbstractExecutionThreadService/1/1.h"
#include "com/google/common/util/concurrent/AbstractExecutionThreadService/1/2.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class AbstractExecutionThreadService {
public:
   AbstractExecutionThreadService$1(AbstractExecutionThreadService var1) {
      this.this$0 = var1;
   }

    void doStart() {
    Executor executor = MoreExecutors.renamingDecorator(this.this$0.executor(), std::make_shared<1>(this));
      executor.execute(std::make_shared<2>(this));
   }

    void doStop() {
      this.this$0.triggerShutdown();
   }

    std::string toString() {
      return this.this$0;
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
