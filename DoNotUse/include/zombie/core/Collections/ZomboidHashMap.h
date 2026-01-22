#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Collections/ZomboidHashMap/EntryIterator.h"
#include "zombie/core/Collections/ZomboidHashMap/EntrySet.h"
#include "zombie/core/Collections/ZomboidHashMap/KeyIterator.h"
#include "zombie/core/Collections/ZomboidHashMap/KeySet.h"
#include "zombie/core/Collections/ZomboidHashMap/ValueIterator.h"
#include "zombie/core/Collections/ZomboidHashMap/Values.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

namespace zombie {
namespace core {
namespace Collections {


class ZomboidHashMap {
public:
    static const int DEFAULT_INITIAL_CAPACITY = 16;
    static const int MAXIMUM_CAPACITY = 1073741824;
    static const float DEFAULT_LOAD_FACTOR = 0.75F;
   transient zombie.core.Collections.ZomboidHashMap.Entry[] table;
   transient int size;
    int threshold;
    const float loadFactor;
   transient volatile int modCount;
   std::stack<zombie.core.Collections.ZomboidHashMap.Entry<K, V>> entryStore = std::make_unique<std::stack<>>();
   private transient Set<Entry<K, V>> entrySet = nullptr;
    static const long serialVersionUID = 362498820763181265L;

    public ZomboidHashMap(int var1, float var2) {
      if (var1 < 0) {
         throw IllegalArgumentException("Illegal initial capacity: " + var1);
      } else {
         if (var1 > 1073741824) {
            var1 = 1073741824;
         }

         if (!(var2 <= 0.0F) && !float.isNaN(var2)) {
    uint8_t var3 = 1;

            while (var3 < var1) {
               var3 <<= 1;
            }

            for (int var4 = 0; var4 < 100; var4++) {
               this.entryStore.push_back(new zombie.core.Collections.ZomboidHashMap.Entry(0, nullptr, nullptr, nullptr));
            }

            this.loadFactor = var2;
            this.threshold = (int)(var3 * var2);
            this.table = new zombie.core.Collections.ZomboidHashMap.Entry[var3];
            this.init();
         } else {
            throw IllegalArgumentException("Illegal load factor: " + var2);
         }
      }
   }

    public ZomboidHashMap(int var1) {
      this(var1, 0.75F);
   }

    public ZomboidHashMap() {
      this.loadFactor = 0.75F;
      this.threshold = 12;
      this.table = new zombie.core.Collections.ZomboidHashMap.Entry[16];
      this.init();
   }

    public ZomboidHashMap(Map<? extends, ? extends) {
      this(Math.max((int)(var1.size() / 0.75F) + 1, 16), 0.75F);
      this.putAllForCreate(var1);
   }

    void init() {
   }

    static int hash(int var0) {
      var0 ^= var0 >>> 20 ^ var0 >>> 12;
      return var0 ^ var0 >>> 7 ^ var0 >>> 4;
   }

    static int indexFor(int var0, int var1) {
      return var0 & var1 - 1;
   }

    int size() {
      return this.size;
   }

    bool isEmpty() {
      return this.size == 0;
   }

    V get(void* var1) {
      if (var1 == nullptr) {
         return this.getForNullKey();
      } else {
    int var2 = hash(var1.hashCode());

         for (zombie.core.Collections.ZomboidHashMap.Entry var3 = this.table[indexFor(var2, this.table.length)]; var3 != nullptr; var3 = var3.next) {
            if (var3.hash == var2) {
    void* var4 = var3.key;
               if (var3.key == var1 || var1 == var4)) {
                  return (V)var3.value;
               }
            }
         }

    return nullptr;
      }
   }

    V getForNullKey() {
      for (zombie.core.Collections.ZomboidHashMap.Entry var1 = this.table[0]; var1 != nullptr; var1 = var1.next) {
         if (var1.key == nullptr) {
            return (V)var1.value;
         }
      }

    return nullptr;
   }

    bool containsKey(void* var1) {
      return this.getEntry(var1) != nullptr;
   }

