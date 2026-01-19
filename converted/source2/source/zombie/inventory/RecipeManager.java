package zombie.inventory;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.Set;
import java.util.Stack;
import zombie.Lua.LuaEventManager;
import zombie.Lua.LuaManager;
import zombie.characters.IsoGameCharacter;
import zombie.characters.skills.PerkFactory.Perks;
import zombie.debug.DebugLog;
import zombie.inventory.RecipeManager.1;
import zombie.inventory.RecipeManager.RMRecipe;
import zombie.inventory.RecipeManager.SourceItems;
import zombie.inventory.types.Clothing;
import zombie.inventory.types.Drainable;
import zombie.inventory.types.DrainableComboItem;
import zombie.inventory.types.Food;
import zombie.inventory.types.Moveable;
import zombie.iso.IsoGridSquare;
import zombie.iso.IsoObject;
import zombie.network.GameClient;
import zombie.scripting.ScriptManager;
import zombie.scripting.objects.EvolvedRecipe;
import zombie.scripting.objects.Item;
import zombie.scripting.objects.MovableRecipe;
import zombie.scripting.objects.Recipe;
import zombie.scripting.objects.ScriptModule;
import zombie.scripting.objects.Recipe.RequiredSkill;
import zombie.scripting.objects.Recipe.Result;
import zombie.scripting.objects.Recipe.Source;
import zombie.util.StringUtils;

public final class RecipeManager {
   private static final ArrayList<Recipe> RecipeList = new ArrayList<>();

   public static void Loaded() {
      ArrayList var0 = ScriptManager.instance.getAllRecipes();
      HashSet var1 = new HashSet();

      for (int var2 = 0; var2 < var0.size(); var2++) {
         Recipe var3 = (Recipe)var0.get(var2);

         for (int var4 = 0; var4 < var3.getSource().size(); var4++) {
            Source var5 = (Source)var3.getSource().get(var4);

            for (int var6 = 0; var6 < var5.getItems().size(); var6++) {
               String var7 = (String)var5.getItems().get(var6);
               if (!"Water".equals(var7) && !var7.contains(".") && !var7.startsWith("[")) {
                  Item var8 = resolveItemModuleDotType(var3, var7, var1, "recipe source");
                  if (var8 == null) {
                     var5.getItems().set(var6, "???." + var7);
                  } else {
                     var5.getItems().set(var6, var8.getFullName());
                  }
               }
            }
         }

         if (var3.getResult() != null && var3.getResult().getModule() == null) {
            Item var9 = resolveItemModuleDotType(var3, var3.getResult().getType(), var1, "recipe result");
            if (var9 == null) {
               var3.getResult().module = "???";
            } else {
               var3.getResult().module = var9.getModule().getName();
            }
         }
      }
   }

   private static Item resolveItemModuleDotType(Recipe var0, String var1, Set<String> var2, String var3) {
      ScriptModule var4 = var0.getModule();
      Item var5 = var4.getItem(var1);
      if (var5 != null && !var5.getObsolete()) {
         return var5;
      } else {
         for (int var6 = 0; var6 < ScriptManager.instance.ModuleList.size(); var6++) {
            ScriptModule var7 = (ScriptModule)ScriptManager.instance.ModuleList.get(var6);
            var5 = var7.getItem(var1);
            if (var5 != null && !var5.getObsolete()) {
               String var8 = var0.getModule().getName();
               if (!var2.contains(var8)) {
                  var2.add(var8);
                  DebugLog.Recipe.warn("WARNING: module \"%s\" may have forgot to import module Base", new Object[]{var8});
               }

               return var5;
            }
         }

         DebugLog.Recipe.warn("ERROR: can't find %s \"%s\" in recipe \"%s\"", new Object[]{var3, var1, var0.getOriginalname()});
         return null;
      }
   }

   public static void LoadedAfterLua() {
      ArrayList var0 = new ArrayList();
      ArrayList var1 = ScriptManager.instance.getAllRecipes();

      for (int var2 = 0; var2 < var1.size(); var2++) {
         Recipe var3 = (Recipe)var1.get(var2);
         LoadedAfterLua(var3, var0);
      }

      var0.clear();
   }

