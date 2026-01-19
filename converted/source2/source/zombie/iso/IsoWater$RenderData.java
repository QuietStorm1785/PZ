package zombie.iso;

import java.util.Arrays;

final class IsoWater$RenderData {
   int numSquares;
   int capacity = 512;
   float[] data;

   private IsoWater$RenderData() {
   }

   void clear() {
      this.numSquares = 0;
   }

   void addSquare(IsoWaterGeometry var1) {
      int var2 = IsoCamera.frameState.playerIndex;
      byte var3 = 4;
      if (this.data == null) {
         this.data = new float[this.capacity * var3 * 7];
      }

      if (this.numSquares + 1 > this.capacity) {
         this.capacity += 128;
         this.data = Arrays.copyOf(this.data, this.capacity * var3 * 7);
      }

      int var4 = this.numSquares * var3 * 7;

      for (int var5 = 0; var5 < 4; var5++) {
         this.data[var4++] = var1.depth[var5];
         this.data[var4++] = var1.flow[var5];
         this.data[var4++] = var1.speed[var5];
         this.data[var4++] = var1.IsExternal;
         this.data[var4++] = var1.x[var5];
         this.data[var4++] = var1.y[var5];
         if (var1.square != null) {
            int var6 = var1.square.getVertLight((4 - var5) % 4, var2);
            this.data[var4++] = Float.intBitsToFloat(var6);
         } else {
            var4++;
         }
      }

      this.numSquares++;
   }
}
