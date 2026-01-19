package zombie.core.Collections;

import java.util.AbstractCollection;
import java.util.Iterator;
import zombie.core.Collections.ZomboidAbstractMap.2.1;

class ZomboidAbstractMap$2 extends AbstractCollection<V> {
   ZomboidAbstractMap$2(ZomboidAbstractMap var1) {
      this.this$0 = var1;
   }

   @Override
   public Iterator<V> iterator() {
      return new 1(this);
   }

   @Override
   public int size() {
      return this.this$0.size();
   }

   @Override
   public boolean contains(Object var1) {
      return this.this$0.containsValue(var1);
   }
}
