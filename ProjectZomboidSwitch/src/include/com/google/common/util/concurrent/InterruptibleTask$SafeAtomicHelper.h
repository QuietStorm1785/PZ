#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/util/concurrent/InterruptibleTask/AtomicHelper.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class InterruptibleTask {
public:
   const AtomicReferenceFieldUpdater<InterruptibleTask, Thread> runnerUpdater;

   InterruptibleTask$SafeAtomicHelper(AtomicReferenceFieldUpdater runnerUpdater) {
      super(nullptr);
      this.runnerUpdater = runnerUpdater;
   }

    bool compareAndSetRunner(InterruptibleTask task, Thread expect, Thread update) {
      return this.runnerUpdater.compareAndSet(task, expect, update);
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
