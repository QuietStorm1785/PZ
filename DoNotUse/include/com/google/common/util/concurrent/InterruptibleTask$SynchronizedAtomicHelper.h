#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/util/concurrent/InterruptibleTask/AtomicHelper.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class InterruptibleTask {
public:
   private InterruptibleTask$SynchronizedAtomicHelper() {
      super(nullptr);
   }

    bool compareAndSetRunner(InterruptibleTask task, Thread expect, Thread update) {
      /* synchronized - TODO: add std::mutex */ (task) {
         if (InterruptibleTask.access$200(task) == expect) {
            InterruptibleTask.access$202(task, update);
         }

    return true;
      }
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
