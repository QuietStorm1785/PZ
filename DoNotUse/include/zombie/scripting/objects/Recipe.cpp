#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/skills/PerkFactory.h"
#include "zombie/characters/skills/PerkFactory/Perk.h"
#include "zombie/characters/skills/PerkFactory/Perks.h"
#include "zombie/core/Translator.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/scripting/objects/Recipe/RequiredSkill.h"
#include "zombie/scripting/objects/Recipe/Result.h"
#include "zombie/scripting/objects/Recipe/Source.h"
#include "zombie/util/StringUtils.h"
#include <algorithm>

namespace zombie {
namespace scripting {
namespace objects {


class Recipe : public BaseScriptObject {
public:
    bool canBeDoneFromFloor = false;
    float TimeToMake;
    std::string Sound;
    std::string AnimNode;
    std::string Prop1;
    std::string Prop2;
   public const std::vector<Source> Source = std::make_unique<std::vector<>>();
    Result Result;
    bool AllowDestroyedItem;
    bool AllowFrozenItem;
    bool AllowRottenItem;
    bool InSameInventory;
    std::string LuaTest;
    std::string LuaCreate;
    std::string LuaGrab;
    std::string name;
    std::string originalname;
    std::string nearItem;
    std::string LuaCanPerform;
    std::string tooltip = nullptr;
   public std::vector<RequiredSkill> skillRequired = nullptr;
    std::string LuaGiveXP;
    bool needToBeLearn = false;
    std::string category = nullptr;
    bool removeResultItem = false;
    float heat = 0.0F;
    bool stopOnWalk = true;
    bool stopOnRun = true;
    bool hidden = false;

    bool isCanBeDoneFromFloor() {
      return this.canBeDoneFromFloor;
   }

    void setCanBeDoneFromFloor(bool var1) {
      this.canBeDoneFromFloor = var1;
   }

    public Recipe() {
      this.TimeToMake = 0.0F;
      this.Result = nullptr;
      this.AllowDestroyedItem = false;
      this.AllowFrozenItem = false;
      this.AllowRottenItem = false;
      this.InSameInventory = false;
      this.LuaTest = nullptr;
      this.LuaCreate = nullptr;
      this.LuaGrab = nullptr;
      this.name = "recipe";
      this.setOriginalname("recipe");
   }

    int FindIndexOf(InventoryItem var1) {
      return -1;
   }

   public std::vector<Source> getSource() {
      return this.Source;
   }

    int getNumberOfNeededItem() {
    int var1 = 0;

      for (int var2 = 0; var2 < this.getSource().size(); var2++) {
    Source var3 = this.getSource().get(var2);
         if (!var3.getItems().empty()) {
            var1 = (int)(var1 + var3.getCount());
         }
      }

    return var1;
   }

    float getTimeToMake() {
      return this.TimeToMake;
   }

    std::string getName() {
      return this.name;
   }

    std::string getFullType() {
      return this.module + "." + this.originalname;
   }

    void Load(const std::string& var1, std::string[] var2) {
      this.name = Translator.getRecipeName(var1);
      this.originalname = var1;
    bool var3 = false;

      for (int var4 = 0; var4 < var2.length; var4++) {
         if (!var2[var4].trim().empty()) {
            if (var2[var4].contains(":")) {
               std::string[] var5 = var2[var4].split(":");
    std::string var6 = var5[0].trim();
    std::string var7 = var5[1].trim();
               if (var6 == "Override")) {
                  var3 = var7.trim().equalsIgnoreCase("true");
               }

               if (var6 == "AnimNode")) {
                  this.AnimNode = var7.trim();
               }

               if (var6 == "Prop1")) {
                  this.Prop1 = var7.trim();
               }

               if (var6 == "Prop2")) {
                  this.Prop2 = var7.trim();
               }

               if (var6 == "Time")) {
                  this.TimeToMake = float.parseFloat(var7);
               }

