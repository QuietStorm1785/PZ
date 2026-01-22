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
    std::string category;

   private ItemContainer$CategoryPredicate() {
   }

   ItemContainer$CategoryPredicate init(std::string var1) {
      this.category = Objects.requireNonNull(var1);
    return this;
   }

    bool test(InventoryItem var1) {
      return var1.getCategory() == this.category);
   }
}
} // namespace inventory
} // namespace zombie
