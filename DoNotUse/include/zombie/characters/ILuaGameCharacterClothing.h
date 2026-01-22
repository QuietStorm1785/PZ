#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/WornItems/BodyLocationGroup.h"
#include "zombie/characters/WornItems/WornItems.h"
#include "zombie/inventory/InventoryItem.h"

namespace zombie {
namespace characters {


class ILuaGameCharacterClothing {
public:
    virtual ~ILuaGameCharacterClothing() = default;
    void dressInNamedOutfit(const std::string& var1);

    void dressInPersistentOutfit(const std::string& var1);

    void dressInPersistentOutfitID(int var1);

    std::string getOutfitName();

    WornItems getWornItems();

    void setWornItems(WornItems var1);

    InventoryItem getWornItem(const std::string& var1);

    void setWornItem(const std::string& var1, InventoryItem var2);

    void removeWornItem(InventoryItem var1);

    void clearWornItems();

    BodyLocationGroup getBodyLocationGroup();

    void setClothingItem_Head(InventoryItem var1);

    void setClothingItem_Torso(InventoryItem var1);

    void setClothingItem_Back(InventoryItem var1);

    void setClothingItem_Hands(InventoryItem var1);

    void setClothingItem_Legs(InventoryItem var1);

    void setClothingItem_Feet(InventoryItem var1);

    void Dressup(SurvivorDesc var1);
}
} // namespace characters
} // namespace zombie
