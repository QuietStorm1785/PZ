#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/skills/PerkFactory/Perk.h"
#include "zombie/characters/skills/PerkFactory/Perks.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/interfaces/IListBoxItem.h"
#include <algorithm>

namespace zombie {
namespace characters {
namespace traits {


class TraitFactory {
public:
    std::string traitID;
    std::string name;
    int cost;
    std::string description;
    bool prof;
    Texture texture = nullptr;
    bool removeInMP = false;
   private List<std::string> freeRecipes = std::make_unique<std::vector<>>();
   public std::vector<std::string> MutuallyExclusive = new std::vector<>(0);
   public std::unordered_map<Perk, int> XPBoostMap = std::make_unique<std::unordered_map<>>();

    void addXPBoost(Perk var1, int var2) {
      if (var1 != nullptr && var1 != Perks.None && var1 != Perks.MAX) {
         this.XPBoostMap.put(var1, var2);
      } else {
         DebugLog.General.warn("invalid perk passed to Trait.addXPBoost trait=%s perk=%s", new Object[]{this.name, var1});
      }
   }

   public List<std::string> getFreeRecipes() {
      return this.freeRecipes;
   }

    void setFreeRecipes(List<std::string> var1) {
      this.freeRecipes = var1;
   }

   public TraitFactory$Trait(std::string var1, std::string var2, int var3, std::string var4, boolean var5, boolean var6) {
      this.traitID = var1;
      this.name = var2;
      this.cost = var3;
      this.description = var4;
      this.prof = var5;
      this.texture = Texture.getSharedTexture("media/ui/Traits/trait_" + this.traitID.toLowerCase(Locale.ENGLISH) + ".png");
      if (this.texture == nullptr) {
         this.texture = Texture.getSharedTexture("media/ui/Traits/trait_generic.png");
      }

      this.removeInMP = var6;
   }

    std::string getType() {
      return this.traitID;
   }

    Texture getTexture() {
      return this.texture;
   }

    std::string getLabel() {
      return this.name;
   }

    std::string getLeftLabel() {
      return this.name;
   }

    std::string getRightLabel() {
    int var1 = this.cost;
      if (var1 == 0) {
         return "";
      } else {
    std::string var2 = "+";
         if (var1 > 0) {
            var2 = "-";
         } else if (var1 == 0) {
            var2 = "";
         }

         if (var1 < 0) {
            var1 = -var1;
         }

         return var2 + std::make_shared<int>(var1);
      }
   }

    int getCost() {
      return this.cost;
   }

    bool isFree() {
      return this.prof;
   }

    std::string getDescription() {
      return this.description;
   }

    void setDescription(const std::string& var1) {
      this.description = var1;
   }

   public std::vector<std::string> getMutuallyExclusiveTraits() {
      return this.MutuallyExclusive;
   }

   public std::unordered_map<Perk, int> getXPBoostMap() {
      return this.XPBoostMap;
   }

    bool isRemoveInMP() {
      return this.removeInMP;
   }

    void setRemoveInMP(bool var1) {
      this.removeInMP = var1;
   }
}
} // namespace traits
} // namespace characters
} // namespace zombie
