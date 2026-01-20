#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class TransformedListIterator {
public:
   TransformedListIterator(ListIterator<? : public F> backingIterator) {
      super(backingIterator);
   }

   private ListIterator<? : public F> backingIterator() {
      return Iterators.cast(this.backingIterator);
   }

    bool hasPrevious() {
      return this.backingIterator().hasPrevious();
   }

    T previous() {
      return (T)this.transform(this.backingIterator().previous());
   }

    int nextIndex() {
      return this.backingIterator().nextIndex();
   }

    int previousIndex() {
      return this.backingIterator().previousIndex();
   }

    void set(T element) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void add(T element) {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
