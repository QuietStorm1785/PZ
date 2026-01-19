package zombie.core.Collections;

import java.util.AbstractSet;
import java.util.Iterator;
import zombie.core.Collections.ZomboidAbstractMap.1.1;

class ZomboidAbstractMap$1 extends AbstractSet<K> {
   ZomboidAbstractMap$1(ZomboidAbstractMap var1) {
      this.this$0 = var1;
   }

   @Override
   public Iterator<K> iterator() {
      return new 1(this);
   }

   @Override
   public int size() {
      return this.this$0.size();
   }

   @Override
   public boolean contains(Object var1) {
      return this.this$0.containsKey(var1);
   }
}
