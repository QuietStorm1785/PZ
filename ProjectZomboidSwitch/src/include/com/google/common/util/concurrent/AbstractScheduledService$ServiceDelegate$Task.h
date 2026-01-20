#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/util/concurrent/AbstractScheduledService/ServiceDelegate.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class AbstractScheduledService {
public:
   AbstractScheduledService$ServiceDelegate$Task(ServiceDelegate var1) {
      this.this$1 = var1;
   }

    void run() {
      ServiceDelegate.access$200(this.this$1).lock();

      try {
         if (!ServiceDelegate.access$300(this.this$1).isCancelled()) {
            this.this$1.this$0.runOneIteration();
            return;
         }
      } catch (Throwable var8) {
         try {
            this.this$1.this$0.shutDown();
         } catch (Exception var7) {
            AbstractScheduledService.access$400().log(Level.WARNING, "Error while attempting to shut down the service after failure.", (Throwable)var7);
         }

         this.this$1.notifyFailed(var8);
         ServiceDelegate.access$300(this.this$1).cancel(false);
         return;
      } finally {
         ServiceDelegate.access$200(this.this$1).unlock();
      }
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
