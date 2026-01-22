#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/inventory/InventoryItem.h"
#include "zombie/scripting/objects/Item.h"
#include "zombie/scripting/objects/Item/Type.h"

namespace zombie {
namespace inventory {
namespace types {


class ComboItem : public InventoryItem {
public:
    public ComboItem(const std::string& var1, const std::string& var2, const std::string& var3, const std::string& var4) {
      super(var1, var2, var3, var4);
   }

    public ComboItem(const std::string& var1, const std::string& var2, const std::string& var3, Item var4) {
      super(var1, var2, var3, var4);
   }

    int getSaveType() {
      return Type.Normal.ordinal();
   }
}
} // namespace types
} // namespace inventory
} // namespace zombie
