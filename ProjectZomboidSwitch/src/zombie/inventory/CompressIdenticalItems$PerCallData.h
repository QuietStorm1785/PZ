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


class CompressIdenticalItems {
public:
   const std::vector<std::string> types = std::make_unique<std::vector<>>();
   const std::unordered_map<std::string, std::vector<InventoryItem>> typeToItems = std::make_unique<std::unordered_map<>>();
   const ArrayDeque<std::vector<InventoryItem>> itemLists = std::make_unique<ArrayDeque<>>();
   const std::vector<InventoryItem> savedItems = std::make_unique<std::vector<>>();
   CompressIdenticalItems$PerCallData next;

   private CompressIdenticalItems$PerCallData() {
   }

    void reset() {
      for (int var1 = 0; var1 < this.types.size(); var1++) {
    std::vector var2 = this.typeToItems.get(this.types.get(var1));
         var2.clear();
         this.itemLists.push(var2);
      }

      this.types.clear();
      this.typeToItems.clear();
      this.savedItems.clear();
   }

   std::vector<InventoryItem> allocItemList() {
      return this.itemLists.empty() ? std::make_unique<std::vector<>>() : this.itemLists.pop();
   }
}
} // namespace inventory
} // namespace zombie
