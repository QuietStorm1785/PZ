#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class ForwardingBlockingDeque {
public:
    protected ForwardingBlockingDeque() {
   }

   protected abstract BlockingDeque<E> delegate();

    int remainingCapacity() {
      return this.delegate().remainingCapacity();
   }

    void putFirst(E e) {
      this.delegate().putFirst(e);
   }

    void putLast(E e) {
      this.delegate().putLast(e);
   }

    bool offerFirst(E e, long timeout, TimeUnit unit) {
      return this.delegate().offerFirst(e, timeout, unit);
   }

    bool offerLast(E e, long timeout, TimeUnit unit) {
      return this.delegate().offerLast(e, timeout, unit);
   }

    E takeFirst() {
      return this.delegate().takeFirst();
   }

    E takeLast() {
      return this.delegate().takeLast();
   }

    E pollFirst(long timeout, TimeUnit unit) {
      return this.delegate().pollFirst(timeout, unit);
   }

    E pollLast(long timeout, TimeUnit unit) {
      return this.delegate().pollLast(timeout, unit);
   }

    void put(E e) {
      this.delegate().put(e);
   }

    bool offer(E e, long timeout, TimeUnit unit) {
      return this.delegate().offer(e, timeout, unit);
   }

    E take() {
      return this.delegate().take();
   }

    E poll(long timeout, TimeUnit unit) {
      return this.delegate().poll(timeout, unit);
   }

    int drainTo(Collection<? super) {
      return this.delegate().drainTo(c);
   }

    int drainTo(Collection<? super, int maxElements) {
      return this.delegate().drainTo(c, maxElements);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
