package zombie.erosion;

import java.nio.ByteBuffer;
import zombie.iso.IsoChunk;

public class ErosionData$Chunk {
   public boolean init = false;
   public int eTickStamp = -1;
   public int epoch = -1;
   public int x;
   public int y;
   public float moisture;
   public float minerals;
   public int soil;

   public void set(IsoChunk var1) {
      this.x = var1.wx;
      this.y = var1.wy;
   }

   public void save(ByteBuffer var1) {
      if (this.init) {
         var1.put((byte)1);
         var1.putInt(this.eTickStamp);
         var1.putInt(this.epoch);
         var1.putFloat(this.moisture);
         var1.putFloat(this.minerals);
         var1.put((byte)this.soil);
      } else {
         var1.put((byte)0);
      }
   }

   public void load(ByteBuffer var1, int var2) {
      this.init = var1.get() == 1;
      if (this.init) {
         this.eTickStamp = var1.getInt();
         this.epoch = var1.getInt();
         this.moisture = var1.getFloat();
         this.minerals = var1.getFloat();
         this.soil = var1.get();
      }
   }
}
