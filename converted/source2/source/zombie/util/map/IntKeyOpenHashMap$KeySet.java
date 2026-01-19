package zombie.util.map;

import zombie.util.IntIterator;
import zombie.util.map.IntKeyOpenHashMap.KeySet.1;
import zombie.util.set.AbstractIntSet;

class IntKeyOpenHashMap$KeySet extends AbstractIntSet {
   private IntKeyOpenHashMap$KeySet(IntKeyOpenHashMap var1) {
      this.this$0 = var1;
   }

   public void clear() {
      this.this$0.clear();
   }

   public boolean contains(int var1) {
      return this.this$0.containsKey(var1);
   }

   public IntIterator iterator() {
      return new 1(this);
   }

   public boolean remove(int var1) {
      boolean var2 = this.this$0.containsKey(var1);
      if (var2) {
         this.this$0.remove(var1);
      }

      return var2;
   }

   public int size() {
      return this.this$0.size;
   }
}
