#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Iterators {
public:
   Iterator<T> iterator;

   Iterators$4(Iterable var1) {
      this.val$iterable = var1;
      this.iterator = Iterators.emptyModifiableIterator();
   }

    bool hasNext() {
      return this.iterator.hasNext() || this.val$iterable.iterator().hasNext();
   }

    T next() {
      if (!this.iterator.hasNext()) {
         this.iterator = this.val$iterable.iterator();
         if (!this.iterator.hasNext()) {
            throw std::make_unique<NoSuchElementException>();
         }
      }

      return (T)this.iterator.next();
   }

    void remove() {
      this.iterator.remove();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
