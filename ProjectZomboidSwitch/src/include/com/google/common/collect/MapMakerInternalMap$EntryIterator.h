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
namespace collect {


class MapMakerInternalMap {
public:
   MapMakerInternalMap$EntryIterator(MapMakerInternalMap var1) {
      super(var1);
      this.this$0 = var1;
   }

   public Entry<K, V> next() {
      return this.nextEntry();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
