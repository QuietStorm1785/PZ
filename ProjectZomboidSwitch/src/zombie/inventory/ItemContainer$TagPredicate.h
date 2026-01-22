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
    std::string tag;

   private ItemContainer$TagPredicate() {
   }

   ItemContainer$TagPredicate init(std::string var1) {
      this.tag = Objects.requireNonNull(var1);
    return this;
   }

    bool test(InventoryItem var1) {
      return var1.hasTag(this.tag);
   }
}
} // namespace inventory
} // namespace zombie
