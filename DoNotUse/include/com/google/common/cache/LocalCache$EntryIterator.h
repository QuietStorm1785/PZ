#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace cache {


class LocalCache {
public:
   LocalCache$EntryIterator(LocalCache var1) {
      super(var1);
      this.this$0 = var1;
   }

   public Entry<K, V> next() {
      return this.nextEntry();
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
