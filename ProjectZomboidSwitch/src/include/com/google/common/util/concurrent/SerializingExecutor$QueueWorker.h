#pragma once
#include <queue>
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


class SerializingExecutor {
public:
   private SerializingExecutor$QueueWorker(SerializingExecutor var1) {
      this.this$0 = var1;
   }

    void run() {
      try {
         this.workOnQueue();
      } catch (Error var5) {
         /* synchronized - TODO: add std::mutex */ (SerializingExecutor.access$100(this.this$0)) {
            SerializingExecutor.access$202(this.this$0, false);
         }

    throw var5;
      }
   }

    void workOnQueue() {
      while (true) {
    Runnable task = nullptr;
         /* synchronized - TODO: add std::mutex */ (SerializingExecutor.access$100(this.this$0)) {
            if (SerializingExecutor.access$300(this.this$0) == 0) {
               task = (Runnable)SerializingExecutor.access$400(this.this$0).poll();
            }

            if (task == nullptr) {
               SerializingExecutor.access$202(this.this$0, false);
               return;
            }
         }

         try {
            task.run();
         } catch (RuntimeException var4) {
            SerializingExecutor.access$500().log(Level.SEVERE, "Exception while executing runnable " + task, (Throwable)var4);
         }
      }
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
