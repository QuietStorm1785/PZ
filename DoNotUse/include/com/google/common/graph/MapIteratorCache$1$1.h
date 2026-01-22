#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/UnmodifiableIterator.h"
#include "com/google/common/graph/MapIteratorCache/1.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace graph {


class MapIteratorCache {
public:
   MapIteratorCache$1$1(1 var1, Iterator var2) {
      this.this$1 = var1;
      this.val$entryIterator = var2;
   }

    bool hasNext() {
      return this.val$entryIterator.hasNext();
   }

    K next() {
      Entry<K, V> entry = (Entry<K, V>)this.val$entryIterator.next();
      MapIteratorCache.access$102(this.this$1.this$0, entry);
      return (K)entry.getKey();
   }
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
