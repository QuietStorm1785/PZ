#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/skills/PerkFactory/Perk.h"
#include "zombie/characters/skills/PerkFactory/Perks.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/scripting/objects/Recipe/RequiredSkill.h"
#include "zombie/scripting/objects/Recipe/Result.h"
#include "zombie/scripting/objects/Recipe/Source.h"
#include <algorithm>

namespace zombie {
namespace scripting {
namespace objects {


class MovableRecipe : public Recipe {
public:
    bool isValid = false;
    std::string worldSprite = "";
    Perk xpPerk = Perks.MAX;
    Source primaryTools;
    Source secondaryTools;

    public MovableRecipe() {
      this.AnimNode = "Disassemble";
      this.removeResultItem = true;
      this.AllowDestroyedItem = false;
      this.name = "Disassemble Movable";
      this.setCanBeDoneFromFloor(false);
   }

    void setResult(const std::string& var1, int var2) {
    Result var3 = std::make_shared<Result>();
      var3.count = var2;
      if (var1.contains(".")) {
         var3.type = var1.split("\\.")[1];
         var3.module = var1.split("\\.")[0];
      } else {
         DebugLog.log("MovableRecipe invalid result item. item = " + var1);
      }

      this.Result = var3;
   }

    void setSource(const std::string& var1) {
    Source var2 = std::make_shared<Source>();
      var2.getItems().push_back(var1);
      this.Source.push_back(var2);
   }

    void setTool(const std::string& var1, bool var2) {
    Source var3 = std::make_shared<Source>();
      var3.keep = true;
      if (var1.contains("/")) {
         var1 = var1.replaceFirst("keep ", "").trim();
         var3.getItems().addAll(Arrays.asList(var1.split("/")));
      } else {
         var3.getItems().push_back(var1);
      }

      if (var2) {
         this.primaryTools = var3;
      } else {
         this.secondaryTools = var3;
      }

      this.Source.push_back(var3);
   }

    Source getPrimaryTools() {
      return this.primaryTools;
   }

    Source getSecondaryTools() {
      return this.secondaryTools;
   }

    void setRequiredSkill(Perk var1, int var2) {
    RequiredSkill var3 = std::make_shared<RequiredSkill>(var1, var2);
      this.skillRequired.push_back(var3);
   }

    void setXpPerk(Perk var1) {
      this.xpPerk = var1;
   }

    Perk getXpPerk() {
      return this.xpPerk;
   }

    bool hasXpPerk() {
      return this.xpPerk != Perks.MAX;
   }

    void setOnCreate(const std::string& var1) {
      this.LuaCreate = var1;
   }

    void setOnXP(const std::string& var1) {
      this.LuaGiveXP = var1;
   }

    void setTime(float var1) {
      this.TimeToMake = var1;
   }

    void setName(const std::string& var1) {
      this.name = var1;
   }

    std::string getWorldSprite() {
      return this.worldSprite;
   }

    void setWorldSprite(const std::string& var1) {
      this.worldSprite = var1;
   }

    bool isValid() {
      return this.isValid;
   }

    void setValid(bool var1) {
      this.isValid = var1;
   }
}
} // namespace objects
} // namespace scripting
} // namespace zombie
