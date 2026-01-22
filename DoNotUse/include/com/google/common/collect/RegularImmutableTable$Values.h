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

class RegularImmutableTable {
public:
   private RegularImmutableTable$Values(RegularImmutableTable var1) {
      this.this$0 = var1;
   }

    int size() {
      return this.this$0.size();
   }

    V get(int index) {
      return (V)this.this$0.getValue(index);
   }

    bool isPartialView() {
    return true;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
