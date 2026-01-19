package zombie.util.map;

import java.util.Iterator;
import zombie.util.map.IntKeyOpenHashMap.ValueCollection;
import zombie.util.util.Exceptions;

class IntKeyOpenHashMap$ValueCollection$1 implements Iterator<V> {
   int nextEntry;
   int lastEntry;

   IntKeyOpenHashMap$ValueCollection$1(ValueCollection var1) {
      this.this$1 = var1;
      this.nextEntry = this.nextEntry(0);
      this.lastEntry = -1;
   }

   int nextEntry(int var1) {
      while (var1 < this.this$1.this$0.keys.length && this.this$1.this$0.states[var1] != 1) {
         var1++;
      }

      return var1;
   }

   @Override
   public boolean hasNext() {
      return this.nextEntry < this.this$1.this$0.keys.length;
   }

   @Override
   public V next() {
      if (!this.hasNext()) {
         Exceptions.endOfIterator();
      }

      this.lastEntry = this.nextEntry;
      this.nextEntry = this.nextEntry(this.nextEntry + 1);
      return (V)this.this$1.this$0.values[this.lastEntry];
   }

   @Override
   public void remove() {
      if (this.lastEntry == -1) {
         Exceptions.noElementToRemove();
      }

      this.this$1.this$0.states[this.lastEntry] = 2;
      this.this$1.this$0.values[this.lastEntry] = null;
      this.this$1.this$0.size--;
      this.lastEntry = -1;
   }
}
