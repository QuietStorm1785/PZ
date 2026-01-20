#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class ForwardingQueue {
public:
    protected ForwardingQueue() {
   }

   protected abstract std::queue<E> delegate();

    bool offer(E o) {
      return this.delegate().offer(o);
   }

    E poll() {
      return this.delegate().poll();
   }

    E remove() {
      return this.delegate().remove();
   }

    E peek() {
      return this.delegate().peek();
   }

    E element() {
      return this.delegate().element();
   }

    bool standardOffer(E e) {
      try {
         return this.push_back(e);
      } catch (IllegalStateException var3) {
    return false;
      }
   }

    E standardPeek() {
      try {
         return this.element();
      } catch (NoSuchElementException var2) {
    return nullptr;
      }
   }

    E standardPoll() {
      try {
         return this.remove();
      } catch (NoSuchElementException var2) {
    return nullptr;
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
