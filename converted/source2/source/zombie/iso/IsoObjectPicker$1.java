package zombie.iso;

import java.util.Comparator;
import zombie.iso.IsoObjectPicker.ClickObject;

class IsoObjectPicker$1 implements Comparator<ClickObject> {
   public int compare(ClickObject var1, ClickObject var2) {
      int var3 = var1.getScore();
      int var4 = var2.getScore();
      if (var3 > var4) {
         return 1;
      } else if (var3 < var4) {
         return -1;
      } else {
         return var1.tile != null && var1.tile.square != null && var2.tile != null && var1.tile.square == var2.tile.square
            ? var1.tile.getObjectIndex() - var2.tile.getObjectIndex()
            : 0;
      }
   }
}
