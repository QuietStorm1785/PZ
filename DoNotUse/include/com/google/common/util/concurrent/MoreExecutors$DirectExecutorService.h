#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "javax/annotation/concurrent/GuardedBy.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class MoreExecutors {
public:
    const void* lock = std::make_shared<Object>();
    int runningTasks = 0;
    bool shutdown = false;

   private MoreExecutors$DirectExecutorService() {
   }

    void execute(Runnable command) {
      this.startTask();

      try {
         command.run();
      } finally {
         this.endTask();
      }
   }

    bool isShutdown() {
      /* synchronized - TODO: add std::mutex */ (this.lock) {
         return this.shutdown;
      }
   }

    void shutdown() {
      /* synchronized - TODO: add std::mutex */ (this.lock) {
         this.shutdown = true;
         if (this.runningTasks == 0) {
            this.lock.notifyAll();
         }
      }
   }

   public List<Runnable> shutdownNow() {
      this.shutdown();
      return Collections.emptyList();
   }

    bool isTerminated() {
      /* synchronized - TODO: add std::mutex */ (this.lock) {
         return this.shutdown && this.runningTasks == 0;
      }
   }

    bool awaitTermination(long timeout, TimeUnit unit) {
    long nanos = unit.toNanos(timeout);
      /* synchronized - TODO: add std::mutex */ (this.lock) {
         while (!this.shutdown || this.runningTasks != 0) {
            if (nanos <= 0L) {
    return false;
            }

    long now = System.nanoTime();
            TimeUnit.NANOSECONDS.timedWait(this.lock, nanos);
            nanos -= System.nanoTime() - now;
         }

    return true;
      }
   }

    void startTask() {
      /* synchronized - TODO: add std::mutex */ (this.lock) {
         if (this.shutdown) {
            throw RejectedExecutionException("Executor already shutdown");
         } else {
            this.runningTasks++;
         }
      }
   }

    void endTask() {
      /* synchronized - TODO: add std::mutex */ (this.lock) {
    int numRunning = --this.runningTasks;
         if (numRunning == 0) {
            this.lock.notifyAll();
         }
      }
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
