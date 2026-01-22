#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/AttachedItems/AttachedItems.h"
#include "zombie/characters/AttachedItems/AttachedLocationGroup.h"
#include "zombie/inventory/InventoryItem.h"

namespace zombie {
namespace characters {


class ILuaGameCharacterAttachedItems {
public:
    virtual ~ILuaGameCharacterAttachedItems() = default;
    AttachedItems getAttachedItems();

    void setAttachedItems(AttachedItems var1);

    InventoryItem getAttachedItem(const std::string& var1);

    void setAttachedItem(const std::string& var1, InventoryItem var2);

    void removeAttachedItem(InventoryItem var1);

    void clearAttachedItems();

    AttachedLocationGroup getAttachedLocationGroup();
}
} // namespace characters
} // namespace zombie
