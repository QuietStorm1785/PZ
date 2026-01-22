#pragma once
#include <stack>
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
namespace professions {


class ProfessionFactory {
public:
    std::string type;
    std::string name;
    int cost;
    std::string description;
    std::string IconPath;
    Texture texture = nullptr;
   public std::stack<std::string> FreeTraitStack = std::make_unique<std::stack<>>();
   private List<std::string> freeRecipes = std::make_unique<std::vector<>>();
   public std::unordered_map<Perk, int> XPBoostMap = std::make_unique<std::unordered_map<>>();

   public ProfessionFactory$Profession(std::string var1, std::string var2, std::string var3, int var4, std::string var5) {
      this.type = var1;
      this.name = var2;
      this.IconPath = var3;
      if (!var3 == "")) {
         this.texture = Texture.trygetTexture(var3);
      }

      this.cost = var4;
      this.description = var5;
   }

    Texture getTexture() {
      return this.texture;
   }

    void addFreeTrait(const std::string& var1) {
      this.FreeTraitStack.push_back(var1);
   }

   public std::vector<std::string> getFreeTraits() {
    std::vector var1 = new std::vector();
      var1.addAll(this.FreeTraitStack);
    return var1;
   }

    std::string getLabel() {
      return this.getName();
   }

    std::string getIconPath() {
      return this.IconPath;
   }

    std::string getLeftLabel() {
      return this.getName();
   }

    std::string getRightLabel() {
    int var1 = this.getCost();
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

         return var2 + var1;
      }
   }

    std::string getType() {
      return this.type;
   }

    void setType(const std::string& var1) {
      this.type = var1;
   }

    std::string getName() {
      return this.name;
   }

    void setName(const std::string& var1) {
      this.name = var1;
   }

    int getCost() {
      return this.cost;
   }

    void setCost(int var1) {
      this.cost = var1;
   }

    std::string getDescription() {
      return this.description;
   }

    void setDescription(const std::string& var1) {
      this.description = var1;
   }

    void setIconPath(const std::string& var1) {
      this.IconPath = var1;
   }

   public std::stack<std::string> getFreeTraitStack() {
      return this.FreeTraitStack;
   }

    void addXPBoost(Perk var1, int var2) {
      if (var1 != nullptr && var1 != Perks.None && var1 != Perks.MAX) {
         this.XPBoostMap.put(var1, var2);
      } else {
         DebugLog.General.warn("invalid perk passed to Profession.addXPBoost profession=%s perk=%s", new Object[]{this.name, var1});
      }
   }

   public std::unordered_map<Perk, int> getXPBoostMap() {
      return this.XPBoostMap;
   }

    void setFreeTraitStack(std::stack<std::string> var1) {
      this.FreeTraitStack = var1;
   }

   public List<std::string> getFreeRecipes() {
      return this.freeRecipes;
   }

    void setFreeRecipes(List<std::string> var1) {
      this.freeRecipes = var1;
   }
}
} // namespace professions
} // namespace characters
} // namespace zombie
