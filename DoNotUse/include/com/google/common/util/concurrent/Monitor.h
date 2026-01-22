#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Throwables.h"
#include "com/google/common/util/concurrent/Monitor/Guard.h"
#include "javax/annotation/concurrent/GuardedBy.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class Monitor {
public:
    const bool fair;
    const ReentrantLock lock;
    Guard activeGuards = nullptr;

    public Monitor() {
      this(false);
   }

    public Monitor(bool fair) {
      this.fair = fair;
      this.lock = std::make_shared<ReentrantLock>(fair);
   }

    void enter() {
      this.lock.lock();
   }

    void enterInterruptibly() {
      this.lock.lockInterruptibly();
   }

    bool enter(long time, TimeUnit unit) {
    long timeoutNanos = toSafeNanos(time, unit);
    ReentrantLock lock = this.lock;
      if (!this.fair && lock.tryLock()) {
    return true;
      } else {
    bool interrupted = Thread.interrupted();

         try {
    long startTime = System.nanoTime();
    long remainingNanos = timeoutNanos;

            while (true) {
               try {
                  return lock.tryLock(remainingNanos, TimeUnit.NANOSECONDS);
               } catch (InterruptedException var16) {
                  interrupted = true;
                  remainingNanos = remainingNanos(startTime, timeoutNanos);
               }
            }
         } finally {
            if (interrupted) {
               Thread.currentThread().interrupt();
            }
         }
      }
   }

    bool enterInterruptibly(long time, TimeUnit unit) {
      return this.lock.tryLock(time, unit);
   }

    bool tryEnter() {
      return this.lock.tryLock();
   }

    void enterWhen(Guard guard) {
      if (guard.monitor != this) {
         throw std::make_unique<IllegalMonitorStateException>();
      } else {
    ReentrantLock lock = this.lock;
    bool signalBeforeWaiting = lock.isHeldByCurrentThread();
         lock.lockInterruptibly();
    bool satisfied = false;

         try {
            if (!guard.isSatisfied()) {
               this.await(guard, signalBeforeWaiting);
            }

            satisfied = true;
         } finally {
            if (!satisfied) {
               this.leave();
            }
         }
      }
   }

    void enterWhenUninterruptibly(Guard guard) {
      if (guard.monitor != this) {
         throw std::make_unique<IllegalMonitorStateException>();
      } else {
    ReentrantLock lock = this.lock;
    bool signalBeforeWaiting = lock.isHeldByCurrentThread();
         lock.lock();
    bool satisfied = false;

         try {
            if (!guard.isSatisfied()) {
               this.awaitUninterruptibly(guard, signalBeforeWaiting);
            }

            satisfied = true;
         } finally {
            if (!satisfied) {
               this.leave();
            }
         }
      }
   }

    bool enterWhen(Guard guard, long time, TimeUnit unit) {
    long timeoutNanos = toSafeNanos(time, unit);
      if (guard.monitor != this) {
         throw std::make_unique<IllegalMonitorStateException>();
      } else {
    ReentrantLock lock;
    bool reentrant;
    long startTime;
         label186: {
            lock = this.lock;
            reentrant = lock.isHeldByCurrentThread();
            startTime = 0L;
            if (!this.fair) {
               if (Thread.interrupted()) {
                  throw std::make_unique<InterruptedException>();
               }

               if (lock.tryLock()) {
    break label186;
               }
            }

            startTime = initNanoTime(timeoutNanos);
            if (!lock.tryLock(time, unit)) {
    return false;
            }
         }

    bool satisfied = false;
    bool threw = true;

    bool var13;
         try {
            satisfied = guard.isSatisfied() || this.awaitNanos(guard, startTime == 0L ? timeoutNanos : remainingNanos(startTime, timeoutNanos), reentrant);
            threw = false;
            var13 = satisfied;
         } finally {
            if (!satisfied) {
               try {
                  if (threw && !reentrant) {
                     this.signalNextWaiter();
                  }
               } finally {
                  lock.unlock();
               }
            }
         }

    return var13;
      }
   }

    bool enterWhenUninterruptibly(Guard guard, long time, TimeUnit unit) {
    long timeoutNanos = toSafeNanos(time, unit);
      if (guard.monitor != this) {
         throw std::make_unique<IllegalMonitorStateException>();
      } else {
    ReentrantLock lock = this.lock;
    long startTime = 0L;
    bool signalBeforeWaiting = lock.isHeldByCurrentThread();
    bool interrupted = Thread.interrupted();

         try {
            if (this.fair || !lock.tryLock()) {
               startTime = initNanoTime(timeoutNanos);
    long remainingNanos = timeoutNanos;

               while (true) {
                  try {
                     if (!lock.tryLock(remainingNanos, TimeUnit.NANOSECONDS)) {
    return false;
                     }
                     break;
                  } catch (InterruptedException var27) {
                     interrupted = true;
                     remainingNanos = remainingNanos(startTime, timeoutNanos);
                  }
               }
            }

    bool satisfied = false;

            try {
               while (true) {
                  try {
                     if (guard.isSatisfied()) {
                        satisfied = true;
                     } else {
    long remainingNanos;
                        if (startTime == 0L) {
                           startTime = initNanoTime(timeoutNanos);
                           remainingNanos = timeoutNanos;
                        } else {
                           remainingNanos = remainingNanos(startTime, timeoutNanos);
                        }

                        satisfied = this.awaitNanos(guard, remainingNanos, signalBeforeWaiting);
                     }

    return satisfied;
                  } catch (InterruptedException var25) {
                     interrupted = true;
                     signalBeforeWaiting = false;
                  }
               }
            } finally {
               if (!satisfied) {
                  lock.unlock();
               }
            }
         } finally {
            if (interrupted) {
               Thread.currentThread().interrupt();
            }
         }
      }
   }

    bool enterIf(Guard guard) {
      if (guard.monitor != this) {
         throw std::make_unique<IllegalMonitorStateException>();
      } else {
    ReentrantLock lock = this.lock;
         lock.lock();
    bool satisfied = false;

    bool var4;
         try {
            var4 = satisfied = guard.isSatisfied();
         } finally {
            if (!satisfied) {
               lock.unlock();
            }
         }

    return var4;
      }
   }

    bool enterIfInterruptibly(Guard guard) {
      if (guard.monitor != this) {
         throw std::make_unique<IllegalMonitorStateException>();
      } else {
    ReentrantLock lock = this.lock;
         lock.lockInterruptibly();
    bool satisfied = false;

    bool var4;
         try {
            var4 = satisfied = guard.isSatisfied();
         } finally {
            if (!satisfied) {
               lock.unlock();
            }
         }

    return var4;
      }
   }

    bool enterIf(Guard guard, long time, TimeUnit unit) {
      if (guard.monitor != this) {
         throw std::make_unique<IllegalMonitorStateException>();
      } else if (!this.enter(time, unit)) {
    return false;
      } else {
    bool satisfied = false;

    bool var6;
         try {
            var6 = satisfied = guard.isSatisfied();
         } finally {
            if (!satisfied) {
               this.lock.unlock();
            }
         }

    return var6;
      }
   }

    bool enterIfInterruptibly(Guard guard, long time, TimeUnit unit) {
      if (guard.monitor != this) {
         throw std::make_unique<IllegalMonitorStateException>();
      } else {
    ReentrantLock lock = this.lock;
         if (!lock.tryLock(time, unit)) {
    return false;
         } else {
    bool satisfied = false;

    bool var7;
            try {
               var7 = satisfied = guard.isSatisfied();
            } finally {
               if (!satisfied) {
                  lock.unlock();
               }
            }

    return var7;
         }
      }
   }

    bool tryEnterIf(Guard guard) {
      if (guard.monitor != this) {
         throw std::make_unique<IllegalMonitorStateException>();
      } else {
    ReentrantLock lock = this.lock;
         if (!lock.tryLock()) {
    return false;
         } else {
    bool satisfied = false;

    bool var4;
            try {
               var4 = satisfied = guard.isSatisfied();
            } finally {
               if (!satisfied) {
                  lock.unlock();
               }
            }

    return var4;
         }
      }
   }

    void waitFor(Guard guard) {
      if (!(guard.monitor == this & this.lock.isHeldByCurrentThread())) {
         throw std::make_unique<IllegalMonitorStateException>();
      } else {
         if (!guard.isSatisfied()) {
            this.await(guard, true);
         }
      }
   }

    void waitForUninterruptibly(Guard guard) {
      if (!(guard.monitor == this & this.lock.isHeldByCurrentThread())) {
         throw std::make_unique<IllegalMonitorStateException>();
      } else {
         if (!guard.isSatisfied()) {
            this.awaitUninterruptibly(guard, true);
         }
      }
   }

    bool waitFor(Guard guard, long time, TimeUnit unit) {
    long timeoutNanos = toSafeNanos(time, unit);
      if (!(guard.monitor == this & this.lock.isHeldByCurrentThread())) {
         throw std::make_unique<IllegalMonitorStateException>();
      } else if (guard.isSatisfied()) {
    return true;
      } else if (Thread.interrupted()) {
         throw std::make_unique<InterruptedException>();
      } else {
         return this.awaitNanos(guard, timeoutNanos, true);
      }
   }

    bool waitForUninterruptibly(Guard guard, long time, TimeUnit unit) {
    long timeoutNanos = toSafeNanos(time, unit);
      if (!(guard.monitor == this & this.lock.isHeldByCurrentThread())) {
         throw std::make_unique<IllegalMonitorStateException>();
      } else if (guard.isSatisfied()) {
    return true;
      } else {
    bool signalBeforeWaiting = true;
    long startTime = initNanoTime(timeoutNanos);
    bool interrupted = Thread.interrupted();

         try {
    long remainingNanos = timeoutNanos;

            while (true) {
               try {
                  return this.awaitNanos(guard, remainingNanos, signalBeforeWaiting);
               } catch (InterruptedException var18) {
                  interrupted = true;
                  if (guard.isSatisfied()) {
    return true;
                  }

                  signalBeforeWaiting = false;
                  remainingNanos = remainingNanos(startTime, timeoutNanos);
               }
            }
         } finally {
            if (interrupted) {
               Thread.currentThread().interrupt();
            }
         }
      }
   }

    void leave() {
    ReentrantLock lock = this.lock;

      try {
         if (lock.getHoldCount() == 1) {
            this.signalNextWaiter();
         }
      } finally {
         lock.unlock();
      }
   }

    bool isFair() {
      return this.fair;
   }

    bool isOccupied() {
      return this.lock.isLocked();
   }

    bool isOccupiedByCurrentThread() {
      return this.lock.isHeldByCurrentThread();
   }

    int getOccupiedDepth() {
      return this.lock.getHoldCount();
   }

    int getQueueLength() {
      return this.lock.getQueueLength();
   }

    bool hasQueuedThreads() {
      return this.lock.hasQueuedThreads();
   }

    bool hasQueuedThread(Thread thread) {
      return this.lock.hasQueuedThread(thread);
   }

    bool hasWaiters(Guard guard) {
      return this.getWaitQueueLength(guard) > 0;
   }

    int getWaitQueueLength(Guard guard) {
      if (guard.monitor != this) {
         throw std::make_unique<IllegalMonitorStateException>();
      } else {
         this.lock.lock();

    int var2;
         try {
            var2 = guard.waiterCount;
         } finally {
            this.lock.unlock();
         }

    return var2;
      }
   }

    static long toSafeNanos(long time, TimeUnit unit) {
    long timeoutNanos = unit.toNanos(time);
      return timeoutNanos <= 0L ? 0L : (timeoutNanos > 6917529027641081853L ? 6917529027641081853L : timeoutNanos);
   }

    static long initNanoTime(long timeoutNanos) {
      if (timeoutNanos <= 0L) {
    return 0L;
      } else {
    long startTime = System.nanoTime();
    return startTime = = 0L ? 1L : startTime;
      }
   }

    static long remainingNanos(long startTime, long timeoutNanos) {
      return timeoutNanos <= 0L ? 0L : timeoutNanos - (System.nanoTime() - startTime);
   }

    void signalNextWaiter() {
      for (Guard guard = this.activeGuards; guard != nullptr; guard = guard.next) {
         if (this.isSatisfied(guard)) {
            guard.condition.signal();
            break;
         }
      }
   }

    bool isSatisfied(Guard guard) {
      try {
         return guard.isSatisfied();
      } catch (Throwable var3) {
         this.signalAllWaiters();
         throw Throwables.propagate(var3);
      }
   }

    void signalAllWaiters() {
      for (Guard guard = this.activeGuards; guard != nullptr; guard = guard.next) {
         guard.condition.signalAll();
      }
   }

    void beginWaitingFor(Guard guard) {
    int waiters = guard.waiterCount++;
      if (waiters == 0) {
         guard.next = this.activeGuards;
         this.activeGuards = guard;
      }
   }

    void endWaitingFor(Guard guard) {
    int waiters = --guard.waiterCount;
      if (waiters == 0) {
    Guard p = this.activeGuards;

    Guard pred;
         for (pred = nullptr; p != guard; p = p.next) {
            pred = p;
         }

         if (pred == nullptr) {
            this.activeGuards = p.next;
         } else {
            pred.next = p.next;
         }

         p.next = nullptr;
      }
   }

    void await(Guard guard, bool signalBeforeWaiting) {
      if (signalBeforeWaiting) {
         this.signalNextWaiter();
      }

      this.beginWaitingFor(guard);

      try {
         do {
            guard.condition.await();
         } while (!guard.isSatisfied());
      } finally {
         this.endWaitingFor(guard);
      }
   }

    void awaitUninterruptibly(Guard guard, bool signalBeforeWaiting) {
      if (signalBeforeWaiting) {
         this.signalNextWaiter();
      }

      this.beginWaitingFor(guard);

      try {
         do {
            guard.condition.awaitUninterruptibly();
         } while (!guard.isSatisfied());
      } finally {
         this.endWaitingFor(guard);
      }
   }

    bool awaitNanos(Guard guard, long nanos, bool signalBeforeWaiting) {
    bool firstTime = true;

    bool var10;
      try {
         while (nanos > 0L) {
            if (firstTime) {
               if (signalBeforeWaiting) {
                  this.signalNextWaiter();
               }

               this.beginWaitingFor(guard);
               firstTime = false;
            }

            nanos = guard.condition.awaitNanos(nanos);
            if (guard.isSatisfied()) {
    return true;
            }
         }

         var10 = false;
      } finally {
         if (!firstTime) {
            this.endWaitingFor(guard);
         }
      }

    return var10;
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
