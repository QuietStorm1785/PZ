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
namespace AttachedItems {


class AttachedItem {
public:
    const std::string location;
    const InventoryItem item;

    public AttachedItem(const std::string& var1, InventoryItem var2) {
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
} // namespace AttachedItems
} // namespace characters
} // namespace zombie
