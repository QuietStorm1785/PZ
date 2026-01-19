package zombie.characters.skills;

import zombie.characters.skills.PerkFactory.Perks;
import zombie.core.math.PZMath;

public final class PerkFactory$Perk {
   private final String id;
   private int index;
   private boolean bCustom = false;
   public String translation;
   public String name;
   public boolean passiv = false;
   public int xp1;
   public int xp2;
   public int xp3;
   public int xp4;
   public int xp5;
   public int xp6;
   public int xp7;
   public int xp8;
   public int xp9;
   public int xp10;
   public PerkFactory$Perk parent = Perks.None;

   public PerkFactory$Perk(String var1) {
      this.id = var1;
      this.index = PerkFactory.NextPerkID++;
      this.translation = var1;
      this.name = var1;
      PerkFactory.PerkById.put(var1, this);
      PerkFactory.PerkByIndex[this.index] = this;
      if (Perks.MAX != null) {
         Perks.MAX.index = PZMath.max(Perks.MAX.index, this.index + 1);
      }
   }

   public PerkFactory$Perk(String var1, PerkFactory$Perk var2) {
      this(var1);
      this.parent = var2;
   }

   public String getId() {
      return this.id;
   }

   public int index() {
      return this.index;
   }

   public void setCustom() {
      this.bCustom = true;
   }

   public boolean isCustom() {
      return this.bCustom;
   }

   public boolean isPassiv() {
      return this.passiv;
   }

   public PerkFactory$Perk getParent() {
      return this.parent;
   }

   public String getName() {
      return this.name;
   }

   public PerkFactory$Perk getType() {
      return this;
   }

   public int getXp1() {
      return this.xp1;
   }

   public int getXp2() {
      return this.xp2;
   }

   public int getXp3() {
      return this.xp3;
   }

   public int getXp4() {
      return this.xp4;
   }

   public int getXp5() {
      return this.xp5;
   }

   public int getXp6() {
      return this.xp6;
   }

   public int getXp7() {
      return this.xp7;
   }

   public int getXp8() {
      return this.xp8;
   }

   public int getXp9() {
      return this.xp9;
   }

   public int getXp10() {
      return this.xp10;
   }

   public float getXpForLevel(int var1) {
      if (var1 == 1) {
         return this.xp1;
      } else if (var1 == 2) {
         return this.xp2;
      } else if (var1 == 3) {
         return this.xp3;
      } else if (var1 == 4) {
         return this.xp4;
      } else if (var1 == 5) {
         return this.xp5;
      } else if (var1 == 6) {
         return this.xp6;
      } else if (var1 == 7) {
         return this.xp7;
      } else if (var1 == 8) {
         return this.xp8;
      } else if (var1 == 9) {
         return this.xp9;
      } else {
         return var1 == 10 ? this.xp10 : -1.0F;
      }
   }

   public float getTotalXpForLevel(int var1) {
      int var2 = 0;

      for (int var3 = 1; var3 <= var1; var3++) {
         float var4 = this.getXpForLevel(var3);
         if (var4 != -1.0F) {
            var2 = (int)(var2 + var4);
         }
      }

      return var2;
   }

   @Override
   public String toString() {
      return this.id;
   }
}
