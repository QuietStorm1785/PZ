#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Ordering.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace reflect {


class TypeToken {
public:
   TypeToken$TypeCollector$4(Comparator var1, Map var2) {
      this.val$valueComparator = var1;
      this.val$map = var2;
   }

    int compare(K left, K right) {
      return this.val$valueComparator.compare(this.val$map.get(left), this.val$map.get(right));
   }
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
