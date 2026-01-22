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
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class ForwardingDeque {
public:
    protected ForwardingDeque() {
   }

   protected abstract std::deque<E> delegate();

    void addFirst(E e) {
      this.delegate().addFirst(e);
   }

    void addLast(E e) {
      this.delegate().addLast(e);
   }

   public Iterator<E> descendingIterator() {
      return this.delegate().descendingIterator();
   }

    E getFirst() {
      return this.delegate().getFirst();
   }

    E getLast() {
      return this.delegate().getLast();
   }

    bool offerFirst(E e) {
      return this.delegate().offerFirst(e);
   }

    bool offerLast(E e) {
      return this.delegate().offerLast(e);
   }

    E peekFirst() {
      return this.delegate().peekFirst();
   }

    E peekLast() {
      return this.delegate().peekLast();
   }

    E pollFirst() {
      return this.delegate().pollFirst();
   }

    E pollLast() {
      return this.delegate().pollLast();
   }

    E pop() {
      return this.delegate().pop();
   }

    void push(E e) {
      this.delegate().push(e);
   }

    E removeFirst() {
      return this.delegate().removeFirst();
   }

    E removeLast() {
      return this.delegate().removeLast();
   }

    bool removeFirstOccurrence(void* o) {
      return this.delegate().removeFirstOccurrence(o);
   }

    bool removeLastOccurrence(void* o) {
      return this.delegate().removeLastOccurrence(o);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
