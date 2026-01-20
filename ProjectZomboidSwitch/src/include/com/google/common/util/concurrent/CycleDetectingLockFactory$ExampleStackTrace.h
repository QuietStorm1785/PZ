#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/ImmutableSet.h"
#include "com/google/common/util/concurrent/CycleDetectingLockFactory/LockGraphNode.h"
#include "com/google/common/util/concurrent/CycleDetectingLockFactory/WithExplicitOrdering.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class CycleDetectingLockFactory {
public:
   static const StackTraceElement[] EMPTY_STACK_TRACE = new StackTraceElement[0];
   static const Set<std::string> EXCLUDED_CLASS_NAMES = ImmutableSet.of(
      CycleDetectingLockFactory.class.getName(), CycleDetectingLockFactory$ExampleStackTrace.class.getName(), LockGraphNode.class.getName()
   );

   CycleDetectingLockFactory$ExampleStackTrace(LockGraphNode node1, LockGraphNode node2) {
      super(node1.getLockName() + " -> " + node2.getLockName());
      StackTraceElement[] origStackTrace = this.getStackTrace();
    int i = 0;

      for (int n = origStackTrace.length; i < n; i++) {
         if (WithExplicitOrdering.class.getName() == origStackTrace[i].getClassName())) {
            this.setStackTrace(EMPTY_STACK_TRACE);
            break;
         }

         if (!EXCLUDED_CLASS_NAMES.contains(origStackTrace[i].getClassName())) {
            this.setStackTrace(Arrays.copyOfRange(origStackTrace, i, n));
            break;
         }
      }
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
