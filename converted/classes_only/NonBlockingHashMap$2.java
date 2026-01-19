package zombie.core.Collections;

import java.util.AbstractSet;
import java.util.Iterator;
import zombie.core.Collections.NonBlockingHashMap.SnapshotK;

class NonBlockingHashMap$2 extends AbstractSet<TypeK> {
   NonBlockingHashMap$2(NonBlockingHashMap var1) {
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

   @Override
   public Iterator<TypeK> iterator() {
      return new SnapshotK(this.this$0);
   }
}
