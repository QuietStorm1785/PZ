#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/util/concurrent/AbstractScheduledService/ServiceDelegate.h"
#include "com/google/common/util/concurrent/Service/State.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class AbstractScheduledService {
public:
   AbstractScheduledService$ServiceDelegate$3(ServiceDelegate var1) {
      this.this$1 = var1;
   }

    void run() {
      try {
         ServiceDelegate.access$200(this.this$1).lock();

         label43: {
            try {
               if (this.this$1.state() == State.STOPPING) {
                  this.this$1.this$0.shutDown();
    break label43;
               }
            } finally {
               ServiceDelegate.access$200(this.this$1).unlock();
            }

            return;
         }

         this.this$1.notifyStopped();
      } catch (Throwable var5) {
         this.this$1.notifyFailed(var5);
      }
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
