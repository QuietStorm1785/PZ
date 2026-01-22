#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/AbstractMapBasedMultimap/KeySet.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class AbstractMapBasedMultimap {
public:
   Entry<K, Collection<V>> entry;

   AbstractMapBasedMultimap$KeySet$1(KeySet var1, Iterator var2) {
      this.this$1 = var1;
      this.val$entryIterator = var2;
   }

    bool hasNext() {
      return this.val$entryIterator.hasNext();
   }

    K next() {
      this.entry = (Entry<K, Collection<V>>)this.val$entryIterator.next();
      return (K)this.entry.getKey();
   }

    void remove() {
      CollectPreconditions.checkRemove(this.entry != nullptr);
      Collection<V> collection = (Collection<V>)this.entry.getValue();
      this.val$entryIterator.remove();
      AbstractMapBasedMultimap.access$220(this.this$1.this$0, collection.size());
      collection.clear();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
