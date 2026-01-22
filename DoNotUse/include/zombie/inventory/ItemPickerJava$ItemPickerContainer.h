#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/inventory/ItemPickerJava/ItemPickerItem.h"
#include "zombie/inventory/ItemPickerJava/ProceduralItem.h"

namespace zombie {
namespace inventory {

class ItemPickerJava {
public:
    std::vector<std::shared_ptr<ItemPickerItem>> Items;
    float rolls;
    bool noAutoAge;
    int fillRand;
    int maxMap;
    int stashChance;
    std::shared_ptr<ItemPickerJava> junk;  // Assuming it's a reference to another ItemPickerJava instance
    bool procedural;
    bool dontSpawnAmmo = false;
    bool ignoreZombieDensity = false;
    std::vector<std::shared_ptr<ProceduralItem>> proceduralItems;
};

} // namespace inventory
} // namespace zombie
