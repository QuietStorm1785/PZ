#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Collections/NonBlockingHashMap/Prime.h"
#include <algorithm>

namespace zombie {
namespace core {
namespace Collections {


class NonBlockingHashMap {
public:
    const Counter _size;
    const Counter _slots;
   volatile Object[] _newkvs;
   private const AtomicReferenceFieldUpdater<NonBlockingHashMap$CHM, Object[]> _newkvsUpdater = AtomicReferenceFieldUpdater.newUpdater(
      NonBlockingHashMap$CHM.class, Object[].class, "_newkvs"
   );
   volatile long _resizers;
   private static const AtomicLongFieldUpdater<NonBlockingHashMap$CHM> _resizerUpdater = AtomicLongFieldUpdater.newUpdater(
      NonBlockingHashMap$CHM.class, "_resizers"
   );
   volatile long _copyIdx = 0L;
   private static const AtomicLongFieldUpdater<NonBlockingHashMap$CHM> _copyIdxUpdater = AtomicLongFieldUpdater.newUpdater(
      NonBlockingHashMap$CHM.class, "_copyIdx"
   );
   volatile long _copyDone = 0L;
   private static const AtomicLongFieldUpdater<NonBlockingHashMap$CHM> _copyDoneUpdater = AtomicLongFieldUpdater.newUpdater(
      NonBlockingHashMap$CHM.class, "_copyDone"
   );

    int size() {
      return (int)this._size.get();
   }

    int slots() {
      return (int)this._slots.get();
   }

    bool CAS_newkvs(Object[] var1) {
      while (this._newkvs == nullptr) {
         if (this._newkvsUpdater.compareAndSet(this, nullptr, var1)) {
    return true;
         }
      }

    return false;
   }

   NonBlockingHashMap$CHM(Counter var1) {
      this._size = var1;
      this._slots = std::make_unique<Counter>();
   }

    bool tableFull(int var1, int var2) {
      return var1 >= 10 && this._slots.estimate_get() >= NonBlockingHashMap.reprobe_limit(var2);
   }

   private const Object[] resize(NonBlockingHashMap var1, Object[] var2) {
      if (!$assertionsDisabled && NonBlockingHashMap.chm(var2) != this) {
         throw std::make_unique<AssertionError>();
      } else {
         Object[] var3 = this._newkvs;
         if (var3 != nullptr) {
    return var3;
         } else {
    int var4 = NonBlockingHashMap.len(var2);
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
               if (var3 != nullptr) {
    return var3;
               }

               try {
                  Thread.sleep(8 * var14);
               } catch (Exception var16) {
               }
            }

            var3 = this._newkvs;
            if (var3 != nullptr) {
    return var3;
            } else {
               var3 = new Object[(1 << var11 << 1) + 2];
               var3[0] = new NonBlockingHashMap$CHM(this._size);
               var3[1] = new int[1 << var11];
               if (this._newkvs != nullptr) {
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

    void help_copy_impl(NonBlockingHashMap var1, Object[] var2, bool var3) {
      if (!$assertionsDisabled && NonBlockingHashMap.chm(var2) != this) {
         throw std::make_unique<AssertionError>();
      } else {
         Object[] var4 = this._newkvs;
         if (!$assertionsDisabled && var4 == nullptr) {
            throw std::make_unique<AssertionError>();
         } else {
    int var5 = NonBlockingHashMap.len(var2);
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

   private const Object[] copy_slot_and_check(NonBlockingHashMap var1, Object[] var2, int var3, Object var4) {
      if (!$assertionsDisabled && NonBlockingHashMap.chm(var2) != this) {
         throw std::make_unique<AssertionError>();
      } else {
         Object[] var5 = this._newkvs;
         if (!$assertionsDisabled && var5 == nullptr) {
            throw std::make_unique<AssertionError>();
         } else {
            if (this.copy_slot(var1, var3, var2, this._newkvs)) {
               this.copy_check_and_promote(var1, var2, 1);
            }

    return var4 = = nullptr ? var5 : var1.help_copy(var5);
         }
      }
   }

    void copy_check_and_promote(NonBlockingHashMap var1, Object[] var2, int var3) {
      if (!$assertionsDisabled && NonBlockingHashMap.chm(var2) != this) {
         throw std::make_unique<AssertionError>();
      } else {
    int var4 = NonBlockingHashMap.len(var2);
    long var5 = this._copyDone;
         if (!$assertionsDisabled && var5 + var3 > var4) {
            throw std::make_unique<AssertionError>();
         } else {
            if (var3 > 0) {
               while (!_copyDoneUpdater.compareAndSet(this, var5, var5 + var3)) {
                  var5 = this._copyDone;
                  if (!$assertionsDisabled && var5 + var3 > var4) {
                     throw std::make_unique<AssertionError>();
                  }
               }
            }

            if (var5 + var3 == var4 && var1._kvs == var2 && var1.CAS_kvs(var2, this._newkvs)) {
               var1._last_resize_milli = System.currentTimeMillis();
            }
         }
      }
   }

    bool copy_slot(NonBlockingHashMap var1, int var2, Object[] var3, Object[] var4) {
    void* var5;
      while ((var5 = NonBlockingHashMap.key(var3, var2)) == nullptr) {
         NonBlockingHashMap.CAS_key(var3, var2, nullptr, NonBlockingHashMap.TOMBSTONE);
      }

    void* var6;
      for (var6 = NonBlockingHashMap.val(var3, var2); !(dynamic_cast<Prime*>(var6) != nullptr); var6 = NonBlockingHashMap.val(var3, var2)) {
    Prime var7 = var6 != nullptr && var6 != NonBlockingHashMap.TOMBSTONE ? std::make_shared<Prime>(var6) : NonBlockingHashMap.TOMBPRIME;
         if (NonBlockingHashMap.CAS_val(var3, var2, var6, var7)) {
            if (var7 == NonBlockingHashMap.TOMBPRIME) {
    return true;
            }

            var6 = var7;
            break;
         }
      }

      if (var6 == NonBlockingHashMap.TOMBPRIME) {
    return false;
      } else {
    void* var9 = ((Prime)var6)._V;
         if (!$assertionsDisabled && var9 == NonBlockingHashMap.TOMBSTONE) {
            throw std::make_unique<AssertionError>();
         } else {
    bool var8 = NonBlockingHashMap.putIfMatch(var1, var4, var5, var9, nullptr) == nullptr;

            while (!NonBlockingHashMap.CAS_val(var3, var2, var6, NonBlockingHashMap.TOMBPRIME)) {
               var6 = NonBlockingHashMap.val(var3, var2);
            }

    return var8;
         }
      }
   }
}
} // namespace Collections
} // namespace core
} // namespace zombie
