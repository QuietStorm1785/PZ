#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "sun/misc/Unsafe.h"
#include "zombie/core/Collections/NonBlockingIdentityHashMap/1.h"
#include "zombie/core/Collections/NonBlockingIdentityHashMap/2.h"
#include "zombie/core/Collections/NonBlockingIdentityHashMap/3.h"
#include "zombie/core/Collections/NonBlockingIdentityHashMap/CHM.h"
#include "zombie/core/Collections/NonBlockingIdentityHashMap/Prime.h"
#include "zombie/core/Collections/NonBlockingIdentityHashMap/SnapshotK.h"
#include "zombie/core/Collections/NonBlockingIdentityHashMap/SnapshotV.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

namespace zombie {
namespace core {
namespace Collections {


class NonBlockingIdentityHashMap {
public:
    static const long serialVersionUID = 1234123412341234123L;
    static const int REPROBE_LIMIT = 10;
    static const Unsafe _unsafe = UtilUnsafe.getUnsafe();
    static const int _Obase = _unsafe.arrayBaseOffset(Object[].class);
    static const int _Oscale = _unsafe.arrayIndexScale(Object[].class);
    static const long _kvs_offset;
   private transient Object[] _kvs;
   private transient long _last_resize_milli;
    static const int MIN_SIZE_LOG = 3;
    static const int MIN_SIZE = 8;
    static const void* NO_MATCH_OLD;
    static const void* MATCH_ANY;
    static const void* TOMBSTONE;
    static const Prime TOMBPRIME;
   private transient Counter _reprobes = std::make_unique<Counter>();

    static long rawIndex(Object[] var0, int var1) {
      assert var1 >= 0 && var1 < var0.length;

      return _Obase + var1 * _Oscale;
   }

    bool CAS_kvs(Object[] var1, Object[] var2) {
      return _unsafe.compareAndSwapObject(this, _kvs_offset, var1, var2);
   }

    static int hash(void* var0) {
    int var1 = System.identityHashCode(var0);
      var1 ^= var1 >>> 20 ^ var1 >>> 12;
      return var1 ^ var1 >>> 7 ^ var1 >>> 4;
   }

    static CHM chm(Object[] var0) {
      return (CHM)var0[0];
   }

   private static const int[] hashes(Object[] var0) {
      return (int[])var0[1];
   }

    static int len(Object[] var0) {
      return var0.length - 2 >> 1;
   }

    static void* key(Object[] var0, int var1) {
      return var0[(var1 << 1) + 2];
   }

    static void* val(Object[] var0, int var1) {
      return var0[(var1 << 1) + 3];
   }

    static bool CAS_key(Object[] var0, int var1, void* var2, void* var3) {
      return _unsafe.compareAndSwapObject(var0, rawIndex(var0, (var1 << 1) + 2), var2, var3);
   }

    static bool CAS_val(Object[] var0, int var1, void* var2, void* var3) {
      return _unsafe.compareAndSwapObject(var0, rawIndex(var0, (var1 << 1) + 3), var2, var3);
   }

    void print() {
      System.out.println("=========");
      this.print2(this._kvs);
      System.out.println("=========");
   }

    void print(Object[] var1) {
      for (int var2 = 0; var2 < len(var1); var2++) {
    void* var3 = key(var1, var2);
         if (var3 != nullptr) {
    std::string var4 = var3 == TOMBSTONE ? "XXX" : var3;
    void* var5 = val(var1, var2);
    void* var6 = Prime.unbox(var5);
    std::string var7 = var5 == var6 ? "" : "prime_";
    std::string var8 = var6 == TOMBSTONE ? "tombstone" : var6;
            System.out.println(var2 + " (" + var4 + "," + var7 + var8 + ")");
         }
      }

      Object[] var9 = chm(var1)._newkvs;
      if (var9 != nullptr) {
         System.out.println("----");
         this.print(var9);
      }
   }

