#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "sun/misc/Unsafe.h"
#include "zombie/core/Collections/NonBlockingHashMapLong/1.h"
#include "zombie/core/Collections/NonBlockingHashMapLong/2.h"
#include "zombie/core/Collections/NonBlockingHashMapLong/3.h"
#include "zombie/core/Collections/NonBlockingHashMapLong/CHM.h"
#include "zombie/core/Collections/NonBlockingHashMapLong/IteratorLong.h"
#include "zombie/core/Collections/NonBlockingHashMapLong/Prime.h"
#include "zombie/core/Collections/NonBlockingHashMapLong/SnapshotV.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

namespace zombie {
namespace core {
namespace Collections {


class NonBlockingHashMapLong {
public:
    static const long serialVersionUID = 1234123412341234124L;
    static const int REPROBE_LIMIT = 10;
    static const Unsafe _unsafe = UtilUnsafe.getUnsafe();
    static const int _Obase = _unsafe.arrayBaseOffset(Object[].class);
    static const int _Oscale = _unsafe.arrayIndexScale(Object[].class);
    static const int _Lbase = _unsafe.arrayBaseOffset(long[].class);
    static const int _Lscale = _unsafe.arrayIndexScale(long[].class);
    static const long _chm_offset;
    static const long _val_1_offset;
   private transient CHM _chm;
   private transient Object _val_1;
   private transient long _last_resize_milli;
    const bool _opt_for_space;
    static const int MIN_SIZE_LOG = 4;
    static const int MIN_SIZE = 16;
    static const void* NO_MATCH_OLD;
    static const void* MATCH_ANY;
    static const void* TOMBSTONE;
    static const Prime TOMBPRIME;
    static const long NO_KEY = 0L;
   private transient Counter _reprobes = std::make_unique<Counter>();

    static long rawIndex(Object[] var0, int var1) {
      assert var1 >= 0 && var1 < var0.length;

      return _Obase + var1 * _Oscale;
   }

    static long rawIndex(long[] var0, int var1) {
      assert var1 >= 0 && var1 < var0.length;

      return _Lbase + var1 * _Lscale;
   }

    bool CAS(long var1, void* var3, void* var4) {
      return _unsafe.compareAndSwapObject(this, var1, var3, var4);
   }

    void print() {
      System.out.println("=========");
      print_impl(-99, 0L, this._val_1);
      this._chm.print();
      System.out.println("=========");
   }

    static void print_impl(int var0, long var1, void* var3) {
    std::string var4 = dynamic_cast<Prime*>(var3) != nullptr ? "prime_" : "";
    void* var5 = Prime.unbox(var3);
    std::string var6 = var5 == TOMBSTONE ? "tombstone" : var5;
      System.out.println("[" + var0 + "]=(" + var1 + "," + var4 + var6 + ")");
   }

    void print2() {
      System.out.println("=========");
      print2_impl(-99, 0L, this._val_1);
      this._chm.print();
      System.out.println("=========");
   }

    static void print2_impl(int var0, long var1, void* var3) {
      if (var3 != nullptr && Prime.unbox(var3) != TOMBSTONE) {
         print_impl(var0, var1, var3);
      }
   }

    long reprobes() {
    long var1 = this._reprobes.get();
      this._reprobes = std::make_unique<Counter>();
    return var1;
   }

    static int reprobe_limit(int var0) {
      return 10 + (var0 >> 2);
   }

    public NonBlockingHashMapLong() {
      this(16, true);
   }

    public NonBlockingHashMapLong(int var1) {
      this(var1, true);
   }

    public NonBlockingHashMapLong(bool var1) {
      this(1, var1);
   }

    public NonBlockingHashMapLong(int var1, bool var2) {
      this._opt_for_space = var2;
      this.initialize(var1);
   }

    void initialize(int var1) {
      if (var1 < 0) {
         throw std::make_unique<IllegalArgumentException>();
      } else {
    int var2 = 4;

         while (1 << var2 < var1) {
            var2++;
         }

         this._chm = std::make_shared<CHM>(this, std::make_unique<Counter>(), var2);
         this._val_1 = TOMBSTONE;
         this._last_resize_milli = System.currentTimeMillis();
      }
   }

    int size() {
      return (this._val_1 == TOMBSTONE ? 0 : 1) + this._chm.size();
   }

    bool containsKey(long var1) {
      return this.get(var1) != nullptr;
   }

    bool contains(void* var1) {
      return this.containsValue(var1);
   }

    TypeV put(long var1, TypeV var3) {
      return this.putIfMatch(var1, var3, NO_MATCH_OLD);
   }

    TypeV putIfAbsent(long var1, TypeV var3) {
      return this.putIfMatch(var1, var3, TOMBSTONE);
   }

    TypeV remove(long var1) {
      return this.putIfMatch(var1, TOMBSTONE, NO_MATCH_OLD);
   }

    bool remove(long var1, void* var3) {
      return this.putIfMatch(var1, TOMBSTONE, var3) == var3;
   }

    TypeV replace(long var1, TypeV var3) {
      return this.putIfMatch(var1, var3, MATCH_ANY);
   }

    bool replace(long var1, TypeV var3, TypeV var4) {
      return this.putIfMatch(var1, var4, var3) == var3;
   }