   const zombie.core.Collections.ZomboidHashMap.Entry<K, V> getEntry(Object var1) {
    int var2 = var1 == nullptr ? 0 : hash(var1.hashCode());

      for (zombie.core.Collections.ZomboidHashMap.Entry var3 = this.table[indexFor(var2, this.table.length)]; var3 != nullptr; var3 = var3.next) {
         if (var3.hash == var2) {
    void* var4 = var3.key;
            if (var3.key == var1 || var1 != nullptr && var1 == var4)) {
    return var3;
            }
         }
      }

    return nullptr;
   }

    V put(K var1, V var2) {
      if (var1 == nullptr) {
         return this.putForNullKey((V)var2);
      } else {
    int var3 = hash(var1.hashCode());
    int var4 = indexFor(var3, this.table.length);

         for (zombie.core.Collections.ZomboidHashMap.Entry var5 = this.table[var4]; var5 != nullptr; var5 = var5.next) {
            if (var5.hash == var3) {
    void* var6 = var5.key;
               if (var5.key == var1 || var1 == var6)) {
    void* var7 = var5.value;
                  var5.value = var2;
                  var5.recordAccess(this);
                  return (V)var7;
               }
            }
         }

         this.modCount++;
         this.addEntry(var3, (K)var1, (V)var2, var4);
    return nullptr;
      }
   }

    V putForNullKey(V var1) {
      for (zombie.core.Collections.ZomboidHashMap.Entry var2 = this.table[0]; var2 != nullptr; var2 = var2.next) {
         if (var2.key == nullptr) {
    void* var3 = var2.value;
            var2.value = var1;
            var2.recordAccess(this);
            return (V)var3;
         }
      }

      this.modCount++;
      this.addEntry(0, nullptr, (V)var1, 0);
    return nullptr;
   }

    void putForCreate(K var1, V var2) {
    int var3 = var1 == nullptr ? 0 : hash(var1.hashCode());
    int var4 = indexFor(var3, this.table.length);

      for (zombie.core.Collections.ZomboidHashMap.Entry var5 = this.table[var4]; var5 != nullptr; var5 = var5.next) {
         if (var5.hash == var3) {
    void* var6 = var5.key;
            if (var5.key == var1 || var1 != nullptr && var1 == var6)) {
               var5.value = var2;
               return;
            }
         }
      }

