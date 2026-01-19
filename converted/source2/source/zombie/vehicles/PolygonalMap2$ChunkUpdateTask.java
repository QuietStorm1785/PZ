package zombie.vehicles;

import java.util.ArrayDeque;
import zombie.iso.IsoChunk;
import zombie.iso.IsoGridSquare;
import zombie.vehicles.PolygonalMap2.Chunk;
import zombie.vehicles.PolygonalMap2.IChunkTask;
import zombie.vehicles.PolygonalMap2.SquareUpdateTask;

final class PolygonalMap2$ChunkUpdateTask implements IChunkTask {
   PolygonalMap2 map;
   int wx;
   int wy;
   final int[][][] data = new int[10][10][8];
   final short[][][] cost = new short[10][10][8];
   static final ArrayDeque<PolygonalMap2$ChunkUpdateTask> pool = new ArrayDeque<>();

   private PolygonalMap2$ChunkUpdateTask() {
   }

   PolygonalMap2$ChunkUpdateTask init(PolygonalMap2 var1, IsoChunk var2) {
      this.map = var1;
      this.wx = var2.wx;
      this.wy = var2.wy;

      for (int var3 = 0; var3 < 8; var3++) {
         for (int var4 = 0; var4 < 10; var4++) {
            for (int var5 = 0; var5 < 10; var5++) {
               IsoGridSquare var6 = var2.getGridSquare(var5, var4, var3);
               if (var6 == null) {
                  this.data[var5][var4][var3] = 0;
                  this.cost[var5][var4][var3] = 0;
               } else {
                  this.data[var5][var4][var3] = SquareUpdateTask.getBits(var6);
                  this.cost[var5][var4][var3] = SquareUpdateTask.getCost(var6);
               }
            }
         }
      }

      return this;
   }

   public void execute() {
      Chunk var1 = this.map.allocChunkIfNeeded(this.wx, this.wy);
      var1.setData(this);
   }

   static PolygonalMap2$ChunkUpdateTask alloc() {
      synchronized (pool) {
         return pool.isEmpty() ? new PolygonalMap2$ChunkUpdateTask() : pool.pop();
      }
   }

   public void release() {
      synchronized (pool) {
         if (!$assertionsDisabled && pool.contains(this)) {
            throw new AssertionError();
         } else {
            pool.push(this);
         }
      }
   }
}
