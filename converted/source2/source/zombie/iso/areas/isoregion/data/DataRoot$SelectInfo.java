package zombie.iso.areas.isoregion.data;

import zombie.iso.areas.isoregion.IsoRegions;

public final class DataRoot$SelectInfo {
   public int x;
   public int y;
   public int z;
   public int chunkSquareX;
   public int chunkSquareY;
   public int chunkx;
   public int chunky;
   public int cellx;
   public int celly;
   public int chunkID;
   public int cellID;
   public DataCell cell;
   public DataChunk chunk;
   public byte square;
   private final DataRoot root;

   private DataRoot$SelectInfo(DataRoot var1) {
      this.root = var1;
   }

   public void reset(int var1, int var2, int var3, boolean var4) {
      this.reset(var1, var2, var3, var4, var4);
   }

   public void reset(int var1, int var2, int var3, boolean var4, boolean var5) {
      this.x = var1;
      this.y = var2;
      this.z = var3;
      this.chunkSquareX = var1 % 10;
      this.chunkSquareY = var2 % 10;
      this.chunkx = var1 / 10;
      this.chunky = var2 / 10;
      this.cellx = var1 / 300;
      this.celly = var2 / 300;
      this.chunkID = IsoRegions.hash(this.chunkx, this.chunky);
      this.cellID = IsoRegions.hash(this.cellx, this.celly);
      this.cell = null;
      this.chunk = null;
      this.square = -1;
      this.ensureSquare(var5);
      if (this.chunk == null && var4) {
         this.ensureChunk(var4);
      }
   }

   private void ensureCell(boolean var1) {
      if (this.cell == null) {
         this.cell = this.root.getCell(this.cellID);
      }

      if (this.cell == null && var1) {
         this.cell = this.root.addCell(this.cellx, this.celly, this.cellID);
      }
   }

   private void ensureChunk(boolean var1) {
      this.ensureCell(var1);
      if (this.cell != null) {
         if (this.chunk == null) {
            this.chunk = this.cell.getChunk(this.chunkID);
         }

         if (this.chunk == null && var1) {
            this.chunk = this.cell.addChunk(this.chunkx, this.chunky, this.chunkID);
         }
      }
   }

   private void ensureSquare(boolean var1) {
      this.ensureCell(var1);
      if (this.cell != null) {
         this.ensureChunk(var1);
         if (this.chunk != null) {
            if (this.square == -1) {
               this.square = this.chunk.getSquare(this.chunkSquareX, this.chunkSquareY, this.z, true);
            }

            if (this.square == -1 && var1) {
               this.square = this.chunk.setOrAddSquare(this.chunkSquareX, this.chunkSquareY, this.z, (byte)0, true);
            }
         }
      }
   }
}
