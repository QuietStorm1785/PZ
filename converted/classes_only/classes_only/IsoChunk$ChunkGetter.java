package zombie.iso;

import zombie.iso.IsoGridSquare.GetSquare;

class IsoChunk$ChunkGetter implements GetSquare {
   IsoChunk chunk;

   private IsoChunk$ChunkGetter() {
   }

   public IsoGridSquare getGridSquare(int var1, int var2, int var3) {
      var1 -= this.chunk.wx * 10;
      var2 -= this.chunk.wy * 10;
      return var1 >= 0 && var1 < 10 && var2 >= 0 && var2 < 10 && var3 >= 0 && var3 < 8 ? this.chunk.getGridSquare(var1, var2, var3) : null;
   }
}
