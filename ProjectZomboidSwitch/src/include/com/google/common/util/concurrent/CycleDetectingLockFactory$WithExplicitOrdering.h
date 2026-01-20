#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/VisibleForTesting.h"
#include "com/google/common/util/concurrent/CycleDetectingLockFactory/CycleDetectingReentrantLock.h"
#include "com/google/common/util/concurrent/CycleDetectingLockFactory/CycleDetectingReentrantReadWriteLock.h"
#include "com/google/common/util/concurrent/CycleDetectingLockFactory/LockGraphNode.h"
#include "com/google/common/util/concurrent/CycleDetectingLockFactory/Policies.h"
#include "com/google/common/util/concurrent/CycleDetectingLockFactory/Policy.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class CycleDetectingLockFactory {
public:
   private const Map<E, LockGraphNode> lockGraphNodes;

   CycleDetectingLockFactory$WithExplicitOrdering(Policy policy, Map<E, LockGraphNode> lockGraphNodes) {
      super(policy, nullptr);
      this.lockGraphNodes = lockGraphNodes;
   }

    ReentrantLock newReentrantLock(E rank) {
      return this.newReentrantLock(rank, false);
   }

    ReentrantLock newReentrantLock(E rank, bool fair) {
      return (ReentrantLock)(this.policy == Policies.DISABLED
         ? std::make_shared<ReentrantLock>(fair)
         : std::make_shared<CycleDetectingReentrantLock>(this, this.lockGraphNodes.get(rank), fair, nullptr));
   }

    ReentrantReadWriteLock newReentrantReadWriteLock(E rank) {
      return this.newReentrantReadWriteLock(rank, false);
   }

    ReentrantReadWriteLock newReentrantReadWriteLock(E rank, bool fair) {
      return (ReentrantReadWriteLock)(this.policy == Policies.DISABLED
         ? std::make_shared<ReentrantReadWriteLock>(fair)
         : std::make_shared<CycleDetectingReentrantReadWriteLock>(this, this.lockGraphNodes.get(rank), fair, nullptr));
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
