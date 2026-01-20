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
   public ItemPickerItem[] Items = new ItemPickerItem[0];
    float rolls;
    bool noAutoAge;
    int fillRand;
    int maxMap;
    int stashChance;
   public ItemPickerJava$ItemPickerContainer junk;
    bool procedural;
    bool dontSpawnAmmo = false;
    bool ignoreZombieDensity = false;
   public std::vector<ProceduralItem> proceduralItems;
}
} // namespace inventory
} // namespace zombie
