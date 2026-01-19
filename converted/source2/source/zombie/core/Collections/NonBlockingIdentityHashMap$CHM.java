package zombie.core.Collections;

import java.util.concurrent.atomic.AtomicLongFieldUpdater;
import java.util.concurrent.atomic.AtomicReferenceFieldUpdater;
import zombie.core.Collections.NonBlockingIdentityHashMap.Prime;

final class NonBlockingIdentityHashMap$CHM<TypeK, TypeV> {
   private final Counter _size;
   private final Counter _slots;
   volatile Object[] _newkvs;
   private final AtomicReferenceFieldUpdater<NonBlockingIdentityHashMap$CHM, Object[]> _newkvsUpdater = AtomicReferenceFieldUpdater.newUpdater(
      NonBlockingIdentityHashMap$CHM.class, Object[].class, "_newkvs"
   );
   volatile long _resizers;
   private static final AtomicLongFieldUpdater<NonBlockingIdentityHashMap$CHM> _resizerUpdater = AtomicLongFieldUpdater.newUpdater(
      NonBlockingIdentityHashMap$CHM.class, "_resizers"
   );
   volatile long _copyIdx = 0L;
   private static final AtomicLongFieldUpdater<NonBlockingIdentityHashMap$CHM> _copyIdxUpdater = AtomicLongFieldUpdater.newUpdater(
      NonBlockingIdentityHashMap$CHM.class, "_copyIdx"
   );
   volatile long _copyDone = 0L;
   private static final AtomicLongFieldUpdater<NonBlockingIdentityHashMap$CHM> _copyDoneUpdater = AtomicLongFieldUpdater.newUpdater(
      NonBlockingIdentityHashMap$CHM.class, "_copyDone"
   );

   public int size() {
      return (int)this._size.get();
   }

   public int slots() {
      return (int)this._slots.get();
   }

   boolean CAS_newkvs(Object[] var1) {
      while (this._newkvs == null) {
         if (this._newkvsUpdater.compareAndSet(this, null, var1)) {
            return true;
         }
      }

      return false;
   }

   NonBlockingIdentityHashMap$CHM(Counter var1) {
      this._size = var1;
      this._slots = new Counter();
   }

   private final boolean tableFull(int var1, int var2) {
      return var1 >= 10 && this._slots.estimate_get() >= NonBlockingIdentityHashMap.reprobe_limit(var2);
   }

   private final Object[] resize(NonBlockingIdentityHashMap var1, Object[] var2) {
      if (!$assertionsDisabled && NonBlockingIdentityHashMap.chm(var2) != this) {
         throw new AssertionError();
      } else {
         Object[] var3 = this._newkvs;
         if (var3 != null) {
            return var3;
         } else {
            int var4 = NonBlockingIdentityHashMap.len(var2);
            int var5 = this.size();
            int var6 = var5;
            if (var5 >= var4 >> 2) {
               var6 = var4 << 1;
               if (var5 >= var4 >> 1) {
                  var6 = var4 << 2;
               }
            }

            long var7 = System.currentTimeMillis();
            long var9 = 0L;
            if (var6 <= var4 && var7 <= var1._last_resize_milli + 10000L && this._slots.estimate_get() >= var5 << 1) {
               var6 = var4 << 1;
            }

            if (var6 < var4) {
               var6 = var4;
            }

            int var11 = 3;

            while (1 << var11 < var6) {
               var11++;
            }

            long var12 = this._resizers;

            while (!_resizerUpdater.compareAndSet(this, var12, var12 + 1L)) {
               var12 = this._resizers;
            }

            int var14 = (1 << var11 << 1) + 4 << 3 >> 20;
            if (var12 >= 2L && var14 > 0) {
               var3 = this._newkvs;
               if (var3 != null) {
                  return var3;
               }

               try {
                  Thread.sleep(8 * var14);
               } catch (Exception var16) {
               }
            }

            var3 = this._newkvs;
            if (var3 != null) {
               return var3;
            } else {
               var3 = new Object[(1 << var11 << 1) + 2];
               var3[0] = new NonBlockingIdentityHashMap$CHM(this._size);
               var3[1] = new int[1 << var11];
               if (this._newkvs != null) {
                  return this._newkvs;
               } else {
                  if (this.CAS_newkvs(var3)) {
                     var1.rehash();
                  } else {
                     var3 = this._newkvs;
                  }

                  return var3;
               }
            }
         }
      }
   }

