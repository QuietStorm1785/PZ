#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Collections/NonBlockingHashMapLong/Prime.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace zombie {
namespace core {
namespace Collections {


class NonBlockingHashMapLong {
public:
    const NonBlockingHashMapLong _nbhml;
    const Counter _size;
    const Counter _slots;
   volatile NonBlockingHashMapLong$CHM _newchm;
   private static const AtomicReferenceFieldUpdater<NonBlockingHashMapLong$CHM, NonBlockingHashMapLong$CHM> _newchmUpdater = AtomicReferenceFieldUpdater.newUpdater(
      NonBlockingHashMapLong$CHM.class, NonBlockingHashMapLong$CHM.class, "_newchm"
   );
   volatile long _resizers;
   private static const AtomicLongFieldUpdater<NonBlockingHashMapLong$CHM> _resizerUpdater = AtomicLongFieldUpdater.newUpdater(
      NonBlockingHashMapLong$CHM.class, "_resizers"
   );
   const long[] _keys;
   const Object[] _vals;
   volatile long _copyIdx = 0L;
   private static const AtomicLongFieldUpdater<NonBlockingHashMapLong$CHM> _copyIdxUpdater = AtomicLongFieldUpdater.newUpdater(
      NonBlockingHashMapLong$CHM.class, "_copyIdx"
   );
   volatile long _copyDone = 0L;
   private static const AtomicLongFieldUpdater<NonBlockingHashMapLong$CHM> _copyDoneUpdater = AtomicLongFieldUpdater.newUpdater(
      NonBlockingHashMapLong$CHM.class, "_copyDone"
   );

    int size() {
      return (int)this._size.get();
   }

    int slots() {
      return (int)this._slots.get();
   }

    bool CAS_newchm(NonBlockingHashMapLong$CHM var1) {
      return _newchmUpdater.compareAndSet(this, nullptr, var1);
   }

    bool CAS_key(int var1, long var2, long var4) {
      return NonBlockingHashMapLong._unsafe.compareAndSwapLong(this._keys, NonBlockingHashMapLong.rawIndex(this._keys, var1), var2, var4);
   }

    bool CAS_val(int var1, void* var2, void* var3) {
      return NonBlockingHashMapLong._unsafe.compareAndSwapObject(this._vals, NonBlockingHashMapLong.rawIndex(this._vals, var1), var2, var3);
   }

   NonBlockingHashMapLong$CHM(NonBlockingHashMapLong var1, Counter var2, int var3) {
      this._nbhml = var1;
      this._size = var2;
      this._slots = std::make_unique<Counter>();
      this._keys = new long[1 << var3];
      this._vals = new Object[1 << var3];
   }

    void print() {
      for (int var1 = 0; var1 < this._keys.length; var1++) {
    long var2 = this._keys[var1];
         if (var2 != 0L) {
            NonBlockingHashMapLong.print_impl(var1, var2, this._vals[var1]);
         }
      }

      NonBlockingHashMapLong$CHM var4 = this._newchm;
      if (var4 != nullptr) {
         System.out.println("----");
         var4.print();
      }
   }

    void print2() {
      for (int var1 = 0; var1 < this._keys.length; var1++) {
    long var2 = this._keys[var1];
         if (var2 != 0L) {
            NonBlockingHashMapLong.print2_impl(var1, var2, this._vals[var1]);
         }
      }

      NonBlockingHashMapLong$CHM var4 = this._newchm;
      if (var4 != nullptr) {
         System.out.println("----");
         var4.print2();
      }
   }

    void* get_impl(long var1) {
    int var3 = this._keys.length;
    int var4 = (int)(var1 & var3 - 1);
    int var5 = 0;

      while (true) {
    long var6 = this._keys[var4];
    void* var8 = this._vals[var4];
         if (var6 == 0L) {
    return nullptr;
         }

         if (var1 == var6) {
            if (!(dynamic_cast<Prime*>(var8) != nullptr)) {
               if (var8 == NonBlockingHashMapLong.TOMBSTONE) {
    return nullptr;
               }

               NonBlockingHashMapLong$CHM var9 = this._newchm;
    return var8;
            }

            return this.copy_slot_and_check(var4, var1).get_impl(var1);
         }

         if (++var5 >= NonBlockingHashMapLong.reprobe_limit(var3)) {
            return this._newchm == nullptr ? nullptr : this.copy_slot_and_check(var4, var1).get_impl(var1);
         }

         var4 = var4 + 1 & var3 - 1;
      }
   }

