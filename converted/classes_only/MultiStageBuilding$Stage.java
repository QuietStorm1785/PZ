package zombie.iso;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map.Entry;
import se.krka.kahlua.vm.KahluaTable;
import zombie.SandboxOptions;
import zombie.Lua.LuaManager;
import zombie.characters.IsoGameCharacter;
import zombie.characters.skills.PerkFactory.Perks;
import zombie.core.Translator;
import zombie.inventory.InventoryItem;
import zombie.inventory.ItemContainer;
import zombie.inventory.types.DrainableComboItem;
import zombie.iso.objects.IsoThumpable;
import zombie.scripting.ScriptManager;
import zombie.scripting.objects.Item;
import zombie.scripting.objects.Item.Type;
import zombie.util.StringUtils;

public class MultiStageBuilding$Stage {
   public String name;
   public ArrayList<String> previousStage;
   public String recipeName;
   public String sprite;
   public String northSprite;
   public int timeNeeded;
   public int bonusHealth;
   public boolean bonusHealthSkill;
   public HashMap<String, Integer> xp;
   public HashMap<String, Integer> perks;
   public HashMap<String, Integer> items;
   public ArrayList<String> itemsToKeep;
   public String knownRecipe;
   public String thumpSound;
   public String wallType;
   public boolean canBePlastered;
   public String craftingSound;
   public String completionSound;
   public String ID;
   public boolean canBarricade;

   public MultiStageBuilding$Stage(MultiStageBuilding var1) {
      this.this$0 = var1;
      this.previousStage = new ArrayList<>();
      this.bonusHealthSkill = true;
      this.xp = new HashMap<>();
      this.perks = new HashMap<>();
      this.items = new HashMap<>();
      this.itemsToKeep = new ArrayList<>();
      this.thumpSound = "ZombieThumpGeneric";
      this.completionSound = "BuildWoodenStructureMedium";
      this.canBarricade = false;
   }

   public String getName() {
      return this.name;
   }

   public String getDisplayName() {
      return Translator.getMultiStageBuild(this.recipeName);
   }

   public String getSprite() {
      return this.sprite;
   }

   public String getNorthSprite() {
      return this.northSprite;
   }

   public String getThumpSound() {
      return this.thumpSound;
   }

   public String getRecipeName() {
      return this.recipeName;
   }

   public String getKnownRecipe() {
      return this.knownRecipe;
   }

   public int getTimeNeeded(IsoGameCharacter var1) {
      int var2 = this.timeNeeded;

      for (Entry var4 : this.xp.entrySet()) {
         var2 -= var1.getPerkLevel(Perks.FromString((String)var4.getKey())) * 10;
      }

      return var2;
   }

   public ArrayList<String> getItemsToKeep() {
      return this.itemsToKeep;
   }

   public ArrayList<String> getPreviousStages() {
      return this.previousStage;
   }

   public String getCraftingSound() {
      return this.craftingSound;
   }

   public KahluaTable getItemsLua() {
      KahluaTable var1 = LuaManager.platform.newTable();

      for (Entry var3 : this.items.entrySet()) {
         var1.rawset(var3.getKey(), ((Integer)var3.getValue()).toString());
      }

      return var1;
   }

   public KahluaTable getPerksLua() {
      KahluaTable var1 = LuaManager.platform.newTable();

      for (Entry var3 : this.perks.entrySet()) {
         var1.rawset(Perks.FromString((String)var3.getKey()), ((Integer)var3.getValue()).toString());
      }

      return var1;
   }

   public void doStage(IsoGameCharacter var1, IsoThumpable var2, boolean var3) {
      int var4 = var2.getHealth();
      int var5 = var2.getMaxHealth();
      String var6 = this.sprite;
      if (var2.north) {
         var6 = this.northSprite;
      }

      IsoThumpable var7 = new IsoThumpable(IsoWorld.instance.getCell(), var2.square, var6, var2.north, var2.getTable());
      var7.setCanBePlastered(this.canBePlastered);
      if ("doorframe".equals(this.wallType)) {
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
      byte var11 = 20;
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
            String var10 = (String)var9.next();
            var12 += var1.getPerkLevel(Perks.FromString(var10)) * var11;
         }
      }

      var7.setMaxHealth(var5 + var8 + var12);
      var7.setHealth(var4 + var8 + var12);
      var7.setName(this.name);
      var7.setThumpSound(this.getThumpSound());
      var7.setCanBarricade(this.canBarricade);
      var7.setModData(var2.getModData());
      if (this.wallType != null) {
         var7.getModData().rawset("wallType", this.wallType);
      }

