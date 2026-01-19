package zombie.characters;

import java.util.Comparator;

class BaseZombieSoundManager$1 implements Comparator<IsoZombie> {
   BaseZombieSoundManager$1(BaseZombieSoundManager var1) {
      this.this$0 = var1;
   }

   public int compare(IsoZombie var1, IsoZombie var2) {
      float var3 = this.this$0.getClosestListener(var1.x, var1.y, var1.z);
      float var4 = this.this$0.getClosestListener(var2.x, var2.y, var2.z);
      if (var3 > var4) {
         return 1;
      } else {
         return var3 < var4 ? -1 : 0;
      }
   }
}
