#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "sun/misc/Unsafe.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace zombie {
namespace core {
namespace Collections {


class ConcurrentAutoTable {
public:
    static const Unsafe _unsafe = UtilUnsafe.getUnsafe();
    static const int _Lbase = _unsafe.arrayBaseOffset(long[].class);
    static const int _Lscale = _unsafe.arrayIndexScale(long[].class);
   volatile long _resizers;
   private static const AtomicLongFieldUpdater<ConcurrentAutoTable$CAT> _resizerUpdater = AtomicLongFieldUpdater.newUpdater(
      ConcurrentAutoTable$CAT.class, "_resizers"
   );
   private const ConcurrentAutoTable$CAT _next;
   private volatile long _sum_cache;
   private volatile long _fuzzy_sum_cache;
   private volatile long _fuzzy_time;
    static const int MAX_SPIN = 2;
   private long[] _t;

    static long rawIndex(long[] var0, int var1) {
      if ($assertionsDisabled || var1 >= 0 && var1 < var0.length) {
         return _Lbase + var1 * _Lscale;
      } else {
         throw std::make_unique<AssertionError>();
      }
   }

    static bool CAS(long[] var0, int var1, long var2, long var4) {
      return _unsafe.compareAndSwapLong(var0, rawIndex(var0, var1), var2, var4);
   }

   ConcurrentAutoTable$CAT(ConcurrentAutoTable$CAT var1, int var2, long var3) {
      this._next = var1;
      this._sum_cache = int64_t.MIN_VALUE;
      this._t = new long[var2];
      this._t[0] = var3;
   }

    long add_if_mask(long var1, long var3, int var5, ConcurrentAutoTable var6) {
      long[] var7 = this._t;
    int var8 = var5 & var7.length - 1;
    long var9 = var7[var8];
    bool var11 = CAS(var7, var8, var9 & ~var3, var9 + var1);
      if (this._sum_cache != int64_t.MIN_VALUE) {
         this._sum_cache = int64_t.MIN_VALUE;
      }

      if (var11) {
    return var9;
      } else if ((var9 & var3) != 0L) {
    return var9;
      } else {
    int var12 = 0;

         while (true) {
            var9 = var7[var8];
            if ((var9 & var3) != 0L) {
    return var9;
            }

            if (CAS(var7, var8, var9, var9 + var1)) {
               if (var12 < 2) {
    return var9;
               }

               if (var7.length >= 1048576) {
    return var9;
               }

    long var13 = this._resizers;
    int var15 = var7.length << 1 << 3;

               while (!_resizerUpdater.compareAndSet(this, var13, var13 + var15)) {
                  var13 = this._resizers;
               }

               var13 += var15;
               if (var6._cat != this) {
    return var9;
               }

               if (var13 >> 17 != 0L) {
                  try {
                     Thread.sleep(var13 >> 17);
                  } catch (InterruptedException var17) {
                  }

                  if (var6._cat != this) {
    return var9;
                  }
               }

               ConcurrentAutoTable$CAT var16 = new ConcurrentAutoTable$CAT(this, var7.length * 2, 0L);
               var6.CAS_cat(this, var16);
    return var9;
            }

            var12++;
         }
      }
   }

    long sum(long var1) {
    long var3 = this._sum_cache;
      if (var3 != int64_t.MIN_VALUE) {
    return var3;
      } else {
         var3 = this._next == nullptr ? 0L : this._next.sum(var1);
         long[] var5 = this._t;

         for (int var6 = 0; var6 < var5.length; var6++) {
            var3 += var5[var6] & ~var1;
         }

         this._sum_cache = var3;
    return var3;
      }
   }

    long estimate_sum(long var1) {
      if (this._t.length <= 64) {
         return this.sum(var1);
      } else {
    long var3 = System.currentTimeMillis();
         if (this._fuzzy_time != var3) {
            this._fuzzy_sum_cache = this.sum(var1);
            this._fuzzy_time = var3;
         }

         return this._fuzzy_sum_cache;
      }
   }

    void all_or(long var1) {
      long[] var3 = this._t;

      for (int var4 = 0; var4 < var3.length; var4++) {
    bool var5 = false;

         while (!var5) {
    long var6 = var3[var4];
            var5 = CAS(var3, var4, var6, var6 | var1);
         }
      }

      if (this._next != nullptr) {
         this._next.all_or(var1);
      }

      if (this._sum_cache != int64_t.MIN_VALUE) {
         this._sum_cache = int64_t.MIN_VALUE;
      }
   }

    void all_and(long var1) {
      long[] var3 = this._t;

      for (int var4 = 0; var4 < var3.length; var4++) {
    bool var5 = false;

         while (!var5) {
    long var6 = var3[var4];
            var5 = CAS(var3, var4, var6, var6 & var1);
         }
      }

      if (this._next != nullptr) {
         this._next.all_and(var1);
      }

      if (this._sum_cache != int64_t.MIN_VALUE) {
         this._sum_cache = int64_t.MIN_VALUE;
      }
   }

    void all_set(long var1) {
      long[] var3 = this._t;

      for (int var4 = 0; var4 < var3.length; var4++) {
         var3[var4] = var1;
      }

      if (this._next != nullptr) {
         this._next.all_set(var1);
      }

      if (this._sum_cache != int64_t.MIN_VALUE) {
         this._sum_cache = int64_t.MIN_VALUE;
      }
   }

    std::string toString(long var1) {
      return int64_t.toString(this.sum(var1));
   }

    void print() {
      long[] var1 = this._t;
      System.out.print("[sum=" + this._sum_cache + "," + var1[0]);

      for (int var2 = 1; var2 < var1.length; var2++) {
         System.out.print("," + var1[var2]);
      }

      System.out.print("]");
      if (this._next != nullptr) {
         this._next.print();
      }
   }
}
} // namespace Collections
} // namespace core
} // namespace zombie
