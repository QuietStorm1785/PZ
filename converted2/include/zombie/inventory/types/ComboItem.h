#pragma once
#include "zombie/inventory/InventoryItem.h"
#include "zombie/scripting/objects/Item.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace inventory {
namespace types {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ComboItem : public InventoryItem {
public:
public
  ComboItem(const std::string &module, const std::string &name,
            const std::string &itemType, const std::string &texName) {
    super(module, name, itemType, texName);
  }

public
  ComboItem(const std::string &module, const std::string &name,
            const std::string &itemType, Item item) {
    super(module, name, itemType, item);
  }

  int getSaveType() { return Item.Type.Normal.ordinal(); }
}
} // namespace types
} // namespace inventory
} // namespace zombie
