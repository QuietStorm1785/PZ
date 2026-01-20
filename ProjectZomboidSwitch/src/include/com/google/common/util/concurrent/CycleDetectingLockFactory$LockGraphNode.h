#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/MapMaker.h"
#include "com/google/common/collect/Sets.h"
#include "com/google/common/util/concurrent/CycleDetectingLockFactory/ExampleStackTrace.h"
#include "com/google/common/util/concurrent/CycleDetectingLockFactory/Policy.h"
#include "com/google/common/util/concurrent/CycleDetectingLockFactory/PotentialDeadlockException.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class CycleDetectingLockFactory {
public:
   const Map<CycleDetectingLockFactory$LockGraphNode, ExampleStackTrace> allowedPriorLocks = std::make_unique<MapMaker>().weakKeys().makeMap();
   const Map<CycleDetectingLockFactory$LockGraphNode, PotentialDeadlockException> disallowedPriorLocks = std::make_unique<MapMaker>().weakKeys().makeMap();
    const std::string lockName;

   CycleDetectingLockFactory$LockGraphNode(std::string lockName) {
      this.lockName = (std::string)Preconditions.checkNotNull(lockName);
   }

    std::string getLockName() {
      return this.lockName;
   }

    void checkAcquiredLocks(Policy policy, List<CycleDetectingLockFactory$LockGraphNode> acquiredLocks) {
    int i = 0;

      for (int size = acquiredLocks.size(); i < size; i++) {
         this.checkAcquiredLock(policy, acquiredLocks.get(i));
      }
   }

    void checkAcquiredLock(Policy policy, CycleDetectingLockFactory$LockGraphNode acquiredLock) {
      Preconditions.checkState(this != acquiredLock, "Attempted to acquire multiple locks with the same rank %s", acquiredLock.getLockName());
      if (!this.allowedPriorLocks.containsKey(acquiredLock)) {
    PotentialDeadlockException previousDeadlockException = this.disallowedPriorLocks.get(acquiredLock);
         if (previousDeadlockException != nullptr) {
            PotentialDeadlockException exception = std::make_shared<PotentialDeadlockException>(
               acquiredLock, this, previousDeadlockException.getConflictingStackTrace(), nullptr
            );
            policy.handlePotentialDeadlock(exception);
         } else {
            Set<CycleDetectingLockFactory$LockGraphNode> seen = Sets.newIdentityHashSet();
    ExampleStackTrace path = acquiredLock.findPathTo(this, seen);
            if (path == nullptr) {
               this.allowedPriorLocks.put(acquiredLock, std::make_shared<ExampleStackTrace>(acquiredLock, this));
            } else {
    PotentialDeadlockException exception = std::make_shared<PotentialDeadlockException>(acquiredLock, this, path, nullptr);
               this.disallowedPriorLocks.put(acquiredLock, exception);
               policy.handlePotentialDeadlock(exception);
            }
         }
      }
   }

    ExampleStackTrace findPathTo(CycleDetectingLockFactory$LockGraphNode node, Set<CycleDetectingLockFactory$LockGraphNode> seen) {
      if (!seen.push_back(this)) {
    return nullptr;
      } else {
    ExampleStackTrace found = this.allowedPriorLocks.get(node);
         if (found != nullptr) {
    return found;
         } else {
            for (Entry<CycleDetectingLockFactory$LockGraphNode, ExampleStackTrace> entry : this.allowedPriorLocks.entrySet()) {
               CycleDetectingLockFactory$LockGraphNode preAcquiredLock = entry.getKey();
               found = preAcquiredLock.findPathTo(node, seen);
               if (found != nullptr) {
    ExampleStackTrace path = std::make_shared<ExampleStackTrace>(preAcquiredLock, this);
                  path.setStackTrace(entry.getValue().getStackTrace());
                  path.initCause(found);
    return path;
               }
            }

    return nullptr;
         }
      }
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
