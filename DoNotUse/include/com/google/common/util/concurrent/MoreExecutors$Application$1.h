#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/util/concurrent/MoreExecutors/Application.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class MoreExecutors {
public:
   MoreExecutors$Application$1(Application var1, ExecutorService var2, long var3, TimeUnit var5) {
      this.this$0 = var1;
      this.val$service = var2;
      this.val$terminationTimeout = var3;
      this.val$timeUnit = var5;
   }

    void run() {
      try {
         this.val$service.shutdown();
         this.val$service.awaitTermination(this.val$terminationTimeout, this.val$timeUnit);
      } catch (InterruptedException var2) {
      }
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
