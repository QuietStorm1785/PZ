package zombie.characters;

import java.util.Comparator;
import zombie.iso.IsoUtils;

class IsoPlayer$1 implements Comparator<IsoGameCharacter> {
   IsoPlayer$1(IsoPlayer var1) {
      this.this$0 = var1;
   }

   public int compare(IsoGameCharacter var1, IsoGameCharacter var2) {
      float var3 = IsoUtils.DistanceTo(var1.x, var1.y, IsoPlayer.testHitPosition.x, IsoPlayer.testHitPosition.y);
      float var4 = IsoUtils.DistanceTo(var2.x, var2.y, IsoPlayer.testHitPosition.x, IsoPlayer.testHitPosition.y);
      if (var3 > var4) {
         return 1;
      } else {
         return var4 > var3 ? -1 : 0;
      }
   }
}
