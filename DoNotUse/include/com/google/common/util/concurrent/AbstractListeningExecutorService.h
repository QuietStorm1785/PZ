#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class AbstractListeningExecutorService : public AbstractExecutorService {
public:
   protected const <T> RunnableFuture<T> newTaskFor(Runnable runnable, T value) {
      return TrustedListenableFutureTask.create(runnable, value);
   }

   protected const <T> RunnableFuture<T> newTaskFor(Callable<T> callable) {
      return TrustedListenableFutureTask.create(callable);
   }

   public ListenableFuture<?> submit(Runnable task) {
      return (ListenableFuture<?>)super.submit(task);
   }

   public <T> ListenableFuture<T> submit(Runnable task, @Nullable T result) {
      return (ListenableFuture<T>)super.<T>submit(task, result);
   }

   public <T> ListenableFuture<T> submit(Callable<T> task) {
      return (ListenableFuture<T>)super.<T>submit(task);
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
