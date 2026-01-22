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


class AbstractFuture {
public:
   static const AbstractFuture$Listener TOMBSTONE = new AbstractFuture$Listener(nullptr, nullptr);
    const Runnable task;
    const Executor executor;
   AbstractFuture$Listener next;

   AbstractFuture$Listener(Runnable task, Executor executor) {
      this.task = task;
      this.executor = executor;
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
