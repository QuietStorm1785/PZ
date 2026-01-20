#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Iterators {
public:
   private const Iterator<? : public E> iterator;
    bool hasPeeked;
    E peekedElement;

   public Iterators$PeekingImpl(Iterator<? : public E> iterator) {
      this.iterator = (Iterator<? : public E>)Preconditions.checkNotNull(iterator);
   }

    bool hasNext() {
      return this.hasPeeked || this.iterator.hasNext();
   }

    E next() {
      if (!this.hasPeeked) {
         return (E)this.iterator.next();
      } else {
    E result = this.peekedElement;
         this.hasPeeked = false;
         this.peekedElement = nullptr;
    return result;
      }
   }

    void remove() {
      Preconditions.checkState(!this.hasPeeked, "Can't remove after you've peeked at next");
      this.iterator.remove();
   }

    E peek() {
      if (!this.hasPeeked) {
         this.peekedElement = (E)this.iterator.next();
         this.hasPeeked = true;
      }

      return this.peekedElement;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
