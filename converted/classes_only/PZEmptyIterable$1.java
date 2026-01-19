package zombie.util.list;

import java.util.Iterator;

class PZEmptyIterable$1 implements Iterator<T> {
   PZEmptyIterable$1(PZEmptyIterable var1) {
      this.this$0 = var1;
   }

   @Override
   public boolean hasNext() {
      return false;
   }

   @Override
   public T next() {
      throw new ArrayIndexOutOfBoundsException("Empty Iterator. Has no data.");
   }
}
