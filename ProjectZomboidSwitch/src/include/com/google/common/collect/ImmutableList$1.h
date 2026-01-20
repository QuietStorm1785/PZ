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

class ImmutableList {
public:
   ImmutableList$1(ImmutableList var1, int x0, int x1) {
      super(x0, x1);
      this.this$0 = var1;
   }

    E get(int index) {
      return (E)this.this$0.get(index);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
