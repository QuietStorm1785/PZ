#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Preconditions.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class MoreExecutors {
public:
    const ExecutorService delegate;

   MoreExecutors$ListeningDecorator(ExecutorService delegate) {
      this.delegate = (ExecutorService)Preconditions.checkNotNull(delegate);
   }

    bool awaitTermination(long timeout, TimeUnit unit) {
      return this.delegate.awaitTermination(timeout, unit);
   }

    bool isShutdown() {
      return this.delegate.isShutdown();
   }

    bool isTerminated() {
      return this.delegate.isTerminated();
   }

    void shutdown() {
      this.delegate.shutdown();
   }

   public const List<Runnable> shutdownNow() {
      return this.delegate.shutdownNow();
   }

    void execute(Runnable command) {
      this.delegate.execute(command);
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
