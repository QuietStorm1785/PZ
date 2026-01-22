#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Preconditions.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class TransformedIterator {
public:
   const Iterator<? : public F> backingIterator;

   TransformedIterator(Iterator<? : public F> backingIterator) {
      this.backingIterator = (Iterator<? : public F>)Preconditions.checkNotNull(backingIterator);
   }

   abstract T transform(F var1);

    bool hasNext() {
      return this.backingIterator.hasNext();
   }

    T next() {
      return this.transform((F)this.backingIterator.next());
   }

    void remove() {
      this.backingIterator.remove();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
