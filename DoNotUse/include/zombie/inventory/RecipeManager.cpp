#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/skills/PerkFactory/Perks.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/inventory/RecipeManager/1.h"
#include "zombie/inventory/RecipeManager/RMRecipe.h"
#include "zombie/inventory/RecipeManager/SourceItems.h"
#include "zombie/inventory/types/Clothing.h"
#include "zombie/inventory/types/Drainable.h"
#include "zombie/inventory/types/DrainableComboItem.h"
#include "zombie/inventory/types/Food.h"
#include "zombie/inventory/types/Moveable.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/network/GameClient.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/EvolvedRecipe.h"
#include "zombie/scripting/objects/Item.h"
#include "zombie/scripting/objects/MovableRecipe.h"
#include "zombie/scripting/objects/Recipe.h"
#include "zombie/scripting/objects/Recipe/RequiredSkill.h"
#include "zombie/scripting/objects/Recipe/Result.h"
#include "zombie/scripting/objects/Recipe/Source.h"
#include "zombie/scripting/objects/ScriptModule.h"
#include "zombie/util/StringUtils.h"
#include <algorithm>

namespace zombie {
namespace inventory {


class RecipeManager {
public:
   private static const std::vector<Recipe> RecipeList = std::make_unique<std::vector<>>();

    static void Loaded() {
    std::vector var0 = ScriptManager.instance.getAllRecipes();
    std::unordered_set var1 = new std::unordered_set();

      for (int var2 = 0; var2 < var0.size(); var2++) {
    Recipe var3 = (Recipe)var0.get(var2);

         for (int var4 = 0; var4 < var3.getSource().size(); var4++) {
    Source var5 = (Source)var3.getSource().get(var4);

            for (int var6 = 0; var6 < var5.getItems().size(); var6++) {
    std::string var7 = (std::string)var5.getItems().get(var6);
               if (!"Water" == var7) && !var7.contains(".") && !var7.startsWith("[")) {
    Item var8 = resolveItemModuleDotType(var3, var7, var1, "recipe source");
                  if (var8 == nullptr) {
                     var5.getItems().set(var6, "???." + var7);
                  } else {
                     var5.getItems().set(var6, var8.getFullName());
                  }
               }
            }
         }

         if (var3.getResult() != nullptr && var3.getResult().getModule() == nullptr) {
    Item var9 = resolveItemModuleDotType(var3, var3.getResult().getType(), var1, "recipe result");
            if (var9 == nullptr) {
               var3.getResult().module = "???";
            } else {
               var3.getResult().module = var9.getModule().getName();
            }
         }
      }
   }

    static Item resolveItemModuleDotType(Recipe var0, const std::string& var1, Set<std::string> var2, const std::string& var3) {
    ScriptModule var4 = var0.getModule();
    Item var5 = var4.getItem(var1);
      if (var5 != nullptr && !var5.getObsolete()) {
    return var5;
      } else {
         for (int var6 = 0; var6 < ScriptManager.instance.ModuleList.size(); var6++) {
    ScriptModule var7 = (ScriptModule)ScriptManager.instance.ModuleList.get(var6);
            var5 = var7.getItem(var1);
            if (var5 != nullptr && !var5.getObsolete()) {
    std::string var8 = var0.getModule().getName();
               if (!var2.contains(var8)) {
                  var2.push_back(var8);
                  DebugLog.Recipe.warn("WARNING: module \"%s\" may have forgot to import module Base", new Object[]{var8});
               }

    return var5;
            }
         }

         DebugLog.Recipe.warn("ERROR: can't find %s \"%s\" in recipe \"%s\"", new Object[]{var3, var1, var0.getOriginalname()});
    return nullptr;
      }
   }

    static void LoadedAfterLua() {
    std::vector var0 = new std::vector();
    std::vector var1 = ScriptManager.instance.getAllRecipes();

      for (int var2 = 0; var2 < var1.size(); var2++) {
    Recipe var3 = (Recipe)var1.get(var2);
         LoadedAfterLua(var3, var0);
      }

      var0.clear();
   }

