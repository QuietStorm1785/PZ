package zombie.core.Collections;

import java.util.AbstractSet;
import java.util.Iterator;
import java.util.Map.Entry;
import zombie.core.Collections.NonBlockingIdentityHashMap.SnapshotE;

class NonBlockingIdentityHashMap$3 extends AbstractSet<Entry<TypeK, TypeV>> {
   NonBlockingIdentityHashMap$3(NonBlockingIdentityHashMap var1) {
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
   public boolean remove(Object var1) {
      return !(var1 instanceof Entry var2) ? false : this.this$0.remove(var2.getKey(), var2.getValue());
   }

   @Override
   public boolean contains(Object var1) {
      if (!(var1 instanceof Entry var2)) {
         return false;
      } else {
         Object var3 = this.this$0.get(var2.getKey());
         return var3.equals(var2.getValue());
      }
   }

   @Override
   public Iterator<Entry<TypeK, TypeV>> iterator() {
      return new SnapshotE(this.this$0);
   }
}
