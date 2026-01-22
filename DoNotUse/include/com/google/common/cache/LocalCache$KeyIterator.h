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
namespace cache {

class LocalCache {
public:
   LocalCache$KeyIterator(LocalCache var1) {
      super(var1);
      this.this$0 = var1;
   }

    K next() {
      return (K)this.nextEntry().getKey();
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
