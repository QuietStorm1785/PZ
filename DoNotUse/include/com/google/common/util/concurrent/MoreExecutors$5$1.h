#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/util/concurrent/MoreExecutors/5.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class MoreExecutors {
public:
   MoreExecutors$5$1(5 var1, Runnable var2) {
      this.this$0 = var1;
      this.val$command = var2;
   }

    void run() {
      this.this$0.thrownFromDelegate = false;
      this.val$command.run();
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
