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


class Maps {
public:
   Maps$5(Entry var1) {
      this.val$entry = var1;
   }

    K getKey() {
      return (K)this.val$entry.getKey();
   }

    V getValue() {
      return (V)this.val$entry.getValue();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
