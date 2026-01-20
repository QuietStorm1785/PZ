#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/UnderwearDefinition/StringChance.h"

namespace zombie {
namespace characters {


class UnderwearDefinition {
public:
   public std::vector<StringChance> top;
    int topTotalChance = 0;
    std::string bottom;
    int chanceToSpawn;
    bool female = false;

   public UnderwearDefinition$OutfitUnderwearDefinition(std::vector<StringChance> var1, std::string var2, int var3, std::string var4) {
      this.top = var1;
      if (var1 != nullptr) {
         for (int var5 = 0; var5 < var1.size(); var5++) {
            this.topTotalChance = (int)(this.topTotalChance + ((StringChance)var1.get(var5)).chance);
         }
      }

      this.bottom = var2;
      this.chanceToSpawn = var3;
      if ("female" == var4)) {
         this.female = true;
      }
   }
}
} // namespace characters
} // namespace zombie
