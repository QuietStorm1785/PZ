package zombie.util.list;

import zombie.util.AbstractIntCollection;
import zombie.util.IntCollection;
import zombie.util.IntIterator;
import zombie.util.hash.DefaultIntHashFunction;
import zombie.util.list.AbstractIntList.1;
import zombie.util.util.Exceptions;

public abstract class AbstractIntList extends AbstractIntCollection implements IntList {
   protected AbstractIntList() {
   }

   public boolean add(int var1) {
      this.add(this.size(), var1);
      return true;
   }

   public void add(int var1, int var2) {
      Exceptions.unsupported("add");
   }

   public boolean addAll(int var1, IntCollection var2) {
      if (var1 < 0 || var1 > this.size()) {
         Exceptions.indexOutOfBounds(var1, 0, this.size());
      }

      IntIterator var3 = var2.iterator();

      boolean var4;
      for (var4 = var3.hasNext(); var3.hasNext(); var1++) {
         this.add(var1, var3.next());
      }

      return var4;
   }

   public int indexOf(int var1) {
      return this.indexOf(0, var1);
   }

   public int indexOf(int var1, int var2) {
      IntListIterator var3 = this.listIterator(var1);

      while (var3.hasNext()) {
         if (var3.next() == var2) {
            return var3.previousIndex();
         }
      }

      return -1;
   }

   public IntIterator iterator() {
      return this.listIterator();
   }

   public int lastIndexOf(int var1) {
      IntListIterator var2 = this.listIterator(this.size());

      while (var2.hasPrevious()) {
         if (var2.previous() == var1) {
            return var2.nextIndex();
         }
      }

      return -1;
   }

   public int lastIndexOf(int var1, int var2) {
      IntListIterator var3 = this.listIterator(var1);

      while (var3.hasPrevious()) {
         if (var3.previous() == var2) {
            return var3.nextIndex();
         }
      }

      return -1;
   }

   public IntListIterator listIterator() {
      return this.listIterator(0);
   }

   public IntListIterator listIterator(int var1) {
      if (var1 < 0 || var1 > this.size()) {
         Exceptions.indexOutOfBounds(var1, 0, this.size());
      }

      return new 1(this, var1);
   }

   public int removeElementAt(int var1) {
      Exceptions.unsupported("removeElementAt");
      throw new RuntimeException();
   }

   public boolean equals(Object var1) {
      if (this == var1) {
         return true;
      } else if (!(var1 instanceof IntList)) {
         return false;
      } else {
         IntListIterator var2 = this.listIterator();
         IntListIterator var3 = ((IntList)var1).listIterator();

         while (var2.hasNext() && var3.hasNext()) {
            if (var2.next() != var3.next()) {
               return false;
            }
         }

         return !var2.hasNext() && !var3.hasNext();
      }
   }

   public int hashCode() {
      int var1 = 1;
      IntIterator var2 = this.iterator();

      while (var2.hasNext()) {
         var1 = 31 * var1 + DefaultIntHashFunction.INSTANCE.hash(var2.next());
      }

      return var1;
   }
}
