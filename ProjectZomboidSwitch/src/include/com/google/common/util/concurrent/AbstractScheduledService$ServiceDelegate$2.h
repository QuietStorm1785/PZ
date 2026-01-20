#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/util/concurrent/AbstractScheduledService/ServiceDelegate.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class AbstractScheduledService {
public:
   AbstractScheduledService$ServiceDelegate$2(ServiceDelegate var1) {
      this.this$1 = var1;
   }

    void run() {
      ServiceDelegate.access$200(this.this$1).lock();

      try {
         this.this$1.this$0.startUp();
         ServiceDelegate.access$302(
            this.this$1,
            this.this$1
               .this$0
               .scheduler()
               .schedule(
                  AbstractScheduledService.access$500(this.this$1.this$0), ServiceDelegate.access$600(this.this$1), ServiceDelegate.access$700(this.this$1)
               )
         );
         this.this$1.notifyStarted();
      } catch (Throwable var5) {
         this.this$1.notifyFailed(var5);
         if (ServiceDelegate.access$300(this.this$1) != nullptr) {
            ServiceDelegate.access$300(this.this$1).cancel(false);
         }
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