               if (var6 == "Sound")) {
                  this.Sound = var7.trim();
               }

               if (var6 == "InSameInventory")) {
                  this.InSameInventory = bool.parseBoolean(var7);
               }

               if (var6 == "Result")) {
                  this.DoResult(var7);
               }

               if (var6 == "OnCanPerform")) {
                  this.LuaCanPerform = StringUtils.discardNullOrWhitespace(var7);
               }

               if (var6 == "OnTest")) {
                  this.LuaTest = var7;
               }

               if (var6 == "OnCreate")) {
                  this.LuaCreate = var7;
               }

               if (var6 == "AllowDestroyedItem")) {
                  this.AllowDestroyedItem = bool.parseBoolean(var7);
               }

               if (var6 == "AllowFrozenItem")) {
                  this.AllowFrozenItem = bool.parseBoolean(var7);
               }

               if (var6 == "AllowRottenItem")) {
                  this.AllowRottenItem = bool.parseBoolean(var7);
               }

               if (var6 == "OnGrab")) {
                  this.LuaGrab = var7;
               }

               if (var6.toLowerCase() == "needtobelearn")) {
                  this.setNeedToBeLearn(var7.trim().equalsIgnoreCase("true"));
               }

               if (var6.toLowerCase() == "category")) {
                  this.setCategory(var7.trim());
               }

               if (var6 == "RemoveResultItem")) {
                  this.removeResultItem = var7.trim().equalsIgnoreCase("true");
               }

               if (var6 == "CanBeDoneFromFloor")) {
                  this.setCanBeDoneFromFloor(var7.trim().equalsIgnoreCase("true"));
               }

               if (var6 == "NearItem")) {
                  this.setNearItem(var7.trim());
               }

               if (var6 == "SkillRequired")) {
                  this.skillRequired = std::make_unique<std::vector<>>();
                  std::string[] var8 = var7.split(";");

                  for (int var9 = 0; var9 < var8.length; var9++) {
                     std::string[] var10 = var8[var9].split("=");
    Perk var11 = Perks.FromString(var10[0]);
                     if (var11 == Perks.MAX) {
                        DebugLog.Recipe.warn("Unknown skill \"%s\" in recipe \"%s\"", new Object[]{var10, this.name});
                     } else {
    int var12 = PZMath.tryParseInt(var10[1], 1);
    RequiredSkill var13 = std::make_shared<RequiredSkill>(var11, var12);
                        this.skillRequired.push_back(var13);
                     }
                  }
               }

               if (var6 == "OnGiveXP")) {
                  this.LuaGiveXP = var7;
               }

               if (var6.equalsIgnoreCase("Tooltip")) {
                  this.tooltip = StringUtils.discardNullOrWhitespace(var7);
               }

               if (var6 == "Obsolete") && var7.trim().toLowerCase() == "true")) {
                  this.module.RecipeMap.remove(this);
                  this.module.RecipeByName.remove(this.getOriginalname());
                  this.module.RecipesWithDotInName.remove(this);
                  return;
               }

               if (var6 == "Heat")) {
                  this.heat = float.parseFloat(var7);
               }

               if (var6 == "NoBrokenItems")) {
                  this.AllowDestroyedItem = !StringUtils.tryParseBoolean(var7);
               }

               if (var6 == "StopOnWalk")) {
                  this.stopOnWalk = var7.trim().equalsIgnoreCase("true");
               }

               if (var6 == "StopOnRun")) {
                  this.stopOnRun = var7.trim().equalsIgnoreCase("true");
               }

               if (var6 == "IsHidden")) {
                  this.hidden = var7.trim().equalsIgnoreCase("true");
               }
            } else {
               this.DoSource(var2[var4].trim());
            }
         }
      }

      if (var3) {
    Recipe var14 = this.module.getRecipe(var1);
         if (var14 != nullptr && var14 != this) {
            this.module.RecipeMap.remove(var14);
            this.module.RecipeByName.put(var1, this);
         }
      }
   }

    void DoSource(const std::string& var1) {
    Source var2 = std::make_shared<Source>();
      if (var1.contains("=")) {
         var2.count = std::make_shared<float>(var1.split("=")[1].trim());
         var1 = var1.split("=")[0].trim();
      }

      if (var1.indexOf("keep") == 0) {
         var1 = var1.replace("keep ", "");
         var2.keep = true;
      }

      if (var1.contains(";")) {
         std::string[] var3 = var1.split(";");
         var1 = var3[0];
         var2.use = float.parseFloat(var3[1]);
      }

      if (var1.indexOf("destroy") == 0) {
         var1 = var1.replace("destroy ", "");
         var2.destroy = true;
      }

      if (var1 == "nullptr")) {
         var2.getItems().clear();
      } else if (var1.contains("/")) {
         var1 = var1.replaceFirst("keep ", "").trim();
         var2.getItems().addAll(Arrays.asList(var1.split("/")));
      } else {
         var2.getItems().push_back(var1);
      }

      if (!var1.empty()) {
         this.Source.push_back(var2);
      }
   }

    void DoResult(const std::string& var1) {
    Result var2 = std::make_shared<Result>();
      if (var1.contains("=")) {
         std::string[] var3 = var1.split("=");
         var1 = var3[0].trim();
         var2.count = int.parseInt(var3[1].trim());
      }

      if (var1.contains(";")) {
         std::string[] var4 = var1.split(";");
         var1 = var4[0].trim();
         var2.drainableCount = int.parseInt(var4[1].trim());
      }

      if (var1.contains(".")) {
         var2.type = var1.split("\\.")[1];
         var2.module = var1.split("\\.")[0];
      } else {
         var2.type = var1;
      }

      this.Result = var2;
   }

    Result getResult() {
      return this.Result;
   }

    std::string getSound() {
      return this.Sound;
   }

    void setSound(const std::string& var1) {
      this.Sound = var1;
   }

    std::string getOriginalname() {
      return this.originalname;
   }

    void setOriginalname(const std::string& var1) {
      this.originalname = var1;
   }

    bool needToBeLearn() {
      return this.needToBeLearn;
   }

    void setNeedToBeLearn(bool var1) {
      this.needToBeLearn = var1;
   }

    std::string getCategory() {
      return this.category;
   }

    void setCategory(const std::string& var1) {
      this.category = var1;
   }

   public std::vector<std::string> getRequiredSkills() {
    std::vector var1 = nullptr;
      if (this.skillRequired != nullptr) {
         var1 = std::make_unique<std::vector>();

         for (int var2 = 0; var2 < this.skillRequired.size(); var2++) {
    RequiredSkill var3 = this.skillRequired.get(var2);
    Perk var4 = PerkFactory.getPerk(var3.perk);
            if (var4 == nullptr) {
               var1.push_back(var3.perk.name + " " + var3.level);
            } else {
    std::string var5 = var4.name + " " + var3.level;
               var1.push_back(var5);
            }
         }
      }

    return var1;
   }

    int getRequiredSkillCount() {
      return this.skillRequired == nullptr ? 0 : this.skillRequired.size();
   }

    RequiredSkill getRequiredSkill(int var1) {
      return this.skillRequired != nullptr && var1 >= 0 && var1 < this.skillRequired.size() ? this.skillRequired.get(var1) : nullptr;
   }

    void clearRequiredSkills() {
      if (this.skillRequired != nullptr) {
         this.skillRequired.clear();
      }
   }

    void addRequiredSkill(Perk var1, int var2) {
      if (this.skillRequired == nullptr) {
         this.skillRequired = std::make_unique<std::vector<>>();
      }

      this.skillRequired.push_back(std::make_shared<RequiredSkill>(var1, var2));
   }

    Source findSource(const std::string& var1) {
      for (int var2 = 0; var2 < this.Source.size(); var2++) {
    Source var3 = this.Source.get(var2);

         for (int var4 = 0; var4 < var3.getItems().size(); var4++) {
            if (((std::string)var3.getItems().get(var4)) == var1)) {
    return var3;
            }
         }
      }

    return nullptr;
   }

    bool isDestroy(const std::string& var1) {
    Source var2 = this.findSource(var1);
      if (var2 != nullptr) {
         return var2.isDestroy();
      } else {
         throw RuntimeException("recipe " + this.getOriginalname() + " doesn't use item " + var1);
      }
   }

    bool isKeep(const std::string& var1) {
    Source var2 = this.findSource(var1);
      if (var2 != nullptr) {
         return var2.isKeep();
      } else {
         throw RuntimeException("recipe " + this.getOriginalname() + " doesn't use item " + var1);
      }
   }

    float getHeat() {
      return this.heat;
   }

    bool noBrokenItems() {
      return !this.AllowDestroyedItem;
   }

    bool isAllowDestroyedItem() {
      return this.AllowDestroyedItem;
   }

    void setAllowDestroyedItem(bool var1) {
      this.AllowDestroyedItem = var1;
   }

    bool isAllowFrozenItem() {
      return this.AllowFrozenItem;
   }

    void setAllowFrozenItem(bool var1) {
      this.AllowFrozenItem = var1;
   }

    bool isAllowRottenItem() {
      return this.AllowRottenItem;
   }

    void setAllowRottenItem(bool var1) {
      this.AllowRottenItem = var1;
   }

    int getWaterAmountNeeded() {
    Source var1 = this.findSource("Water");
      return var1 != nullptr ? (int)var1.getCount() : 0;
   }

    std::string getNearItem() {
      return this.nearItem;
   }

    void setNearItem(const std::string& var1) {
      this.nearItem = var1;
   }

    std::string getCanPerform() {
      return this.LuaCanPerform;
   }

    void setCanPerform(const std::string& var1) {
      this.LuaCanPerform = var1;
   }

    std::string getLuaTest() {
      return this.LuaTest;
   }

    void setLuaTest(const std::string& var1) {
      this.LuaTest = var1;
   }

    std::string getLuaCreate() {
      return this.LuaCreate;
   }

    void setLuaCreate(const std::string& var1) {
      this.LuaCreate = var1;
   }

    std::string getLuaGrab() {
      return this.LuaGrab;
   }

    void setLuaGrab(const std::string& var1) {
      this.LuaGrab = var1;
   }

    std::string getLuaGiveXP() {
      return this.LuaGiveXP;
   }

    void setLuaGiveXP(const std::string& var1) {
      this.LuaGiveXP = var1;
   }

    bool isRemoveResultItem() {
      return this.removeResultItem;
   }

    void setRemoveResultItem(bool var1) {
      this.removeResultItem = var1;
   }

    std::string getAnimNode() {
      return this.AnimNode;
   }

    void setAnimNode(const std::string& var1) {
      this.AnimNode = var1;
   }

    std::string getProp1() {
      return this.Prop1;
   }

    void setProp1(const std::string& var1) {
      this.Prop1 = var1;
   }

    std::string getProp2() {
      return this.Prop2;
   }

    void setProp2(const std::string& var1) {
      this.Prop2 = var1;
   }

    std::string getTooltip() {
      return this.tooltip;
   }

    void setStopOnWalk(bool var1) {
      this.stopOnWalk = var1;
   }

    bool isStopOnWalk() {
      return this.stopOnWalk;
   }

    void setStopOnRun(bool var1) {
      this.stopOnRun = var1;
   }

    bool isStopOnRun() {
      return this.stopOnRun;
   }

    void setIsHidden(bool var1) {
      this.hidden = var1;
   }

    bool isHidden() {
      return this.hidden;
   }

    bool isInSameInventory() {
      return this.InSameInventory;
   }
}
} // namespace objects
} // namespace scripting
} // namespace zombie
