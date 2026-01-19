package zombie.core.Collections;

import java.util.Iterator;
import java.util.Map.Entry;
import zombie.core.Collections.ZomboidAbstractMap.1;

class ZomboidAbstractMap$1$1 implements Iterator<K> {
   private Iterator<Entry<K, V>> i;

   ZomboidAbstractMap$1$1(1 var1) {
      this.this$1 = var1;
      this.i = this.this$1.this$0.entrySet().iterator();
   }

   @Override
   public boolean hasNext() {
      return this.i.hasNext();
   }

   @Override
   public K next() {
      return (K)((Entry)this.i.next()).getKey();
   }

   @Override
   public void remove() {
      this.i.remove();
   }
}