   private static void LoadedAfterLua(Recipe var0, ArrayList<Item> var1) {
      LoadedAfterLua(var0, var0.LuaCreate, "LuaCreate");
      LoadedAfterLua(var0, var0.LuaGiveXP, "LuaGiveXP");
      LoadedAfterLua(var0, var0.LuaTest, "LuaTest");

      for (int var2 = 0; var2 < var0.getSource().size(); var2++) {
         Source var3 = (Source)var0.getSource().get(var2);
         LoadedAfterLua(var3, var1);
      }
   }

   private static void LoadedAfterLua(Recipe var0, String var1, String var2) {
      if (!StringUtils.isNullOrWhitespace(var1)) {
         Object var3 = LuaManager.getFunctionObject(var1);
         if (var3 == null) {
            DebugLog.General.error("no such function %s = \"%s\" in recipe \"%s\"", new Object[]{var2, var1, var0.name});
         }
      }
   }

   private static void LoadedAfterLua(Source var0, ArrayList<Item> var1) {
      for (int var2 = var0.getItems().size() - 1; var2 >= 0; var2--) {
         String var3 = (String)var0.getItems().get(var2);
         if (var3.startsWith("[")) {
            var0.getItems().remove(var2);
            String var4 = var3.substring(1, var3.indexOf("]"));
            Object var5 = LuaManager.getFunctionObject(var4);
            if (var5 != null) {
               var1.clear();
               LuaManager.caller.protectedCallVoid(LuaManager.thread, var5, var1);

               for (int var6 = 0; var6 < var1.size(); var6++) {
                  Item var7 = (Item)var1.get(var6);
                  var0.getItems().add(var2 + var6, var7.getFullName());
               }
            }
         }
      }
   }

   public static boolean DoesWipeUseDelta(String var0, String var1) {
      return true;
   }

   public static int getKnownRecipesNumber(IsoGameCharacter var0) {
      int var1 = 0;
      ArrayList var2 = ScriptManager.instance.getAllRecipes();

      for (int var3 = 0; var3 < var2.size(); var3++) {
         Recipe var4 = (Recipe)var2.get(var3);
         if (var0.isRecipeKnown(var4)) {
            var1++;
         }
      }

      return var1;
   }

   public static boolean DoesUseItemUp(String var0, Recipe var1) {
      assert "Water".equals(var0) || var0.contains(".");

      for (int var2 = 0; var2 < var1.Source.size(); var2++) {
         if (((Source)var1.Source.get(var2)).keep) {
            ArrayList var3 = ((Source)var1.Source.get(var2)).getItems();

            for (int var4 = 0; var4 < var3.size(); var4++) {
               if (var0.equals(var3.get(var4))) {
                  return false;
               }
            }
         }
      }

      return true;
   }

   public static boolean IsItemDestroyed(String var0, Recipe var1) {
      assert "Water".equals(var0) || var0.contains(".");

      for (int var2 = 0; var2 < var1.Source.size(); var2++) {
         Source var3 = (Source)var1.getSource().get(var2);
         if (var3.destroy) {
            for (int var4 = 0; var4 < var3.getItems().size(); var4++) {
               if (var0.equals(var3.getItems().get(var4))) {
                  return true;
               }
            }
         }
      }

      return false;
   }

   public static float UseAmount(String var0, Recipe var1, IsoGameCharacter var2) {
      Source var3 = var1.findSource(var0);
      return var3.getCount();
   }

