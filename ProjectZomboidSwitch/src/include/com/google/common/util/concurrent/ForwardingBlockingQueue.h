#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/collect/ForwardingQueue.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class ForwardingBlockingQueue {
public:
    protected ForwardingBlockingQueue() {
   }

   protected abstract BlockingQueue<E> delegate();

    int drainTo(Collection<? super, int maxElements) {
      return this.delegate().drainTo(c, maxElements);
   }

    int drainTo(Collection<? super) {
      return this.delegate().drainTo(c);
   }

    bool offer(E e, long timeout, TimeUnit unit) {
      return this.delegate().offer(e, timeout, unit);
   }

    E poll(long timeout, TimeUnit unit) {
      return this.delegate().poll(timeout, unit);
   }

    void put(E e) {
      this.delegate().put(e);
   }

    int remainingCapacity() {
      return this.delegate().remainingCapacity();
   }

    E take() {
      return this.delegate().take();
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
