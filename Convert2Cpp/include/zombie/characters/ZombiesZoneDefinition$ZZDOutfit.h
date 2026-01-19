#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/ZombiesZoneDefinition/StringChance.h"

namespace zombie {
namespace characters {


class ZombiesZoneDefinition {
public:
    std::string name;
    std::string customName;
    float chance;
    int toSpawn;
    std::string gender;
    std::string mandatory;
    std::string room;
   ArrayList<StringChance> femaleHairStyles;
   ArrayList<StringChance> maleHairStyles;
   ArrayList<StringChance> beardStyles;

   private ZombiesZoneDefinition$ZZDOutfit() {
   }
}
} // namespace characters
} // namespace zombie