    static void LoadedAfterLua(Recipe var0, std::vector<Item> var1) {
      LoadedAfterLua(var0, var0.LuaCreate, "LuaCreate");
      LoadedAfterLua(var0, var0.LuaGiveXP, "LuaGiveXP");
      LoadedAfterLua(var0, var0.LuaTest, "LuaTest");

      for (int var2 = 0; var2 < var0.getSource().size(); var2++) {
    Source var3 = (Source)var0.getSource().get(var2);
         LoadedAfterLua(var3, var1);
      }
   }

    static void LoadedAfterLua(Recipe var0, const std::string& var1, const std::string& var2) {
      if (!StringUtils.isNullOrWhitespace(var1)) {
    void* var3 = LuaManager.getFunctionObject(var1);
         if (var3 == nullptr) {
            DebugLog.General.error("no such function %s = \"%s\" in recipe \"%s\"", new Object[]{var2, var1, var0.name});
         }
      }
   }

    static void LoadedAfterLua(Source var0, std::vector<Item> var1) {
      for (int var2 = var0.getItems().size() - 1; var2 >= 0; var2--) {
    std::string var3 = (std::string)var0.getItems().get(var2);
         if (var3.startsWith("[")) {
            var0.getItems().remove(var2);
    std::string var4 = var3.substr(1, var3.indexOf("]"));
    void* var5 = LuaManager.getFunctionObject(var4);
            if (var5 != nullptr) {
               var1.clear();
               LuaManager.caller.protectedCallVoid(LuaManager.thread, var5, var1);

               for (int var6 = 0; var6 < var1.size(); var6++) {
    Item var7 = (Item)var1.get(var6);
                  var0.getItems().push_back(var2 + var6, var7.getFullName());
               }
            }
         }
      }
   }

    static bool DoesWipeUseDelta(const std::string& var0, const std::string& var1) {
    return true;
   }

    static int getKnownRecipesNumber(IsoGameCharacter var0) {
    int var1 = 0;
    std::vector var2 = ScriptManager.instance.getAllRecipes();

      for (int var3 = 0; var3 < var2.size(); var3++) {
    Recipe var4 = (Recipe)var2.get(var3);
         if (var0.isRecipeKnown(var4)) {
            var1++;
         }
      }

    return var1;
   }

    static bool DoesUseItemUp(const std::string& var0, Recipe var1) {
      assert "Water" == var0) || var0.contains(".");

      for (int var2 = 0; var2 < var1.Source.size(); var2++) {
         if (((Source)var1.Source.get(var2)).keep) {
    std::vector var3 = ((Source)var1.Source.get(var2)).getItems();

            for (int var4 = 0; var4 < var3.size(); var4++) {
               if (var0 == var3.get(var4))) {
    return false;
               }
            }
         }
      }

