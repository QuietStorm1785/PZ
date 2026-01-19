package zombie.popman;

import java.util.ArrayList;

class ObjectPool$1 extends ArrayList<T> {
   ObjectPool$1(ObjectPool var1) {
      this.this$0 = var1;
   }

   @Override
   public boolean contains(Object var1) {
      for (int var2 = 0; var2 < this.this$0.pool.size(); var2++) {
         if (this.this$0.pool.get(var2) == var1) {
            return true;
         }
      }

      return false;
   }
}
