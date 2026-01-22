#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/HashBiMap/BiEntry.h"
#include "com/google/common/collect/HashBiMap/Inverse/InverseKeySet.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class HashBiMap {
public:
   HashBiMap$Inverse$InverseKeySet$1(InverseKeySet var1) {
      super(var1.this$1.this$0);
      this.this$2 = var1;
   }

    V output(V> entry) {
      return (V)entry.value;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
