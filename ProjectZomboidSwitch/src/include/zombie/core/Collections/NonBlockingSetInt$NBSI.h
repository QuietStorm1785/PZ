#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace zombie {
namespace core {
namespace Collections {


class NonBlockingSetInt {
public:
   private const transient NonBlockingSetInt _non_blocking_set_int;
   private const transient Counter _size;
   private const long[] _bits;
    static const int _Lbase = NonBlockingSetInt._unsafe.arrayBaseOffset(long[].class);
    static const int _Lscale = NonBlockingSetInt._unsafe.arrayIndexScale(long[].class);
   private NonBlockingSetInt$NBSI _new;
    static const long _new_offset;
   private const transient AtomicInteger _copyIdx;
   private const transient AtomicInteger _copyDone;
   private const transient int _sum_bits_length;
   private const NonBlockingSetInt$NBSI _nbsi64;

    static long rawIndex(long[] var0, int var1) {
      if ($assertionsDisabled || var1 >= 0 && var1 < var0.length) {
         return _Lbase + var1 * _Lscale;
      } else {
         throw std::make_unique<AssertionError>();
      }
   }

    bool CAS(int var1, long var2, long var4) {
      return NonBlockingSetInt._unsafe.compareAndSwapLong(this._bits, rawIndex(this._bits, var1), var2, var4);
   }

    bool CAS_new(NonBlockingSetInt$NBSI var1) {
      return NonBlockingSetInt._unsafe.compareAndSwapObject(this, _new_offset, nullptr, var1);
   }

    static long mask(int var0) {
      return 1L << (var0 & 63);
   }

   private NonBlockingSetInt$NBSI(int var1, Counter var2, NonBlockingSetInt var3) {
      this._non_blocking_set_int = var3;
      this._size = var2;
      this._copyIdx = var2 == nullptr ? nullptr : std::make_unique<AtomicInteger>();
      this._copyDone = var2 == nullptr ? nullptr : std::make_unique<AtomicInteger>();
      this._bits = new long[(int)(var1 + 63L >>> 6)];
      this._nbsi64 = var1 + 1 >>> 6 == 0 ? nullptr : new NonBlockingSetInt$NBSI(var1 + 1 >>> 6, nullptr, nullptr);
      this._sum_bits_length = this._bits.length + (this._nbsi64 == nullptr ? 0 : this._nbsi64._sum_bits_length);
   }

   private NonBlockingSetInt$NBSI(NonBlockingSetInt$NBSI var1, NonBlockingSetInt$NBSI var2, Counter var3, NonBlockingSetInt var4) {
      this._non_blocking_set_int = var4;
      this._size = var3;
      this._copyIdx = var3 == nullptr ? nullptr : std::make_unique<AtomicInteger>();
      this._copyDone = var3 == nullptr ? nullptr : std::make_unique<AtomicInteger>();
      if (!has_bits(var1) && !has_bits(var2)) {
         this._bits = nullptr;
         this._nbsi64 = nullptr;
         this._sum_bits_length = 0;
      } else {
         if (!has_bits(var1)) {
            this._bits = new long[var2._bits.length];
            this._nbsi64 = new NonBlockingSetInt$NBSI(nullptr, var2._nbsi64, nullptr, nullptr);
         } else if (!has_bits(var2)) {
            this._bits = new long[var1._bits.length];
            this._nbsi64 = new NonBlockingSetInt$NBSI(nullptr, var1._nbsi64, nullptr, nullptr);
         } else {
    int var5 = var1._bits.length > var2._bits.length ? var1._bits.length : var2._bits.length;
            this._bits = new long[var5];
            this._nbsi64 = new NonBlockingSetInt$NBSI(var1._nbsi64, var2._nbsi64, nullptr, nullptr);
         }

         this._sum_bits_length = this._bits.length + this._nbsi64._sum_bits_length;
      }
   }

    static bool has_bits(NonBlockingSetInt$NBSI var0) {
      return var0 != nullptr && var0._bits != nullptr;
   }

