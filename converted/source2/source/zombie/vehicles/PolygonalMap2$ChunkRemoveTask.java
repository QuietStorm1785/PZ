package zombie.vehicles;

import java.util.ArrayDeque;
import zombie.iso.IsoChunk;
import zombie.vehicles.PolygonalMap2.Cell;
import zombie.vehicles.PolygonalMap2.IChunkTask;

final class PolygonalMap2$ChunkRemoveTask implements IChunkTask {
   PolygonalMap2 map;
   int wx;
   int wy;
   static final ArrayDeque<PolygonalMap2$ChunkRemoveTask> pool = new ArrayDeque<>();

   private PolygonalMap2$ChunkRemoveTask() {
   }

   PolygonalMap2$ChunkRemoveTask init(PolygonalMap2 var1, IsoChunk var2) {
      this.map = var1;
      this.wx = var2.wx;
      this.wy = var2.wy;
      return this;
   }

   public void execute() {
      Cell var1 = this.map.getCellFromChunkPos(this.wx, this.wy);
      var1.removeChunk(this.wx, this.wy);
   }

   static PolygonalMap2$ChunkRemoveTask alloc() {
      synchronized (pool) {
         return pool.isEmpty() ? new PolygonalMap2$ChunkRemoveTask() : pool.pop();
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
