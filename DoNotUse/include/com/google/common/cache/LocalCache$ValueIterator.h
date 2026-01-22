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
   LocalCache$ValueIterator(LocalCache var1) {
      super(var1);
      this.this$0 = var1;
   }

    V next() {
      return (V)this.nextEntry().getValue();
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
