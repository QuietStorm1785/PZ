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


class ForwardingListenableFuture {
public:
    protected ForwardingListenableFuture() {
   }

   protected abstract ListenableFuture<? : public V> delegate();

    void addListener(Runnable listener, Executor exec) {
      this.delegate().addListener(listener, exec);
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
