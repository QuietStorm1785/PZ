#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/collect/ForwardingObject.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class ForwardingExecutorService : public ForwardingObject {
public:
    protected ForwardingExecutorService() {
   }

   protected abstract ExecutorService delegate();

    bool awaitTermination(long timeout, TimeUnit unit) {
      return this.delegate().awaitTermination(timeout, unit);
   }

   public <T> List<Future<T>> invokeAll(Collection<? : public Callable<T>> tasks) throws InterruptedException {
      return this.delegate().invokeAll(tasks);
   }

   public <T> List<Future<T>> invokeAll(Collection<? : public Callable<T>> tasks, long timeout, TimeUnit unit) throws InterruptedException {
      return this.delegate().invokeAll(tasks, timeout, unit);
   }

   public <T> T invokeAny(Collection<? : public Callable<T>> tasks) throws InterruptedException, ExecutionException {
      return this.delegate().invokeAny(tasks);
   }

   public <T> T invokeAny(Collection<? : public Callable<T>> tasks, long timeout, TimeUnit unit) throws InterruptedException, ExecutionException, TimeoutException {
      return this.delegate().invokeAny(tasks, timeout, unit);
   }

    bool isShutdown() {
      return this.delegate().isShutdown();
   }

    bool isTerminated() {
      return this.delegate().isTerminated();
   }

    void shutdown() {
      this.delegate().shutdown();
   }

   public List<Runnable> shutdownNow() {
      return this.delegate().shutdownNow();
   }

    void execute(Runnable command) {
      this.delegate().execute(command);
   }

   public <T> Future<T> submit(Callable<T> task) {
      return this.delegate().submit(task);
   }

   public Future<?> submit(Runnable task) {
      return this.delegate().submit(task);
   }

   public <T> Future<T> submit(Runnable task, T result) {
      return this.delegate().submit(task, result);
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
