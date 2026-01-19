package zombie.util.list;

import java.util.Iterator;
import zombie.util.list.PZPrimitiveArrayIterable.1;

class PZPrimitiveArrayIterable$1$1 implements Iterator<Float> {
   private int pos;

   PZPrimitiveArrayIterable$1$1(1 var1) {
      this.this$0 = var1;
      this.pos = 0;
   }

   @Override
   public boolean hasNext() {
      return this.this$0.m_list.length > this.pos;
   }

   public Float next() {
      return this.this$0.m_list[this.pos++];
   }
}
