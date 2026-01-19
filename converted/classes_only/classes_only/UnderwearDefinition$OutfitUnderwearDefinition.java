package zombie.characters;

import java.util.ArrayList;
import zombie.characters.UnderwearDefinition.StringChance;

public final class UnderwearDefinition$OutfitUnderwearDefinition {
   public ArrayList<StringChance> top;
   public int topTotalChance = 0;
   public String bottom;
   public int chanceToSpawn;
   public boolean female = false;

   public UnderwearDefinition$OutfitUnderwearDefinition(ArrayList<StringChance> var1, String var2, int var3, String var4) {
      this.top = var1;
      if (var1 != null) {
         for (int var5 = 0; var5 < var1.size(); var5++) {
            this.topTotalChance = (int)(this.topTotalChance + ((StringChance)var1.get(var5)).chance);
         }
      }

      this.bottom = var2;
      this.chanceToSpawn = var3;
      if ("female".equals(var4)) {
         this.female = true;
      }
   }
}
