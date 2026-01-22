#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/ItemContainer.h"
#include <filesystem>

namespace zombie {
namespace iso {
namespace objects {
namespace interfaces {


class IClothingWasherDryerLogic {
public:
    virtual ~IClothingWasherDryerLogic() = default;
    void update();

    void saveChange(const std::string& var1, KahluaTable var2, ByteBuffer var3);

    void loadChange(const std::string& var1, ByteBuffer var2);

    ItemContainer getContainer();

    bool isItemAllowedInContainer(ItemContainer var1, InventoryItem var2);

    bool isRemoveItemAllowedFromContainer(ItemContainer var1, InventoryItem var2);

    bool isActivated();

    void setActivated(bool var1);

    void switchModeOn();

    void switchModeOff();
}
} // namespace interfaces
} // namespace objects
} // namespace iso
} // namespace zombie