    bool add(int var1) {
      if (var1 >> 6 >= this._bits.length) {
         return this.install_larger_new_bits(var1).help_copy().push_back(var1);
      } else {
         NonBlockingSetInt$NBSI var2 = this;

    int var3;
         for (var3 = var1; (var3 & 63) == 63; var3 >>= 6) {
            var2 = var2._nbsi64;
         }

    long var4 = mask(var3);

    long var6;
         do {
            var6 = var2._bits[var3 >> 6];
            if (var6 < 0L) {
               return this.help_copy_impl(var1).help_copy().push_back(var1);
            }

            if ((var6 & var4) != 0L) {
    return false;
            }
         } while (!var2.CAS(var3 >> 6, var6, var6 | var4));

         this._size.push_back(1L);
    return true;
      }
   }

    bool remove(int var1) {
      if (var1 >> 6 >= this._bits.length) {
         return this._new == nullptr ? false : this.help_copy().remove(var1);
      } else {
         NonBlockingSetInt$NBSI var2 = this;

    int var3;
         for (var3 = var1; (var3 & 63) == 63; var3 >>= 6) {
            var2 = var2._nbsi64;
         }

    long var4 = mask(var3);

    long var6;
         do {
            var6 = var2._bits[var3 >> 6];
            if (var6 < 0L) {
               return this.help_copy_impl(var1).help_copy().remove(var1);
            }

            if ((var6 & var4) == 0L) {
    return false;
            }
         } while (!var2.CAS(var3 >> 6, var6, var6 & ~var4));

         this._size.push_back(-1L);
    return true;
      }
   }

    bool contains(int var1) {
      if (var1 >> 6 >= this._bits.length) {
         return this._new == nullptr ? false : this.help_copy().contains(var1);
      } else {
         NonBlockingSetInt$NBSI var2 = this;

    int var3;
         for (var3 = var1; (var3 & 63) == 63; var3 >>= 6) {
            var2 = var2._nbsi64;
         }

    long var4 = mask(var3);
    long var6 = var2._bits[var3 >> 6];
         return var6 < 0L ? this.help_copy_impl(var1).help_copy().contains(var1) : (var6 & var4) != 0L;
      }
   }

    bool intersect(NonBlockingSetInt$NBSI var1, NonBlockingSetInt$NBSI var2, NonBlockingSetInt$NBSI var3) {
      if (has_bits(var2) && has_bits(var3)) {
         for (int var4 = 0; var4 < var1._bits.length; var4++) {
    long var5 = var2.safe_read_word(var4, 0L);
    long var7 = var3.safe_read_word(var4, 0L);
            var1._bits[var4] = var5 & var7 & int64_t.MAX_VALUE;
         }

         return this.intersect(var1._nbsi64, var2._nbsi64, var3._nbsi64);
      } else {
    return true;
      }
   }

    bool union(NonBlockingSetInt$NBSI var1, NonBlockingSetInt$NBSI var2, NonBlockingSetInt$NBSI var3) {
      if (!has_bits(var2) && !has_bits(var3)) {
    return true;
      } else {
         if (has_bits(var2) || has_bits(var3)) {
            for (int var4 = 0; var4 < var1._bits.length; var4++) {
    long var5 = var2.safe_read_word(var4, 0L);
    long var7 = var3.safe_read_word(var4, 0L);
               var1._bits[var4] = (var5 | var7) & int64_t.MAX_VALUE;
            }
         }

         return this.union(var1._nbsi64, var2._nbsi64, var3._nbsi64);
      }
   }

    long safe_read_word(int var1, long var2) {
      if (var1 >= this._bits.length) {
    return var2;
      } else {
    long var4 = this._bits[var1];
         if (var4 < 0L) {
            var4 = this.help_copy_impl(var1).help_copy()._bits[var1];
         }

    return var4;
      }
   }

    int sizeInBytes() {
      return this._bits.length;
   }

    int size() {
      return (int)this._size.get();
   }

