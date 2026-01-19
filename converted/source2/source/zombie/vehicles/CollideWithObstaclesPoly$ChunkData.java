package zombie.vehicles;

import java.util.Arrays;
import zombie.GameWindow;
import zombie.iso.IsoChunk;
import zombie.util.list.PZArrayUtil;
import zombie.vehicles.CollideWithObstaclesPoly.ChunkDataZ;

public final class CollideWithObstaclesPoly$ChunkData {
   final ChunkDataZ[] data = new ChunkDataZ[8];
   private boolean bClear = false;

   public ChunkDataZ init(IsoChunk var1, int var2, CollideWithObstaclesPoly var3) {
      if (!$assertionsDisabled && Thread.currentThread() != GameWindow.GameThread) {
         throw new AssertionError();
      } else {
         if (this.bClear) {
            this.bClear = false;
            this.clearInner();
         }

         if (this.data[var2] == null) {
            this.data[var2] = (ChunkDataZ)ChunkDataZ.pool.alloc();
            this.data[var2].init(var1, var2, var3);
         }

         return this.data[var2];
      }
   }

   private void clearInner() {
      PZArrayUtil.forEach(this.data, var0 -> {
         if (var0 != null) {
            var0.clear();
            ChunkDataZ.pool.release(var0);
         }
      });
      Arrays.fill(this.data, null);
   }

   public void clear() {
      this.bClear = true;
   }
}
