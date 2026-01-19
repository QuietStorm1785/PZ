package zombie.characters.skills;

import zombie.characters.skills.PerkFactory.Perk;

public final class PerkFactory$Perks {
   public static final Perk None = new Perk("None");
   public static final Perk Agility = new Perk("Agility");
   public static final Perk Cooking = new Perk("Cooking");
   public static final Perk Melee = new Perk("Melee");
   public static final Perk Crafting = new Perk("Crafting");
   public static final Perk Fitness = new Perk("Fitness");
   public static final Perk Strength = new Perk("Strength");
   public static final Perk Blunt = new Perk("Blunt");
   public static final Perk Axe = new Perk("Axe");
   public static final Perk Sprinting = new Perk("Sprinting");
   public static final Perk Lightfoot = new Perk("Lightfoot");
   public static final Perk Nimble = new Perk("Nimble");
   public static final Perk Sneak = new Perk("Sneak");
   public static final Perk Woodwork = new Perk("Woodwork");
   public static final Perk Aiming = new Perk("Aiming");
   public static final Perk Reloading = new Perk("Reloading");
   public static final Perk Farming = new Perk("Farming");
   public static final Perk Survivalist = new Perk("Survivalist");
   public static final Perk Fishing = new Perk("Fishing");
   public static final Perk Trapping = new Perk("Trapping");
   public static final Perk Passiv = new Perk("Passiv");
   public static final Perk Firearm = new Perk("Firearm");
   public static final Perk PlantScavenging = new Perk("PlantScavenging");
   public static final Perk Doctor = new Perk("Doctor");
   public static final Perk Electricity = new Perk("Electricity");
   public static final Perk Blacksmith = new Perk("Blacksmith");
   public static final Perk MetalWelding = new Perk("MetalWelding");
   public static final Perk Melting = new Perk("Melting");
   public static final Perk Mechanics = new Perk("Mechanics");
   public static final Perk Spear = new Perk("Spear");
   public static final Perk Maintenance = new Perk("Maintenance");
   public static final Perk SmallBlade = new Perk("SmallBlade");
   public static final Perk LongBlade = new Perk("LongBlade");
   public static final Perk SmallBlunt = new Perk("SmallBlunt");
   public static final Perk Combat = new Perk("Combat");
   public static final Perk Tailoring = new Perk("Tailoring");
   public static final Perk MAX = new Perk("MAX");

   public static int getMaxIndex() {
      return MAX.index();
   }

   public static Perk fromIndex(int var0) {
      return var0 >= 0 && var0 <= PerkFactory.NextPerkID ? PerkFactory.PerkByIndex[var0] : null;
   }

   public static Perk FromString(String var0) {
      return PerkFactory.PerkById.getOrDefault(var0, MAX);
   }
}
