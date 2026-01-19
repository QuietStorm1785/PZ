package zombie.util.map;

import zombie.util.IntIterator;
import zombie.util.map.IntKeyOpenHashMap.KeySet;
import zombie.util.util.Exceptions;

class IntKeyOpenHashMap$KeySet$1 implements IntIterator {
   int nextEntry;
   int lastEntry;

   IntKeyOpenHashMap$KeySet$1(KeySet var1) {
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

   public boolean hasNext() {
      return this.nextEntry < this.this$1.this$0.keys.length;
   }

   public int next() {
      if (!this.hasNext()) {
         Exceptions.endOfIterator();
      }

      this.lastEntry = this.nextEntry;
      this.nextEntry = this.nextEntry(this.nextEntry + 1);
      return this.this$1.this$0.keys[this.lastEntry];
   }

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
