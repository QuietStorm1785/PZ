package zombie.util.map;

import zombie.util.util.Exceptions;

class IntKeyOpenHashMap$1 implements IntKeyMapIterator<V> {
   int nextEntry;
   int lastEntry;

   IntKeyOpenHashMap$1(IntKeyOpenHashMap var1) {
      this.this$0 = var1;
      this.nextEntry = this.nextEntry(0);
      this.lastEntry = -1;
   }

   int nextEntry(int var1) {
      while (var1 < this.this$0.keys.length && this.this$0.states[var1] != 1) {
         var1++;
      }

      return var1;
   }

   public boolean hasNext() {
      return this.nextEntry < this.this$0.keys.length;
   }

   public void next() {
      if (!this.hasNext()) {
         Exceptions.endOfIterator();
      }

      this.lastEntry = this.nextEntry;
      this.nextEntry = this.nextEntry(this.nextEntry + 1);
   }

   public void remove() {
      if (this.lastEntry == -1) {
         Exceptions.noElementToRemove();
      }

      this.this$0.states[this.lastEntry] = 2;
      this.this$0.values[this.lastEntry] = null;
      this.this$0.size--;
      this.lastEntry = -1;
   }

   public int getKey() {
      if (this.lastEntry == -1) {
         Exceptions.noElementToGet();
      }

      return this.this$0.keys[this.lastEntry];
   }

   public V getValue() {
      if (this.lastEntry == -1) {
         Exceptions.noElementToGet();
      }

      return (V)this.this$0.values[this.lastEntry];
   }
}
