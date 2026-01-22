#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/base/Throwables.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class MoreExecutors {
public:
    const Runnable delegate;

   public MoreExecutors$ScheduledListeningDecorator$NeverSuccessfulListenableFutureTask(Runnable delegate) {
      this.delegate = (Runnable)Preconditions.checkNotNull(delegate);
   }

    void run() {
      try {
         this.delegate.run();
      } catch (Throwable var2) {
         this.setException(var2);
         throw Throwables.propagate(var2);
      }
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
