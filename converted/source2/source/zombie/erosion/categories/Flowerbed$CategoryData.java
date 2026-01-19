package zombie.erosion.categories;

import java.nio.ByteBuffer;
import zombie.erosion.categories.ErosionCategory.Data;

final class Flowerbed$CategoryData extends Data {
   public int gameObj;

   private Flowerbed$CategoryData() {
   }

   public void save(ByteBuffer var1) {
      super.save(var1);
      var1.put((byte)this.gameObj);
   }

   public void load(ByteBuffer var1, int var2) {
      super.load(var1, var2);
      this.gameObj = var1.get();
   }
}
