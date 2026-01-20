#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/AbstractMapBasedMultimap/WrappedCollection.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class AbstractMapBasedMultimap {
public:
   const Iterator<V> delegateIterator;
   const Collection<V> originalDelegate;

   AbstractMapBasedMultimap$WrappedCollection$WrappedIterator(WrappedCollection var1) {
      this.this$1 = var1;
      this.originalDelegate = this.this$1.delegate;
      this.delegateIterator = AbstractMapBasedMultimap.access$100(var1.this$0, var1.delegate);
   }

   AbstractMapBasedMultimap$WrappedCollection$WrappedIterator(Iterator<V> var1, Iterator delegateIterator) {
      this.this$1 = var1;
      this.originalDelegate = this.this$1.delegate;
      this.delegateIterator = delegateIterator;
   }

    void validateIterator() {
      this.this$1.refreshIfEmpty();
      if (this.this$1.delegate != this.originalDelegate) {
         throw std::make_unique<ConcurrentModificationException>();
      }
   }

    bool hasNext() {
      this.validateIterator();
      return this.delegateIterator.hasNext();
   }

    V next() {
      this.validateIterator();
      return (V)this.delegateIterator.next();
   }

    void remove() {
      this.delegateIterator.remove();
      AbstractMapBasedMultimap.access$210(this.this$1.this$0);
      this.this$1.removeIfEmpty();
   }

   Iterator<V> getDelegateIterator() {
      this.validateIterator();
      return this.delegateIterator;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
