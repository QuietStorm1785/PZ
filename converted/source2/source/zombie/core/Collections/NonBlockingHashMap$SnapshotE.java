package zombie.core.Collections;

import java.util.Iterator;
import java.util.Map.Entry;
import zombie.core.Collections.NonBlockingHashMap.NBHMEntry;
import zombie.core.Collections.NonBlockingHashMap.SnapshotV;

class NonBlockingHashMap$SnapshotE implements Iterator<Entry<TypeK, TypeV>> {
   final NonBlockingHashMap<TypeK, TypeV>.SnapshotV _ss;

   public NonBlockingHashMap$SnapshotE(NonBlockingHashMap var1) {
      this.this$0 = var1;
      this._ss = new SnapshotV(var1);
   }

   @Override
   public void remove() {
      this._ss.remove();
   }

   public Entry<TypeK, TypeV> next() {
      this._ss.next();
      return new NBHMEntry(this.this$0, this._ss._prevK, this._ss._prevV);
   }

   @Override
   public boolean hasNext() {
      return this._ss.hasNext();
   }
}
