package zombie.core.Collections;

import java.util.Iterator;
import java.util.Map.Entry;
import zombie.core.Collections.NonBlockingHashMapLong.NBHMLEntry;
import zombie.core.Collections.NonBlockingHashMapLong.SnapshotV;

class NonBlockingHashMapLong$SnapshotE implements Iterator<Entry<Long, TypeV>> {
   final NonBlockingHashMapLong<TypeV>.SnapshotV _ss;

   public NonBlockingHashMapLong$SnapshotE(NonBlockingHashMapLong var1) {
      this.this$0 = var1;
      this._ss = new SnapshotV(var1);
   }

   @Override
   public void remove() {
      this._ss.remove();
   }

   public Entry<Long, TypeV> next() {
      this._ss.next();
      return new NBHMLEntry(this.this$0, this._ss._prevK, this._ss._prevV);
   }

   @Override
   public boolean hasNext() {
      return this._ss.hasNext();
   }
}
