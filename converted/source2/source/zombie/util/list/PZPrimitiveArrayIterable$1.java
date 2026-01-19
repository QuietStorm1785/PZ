package zombie.util.list;

import java.util.Iterator;
import zombie.util.list.PZPrimitiveArrayIterable.1.1;

class PZPrimitiveArrayIterable$1 implements Iterable<Float> {
   private final float[] m_list;

   PZPrimitiveArrayIterable$1(float[] var1) {
      this.val$list = var1;
      this.m_list = this.val$list;
   }

   @Override
   public Iterator<Float> iterator() {
      return new 1(this);
   }
}