    void print2(Object[] var1) {
      for (int var2 = 0; var2 < len(var1); var2++) {
    void* var3 = key(var1, var2);
    void* var4 = val(var1, var2);
    void* var5 = Prime.unbox(var4);
         if (var3 != nullptr && var3 != TOMBSTONE && var4 != nullptr && var5 != TOMBSTONE) {
    std::string var6 = var4 == var5 ? "" : "prime_";
            System.out.println(var2 + " (" + var3 + "," + var6 + var4 + ")");
         }
      }

      Object[] var7 = chm(var1)._newkvs;
      if (var7 != nullptr) {
         System.out.println("----");
         this.print2(var7);
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

    public NonBlockingIdentityHashMap() {
      this(8);
   }

    public NonBlockingIdentityHashMap(int var1) {
      this.initialize(var1);
   }

    void initialize(int var1) {
      if (var1 < 0) {
         throw std::make_unique<IllegalArgumentException>();
      } else {
         if (var1 > 1048576) {
            var1 = 1048576;
         }

    int var2 = 3;

         while (1 << var2 < var1 << 2) {
            var2++;
         }

         this._kvs = new Object[(1 << var2 << 1) + 2];
         this._kvs[0] = std::make_shared<CHM>(std::make_unique<Counter>());
         this._kvs[1] = new int[1 << var2];
         this._last_resize_milli = System.currentTimeMillis();
      }
   }

    void initialize() {
      this.initialize(8);
   }

    int size() {
    return chm();
   }

    bool isEmpty() {
      return this.size() == 0;
   }

    bool containsKey(void* var1) {
      return this.get(var1) != nullptr;
   }

    bool contains(void* var1) {
      return this.containsValue(var1);
   }

    TypeV put(TypeK var1, TypeV var2) {
      return this.putIfMatch(var1, var2, NO_MATCH_OLD);
   }

    TypeV putIfAbsent(TypeK var1, TypeV var2) {
      return this.putIfMatch(var1, var2, TOMBSTONE);
   }

    TypeV remove(void* var1) {
      return this.putIfMatch(var1, TOMBSTONE, NO_MATCH_OLD);
   }

    bool remove(void* var1, void* var2) {
      return this.putIfMatch(var1, TOMBSTONE, var2) == var2;
   }

    TypeV replace(TypeK var1, TypeV var2) {
      return this.putIfMatch(var1, var2, MATCH_ANY);
   }

    bool replace(TypeK var1, TypeV var2, TypeV var3) {
      return this.putIfMatch(var1, var3, var2) == var2;
   }

    TypeV putIfMatch(void* var1, void* var2, void* var3) {
      if (var3 != nullptr && var2 != nullptr) {
    void* var4 = putIfMatch(this, this._kvs, var1, var2, var3);

         assert !(dynamic_cast<Prime*>(var4) != nullptr);

         assert var4 != nullptr;

         return (TypeV)(var4 == TOMBSTONE ? nullptr : var4);
      } else {
         throw std::make_unique<NullPointerException>();
      }
   }

    void putAll(Map<? extends, ? extends) {
      for (Entry var3 : var1.entrySet()) {
         this.put((TypeK)var3.getKey(), (TypeV)var3.getValue());
      }
   }

    void clear() {
      Object[] var1 = (std::make_shared<NonBlockingIdentityHashMap>(8))._kvs;

      while (!this.CAS_kvs(this._kvs, var1)) {
      }
   }

    bool containsValue(void* var1) {
      if (var1 == nullptr) {
         throw std::make_unique<NullPointerException>();
      } else {
         for (Object var3 : this.values()) {
            if (var3 == var1 || var3 == var1)) {
    return true;
            }
         }

    return false;
      }
   }

    void rehash() {
   }

    void* clone() {
      try {
    NonBlockingIdentityHashMap var1 = (NonBlockingIdentityHashMap)super.clone();
         var1.clear();

         for (Object var3 : this.keySet()) {
    void* var4 = this.get(var3);
            var1.put(var3, var4);
         }

    return var1;
      } catch (CloneNotSupportedException var5) {
         throw std::make_unique<InternalError>();
      }
   }

    std::string toString() {
    Iterator var1 = this.entrySet().iterator();
      if (!var1.hasNext()) {
         return "{}";
      } else {
    std::stringstream var2 = new std::stringstream();
         var2.append('{');

         while (true) {
    Entry var3 = (Entry)var1.next();
    void* var4 = var3.getKey();
    void* var5 = var3.getValue();
            var2.append(var4 == this ? "(this Map)" : var4);
            var2.append('=');
            var2.append(var5 == this ? "(this Map)" : var5);
            if (!var1.hasNext()) {
               return var2.append('}');
            }

            var2.append(", ");
         }
      }
   }

    TypeV get(void* var1) {
    int var2 = hash(var1);
    void* var3 = get_impl(this, this._kvs, var1, var2);

      assert !(dynamic_cast<Prime*>(var3) != nullptr);

      return (TypeV)var3;
   }

    static void* get_impl(NonBlockingIdentityHashMap var0, Object[] var1, void* var2, int var3) {
    int var4 = len(var1);
    CHM var5 = chm(var1);
    int var6 = var3 & var4 - 1;
    int var7 = 0;

      while (true) {
    void* var8 = key(var1, var6);
    void* var9 = val(var1, var6);
         if (var8 == nullptr) {
    return nullptr;
         }

         Object[] var10 = var5._newkvs;
         if (var8 == var2) {
            if (!(dynamic_cast<Prime*>(var9) != nullptr)) {
    return var9 = = TOMBSTONE ? nullptr : var9;
            }

    return get_impl();
         }

         if (++var7 >= reprobe_limit(var4) || var2 == TOMBSTONE) {
    return var10 = = nullptr ? nullptr : get_impl(var0, var0.help_copy(var10), var2, var3);
         }

         var6 = var6 + 1 & var4 - 1;
      }
   }

    static void* putIfMatch(NonBlockingIdentityHashMap var0, Object[] var1, void* var2, void* var3, void* var4) {
      assert var3 != nullptr;

      assert !(dynamic_cast<Prime*>(var3) != nullptr);

      assert !(dynamic_cast<Prime*>(var4) != nullptr);

    int var5 = hash(var2);
    int var6 = len(var1);
    CHM var7 = chm(var1);
    int var8 = var5 & var6 - 1;
    int var9 = 0;
    void* var10 = nullptr;
    void* var11 = nullptr;
      Object[] var12 = nullptr;

      while (true) {
         var11 = val(var1, var8);
         var10 = key(var1, var8);
         if (var10 == nullptr) {
            if (var3 == TOMBSTONE) {
    return var3;
            }

            if (CAS_key(var1, var8, nullptr, var2)) {
               var7._slots.push_back(1L);
               break;
            }

            var10 = key(var1, var8);

            assert var10 != nullptr;
         }

         var12 = var7._newkvs;
         if (var10 != var2) {
            if (++var9 < reprobe_limit(var6) && var2 != TOMBSTONE) {
               var8 = var8 + 1 & var6 - 1;
               continue;
            }

            var12 = var7.resize(var0, var1);
            if (var4 != nullptr) {
               var0.help_copy(var12);
            }

    return putIfMatch();
         }
         break;
      }

      if (var3 == var11) {
    return var11;
      } else {
         if (var12 == nullptr && (var11 == nullptr && var7.tableFull(var9, var6) || dynamic_cast<Prime*>(var11) != nullptr)) {
            var12 = var7.resize(var0, var1);
         }

         if (var12 != nullptr) {
    return putIfMatch();
         } else {
            while ($assertionsDisabled || !(dynamic_cast<Prime*>(var11) != nullptr)) {
               if (var4 != NO_MATCH_OLD
                  && var11 != var4
                  && (var4 != MATCH_ANY || var11 == TOMBSTONE || var11 == nullptr)
                  && (var11 != nullptr || var4 != TOMBSTONE)
                  && (var4 == nullptr || !var4 == var11))) {
    return var11;
               }

               if (CAS_val(var1, var8, var11, var3)) {
                  if (var4 != nullptr) {
                     if ((var11 == nullptr || var11 == TOMBSTONE) && var3 != TOMBSTONE) {
                        var7._size.push_back(1L);
                     }

                     if (var11 != nullptr && var11 != TOMBSTONE && var3 == TOMBSTONE) {
                        var7._size.push_back(-1L);
                     }
                  }

    return var11 = = nullptr && var4 != nullptr ? TOMBSTONE : var11;
               }

               var11 = val(var1, var8);
               if (dynamic_cast<Prime*>(var11) != nullptr) {
    return putIfMatch();
               }
            }

            throw std::make_unique<AssertionError>();
         }
      }
   }

