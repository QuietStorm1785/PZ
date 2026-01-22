#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/SandboxOptions.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/skills/PerkFactory/Perks.h"
#include "zombie/core/Translator.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/inventory/types/DrainableComboItem.h"
#include "zombie/iso/objects/IsoThumpable.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/Item.h"
#include "zombie/scripting/objects/Item/Type.h"
#include "zombie/util/StringUtils.h"
#include <algorithm>
#include <iterator>

namespace zombie {
namespace iso {


class MultiStageBuilding {
public:
    std::string name;
   public std::vector<std::string> previousStage;
    std::string recipeName;
    std::string sprite;
    std::string northSprite;
    int timeNeeded;
    int bonusHealth;
    bool bonusHealthSkill;
   public std::unordered_map<std::string, int> xp;
   public std::unordered_map<std::string, int> perks;
   public std::unordered_map<std::string, int> items;
   public std::vector<std::string> itemsToKeep;
    std::string knownRecipe;
    std::string thumpSound;
    std::string wallType;
    bool canBePlastered;
    std::string craftingSound;
    std::string completionSound;
    std::string ID;
    bool canBarricade;

   public MultiStageBuilding$Stage(MultiStageBuilding var1) {
      this.this$0 = var1;
      this.previousStage = std::make_unique<std::vector<>>();
      this.bonusHealthSkill = true;
      this.xp = std::make_unique<std::unordered_map<>>();
      this.perks = std::make_unique<std::unordered_map<>>();
      this.items = std::make_unique<std::unordered_map<>>();
      this.itemsToKeep = std::make_unique<std::vector<>>();
      this.thumpSound = "ZombieThumpGeneric";
      this.completionSound = "BuildWoodenStructureMedium";
      this.canBarricade = false;
   }

    std::string getName() {
      return this.name;
   }

    std::string getDisplayName() {
      return Translator.getMultiStageBuild(this.recipeName);
   }

    std::string getSprite() {
      return this.sprite;
   }

    std::string getNorthSprite() {
      return this.northSprite;
   }

    std::string getThumpSound() {
      return this.thumpSound;
   }

    std::string getRecipeName() {
      return this.recipeName;
   }

    std::string getKnownRecipe() {
      return this.knownRecipe;
   }

    int getTimeNeeded(IsoGameCharacter var1) {
    int var2 = this.timeNeeded;

      for (Entry var4 : this.xp.entrySet()) {
         var2 -= var1.getPerkLevel(Perks.FromString((std::string)var4.getKey())) * 10;
      }

    return var2;
   }

   public std::vector<std::string> getItemsToKeep() {
      return this.itemsToKeep;
   }

   public std::vector<std::string> getPreviousStages() {
      return this.previousStage;
   }

    std::string getCraftingSound() {
      return this.craftingSound;
   }

    KahluaTable getItemsLua() {
    KahluaTable var1 = LuaManager.platform.newTable();

      for (Entry var3 : this.items.entrySet()) {
         var1.rawset(var3.getKey(), ((int)var3.getValue()));
      }

    return var1;
   }

    KahluaTable getPerksLua() {
    KahluaTable var1 = LuaManager.platform.newTable();

      for (Entry var3 : this.perks.entrySet()) {
         var1.rawset(Perks.FromString((std::string)var3.getKey()), ((int)var3.getValue()));
      }

    return var1;
   }

    void doStage(IsoGameCharacter var1, IsoThumpable var2, bool var3) {
    int var4 = var2.getHealth();
    int var5 = var2.getMaxHealth();
    std::string var6 = this.sprite;
      if (var2.north) {
         var6 = this.northSprite;
      }

    IsoThumpable var7 = std::make_shared<IsoThumpable>(IsoWorld.instance.getCell(), var2.square, var6, var2.north, var2.getTable());
      var7.setCanBePlastered(this.canBePlastered);
      if ("doorframe" == this.wallType)) {
         var7.setIsDoorFrame(true);
         var7.setCanPassThrough(true);
         var7.setIsThumpable(var2.isThumpable());
      }

    int var8 = this.bonusHealth;
      switch (SandboxOptions.instance.ConstructionBonusPoints.getValue()) {
         case 1:
            var8 = (int)(var8 * 0.5);
            break;
         case 2:
            var8 = (int)(var8 * 0.7);
         case 3:
         default:
            break;
         case 4:
            var8 = (int)(var8 * 1.3);
            break;
         case 5:
            var8 = (int)(var8 * 1.5);
      }

    Iterator var9 = this.perks.keySet().iterator();
    uint8_t var11 = 20;
      switch (SandboxOptions.instance.ConstructionBonusPoints.getValue()) {
         case 1:
            var11 = 5;
            break;
         case 2:
            var11 = 10;
         case 3:
         default:
            break;
         case 4:
            var11 = 35;
            break;
         case 5:
            var11 = 60;
      }

    int var12 = 0;
      if (this.bonusHealthSkill) {
         while (var9.hasNext()) {
    std::string var10 = (std::string)var9.next();
            var12 += var1.getPerkLevel(Perks.FromString(var10)) * var11;
         }
      }

      var7.setMaxHealth(var5 + var8 + var12);
      var7.setHealth(var4 + var8 + var12);
      var7.setName(this.name);
      var7.setThumpSound(this.getThumpSound());
      var7.setCanBarricade(this.canBarricade);
      var7.setModData(var2.getModData());
      if (this.wallType != nullptr) {
         var7.getModData().rawset("wallType", this.wallType);
      }

