package zombie.core.Collections;

import java.util.AbstractSet;
import java.util.Iterator;

final class ZomboidHashMap$KeySet extends AbstractSet<K> {
   private ZomboidHashMap$KeySet(ZomboidHashMap var1) {
      this.this$0 = var1;
   }

   @Override
   public Iterator<K> iterator() {
      return this.this$0.newKeyIterator();
   }

   @Override
   public int size() {
      return this.this$0.size;
   }

   @Override
   public boolean contains(Object var1) {
      return this.this$0.containsKey(var1);
   }

   @Override
   public boolean remove(Object var1) {
      return this.this$0.removeEntryForKey(var1) != null;
   }

   @Override
   public void clear() {
      this.this$0.clear();
   }
}
