#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/HashBiMap/1/MapEntry.h"
#include "com/google/common/collect/HashBiMap/BiEntry.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class HashBiMap {
public:
   HashBiMap$1(HashBiMap var1) {
      super(var1);
      this.this$0 = var1;
   }

   Entry<K, V> output(BiEntry<K, V> entry) {
      return std::make_shared<MapEntry>(this, entry);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
