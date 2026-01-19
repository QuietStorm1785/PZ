package zombie.core.Collections;

import java.util.Enumeration;
import java.util.Iterator;
import zombie.core.Collections.NonBlockingHashMapLong.SnapshotV;

public class NonBlockingHashMapLong$IteratorLong implements Iterator<Long>, Enumeration<Long> {
   private final NonBlockingHashMapLong<TypeV>.SnapshotV _ss;

   public NonBlockingHashMapLong$IteratorLong(NonBlockingHashMapLong var1) {
      this.this$0 = var1;
      this._ss = new SnapshotV(var1);
   }

   @Override
   public void remove() {
      this._ss.remove();
   }

   public Long next() {
      this._ss.next();
      return this._ss._prevK;
   }

   public long nextLong() {
      this._ss.next();
      return this._ss._prevK;
   }

   @Override
   public boolean hasNext() {
      return this._ss.hasNext();
   }

   public Long nextElement() {
      return this.next();
   }

   @Override
   public boolean hasMoreElements() {
      return this.hasNext();
   }
}
