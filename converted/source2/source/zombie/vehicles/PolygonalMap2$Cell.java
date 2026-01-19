package zombie.vehicles;

import java.util.ArrayDeque;
import zombie.vehicles.PolygonalMap2.Chunk;

final class PolygonalMap2$Cell {
   PolygonalMap2 map;
   public short cx;
   public short cy;
   public Chunk[][] chunks;
   static final ArrayDeque<PolygonalMap2$Cell> pool = new ArrayDeque<>();

   private PolygonalMap2$Cell() {
   }

   PolygonalMap2$Cell init(PolygonalMap2 var1, int var2, int var3) {
      this.map = var1;
      this.cx = (short)var2;
      this.cy = (short)var3;
      return this;
   }

   Chunk getChunkFromChunkPos(int var1, int var2) {
      if (this.chunks == null) {
         return null;
      } else {
         var1 -= this.cx * 30;
         var2 -= this.cy * 30;
         return var1 >= 0 && var1 < 30 && var2 >= 0 && var2 < 30 ? this.chunks[var1][var2] : null;
      }
   }

   Chunk allocChunkIfNeeded(int var1, int var2) {
      var1 -= this.cx * 30;
      var2 -= this.cy * 30;
      if (var1 >= 0 && var1 < 30 && var2 >= 0 && var2 < 30) {
         if (this.chunks == null) {
            this.chunks = new Chunk[30][30];
         }

         if (this.chunks[var1][var2] == null) {
            this.chunks[var1][var2] = Chunk.alloc();
         }

         this.chunks[var1][var2].init(this.cx * 30 + var1, this.cy * 30 + var2);
         return this.chunks[var1][var2];
      } else {
         return null;
      }
   }

   void removeChunk(int var1, int var2) {
      if (this.chunks != null) {
         var1 -= this.cx * 30;
         var2 -= this.cy * 30;
         if (var1 >= 0 && var1 < 30 && var2 >= 0 && var2 < 30) {
            Chunk var3 = this.chunks[var1][var2];
            if (var3 != null) {
               var3.release();
               this.chunks[var1][var2] = null;
            }
         }
      }
   }

   static PolygonalMap2$Cell alloc() {
      return pool.isEmpty() ? new PolygonalMap2$Cell() : pool.pop();
   }

   void release() {
      if (!$assertionsDisabled && pool.contains(this)) {
         throw new AssertionError();
      } else {
         pool.push(this);
      }
   }
}
