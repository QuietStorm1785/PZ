package zombie.iso.objects;

import java.util.Comparator;
import zombie.iso.objects.IsoFireManager.FireSounds;

class IsoFireManager$FireSounds$1 implements Comparator<IsoFire> {
   IsoFireManager$FireSounds$1(FireSounds var1) {
      this.this$0 = var1;
   }

   public int compare(IsoFire var1, IsoFire var2) {
      float var3 = this.this$0.getClosestListener(var1.square.x + 0.5F, var1.square.y + 0.5F, var1.square.z);
      float var4 = this.this$0.getClosestListener(var2.square.x + 0.5F, var2.square.y + 0.5F, var2.square.z);
      if (var3 > var4) {
         return 1;
      } else {
         return var3 < var4 ? -1 : 0;
      }
   }
}
