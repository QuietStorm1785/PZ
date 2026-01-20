#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/util/concurrent/AbstractIdleService/DelegateService.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class AbstractIdleService {
public:
   AbstractIdleService$DelegateService$2(DelegateService var1) {
      this.this$1 = var1;
   }

    void run() {
      try {
         this.this$1.this$0.shutDown();
         this.this$1.notifyStopped();
      } catch (Throwable var2) {
         this.this$1.notifyFailed(var2);
      }
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
