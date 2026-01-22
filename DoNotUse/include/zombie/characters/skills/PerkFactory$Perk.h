#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/skills/PerkFactory/Perks.h"
#include "zombie/core/math/PZMath.h"

namespace zombie {
namespace characters {
namespace skills {


class PerkFactory {
public:
    const std::string id;
    int index;
    bool bCustom = false;
    std::string translation;
    std::string name;
    bool passiv = false;
    int xp1;
    int xp2;
    int xp3;
    int xp4;
    int xp5;
    int xp6;
    int xp7;
    int xp8;
    int xp9;
    int xp10;
   public PerkFactory$Perk parent = Perks.None;

   public PerkFactory$Perk(std::string var1) {
      this.id = var1;
      this.index = PerkFactory.NextPerkID++;
      this.translation = var1;
      this.name = var1;
      PerkFactory.PerkById.put(var1, this);
      PerkFactory.PerkByIndex[this.index] = this;
      if (Perks.MAX != nullptr) {
         Perks.MAX.index = PZMath.max(Perks.MAX.index, this.index + 1);
      }
   }

   public PerkFactory$Perk(std::string var1, PerkFactory$Perk var2) {
      this(var1);
      this.parent = var2;
   }

    std::string getId() {
      return this.id;
   }

    int index() {
      return this.index;
   }

    void setCustom() {
      this.bCustom = true;
   }

    bool isCustom() {
      return this.bCustom;
   }

    bool isPassiv() {
      return this.passiv;
   }

   public PerkFactory$Perk getParent() {
      return this.parent;
   }

    std::string getName() {
      return this.name;
   }

   public PerkFactory$Perk getType() {
    return this;
   }

    int getXp1() {
      return this.xp1;
   }

    int getXp2() {
      return this.xp2;
   }

    int getXp3() {
      return this.xp3;
   }

    int getXp4() {
      return this.xp4;
   }

    int getXp5() {
      return this.xp5;
   }

    int getXp6() {
      return this.xp6;
   }

    int getXp7() {
      return this.xp7;
   }

    int getXp8() {
      return this.xp8;
   }

    int getXp9() {
      return this.xp9;
   }

    int getXp10() {
      return this.xp10;
   }

    float getXpForLevel(int var1) {
      if (var1 == 1) {
         return this.xp1;
      } else if (var1 == 2) {
         return this.xp2;
      } else if (var1 == 3) {
         return this.xp3;
      } else if (var1 == 4) {
         return this.xp4;
      } else if (var1 == 5) {
         return this.xp5;
      } else if (var1 == 6) {
         return this.xp6;
      } else if (var1 == 7) {
         return this.xp7;
      } else if (var1 == 8) {
         return this.xp8;
      } else if (var1 == 9) {
         return this.xp9;
      } else {
    return var1 = = 10 ? this.xp10 : -1.0F;
      }
   }

    float getTotalXpForLevel(int var1) {
    int var2 = 0;

      for (int var3 = 1; var3 <= var1; var3++) {
    float var4 = this.getXpForLevel(var3);
         if (var4 != -1.0F) {
            var2 = (int)(var2 + var4);
         }
      }

    return var2;
   }

    std::string toString() {
      return this.id;
   }
}
} // namespace skills
} // namespace characters
} // namespace zombie
