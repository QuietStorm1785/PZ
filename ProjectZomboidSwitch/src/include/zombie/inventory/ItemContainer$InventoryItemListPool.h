#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/inventory/ItemContainer/InventoryItemList.h"
#include "zombie/popman/ObjectPool.h"

namespace zombie {
namespace inventory {


class ItemContainer {
public:
   public ItemContainer$InventoryItemListPool() {
      super(InventoryItemList::new);
   }

    void release(InventoryItemList var1) {
      var1.clear();
      super.release(var1);
   }
}
} // namespace inventory
} // namespace zombie
