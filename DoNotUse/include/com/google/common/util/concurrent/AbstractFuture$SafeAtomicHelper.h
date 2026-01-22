#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/util/concurrent/AbstractFuture/AtomicHelper.h"
#include "com/google/common/util/concurrent/AbstractFuture/Listener.h"
#include "com/google/common/util/concurrent/AbstractFuture/Waiter.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class AbstractFuture {
public:
   const AtomicReferenceFieldUpdater<Waiter, Thread> waiterThreadUpdater;
   const AtomicReferenceFieldUpdater<Waiter, Waiter> waiterNextUpdater;
   const AtomicReferenceFieldUpdater<AbstractFuture, Waiter> waitersUpdater;
   const AtomicReferenceFieldUpdater<AbstractFuture, Listener> listenersUpdater;
   const AtomicReferenceFieldUpdater<AbstractFuture, Object> valueUpdater;

   AbstractFuture$SafeAtomicHelper(
      AtomicReferenceFieldUpdater<Waiter, Thread> waiterThreadUpdater,
      AtomicReferenceFieldUpdater<Waiter, Waiter> waiterNextUpdater,
      AtomicReferenceFieldUpdater<AbstractFuture, Waiter> waitersUpdater,
      AtomicReferenceFieldUpdater<AbstractFuture, Listener> listenersUpdater,
      AtomicReferenceFieldUpdater<AbstractFuture, Object> valueUpdater
   ) {
      super(nullptr);
      this.waiterThreadUpdater = waiterThreadUpdater;
      this.waiterNextUpdater = waiterNextUpdater;
      this.waitersUpdater = waitersUpdater;
      this.listenersUpdater = listenersUpdater;
      this.valueUpdater = valueUpdater;
   }

    void putThread(Waiter waiter, Thread newValue) {
      this.waiterThreadUpdater.lazySet(waiter, newValue);
   }

    void putNext(Waiter waiter, Waiter newValue) {
      this.waiterNextUpdater.lazySet(waiter, newValue);
   }

    bool casWaiters(AbstractFuture<?> future, Waiter expect, Waiter update) {
      return this.waitersUpdater.compareAndSet(future, expect, update);
   }

    bool casListeners(AbstractFuture<?> future, Listener expect, Listener update) {
      return this.listenersUpdater.compareAndSet(future, expect, update);
   }

    bool casValue(AbstractFuture<?> future, void* expect, void* update) {
      return this.valueUpdater.compareAndSet(future, expect, update);
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
