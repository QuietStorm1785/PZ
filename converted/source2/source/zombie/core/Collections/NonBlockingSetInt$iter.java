package zombie.core.Collections;

import java.util.Iterator;
import zombie.core.Collections.NonBlockingSetInt.NBSIIntIterator;

class NonBlockingSetInt$iter implements Iterator<Integer> {
   NBSIIntIterator intIterator;

   NonBlockingSetInt$iter(NonBlockingSetInt var1) {
      this.this$0 = var1;
      this.intIterator = new NBSIIntIterator(var1);
   }

   @Override
   public boolean hasNext() {
      return this.intIterator.hasNext();
   }

   public Integer next() {
      return this.intIterator.next();
   }

   @Override
   public void remove() {
      this.intIterator.remove();
   }
}
