#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/HashBiMap/BiEntry.h"
#include "com/google/common/collect/HashBiMap/Inverse/1.h"
#include "com/google/common/collect/HashBiMap/Inverse/1/1/InverseEntry.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class HashBiMap {
public:
   HashBiMap$Inverse$1$1(1 var1) {
      super(var1.this$1.this$0);
      this.this$2 = var1;
   }

   Entry<V, K> output(BiEntry<K, V> entry) {
      return std::make_shared<InverseEntry>(this, entry);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
