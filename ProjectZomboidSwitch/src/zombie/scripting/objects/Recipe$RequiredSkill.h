#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/skills/PerkFactory/Perk.h"

namespace zombie {
namespace scripting {
namespace objects {


class Recipe {
public:
    const Perk perk;
    const int level;

   public Recipe$RequiredSkill(Perk var1, int var2) {
      this.perk = var1;
      this.level = var2;
   }

    Perk getPerk() {
      return this.perk;
   }

    int getLevel() {
      return this.level;
   }
}
} // namespace objects
} // namespace scripting
} // namespace zombie
