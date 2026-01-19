package zombie.core.Collections;

import java.util.AbstractSet;
import java.util.Iterator;
import java.util.Map.Entry;

final class ZomboidHashMap$EntrySet extends AbstractSet<Entry<K, V>> {
   private ZomboidHashMap$EntrySet(ZomboidHashMap var1) {
      this.this$0 = var1;
   }

   @Override
   public Iterator<Entry<K, V>> iterator() {
      return this.this$0.newEntryIterator();
   }

   @Override
   public boolean contains(Object var1) {
      if (!(var1 instanceof Entry var2)) {
         return false;
      } else {
         zombie.core.Collections.ZomboidHashMap.Entry var3 = this.this$0.getEntry(var2.getKey());
         return var3 != null && var3.equals(var2);
      }
   }

   @Override
   public boolean remove(Object var1) {
      return this.this$0.removeMapping(var1) != null;
   }

   @Override
   public int size() {
      return this.this$0.size;
   }

   @Override
   public void clear() {
      this.this$0.clear();
   }
}
