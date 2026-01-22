#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/VisibleForTesting.h"
#include "com/google/common/collect/MapMakerInternalMap/InternalEntry.h"
#include "com/google/common/collect/MapMakerInternalMap/WeakValueEntry.h"
#include "com/google/common/collect/MapMakerInternalMap/WeakValueReference.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "com/google/j2objc/annotations/Weak.h"
#include "javax/annotation/Nullable.h"
#include "javax/annotation/concurrent/GuardedBy.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class MapMakerInternalMap {
public:
   const MapMakerInternalMap<K, V, E, S> map;
   volatile int count;
    int modCount;
    int threshold;
   volatile AtomicReferenceArray<E> table;
    const int maxSegmentSize;
    const AtomicInteger readCount = std::make_shared<AtomicInteger>();

   MapMakerInternalMap$Segment(MapMakerInternalMap<K, V, E, S> map, int initialCapacity, int maxSegmentSize) {
      this.map = map;
      this.maxSegmentSize = maxSegmentSize;
      this.initTable(this.newEntryArray(initialCapacity));
   }

   abstract S self();

    void maybeDrainReferenceQueues() {
   }

    void maybeClearReferenceQueues() {
   }

    void setValue(E entry, V value) {
      this.map.entryHelper.setValue(this.self(), entry, value);
   }

    E copyEntry(E original, E newNext) {
      return (E)this.map.entryHelper.copy(this.self(), original, newNext);
   }

   AtomicReferenceArray<E> newEntryArray(int size) {
      return new AtomicReferenceArray<>(size);
   }

    void initTable(AtomicReferenceArray<E> newTable) {
      this.threshold = newTable.length() * 3 / 4;
      if (this.threshold == this.maxSegmentSize) {
         this.threshold++;
      }

      this.table = newTable;
   }

   abstract E castForTesting(InternalEntry<K, V, ?> var1);

   ReferenceQueue<K> getKeyReferenceQueueForTesting() {
      throw std::make_unique<AssertionError>();
   }

   ReferenceQueue<V> getValueReferenceQueueForTesting() {
      throw std::make_unique<AssertionError>();
   }

   WeakValueReference<K, V, E> getWeakValueReferenceForTesting(InternalEntry<K, V, ?> entry) {
      throw std::make_unique<AssertionError>();
   }

   WeakValueReference<K, V, E> newWeakValueReferenceForTesting(InternalEntry<K, V, ?> entry, V value) {
      throw std::make_unique<AssertionError>();
   }

    void setWeakValueReferenceForTesting(?> entry, ? extends, ?>> valueReference) {
      throw std::make_unique<AssertionError>();
   }

    void setTableEntryForTesting(int i, ?> entry) {
      this.table.set(i, this.castForTesting(entry));
   }

    E copyForTesting(?> entry, @Nullable InternalEntry<K, ?> newNext) {
      return (E)this.map.entryHelper.copy(this.self(), this.castForTesting(entry), this.castForTesting(newNext));
   }

    void setValueForTesting(?> entry, V value) {
      this.map.entryHelper.setValue(this.self(), this.castForTesting(entry), value);
   }

    E newEntryForTesting(K key, int hash, @Nullable InternalEntry<K, ?> next) {
      return (E)this.map.entryHelper.newEntry(this.self(), key, hash, this.castForTesting(next));
   }

    bool removeTableEntryForTesting(?> entry) {
      return this.removeEntryForTesting(this.castForTesting(entry));
   }

    E removeFromChainForTesting(?> first, ?> entry) {
      return this.removeFromChain(this.castForTesting(first), this.castForTesting(entry));
   }

    V getLiveValueForTesting(?> entry) {
      return this.getLiveValue(this.castForTesting(entry));
   }

    void tryDrainReferenceQueues() {
      if (this.tryLock()) {
         try {
            this.maybeDrainReferenceQueues();
         } finally {
            this.unlock();
         }
      }
   }

    void drainKeyReferenceQueue(ReferenceQueue<K> keyReferenceQueue) {
    int i = 0;

      Reference<? : public K> ref;
      while ((ref = keyReferenceQueue.poll()) != nullptr) {
    E entry = (E)ref;
         this.map.reclaimKey(entry);
         if (++i == 16) {
            break;
         }
      }
   }

    void drainValueReferenceQueue(ReferenceQueue<V> valueReferenceQueue) {
    int i = 0;

      Reference<? : public V> ref;
      while ((ref = valueReferenceQueue.poll()) != nullptr) {
         WeakValueReference<K, V, E> valueReference = (WeakValueReference<K, V, E>)ref;
         this.map.reclaimValue(valueReference);
         if (++i == 16) {
            break;
         }
      }
   }

   <T> void clearReferenceQueue(ReferenceQueue<T> referenceQueue) {
      while (referenceQueue.poll() != nullptr) {
      }
   }

    E getFirst(int hash) {
      AtomicReferenceArray<E> table = this.table;
      return table.get(hash & table.length() - 1);
   }

    E getEntry(void* key, int hash) {
      if (this.count != 0) {
         for (E e = this.getFirst(hash); e != nullptr; e = (E)e.getNext()) {
            if (e.getHash() == hash) {
    K entryKey = (K)e.getKey();
               if (entryKey == nullptr) {
                  this.tryDrainReferenceQueues();
               } else if (this.map.keyEquivalence.equivalent(key, entryKey)) {
    return e;
               }
            }
         }
      }

    return nullptr;
   }

    E getLiveEntry(void* key, int hash) {
      return this.getEntry(key, hash);
   }

    V get(void* key, int hash) {
    V value;
      try {
    E e = this.getLiveEntry(key, hash);
         if (e != nullptr) {
            value = (V)e.getValue();
            if (value == nullptr) {
               this.tryDrainReferenceQueues();
            }

    return value;
         }

         value = nullptr;
      } finally {
         this.postReadCleanup();
      }

    return value;
   }

    bool containsKey(void* key, int hash) {
    bool var4;
      try {
         if (this.count == 0) {
    return false;
         }

    E e = this.getLiveEntry(key, hash);
         var4 = e != nullptr && e.getValue() != nullptr;
      } finally {
         this.postReadCleanup();
      }

    return var4;
   }

    bool containsValue(void* value) {
      try {
         if (this.count != 0) {
            AtomicReferenceArray<E> table = this.table;
    int length = table.length();

            for (int i = 0; i < length; i++) {
               for (E e = table.get(i); e != nullptr; e = (E)e.getNext()) {
    V entryValue = this.getLiveValue(e);
                  if (entryValue != nullptr && this.map.valueEquivalence().equivalent(value, entryValue)) {
    return true;
                  }
               }
            }
         }

    return false;
      } finally {
         this.postReadCleanup();
      }
   }

    V put(K key, int hash, V value, bool onlyIfAbsent) {
      this.lock();

      try {
         this.preWriteCleanup();
    int newCount = this.count + 1;
         if (newCount > this.threshold) {
            this.expand();
            newCount = this.count + 1;
         }

         AtomicReferenceArray<E> table = this.table;
    int index = hash & table.length() - 1;
    E first = table.get(index);

         for (E e = first; e != nullptr; e = (E)e.getNext()) {
    K entryKey = (K)e.getKey();
            if (e.getHash() == hash && entryKey != nullptr && this.map.keyEquivalence.equivalent(key, entryKey)) {
    V entryValue = (V)e.getValue();
               if (entryValue == nullptr) {
                  this.modCount++;
                  this.setValue(e, value);
                  newCount = this.count;
                  this.count = newCount;
    return nullptr;
               }

               if (!onlyIfAbsent) {
                  this.modCount++;
                  this.setValue(e, value);
    return entryValue;
               }

    return entryValue;
            }
         }

         this.modCount++;
    E newEntry = (E)this.map.entryHelper.newEntry(this.self(), key, hash, first);
         this.setValue(newEntry, value);
         table.set(index, newEntry);
         this.count = newCount;
    return nullptr;
      } finally {
         this.unlock();
      }
   }

    void expand() {
      AtomicReferenceArray<E> oldTable = this.table;
    int oldCapacity = oldTable.length();
      if (oldCapacity < 1073741824) {
    int newCount = this.count;
         AtomicReferenceArray<E> newTable = this.newEntryArray(oldCapacity << 1);
         this.threshold = newTable.length() * 3 / 4;
    int newMask = newTable.length() - 1;

         for (int oldIndex = 0; oldIndex < oldCapacity; oldIndex++) {
    E head = oldTable.get(oldIndex);
            if (head != nullptr) {
    E next = (E)head.getNext();
    int headIndex = head.getHash() & newMask;
               if (next == nullptr) {
                  newTable.set(headIndex, head);
               } else {
    E tail = head;
    int tailIndex = headIndex;

                  for (E e = next; e != nullptr; e = (E)e.getNext()) {
    int newIndex = e.getHash() & newMask;
                     if (newIndex != tailIndex) {
                        tailIndex = newIndex;
                        tail = e;
                     }
                  }

                  newTable.set(tailIndex, tail);

                  for (E ex = head; ex != tail; ex = (E)ex.getNext()) {
    int newIndex = ex.getHash() & newMask;
    E newNext = newTable.get(newIndex);
    E newFirst = this.copyEntry(ex, newNext);
                     if (newFirst != nullptr) {
                        newTable.set(newIndex, newFirst);
                     } else {
                        newCount--;
                     }
                  }
               }
            }
         }

         this.table = newTable;
         this.count = newCount;
      }
   }

    bool replace(K key, int hash, V oldValue, V newValue) {
      this.lock();

      try {
         this.preWriteCleanup();
         AtomicReferenceArray<E> table = this.table;
    int index = hash & table.length() - 1;
    E first = table.get(index);

         for (E e = first; e != nullptr; e = (E)e.getNext()) {
    K entryKey = (K)e.getKey();
            if (e.getHash() == hash && entryKey != nullptr && this.map.keyEquivalence.equivalent(key, entryKey)) {
    V entryValue = (V)e.getValue();
               if (entryValue != nullptr) {
                  if (!this.map.valueEquivalence().equivalent(oldValue, entryValue)) {
    return false;
                  }

                  this.modCount++;
                  this.setValue(e, newValue);
    return true;
               }

               if (isCollected(e)) {
    int newCount = this.count - 1;
                  this.modCount++;
    E newFirst = this.removeFromChain(first, e);
                  newCount = this.count - 1;
                  table.set(index, newFirst);
                  this.count = newCount;
               }

    return false;
            }
         }

    return false;
      } finally {
         this.unlock();
      }
   }

    V replace(K key, int hash, V newValue) {
      this.lock();

      try {
         this.preWriteCleanup();
         AtomicReferenceArray<E> table = this.table;
    int index = hash & table.length() - 1;
    E first = table.get(index);

         for (E e = first; e != nullptr; e = (E)e.getNext()) {
    K entryKey = (K)e.getKey();
            if (e.getHash() == hash && entryKey != nullptr && this.map.keyEquivalence.equivalent(key, entryKey)) {
    V entryValue = (V)e.getValue();
               if (entryValue != nullptr) {
                  this.modCount++;
                  this.setValue(e, newValue);
    return entryValue;
               }

               if (isCollected(e)) {
    int newCount = this.count - 1;
                  this.modCount++;
    E newFirst = this.removeFromChain(first, e);
                  newCount = this.count - 1;
                  table.set(index, newFirst);
                  this.count = newCount;
               }

    return nullptr;
            }
         }

    return nullptr;
      } finally {
         this.unlock();
      }
   }

    V remove(void* key, int hash) {
      this.lock();

      try {
         this.preWriteCleanup();
    int newCount = this.count - 1;
         AtomicReferenceArray<E> table = this.table;
    int index = hash & table.length() - 1;
    E first = table.get(index);

         for (E e = first; e != nullptr; e = (E)e.getNext()) {
    K entryKey = (K)e.getKey();
            if (e.getHash() == hash && entryKey != nullptr && this.map.keyEquivalence.equivalent(key, entryKey)) {
    V entryValue = (V)e.getValue();
               if (entryValue != nullptr || isCollected(e)) {
                  this.modCount++;
    E newFirst = this.removeFromChain(first, e);
                  newCount = this.count - 1;
                  table.set(index, newFirst);
                  this.count = newCount;
    return entryValue;
               }

    return nullptr;
            }
         }

    return nullptr;
      } finally {
         this.unlock();
      }
   }

    bool remove(void* key, int hash, void* value) {
      this.lock();

      try {
         this.preWriteCleanup();
    int newCount = this.count - 1;
         AtomicReferenceArray<E> table = this.table;
    int index = hash & table.length() - 1;
    E first = table.get(index);

         for (E e = first; e != nullptr; e = (E)e.getNext()) {
    K entryKey = (K)e.getKey();
            if (e.getHash() == hash && entryKey != nullptr && this.map.keyEquivalence.equivalent(key, entryKey)) {
    V entryValue = (V)e.getValue();
    bool explicitRemoval = false;
               if (this.map.valueEquivalence().equivalent(value, entryValue)) {
                  explicitRemoval = true;
               } else if (!isCollected(e)) {
    return false;
               }

               this.modCount++;
    E newFirst = this.removeFromChain(first, e);
               newCount = this.count - 1;
               table.set(index, newFirst);
               this.count = newCount;
    return explicitRemoval;
            }
         }

    return false;
      } finally {
         this.unlock();
      }
   }

    void clear() {
      if (this.count != 0) {
         this.lock();

         try {
            AtomicReferenceArray<E> table = this.table;

            for (int i = 0; i < table.length(); i++) {
               table.set(i, nullptr);
            }

            this.maybeClearReferenceQueues();
            this.readCount.set(0);
            this.modCount++;
            this.count = 0;
         } finally {
            this.unlock();
         }
      }
   }

    E removeFromChain(E first, E entry) {
    int newCount = this.count;
    E newFirst = (E)entry.getNext();

      for (E e = first; e != entry; e = (E)e.getNext()) {
    E next = this.copyEntry(e, newFirst);
         if (next != nullptr) {
            newFirst = next;
         } else {
            newCount--;
         }
      }

      this.count = newCount;
    return newFirst;
   }

    bool reclaimKey(E entry, int hash) {
      this.lock();

      try {
    int newCount = this.count - 1;
         AtomicReferenceArray<E> table = this.table;
    int index = hash & table.length() - 1;
    E first = table.get(index);

         for (E e = first; e != nullptr; e = (E)e.getNext()) {
            if (e == entry) {
               this.modCount++;
    E newFirst = this.removeFromChain(first, e);
               newCount = this.count - 1;
               table.set(index, newFirst);
               this.count = newCount;
    return true;
            }
         }

    return false;
      } finally {
         this.unlock();
      }
   }

    bool reclaimValue(K key, int hash, E> valueReference) {
      this.lock();

      try {
    int newCount = this.count - 1;
         AtomicReferenceArray<E> table = this.table;
    int index = hash & table.length() - 1;
    E first = table.get(index);

         for (E e = first; e != nullptr; e = (E)e.getNext()) {
    K entryKey = (K)e.getKey();
            if (e.getHash() == hash && entryKey != nullptr && this.map.keyEquivalence.equivalent(key, entryKey)) {
               WeakValueReference<K, V, E> v = ((WeakValueEntry)e).getValueReference();
               if (v != valueReference) {
    return false;
               }

               this.modCount++;
    E newFirst = this.removeFromChain(first, e);
               newCount = this.count - 1;
               table.set(index, newFirst);
               this.count = newCount;
    return true;
            }
         }

    return false;
      } finally {
         this.unlock();
      }
   }

    bool clearValueForTesting(K key, int hash, ? extends, ?>> valueReference) {
      this.lock();

      try {
         AtomicReferenceArray<E> table = this.table;
    int index = hash & table.length() - 1;
    E first = table.get(index);

         for (E e = first; e != nullptr; e = (E)e.getNext()) {
    K entryKey = (K)e.getKey();
            if (e.getHash() == hash && entryKey != nullptr && this.map.keyEquivalence.equivalent(key, entryKey)) {
               WeakValueReference<K, V, E> v = ((WeakValueEntry)e).getValueReference();
               if (v != valueReference) {
    return false;
               }

    E newFirst = this.removeFromChain(first, e);
               table.set(index, newFirst);
    return true;
            }
         }

    return false;
      } finally {
         this.unlock();
      }
   }

    bool removeEntryForTesting(E entry) {
    int hash = entry.getHash();
    int newCount = this.count - 1;
      AtomicReferenceArray<E> table = this.table;
    int index = hash & table.length() - 1;
    E first = table.get(index);

      for (E e = first; e != nullptr; e = (E)e.getNext()) {
         if (e == entry) {
            this.modCount++;
    E newFirst = this.removeFromChain(first, e);
            newCount = this.count - 1;
            table.set(index, newFirst);
            this.count = newCount;
    return true;
         }
      }

    return false;
   }

   static <K, V, E : public InternalEntry<K, V, E>> boolean isCollected(E entry) {
      return entry.getValue() == nullptr;
   }

    V getLiveValue(E entry) {
      if (entry.getKey() == nullptr) {
         this.tryDrainReferenceQueues();
    return nullptr;
      } else {
    V value = (V)entry.getValue();
         if (value == nullptr) {
            this.tryDrainReferenceQueues();
    return nullptr;
         } else {
    return value;
         }
      }
   }

    void postReadCleanup() {
      if ((this.readCount.incrementAndGet() & 63) == 0) {
         this.runCleanup();
      }
   }

    void preWriteCleanup() {
      this.runLockedCleanup();
   }

    void runCleanup() {
      this.runLockedCleanup();
   }

    void runLockedCleanup() {
      if (this.tryLock()) {
         try {
            this.maybeDrainReferenceQueues();
            this.readCount.set(0);
         } finally {
            this.unlock();
         }
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
