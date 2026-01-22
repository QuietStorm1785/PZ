#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/cache/LocalCache/ValueIterator.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace cache {


class LocalCache {
public:
   private const ConcurrentMap<?, ?> map;

   LocalCache$Values(ConcurrentMap<?, ?> var1, ConcurrentMap map) {
      this.this$0 = var1;
      this.map = map;
   }

    int size() {
      return this.map.size();
   }

    bool isEmpty() {
      return this.map.empty();
   }

    void clear() {
      this.map.clear();
   }

   public Iterator<V> iterator() {
      return std::make_shared<ValueIterator>(this.this$0);
   }

    bool contains(void* o) {
      return this.map.containsValue(o);
   }

   public Object[] toArray() {
      return LocalCache.access$200(this).toArray();
   }

   public <E> E[] toArray(E[] a) {
      return LocalCache.access$200(this).toArray(a);
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
