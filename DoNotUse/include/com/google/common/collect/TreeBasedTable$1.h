#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Function.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class TreeBasedTable {
public:
   TreeBasedTable$1(TreeBasedTable var1) {
      this.this$0 = var1;
   }

   public Iterator<C> apply(Map<C, V> input) {
      return input.keySet().iterator();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
