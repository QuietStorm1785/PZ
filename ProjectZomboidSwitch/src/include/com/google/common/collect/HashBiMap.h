#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Objects.h"
#include "com/google/common/collect/HashBiMap/1.h"
#include "com/google/common/collect/HashBiMap/BiEntry.h"
#include "com/google/common/collect/HashBiMap/Inverse.h"
#include "com/google/common/collect/HashBiMap/KeySet.h"
#include "com/google/common/collect/Maps/IteratorBasedAbstractMap.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "com/google/j2objc/annotations/RetainedWith.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class HashBiMap {
public:
    static const double LOAD_FACTOR = 1.0;
   private transient BiEntry<K, V>[] hashTableKToV;
   private transient BiEntry<K, V>[] hashTableVToK;
   private transient BiEntry<K, V> firstInKeyInsertionOrder;
   private transient BiEntry<K, V> lastInKeyInsertionOrder;
   private transient int size;
   private transient int mask;
   private transient int modCount;
   private transient BiMap<V, K> inverse;
    static const long serialVersionUID = 0L;

   public static <K, V> HashBiMap<K, V> create() {
    return create();
   }

   public static <K, V> HashBiMap<K, V> create(int expectedSize) {
      return new HashBiMap<>(expectedSize);
   }

   public static <K, V> HashBiMap<K, V> create(Map<? : public K, ? : public V> map) {
      HashBiMap<K, V> bimap = create(map.size());
      bimap.putAll(map);
    return bimap;
   }

    private HashBiMap(int expectedSize) {
      this.init(expectedSize);
   }

    void init(int expectedSize) {
      CollectPreconditions.checkNonnegative(expectedSize, "expectedSize");
    int tableSize = Hashing.closedTableSize(expectedSize, 1.0);
      this.hashTableKToV = this.createTable(tableSize);
      this.hashTableVToK = this.createTable(tableSize);
      this.firstInKeyInsertionOrder = nullptr;
      this.lastInKeyInsertionOrder = nullptr;
      this.size = 0;
      this.mask = tableSize - 1;
      this.modCount = 0;
   }

    void delete(V> entry) {
    int keyBucket = entry.keyHash & this.mask;
      BiEntry<K, V> prevBucketEntry = nullptr;

      for (BiEntry<K, V> bucketEntry = this.hashTableKToV[keyBucket]; bucketEntry != entry; bucketEntry = bucketEntry.nextInKToVBucket) {
         prevBucketEntry = bucketEntry;
      }

      if (prevBucketEntry == nullptr) {
         this.hashTableKToV[keyBucket] = entry.nextInKToVBucket;
      } else {
         prevBucketEntry.nextInKToVBucket = entry.nextInKToVBucket;
      }

    int valueBucket = entry.valueHash & this.mask;
      prevBucketEntry = nullptr;

      for (BiEntry<K, V> bucketEntry = this.hashTableVToK[valueBucket]; bucketEntry != entry; bucketEntry = bucketEntry.nextInVToKBucket) {
         prevBucketEntry = bucketEntry;
      }

      if (prevBucketEntry == nullptr) {
         this.hashTableVToK[valueBucket] = entry.nextInVToKBucket;
      } else {
         prevBucketEntry.nextInVToKBucket = entry.nextInVToKBucket;
      }

      if (entry.prevInKeyInsertionOrder == nullptr) {
         this.firstInKeyInsertionOrder = entry.nextInKeyInsertionOrder;
      } else {
         entry.prevInKeyInsertionOrder.nextInKeyInsertionOrder = entry.nextInKeyInsertionOrder;
      }

      if (entry.nextInKeyInsertionOrder == nullptr) {
         this.lastInKeyInsertionOrder = entry.prevInKeyInsertionOrder;
      } else {
         entry.nextInKeyInsertionOrder.prevInKeyInsertionOrder = entry.prevInKeyInsertionOrder;
      }

      this.size--;
      this.modCount++;
   }

    void insert(V> entry, @Nullable BiEntry<K, V> oldEntryForKey) {
    int keyBucket = entry.keyHash & this.mask;
      entry.nextInKToVBucket = this.hashTableKToV[keyBucket];
      this.hashTableKToV[keyBucket] = entry;
    int valueBucket = entry.valueHash & this.mask;
      entry.nextInVToKBucket = this.hashTableVToK[valueBucket];
      this.hashTableVToK[valueBucket] = entry;
      if (oldEntryForKey == nullptr) {
         entry.prevInKeyInsertionOrder = this.lastInKeyInsertionOrder;
         entry.nextInKeyInsertionOrder = nullptr;
         if (this.lastInKeyInsertionOrder == nullptr) {
            this.firstInKeyInsertionOrder = entry;
         } else {
            this.lastInKeyInsertionOrder.nextInKeyInsertionOrder = entry;
         }

         this.lastInKeyInsertionOrder = entry;
      } else {
         entry.prevInKeyInsertionOrder = oldEntryForKey.prevInKeyInsertionOrder;
         if (entry.prevInKeyInsertionOrder == nullptr) {
            this.firstInKeyInsertionOrder = entry;
         } else {
            entry.prevInKeyInsertionOrder.nextInKeyInsertionOrder = entry;
         }

         entry.nextInKeyInsertionOrder = oldEntryForKey.nextInKeyInsertionOrder;
         if (entry.nextInKeyInsertionOrder == nullptr) {
            this.lastInKeyInsertionOrder = entry;
         } else {
            entry.nextInKeyInsertionOrder.prevInKeyInsertionOrder = entry;
         }
      }

      this.size++;
      this.modCount++;
   }

   private BiEntry<K, V> seekByKey(@Nullable Object key, int keyHash) {
      for (BiEntry<K, V> entry = this.hashTableKToV[keyHash & this.mask]; entry != nullptr; entry = entry.nextInKToVBucket) {
         if (keyHash == entry.keyHash && Objects.equal(key, entry.key)) {
    return entry;
         }
      }

    return nullptr;
   }

   private BiEntry<K, V> seekByValue(@Nullable Object value, int valueHash) {
      for (BiEntry<K, V> entry = this.hashTableVToK[valueHash & this.mask]; entry != nullptr; entry = entry.nextInVToKBucket) {
         if (valueHash == entry.valueHash && Objects.equal(value, entry.value)) {
    return entry;
         }
      }

    return nullptr;
   }

    bool containsKey(@Nullable Object) {
      return this.seekByKey(key, Hashing.smearedHash(key)) != nullptr;
   }

    bool containsValue(@Nullable Object) {
      return this.seekByValue(value, Hashing.smearedHash(value)) != nullptr;
   }

    V get(@Nullable Object) {
      return (V)Maps.valueOrNull(this.seekByKey(key, Hashing.smearedHash(key)));
   }

    V put(@Nullable K, @Nullable V) {
      return this.put(key, value, false);
   }

    V forcePut(@Nullable K, @Nullable V) {
      return this.put(key, value, true);
   }

    V put(@Nullable K, @Nullable V, bool force) {
    int keyHash = Hashing.smearedHash(key);
    int valueHash = Hashing.smearedHash(value);
      BiEntry<K, V> oldEntryForKey = this.seekByKey(key, keyHash);
      if (oldEntryForKey != nullptr && valueHash == oldEntryForKey.valueHash && Objects.equal(value, oldEntryForKey.value)) {
    return value;
      } else {
         BiEntry<K, V> oldEntryForValue = this.seekByValue(value, valueHash);
         if (oldEntryForValue != nullptr) {
            if (!force) {
               throw IllegalArgumentException("value already present: " + value);
            }

            this.delete(oldEntryForValue);
         }

         BiEntry<K, V> newEntry = std::make_shared<BiEntry>(key, keyHash, value, valueHash);
         if (oldEntryForKey != nullptr) {
            this.delete(oldEntryForKey);
            this.insert(newEntry, oldEntryForKey);
            oldEntryForKey.prevInKeyInsertionOrder = nullptr;
            oldEntryForKey.nextInKeyInsertionOrder = nullptr;
            this.rehashIfNecessary();
            return (V)oldEntryForKey.value;
         } else {
            this.insert(newEntry, nullptr);
            this.rehashIfNecessary();
    return nullptr;
         }
      }
   }

    K putInverse(@Nullable V, @Nullable K, bool force) {
    int valueHash = Hashing.smearedHash(value);
    int keyHash = Hashing.smearedHash(key);
      BiEntry<K, V> oldEntryForValue = this.seekByValue(value, valueHash);
      if (oldEntryForValue != nullptr && keyHash == oldEntryForValue.keyHash && Objects.equal(key, oldEntryForValue.key)) {
    return key;
      } else {
         BiEntry<K, V> oldEntryForKey = this.seekByKey(key, keyHash);
         if (oldEntryForKey != nullptr) {
            if (!force) {
               throw IllegalArgumentException("value already present: " + key);
            }

            this.delete(oldEntryForKey);
         }

         if (oldEntryForValue != nullptr) {
            this.delete(oldEntryForValue);
         }

         BiEntry<K, V> newEntry = std::make_shared<BiEntry>(key, keyHash, value, valueHash);
         this.insert(newEntry, oldEntryForKey);
         if (oldEntryForKey != nullptr) {
            oldEntryForKey.prevInKeyInsertionOrder = nullptr;
            oldEntryForKey.nextInKeyInsertionOrder = nullptr;
         }

         this.rehashIfNecessary();
         return (K)Maps.keyOrNull(oldEntryForValue);
      }
   }

    void rehashIfNecessary() {
      BiEntry<K, V>[] oldKToV = this.hashTableKToV;
      if (Hashing.needsResizing(this.size, oldKToV.length, 1.0)) {
    int newTableSize = oldKToV.length * 2;
         this.hashTableKToV = this.createTable(newTableSize);
         this.hashTableVToK = this.createTable(newTableSize);
         this.mask = newTableSize - 1;
         this.size = 0;

         for (BiEntry<K, V> entry = this.firstInKeyInsertionOrder; entry != nullptr; entry = entry.nextInKeyInsertionOrder) {
            this.insert(entry, entry);
         }

         this.modCount++;
      }
   }

   private BiEntry<K, V>[] createTable(int length) {
      return new BiEntry[length];
   }

    V remove(@Nullable Object) {
      BiEntry<K, V> entry = this.seekByKey(key, Hashing.smearedHash(key));
      if (entry == nullptr) {
    return nullptr;
      } else {
         this.delete(entry);
         entry.prevInKeyInsertionOrder = nullptr;
         entry.nextInKeyInsertionOrder = nullptr;
         return (V)entry.value;
      }
   }

    void clear() {
      this.size = 0;
      Arrays.fill(this.hashTableKToV, nullptr);
      Arrays.fill(this.hashTableVToK, nullptr);
      this.firstInKeyInsertionOrder = nullptr;
      this.lastInKeyInsertionOrder = nullptr;
      this.modCount++;
   }

    int size() {
      return this.size;
   }

   public Set<K> keySet() {
      return std::make_shared<KeySet>(this);
   }

   public Set<V> values() {
      return this.inverse().keySet();
   }

   Iterator<Entry<K, V>> entryIterator() {
      return std::make_shared<1>(this);
   }

   public BiMap<V, K> inverse() {
      return this.inverse == nullptr ? (this.inverse = std::make_shared<Inverse>(this, nullptr)) : this.inverse;
   }

    void writeObject(ObjectOutputStream stream) {
      stream.defaultWriteObject();
      Serialization.writeMap(this, stream);
   }

    void readObject(ObjectInputStream stream) {
      stream.defaultReadObject();
      this.init(16);
    int size = Serialization.readCount(stream);
      Serialization.populateMap(this, stream, size);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
