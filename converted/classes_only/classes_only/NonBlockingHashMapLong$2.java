package zombie.core.Collections;

import java.util.AbstractSet;
import zombie.core.Collections.NonBlockingHashMapLong.IteratorLong;

class NonBlockingHashMapLong$2 extends AbstractSet<Long> {
   NonBlockingHashMapLong$2(NonBlockingHashMapLong var1) {
      this.this$0 = var1;
   }

   @Override
   public void clear() {
      this.this$0.clear();
   }

   @Override
   public int size() {
      return this.this$0.size();
   }

   @Override
   public boolean contains(Object var1) {
      return this.this$0.containsKey(var1);
   }

   @Override
   public boolean remove(Object var1) {
      return this.this$0.remove(var1) != null;
   }

   public NonBlockingHashMapLong<TypeV>.IteratorLong iterator() {
      return new IteratorLong(this.this$0);
   }
}
