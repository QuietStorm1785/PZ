#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/AbstractMapBasedMultiset/1/1.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class AbstractMapBasedMultiset {
public:
   Entry<E, Count> toRemove;

   AbstractMapBasedMultiset$1(AbstractMapBasedMultiset var1, Iterator var2) {
      this.this$0 = var1;
      this.val$backingEntries = var2;
   }

    bool hasNext() {
      return this.val$backingEntries.hasNext();
   }

   public com.google.common.collect.Multiset.Entry<E> next() {
      Entry<E, Count> mapEntry = (Entry<E, Count>)this.val$backingEntries.next();
      this.toRemove = mapEntry;
      return std::make_shared<1>(this, mapEntry);
   }

    void remove() {
      CollectPreconditions.checkRemove(this.toRemove != nullptr);
      AbstractMapBasedMultiset.access$122(this.this$0, this.toRemove.getValue().getAndSet(0));
      this.val$backingEntries.remove();
      this.toRemove = nullptr;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
