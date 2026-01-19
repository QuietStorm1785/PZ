package zombie.characters.skills;

import java.util.ArrayList;
import java.util.HashMap;
import zombie.characters.skills.PerkFactory.Perk;
import zombie.characters.skills.PerkFactory.Perks;
import zombie.core.Translator;

public final class PerkFactory {
   public static final ArrayList<Perk> PerkList = new ArrayList<>();
   private static final HashMap<String, Perk> PerkById = new HashMap<>();
   private static final HashMap<String, Perk> PerkByName = new HashMap<>();
   private static final Perk[] PerkByIndex = new Perk[256];
   private static int NextPerkID = 0;
   static float PerkXPReqMultiplier = 1.5F;

   public static String getPerkName(Perk var0) {
      return var0.getName();
   }

   public static Perk getPerkFromName(String var0) {
      return PerkByName.get(var0);
   }

   public static Perk getPerk(Perk var0) {
      return var0;
   }

   public static Perk AddPerk(Perk var0, String var1, int var2, int var3, int var4, int var5, int var6, int var7, int var8, int var9, int var10, int var11) {
      return AddPerk(var0, var1, Perks.None, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, false);
   }

   public static Perk AddPerk(
      Perk var0, String var1, int var2, int var3, int var4, int var5, int var6, int var7, int var8, int var9, int var10, int var11, boolean var12
   ) {
      return AddPerk(var0, var1, Perks.None, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12);
   }

   public static Perk AddPerk(
      Perk var0, String var1, Perk var2, int var3, int var4, int var5, int var6, int var7, int var8, int var9, int var10, int var11, int var12
   ) {
      return AddPerk(var0, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, false);
   }

   public static Perk AddPerk(
      Perk var0, String var1, Perk var2, int var3, int var4, int var5, int var6, int var7, int var8, int var9, int var10, int var11, int var12, boolean var13
   ) {
      var0.translation = var1;
      var0.name = Translator.getText("IGUI_perks_" + var1);
      var0.parent = var2;
      var0.passiv = var13;
      var0.xp1 = (int)(var3 * PerkXPReqMultiplier);
      var0.xp2 = (int)(var4 * PerkXPReqMultiplier);
      var0.xp3 = (int)(var5 * PerkXPReqMultiplier);
      var0.xp4 = (int)(var6 * PerkXPReqMultiplier);
      var0.xp5 = (int)(var7 * PerkXPReqMultiplier);
      var0.xp6 = (int)(var8 * PerkXPReqMultiplier);
      var0.xp7 = (int)(var9 * PerkXPReqMultiplier);
      var0.xp8 = (int)(var10 * PerkXPReqMultiplier);
      var0.xp9 = (int)(var11 * PerkXPReqMultiplier);
      var0.xp10 = (int)(var12 * PerkXPReqMultiplier);
      PerkByName.put(var0.getName(), var0);
      PerkList.add(var0);
      return var0;
   }

