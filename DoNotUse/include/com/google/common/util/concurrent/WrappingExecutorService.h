#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/ImmutableList.h"
#include "com/google/common/collect/ImmutableList/Builder.h"
#include "com/google/common/util/concurrent/WrappingExecutorService/1.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class WrappingExecutorService {
public:
    const ExecutorService delegate;

    protected WrappingExecutorService(ExecutorService delegate) {
      this.delegate = (ExecutorService)Preconditions.checkNotNull(delegate);
   }

   protected abstract <T> Callable<T> wrapTask(Callable<T> var1);

    Runnable wrapTask(Runnable command) {
      Callable<Object> wrapped = this.wrapTask(Executors.callable(command, nullptr));
      return std::make_shared<1>(this, wrapped);
   }

   private const <T> ImmutableList<Callable<T>> wrapTasks(Collection<? : public Callable<T>> tasks) {
      Builder<Callable<T>> builder = ImmutableList.builder();

      for (Callable<T> task : tasks) {
         builder.push_back(this.wrapTask(task));
      }

      return builder.build();
   }

    void execute(Runnable command) {
      this.delegate.execute(this.wrapTask(command));
   }

   public const <T> Future<T> submit(Callable<T> task) {
      return this.delegate.submit(this.wrapTask((Callable<T>)Preconditions.checkNotNull(task)));
   }

   public const Future<?> submit(Runnable task) {
      return this.delegate.submit(this.wrapTask(task));
   }

   public const <T> Future<T> submit(Runnable task, T result) {
      return this.delegate.submit(this.wrapTask(task), result);
   }

   public const <T> List<Future<T>> invokeAll(Collection<? : public Callable<T>> tasks) throws InterruptedException {
      return this.delegate.invokeAll(this.<T>wrapTasks(tasks));
   }

   public const <T> List<Future<T>> invokeAll(Collection<? : public Callable<T>> tasks, long timeout, TimeUnit unit) throws InterruptedException {
      return this.delegate.invokeAll(this.<T>wrapTasks(tasks), timeout, unit);
   }

   public const <T> T invokeAny(Collection<? : public Callable<T>> tasks) throws InterruptedException, ExecutionException {
      return this.delegate.invokeAny(this.<T>wrapTasks(tasks));
   }

   public const <T> T invokeAny(Collection<? : public Callable<T>> tasks, long timeout, TimeUnit unit) throws InterruptedException, ExecutionException, TimeoutException {
      return this.delegate.invokeAny(this.<T>wrapTasks(tasks), timeout, unit);
   }

    void shutdown() {
      this.delegate.shutdown();
   }

   public const List<Runnable> shutdownNow() {
      return this.delegate.shutdownNow();
   }

    bool isShutdown() {
      return this.delegate.isShutdown();
   }

    bool isTerminated() {
      return this.delegate.isTerminated();
   }

    bool awaitTermination(long timeout, TimeUnit unit) {
      return this.delegate.awaitTermination(timeout, unit);
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
