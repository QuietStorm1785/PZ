package zombie.core.Collections;

import java.util.Iterator;
import java.util.Map.Entry;
import zombie.core.Collections.NonBlockingHashtable.NBHMEntry;
import zombie.core.Collections.NonBlockingHashtable.SnapshotV;

class NonBlockingHashtable$SnapshotE implements Iterator<Entry<TypeK, TypeV>> {
   final NonBlockingHashtable<TypeK, TypeV>.SnapshotV _ss;

   public NonBlockingHashtable$SnapshotE(NonBlockingHashtable var1) {
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
