#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/util/concurrent/AbstractExecutionThreadService/1.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class AbstractExecutionThreadService {
public:
   AbstractExecutionThreadService$1$2(1 var1) {
      this.this$1 = var1;
   }

    void run() {
      try {
         this.this$1.this$0.startUp();
         this.this$1.notifyStarted();
         if (this.this$1.isRunning()) {
            try {
               this.this$1.this$0.run();
            } catch (Throwable var4) {
               try {
                  this.this$1.this$0.shutDown();
               } catch (Exception var3) {
                  AbstractExecutionThreadService.access$000()
                     .log(Level.WARNING, "Error while attempting to shut down the service after failure.", (Throwable)var3);
               }

               this.this$1.notifyFailed(var4);
               return;
            }
         }

         this.this$1.this$0.shutDown();
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
