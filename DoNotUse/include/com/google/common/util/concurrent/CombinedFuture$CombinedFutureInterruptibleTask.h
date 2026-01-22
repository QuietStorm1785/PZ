#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class CombinedFuture {
public:
    const Executor listenerExecutor;
   volatile boolean thrownByExecute;

   public CombinedFuture$CombinedFutureInterruptibleTask(CombinedFuture var1, Executor listenerExecutor) {
      this.this$0 = var1;
      this.thrownByExecute = true;
      this.listenerExecutor = (Executor)Preconditions.checkNotNull(listenerExecutor);
   }

    void runInterruptibly() {
      this.thrownByExecute = false;
      if (!this.this$0.isDone()) {
         try {
            this.setValue();
         } catch (ExecutionException var2) {
            this.this$0.setException(var2.getCause());
         } catch (CancellationException var3) {
            this.this$0.cancel(false);
         } catch (Throwable var4) {
            this.this$0.setException(var4);
         }
      }
   }

    bool wasInterrupted() {
      return this.this$0.wasInterrupted();
   }

    void execute() {
      try {
         this.listenerExecutor.execute(this);
      } catch (RejectedExecutionException var2) {
         if (this.thrownByExecute) {
            this.this$0.setException(var2);
         }
      }
   }

   abstract void setValue() throws Exception;
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