   public static void init() {
      Perks.None.parent = Perks.None;
      Perks.MAX.parent = Perks.None;
      AddPerk(Perks.Combat, "Combat", 50, 100, 200, 500, 1000, 2000, 3000, 4000, 5000, 6000);
      AddPerk(Perks.Axe, "Axe", Perks.Combat, 50, 100, 200, 500, 1000, 2000, 3000, 4000, 5000, 6000);
      AddPerk(Perks.Blunt, "Blunt", Perks.Combat, 50, 100, 200, 500, 1000, 2000, 3000, 4000, 5000, 6000);
      AddPerk(Perks.SmallBlunt, "SmallBlunt", Perks.Combat, 50, 100, 200, 500, 1000, 2000, 3000, 4000, 5000, 6000);
      AddPerk(Perks.LongBlade, "LongBlade", Perks.Combat, 50, 100, 200, 500, 1000, 2000, 3000, 4000, 5000, 6000);
      AddPerk(Perks.SmallBlade, "SmallBlade", Perks.Combat, 50, 100, 200, 500, 1000, 2000, 3000, 4000, 5000, 6000);
      AddPerk(Perks.Spear, "Spear", Perks.Combat, 50, 100, 200, 500, 1000, 2000, 3000, 4000, 5000, 6000);
      AddPerk(Perks.Maintenance, "Maintenance", Perks.Combat, 50, 100, 200, 500, 1000, 2000, 3000, 4000, 5000, 6000);
      AddPerk(Perks.Firearm, "Firearm", 50, 100, 200, 500, 1000, 2000, 3000, 4000, 5000, 6000);
      AddPerk(Perks.Aiming, "Aiming", Perks.Firearm, 50, 100, 200, 500, 1000, 2000, 3000, 4000, 5000, 6000);
      AddPerk(Perks.Reloading, "Reloading", Perks.Firearm, 50, 100, 200, 500, 1000, 2000, 3000, 4000, 5000, 6000);
      AddPerk(Perks.Crafting, "Crafting", 50, 100, 200, 500, 1000, 2000, 3000, 4000, 5000, 6000);
      AddPerk(Perks.Woodwork, "Carpentry", Perks.Crafting, 50, 100, 200, 500, 1000, 2000, 3000, 4000, 5000, 6000);
      AddPerk(Perks.Cooking, "Cooking", Perks.Crafting, 50, 100, 200, 500, 1000, 2000, 3000, 4000, 5000, 6000);
      AddPerk(Perks.Farming, "Farming", Perks.Crafting, 50, 100, 200, 500, 1000, 2000, 3000, 4000, 5000, 6000);
      AddPerk(Perks.Doctor, "Doctor", Perks.Crafting, 50, 100, 200, 500, 1000, 2000, 3000, 4000, 5000, 6000);
      AddPerk(Perks.Electricity, "Electricity", Perks.Crafting, 50, 100, 200, 500, 1000, 2000, 3000, 4000, 5000, 6000);
      AddPerk(Perks.MetalWelding, "MetalWelding", Perks.Crafting, 50, 100, 200, 500, 1000, 2000, 3000, 4000, 5000, 6000);
      AddPerk(Perks.Mechanics, "Mechanics", Perks.Crafting, 50, 100, 200, 500, 1000, 2000, 3000, 4000, 5000, 6000);
      AddPerk(Perks.Tailoring, "Tailoring", Perks.Crafting, 50, 100, 200, 500, 1000, 2000, 3000, 4000, 5000, 6000);
      AddPerk(Perks.Survivalist, "Survivalist", 50, 100, 200, 500, 1000, 2000, 3000, 4000, 5000, 6000);
      AddPerk(Perks.Fishing, "Fishing", Perks.Survivalist, 50, 100, 200, 500, 1000, 2000, 3000, 4000, 5000, 6000);
      AddPerk(Perks.Trapping, "Trapping", Perks.Survivalist, 50, 100, 200, 500, 1000, 2000, 3000, 4000, 5000, 6000);
      AddPerk(Perks.PlantScavenging, "Foraging", Perks.Survivalist, 50, 100, 200, 500, 1000, 2000, 3000, 4000, 5000, 6000);
      AddPerk(Perks.Passiv, "Passive", 50, 100, 200, 500, 1000, 2000, 3000, 4000, 5000, 6000, true);
      AddPerk(Perks.Fitness, "Fitness", Perks.Passiv, 1000, 2000, 4000, 6000, 12000, 20000, 40000, 60000, 80000, 100000, true);
      AddPerk(Perks.Strength, "Strength", Perks.Passiv, 1000, 2000, 4000, 6000, 12000, 20000, 40000, 60000, 80000, 100000, true);
      AddPerk(Perks.Agility, "Agility", 50, 100, 200, 500, 1000, 2000, 3000, 4000, 5000, 6000);
      AddPerk(Perks.Sprinting, "Sprinting", Perks.Agility, 50, 100, 200, 500, 1000, 2000, 3000, 4000, 5000, 6000);
      AddPerk(Perks.Lightfoot, "Lightfooted", Perks.Agility, 50, 100, 200, 500, 1000, 2000, 3000, 4000, 5000, 6000);
      AddPerk(Perks.Nimble, "Nimble", Perks.Agility, 50, 100, 200, 500, 1000, 2000, 3000, 4000, 5000, 6000);
      AddPerk(Perks.Sneak, "Sneaking", Perks.Agility, 50, 100, 200, 500, 1000, 2000, 3000, 4000, 5000, 6000);
   }

   public static void initTranslations() {
      PerkByName.clear();

      for (Perk var1 : PerkList) {
         var1.name = Translator.getText("IGUI_perks_" + var1.translation);
         PerkByName.put(var1.name, var1);
      }
   }

   public static void Reset() {
      NextPerkID = 0;

      for (int var0 = PerkByIndex.length - 1; var0 >= 0; var0--) {
         Perk var1 = PerkByIndex[var0];
         if (var1 != null) {
            if (var1.isCustom()) {
               PerkList.remove(var1);
               PerkById.remove(var1.getId());
               PerkByName.remove(var1.getName());
               PerkByIndex[var1.index] = null;
            } else if (var1 != Perks.MAX && NextPerkID == 0) {
               NextPerkID = var0 + 1;
            }
         }
      }

      Perks.MAX.index = NextPerkID;
   }
}
