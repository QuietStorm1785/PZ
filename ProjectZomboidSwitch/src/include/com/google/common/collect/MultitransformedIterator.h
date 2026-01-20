#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Preconditions.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class MultitransformedIterator {
public:
   const Iterator<? : public F> backingIterator;
   private Iterator<? : public T> current = Iterators.emptyIterator();
   private Iterator<? : public T> removeFrom;

   MultitransformedIterator(Iterator<? : public F> backingIterator) {
      this.backingIterator = (Iterator<? : public F>)Preconditions.checkNotNull(backingIterator);
   }

   abstract Iterator<? : public T> transform(F var1);

    bool hasNext() {
      Preconditions.checkNotNull(this.current);
      if (this.current.hasNext()) {
    return true;
      } else {
         while (this.backingIterator.hasNext()) {
            Preconditions.checkNotNull(this.current = this.transform((F)this.backingIterator.next()));
            if (this.current.hasNext()) {
    return true;
            }
         }

    return false;
      }
   }

    T next() {
      if (!this.hasNext()) {
         throw std::make_unique<NoSuchElementException>();
      } else {
         this.removeFrom = this.current;
         return (T)this.current.next();
      }
   }

    void remove() {
      CollectPreconditions.checkRemove(this.removeFrom != nullptr);
      this.removeFrom.remove();
      this.removeFrom = nullptr;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
