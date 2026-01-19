package zombie.core.Collections;

import java.io.Serializable;
import java.util.concurrent.atomic.AtomicReferenceFieldUpdater;
import zombie.core.Collections.ConcurrentAutoTable.CAT;

public class ConcurrentAutoTable implements Serializable {
   private volatile CAT _cat = new CAT(null, 4, 0L);
   private static final AtomicReferenceFieldUpdater<ConcurrentAutoTable, CAT> _catUpdater = AtomicReferenceFieldUpdater.newUpdater(
      ConcurrentAutoTable.class, CAT.class, "_cat"
   );

   public void add(long var1) {
      this.add_if_mask(var1, 0L);
   }

   public void decrement() {
      this.add_if_mask(-1L, 0L);
   }

   public void increment() {
      this.add_if_mask(1L, 0L);
   }

   public void set(long var1) {
      CAT var3 = new CAT(null, 4, var1);

      while (!this.CAS_cat(this._cat, var3)) {
      }
   }

   public long get() {
      return this._cat.sum(0L);
   }

   public int intValue() {
      return (int)this._cat.sum(0L);
   }

   public long longValue() {
      return this._cat.sum(0L);
   }

   public long estimate_get() {
      return this._cat.estimate_sum(0L);
   }

   @Override
   public String toString() {
      return this._cat.toString(0L);
   }

   public void print() {
      this._cat.print();
   }

   public int internal_size() {
      return this._cat._t.length;
   }

   private long add_if_mask(long var1, long var3) {
      return this._cat.add_if_mask(var1, var3, hash(), this);
   }

   private boolean CAS_cat(CAT var1, CAT var2) {
      return _catUpdater.compareAndSet(this, var1, var2);
   }

   private static final int hash() {
      int var0 = System.identityHashCode(Thread.currentThread());
      var0 ^= var0 >>> 20 ^ var0 >>> 12;
      var0 ^= var0 >>> 7 ^ var0 >>> 4;
      return var0 << 2;
   }
}
