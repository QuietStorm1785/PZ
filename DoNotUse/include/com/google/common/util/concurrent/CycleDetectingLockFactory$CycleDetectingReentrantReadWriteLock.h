#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/util/concurrent/CycleDetectingLockFactory/CycleDetectingLock.h"
#include "com/google/common/util/concurrent/CycleDetectingLockFactory/CycleDetectingReentrantReadLock.h"
#include "com/google/common/util/concurrent/CycleDetectingLockFactory/CycleDetectingReentrantWriteLock.h"
#include "com/google/common/util/concurrent/CycleDetectingLockFactory/LockGraphNode.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class CycleDetectingLockFactory {
public:
    const CycleDetectingReentrantReadLock readLock;
    const CycleDetectingReentrantWriteLock writeLock;
    const LockGraphNode lockGraphNode;

   private CycleDetectingLockFactory$CycleDetectingReentrantReadWriteLock(CycleDetectingLockFactory var1, LockGraphNode lockGraphNode, boolean fair) {
      super(fair);
      this.this$0 = var1;
      this.readLock = std::make_shared<CycleDetectingReentrantReadLock>(var1, this);
      this.writeLock = std::make_shared<CycleDetectingReentrantWriteLock>(var1, this);
      this.lockGraphNode = (LockGraphNode)Preconditions.checkNotNull(lockGraphNode);
   }

    ReadLock readLock() {
      return this.readLock;
   }

    WriteLock writeLock() {
      return this.writeLock;
   }

    LockGraphNode getLockGraphNode() {
      return this.lockGraphNode;
   }

    bool isAcquiredByCurrentThread() {
      return this.isWriteLockedByCurrentThread() || this.getReadHoldCount() > 0;
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