   public static ArrayList<Recipe> getUniqueRecipeItems(InventoryItem var0, IsoGameCharacter var1, ArrayList<ItemContainer> var2) {
      RecipeList.clear();
      ArrayList var3 = ScriptManager.instance.getAllRecipes();

      for (int var4 = 0; var4 < var3.size(); var4++) {
         Recipe var5 = (Recipe)var3.get(var4);
         if (IsRecipeValid(var5, var1, var0, var2)
            && (!(var0 instanceof Clothing) || var0.getCondition() > 0 || !var5.getOriginalname().equalsIgnoreCase("rip clothing"))) {
            RecipeList.add(var5);
         }
      }

      if (var0 instanceof Moveable && RecipeList.size() == 0 && ((Moveable)var0).getWorldSprite() != null) {
         if (var0.type != null && var0.type.equalsIgnoreCase(((Moveable)var0).getWorldSprite())) {
            MovableRecipe var6 = new MovableRecipe();
            LuaEventManager.triggerEvent("OnDynamicMovableRecipe", ((Moveable)var0).getWorldSprite(), var6, var0, var1);
            if (var6.isValid() && IsRecipeValid(var6, var1, var0, var2)) {
               RecipeList.add(var6);
            }
         } else {
            DebugLog.log("RecipeManager -> Cannot create recipe for this movable item: " + var0.getFullType());
         }
      }

      return RecipeList;
   }

