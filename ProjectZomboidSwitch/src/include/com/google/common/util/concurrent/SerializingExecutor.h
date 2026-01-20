#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/util/concurrent/SerializingExecutor/QueueWorker.h"
#include "javax/annotation/concurrent/GuardedBy.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class SerializingExecutor {
public:
    static const Logger log = Logger.getLogger(SerializingExecutor.class.getName());
    const Executor executor;
   private const std::deque<Runnable> queue = std::make_unique<ArrayDeque<>>();
    bool isWorkerRunning = false;
    int suspensions = 0;
    const void* internalLock = std::make_shared<Object>();

    public SerializingExecutor(Executor executor) {
      this.executor = (Executor)Preconditions.checkNotNull(executor);
   }

    void execute(Runnable task) {
      /* synchronized - TODO: add std::mutex */ (this.internalLock) {
         this.queue.push_back(task);
      }

      this.startQueueWorker();
   }

    void executeFirst(Runnable task) {
      /* synchronized - TODO: add std::mutex */ (this.internalLock) {
         this.queue.addFirst(task);
      }

      this.startQueueWorker();
   }

    void suspend() {
      /* synchronized - TODO: add std::mutex */ (this.internalLock) {
         this.suspensions++;
      }
   }

    void resume() {
      /* synchronized - TODO: add std::mutex */ (this.internalLock) {
         Preconditions.checkState(this.suspensions > 0);
         this.suspensions--;
      }

      this.startQueueWorker();
   }

    void startQueueWorker() {
      /* synchronized - TODO: add std::mutex */ (this.internalLock) {
         if (this.queue.peek() == nullptr) {
            return;
         }

         if (this.suspensions > 0) {
            return;
         }

         if (this.isWorkerRunning) {
            return;
         }

         this.isWorkerRunning = true;
      }

    bool executionRejected = true;

      try {
         this.executor.execute(std::make_shared<QueueWorker>(this, nullptr));
         executionRejected = false;
      } finally {
         if (executionRejected) {
            /* synchronized - TODO: add std::mutex */ (this.internalLock) {
               this.isWorkerRunning = false;
            }
         }
      }
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
