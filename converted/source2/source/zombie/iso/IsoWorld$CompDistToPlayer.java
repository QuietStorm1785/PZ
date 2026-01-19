package zombie.iso;

import java.util.Comparator;
import zombie.characters.IsoZombie;

class IsoWorld$CompDistToPlayer implements Comparator<IsoZombie> {
   public float px;
   public float py;

   private IsoWorld$CompDistToPlayer() {
   }

   public int compare(IsoZombie var1, IsoZombie var2) {
      float var3 = IsoUtils.DistanceManhatten((int)var1.x, (int)var1.y, this.px, this.py);
      float var4 = IsoUtils.DistanceManhatten((int)var2.x, (int)var2.y, this.px, this.py);
      if (var3 < var4) {
         return -1;
      } else {
         return var3 > var4 ? 1 : 0;
      }
   }
}