      if (var3) {
    ItemContainer var13 = var1.getInventory();

         for (std::string var15 : this.items.keySet()) {
    int var16 = this.items.get(var15);
    Item var17 = ScriptManager.instance.getItem(var15);
            if (var17 != nullptr) {
               if (var17.getType() == Type.Drainable) {
                  InventoryItem var23 = var13.getFirstRecurse(
                     var2x -> var2x.getFullType() == var17.getFullName()) && ((DrainableComboItem)var2x).getDrainableUsesInt() >= var16
                  );
                  if (var23 != nullptr) {
                     for (int var24 = 0; var24 < var16; var24++) {
                        var23.Use();
                     }
                  }
               } else {
                  for (int var18 = 0; var18 < var16; var18++) {
    InventoryItem var19 = var13.getFirstTypeRecurse(var15);
                     if (var19 != nullptr) {
                        var19.Use();
                     }
                  }
               }
            }
         }
      }

      for (std::string var21 : this.xp.keySet()) {
         var1.getXp().AddXP(Perks.FromString(var21), this.xp.get(var21).intValue());
      }

    int var22 = var2.getSquare().transmitRemoveItemFromSquare(var2);
      var7.getSquare().AddSpecialObject(var7, var22);
      var7.getSquare().RecalcAllWithNeighbours(true);
      var7.transmitCompleteItemToServer();
      if (var1 != nullptr && !StringUtils.isNullOrWhitespace(this.completionSound)) {
         var1.playSound(this.completionSound);
      }
   }

    bool canBeDone(IsoGameCharacter var1, IsoObject var2, bool var3) {
    ItemContainer var4 = var1.getInventory();
    bool var5 = false;

      for (int var6 = 0; var6 < this.previousStage.size(); var6++) {
         if (this.previousStage.get(var6).equalsIgnoreCase(var2.getName())) {
            var5 = true;
            break;
         }
      }

    return var5;
   }

    void Load(const std::string& var1, std::string[] var2) {
      this.recipeName = var1;

      for (int var3 = 0; var3 < var2.length; var3++) {
         if (!var2[var3].trim().empty() && var2[var3].contains(":")) {
            std::string[] var4 = var2[var3].split(":");
    std::string var5 = var4[0].trim();
    std::string var6 = var4[1].trim();
            if (var5.equalsIgnoreCase("Name")) {
               this.name = var6.trim();
            }

            if (var5.equalsIgnoreCase("TimeNeeded")) {
               this.timeNeeded = int.parseInt(var6.trim());
            }

            if (var5.equalsIgnoreCase("BonusHealth")) {
               this.bonusHealth = int.parseInt(var6.trim());
            }

            if (var5.equalsIgnoreCase("Sprite")) {
               this.sprite = var6.trim();
            }

            if (var5.equalsIgnoreCase("NorthSprite")) {
               this.northSprite = var6.trim();
            }

            if (var5.equalsIgnoreCase("KnownRecipe")) {
               this.knownRecipe = var6.trim();
            }

            if (var5.equalsIgnoreCase("ThumpSound")) {
               this.thumpSound = var6.trim();
            }

            if (var5.equalsIgnoreCase("WallType")) {
               this.wallType = var6.trim();
            }

            if (var5.equalsIgnoreCase("CraftingSound")) {
               this.craftingSound = var6.trim();
            }

            if (var5.equalsIgnoreCase("CompletionSound")) {
               this.completionSound = var6.trim();
            }

            if (var5.equalsIgnoreCase("ID")) {
               this.ID = var6.trim();
            }

            if (var5.equalsIgnoreCase("CanBePlastered")) {
               this.canBePlastered = bool.parseBoolean(var6.trim());
            }

            if (var5.equalsIgnoreCase("BonusSkill")) {
               this.bonusHealthSkill = bool.parseBoolean(var6.trim());
            }

            if (var5.equalsIgnoreCase("CanBarricade")) {
               this.canBarricade = bool.parseBoolean(var6.trim());
            }

            if (var5.equalsIgnoreCase("XP")) {
               std::string[] var7 = var6.split(";");

               for (int var8 = 0; var8 < var7.length; var8++) {
                  std::string[] var9 = var7[var8].split("=");
                  this.xp.put(var9[0], int.parseInt(var9[1]));
               }
            }

            if (var5.equalsIgnoreCase("PreviousStage")) {
               std::string[] var10 = var6.split(";");

               for (int var14 = 0; var14 < var10.length; var14++) {
                  this.previousStage.push_back(var10[var14]);
               }
            }

            if (var5.equalsIgnoreCase("SkillRequired")) {
               std::string[] var11 = var6.split(";");

               for (int var15 = 0; var15 < var11.length; var15++) {
                  std::string[] var18 = var11[var15].split("=");
                  this.perks.put(var18[0], int.parseInt(var18[1]));
               }
            }

            if (var5.equalsIgnoreCase("ItemsRequired")) {
               std::string[] var12 = var6.split(";");

               for (int var16 = 0; var16 < var12.length; var16++) {
                  std::string[] var19 = var12[var16].split("=");
                  this.items.put(var19[0], int.parseInt(var19[1]));
               }
            }

            if (var5.equalsIgnoreCase("ItemsToKeep")) {
               std::string[] var13 = var6.split(";");

               for (int var17 = 0; var17 < var13.length; var17++) {
                  this.itemsToKeep.push_back(var13[var17]);
               }
            }
         }
      }
   }
}
} // namespace iso
} // namespace zombie
