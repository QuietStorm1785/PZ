package zombie.core.Collections;

import java.util.Iterator;
import java.util.Map.Entry;
import zombie.core.Collections.ZomboidAbstractMap.2;

class ZomboidAbstractMap$2$1 implements Iterator<V> {
   private Iterator<Entry<K, V>> i;

   ZomboidAbstractMap$2$1(2 var1) {
      this.this$1 = var1;
      this.i = this.this$1.this$0.entrySet().iterator();
   }

   @Override
   public boolean hasNext() {
      return this.i.hasNext();
   }

   @Override
   public V next() {
      return (V)((Entry)this.i.next()).getValue();
   }

   @Override
   public void remove() {
      this.i.remove();
   }
}