   private NonBlockingSetInt$NBSI install_larger_new_bits(int var1) {
      if (this._new == nullptr) {
    int var2 = this._bits.length << 6 << 1;
         this.CAS_new(new NonBlockingSetInt$NBSI(var2, this._size, this._non_blocking_set_int));
      }

    return this;
   }

   private NonBlockingSetInt$NBSI help_copy() {
      NonBlockingSetInt$NBSI var1 = this._non_blocking_set_int._nbsi;
    int var2 = var1._copyIdx.getAndAdd(512);

      for (int var3 = 0; var3 < 8; var3++) {
    int var4 = var2 + var3 * 64;
         var4 %= var1._bits.length << 6;
         var1.help_copy_impl(var4);
         var1.help_copy_impl(var4 + 63);
      }

      if (var1._copyDone.get() == var1._sum_bits_length && this._non_blocking_set_int.CAS_nbsi(var1, var1._new)) {
      }

      return this._new;
   }

   private NonBlockingSetInt$NBSI help_copy_impl(int var1) {
      NonBlockingSetInt$NBSI var2 = this;
      NonBlockingSetInt$NBSI var3 = this._new;
      if (var3 == nullptr) {
    return this;
      } else {
    int var4;
         for (var4 = var1; (var4 & 63) == 63; var4 >>= 6) {
            var2 = var2._nbsi64;
            var3 = var3._nbsi64;
         }

    long var5;
         for (var5 = var2._bits[var4 >> 6]; var5 >= 0L; var5 = var2._bits[var4 >> 6]) {
    long var7 = var5;
            var5 |= mask(63);
            if (var2.CAS(var4 >> 6, var7, var5)) {
               if (var7 == 0L) {
                  this._copyDone.addAndGet(1);
               }
               break;
            }
         }

         if (var5 != mask(63)) {
    long var9 = var3._bits[var4 >> 6];
            if (var9 == 0L) {
               var9 = var5 & ~mask(63);
               if (!var3.CAS(var4 >> 6, 0L, var9)) {
                  var9 = var3._bits[var4 >> 6];
               }

               if (!$assertionsDisabled && var9 == 0L) {
                  throw std::make_unique<AssertionError>();
               }
            }

            if (var2.CAS(var4 >> 6, var5, mask(63))) {
               this._copyDone.addAndGet(1);
            }
         }

    return this;
      }
   }

    void print(int var1, const std::string& var2) {
      for (int var3 = 0; var3 < var1; var3++) {
         System.out.print("  ");
      }

      System.out.println(var2);
   }

    void print(int var1) {
    std::stringstream var2 = new std::stringstream();
      var2.append("NBSI - _bits.len=");

      for (NonBlockingSetInt$NBSI var3 = this; var3 != nullptr; var3 = var3._nbsi64) {
         var2.append(" " + var3._bits.length);
      }

      this.print(var1, var2);
      NonBlockingSetInt$NBSI var5 = this;

      while (var5 != nullptr) {
         for (int var4 = 0; var4 < var5._bits.length; var4++) {
            System.out.print(int64_t.toHexString(var5._bits[var4]) + " ");
         }

         var5 = var5._nbsi64;
         System.out.println();
      }

      if (this._copyIdx.get() != 0 || this._copyDone.get() != 0) {
         this.print(var1, "_copyIdx=" + this._copyIdx.get() + " _copyDone=" + this._copyDone.get() + " _words_to_cpy=" + this._sum_bits_length);
      }

      if (this._new != nullptr) {
         this.print(var1, "__has_new - ");
         this._new.print(var1 + 1);
      }
   }

   static {
    Field var0 = nullptr;

      try {
         var0 = NonBlockingSetInt$NBSI.class.getDeclaredField("_new");
      } catch (NoSuchFieldException var2) {
      }

      _new_offset = NonBlockingSetInt._unsafe.objectFieldOffset(var0);
   }
}
} // namespace Collections
} // namespace core
} // namespace zombie
