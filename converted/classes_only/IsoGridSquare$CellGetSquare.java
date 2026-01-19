package zombie.iso;

import zombie.iso.IsoGridSquare.GetSquare;

public class IsoGridSquare$CellGetSquare implements GetSquare {
   public IsoGridSquare getGridSquare(int var1, int var2, int var3) {
      return IsoWorld.instance.CurrentCell.getGridSquare(var1, var2, var3);
   }
}
