#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/HashBiMap/BiEntry.h"
#include "com/google/common/collect/HashBiMap/KeySet.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class HashBiMap {
public:
   HashBiMap$KeySet$1(KeySet var1) {
      super(var1.this$0);
      this.this$1 = var1;
   }

    K output(V> entry) {
      return (K)entry.key;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
