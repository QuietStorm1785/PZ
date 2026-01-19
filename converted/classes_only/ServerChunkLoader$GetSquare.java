package zombie.network;

import zombie.iso.IsoChunk;
import zombie.iso.IsoGridSquare;
import zombie.iso.IsoWorld;
import zombie.iso.IsoGridSquare.GetSquare;
import zombie.network.ServerMap.ServerCell;

class ServerChunkLoader$GetSquare implements GetSquare {
   ServerCell cell;

   private ServerChunkLoader$GetSquare(ServerChunkLoader var1) {
      this.this$0 = var1;
   }

   public IsoGridSquare getGridSquare(int var1, int var2, int var3) {
      var1 -= this.cell.WX * 50;
      var2 -= this.cell.WY * 50;
      if (var1 < 0 || var1 >= 50) {
         return null;
      } else if (var2 >= 0 && var2 < 50) {
         IsoChunk var4 = this.cell.chunks[var1 / 10][var2 / 10];
         return var4 == null ? null : var4.getGridSquare(var1 % 10, var2 % 10, var3);
      } else {
         return null;
      }
   }

   public boolean contains(int var1, int var2, int var3) {
      return var1 < 0 || var1 >= 50 ? false : var2 >= 0 && var2 < 50;
   }

   public IsoChunk getChunkForSquare(int var1, int var2) {
      var1 -= this.cell.WX * 50;
      var2 -= this.cell.WY * 50;
      if (var1 < 0 || var1 >= 50) {
         return null;
      } else {
         return var2 >= 0 && var2 < 50 ? this.cell.chunks[var1 / 10][var2 / 10] : null;
      }
   }

   public void EnsureSurroundNotNull(int var1, int var2, int var3) {
      int var4 = this.cell.WX * 50;
      int var5 = this.cell.WY * 50;

      for (int var6 = -1; var6 <= 1; var6++) {
         for (int var7 = -1; var7 <= 1; var7++) {
            if ((var6 != 0 || var7 != 0) && this.contains(var1 + var6, var2 + var7, var3)) {
               IsoGridSquare var8 = this.getGridSquare(var4 + var1 + var6, var5 + var2 + var7, var3);
               if (var8 == null) {
                  var8 = IsoGridSquare.getNew(IsoWorld.instance.CurrentCell, null, var4 + var1 + var6, var5 + var2 + var7, var3);
                  int var9 = (var1 + var6) / 10;
                  int var10 = (var2 + var7) / 10;
                  int var11 = (var1 + var6) % 10;
                  int var12 = (var2 + var7) % 10;
                  if (this.cell.chunks[var9][var10] != null) {
                     this.cell.chunks[var9][var10].setSquare(var11, var12, var3, var8);
                  }
               }
            }
         }
      }
   }
}
