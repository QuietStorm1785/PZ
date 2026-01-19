package zombie;

import zombie.FliesSound.ChunkLevelData;
import zombie.iso.IsoGridSquare;
import zombie.iso.IsoWorld;
import zombie.iso.areas.IsoBuilding;

public class FliesSound$ChunkData {
   private int wx;
   private int wy;
   private final ChunkLevelData[] levelData;

   private FliesSound$ChunkData(FliesSound var1, int var2, int var3) {
      this.this$0 = var1;
      this.levelData = new ChunkLevelData[8];
      this.wx = var2;
      this.wy = var3;

      for (int var4 = 0; var4 < this.levelData.length; var4++) {
         this.levelData[var4] = new ChunkLevelData(var1);
      }
   }

   private void corpseAdded(int var1, int var2, int var3) {
      IsoGridSquare var4 = IsoWorld.instance.CurrentCell.getGridSquare(var1, var2, var3);
      IsoBuilding var5 = var4 == null ? null : var4.getBuilding();
      int var6 = var1 - this.wx * 10;
      int var7 = var2 - this.wy * 10;
      this.levelData[var3].corpseAdded(var6, var7, var5);
   }

   private void corpseRemoved(int var1, int var2, int var3) {
      IsoGridSquare var4 = IsoWorld.instance.CurrentCell.getGridSquare(var1, var2, var3);
      IsoBuilding var5 = var4 == null ? null : var4.getBuilding();
      int var6 = var1 - this.wx * 10;
      int var7 = var2 - this.wy * 10;
      this.levelData[var3].corpseRemoved(var6, var7, var5);
   }

   private void Reset() {
      for (int var1 = 0; var1 < this.levelData.length; var1++) {
         this.levelData[var1].Reset();
      }
   }
}