    return true;
   }

    static bool IsItemDestroyed(const std::string& var0, Recipe var1) {
      assert "Water" == var0) || var0.contains(".");

      for (int var2 = 0; var2 < var1.Source.size(); var2++) {
    Source var3 = (Source)var1.getSource().get(var2);
         if (var3.destroy) {
            for (int var4 = 0; var4 < var3.getItems().size(); var4++) {
               if (var0 == var3.getItems().get(var4))) {
    return true;
               }
            }
         }
      }

    return false;
   }

    static float UseAmount(const std::string& var0, Recipe var1, IsoGameCharacter var2) {
    Source var3 = var1.findSource(var0);
      return var3.getCount();
   }

   public static std::vector<Recipe> getUniqueRecipeItems(InventoryItem var0, IsoGameCharacter var1, std::vector<ItemContainer> var2) {
      RecipeList.clear();
    std::vector var3 = ScriptManager.instance.getAllRecipes();

      for (int var4 = 0; var4 < var3.size(); var4++) {
    Recipe var5 = (Recipe)var3.get(var4);
         if (IsRecipeValid(var5, var1, var0, var2)
            && (!(dynamic_cast<Clothing*>(var0) != nullptr) || var0.getCondition() > 0 || !var5.getOriginalname().equalsIgnoreCase("rip clothing"))) {
            RecipeList.push_back(var5);
         }
      }

      if (dynamic_cast<Moveable*>(var0) != nullptr && RecipeList.size() == 0 && ((Moveable)var0).getWorldSprite() != nullptr) {
         if (var0.type != nullptr && var0.type.equalsIgnoreCase(((Moveable)var0).getWorldSprite())) {
    MovableRecipe var6 = std::make_shared<MovableRecipe>();
            LuaEventManager.triggerEvent("OnDynamicMovableRecipe", ((Moveable)var0).getWorldSprite(), var6, var0, var1);
            if (var6.isValid() && IsRecipeValid(var6, var1, var0, var2)) {
               RecipeList.push_back(var6);
            }
         } else {
            DebugLog.log("RecipeManager -> Cannot create recipe for this movable item: " + var0.getFullType());
         }
      }

    return RecipeList;
   }

    static bool IsRecipeValid(Recipe var0, IsoGameCharacter var1, InventoryItem var2, std::vector<ItemContainer> var3) {
      if (var0.Result == nullptr) {
    return false;
      } else if (!var1.isRecipeKnown(var0)) {
    return false;
      } else if (var2 != nullptr && !RecipeContainsItem(var0, var2)) {
    return false;
      } else if (!HasAllRequiredItems(var0, var1, var2, var3)) {
    return false;
      } else if (!isAllItemsUsableRotten(var0, var1, var2, var3)) {
    return false;
      } else if (!HasRequiredSkill(var0, var1)) {
    return false;
      } else if (!isNearItem(var0, var1)) {
    return false;
      } else {
         return !hasHeat(var0, var2, var3, var1) ? false : CanPerform(var0, var1, var2);
      }
   }

    static bool isNearItem(Recipe var0, IsoGameCharacter var1) {
      if (var0.getNearItem() != nullptr && !var0.getNearItem() == "")) {
         for (int var2 = var1.getSquare().getX() - 2; var2 < var1.getSquare().getX() + 2; var2++) {
            for (int var3 = var1.getSquare().getY() - 2; var3 < var1.getSquare().getY() + 2; var3++) {
    IsoGridSquare var4 = var1.getCell().getGridSquare(var2, var3, var1.getSquare().getZ());
               if (var4 != nullptr) {
                  for (int var5 = 0; var5 < var4.getObjects().size(); var5++) {
                     if (var0.getNearItem() == ((IsoObject)var4.getObjects().get(var5)).getName())) {
    return true;
                     }
                  }
               }
            }
         }

    return false;
      } else {
    return true;
      }
   }

    static bool CanPerform(Recipe var0, IsoGameCharacter var1, InventoryItem var2) {
      if (StringUtils.isNullOrWhitespace(var0.getCanPerform())) {
    return true;
      } else {
    void* var3 = LuaManager.getFunctionObject(var0.getCanPerform());
         if (var3 == nullptr) {
    return false;
         } else {
    bool var4 = LuaManager.caller.protectedCallBoolean(LuaManager.thread, var3, var0, var1, var2);
    return var4 = = bool.TRUE;
         }
      }
   }

    static bool HasRequiredSkill(Recipe var0, IsoGameCharacter var1) {
      if (var0.getRequiredSkillCount() == 0) {
    return true;
      } else {
         for (int var2 = 0; var2 < var0.getRequiredSkillCount(); var2++) {
    RequiredSkill var3 = var0.getRequiredSkill(var2);
            if (var1.getPerkLevel(var3.getPerk()) < var3.getLevel()) {
    return false;
            }
         }

    return true;
      }
   }

    static bool RecipeContainsItem(Recipe var0, InventoryItem var1) {
      for (int var2 = 0; var2 < var0.Source.size(); var2++) {
    Source var3 = (Source)var0.getSource().get(var2);

         for (int var4 = 0; var4 < var3.getItems().size(); var4++) {
    std::string var5 = (std::string)var3.getItems().get(var4);
            if ("Water" == var5) && var1.isWaterSource()) {
    return true;
            }

            if (var5 == var1.getFullType())) {
    return true;
            }
         }
      }

    return false;
   }

    static bool HasAllRequiredItems(Recipe var0, IsoGameCharacter var1, InventoryItem var2, std::vector<ItemContainer> var3) {
    std::vector var4 = getAvailableItemsNeeded(var0, var1, var3, var2, nullptr);
      return !var4.empty();
   }

    static bool isAllItemsUsableRotten(Recipe var0, IsoGameCharacter var1, InventoryItem var2, std::vector<ItemContainer> var3) {
      if (var1.getPerkLevel(Perks.Cooking) >= 7) {
    return true;
      } else if (var0.isAllowRottenItem()) {
    return true;
      } else {
         for (InventoryItem var6 : getAvailableItemsNeeded(var0, var1, var3, var2, nullptr)) {
            if (dynamic_cast<Food*>(var6) != nullptr && ((Food)var6).isRotten()) {
    return false;
            }
         }

    return true;
      }
   }

    static bool hasHeat(Recipe var0, InventoryItem var1, std::vector<ItemContainer> var2, IsoGameCharacter var3) {
      if (var0.getHeat() == 0.0F) {
    return true;
      } else {
    InventoryItem var4 = nullptr;

         for (InventoryItem var6 : getAvailableItemsNeeded(var0, var3, var2, var1, nullptr)) {
            if (dynamic_cast<DrainableComboItem*>(var6) != nullptr) {
               var4 = var6;
               break;
            }
         }

         if (var4 != nullptr) {
    for (auto& var10 : var2)               for (InventoryItem var8 : var10.getItems()) {
                  if (var8.getName() == var4.getName())) {
                     if (var0.getHeat() < 0.0F) {
                        if (var8.getInvHeat() <= var0.getHeat()) {
    return true;
                        }
                     } else if (var0.getHeat() > 0.0F && var8.getInvHeat() + 1.0F >= var0.getHeat()) {
    return true;
                     }
                  }
               }
            }
         }

    return false;
      }
   }

   public static std::vector<InventoryItem> getAvailableItemsAll(
      Recipe var0, IsoGameCharacter var1, std::vector<ItemContainer> var2, InventoryItem var3, std::vector<InventoryItem> var4
   ) {
    return getAvailableItems();
   }

   public static std::vector<InventoryItem> getAvailableItemsNeeded(
      Recipe var0, IsoGameCharacter var1, std::vector<ItemContainer> var2, InventoryItem var3, std::vector<InventoryItem> var4
   ) {
    return getAvailableItems();
   }

   private static SourceItems getAvailableItems(
      Recipe var0, IsoGameCharacter var1, std::vector<ItemContainer> var2, InventoryItem var3, std::vector<InventoryItem> var4, boolean var5
   ) {
      if (var3 != nullptr && (var3.getContainer() == nullptr || !var3.getContainer().contains(var3))) {
         DebugLog.Recipe.warn("recipe: item appears to have been used already, ignoring " + var3.getFullType());
         var3 = nullptr;
      }

    SourceItems var6 = std::make_shared<SourceItems>(var0, var1, var3, var4);
      if (var2 == nullptr) {
         var2 = std::make_unique<std::vector>();
         var2.push_back(var1.getInventory());
      }

      if (var3 != nullptr && !RecipeContainsItem(var0, var3)) {
         throw RuntimeException("item " + var3.getFullType() + " isn't used in recipe " + var0.getOriginalname());
      } else {
    RMRecipe var7 = RMRecipe.alloc(var0);
         var7.getItemsFromContainers(var1, var2, var3);
         if (var5 || var7.hasItems()) {
            var7.getAvailableItems(var6, var5);
         }

         RMRecipe.release(var7);
    return var6;
      }
   }

   public static std::vector<InventoryItem> getSourceItemsAll(
      Recipe var0, int var1, IsoGameCharacter var2, std::vector<ItemContainer> var3, InventoryItem var4, std::vector<InventoryItem> var5
   ) {
      if (var1 >= 0 && var1 < var0.getSource().size()) {
    SourceItems var6 = getAvailableItems(var0, var2, var3, var4, var5, true);
         return var6.itemsPerSource[var1];
      } else {
    return nullptr;
      }
   }

   public static std::vector<InventoryItem> getSourceItemsNeeded(
      Recipe var0, int var1, IsoGameCharacter var2, std::vector<ItemContainer> var3, InventoryItem var4, std::vector<InventoryItem> var5
   ) {
      if (var1 >= 0 && var1 < var0.getSource().size()) {
    SourceItems var6 = getAvailableItems(var0, var2, var3, var4, var5, false);
         return var6.itemsPerSource[var1];
      } else {
    return nullptr;
      }
   }

    static int getNumberOfTimesRecipeCanBeDone(Recipe var0, IsoGameCharacter var1, std::vector<ItemContainer> var2, InventoryItem var3) {
    int var4 = 0;
    RMRecipe var5 = RMRecipe.alloc(var0);
      if (var2 == nullptr) {
         var2 = std::make_unique<std::vector>();
         var2.push_back(var1.getInventory());
      }

      var5.getItemsFromContainers(var1, var2, var3);
    std::vector var6 = new std::vector();

      for (std::vector var7 = std::make_unique<std::vector>(); var5.hasItems(); var4++) {
         var7.clear();
         var5.Use(var7);
         if (var6.containsAll(var7)) {
            var4 = -1;
            break;
         }

         var6.addAll(var7);

         for (int var8 = 0; var8 < var7.size(); var8++) {
    InventoryItem var9 = (InventoryItem)var7.get(var8);
            if (dynamic_cast<Food*>(var9) != nullptr && ((Food)var9).isFrozen() && !var5.recipe.isAllowFrozenItem()) {
               var4--;
               break;
            }
         }
      }

      RMRecipe.release(var5);
    return var4;
   }

    static InventoryItem GetMovableRecipeTool(bool var0, Recipe var1, InventoryItem var2, IsoGameCharacter var3, std::vector<ItemContainer> var4) {
      if (!(dynamic_cast<MovableRecipe*>(var1) != nullptr var5)) {
    return nullptr;
      } else {
    Source var6 = var0 ? var5.getPrimaryTools() : var5.getSecondaryTools();
         if (var6 != nullptr && var6.getItems() != nullptr && var6.getItems().size() != 0) {
    SourceItems var7 = getAvailableItems(var1, var3, var4, var2, nullptr, false);
            if (var7.allItems != nullptr && var7.allItems.size() != 0) {
               for (int var8 = 0; var8 < var7.allItems.size(); var8++) {
    InventoryItem var9 = (InventoryItem)var7.allItems.get(var8);

                  for (int var10 = 0; var10 < var6.getItems().size(); var10++) {
                     if (var9.getFullType().equalsIgnoreCase((std::string)var6.getItems().get(var10))) {
    return var9;
                     }
                  }
               }

    return nullptr;
            } else {
    return nullptr;
            }
         } else {
    return nullptr;
         }
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    static InventoryItem PerformMakeItem(Recipe var0, InventoryItem var1, IsoGameCharacter var2, std::vector<ItemContainer> var3) {
    bool var4 = var2.getPrimaryHandItem() == var1;
    bool var5 = var2.getSecondaryHandItem() == var1;
    SourceItems var6 = getAvailableItems(var0, var2, var3, var1, nullptr, false);
    std::vector var7 = var6.allItems;
      if (var7.empty()) {
         throw RuntimeException("getAvailableItems() didn't return the required number of items");
      } else {
         var2.removeFromHands(var1);
    Result var8 = var0.getResult();
    InventoryItem var9 = InventoryItemFactory.CreateItem(var8.getFullType());
    bool var10 = false;
    bool var11 = false;
    int var12 = -1;
    int var13 = 0;
    bool var14 = false;
    bool var15 = false;
    float var16 = 0.0F;
    float var17 = 0.0F;
    int var18 = 0;
    int var19 = 0;

         for (int var20 = 0; var20 < var0.getSource().size(); var20++) {
    Source var21 = (Source)var0.getSource().get(var20);
            if (!var21.isKeep()) {
    std::vector var22 = var6.itemsPerSource[var20];
               switch (1.$SwitchMap$zombie$inventory$RecipeManager$RMRecipeItemList$Type[var6.typePerSource[var20].ordinal()]) {
                  case 1:
    int var23 = (int)var21.getCount();
    int var35 = 0;

                     for (; var35 < var22.size(); var35++) {
    InventoryItem var39 = (InventoryItem)var22.get(var35);
    int var43 = AvailableUses(var39);
                        if (var43 >= var23) {
                           ReduceUses(var39, var23, var2);
                           var23 = 0;
                        } else {
                           ReduceUses(var39, var43, var2);
                           var23 -= var43;
                        }
                     }

                     if (var23 > 0) {
                        throw RuntimeException("required amount of " + var21.getItems() + " wasn't available");
                     }
                     break;
                  case 2:
    int var24 = (int)var21.use;

                     for (int var38 = 0; var38 < var22.size(); var38++) {
    InventoryItem var42 = (InventoryItem)var22.get(var38);
    int var44 = AvailableUses(var42);
                        if (var44 >= var24) {
                           ReduceUses(var42, var24, var2);
                           var24 = 0;
                        } else {
                           ReduceUses(var42, var44, var2);
                           var24 -= var44;
                        }
                     }
                     break;
                  case 3:
                     for (int var37 = 0; var37 < var22.size(); var37++) {
    InventoryItem var41 = (InventoryItem)var22.get(var37);
                        ItemUser.RemoveItem(var41);
                     }
                     break;
                  case 4:
                     for (int var36 = 0; var36 < var22.size(); var36++) {
    InventoryItem var40 = (InventoryItem)var22.get(var36);
                        ItemUser.UseItem(var40, true, false);
                     }
                     break;
                  case 5:
    int var25 = var0.getWaterAmountNeeded();

                     for (int var26 = 0; var26 < var22.size(); var26++) {
    InventoryItem var27 = (InventoryItem)var22.get(var26);
    int var28 = AvailableUses(var27);
                        if (var28 >= var25) {
                           ReduceUses(var27, var25, var2);
                           var25 = 0;
                        } else {
                           ReduceUses(var27, var28, var2);
                           var25 -= var28;
                        }
                     }

                     if (var25 > 0) {
                        throw RuntimeException("required amount of water wasn't available");
                     }
               }
            }
         }

         for (int var30 = 0; var30 < var7.size(); var30++) {
    InventoryItem var33 = (InventoryItem)var7.get(var30);
            if (dynamic_cast<Food*>(var33) != nullptr) {
               if (((Food)var33).isCooked()) {
                  var10 = true;
               }

               if (((Food)var33).isBurnt()) {
                  var11 = true;
               }

               var12 = ((Food)var33).getPoisonDetectionLevel();
               var13 = ((Food)var33).getPoisonPower();
               var19++;
               if (var33.getAge() > var33.getOffAgeMax()) {
                  var14 = true;
               } else if (!var14 && var33.getOffAgeMax() < 1000000000) {
                  if (var33.getAge() < var33.getOffAge()) {
                     var17 += 0.5F * var33.getAge() / var33.getOffAge();
                  } else {
                     var15 = true;
                     var17 += 0.5F + 0.5F * (var33.getAge() - var33.getOffAge()) / (var33.getOffAgeMax() - var33.getOffAge());
                  }
               }
            }

            if (dynamic_cast<Food*>(var9) != nullptr && var33.isTaintedWater()) {
               var9.setTaintedWater(true);
            }

            if (var9.getScriptItem() == var33.getScriptItem() && var33.isFavorite()) {
               var9.setFavorite(true);
            }

            var16 += (float)var33.getCondition() / var33.getConditionMax();
            var18++;
         }

         var17 /= var19;
         if (dynamic_cast<Food*>(var9) != nullptr && ((Food)var9).IsCookable) {
            ((Food)var9).setCooked(var10);
            ((Food)var9).setBurnt(var11);
            ((Food)var9).setPoisonDetectionLevel(var12);
            ((Food)var9).setPoisonPower(var13);
         }

         if (var9.getOffAgeMax() != 1.0E9) {
            if (var14) {
               var9.setAge(var9.getOffAgeMax());
            } else {
               if (var15 && var17 < 0.5F) {
                  var17 = 0.5F;
               }

               if (var17 < 0.5F) {
                  var9.setAge(2.0F * var17 * var9.getOffAge());
               } else {
                  var9.setAge(var9.getOffAge() + 2.0F * (var17 - 0.5F) * (var9.getOffAgeMax() - var9.getOffAge()));
               }
            }
         }

         var9.setCondition(Math.round(var9.getConditionMax() * (var16 / var18)));

         for (int var31 = 0; var31 < var7.size(); var31++) {
    InventoryItem var34 = (InventoryItem)var7.get(var31);
            var9.setConditionFromModData(var34);
         }

         GivePlayerExperience(var0, var7, var9, var2);
         if (var0.LuaCreate != nullptr) {
    void* var32 = LuaManager.getFunctionObject(var0.LuaCreate);
            if (var32 != nullptr) {
               LuaManager.caller.protectedCall(LuaManager.thread, var32, new Object[]{var7, var9, var2, var1, var4, var5});
            }
         }

         return !var0.isRemoveResultItem() ? var9 : nullptr;
      }
   }

    static bool ReduceUses(InventoryItem var0, float var1, IsoGameCharacter var2) {
      if (dynamic_cast<DrainableComboItem*>(var0) != nullptr var3) {
    float var4 = var3.getUseDelta() * var1;
         var3.setUsedDelta(var3.getUsedDelta() - var4);
         if (AvailableUses(var0) < 1) {
            var3.setUsedDelta(0.0F);
            ItemUser.UseItem(var3);
    return true;
         }

         if (GameClient.bClient && !var0.isInPlayerInventory()) {
            GameClient.instance.sendItemStats(var0);
         }
      }

      if (dynamic_cast<Food*>(var0) != nullptr var6 && var6.getHungerChange() < 0.0F) {
    float var7 = Math.min(-var6.getHungerChange() * 100.0F, var1);
    float var5 = var7 / (-var6.getHungerChange() * 100.0F);
         if (var5 < 0.0F) {
            var5 = 0.0F;
         }

         if (var5 > 1.0F) {
            var5 = 1.0F;
         }

         var6.setHungChange(var6.getHungChange() - var6.getHungChange() * var5);
         var6.setCalories(var6.getCalories() - var6.getCalories() * var5);
         var6.setCarbohydrates(var6.getCarbohydrates() - var6.getCarbohydrates() * var5);
         var6.setLipids(var6.getLipids() - var6.getLipids() * var5);
         var6.setProteins(var6.getProteins() - var6.getProteins() * var5);
         var6.setThirstChange(var6.getThirstChangeUnmodified() - var6.getThirstChangeUnmodified() * var5);
         var6.setFluReduction(var6.getFluReduction() - (int)(var6.getFluReduction() * var5));
         var6.setPainReduction(var6.getPainReduction() - var6.getPainReduction() * var5);
         var6.setEndChange(var6.getEnduranceChangeUnmodified() - var6.getEnduranceChangeUnmodified() * var5);
         var6.setReduceFoodSickness(var6.getReduceFoodSickness() - (int)(var6.getReduceFoodSickness() * var5));
         var6.setStressChange(var6.getStressChangeUnmodified() - var6.getStressChangeUnmodified() * var5);
         var6.setFatigueChange(var6.getFatigueChange() - var6.getFatigueChange() * var5);
         if (var6.getHungerChange() > -0.01) {
            ItemUser.UseItem(var6);
    return true;
         }

         if (GameClient.bClient && !var0.isInPlayerInventory()) {
            GameClient.instance.sendItemStats(var0);
         }
      }

    return false;
   }

    static int AvailableUses(InventoryItem var0) {
      if (dynamic_cast<DrainableComboItem*>(var0) != nullptr var2) {
         return var2.getDrainableUsesInt();
      } else {
         return dynamic_cast<Food*>(var0) != nullptr var1 ? (int)(-var1.getHungerChange() * 100.0F) : 0;
      }
   }

    static void GivePlayerExperience(Recipe var0, std::vector<InventoryItem> var1, InventoryItem var2, IsoGameCharacter var3) {
    std::string var4 = var0.LuaGiveXP;
      if (var4 == nullptr) {
         var4 = "Recipe.OnGiveXP.Default";
      }

    void* var5 = LuaManager.getFunctionObject(var4);
      if (var5 == nullptr) {
         DebugLog.Recipe.warn("ERROR: Lua method \"" + var4 + "\" not found (in RecipeManager.GivePlayerExperience())");
      } else {
         LuaManager.caller.protectedCall(LuaManager.thread, var5, new Object[]{var0, var1, var2, var3});
      }
   }

   public static std::vector<EvolvedRecipe> getAllEvolvedRecipes() {
    std::stack var0 = ScriptManager.instance.getAllEvolvedRecipes();
    std::vector var1 = new std::vector();

      for (int var2 = 0; var2 < var0.size(); var2++) {
         var1.push_back((EvolvedRecipe)var0.get(var2));
      }

    return var1;
   }

   public static std::vector<EvolvedRecipe> getEvolvedRecipe(InventoryItem var0, IsoGameCharacter var1, std::vector<ItemContainer> var2, boolean var3) {
    std::vector var4 = new std::vector();
      if (dynamic_cast<Food*>(var0) != nullptr && ((Food)var0).isRotten() && var1.getPerkLevel(Perks.Cooking) < 7) {
    return var4;
      } else {
    std::stack var5 = ScriptManager.instance.getAllEvolvedRecipes();

         for (int var6 = 0; var6 < var5.size(); var6++) {
    EvolvedRecipe var7 = (EvolvedRecipe)var5.get(var6);
            if ((var0.isCooked() && var7.addIngredientIfCooked || !var0.isCooked())
               && (var0.getType() == var7.baseItem) || var0.getType() == var7.getResultItem()))
               && (!var0.getType() == "WaterPot") || !(((Drainable)var0).getUsedDelta() < 0.75))) {
               if (var3) {
    std::vector var8 = var7.getItemsCanBeUse(var1, var0, var2);
                  if (!var8.empty()) {
                     if (!(dynamic_cast<Food*>(var0) != nullptr) || !((Food)var0).isFrozen()) {
                        var4.push_back(var7);
                     } else if (var7.isAllowFrozenItem()) {
                        var4.push_back(var7);
                     }
                  }
               } else {
                  var4.push_back(var7);
               }
            }
         }

    return var4;
      }
   }

    static void DebugPrintAllRecipes() {
    std::vector var0 = ScriptManager.instance.getAllRecipes();

      for (int var1 = 0; var1 < var0.size(); var1++) {
    Recipe var2 = (Recipe)var0.get(var1);
         if (var2 == nullptr) {
            DebugLog.Recipe.println("Null recipe.");
         } else if (var2.Result == nullptr) {
            DebugLog.Recipe.println("Null result.");
         } else {
            DebugLog.Recipe.println(var2.Result.type);
            DebugLog.Recipe.println("-----");

            for (int var3 = 0; var3 < var2.Source.size(); var3++) {
               if (var2.Source.get(var3) == nullptr) {
                  DebugLog.Recipe.println("Null ingredient.");
               } else if (((Source)var2.Source.get(var3)).getItems().empty()) {
                  DebugLog.Recipe.println(((Source)var2.Source.get(var3)).getItems());
               }
            }
         }
      }
   }

    static Recipe getDismantleRecipeFor(const std::string& var0) {
      RecipeList.clear();
    std::vector var1 = ScriptManager.instance.getAllRecipes();

      for (int var2 = 0; var2 < var1.size(); var2++) {
    Recipe var3 = (Recipe)var1.get(var2);
    std::vector var4 = var3.getSource();
         if (var4.size() > 0) {
            for (int var5 = 0; var5 < var4.size(); var5++) {
    Source var6 = (Source)var4.get(var5);

               for (int var7 = 0; var7 < var6.getItems().size(); var7++) {
                  if (((std::string)var6.getItems().get(var7)).equalsIgnoreCase(var0) && var3.name.toLowerCase().startsWith("dismantle ")) {
    return var3;
                  }
               }
            }
         }
      }

    return nullptr;
   }
}
} // namespace inventory
} // namespace zombie
