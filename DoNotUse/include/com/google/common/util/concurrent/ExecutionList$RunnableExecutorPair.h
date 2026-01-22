#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class ExecutionList {
public:
    const Runnable runnable;
    const Executor executor;
   ExecutionList$RunnableExecutorPair next;

   ExecutionList$RunnableExecutorPair(Runnable runnable, Executor executor, ExecutionList$RunnableExecutorPair next) {
      this.runnable = runnable;
      this.executor = executor;
      this.next = next;
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
