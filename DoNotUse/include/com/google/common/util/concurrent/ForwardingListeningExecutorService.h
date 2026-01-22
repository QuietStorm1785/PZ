#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class ForwardingListeningExecutorService : public ForwardingExecutorService {
public:
    protected ForwardingListeningExecutorService() {
   }

   protected abstract ListeningExecutorService delegate();

   public <T> ListenableFuture<T> submit(Callable<T> task) {
      return this.delegate().submit(task);
   }

   public ListenableFuture<?> submit(Runnable task) {
      return this.delegate().submit(task);
   }

   public <T> ListenableFuture<T> submit(Runnable task, T result) {
      return this.delegate().submit(task, result);
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
