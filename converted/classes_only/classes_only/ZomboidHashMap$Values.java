package zombie.core.Collections;

import java.util.AbstractCollection;
import java.util.Iterator;

final class ZomboidHashMap$Values extends AbstractCollection<V> {
   private ZomboidHashMap$Values(ZomboidHashMap var1) {
      this.this$0 = var1;
   }

   @Override
   public Iterator<V> iterator() {
      return this.this$0.newValueIterator();
   }

   @Override
   public int size() {
      return this.this$0.size;
   }

   @Override
   public boolean contains(Object var1) {
      return this.this$0.containsValue(var1);
   }

   @Override
   public void clear() {
      this.this$0.clear();
   }
}
