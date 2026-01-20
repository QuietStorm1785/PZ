#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/inventory/InventoryItem.h"

namespace zombie {
namespace characters {
namespace WornItems {


class WornItem {
public:
    const std::string location;
    const InventoryItem item;

    public WornItem(const std::string& var1, InventoryItem var2) {
      if (var1 == nullptr) {
         throw NullPointerException("location is nullptr");
      } else if (var1.empty()) {
         throw IllegalArgumentException("location is empty");
      } else if (var2 == nullptr) {
         throw NullPointerException("item is nullptr");
      } else {
         this.location = var1;
         this.item = var2;
      }
   }

    std::string getLocation() {
      return this.location;
   }

    InventoryItem getItem() {
      return this.item;
   }
}
} // namespace WornItems
} // namespace characters
} // namespace zombie