   public static boolean IsRecipeValid(Recipe var0, IsoGameCharacter var1, InventoryItem var2, ArrayList<ItemContainer> var3) {
      if (var0.Result == null) {
         return false;
      } else if (!var1.isRecipeKnown(var0)) {
         return false;
      } else if (var2 != null && !RecipeContainsItem(var0, var2)) {
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

   private static boolean isNearItem(Recipe var0, IsoGameCharacter var1) {
      if (var0.getNearItem() != null && !var0.getNearItem().equals("")) {
         for (int var2 = var1.getSquare().getX() - 2; var2 < var1.getSquare().getX() + 2; var2++) {
            for (int var3 = var1.getSquare().getY() - 2; var3 < var1.getSquare().getY() + 2; var3++) {
               IsoGridSquare var4 = var1.getCell().getGridSquare(var2, var3, var1.getSquare().getZ());
               if (var4 != null) {
                  for (int var5 = 0; var5 < var4.getObjects().size(); var5++) {
                     if (var0.getNearItem().equals(((IsoObject)var4.getObjects().get(var5)).getName())) {
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

   private static boolean CanPerform(Recipe var0, IsoGameCharacter var1, InventoryItem var2) {
      if (StringUtils.isNullOrWhitespace(var0.getCanPerform())) {
         return true;
      } else {
         Object var3 = LuaManager.getFunctionObject(var0.getCanPerform());
         if (var3 == null) {
            return false;
         } else {
            Boolean var4 = LuaManager.caller.protectedCallBoolean(LuaManager.thread, var3, var0, var1, var2);
            return var4 == Boolean.TRUE;
         }
      }
   }

   private static boolean HasRequiredSkill(Recipe var0, IsoGameCharacter var1) {
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

   private static boolean RecipeContainsItem(Recipe var0, InventoryItem var1) {
      for (int var2 = 0; var2 < var0.Source.size(); var2++) {
         Source var3 = (Source)var0.getSource().get(var2);

         for (int var4 = 0; var4 < var3.getItems().size(); var4++) {
            String var5 = (String)var3.getItems().get(var4);
            if ("Water".equals(var5) && var1.isWaterSource()) {
               return true;
            }

            if (var5.equals(var1.getFullType())) {
               return true;
            }
         }
      }

      return false;
   }

   public static boolean HasAllRequiredItems(Recipe var0, IsoGameCharacter var1, InventoryItem var2, ArrayList<ItemContainer> var3) {
      ArrayList var4 = getAvailableItemsNeeded(var0, var1, var3, var2, null);
      return !var4.isEmpty();
   }

   public static boolean isAllItemsUsableRotten(Recipe var0, IsoGameCharacter var1, InventoryItem var2, ArrayList<ItemContainer> var3) {
      if (var1.getPerkLevel(Perks.Cooking) >= 7) {
         return true;
      } else if (var0.isAllowRottenItem()) {
         return true;
      } else {
         for (InventoryItem var6 : getAvailableItemsNeeded(var0, var1, var3, var2, null)) {
            if (var6 instanceof Food && ((Food)var6).isRotten()) {
               return false;
            }
         }

         return true;
      }
   }

   public static boolean hasHeat(Recipe var0, InventoryItem var1, ArrayList<ItemContainer> var2, IsoGameCharacter var3) {
      if (var0.getHeat() == 0.0F) {
         return true;
      } else {
         InventoryItem var4 = null;

         for (InventoryItem var6 : getAvailableItemsNeeded(var0, var3, var2, var1, null)) {
            if (var6 instanceof DrainableComboItem) {
               var4 = var6;
               break;
            }
         }

         if (var4 != null) {
            for (ItemContainer var10 : var2) {
               for (InventoryItem var8 : var10.getItems()) {
                  if (var8.getName().equals(var4.getName())) {
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

   public static ArrayList<InventoryItem> getAvailableItemsAll(
      Recipe var0, IsoGameCharacter var1, ArrayList<ItemContainer> var2, InventoryItem var3, ArrayList<InventoryItem> var4
   ) {
      return getAvailableItems(var0, var1, var2, var3, var4, true).allItems;
   }

   public static ArrayList<InventoryItem> getAvailableItemsNeeded(
      Recipe var0, IsoGameCharacter var1, ArrayList<ItemContainer> var2, InventoryItem var3, ArrayList<InventoryItem> var4
   ) {
      return getAvailableItems(var0, var1, var2, var3, var4, false).allItems;
   }

   private static SourceItems getAvailableItems(
      Recipe var0, IsoGameCharacter var1, ArrayList<ItemContainer> var2, InventoryItem var3, ArrayList<InventoryItem> var4, boolean var5
   ) {
      if (var3 != null && (var3.getContainer() == null || !var3.getContainer().contains(var3))) {
         DebugLog.Recipe.warn("recipe: item appears to have been used already, ignoring " + var3.getFullType());
         var3 = null;
      }

      SourceItems var6 = new SourceItems(var0, var1, var3, var4);
      if (var2 == null) {
         var2 = new ArrayList();
         var2.add(var1.getInventory());
      }

      if (var3 != null && !RecipeContainsItem(var0, var3)) {
         throw new RuntimeException("item " + var3.getFullType() + " isn't used in recipe " + var0.getOriginalname());
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

   public static ArrayList<InventoryItem> getSourceItemsAll(
      Recipe var0, int var1, IsoGameCharacter var2, ArrayList<ItemContainer> var3, InventoryItem var4, ArrayList<InventoryItem> var5
   ) {
      if (var1 >= 0 && var1 < var0.getSource().size()) {
         SourceItems var6 = getAvailableItems(var0, var2, var3, var4, var5, true);
         return var6.itemsPerSource[var1];
      } else {
         return null;
      }
   }

   public static ArrayList<InventoryItem> getSourceItemsNeeded(
      Recipe var0, int var1, IsoGameCharacter var2, ArrayList<ItemContainer> var3, InventoryItem var4, ArrayList<InventoryItem> var5
   ) {
      if (var1 >= 0 && var1 < var0.getSource().size()) {
         SourceItems var6 = getAvailableItems(var0, var2, var3, var4, var5, false);
         return var6.itemsPerSource[var1];
      } else {
         return null;
      }
   }

   public static int getNumberOfTimesRecipeCanBeDone(Recipe var0, IsoGameCharacter var1, ArrayList<ItemContainer> var2, InventoryItem var3) {
      int var4 = 0;
      RMRecipe var5 = RMRecipe.alloc(var0);
      if (var2 == null) {
         var2 = new ArrayList();
         var2.add(var1.getInventory());
      }

      var5.getItemsFromContainers(var1, var2, var3);
      ArrayList var6 = new ArrayList();

      for (ArrayList var7 = new ArrayList(); var5.hasItems(); var4++) {
         var7.clear();
         var5.Use(var7);
         if (var6.containsAll(var7)) {
            var4 = -1;
            break;
         }

         var6.addAll(var7);

         for (int var8 = 0; var8 < var7.size(); var8++) {
            InventoryItem var9 = (InventoryItem)var7.get(var8);
            if (var9 instanceof Food && ((Food)var9).isFrozen() && !var5.recipe.isAllowFrozenItem()) {
               var4--;
               break;
            }
         }
      }

      RMRecipe.release(var5);
      return var4;
   }

   public static InventoryItem GetMovableRecipeTool(boolean var0, Recipe var1, InventoryItem var2, IsoGameCharacter var3, ArrayList<ItemContainer> var4) {
      if (!(var1 instanceof MovableRecipe var5)) {
         return null;
      } else {
         Source var6 = var0 ? var5.getPrimaryTools() : var5.getSecondaryTools();
         if (var6 != null && var6.getItems() != null && var6.getItems().size() != 0) {
            SourceItems var7 = getAvailableItems(var1, var3, var4, var2, null, false);
            if (var7.allItems != null && var7.allItems.size() != 0) {
               for (int var8 = 0; var8 < var7.allItems.size(); var8++) {
                  InventoryItem var9 = (InventoryItem)var7.allItems.get(var8);

                  for (int var10 = 0; var10 < var6.getItems().size(); var10++) {
                     if (var9.getFullType().equalsIgnoreCase((String)var6.getItems().get(var10))) {
                        return var9;
                     }
                  }
               }

               return null;
            } else {
               return null;
            }
         } else {
            return null;
         }
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
   public static InventoryItem PerformMakeItem(Recipe var0, InventoryItem var1, IsoGameCharacter var2, ArrayList<ItemContainer> var3) {
      boolean var4 = var2.getPrimaryHandItem() == var1;
      boolean var5 = var2.getSecondaryHandItem() == var1;
      SourceItems var6 = getAvailableItems(var0, var2, var3, var1, null, false);
      ArrayList var7 = var6.allItems;
      if (var7.isEmpty()) {
         throw new RuntimeException("getAvailableItems() didn't return the required number of items");
      } else {
         var2.removeFromHands(var1);
         Result var8 = var0.getResult();
         InventoryItem var9 = InventoryItemFactory.CreateItem(var8.getFullType());
         boolean var10 = false;
         boolean var11 = false;
         int var12 = -1;
         int var13 = 0;
         boolean var14 = false;
         boolean var15 = false;
         float var16 = 0.0F;
         float var17 = 0.0F;
         int var18 = 0;
         int var19 = 0;

         for (int var20 = 0; var20 < var0.getSource().size(); var20++) {
            Source var21 = (Source)var0.getSource().get(var20);
            if (!var21.isKeep()) {
               ArrayList var22 = var6.itemsPerSource[var20];
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
                        throw new RuntimeException("required amount of " + var21.getItems() + " wasn't available");
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
                        throw new RuntimeException("required amount of water wasn't available");
                     }
               }
            }
         }

         for (int var30 = 0; var30 < var7.size(); var30++) {
            InventoryItem var33 = (InventoryItem)var7.get(var30);
            if (var33 instanceof Food) {
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

            if (var9 instanceof Food && var33.isTaintedWater()) {
               var9.setTaintedWater(true);
            }

            if (var9.getScriptItem() == var33.getScriptItem() && var33.isFavorite()) {
               var9.setFavorite(true);
            }

            var16 += (float)var33.getCondition() / var33.getConditionMax();
            var18++;
         }

         var17 /= var19;
         if (var9 instanceof Food && ((Food)var9).IsCookable) {
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
         if (var0.LuaCreate != null) {
            Object var32 = LuaManager.getFunctionObject(var0.LuaCreate);
            if (var32 != null) {
               LuaManager.caller.protectedCall(LuaManager.thread, var32, new Object[]{var7, var9, var2, var1, var4, var5});
            }
         }

         return !var0.isRemoveResultItem() ? var9 : null;
      }
   }

   private static boolean ReduceUses(InventoryItem var0, float var1, IsoGameCharacter var2) {
      if (var0 instanceof DrainableComboItem var3) {
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

      if (var0 instanceof Food var6 && var6.getHungerChange() < 0.0F) {
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

   private static int AvailableUses(InventoryItem var0) {
      if (var0 instanceof DrainableComboItem var2) {
         return var2.getDrainableUsesInt();
      } else {
         return var0 instanceof Food var1 ? (int)(-var1.getHungerChange() * 100.0F) : 0;
      }
   }

   private static void GivePlayerExperience(Recipe var0, ArrayList<InventoryItem> var1, InventoryItem var2, IsoGameCharacter var3) {
      String var4 = var0.LuaGiveXP;
      if (var4 == null) {
         var4 = "Recipe.OnGiveXP.Default";
      }

      Object var5 = LuaManager.getFunctionObject(var4);
      if (var5 == null) {
         DebugLog.Recipe.warn("ERROR: Lua method \"" + var4 + "\" not found (in RecipeManager.GivePlayerExperience())");
      } else {
         LuaManager.caller.protectedCall(LuaManager.thread, var5, new Object[]{var0, var1, var2, var3});
      }
   }

   public static ArrayList<EvolvedRecipe> getAllEvolvedRecipes() {
      Stack var0 = ScriptManager.instance.getAllEvolvedRecipes();
      ArrayList var1 = new ArrayList();

      for (int var2 = 0; var2 < var0.size(); var2++) {
         var1.add((EvolvedRecipe)var0.get(var2));
      }

      return var1;
   }

   public static ArrayList<EvolvedRecipe> getEvolvedRecipe(InventoryItem var0, IsoGameCharacter var1, ArrayList<ItemContainer> var2, boolean var3) {
      ArrayList var4 = new ArrayList();
      if (var0 instanceof Food && ((Food)var0).isRotten() && var1.getPerkLevel(Perks.Cooking) < 7) {
         return var4;
      } else {
         Stack var5 = ScriptManager.instance.getAllEvolvedRecipes();

         for (int var6 = 0; var6 < var5.size(); var6++) {
            EvolvedRecipe var7 = (EvolvedRecipe)var5.get(var6);
            if ((var0.isCooked() && var7.addIngredientIfCooked || !var0.isCooked())
               && (var0.getType().equals(var7.baseItem) || var0.getType().equals(var7.getResultItem()))
               && (!var0.getType().equals("WaterPot") || !(((Drainable)var0).getUsedDelta() < 0.75))) {
               if (var3) {
                  ArrayList var8 = var7.getItemsCanBeUse(var1, var0, var2);
                  if (!var8.isEmpty()) {
                     if (!(var0 instanceof Food) || !((Food)var0).isFrozen()) {
                        var4.add(var7);
                     } else if (var7.isAllowFrozenItem()) {
                        var4.add(var7);
                     }
                  }
               } else {
                  var4.add(var7);
               }
            }
         }

         return var4;
      }
   }

   private static void DebugPrintAllRecipes() {
      ArrayList var0 = ScriptManager.instance.getAllRecipes();

      for (int var1 = 0; var1 < var0.size(); var1++) {
         Recipe var2 = (Recipe)var0.get(var1);
         if (var2 == null) {
            DebugLog.Recipe.println("Null recipe.");
         } else if (var2.Result == null) {
            DebugLog.Recipe.println("Null result.");
         } else {
            DebugLog.Recipe.println(var2.Result.type);
            DebugLog.Recipe.println("-----");

            for (int var3 = 0; var3 < var2.Source.size(); var3++) {
               if (var2.Source.get(var3) == null) {
                  DebugLog.Recipe.println("Null ingredient.");
               } else if (((Source)var2.Source.get(var3)).getItems().isEmpty()) {
                  DebugLog.Recipe.println(((Source)var2.Source.get(var3)).getItems().toString());
               }
            }
         }
      }
   }

   public static Recipe getDismantleRecipeFor(String var0) {
      RecipeList.clear();
      ArrayList var1 = ScriptManager.instance.getAllRecipes();

      for (int var2 = 0; var2 < var1.size(); var2++) {
         Recipe var3 = (Recipe)var1.get(var2);
         ArrayList var4 = var3.getSource();
         if (var4.size() > 0) {
            for (int var5 = 0; var5 < var4.size(); var5++) {
               Source var6 = (Source)var4.get(var5);

               for (int var7 = 0; var7 < var6.getItems().size(); var7++) {
                  if (((String)var6.getItems().get(var7)).equalsIgnoreCase(var0) && var3.name.toLowerCase().startsWith("dismantle ")) {
                     return var3;
                  }
               }
            }
         }
      }

      return null;
   }
}
