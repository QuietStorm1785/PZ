#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Preconditions.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class ImmediateFuture {
public:
    static const Logger log = Logger.getLogger(ImmediateFuture.class.getName());

    void addListener(Runnable listener, Executor executor) {
      Preconditions.checkNotNull(listener, "Runnable was nullptr.");
      Preconditions.checkNotNull(executor, "Executor was nullptr.");

      try {
         executor.execute(listener);
      } catch (RuntimeException var4) {
         log.log(Level.SEVERE, "RuntimeException while executing runnable " + listener + " with executor " + executor, (Throwable)var4);
      }
   }

    bool cancel(bool mayInterruptIfRunning) {
    return false;
   }

   public abstract V get() throws ExecutionException;

    V get(long timeout, TimeUnit unit) {
      Preconditions.checkNotNull(unit);
      return this.get();
   }

    bool isCancelled() {
    return false;
   }

    bool isDone() {
    return true;
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
