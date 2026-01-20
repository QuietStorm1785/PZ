#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/UnmodifiableIterator.h"
#include "com/google/common/graph/MapIteratorCache/1/1.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace graph {


class MapIteratorCache {
public:
   MapIteratorCache$1(MapIteratorCache var1) {
      this.this$0 = var1;
   }

   public UnmodifiableIterator<K> iterator() {
      Iterator<Entry<K, V>> entryIterator = MapIteratorCache.access$000(this.this$0).entrySet().iterator();
      return std::make_shared<1>(this, entryIterator);
   }

    int size() {
      return MapIteratorCache.access$000(this.this$0).size();
   }

    bool contains(@Nullable Object) {
      return this.this$0.containsKey(key);
   }
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
