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

class Iterators {
public:
   Iterators$10(int x0, int x1, Object[] var3, int var4) {
      super(x0, x1);
      this.val$array = var3;
      this.val$offset = var4;
   }

    T get(int index) {
      return (T)this.val$array[this.val$offset + index];
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
