package zombie.core.Collections;

import java.util.Map.Entry;

final class ZomboidHashMap$EntryIterator extends ZomboidHashMap<K, V>.HashIterator<Entry<K, V>> {
   private ZomboidHashMap$EntryIterator(ZomboidHashMap var1) {
      super(var1);
      this.this$0 = var1;
   }

   public Entry<K, V> next() {
      return this.nextEntry();
   }
}
