#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/ZombiesZoneDefinition/ZZDOutfit.h"

namespace zombie {
namespace characters {


class ZombiesZoneDefinition {
public:
    std::string name;
    int femaleChance;
    int maleChance;
    int chanceToSpawn;
    int toSpawn;
   const std::vector<ZZDOutfit> outfits = std::make_unique<std::vector<>>();

   private ZombiesZoneDefinition$ZZDZone() {
   }
}
} // namespace characters
} // namespace zombie
