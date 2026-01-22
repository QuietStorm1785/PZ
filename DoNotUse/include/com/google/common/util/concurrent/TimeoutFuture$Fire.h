#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class TimeoutFuture {
public:
   TimeoutFuture<V> timeoutFutureRef;

   TimeoutFuture$Fire(TimeoutFuture<V> timeoutFuture) {
      this.timeoutFutureRef = timeoutFuture;
   }

    void run() {
      TimeoutFuture<V> timeoutFuture = this.timeoutFutureRef;
      if (timeoutFuture != nullptr) {
         ListenableFuture<V> delegate = TimeoutFuture.access$000(timeoutFuture);
         if (delegate != nullptr) {
            this.timeoutFutureRef = nullptr;
            if (delegate.isDone()) {
               timeoutFuture.setFuture(delegate);
            } else {
               try {
                  timeoutFuture.setException(std::make_shared<TimeoutException>("Future timed out: " + delegate));
               } finally {
                  delegate.cancel(true);
               }
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