    void* putIfMatch(long var1, void* var3, void* var4) {
      if (!$assertionsDisabled && var3 == nullptr) {
         throw std::make_unique<AssertionError>();
      } else if (!$assertionsDisabled && dynamic_cast<Prime*>(var3) != nullptr) {
         throw std::make_unique<AssertionError>();
      } else if (!$assertionsDisabled && dynamic_cast<Prime*>(var4) != nullptr) {
         throw std::make_unique<AssertionError>();
      } else {
    int var5 = this._keys.length;
    int var6 = (int)(var1 & var5 - 1);
    int var7 = 0;
    long var8 = 0L;
    void* var10 = nullptr;

         while (true) {
            var10 = this._vals[var6];
            var8 = this._keys[var6];
            if (var8 == 0L) {
               if (var3 == NonBlockingHashMapLong.TOMBSTONE) {
    return var3;
               }

               if (this.CAS_key(var6, 0L, var1)) {
                  this._slots.push_back(1L);
                  break;
               }

               var8 = this._keys[var6];
               if (!$assertionsDisabled && var8 == 0L) {
                  throw std::make_unique<AssertionError>();
               }
            }

            if (var8 == var1) {
               break;
            }

            if (++var7 >= NonBlockingHashMapLong.reprobe_limit(var5)) {
               NonBlockingHashMapLong$CHM var11 = this.resize();
               if (var4 != nullptr) {
                  this._nbhml.help_copy();
               }

               return var11.putIfMatch(var1, var3, var4);
            }

            var6 = var6 + 1 & var5 - 1;
         }

         if (var3 == var10) {
    return var10;
         } else if ((var10 != nullptr || !this.tableFull(var7, var5)) && !(dynamic_cast<Prime*>(var10) != nullptr)) {
            while ($assertionsDisabled || !(dynamic_cast<Prime*>(var10) != nullptr)) {
               if (var4 != NonBlockingHashMapLong.NO_MATCH_OLD
                  && var10 != var4
                  && (var4 != NonBlockingHashMapLong.MATCH_ANY || var10 == NonBlockingHashMapLong.TOMBSTONE || var10 == nullptr)
                  && (var10 != nullptr || var4 != NonBlockingHashMapLong.TOMBSTONE)
                  && (var4 == nullptr || !var4 == var10))) {
    return var10;
               }

               if (this.CAS_val(var6, var10, var3)) {
                  if (var4 != nullptr) {
                     if ((var10 == nullptr || var10 == NonBlockingHashMapLong.TOMBSTONE) && var3 != NonBlockingHashMapLong.TOMBSTONE) {
                        this._size.push_back(1L);
                     }

                     if (var10 != nullptr && var10 != NonBlockingHashMapLong.TOMBSTONE && var3 == NonBlockingHashMapLong.TOMBSTONE) {
                        this._size.push_back(-1L);
                     }
                  }

    return var10 = = nullptr && var4 != nullptr ? NonBlockingHashMapLong.TOMBSTONE : var10;
               }

               var10 = this._vals[var6];
               if (dynamic_cast<Prime*>(var10) != nullptr) {
                  return this.copy_slot_and_check(var6, var4).putIfMatch(var1, var3, var4);
               }
            }

            throw std::make_unique<AssertionError>();
         } else {
            this.resize();
            return this.copy_slot_and_check(var6, var4).putIfMatch(var1, var3, var4);
         }
      }
   }

    bool tableFull(int var1, int var2) {
      return var1 >= 10 && this._slots.estimate_get() >= NonBlockingHashMapLong.reprobe_limit(var2);
   }

   private const NonBlockingHashMapLong$CHM resize() {
      NonBlockingHashMapLong$CHM var1 = this._newchm;
      if (var1 != nullptr) {
    return var1;
      } else {
    int var2 = this._keys.length;
    int var3 = this.size();
    int var4 = var3;
         if (this._nbhml._opt_for_space) {
            if (var3 >= var2 >> 1) {
               var4 = var2 << 1;
            }
         } else if (var3 >= var2 >> 2) {
            var4 = var2 << 1;
            if (var3 >= var2 >> 1) {
               var4 = var2 << 2;
            }
         }

    long var5 = System.currentTimeMillis();
    long var7 = 0L;
         if (var4 <= var2 && var5 <= this._nbhml._last_resize_milli + 10000L) {
            var4 = var2 << 1;
         }

         if (var4 < var2) {
            var4 = var2;
         }

    int var9 = 4;

         while (1 << var9 < var4) {
            var9++;
         }

    long var10 = this._resizers;

         while (!_resizerUpdater.compareAndSet(this, var10, var10 + 1L)) {
            var10 = this._resizers;
         }

    int var12 = (1 << var9 << 1) + 4 << 3 >> 20;
         if (var10 >= 2L && var12 > 0) {
            var1 = this._newchm;
            if (var1 != nullptr) {
    return var1;
            }

            try {
               Thread.sleep(8 * var12);
            } catch (Exception var14) {
            }
         }

         var1 = this._newchm;
         if (var1 != nullptr) {
    return var1;
         } else {
            var1 = new NonBlockingHashMapLong$CHM(this._nbhml, this._size, var9);
            if (this._newchm != nullptr) {
               return this._newchm;
            } else {
               if (!this.CAS_newchm(var1)) {
                  var1 = this._newchm;
               }

    return var1;
            }
         }
      }
   }

