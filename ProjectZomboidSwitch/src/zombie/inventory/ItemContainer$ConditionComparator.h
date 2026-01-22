#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace zombie {
namespace inventory {


class ItemContainer {
public:
   private ItemContainer$ConditionComparator() {
   }

    int compare(InventoryItem var1, InventoryItem var2) {
      return var1.getCondition() - var2.getCondition();
   }
}
} // namespace inventory
} // namespace zombie
