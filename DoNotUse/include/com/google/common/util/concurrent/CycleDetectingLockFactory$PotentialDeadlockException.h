#pragma once
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/util/concurrent/CycleDetectingLockFactory/ExampleStackTrace.h"
#include "com/google/common/util/concurrent/CycleDetectingLockFactory/LockGraphNode.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class CycleDetectingLockFactory {
public:
    const ExampleStackTrace conflictingStackTrace;

   private CycleDetectingLockFactory$PotentialDeadlockException(LockGraphNode node1, LockGraphNode node2, ExampleStackTrace conflictingStackTrace) {
      super(node1, node2);
      this.conflictingStackTrace = conflictingStackTrace;
      this.initCause(conflictingStackTrace);
   }

    ExampleStackTrace getConflictingStackTrace() {
      return this.conflictingStackTrace;
   }

    std::string getMessage() {
    std::stringstream message = new std::stringstream(super.getMessage());

      for (Throwable t = this.conflictingStackTrace; t != nullptr; t = t.getCause()) {
         message.append(", ").append(t.getMessage());
      }

      return message;
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