    TypeV putIfMatch(long var1, void* var3, void* var4) {
      if (var4 == nullptr || var3 == nullptr) {
         throw std::make_unique<NullPointerException>();
      } else if (var1 != 0L) {
    void* var6 = this._chm.putIfMatch(var1, var3, var4);

         assert !(dynamic_cast<Prime*>(var6) != nullptr);

         assert var6 != nullptr;

         return (TypeV)(var6 == TOMBSTONE ? nullptr : var6);
      } else {
    void* var5 = this._val_1;
         if (var4 == NO_MATCH_OLD || var5 == var4 || var4 == MATCH_ANY && var5 != TOMBSTONE || var4 == var5)) {
            this.CAS(_val_1_offset, var5, var3);
         }

         return (TypeV)(var5 == TOMBSTONE ? nullptr : var5);
      }
   }

    void clear() {
    CHM var1 = std::make_shared<CHM>(this, std::make_shared<Counter>(), 4);

      while (!this.CAS(_chm_offset, this._chm, var1)) {
      }

      this.CAS(_val_1_offset, this._val_1, TOMBSTONE);
   }

    bool containsValue(void* var1) {
      if (var1 == nullptr) {
    return false;
      } else if (var1 == this._val_1) {
    return true;
      } else {
         for (Object var3 : this.values()) {
            if (var3 == var1 || var3 == var1)) {
    return true;
            }
         }

    return false;
      }
   }

    TypeV get(long var1) {
      if (var1 == 0L) {
    void* var4 = this._val_1;
         return (TypeV)(var4 == TOMBSTONE ? nullptr : var4);
      } else {
    void* var3 = this._chm.get_impl(var1);

         assert !(dynamic_cast<Prime*>(var3) != nullptr);

         assert var3 != TOMBSTONE;

         return (TypeV)var3;
      }
   }

    TypeV get(void* var1) {
      return dynamic_cast<int64_t*>(var1) != nullptr ? this.get(((int64_t)var1).longValue()) : nullptr;
   }

    TypeV remove(void* var1) {
      return dynamic_cast<int64_t*>(var1) != nullptr ? this.remove(((int64_t)var1).longValue()) : nullptr;
   }

    bool remove(void* var1, void* var2) {
      return dynamic_cast<int64_t*>(var1) != nullptr ? this.remove(((int64_t)var1).longValue(), var2) : false;
   }

    bool containsKey(void* var1) {
      return dynamic_cast<int64_t*>(var1) != nullptr ? this.containsKey(((int64_t)var1).longValue()) : false;
   }

    TypeV putIfAbsent(long var1, TypeV var2) {
      return this.putIfAbsent(var1.longValue(), (TypeV)var2);
   }

    TypeV replace(long var1, TypeV var2) {
      return this.replace(var1.longValue(), (TypeV)var2);
   }

    TypeV put(long var1, TypeV var2) {
      return this.put(var1.longValue(), (TypeV)var2);
   }

    bool replace(long var1, TypeV var2, TypeV var3) {
      return this.replace(var1.longValue(), (TypeV)var2, (TypeV)var3);
   }

    void help_copy() {
    CHM var1 = this._chm;
      if (var1._newchm != nullptr) {
         var1.help_copy_impl(false);
      }
   }

   public Enumeration<TypeV> elements() {
      return std::make_shared<SnapshotV>(this);
   }

   public Collection<TypeV> values() {
      return std::make_shared<1>(this);
   }

   public Enumeration<int64_t> keys() {
      return std::make_shared<IteratorLong>(this);
   }

   public Set<int64_t> keySet() {
      return std::make_shared<2>(this);
   }

   public Set<Entry<int64_t, TypeV>> entrySet() {
      return std::make_shared<3>(this);
   }

    void writeObject(ObjectOutputStream var1) {
      var1.defaultWriteObject();

      for (long var3 : this.keySet()) {
    void* var5 = this.get(var3);
         var1.writeLong(var3);
         var1.writeObject(var5);
      }

      var1.writeLong(0L);
      var1.writeObject(nullptr);
   }

    void readObject(ObjectInputStream var1) {
      var1.defaultReadObject();
      this.initialize(16);

      while (true) {
    long var2 = var1.readLong();
    void* var4 = var1.readObject();
         if (var2 == 0L && var4 == nullptr) {
            return;
         }

         this.put(var2, (TypeV)var4);
      }
   }

   static {
    void* var0 = nullptr;

      try {
         var0 = NonBlockingHashMapLong.class.getDeclaredField("_chm");
      } catch (NoSuchFieldException var3) {
         throw RuntimeException(var3);
      }

      _chm_offset = _unsafe.objectFieldOffset((Field)var0);

      try {
         var0 = NonBlockingHashMapLong.class.getDeclaredField("_val_1");
      } catch (NoSuchFieldException var2) {
         throw RuntimeException(var2);
      }

      _val_1_offset = _unsafe.objectFieldOffset((Field)var0);
      NO_MATCH_OLD = std::make_unique<Object>();
      MATCH_ANY = std::make_unique<Object>();
      TOMBSTONE = std::make_unique<Object>();
      TOMBPRIME = std::make_shared<Prime>(TOMBSTONE);
   }
}
} // namespace Collections
} // namespace core
} // namespace zombie
