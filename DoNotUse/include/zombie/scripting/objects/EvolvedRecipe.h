#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/math/RoundingMode.h"
#include "java/text/DecimalFormat.h"
#include "java/text/NumberFormat.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/skills/PerkFactory/Perks.h"
#include "zombie/core/Translator.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/inventory/types/Food.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/util/StringUtils.h"
#include <algorithm>
#include <iterator>

namespace zombie {
namespace scripting {
namespace objects {


class EvolvedRecipe : public BaseScriptObject {
public:
    static const DecimalFormat DECIMAL_FORMAT = (DecimalFormat)NumberFormat.getInstance(Locale.US);
    std::string name = nullptr;
    std::string DisplayName = nullptr;
    std::string originalname;
    int maxItems = 0;
   public const Map<std::string, ItemRecipe> itemsList = std::make_unique<std::unordered_map<>>();
    std::string resultItem = nullptr;
    std::string baseItem = nullptr;
    bool cookable = false;
    bool addIngredientIfCooked = false;
    bool canAddSpicesEmpty = false;
    std::string addIngredientSound = nullptr;
    bool hidden = false;
    bool allowFrozenItem = false;

    public EvolvedRecipe(const std::string& var1) {
      this.name = var1;
   }

    void Load(const std::string& var1, std::string[] var2) {
      this.DisplayName = Translator.getRecipeName(var1);
      this.originalname = var1;

      for (int var3 = 0; var3 < var2.length; var3++) {
         if (!var2[var3].trim().empty() && var2[var3].contains(":")) {
            std::string[] var4 = var2[var3].split(":");
    std::string var5 = var4[0].trim();
    std::string var6 = var4[1].trim();
            if (var5 == "BaseItem")) {
               this.baseItem = var6;
            } else if (var5 == "Name")) {
               this.DisplayName = Translator.getRecipeName(var6);
               this.originalname = var6;
            } else if (var5 == "ResultItem")) {
               this.resultItem = var6;
               if (!var6.contains(".")) {
                  this.resultItem = var6;
               }
            } else if (var5 == "Cookable")) {
               this.cookable = true;
            } else if (var5 == "MaxItems")) {
               this.maxItems = int.parseInt(var6);
            } else if (var5 == "AddIngredientIfCooked")) {
               this.addIngredientIfCooked = bool.parseBoolean(var6);
            } else if (var5 == "AddIngredientSound")) {
               this.addIngredientSound = StringUtils.discardNullOrWhitespace(var6);
            } else if (var5 == "CanAddSpicesEmpty")) {
               this.canAddSpicesEmpty = bool.parseBoolean(var6);
            } else if (var5 == "IsHidden")) {
               this.hidden = bool.parseBoolean(var6);
            } else if (var5 == "AllowFrozenItem")) {
               this.allowFrozenItem = bool.parseBoolean(var6);
            }
         }
      }
   }

    bool needToBeCooked(InventoryItem var1) {
    ItemRecipe var2 = this.getItemRecipe(var1);
    return var2 = = nullptr ? true : var2.cooked == var1.isCooked() || var2.cooked == var1.isBurnt() || !var2.cooked;
   }

   public std::vector<InventoryItem> getItemsCanBeUse(IsoGameCharacter var1, InventoryItem var2, std::vector<ItemContainer> var3) {
    int var4 = var1.getPerkLevel(Perks.Cooking);
      if (var3 == nullptr) {
         var3 = std::make_unique<std::vector>();
      }

    std::vector var5 = new std::vector();
    Iterator var6 = this.itemsList.keySet().iterator();
      if (!var3.contains(var1.getInventory())) {
         var3.push_back(var1.getInventory());
      }

      while (var6.hasNext()) {
    std::string var7 = (std::string)var6.next();

    for (auto& var9 : var3)            this.checkItemCanBeUse(var9, var7, var2, var4, var5);
         }
      }

      if (var2.haveExtraItems() && var2.getExtraItems().size() >= 3) {
         for (int var11 = 0; var11 < var3.size(); var11++) {
    ItemContainer var12 = (ItemContainer)var3.get(var11);

            for (int var13 = 0; var13 < var12.getItems().size(); var13++) {
    InventoryItem var10 = (InventoryItem)var12.getItems().get(var13);
               if (dynamic_cast<Food*>(var10) != nullptr && ((Food)var10).getPoisonLevelForRecipe() != nullptr && var1.isKnownPoison(var10) && !var5.contains(var10)) {
                  var5.push_back(var10);
               }
            }
         }
      }

    return var5;
   }

    void checkItemCanBeUse(ItemContainer var1, const std::string& var2, InventoryItem var3, int var4, std::vector<InventoryItem> var5) {
    std::vector var6 = var1.getItemsFromType(var2);

      for (int var7 = 0; var7 < var6.size(); var7++) {
    InventoryItem var8 = (InventoryItem)var6.get(var7);
    bool var9 = false;
         if (dynamic_cast<Food*>(var8) != nullptr && this.itemsList.get(var2).use != -1) {
    Food var10 = (Food)var8;
            if (var10.isSpice()) {
               if (this.isResultItem(var3)) {
                  var9 = !this.isSpiceAdded(var3, var10);
               } else if (this.canAddSpicesEmpty) {
                  var9 = true;
               }

               if (var10.isRotten() && var4 < 7) {
                  var9 = false;
               }
            } else if ((!var3.haveExtraItems() || var3.extraItems.size() < this.maxItems) && (!var10.isRotten() || var4 >= 7)) {
               var9 = true;
            }

            if (var10.isFrozen() && !this.allowFrozenItem) {
               var9 = false;
            }
         } else {
            var9 = true;
         }

    ItemRecipe var11 = this.getItemRecipe(var8);
         if (var9) {
            var5.push_back(var8);
         }
      }
   }

    InventoryItem addItem(InventoryItem var1, InventoryItem var2, IsoGameCharacter var3) {
    int var4 = var3.getPerkLevel(Perks.Cooking);
      if (!this.isResultItem(var1)) {
    InventoryItem var5 = dynamic_cast<Food*>(var1) != nullptr ? var1 : nullptr;
    InventoryItem var6 = InventoryItemFactory.CreateItem(this.resultItem);
         if (var6 != nullptr) {
            if (dynamic_cast<HandWeapon*>(var1) != nullptr) {
               var6.getModData().rawset("condition:" + var1.getType(), (double)var1.getCondition() / var1.getConditionMax());
            }

            var3.getInventory().Remove(var1);
            var3.getInventory().AddItem(var6);
    InventoryItem var7 = var1;
            var1 = var6;
            if (dynamic_cast<Food*>(var6) != nullptr) {
               ((Food)var6).setCalories(0.0F);
               ((Food)var6).setCarbohydrates(0.0F);
               ((Food)var6).setProteins(0.0F);
               ((Food)var6).setLipids(0.0F);
               if (dynamic_cast<Food*>(var2) != nullptr && ((Food)var2).getPoisonLevelForRecipe() != nullptr) {
                  this.addPoison(var2, var6, var3);
               }

               ((Food)var6).setIsCookable(this.cookable);
               if (var5 != nullptr) {
                  ((Food)var6).setHungChange(((Food)var5).getHungChange());
                  ((Food)var6).setBaseHunger(((Food)var5).getBaseHunger());
               } else {
                  ((Food)var6).setHungChange(0.0F);
                  ((Food)var6).setBaseHunger(0.0F);
               }

               if (var7.isTaintedWater()) {
                  var6.setTaintedWater(true);
               }

               if (dynamic_cast<Food*>(var7) != nullptr && var7.getOffAgeMax() != 1000000000 && var6.getOffAgeMax() != 1000000000) {
    float var8 = var7.getAge() / var7.getOffAgeMax();
                  var6.setAge(var6.getOffAgeMax() * var8);
               }

               if (dynamic_cast<Food*>(var5) != nullptr) {
                  ((Food)var6).setCalories(((Food)var5).getCalories());
                  ((Food)var6).setProteins(((Food)var5).getProteins());
                  ((Food)var6).setLipids(((Food)var5).getLipids());
                  ((Food)var6).setCarbohydrates(((Food)var5).getCarbohydrates());
                  ((Food)var6).setThirstChange(((Food)var5).getThirstChange());
               }
            }

            var6.setUnhappyChange(0.0F);
            var6.setBoredomChange(0.0F);
         }
      }

      if (this.itemsList.get(var2.getType()) != nullptr && this.itemsList.get(var2.getType()).use > -1) {
         if (!(dynamic_cast<Food*>(var2) != nullptr)) {
            var2.Use();
         } else {
    float var15 = this.itemsList.get(var2.getType()).use.intValue() / 100.0F;
    Food var16 = (Food)var2;
    Food var17 = (Food)var1;
    bool var18 = var17.hasTag("HerbalTea") && var16.hasTag("HerbalTea");
            if (var16.isSpice() && dynamic_cast<Food*>(var1) != nullptr) {
               if (dynamic_cast<Food*>(var1) != nullptr && var18) {
                  var17.setReduceFoodSickness(var17.getReduceFoodSickness() + var16.getReduceFoodSickness());
                  var17.setPainReduction(var17.getPainReduction() + var16.getPainReduction());
                  var17.setFluReduction(var17.getFluReduction() + var16.getFluReduction());
                  if (var16.getEnduranceChange() > 0.0F) {
                     var17.setEnduranceChange(var17.getEnduranceChange() + var16.getEnduranceChange());
                  }

                  if (var17.getReduceFoodSickness() > 12) {
                     var17.setReduceFoodSickness(12);
                  }
               }

               this.useSpice(var16, (Food)var1, var15, var4);
    return var1;
            }

    bool var9 = false;
            if (var16.isRotten()) {
    DecimalFormat var10 = DECIMAL_FORMAT;
               var10.setRoundingMode(RoundingMode.HALF_EVEN);
               if (var4 == 7 || var4 == 8) {
                  var15 = float.parseFloat(
                     var10.format(Math.abs(var16.getBaseHunger() - (var16.getBaseHunger() - 0.05F * var16.getBaseHunger()))).replace(",", ".")
                  );
               } else if (var4 == 9 || var4 == 10) {
                  var15 = float.parseFloat(
                     var10.format(Math.abs(var16.getBaseHunger() - (var16.getBaseHunger() - 0.1F * var16.getBaseHunger()))).replace(",", ".")
                  );
               }

               var9 = true;
            }

            if (Math.abs(var16.getHungerChange()) < var15) {
    DecimalFormat var19 = DECIMAL_FORMAT;
               var19.setRoundingMode(RoundingMode.DOWN);
               var15 = Math.abs(float.parseFloat(var19.format(var16.getHungerChange()).replace(",", ".")));
               var9 = true;
            }

            if (dynamic_cast<Food*>(var1) != nullptr) {
               if (dynamic_cast<Food*>(var2) != nullptr && ((Food)var2).getPoisonLevelForRecipe() != nullptr) {
                  this.addPoison(var2, var1, var3);
               }

               var17.setHungChange(var17.getHungChange() - var15);
               var17.setBaseHunger(var17.getBaseHunger() - var15);
               if (var16.isbDangerousUncooked() && !var16.isCooked()) {
                  var17.setbDangerousUncooked(true);
               }

    int var20 = 0;
               if (var1.extraItems != nullptr) {
                  for (int var11 = 0; var11 < var1.extraItems.size(); var11++) {
                     if (((std::string)var1.extraItems.get(var11)) == var2.getFullType())) {
                        var20++;
                     }
                  }
               }

               if (var1.extraItems != nullptr && var1.extraItems.size() - 2 > var4) {
                  var20 += var1.extraItems.size() - 2 - var4 * 3;
               }

    float var21 = var15 - 3 * var4 / 100.0F * var15;
    float var12 = Math.abs(var21 / var16.getHungChange());
               if (var12 > 1.0F) {
                  var12 = 1.0F;
               }

               var1.setUnhappyChange(((Food)var1).getUnhappyChangeUnmodified() - (5 - var20 * 5));
               if (var1.getUnhappyChange() > 25.0F) {
                  var1.setUnhappyChange(25.0F);
               }

    float var13 = var4 / 15.0F + 1.0F;
               var17.setCalories(var17.getCalories() + var16.getCalories() * var13 * var12);
               var17.setProteins(var17.getProteins() + var16.getProteins() * var13 * var12);
               var17.setCarbohydrates(var17.getCarbohydrates() + var16.getCarbohydrates() * var13 * var12);
               var17.setLipids(var17.getLipids() + var16.getLipids() * var13 * var12);
    float var14 = var16.getThirstChangeUnmodified() * var13 * var12;
               if (!var16.hasTag("DriedFood")) {
                  var17.setThirstChange(var17.getThirstChangeUnmodified() + var14);
               }

               if (var16.isCooked()) {
                  var21 = (float)(var21 / 1.3);
               }

               var16.setHungChange(var16.getHungChange() + var21);
               var16.setBaseHunger(var16.getBaseHunger() + var21);
               var16.setThirstChange(var16.getThirstChange() - var14);
               var16.setCalories(var16.getCalories() - var16.getCalories() * var12);
               var16.setProteins(var16.getProteins() - var16.getProteins() * var12);
               var16.setCarbohydrates(var16.getCarbohydrates() - var16.getCarbohydrates() * var12);
               var16.setLipids(var16.getLipids() - var16.getLipids() * var12);
               if (var17.hasTag("AlcoholicBeverage") && var16.isAlcoholic()) {
                  var17.setAlcoholic(true);
               }

               if (var18) {
                  var17.setReduceFoodSickness(var17.getReduceFoodSickness() + var16.getReduceFoodSickness());
                  var17.setPainReduction(var17.getPainReduction() + var16.getPainReduction());
                  var17.setFluReduction(var17.getFluReduction() + var16.getFluReduction());
                  if (var17.getReduceFoodSickness() > 12) {
                     var17.setReduceFoodSickness(12);
                  }
               }

               if (var16.getHungerChange() >= -0.02 || var9) {
                  var2.Use();
               }

               if (var16.getFatigueChange() < 0.0F) {
                  var1.setFatigueChange(var16.getFatigueChange() * var12);
                  var16.setFatigueChange(var16.getFatigueChange() - var16.getFatigueChange() * var12);
               }

               if (var16.getPoisonPower() > 0) {
                  var16.setPoisonPower((int)(var16.getPoisonPower() - var16.getPoisonPower() * var12 + 0.999));
                  ((Food)var1).setPoisonPower((int)(var16.getPoisonPower() * var12 + 0.999));
               }
            }
         }

         var1.addExtraItem(var2.getFullType());
      } else if (dynamic_cast<Food*>(var2) != nullptr && ((Food)var2).getPoisonLevelForRecipe() != nullptr) {
         this.addPoison(var2, var1, var3);
      }

      this.checkUniqueRecipe(var1);
      var3.getXp().AddXP(Perks.Cooking, 3.0F);
    return var1;
   }

    void checkUniqueRecipe(InventoryItem var1) {
      if (dynamic_cast<Food*>(var1) != nullptr var2) {
    std::stack var3 = ScriptManager.instance.getAllUniqueRecipes();

         for (int var4 = 0; var4 < var3.size(); var4++) {
    std::vector var5 = new std::vector();
    UniqueRecipe var6 = (UniqueRecipe)var3.get(var4);
            if (var6.getBaseRecipe() == var1.getType())) {
    bool var7 = true;

               for (int var8 = 0; var8 < var6.getItems().size(); var8++) {
    bool var9 = false;

                  for (int var10 = 0; var10 < var2.getExtraItems().size(); var10++) {
                     if (!var5.contains(var10) && ((std::string)var2.getExtraItems().get(var10)) == var6.getItems().get(var8))) {
                        var9 = true;
                        var5.push_back(var10);
                        break;
                     }
                  }

                  if (!var9) {
                     var7 = false;
                     break;
                  }
               }

               if (var2.getExtraItems().size() == var6.getItems().size() && var7) {
                  var2.setName(var6.getName());
                  if (var2.hasTag("Beer")) {
                     var2.setName("Beer");
                  }

                  var2.setBaseHunger(var2.getBaseHunger() - var6.getHungerBonus() / 100.0F);
                  var2.setHungChange(var2.getBaseHunger());
                  var2.setBoredomChange(var2.getBoredomChangeUnmodified() - var6.getBoredomBonus());
                  var2.setUnhappyChange(var2.getUnhappyChangeUnmodified() - var6.getHapinessBonus());
                  var2.setCustomName(true);
               }
            }
         }
      }
   }

    void addPoison(InventoryItem var1, InventoryItem var2, IsoGameCharacter var3) {
    Food var4 = (Food)var1;
      if (dynamic_cast<Food*>(var2) != nullptr var5) {
    int var6 = var4.getPoisonLevelForRecipe() - var3.getPerkLevel(Perks.Cooking);
         if (var6 < 1) {
            var6 = 1;
         }

    float var7 = 0.0F;
         if (var4.getThirstChange() <= -0.01F) {
    float var8 = var4.getUseForPoison() / 100.0F;
            if (Math.abs(var4.getThirstChange()) < var8) {
               var8 = Math.abs(var4.getThirstChange());
            }

            var7 = Math.abs(var8 / var4.getThirstChange());
            var7 = std::make_shared<float>(Math.round(var7.doubleValue() * 100.0) / 100.0);
            var4.setThirstChange(var4.getThirstChange() + var8);
            if (var4.getThirstChange() > -0.01) {
               var4.Use();
            }
         } else if (var4.getBaseHunger() <= -0.01F) {
    float var11 = var4.getUseForPoison() / 100.0F;
            if (Math.abs(var4.getBaseHunger()) < var11) {
               var11 = Math.abs(var4.getThirstChange());
            }

            var7 = Math.abs(var11 / var4.getBaseHunger());
            var7 = std::make_shared<float>(Math.round(var7.doubleValue() * 100.0) / 100.0);
         }

         if (var5.getPoisonDetectionLevel() == -1) {
            var5.setPoisonDetectionLevel(0);
         }

         var5.setPoisonDetectionLevel(var5.getPoisonDetectionLevel() + var6);
         if (var5.getPoisonDetectionLevel() > 10) {
            var5.setPoisonDetectionLevel(10);
         }

    int var12 = std::make_shared<float>(var7 * (var4.getPoisonPower() / 100.0F) * 100.0F).intValue();
         var5.setPoisonPower(var5.getPoisonPower() + var12);
         var4.setPoisonPower(var4.getPoisonPower() - var12);
      }
   }

    void useSpice(Food var1, Food var2, float var3, int var4) {
      if (!this.isSpiceAdded(var2, var1)) {
         if (var2.spices == nullptr) {
            var2.spices = std::make_unique<std::vector>();
         }

         var2.spices.push_back(var1.getFullType());
    float var5 = var3;
         if (var1.isRotten()) {
    DecimalFormat var6 = DECIMAL_FORMAT;
            var6.setRoundingMode(RoundingMode.HALF_EVEN);
            if (var4 == 7 || var4 == 8) {
               var3 = float.parseFloat(var6.format(Math.abs(var1.getBaseHunger() - (var1.getBaseHunger() - 0.05F * var1.getBaseHunger()))).replace(",", "."));
            } else if (var4 == 9 || var4 == 10) {
               var3 = float.parseFloat(var6.format(Math.abs(var1.getBaseHunger() - (var1.getBaseHunger() - 0.1F * var1.getBaseHunger()))).replace(",", "."));
            }
         }

    float var8 = Math.abs(var3 / var1.getHungChange());
         if (var8 > 1.0F) {
            var8 = 1.0F;
         }

    float var7 = var4 / 15.0F + 1.0F;
         var2.setUnhappyChange(var2.getUnhappyChangeUnmodified() - var3 * 200.0F);
         var2.setBoredomChange(var2.getBoredomChangeUnmodified() - var3 * 200.0F);
         var2.setCalories(var2.getCalories() + var1.getCalories() * var7 * var8);
         var2.setProteins(var2.getProteins() + var1.getProteins() * var7 * var8);
         var2.setCarbohydrates(var2.getCarbohydrates() + var1.getCarbohydrates() * var7 * var8);
         var2.setLipids(var2.getLipids() + var1.getLipids() * var7 * var8);
         var8 = Math.abs(var5 / var1.getHungChange());
         if (var8 > 1.0F) {
            var8 = 1.0F;
         }

         var1.setCalories(var1.getCalories() - var1.getCalories() * var8);
         var1.setProteins(var1.getProteins() - var1.getProteins() * var8);
         var1.setCarbohydrates(var1.getCarbohydrates() - var1.getCarbohydrates() * var8);
         var1.setLipids(var1.getLipids() - var1.getLipids() * var8);
         var1.setHungChange(var1.getHungChange() + var5);
         if (var1.getHungerChange() > -0.01) {
            var1.Use();
         }
      }
   }

    ItemRecipe getItemRecipe(InventoryItem var1) {
      return this.itemsList.get(var1.getType());
   }

    std::string getName() {
      return this.DisplayName;
   }

    std::string getOriginalname() {
      return this.originalname;
   }

    std::string getUntranslatedName() {
      return this.name;
   }

    std::string getBaseItem() {
      return this.baseItem;
   }

   public Map<std::string, ItemRecipe> getItemsList() {
      return this.itemsList;
   }

   public std::vector<ItemRecipe> getPossibleItems() {
    std::vector var1 = new std::vector();

      for (ItemRecipe var3 : this.itemsList.values()) {
         var1.push_back(var3);
      }

    return var1;
   }

    std::string getResultItem() {
      return !this.resultItem.contains(".") ? this.resultItem : this.resultItem.split("\\.")[1];
   }

    std::string getFullResultItem() {
      return this.resultItem;
   }

    bool isCookable() {
      return this.cookable;
   }

    int getMaxItems() {
      return this.maxItems;
   }

    bool isResultItem(InventoryItem var1) {
    return var1 = = nullptr ? false : this.getResultItem() == var1.getType());
   }

    bool isSpiceAdded(InventoryItem var1, InventoryItem var2) {
      if (!this.isResultItem(var1)) {
    return false;
      } else if (!(dynamic_cast<Food*>(var1) != nullptr) || !(dynamic_cast<Food*>(var2) != nullptr)) {
    return false;
      } else if (!((Food)var2).isSpice()) {
    return false;
      } else {
    std::vector var3 = ((Food)var1).getSpices();
    return var3 = = nullptr ? false : var3.contains(var2.getFullType());
      }
   }

    std::string getAddIngredientSound() {
      return this.addIngredientSound;
   }

    void setIsHidden(bool var1) {
      this.hidden = var1;
   }

    bool isHidden() {
      return this.hidden;
   }

    bool isAllowFrozenItem() {
      return this.allowFrozenItem;
   }

    void setAllowFrozenItem(bool var1) {
      this.allowFrozenItem = var1;
   }

   static {
      DECIMAL_FORMAT.applyPattern("#.##");
   }
}
} // namespace objects
} // namespace scripting
} // namespace zombie
