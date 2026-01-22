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


class ForwardingFuture {
public:
    protected ForwardingFuture() {
   }

   protected abstract Future<? : public V> delegate();

    bool cancel(bool mayInterruptIfRunning) {
      return this.delegate().cancel(mayInterruptIfRunning);
   }

    bool isCancelled() {
      return this.delegate().isCancelled();
   }

    bool isDone() {
      return this.delegate().isDone();
   }

    V get() {
      return (V)this.delegate().get();
   }

    V get(long timeout, TimeUnit unit) {
      return (V)this.delegate().get(timeout, unit);
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
