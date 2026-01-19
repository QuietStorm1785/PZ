package zombie.globalObjects;

import zombie.globalObjects.GlobalObjectLookup.Cell;
import zombie.iso.IsoMetaGrid;

final class GlobalObjectLookup$Shared {
   Cell[] cells;

   private GlobalObjectLookup$Shared() {
   }

   void init(IsoMetaGrid var1) {
      this.cells = new Cell[var1.getWidth() * var1.getHeight()];
   }

   void reset() {
      if (this.cells != null) {
         for (int var1 = 0; var1 < this.cells.length; var1++) {
            Cell var2 = this.cells[var1];
            if (var2 != null) {
               var2.Reset();
            }
         }

         this.cells = null;
      }
   }
}