      if (var3) {
         ItemContainer var13 = var1.getInventory();

         for (String var15 : this.items.keySet()) {
            int var16 = this.items.get(var15);
            Item var17 = ScriptManager.instance.getItem(var15);
            if (var17 != null) {
               if (var17.getType() == Type.Drainable) {
                  InventoryItem var23 = var13.getFirstRecurse(
                     var2x -> var2x.getFullType().equals(var17.getFullName()) && ((DrainableComboItem)var2x).getDrainableUsesInt() >= var16
                  );
                  if (var23 != null) {
                     for (int var24 = 0; var24 < var16; var24++) {
                        var23.Use();
                     }
                  }
               } else {
                  for (int var18 = 0; var18 < var16; var18++) {
                     InventoryItem var19 = var13.getFirstTypeRecurse(var15);
                     if (var19 != null) {
                        var19.Use();
                     }
                  }
               }
            }
         }
      }

      for (String var21 : this.xp.keySet()) {
         var1.getXp().AddXP(Perks.FromString(var21), this.xp.get(var21).intValue());
      }

      int var22 = var2.getSquare().transmitRemoveItemFromSquare(var2);
      var7.getSquare().AddSpecialObject(var7, var22);
      var7.getSquare().RecalcAllWithNeighbours(true);
      var7.transmitCompleteItemToServer();
      if (var1 != null && !StringUtils.isNullOrWhitespace(this.completionSound)) {
         var1.playSound(this.completionSound);
      }
   }

   public boolean canBeDone(IsoGameCharacter var1, IsoObject var2, boolean var3) {
      ItemContainer var4 = var1.getInventory();
      boolean var5 = false;

      for (int var6 = 0; var6 < this.previousStage.size(); var6++) {
         if (this.previousStage.get(var6).equalsIgnoreCase(var2.getName())) {
            var5 = true;
            break;
         }
      }

      return var5;
   }

   public void Load(String var1, String[] var2) {
      this.recipeName = var1;

      for (int var3 = 0; var3 < var2.length; var3++) {
         if (!var2[var3].trim().isEmpty() && var2[var3].contains(":")) {
            String[] var4 = var2[var3].split(":");
            String var5 = var4[0].trim();
            String var6 = var4[1].trim();
            if (var5.equalsIgnoreCase("Name")) {
               this.name = var6.trim();
            }

            if (var5.equalsIgnoreCase("TimeNeeded")) {
               this.timeNeeded = Integer.parseInt(var6.trim());
            }

            if (var5.equalsIgnoreCase("BonusHealth")) {
               this.bonusHealth = Integer.parseInt(var6.trim());
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
               this.canBePlastered = Boolean.parseBoolean(var6.trim());
            }

            if (var5.equalsIgnoreCase("BonusSkill")) {
               this.bonusHealthSkill = Boolean.parseBoolean(var6.trim());
            }

            if (var5.equalsIgnoreCase("CanBarricade")) {
               this.canBarricade = Boolean.parseBoolean(var6.trim());
            }

            if (var5.equalsIgnoreCase("XP")) {
               String[] var7 = var6.split(";");

               for (int var8 = 0; var8 < var7.length; var8++) {
                  String[] var9 = var7[var8].split("=");
                  this.xp.put(var9[0], Integer.parseInt(var9[1]));
               }
            }

            if (var5.equalsIgnoreCase("PreviousStage")) {
               String[] var10 = var6.split(";");

               for (int var14 = 0; var14 < var10.length; var14++) {
                  this.previousStage.add(var10[var14]);
               }
            }

            if (var5.equalsIgnoreCase("SkillRequired")) {
               String[] var11 = var6.split(";");

               for (int var15 = 0; var15 < var11.length; var15++) {
                  String[] var18 = var11[var15].split("=");
                  this.perks.put(var18[0], Integer.parseInt(var18[1]));
               }
            }

            if (var5.equalsIgnoreCase("ItemsRequired")) {
               String[] var12 = var6.split(";");

               for (int var16 = 0; var16 < var12.length; var16++) {
                  String[] var19 = var12[var16].split("=");
                  this.items.put(var19[0], Integer.parseInt(var19[1]));
               }
            }

            if (var5.equalsIgnoreCase("ItemsToKeep")) {
               String[] var13 = var6.split(";");

               for (int var17 = 0; var17 < var13.length; var17++) {
                  this.itemsToKeep.add(var13[var17]);
               }
            }
         }
      }
   }
}
