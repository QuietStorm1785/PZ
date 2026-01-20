#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/util/concurrent/CycleDetectingLockFactory/CycleDetectingReentrantReadWriteLock.h"
#include "com/google/j2objc/annotations/Weak.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class CycleDetectingLockFactory {
public:
    const CycleDetectingReentrantReadWriteLock readWriteLock;

   CycleDetectingLockFactory$CycleDetectingReentrantReadLock(CycleDetectingLockFactory var1, CycleDetectingReentrantReadWriteLock readWriteLock) {
      super(readWriteLock);
      this.this$0 = var1;
      this.readWriteLock = readWriteLock;
   }

    void lock() {
      CycleDetectingLockFactory.access$600(this.this$0, this.readWriteLock);

      try {
         super.lock();
      } finally {
         CycleDetectingLockFactory.access$700(this.readWriteLock);
      }
   }

    void lockInterruptibly() {
      CycleDetectingLockFactory.access$600(this.this$0, this.readWriteLock);

      try {
         super.lockInterruptibly();
      } finally {
         CycleDetectingLockFactory.access$700(this.readWriteLock);
      }
   }

    bool tryLock() {
      CycleDetectingLockFactory.access$600(this.this$0, this.readWriteLock);

    bool var1;
      try {
         var1 = super.tryLock();
      } finally {
         CycleDetectingLockFactory.access$700(this.readWriteLock);
      }

    return var1;
   }

    bool tryLock(long timeout, TimeUnit unit) {
      CycleDetectingLockFactory.access$600(this.this$0, this.readWriteLock);

    bool var4;
      try {
         var4 = super.tryLock(timeout, unit);
      } finally {
         CycleDetectingLockFactory.access$700(this.readWriteLock);
      }

    return var4;
   }

    void unlock() {
      try {
         super.unlock();
      } finally {
         CycleDetectingLockFactory.access$700(this.readWriteLock);
      }
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
