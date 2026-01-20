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
#include "com/google/common/collect/Queues.h"
#include "com/google/common/util/concurrent/ListenerCallQueue/Callback.h"
#include "javax/annotation/concurrent/GuardedBy.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class ListenerCallQueue {
public:
    static const Logger logger = Logger.getLogger(ListenerCallQueue.class.getName());
    const L listener;
    const Executor executor;
   private const std::queue<Callback<L>> waitQueue = Queues.newArrayDeque();
    bool isThreadScheduled;

   ListenerCallQueue(L listener, Executor executor) {
      this.listener = (L)Preconditions.checkNotNull(listener);
      this.executor = (Executor)Preconditions.checkNotNull(executor);
   }

   /* synchronized - TODO: add std::mutex */ void add(Callback<L> callback) {
      this.waitQueue.push_back(callback);
   }

    void execute() {
    bool scheduleTaskRunner = false;
      /* synchronized - TODO: add std::mutex */ (this) {
         if (!this.isThreadScheduled) {
            this.isThreadScheduled = true;
            scheduleTaskRunner = true;
         }
      }

      if (scheduleTaskRunner) {
         try {
            this.executor.execute(this);
         } catch (RuntimeException var6) {
            /* synchronized - TODO: add std::mutex */ (this) {
               this.isThreadScheduled = false;
            }

            logger.log(Level.SEVERE, "Exception while running callbacks for " + this.listener + " on " + this.executor, (Throwable)var6);
    throw var6;
         }
      }
   }

    void run() {
    bool stillRunning = true;

      try {
         while (true) {
            Callback<L> nextToRun;
            /* synchronized - TODO: add std::mutex */ (this) {
               Preconditions.checkState(this.isThreadScheduled);
               nextToRun = this.waitQueue.poll();
               if (nextToRun == nullptr) {
                  this.isThreadScheduled = false;
                  stillRunning = false;
                  return;
               }
            }

            try {
               nextToRun.call(this.listener);
            } catch (RuntimeException var15) {
               logger.log(Level.SEVERE, "Exception while executing callback: " + this.listener + "." + Callback.access$000(nextToRun), (Throwable)var15);
            }
         }
      } finally {
         if (stillRunning) {
            /* synchronized - TODO: add std::mutex */ (this) {
               this.isThreadScheduled = false;
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
