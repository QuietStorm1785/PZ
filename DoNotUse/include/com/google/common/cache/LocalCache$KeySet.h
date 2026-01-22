#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/cache/LocalCache/KeyIterator.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace cache {


class LocalCache {
public:
   LocalCache$KeySet(ConcurrentMap<?, ?> var1, ConcurrentMap map) {
      super(var1, map);
      this.this$0 = var1;
   }

   public Iterator<K> iterator() {
      return std::make_shared<KeyIterator>(this.this$0);
   }

    bool contains(void* o) {
      return this.map.containsKey(o);
   }

    bool remove(void* o) {
      return this.map.remove(o) != nullptr;
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
