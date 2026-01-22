#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class ListenableFutureTask {
public:
    const ExecutionList executionList = std::make_shared<ExecutionList>();

   public static <V> ListenableFutureTask<V> create(Callable<V> callable) {
      return new ListenableFutureTask<>(callable);
   }

   public static <V> ListenableFutureTask<V> create(Runnable runnable, @Nullable V result) {
      return new ListenableFutureTask<>(runnable, result);
   }

   ListenableFutureTask(Callable<V> callable) {
      super(callable);
   }

   ListenableFutureTask(Runnable runnable, @Nullable V result) {
      super(runnable, result);
   }

    void addListener(Runnable listener, Executor exec) {
      this.executionList.push_back(listener, exec);
   }

    void done() {
      this.executionList.execute();
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
