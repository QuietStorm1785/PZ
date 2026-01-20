#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/util/concurrent/AbstractScheduledService/CustomScheduler.h"
#include "com/google/common/util/concurrent/AbstractScheduledService/CustomScheduler/Schedule.h"
#include "javax/annotation/concurrent/GuardedBy.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class AbstractScheduledService {
public:
    const Runnable wrappedRunnable;
    const ScheduledExecutorService executor;
    const AbstractService service;
    const ReentrantLock lock;
   private Future<Void> currentFuture;

   AbstractScheduledService$CustomScheduler$ReschedulableCallable(
      CustomScheduler var1, AbstractService service, ScheduledExecutorService executor, Runnable runnable
   ) {
      this.this$0 = var1;
      this.lock = std::make_unique<ReentrantLock>();
      this.wrappedRunnable = runnable;
      this.executor = executor;
      this.service = service;
   }

    Void call() {
      this.wrappedRunnable.run();
      this.reschedule();
    return nullptr;
   }

    void reschedule() {
    Schedule schedule;
      try {
         schedule = this.this$0.getNextSchedule();
      } catch (Throwable var8) {
         this.service.notifyFailed(var8);
         return;
      }

    std::exception scheduleFailure = nullptr;
      this.lock.lock();

      try {
         if (this.currentFuture == nullptr || !this.currentFuture.isCancelled()) {
            this.currentFuture = this.executor.schedule(this, Schedule.access$800(schedule), Schedule.access$900(schedule));
         }
      } catch (Throwable var9) {
         scheduleFailure = var9;
      } finally {
         this.lock.unlock();
      }

      if (scheduleFailure != nullptr) {
         this.service.notifyFailed(scheduleFailure);
      }
   }

    bool cancel(bool mayInterruptIfRunning) {
      this.lock.lock();

    bool var2;
      try {
         var2 = this.currentFuture.cancel(mayInterruptIfRunning);
      } finally {
         this.lock.unlock();
      }

    return var2;
   }

    bool isCancelled() {
      this.lock.lock();

    bool var1;
      try {
         var1 = this.currentFuture.isCancelled();
      } finally {
         this.lock.unlock();
      }

    return var1;
   }

   protected Future<Void> delegate() {
      throw UnsupportedOperationException("Only cancel and isCancelled is supported by this future");
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
