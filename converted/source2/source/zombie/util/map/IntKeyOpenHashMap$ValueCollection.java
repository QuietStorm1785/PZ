package zombie.util.map;

import java.util.AbstractCollection;
import java.util.Iterator;
import zombie.util.map.IntKeyOpenHashMap.ValueCollection.1;

class IntKeyOpenHashMap$ValueCollection extends AbstractCollection<V> {
   private IntKeyOpenHashMap$ValueCollection(IntKeyOpenHashMap var1) {
      this.this$0 = var1;
   }

   @Override
   public void clear() {
      this.this$0.clear();
   }

   @Override
   public boolean contains(Object var1) {
      return this.this$0.containsValue(var1);
   }

   @Override
   public Iterator<V> iterator() {
      return new 1(this);
   }

   @Override
   public int size() {
      return this.this$0.size;
   }
}
