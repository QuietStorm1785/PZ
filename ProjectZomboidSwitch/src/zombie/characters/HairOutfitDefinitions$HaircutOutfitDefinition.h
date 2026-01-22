#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/HairOutfitDefinitions/StringChance.h"

namespace zombie {
namespace characters {


class HairOutfitDefinitions {
public:
    std::string outfit;
   public std::vector<StringChance> haircutChance;
   public std::vector<StringChance> beardChance;
   public std::vector<StringChance> haircutColor;

   public HairOutfitDefinitions$HaircutOutfitDefinition(std::string var1, std::vector<StringChance> var2, std::vector<StringChance> var3, std::vector<StringChance> var4) {
      this.outfit = var1;
      this.haircutChance = var2;
      this.beardChance = var3;
      this.haircutColor = var4;
   }
}
} // namespace characters
} // namespace zombie