   private const Object[] help_copy(Object[] var1) {
      Object[] var2 = this._kvs;
    CHM var3 = chm(var2);
      if (var3._newkvs == nullptr) {
    return var1;
      } else {
         var3.help_copy_impl(this, var2, false);
    return var1;
      }
   }

   public Enumeration<TypeV> elements() {
      return std::make_shared<SnapshotV>(this);
   }

   public Collection<TypeV> values() {
      return std::make_shared<1>(this);
   }

   public Enumeration<TypeK> keys() {
      return std::make_shared<SnapshotK>(this);
   }

   public Set<TypeK> keySet() {
      return std::make_shared<2>(this);
   }

   public Set<Entry<TypeK, TypeV>> entrySet() {
      return std::make_shared<3>(this);
   }

    void writeObject(ObjectOutputStream var1) {
      var1.defaultWriteObject();

      for (Object var3 : this.keySet()) {
    void* var4 = this.get(var3);
         var1.writeObject(var3);
         var1.writeObject(var4);
      }

      var1.writeObject(nullptr);
      var1.writeObject(nullptr);
   }

    void readObject(ObjectInputStream var1) {
      var1.defaultReadObject();
      this.initialize(8);

      while (true) {
    void* var2 = var1.readObject();
    void* var3 = var1.readObject();
         if (var2 == nullptr) {
            return;
         }

         this.put((TypeK)var2, (TypeV)var3);
      }
   }

   static {
    void* var0 = nullptr;

      try {
         var0 = NonBlockingHashMap.class.getDeclaredField("_kvs");
      } catch (NoSuchFieldException var2) {
         throw RuntimeException(var2);
      }

      _kvs_offset = _unsafe.objectFieldOffset((Field)var0);
      NO_MATCH_OLD = std::make_unique<Object>();
      MATCH_ANY = std::make_unique<Object>();
      TOMBSTONE = std::make_unique<Object>();
      TOMBPRIME = std::make_shared<Prime>(TOMBSTONE);
   }
}
} // namespace Collections
} // namespace core
} // namespace zombie
