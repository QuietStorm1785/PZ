package zombie.scripting.objects;

import java.util.LinkedList;
import zombie.scripting.objects.Fixing.FixerSkill;

public final class Fixing$Fixer {
   private String fixerName = null;
   private LinkedList<FixerSkill> skills = null;
   private int numberOfUse = 1;

   public Fixing$Fixer(String var1, LinkedList<FixerSkill> var2, int var3) {
      this.fixerName = var1;
      this.skills = var2;
      this.numberOfUse = var3;
   }

   public String getFixerName() {
      return this.fixerName;
   }

   public LinkedList<FixerSkill> getFixerSkills() {
      return this.skills;
   }

   public int getNumberOfUse() {
      return this.numberOfUse;
   }
}
