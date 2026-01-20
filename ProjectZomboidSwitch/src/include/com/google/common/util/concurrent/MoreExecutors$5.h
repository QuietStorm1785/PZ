#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/util/concurrent/MoreExecutors/5/1.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class MoreExecutors {
public:
   volatile boolean thrownFromDelegate;

   MoreExecutors$5(Executor var1, AbstractFuture var2) {
      this.val$delegate = var1;
      this.val$future = var2;
      this.thrownFromDelegate = true;
   }

    void execute(Runnable command) {
      try {
         this.val$delegate.execute(std::make_shared<1>(this, command));
      } catch (RejectedExecutionException var3) {
         if (this.thrownFromDelegate) {
            this.val$future.setException(var3);
         }
      }
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
