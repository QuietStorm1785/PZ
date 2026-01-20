#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/AbstractMapBasedMultimap/AsMap.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class AbstractMapBasedMultimap {
public:
   const Iterator<Entry<K, Collection<V>>> delegateIterator;
   Collection<V> collection;

   AbstractMapBasedMultimap$AsMap$AsMapIterator(AsMap var1) {
      this.this$1 = var1;
      this.delegateIterator = this.this$1.submap.entrySet().iterator();
   }

    bool hasNext() {
      return this.delegateIterator.hasNext();
   }

   public Entry<K, Collection<V>> next() {
      Entry<K, Collection<V>> entry = (Entry<K, Collection<V>>)this.delegateIterator.next();
      this.collection = (Collection<V>)entry.getValue();
      return this.this$1.wrapEntry(entry);
   }

    void remove() {
      this.delegateIterator.remove();
      AbstractMapBasedMultimap.access$220(this.this$1.this$0, this.collection.size());
      this.collection.clear();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
