package zombie.erosion.categories;

import java.nio.ByteBuffer;
import zombie.erosion.categories.ErosionCategory.Data;

final class NatureGeneric$CategoryData extends Data {
   public int gameObj;
   public int maxStage;
   public int spawnTime;
   public boolean notGrass;

   private NatureGeneric$CategoryData() {
   }

   public void save(ByteBuffer var1) {
      super.save(var1);
      var1.put((byte)this.gameObj);
      var1.put((byte)this.maxStage);
      var1.putShort((short)this.spawnTime);
      var1.put((byte)(this.notGrass ? 1 : 0));
   }

   public void load(ByteBuffer var1, int var2) {
      super.load(var1, var2);
      this.gameObj = var1.get();
      this.maxStage = var1.get();
      this.spawnTime = var1.getShort();
      this.notGrass = var1.get() == 1;
   }
}