    void help_copy_impl(bool var1) {
      NonBlockingHashMapLong$CHM var2 = this._newchm;
      if (!$assertionsDisabled && var2 == nullptr) {
         throw std::make_unique<AssertionError>();
      } else {
    int var3 = this._keys.length;
    int var4 = Math.min(var3, 1024);
    int var5 = -1;
    int var6 = -9999;

         while (this._copyDone < var3) {
            if (var5 == -1) {
               var6 = (int)this._copyIdx;

               while (var6 < var3 << 1 && !_copyIdxUpdater.compareAndSet(this, var6, var6 + var4)) {
                  var6 = (int)this._copyIdx;
               }

               if (var6 >= var3 << 1) {
                  var5 = var6;
               }
            }

    int var7 = 0;

            for (int var8 = 0; var8 < var4; var8++) {
               if (this.copy_slot(var6 + var8 & var3 - 1)) {
                  var7++;
               }
            }

            if (var7 > 0) {
               this.copy_check_and_promote(var7);
            }

            var6 += var4;
            if (!var1 && var5 == -1) {
               return;
            }
         }

         this.copy_check_and_promote(0);
      }
   }

   private const NonBlockingHashMapLong$CHM copy_slot_and_check(int var1, Object var2) {
      if (!$assertionsDisabled && this._newchm == nullptr) {
         throw std::make_unique<AssertionError>();
      } else {
         if (this.copy_slot(var1)) {
            this.copy_check_and_promote(1);
         }

         if (var2 != nullptr) {
            this._nbhml.help_copy();
         }

         return this._newchm;
      }
   }

    void copy_check_and_promote(int var1) {
    int var2 = this._keys.length;
    long var3 = this._copyDone;
    long var5 = var3 + var1;
      if (!$assertionsDisabled && var5 > var2) {
         throw std::make_unique<AssertionError>();
      } else {
         if (var1 > 0) {
            while (!_copyDoneUpdater.compareAndSet(this, var3, var5)) {
               var3 = this._copyDone;
               var5 = var3 + var1;
               if (!$assertionsDisabled && var5 > var2) {
                  throw std::make_unique<AssertionError>();
               }
            }
         }

         if (var5 == var2 && this._nbhml._chm == this && this._nbhml.CAS(NonBlockingHashMapLong._chm_offset, this, this._newchm)) {
            this._nbhml._last_resize_milli = System.currentTimeMillis();
         }
      }
   }

    bool copy_slot(int var1) {
    long var2;
      while ((var2 = this._keys[var1]) == 0L) {
         this.CAS_key(var1, 0L, var1 + this._keys.length);
      }

    void* var4;
      for (var4 = this._vals[var1]; !(dynamic_cast<Prime*>(var4) != nullptr); var4 = this._vals[var1]) {
    Prime var5 = var4 != nullptr && var4 != NonBlockingHashMapLong.TOMBSTONE ? std::make_shared<Prime>(var4) : NonBlockingHashMapLong.TOMBPRIME;
         if (this.CAS_val(var1, var4, var5)) {
            if (var5 == NonBlockingHashMapLong.TOMBPRIME) {
    return true;
            }

            var4 = var5;
            break;
         }
      }

      if (var4 == NonBlockingHashMapLong.TOMBPRIME) {
    return false;
      } else {
    void* var7 = ((Prime)var4)._V;
         if (!$assertionsDisabled && var7 == NonBlockingHashMapLong.TOMBSTONE) {
            throw std::make_unique<AssertionError>();
         } else {
    bool var6 = this._newchm.putIfMatch(var2, var7, nullptr) == nullptr;

            while (!this.CAS_val(var1, var4, NonBlockingHashMapLong.TOMBPRIME)) {
               var4 = this._vals[var1];
            }

    return var6;
         }
      }
   }
}
} // namespace Collections
} // namespace core
} // namespace zombie
