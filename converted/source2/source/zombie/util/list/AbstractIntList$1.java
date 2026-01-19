package zombie.util.list;

import zombie.util.util.Exceptions;

class AbstractIntList$1 implements IntListIterator {
   private int ptr;
   private int lptr;

   AbstractIntList$1(AbstractIntList var1, int var2) {
      this.this$0 = var1;
      this.val$index = var2;
      this.ptr = this.val$index;
      this.lptr = -1;
   }

   public boolean hasNext() {
      return this.ptr < this.this$0.size();
   }

   public int next() {
      if (this.ptr == this.this$0.size()) {
         Exceptions.endOfIterator();
      }

      this.lptr = this.ptr++;
      return this.this$0.get(this.lptr);
   }

   public void remove() {
      if (this.lptr == -1) {
         Exceptions.noElementToRemove();
      }

      this.this$0.removeElementAt(this.lptr);
      if (this.lptr < this.ptr) {
         this.ptr--;
      }

      this.lptr = -1;
   }

   public void add(int var1) {
      this.this$0.add(this.ptr++, var1);
      this.lptr = -1;
   }

   public boolean hasPrevious() {
      return this.ptr > 0;
   }

   public int nextIndex() {
      return this.ptr;
   }

   public int previous() {
      if (this.ptr == 0) {
         Exceptions.startOfIterator();
      }

      this.ptr--;
      this.lptr = this.ptr;
      return this.this$0.get(this.ptr);
   }

   public int previousIndex() {
      return this.ptr - 1;
   }

   public void set(int var1) {
      if (this.lptr == -1) {
         Exceptions.noElementToSet();
      }

      this.this$0.set(this.lptr, var1);
   }
}
