#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/j2objc/annotations/Weak.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace cache {


class LocalCache {
public:
   const ConcurrentMap<?, ?> map;

   LocalCache$AbstractCacheSet(ConcurrentMap<?, ?> var1, ConcurrentMap map) {
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