   private final void help_copy_impl(NonBlockingIdentityHashMap var1, Object[] var2, boolean var3) {
      if (!$assertionsDisabled && NonBlockingIdentityHashMap.chm(var2) != this) {
         throw new AssertionError();
      } else {
         Object[] var4 = this._newkvs;
         if (!$assertionsDisabled && var4 == null) {
            throw new AssertionError();
         } else {
            int var5 = NonBlockingIdentityHashMap.len(var2);
            int var6 = Math.min(var5, 1024);
            int var7 = -1;
            int var8 = -9999;

            while (this._copyDone < var5) {
               if (var7 == -1) {
                  var8 = (int)this._copyIdx;

                  while (var8 < var5 << 1 && !_copyIdxUpdater.compareAndSet(this, var8, var8 + var6)) {
                     var8 = (int)this._copyIdx;
                  }

                  if (var8 >= var5 << 1) {
                     var7 = var8;
                  }
               }

               int var9 = 0;

               for (int var10 = 0; var10 < var6; var10++) {
                  if (this.copy_slot(var1, var8 + var10 & var5 - 1, var2, var4)) {
                     var9++;
                  }
               }

               if (var9 > 0) {
                  this.copy_check_and_promote(var1, var2, var9);
               }

               var8 += var6;
               if (!var3 && var7 == -1) {
                  return;
               }
            }

            this.copy_check_and_promote(var1, var2, 0);
         }
      }
   }

   private final Object[] copy_slot_and_check(NonBlockingIdentityHashMap var1, Object[] var2, int var3, Object var4) {
      if (!$assertionsDisabled && NonBlockingIdentityHashMap.chm(var2) != this) {
         throw new AssertionError();
      } else {
         Object[] var5 = this._newkvs;
         if (!$assertionsDisabled && var5 == null) {
            throw new AssertionError();
         } else {
            if (this.copy_slot(var1, var3, var2, this._newkvs)) {
               this.copy_check_and_promote(var1, var2, 1);
            }

            return var4 == null ? var5 : var1.help_copy(var5);
         }
      }
   }

   private final void copy_check_and_promote(NonBlockingIdentityHashMap var1, Object[] var2, int var3) {
      if (!$assertionsDisabled && NonBlockingIdentityHashMap.chm(var2) != this) {
         throw new AssertionError();
      } else {
         int var4 = NonBlockingIdentityHashMap.len(var2);
         long var5 = this._copyDone;
         if (!$assertionsDisabled && var5 + var3 > var4) {
            throw new AssertionError();
         } else {
            if (var3 > 0) {
               while (!_copyDoneUpdater.compareAndSet(this, var5, var5 + var3)) {
                  var5 = this._copyDone;
                  if (!$assertionsDisabled && var5 + var3 > var4) {
                     throw new AssertionError();
                  }
               }
            }

            if (var5 + var3 == var4 && var1._kvs == var2 && var1.CAS_kvs(var2, this._newkvs)) {
               var1._last_resize_milli = System.currentTimeMillis();
            }
         }
      }
   }

   private boolean copy_slot(NonBlockingIdentityHashMap var1, int var2, Object[] var3, Object[] var4) {
      Object var5;
      while ((var5 = NonBlockingIdentityHashMap.key(var3, var2)) == null) {
         NonBlockingIdentityHashMap.CAS_key(var3, var2, null, NonBlockingIdentityHashMap.TOMBSTONE);
      }

      Object var6;
      for (var6 = NonBlockingIdentityHashMap.val(var3, var2); !(var6 instanceof Prime); var6 = NonBlockingIdentityHashMap.val(var3, var2)) {
         Prime var7 = var6 != null && var6 != NonBlockingIdentityHashMap.TOMBSTONE ? new Prime(var6) : NonBlockingIdentityHashMap.TOMBPRIME;
         if (NonBlockingIdentityHashMap.CAS_val(var3, var2, var6, var7)) {
            if (var7 == NonBlockingIdentityHashMap.TOMBPRIME) {
               return true;
            }

            var6 = var7;
            break;
         }
      }

      if (var6 == NonBlockingIdentityHashMap.TOMBPRIME) {
         return false;
      } else {
         Object var9 = ((Prime)var6)._V;
         if (!$assertionsDisabled && var9 == NonBlockingIdentityHashMap.TOMBSTONE) {
            throw new AssertionError();
         } else {
            boolean var8 = NonBlockingIdentityHashMap.putIfMatch(var1, var4, var5, var9, null) == null;

            while (!NonBlockingIdentityHashMap.CAS_val(var3, var2, var6, NonBlockingIdentityHashMap.TOMBPRIME)) {
               var6 = NonBlockingIdentityHashMap.val(var3, var2);
            }

            return var8;
         }
      }
   }
}
