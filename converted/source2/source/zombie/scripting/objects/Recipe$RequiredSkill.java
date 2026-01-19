package zombie.scripting.objects;

import zombie.characters.skills.PerkFactory.Perk;

public final class Recipe$RequiredSkill {
   private final Perk perk;
   private final int level;

   public Recipe$RequiredSkill(Perk var1, int var2) {
      this.perk = var1;
      this.level = var2;
   }

   public Perk getPerk() {
      return this.perk;
   }

   public int getLevel() {
      return this.level;
   }
}
