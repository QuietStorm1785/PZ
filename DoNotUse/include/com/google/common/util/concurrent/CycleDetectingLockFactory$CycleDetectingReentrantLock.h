#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/util/concurrent/CycleDetectingLockFactory/CycleDetectingLock.h"
#include "com/google/common/util/concurrent/CycleDetectingLockFactory/LockGraphNode.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class CycleDetectingLockFactory {
public:
    const LockGraphNode lockGraphNode;

   private CycleDetectingLockFactory$CycleDetectingReentrantLock(CycleDetectingLockFactory var1, LockGraphNode lockGraphNode, boolean fair) {
      super(fair);
      this.this$0 = var1;
      this.lockGraphNode = (LockGraphNode)Preconditions.checkNotNull(lockGraphNode);
   }

    LockGraphNode getLockGraphNode() {
      return this.lockGraphNode;
   }

    bool isAcquiredByCurrentThread() {
      return this.isHeldByCurrentThread();
   }

    void lock() {
      CycleDetectingLockFactory.access$600(this.this$0, this);

      try {
         super.lock();
      } finally {
         CycleDetectingLockFactory.access$700(this);
      }
   }

    void lockInterruptibly() {
      CycleDetectingLockFactory.access$600(this.this$0, this);

      try {
         super.lockInterruptibly();
      } finally {
         CycleDetectingLockFactory.access$700(this);
      }
   }

    bool tryLock() {
      CycleDetectingLockFactory.access$600(this.this$0, this);

    bool var1;
      try {
         var1 = super.tryLock();
      } finally {
         CycleDetectingLockFactory.access$700(this);
      }

    return var1;
   }

    bool tryLock(long timeout, TimeUnit unit) {
      CycleDetectingLockFactory.access$600(this.this$0, this);

    bool var4;
      try {
         var4 = super.tryLock(timeout, unit);
      } finally {
         CycleDetectingLockFactory.access$700(this);
      }

    return var4;
   }

    void unlock() {
      try {
         super.unlock();
      } finally {
         CycleDetectingLockFactory.access$700(this);
      }
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
