#pragma once
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/ItemContainer.h"
#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace iso {
namespace objects {
namespace interfaces {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class IClothingWasherDryerLogic {
public:
 virtual ~IClothingWasherDryerLogic() = default;
 void update();

 void saveChange(const std::string &change, KahluaTable tbl, ByteBuffer bb);

 void loadChange(const std::string &change, ByteBuffer bb);

 ItemContainer getContainer();

 bool isItemAllowedInContainer(ItemContainer container, InventoryItem item);

 bool isRemoveItemAllowedFromContainer(ItemContainer container,
 InventoryItem item);

 bool isActivated();

 void setActivated(bool activated);

 void switchModeOn();

 void switchModeOff();
}
} // namespace interfaces
} // namespace objects
} // namespace iso
} // namespace zombie
