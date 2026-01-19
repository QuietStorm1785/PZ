package zombie.core.Collections;

import java.util.Enumeration;
import java.util.Iterator;
import zombie.core.Collections.NonBlockingHashMap.SnapshotV;

class NonBlockingHashMap$SnapshotK implements Iterator<TypeK>, Enumeration<TypeK> {
   final NonBlockingHashMap<TypeK, TypeV>.SnapshotV _ss;

   public NonBlockingHashMap$SnapshotK(NonBlockingHashMap var1) {
      this.this$0 = var1;
      this._ss = new SnapshotV(var1);
   }

   @Override
   public void remove() {
      this._ss.remove();
   }

   @Override
   public TypeK next() {
      this._ss.next();
      return (TypeK)this._ss._prevK;
   }

   @Override
   public boolean hasNext() {
      return this._ss.hasNext();
   }

   @Override
   public TypeK nextElement() {
      return (TypeK)this.next();
   }

   @Override
   public boolean hasMoreElements() {
      return this.hasNext();
   }
}
