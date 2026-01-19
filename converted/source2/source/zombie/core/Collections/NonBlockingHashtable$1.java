package zombie.core.Collections;

import java.util.AbstractCollection;
import java.util.Iterator;
import zombie.core.Collections.NonBlockingHashtable.SnapshotV;

class NonBlockingHashtable$1 extends AbstractCollection<TypeV> {
   NonBlockingHashtable$1(NonBlockingHashtable var1) {
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
   public boolean contains(Object var1) {
      return this.this$0.containsValue(var1);
   }

   @Override
   public Iterator<TypeV> iterator() {
      return new SnapshotV(this.this$0);
   }
}
