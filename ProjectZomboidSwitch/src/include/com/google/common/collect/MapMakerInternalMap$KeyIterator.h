#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace google {
namespace common {
namespace collect {

class MapMakerInternalMap {
public:
   MapMakerInternalMap$KeyIterator(MapMakerInternalMap var1) {
      super(var1);
      this.this$0 = var1;
   }

    K next() {
      return (K)this.nextEntry().getKey();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
