package zombie.vehicles;

import java.util.ArrayDeque;
import zombie.vehicles.PolygonalMap2.ChunkData;
import zombie.vehicles.PolygonalMap2.ChunkDataZ;
import zombie.vehicles.PolygonalMap2.ChunkUpdateTask;
import zombie.vehicles.PolygonalMap2.Square;
import zombie.vehicles.PolygonalMap2.SquareUpdateTask;

final class PolygonalMap2$Chunk {
   short wx;
   short wy;
   Square[][][] squares = new Square[10][10][8];
   final ChunkData collision = new ChunkData();
   static final ArrayDeque<PolygonalMap2$Chunk> pool = new ArrayDeque<>();

   private PolygonalMap2$Chunk() {
   }

   void init(int var1, int var2) {
      this.wx = (short)var1;
      this.wy = (short)var2;
   }

   Square getSquare(int var1, int var2, int var3) {
      var1 -= this.wx * 10;
      var2 -= this.wy * 10;
      return var1 >= 0 && var1 < 10 && var2 >= 0 && var2 < 10 && var3 >= 0 && var3 < 8 ? this.squares[var1][var2][var3] : null;
   }

   void setData(ChunkUpdateTask var1) {
      for (int var2 = 0; var2 < 8; var2++) {
         for (int var3 = 0; var3 < 10; var3++) {
            for (int var4 = 0; var4 < 10; var4++) {
               Square var5 = this.squares[var4][var3][var2];
               int var6 = var1.data[var4][var3][var2];
               if (var6 == 0) {
                  if (var5 != null) {
                     var5.release();
                     this.squares[var4][var3][var2] = null;
                  }
               } else {
                  if (var5 == null) {
                     var5 = Square.alloc();
                     this.squares[var4][var3][var2] = var5;
                  }

                  var5.init(this.wx * 10 + var4, this.wy * 10 + var3, var2);
                  var5.bits = var6;
                  var5.cost = var1.cost[var4][var3][var2];
               }
            }
         }
      }

      ChunkDataZ.EPOCH++;
   }

   boolean setData(SquareUpdateTask var1) {
      int var2 = var1.x - this.wx * 10;
      int var3 = var1.y - this.wy * 10;
      if (var2 < 0 || var2 >= 10) {
         return false;
      } else if (var3 >= 0 && var3 < 10) {
         Square var4 = this.squares[var2][var3][var1.z];
         if (var1.bits == 0) {
            if (var4 != null) {
               var4.release();
               this.squares[var2][var3][var1.z] = null;
               return true;
            }
         } else {
            if (var4 == null) {
               var4 = Square.alloc().init(var1.x, var1.y, var1.z);
               this.squares[var2][var3][var1.z] = var4;
            }

            if (var4.bits != var1.bits || var4.cost != var1.cost) {
               var4.bits = var1.bits;
               var4.cost = var1.cost;
               return true;
            }
         }

         return false;
      } else {
         return false;
      }
   }

   static PolygonalMap2$Chunk alloc() {
      return pool.isEmpty() ? new PolygonalMap2$Chunk() : pool.pop();
   }

   void release() {
      if (!$assertionsDisabled && pool.contains(this)) {
         throw new AssertionError();
      } else {
         pool.push(this);
      }
   }
}
