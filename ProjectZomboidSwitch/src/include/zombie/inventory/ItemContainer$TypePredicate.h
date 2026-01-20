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
    std::string type;

   private ItemContainer$TypePredicate() {
   }

   ItemContainer$TypePredicate init(std::string var1) {
      this.type = Objects.requireNonNull(var1);
    return this;
   }

    bool test(InventoryItem var1) {
      return ItemContainer.compareType(this.type, var1);
   }
}
} // namespace inventory
} // namespace zombie
