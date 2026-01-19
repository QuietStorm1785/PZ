package zombie.iso;

import java.util.Comparator;
import zombie.characters.IsoPlayer;
import zombie.characters.IsoZombie;

class IsoWorld$CompScoreToPlayer implements Comparator<IsoZombie> {
   private IsoWorld$CompScoreToPlayer() {
   }

   public int compare(IsoZombie var1, IsoZombie var2) {
      float var3 = this.getScore(var1);
      float var4 = this.getScore(var2);
      if (var3 < var4) {
         return 1;
      } else {
         return var3 > var4 ? -1 : 0;
      }
   }

   public float getScore(IsoZombie var1) {
      float var2 = Float.MIN_VALUE;

      for (int var3 = 0; var3 < 4; var3++) {
         IsoPlayer var4 = IsoPlayer.players[var3];
         if (var4 != null && var4.current != null) {
            float var5 = var4.getZombieRelevenceScore(var1);
            var2 = Math.max(var2, var5);
         }
      }

      return var2;
   }
}
