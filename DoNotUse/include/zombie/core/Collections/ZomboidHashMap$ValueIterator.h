#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace Collections {

class ZomboidHashMap {
public:
   private ZomboidHashMap$ValueIterator(ZomboidHashMap var1) {
      super(var1);
      this.this$0 = var1;
   }

    V next() {
      return (V)this.nextEntry().value;
   }
}
} // namespace Collections
} // namespace core
} // namespace zombie
