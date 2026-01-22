#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/skills/PerkFactory/Perk.h"

namespace zombie {
namespace characters {


class IsoGameCharacter {
public:
    int level;
    Perk perk;

   public IsoGameCharacter$PerkInfo(IsoGameCharacter var1) {
      this.this$0 = var1;
      this.level = 0;
   }

    int getLevel() {
      return this.level;
   }
}
} // namespace characters
} // namespace zombie