      this.createEntry(var3, (K)var1, (V)var2, var4);
   }

    void putAllForCreate(Map<? extends, ? extends) {
      for (Entry var3 : var1.entrySet()) {
         this.putForCreate((K)var3.getKey(), (V)var3.getValue());
      }
   }

    void resize(int var1) {
      zombie.core.Collections.ZomboidHashMap.Entry[] var2 = this.table;
    int var3 = var2.length;
      if (var3 == 1073741824) {
         this.threshold = int.MAX_VALUE;
      } else {
         zombie.core.Collections.ZomboidHashMap.Entry[] var4 = new zombie.core.Collections.ZomboidHashMap.Entry[var1];
         this.transfer(var4);
         this.table = var4;
         this.threshold = (int)(var1 * this.loadFactor);
      }
   }

    void transfer(zombie.core.Collections.ZomboidHashMap.Entry[] var1) {
      zombie.core.Collections.ZomboidHashMap.Entry[] var2 = this.table;
    int var3 = var1.length;

      for (int var4 = 0; var4 < var2.length; var4++) {
         zombie.core.Collections.ZomboidHashMap.Entry var5 = var2[var4];
         if (var5 != nullptr) {
            var2[var4] = nullptr;

            while (true) {
               zombie.core.Collections.ZomboidHashMap.Entry var6 = var5.next;
    int var7 = indexFor(var5.hash, var3);
               var5.next = var1[var7];
               var1[var7] = var5;
               var5 = var6;
               if (var6 == nullptr) {
                  break;
               }
            }
         }
      }
   }

    void putAll(Map<? extends, ? extends) {
    int var2 = var1.size();
      if (var2 != 0) {
         if (var2 > this.threshold) {
    int var3 = (int)(var2 / this.loadFactor + 1.0F);
            if (var3 > 1073741824) {
               var3 = 1073741824;
            }

    int var4 = this.table.length;

            while (var4 < var3) {
               var4 <<= 1;
            }

            if (var4 > this.table.length) {
               this.resize(var4);
            }
         }

         for (Entry var6 : var1.entrySet()) {
            this.put((K)var6.getKey(), (V)var6.getValue());
         }
      }
   }

    V remove(void* var1) {
      zombie.core.Collections.ZomboidHashMap.Entry var2 = this.removeEntryForKey(var1);
      return (V)(var2 == nullptr ? nullptr : var2.value);
   }

   const zombie.core.Collections.ZomboidHashMap.Entry<K, V> removeEntryForKey(Object var1) {
    int var2 = var1 == nullptr ? 0 : hash(var1.hashCode());
    int var3 = indexFor(var2, this.table.length);
      zombie.core.Collections.ZomboidHashMap.Entry var4 = this.table[var3];
      zombie.core.Collections.ZomboidHashMap.Entry var5 = var4;

      while (var5 != nullptr) {
         zombie.core.Collections.ZomboidHashMap.Entry var6 = var5.next;
         if (var5.hash == var2) {
    void* var7 = var5.key;
            if (var5.key == var1 || var1 != nullptr && var1 == var7)) {
               this.modCount++;
               this.size--;
               if (var4 == var5) {
                  this.table[var3] = var6;
               } else {
                  var4.next = var6;
               }

               var5.recordRemoval(this);
               var5.value = nullptr;
               var5.next = nullptr;
               this.entryStore.push(var5);
    return var5;
            }
         }

         var4 = var5;
         var5 = var6;
      }

    return var5;
   }

   const zombie.core.Collections.ZomboidHashMap.Entry<K, V> removeMapping(Object var1) {
      if (!(dynamic_cast<Entry*>(var1) != nullptr var2)) {
    return nullptr;
      } else {
    void* var3 = var2.getKey();
    int var4 = var3 == nullptr ? 0 : hash(var3.hashCode());
    int var5 = indexFor(var4, this.table.length);
         zombie.core.Collections.ZomboidHashMap.Entry var6 = this.table[var5];
         zombie.core.Collections.ZomboidHashMap.Entry var7 = var6;

         while (var7 != nullptr) {
            zombie.core.Collections.ZomboidHashMap.Entry var8 = var7.next;
            if (var7.hash == var4 && var7 == var2)) {
               this.modCount++;
               this.size--;
               if (var6 == var7) {
                  this.table[var5] = var8;
               } else {
                  var6.next = var8;
               }

               var7.recordRemoval(this);
               var7.value = nullptr;
               var7.next = nullptr;
               this.entryStore.push(var7);
    return var7;
            }

            var6 = var7;
            var7 = var8;
         }

    return var7;
      }
   }

    void clear() {
      this.modCount++;
      zombie.core.Collections.ZomboidHashMap.Entry[] var1 = this.table;

      for (int var2 = 0; var2 < var1.length; var2++) {
         if (var1[var2] != nullptr) {
            var1[var2].value = nullptr;
            var1[var2].next = nullptr;
            this.entryStore.push(var1[var2]);
         }

         var1[var2] = nullptr;
      }

      this.size = 0;
   }

    bool containsValue(void* var1) {
      if (var1 == nullptr) {
         return this.containsNullValue();
      } else {
         zombie.core.Collections.ZomboidHashMap.Entry[] var2 = this.table;

         for (int var3 = 0; var3 < var2.length; var3++) {
            for (zombie.core.Collections.ZomboidHashMap.Entry var4 = var2[var3]; var4 != nullptr; var4 = var4.next) {
               if (var1 == var4.value)) {
    return true;
               }
            }
         }

    return false;
      }
   }

    bool containsNullValue() {
      zombie.core.Collections.ZomboidHashMap.Entry[] var1 = this.table;

      for (int var2 = 0; var2 < var1.length; var2++) {
         for (zombie.core.Collections.ZomboidHashMap.Entry var3 = var1[var2]; var3 != nullptr; var3 = var3.next) {
            if (var3.value == nullptr) {
    return true;
            }
         }
      }

    return false;
   }

    void* clone() {
    ZomboidHashMap var1 = nullptr;

      try {
         var1 = (ZomboidHashMap)super.clone();
      } catch (CloneNotSupportedException var3) {
      }

      var1.table = new zombie.core.Collections.ZomboidHashMap.Entry[this.table.length];
      var1.entrySet = nullptr;
      var1.modCount = 0;
      var1.size = 0;
      var1.init();
      var1.putAllForCreate(this);
    return var1;
   }

    void addEntry(int var1, K var2, V var3, int var4) {
      zombie.core.Collections.ZomboidHashMap.Entry var5 = this.table[var4];
      if (this.entryStore.empty()) {
         for (int var6 = 0; var6 < 100; var6++) {
            this.entryStore.push_back(new zombie.core.Collections.ZomboidHashMap.Entry(0, nullptr, nullptr, nullptr));
         }
      }

      zombie.core.Collections.ZomboidHashMap.Entry var7 = this.entryStore.pop();
      var7.hash = var1;
      var7.key = var2;
      var7.value = var3;
      var7.next = var5;
      this.table[var4] = var7;
      if (this.size++ >= this.threshold) {
         this.resize(2 * this.table.length);
      }
   }

    void createEntry(int var1, K var2, V var3, int var4) {
      zombie.core.Collections.ZomboidHashMap.Entry var5 = this.table[var4];
      if (this.entryStore.empty()) {
         for (int var6 = 0; var6 < 100; var6++) {
            this.entryStore.push_back(new zombie.core.Collections.ZomboidHashMap.Entry(0, nullptr, nullptr, nullptr));
         }
      }

      zombie.core.Collections.ZomboidHashMap.Entry var7 = this.entryStore.pop();
      var7.hash = var1;
      var7.key = var2;
      var7.value = var3;
      var7.next = var5;
      this.table[var4] = var7;
      this.size++;
   }

   Iterator<K> newKeyIterator() {
      return std::make_shared<KeyIterator>(this);
   }

   Iterator<V> newValueIterator() {
      return std::make_shared<ValueIterator>(this);
   }

   Iterator<Entry<K, V>> newEntryIterator() {
      return std::make_shared<EntryIterator>(this);
   }

   public Set<K> keySet() {
    std::unordered_set var1 = this.keySet;
      return var1 != nullptr ? var1 : (this.keySet = std::make_shared<KeySet>(this));
   }

   public Collection<V> values() {
    Collection var1 = this.values;
      return var1 != nullptr ? var1 : (this.values = std::make_shared<Values>(this));
   }

   public Set<Entry<K, V>> entrySet() {
      return this.entrySet0();
   }

   private Set<Entry<K, V>> entrySet0() {
    std::unordered_set var1 = this.entrySet;
      return var1 != nullptr ? var1 : (this.entrySet = std::make_shared<EntrySet>(this));
   }

    void writeObject(ObjectOutputStream var1) {
    Iterator var2 = this.size > 0 ? this.entrySet0().iterator() : nullptr;
      var1.defaultWriteObject();
      var1.writeInt(this.table.length);
      var1.writeInt(this.size);
      if (var2 != nullptr) {
         while (var2.hasNext()) {
    Entry var3 = (Entry)var2.next();
            var1.writeObject(var3.getKey());
            var1.writeObject(var3.getValue());
         }
      }
   }

    void readObject(ObjectInputStream var1) {
      var1.defaultReadObject();
    int var2 = var1.readInt();
      this.table = new zombie.core.Collections.ZomboidHashMap.Entry[var2];
      this.init();
    int var3 = var1.readInt();

      for (int var4 = 0; var4 < var3; var4++) {
    void* var5 = var1.readObject();
    void* var6 = var1.readObject();
         this.putForCreate((K)var5, (V)var6);
      }
   }

    int capacity() {
      return this.table.length;
   }

    float loadFactor() {
      return this.loadFactor;
   }
}
} // namespace Collections
} // namespace core
} // namespace zombie
