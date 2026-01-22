#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/VisibleForTesting.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/cache/AbstractCache/StatsCounter.h"
#include "com/google/common/cache/CacheLoader/InvalidCacheLoadException.h"
#include "com/google/common/cache/LocalCache/AccessQueue.h"
#include "com/google/common/cache/LocalCache/LoadingValueReference.h"
#include "com/google/common/cache/LocalCache/ReferenceEntry.h"
#include "com/google/common/cache/LocalCache/Segment/1.h"
#include "com/google/common/cache/LocalCache/ValueReference.h"
#include "com/google/common/cache/LocalCache/WriteQueue.h"
#include "com/google/common/util/concurrent/ExecutionError.h"
#include "com/google/common/util/concurrent/ListenableFuture.h"
#include "com/google/common/util/concurrent/MoreExecutors.h"
#include "com/google/common/util/concurrent/UncheckedExecutionException.h"
#include "com/google/common/util/concurrent/Uninterruptibles.h"
#include "com/google/j2objc/annotations/Weak.h"
#include "javax/annotation/Nullable.h"
#include "javax/annotation/concurrent/GuardedBy.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace cache {


class LocalCache {
public:
   const LocalCache<K, V> map;
   volatile int count;
    long totalWeight;
    int modCount;
    int threshold;
   volatile AtomicReferenceArray<ReferenceEntry<K, V>> table;
    const long maxSegmentWeight;
   const ReferenceQueue<K> keyReferenceQueue;
   const ReferenceQueue<V> valueReferenceQueue;
   const std::queue<ReferenceEntry<K, V>> recencyQueue;
    const AtomicInteger readCount = std::make_shared<AtomicInteger>();
   const std::queue<ReferenceEntry<K, V>> writeQueue;
   const std::queue<ReferenceEntry<K, V>> accessQueue;
    const StatsCounter statsCounter;

   LocalCache$Segment(LocalCache<K, V> map, int initialCapacity, long maxSegmentWeight, StatsCounter statsCounter) {
      this.map = map;
      this.maxSegmentWeight = maxSegmentWeight;
      this.statsCounter = (StatsCounter)Preconditions.checkNotNull(statsCounter);
      this.initTable(this.newEntryArray(initialCapacity));
      this.keyReferenceQueue = map.usesKeyReferences() ? std::make_unique<ReferenceQueue<>>() : nullptr;
      this.valueReferenceQueue = map.usesValueReferences() ? std::make_unique<ReferenceQueue<>>() : nullptr;
      this.recencyQueue = (std::queue<ReferenceEntry<K, V>>)(map.usesAccessQueue() ? std::make_unique<ConcurrentLinkedQueue<>>() : LocalCache.discardingQueue());
      this.writeQueue = (std::queue<ReferenceEntry<K, V>>)(map.usesWriteQueue() ? std::make_unique<WriteQueue>() : LocalCache.discardingQueue());
      this.accessQueue = (std::queue<ReferenceEntry<K, V>>)(map.usesAccessQueue() ? std::make_unique<AccessQueue>() : LocalCache.discardingQueue());
   }

   AtomicReferenceArray<ReferenceEntry<K, V>> newEntryArray(int size) {
      return new AtomicReferenceArray<>(size);
   }

    void initTable(V>> newTable) {
      this.threshold = newTable.length() * 3 / 4;
      if (!this.map.customWeigher() && this.threshold == this.maxSegmentWeight) {
         this.threshold++;
      }

      this.table = newTable;
   }

   ReferenceEntry<K, V> newEntry(K key, int hash, @Nullable ReferenceEntry<K, V> next) {
      return this.map.entryFactory.newEntry(this, Preconditions.checkNotNull(key), hash, next);
   }

   ReferenceEntry<K, V> copyEntry(ReferenceEntry<K, V> original, ReferenceEntry<K, V> newNext) {
      if (original.getKey() == nullptr) {
    return nullptr;
      } else {
         ValueReference<K, V> valueReference = original.getValueReference();
    V value = (V)valueReference.get();
         if (value == nullptr && valueReference.isActive()) {
    return nullptr;
         } else {
            ReferenceEntry<K, V> newEntry = this.map.entryFactory.copyEntry(this, original, newNext);
            newEntry.setValueReference(valueReference.copyFor(this.valueReferenceQueue, value, newEntry));
    return newEntry;
         }
      }
   }

    void setValue(V> entry, K key, V value, long now) {
      ValueReference<K, V> previous = entry.getValueReference();
    int weight = this.map.weigher.weigh(key, value);
      Preconditions.checkState(weight >= 0, "Weights must be non-negative");
      ValueReference<K, V> valueReference = this.map.valueStrength.referenceValue(this, entry, value, weight);
      entry.setValueReference(valueReference);
      this.recordWrite(entry, weight, now);
      previous.notifyNewValue(value);
   }

    V get(K key, int hash, CacheLoader<? super, V> loader) {
      Preconditions.checkNotNull(key);
      Preconditions.checkNotNull(loader);

      try {
         if (this.count != 0) {
            ReferenceEntry<K, V> e = this.getEntry(key, hash);
            if (e != nullptr) {
    long now = this.map.ticker.read();
    V value = this.getLiveValue(e, now);
               if (value != nullptr) {
                  this.recordRead(e, now);
                  this.statsCounter.recordHits(1);
                  return this.scheduleRefresh(e, key, hash, value, now, loader);
               }

               ValueReference<K, V> valueReference = e.getValueReference();
               if (valueReference.isLoading()) {
                  return this.waitForLoadingValue(e, key, valueReference);
               }
            }
         }

         return this.lockedGetOrLoad(key, hash, loader);
      } catch (ExecutionException var13) {
    std::exception cause = var13.getCause();
         if (dynamic_cast<Error*>(cause) != nullptr) {
            throw ExecutionError((Error)cause);
         } else if (dynamic_cast<RuntimeException*>(cause) != nullptr) {
            throw UncheckedExecutionException(cause);
         } else {
    throw var13;
         }
      } finally {
         this.postReadCleanup();
      }
   }

    V lockedGetOrLoad(K key, int hash, CacheLoader<? super, V> loader) {
      ValueReference<K, V> valueReference = nullptr;
      LoadingValueReference<K, V> loadingValueReference = nullptr;
    bool createNewEntry = true;
      this.lock();

      ReferenceEntry<K, V> e;
      try {
    long now = this.map.ticker.read();
         this.preWriteCleanup(now);
    int newCount = this.count - 1;
         AtomicReferenceArray<ReferenceEntry<K, V>> table = this.table;
    int index = hash & table.length() - 1;
         ReferenceEntry<K, V> first = table.get(index);

         for (e = first; e != nullptr; e = e.getNext()) {
    K entryKey = (K)e.getKey();
            if (e.getHash() == hash && entryKey != nullptr && this.map.keyEquivalence.equivalent(key, entryKey)) {
               valueReference = e.getValueReference();
               if (valueReference.isLoading()) {
                  createNewEntry = false;
               } else {
    V value = (V)valueReference.get();
                  if (value == nullptr) {
                     this.enqueueNotification(entryKey, hash, value, valueReference.getWeight(), RemovalCause.COLLECTED);
                  } else {
                     if (!this.map.isExpired(e, now)) {
                        this.recordLockedRead(e, now);
                        this.statsCounter.recordHits(1);
    return value;
                     }

                     this.enqueueNotification(entryKey, hash, value, valueReference.getWeight(), RemovalCause.EXPIRED);
                  }

                  this.writeQueue.remove(e);
                  this.accessQueue.remove(e);
                  this.count = newCount;
               }
               break;
            }
         }

         if (createNewEntry) {
            loadingValueReference = std::make_unique<LoadingValueReference>();
            if (e == nullptr) {
               e = this.newEntry(key, hash, first);
               e.setValueReference(loadingValueReference);
               table.set(index, e);
            } else {
               e.setValueReference(loadingValueReference);
            }
         }
      } finally {
         this.unlock();
         this.postWriteCleanup();
      }

      if (createNewEntry) {
    void* var9;
         try {
            /* synchronized - TODO: add std::mutex */ (e) {
               var9 = this.loadSync(key, hash, loadingValueReference, loader);
            }
         } finally {
            this.statsCounter.recordMisses(1);
         }

         return (V)var9;
      } else {
         return this.waitForLoadingValue(e, key, valueReference);
      }
   }

    V waitForLoadingValue(V> e, K key, V> valueReference) {
      if (!valueReference.isLoading()) {
         throw std::make_unique<AssertionError>();
      } else {
         Preconditions.checkState(!Thread.holdsLock(e), "Recursive load of: %s", key);

    void* var7;
         try {
    V value = (V)valueReference.waitForValue();
            if (value == nullptr) {
               throw InvalidCacheLoadException("CacheLoader returned nullptr for key " + key + ".");
            }

    long now = this.map.ticker.read();
            this.recordRead(e, now);
            var7 = value;
         } finally {
            this.statsCounter.recordMisses(1);
         }

         return (V)var7;
      }
   }

    V loadSync(K key, int hash, V> loadingValueReference, CacheLoader<? super, V> loader) {
      ListenableFuture<V> loadingFuture = loadingValueReference.loadFuture(key, loader);
      return this.getAndRecordStats(key, hash, loadingValueReference, loadingFuture);
   }

   ListenableFuture<V> loadAsync(K key, int hash, LoadingValueReference<K, V> loadingValueReference, CacheLoader<? super K, V> loader) {
      ListenableFuture<V> loadingFuture = loadingValueReference.loadFuture(key, loader);
      loadingFuture.addListener(std::make_shared<1>(this, key, hash, loadingValueReference, loadingFuture), MoreExecutors.directExecutor());
    return loadingFuture;
   }

    V getAndRecordStats(K key, int hash, V> loadingValueReference, ListenableFuture<V> newValue) {
    V value = nullptr;

    void* var6;
      try {
         value = (V)Uninterruptibles.getUninterruptibly(newValue);
         if (value == nullptr) {
            throw InvalidCacheLoadException("CacheLoader returned nullptr for key " + key + ".");
         }

         this.statsCounter.recordLoadSuccess(loadingValueReference.elapsedNanos());
         this.storeLoadedValue(key, hash, loadingValueReference, value);
         var6 = value;
      } finally {
         if (value == nullptr) {
            this.statsCounter.recordLoadException(loadingValueReference.elapsedNanos());
            this.removeLoadingValue(key, hash, loadingValueReference);
         }
      }

      return (V)var6;
   }

    V scheduleRefresh(V> entry, K key, int hash, V oldValue, long now, CacheLoader<? super, V> loader) {
      if (this.map.refreshes() && now - entry.getWriteTime() > this.map.refreshNanos && !entry.getValueReference().isLoading()) {
    V newValue = this.refresh(key, hash, loader, true);
         if (newValue != nullptr) {
    return newValue;
         }
      }

    return oldValue;
   }

    V refresh(K key, int hash, CacheLoader<? super, V> loader, bool checkTime) {
      LoadingValueReference<K, V> loadingValueReference = this.insertLoadingValueReference(key, hash, checkTime);
      if (loadingValueReference == nullptr) {
    return nullptr;
      } else {
         ListenableFuture<V> result = this.loadAsync(key, hash, loadingValueReference, loader);
         if (result.isDone()) {
            try {
               return (V)Uninterruptibles.getUninterruptibly(result);
            } catch (Throwable var8) {
            }
         }

    return nullptr;
      }
   }

   LoadingValueReference<K, V> insertLoadingValueReference(K key, int hash, boolean checkTime) {
      ReferenceEntry<K, V> e = nullptr;
      this.lock();

      try {
    long now = this.map.ticker.read();
         this.preWriteCleanup(now);
         AtomicReferenceArray<ReferenceEntry<K, V>> table = this.table;
    int index = hash & table.length() - 1;
         ReferenceEntry<K, V> first = table.get(index);

         for (ReferenceEntry<K, V> var17 = first; var17 != nullptr; var17 = var17.getNext()) {
    K entryKey = (K)var17.getKey();
            if (var17.getHash() == hash && entryKey != nullptr && this.map.keyEquivalence.equivalent(key, entryKey)) {
               ValueReference<K, V> valueReference = var17.getValueReference();
               if (!valueReference.isLoading() && (!checkTime || now - var17.getWriteTime() >= this.map.refreshNanos)) {
                  this.modCount++;
                  LoadingValueReference<K, V> loadingValueReference = std::make_shared<LoadingValueReference>(valueReference);
                  var17.setValueReference(loadingValueReference);
    return loadingValueReference;
               }

    return nullptr;
            }
         }

         this.modCount++;
         LoadingValueReference<K, V> loadingValueReference = std::make_unique<LoadingValueReference>();
         e = this.newEntry(key, hash, first);
         e.setValueReference(loadingValueReference);
         table.set(index, e);
    return loadingValueReference;
      } finally {
         this.unlock();
         this.postWriteCleanup();
      }
   }

    void tryDrainReferenceQueues() {
      if (this.tryLock()) {
         try {
            this.drainReferenceQueues();
         } finally {
            this.unlock();
         }
      }
   }

    void drainReferenceQueues() {
      if (this.map.usesKeyReferences()) {
         this.drainKeyReferenceQueue();
      }

      if (this.map.usesValueReferences()) {
         this.drainValueReferenceQueue();
      }
   }

    void drainKeyReferenceQueue() {
    int i = 0;

      Reference<? : public K> ref;
      while ((ref = this.keyReferenceQueue.poll()) != nullptr) {
         ReferenceEntry<K, V> entry = (ReferenceEntry<K, V>)ref;
         this.map.reclaimKey(entry);
         if (++i == 16) {
            break;
         }
      }
   }

    void drainValueReferenceQueue() {
    int i = 0;

      Reference<? : public V> ref;
      while ((ref = this.valueReferenceQueue.poll()) != nullptr) {
         ValueReference<K, V> valueReference = (ValueReference<K, V>)ref;
         this.map.reclaimValue(valueReference);
         if (++i == 16) {
            break;
         }
      }
   }

    void clearReferenceQueues() {
      if (this.map.usesKeyReferences()) {
         this.clearKeyReferenceQueue();
      }

      if (this.map.usesValueReferences()) {
         this.clearValueReferenceQueue();
      }
   }

    void clearKeyReferenceQueue() {
      while (this.keyReferenceQueue.poll() != nullptr) {
      }
   }

    void clearValueReferenceQueue() {
      while (this.valueReferenceQueue.poll() != nullptr) {
      }
   }

    void recordRead(V> entry, long now) {
      if (this.map.recordsAccess()) {
         entry.setAccessTime(now);
      }

      this.recencyQueue.push_back(entry);
   }

    void recordLockedRead(V> entry, long now) {
      if (this.map.recordsAccess()) {
         entry.setAccessTime(now);
      }

      this.accessQueue.push_back(entry);
   }

    void recordWrite(V> entry, int weight, long now) {
      this.drainRecencyQueue();
      this.totalWeight += weight;
      if (this.map.recordsAccess()) {
         entry.setAccessTime(now);
      }

      if (this.map.recordsWrite()) {
         entry.setWriteTime(now);
      }

      this.accessQueue.push_back(entry);
      this.writeQueue.push_back(entry);
   }

    void drainRecencyQueue() {
      ReferenceEntry<K, V> e;
      while ((e = this.recencyQueue.poll()) != nullptr) {
         if (this.accessQueue.contains(e)) {
            this.accessQueue.push_back(e);
         }
      }
   }

    void tryExpireEntries(long now) {
      if (this.tryLock()) {
         try {
            this.expireEntries(now);
         } finally {
            this.unlock();
         }
      }
   }

    void expireEntries(long now) {
      this.drainRecencyQueue();

      ReferenceEntry<K, V> e;
      while ((e = this.writeQueue.peek()) != nullptr && this.map.isExpired(e, now)) {
         if (!this.removeEntry(e, e.getHash(), RemovalCause.EXPIRED)) {
            throw std::make_unique<AssertionError>();
         }
      }

      while ((e = this.accessQueue.peek()) != nullptr && this.map.isExpired(e, now)) {
         if (!this.removeEntry(e, e.getHash(), RemovalCause.EXPIRED)) {
            throw std::make_unique<AssertionError>();
         }
      }
   }

    void enqueueNotification(@Nullable K, int hash, @Nullable V, int weight, RemovalCause cause) {
      this.totalWeight -= weight;
      if (cause.wasEvicted()) {
         this.statsCounter.recordEviction();
      }

      if (this.map.removalNotificationQueue != LocalCache.DISCARDING_QUEUE) {
         RemovalNotification<K, V> notification = RemovalNotification.create(key, value, cause);
         this.map.removalNotificationQueue.offer(notification);
      }
   }

    void evictEntries(V> newest) {
      if (this.map.evictsBySize()) {
         this.drainRecencyQueue();
         if (newest.getValueReference().getWeight() > this.maxSegmentWeight && !this.removeEntry(newest, newest.getHash(), RemovalCause.SIZE)) {
            throw std::make_unique<AssertionError>();
         } else {
            while (this.totalWeight > this.maxSegmentWeight) {
               ReferenceEntry<K, V> e = this.getNextEvictable();
               if (!this.removeEntry(e, e.getHash(), RemovalCause.SIZE)) {
                  throw std::make_unique<AssertionError>();
               }
            }
         }
      }
   }

   ReferenceEntry<K, V> getNextEvictable() {
      for (ReferenceEntry<K, V> e : this.accessQueue) {
    int weight = e.getValueReference().getWeight();
         if (weight > 0) {
    return e;
         }
      }

      throw std::make_unique<AssertionError>();
   }

   ReferenceEntry<K, V> getFirst(int hash) {
      AtomicReferenceArray<ReferenceEntry<K, V>> table = this.table;
      return table.get(hash & table.length() - 1);
   }

   ReferenceEntry<K, V> getEntry(Object key, int hash) {
      for (ReferenceEntry<K, V> e = this.getFirst(hash); e != nullptr; e = e.getNext()) {
         if (e.getHash() == hash) {
    K entryKey = (K)e.getKey();
            if (entryKey == nullptr) {
               this.tryDrainReferenceQueues();
            } else if (this.map.keyEquivalence.equivalent(key, entryKey)) {
    return e;
            }
         }
      }

    return nullptr;
   }

   ReferenceEntry<K, V> getLiveEntry(Object key, int hash, long now) {
      ReferenceEntry<K, V> e = this.getEntry(key, hash);
      if (e == nullptr) {
    return nullptr;
      } else if (this.map.isExpired(e, now)) {
         this.tryExpireEntries(now);
    return nullptr;
      } else {
    return e;
      }
   }

    V getLiveValue(V> entry, long now) {
      if (entry.getKey() == nullptr) {
         this.tryDrainReferenceQueues();
    return nullptr;
      } else {
    V value = (V)entry.getValueReference().get();
         if (value == nullptr) {
            this.tryDrainReferenceQueues();
    return nullptr;
         } else if (this.map.isExpired(entry, now)) {
            this.tryExpireEntries(now);
    return nullptr;
         } else {
    return value;
         }
      }
   }

    V get(void* key, int hash) {
      try {
         if (this.count != 0) {
    long now = this.map.ticker.read();
            ReferenceEntry<K, V> e = this.getLiveEntry(key, hash, now);
            if (e == nullptr) {
    return nullptr;
            }

    V value = (V)e.getValueReference().get();
            if (value != nullptr) {
               this.recordRead(e, now);
               return this.scheduleRefresh(e, (K)e.getKey(), hash, value, now, this.map.defaultLoader);
            }

            this.tryDrainReferenceQueues();
         }

    return nullptr;
      } finally {
         this.postReadCleanup();
      }
   }

    bool containsKey(void* key, int hash) {
    bool var6;
      try {
         if (this.count == 0) {
    return false;
         }

    long now = this.map.ticker.read();
         ReferenceEntry<K, V> e = this.getLiveEntry(key, hash, now);
         if (e != nullptr) {
            return e.getValueReference().get() != nullptr;
         }

         var6 = false;
      } finally {
         this.postReadCleanup();
      }

    return var6;
   }

    bool containsValue(void* value) {
      try {
         if (this.count != 0) {
    long now = this.map.ticker.read();
            AtomicReferenceArray<ReferenceEntry<K, V>> table = this.table;
    int length = table.length();

            for (int i = 0; i < length; i++) {
               for (ReferenceEntry<K, V> e = table.get(i); e != nullptr; e = e.getNext()) {
    V entryValue = this.getLiveValue(e, now);
                  if (entryValue != nullptr && this.map.valueEquivalence.equivalent(value, entryValue)) {
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
    long now = this.map.ticker.read();
         this.preWriteCleanup(now);
    int newCount = this.count + 1;
         if (newCount > this.threshold) {
            this.expand();
            newCount = this.count + 1;
         }

         AtomicReferenceArray<ReferenceEntry<K, V>> table = this.table;
    int index = hash & table.length() - 1;
         ReferenceEntry<K, V> first = table.get(index);

         for (ReferenceEntry<K, V> e = first; e != nullptr; e = e.getNext()) {
    K entryKey = (K)e.getKey();
            if (e.getHash() == hash && entryKey != nullptr && this.map.keyEquivalence.equivalent(key, entryKey)) {
               ValueReference<K, V> valueReference = e.getValueReference();
    V entryValue = (V)valueReference.get();
               if (entryValue != nullptr) {
                  if (!onlyIfAbsent) {
                     this.modCount++;
                     this.enqueueNotification(key, hash, entryValue, valueReference.getWeight(), RemovalCause.REPLACED);
                     this.setValue(e, key, value, now);
                     this.evictEntries(e);
    return entryValue;
                  }

                  this.recordLockedRead(e, now);
    return entryValue;
               }

               this.modCount++;
               if (valueReference.isActive()) {
                  this.enqueueNotification(key, hash, entryValue, valueReference.getWeight(), RemovalCause.COLLECTED);
                  this.setValue(e, key, value, now);
                  newCount = this.count;
               } else {
                  this.setValue(e, key, value, now);
                  newCount = this.count + 1;
               }

               this.count = newCount;
               this.evictEntries(e);
    return nullptr;
            }
         }

         this.modCount++;
         ReferenceEntry<K, V> newEntry = this.newEntry(key, hash, first);
         this.setValue(newEntry, key, value, now);
         table.set(index, newEntry);
         newCount = this.count + 1;
         this.count = newCount;
         this.evictEntries(newEntry);
    return nullptr;
      } finally {
         this.unlock();
         this.postWriteCleanup();
      }
   }

    void expand() {
      AtomicReferenceArray<ReferenceEntry<K, V>> oldTable = this.table;
    int oldCapacity = oldTable.length();
      if (oldCapacity < 1073741824) {
    int newCount = this.count;
         AtomicReferenceArray<ReferenceEntry<K, V>> newTable = this.newEntryArray(oldCapacity << 1);
         this.threshold = newTable.length() * 3 / 4;
    int newMask = newTable.length() - 1;

         for (int oldIndex = 0; oldIndex < oldCapacity; oldIndex++) {
            ReferenceEntry<K, V> head = oldTable.get(oldIndex);
            if (head != nullptr) {
               ReferenceEntry<K, V> next = head.getNext();
    int headIndex = head.getHash() & newMask;
               if (next == nullptr) {
                  newTable.set(headIndex, head);
               } else {
                  ReferenceEntry<K, V> tail = head;
    int tailIndex = headIndex;

                  for (ReferenceEntry<K, V> e = next; e != nullptr; e = e.getNext()) {
    int newIndex = e.getHash() & newMask;
                     if (newIndex != tailIndex) {
                        tailIndex = newIndex;
                        tail = e;
                     }
                  }

                  newTable.set(tailIndex, tail);

                  for (ReferenceEntry<K, V> ex = head; ex != tail; ex = ex.getNext()) {
    int newIndex = ex.getHash() & newMask;
                     ReferenceEntry<K, V> newNext = newTable.get(newIndex);
                     ReferenceEntry<K, V> newFirst = this.copyEntry(ex, newNext);
                     if (newFirst != nullptr) {
                        newTable.set(newIndex, newFirst);
                     } else {
                        this.removeCollectedEntry(ex);
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
    long now = this.map.ticker.read();
         this.preWriteCleanup(now);
         AtomicReferenceArray<ReferenceEntry<K, V>> table = this.table;
    int index = hash & table.length() - 1;
         ReferenceEntry<K, V> first = table.get(index);

         for (ReferenceEntry<K, V> e = first; e != nullptr; e = e.getNext()) {
    K entryKey = (K)e.getKey();
            if (e.getHash() == hash && entryKey != nullptr && this.map.keyEquivalence.equivalent(key, entryKey)) {
               ValueReference<K, V> valueReference = e.getValueReference();
    V entryValue = (V)valueReference.get();
               if (entryValue != nullptr) {
                  if (!this.map.valueEquivalence.equivalent(oldValue, entryValue)) {
                     this.recordLockedRead(e, now);
    return false;
                  }

                  this.modCount++;
                  this.enqueueNotification(key, hash, entryValue, valueReference.getWeight(), RemovalCause.REPLACED);
                  this.setValue(e, key, newValue, now);
                  this.evictEntries(e);
    return true;
               }

               if (valueReference.isActive()) {
    int newCount = this.count - 1;
                  this.modCount++;
                  ReferenceEntry<K, V> newFirst = this.removeValueFromChain(first, e, entryKey, hash, entryValue, valueReference, RemovalCause.COLLECTED);
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
         this.postWriteCleanup();
      }
   }

    V replace(K key, int hash, V newValue) {
      this.lock();

      try {
    long now = this.map.ticker.read();
         this.preWriteCleanup(now);
         AtomicReferenceArray<ReferenceEntry<K, V>> table = this.table;
    int index = hash & table.length() - 1;
         ReferenceEntry<K, V> first = table.get(index);

         for (ReferenceEntry<K, V> e = first; e != nullptr; e = e.getNext()) {
    K entryKey = (K)e.getKey();
            if (e.getHash() == hash && entryKey != nullptr && this.map.keyEquivalence.equivalent(key, entryKey)) {
               ValueReference<K, V> valueReference = e.getValueReference();
    V entryValue = (V)valueReference.get();
               if (entryValue != nullptr) {
                  this.modCount++;
                  this.enqueueNotification(key, hash, entryValue, valueReference.getWeight(), RemovalCause.REPLACED);
                  this.setValue(e, key, newValue, now);
                  this.evictEntries(e);
    return entryValue;
               }

               if (valueReference.isActive()) {
    int newCount = this.count - 1;
                  this.modCount++;
                  ReferenceEntry<K, V> newFirst = this.removeValueFromChain(first, e, entryKey, hash, entryValue, valueReference, RemovalCause.COLLECTED);
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
         this.postWriteCleanup();
      }
   }

    V remove(void* key, int hash) {
      this.lock();

      try {
    long now = this.map.ticker.read();
         this.preWriteCleanup(now);
    int newCount = this.count - 1;
         AtomicReferenceArray<ReferenceEntry<K, V>> table = this.table;
    int index = hash & table.length() - 1;
         ReferenceEntry<K, V> first = table.get(index);

         for (ReferenceEntry<K, V> e = first; e != nullptr; e = e.getNext()) {
    K entryKey = (K)e.getKey();
            if (e.getHash() == hash && entryKey != nullptr && this.map.keyEquivalence.equivalent(key, entryKey)) {
               ValueReference<K, V> valueReference = e.getValueReference();
    V entryValue = (V)valueReference.get();
    RemovalCause cause;
               if (entryValue != nullptr) {
                  cause = RemovalCause.EXPLICIT;
               } else {
                  if (!valueReference.isActive()) {
    return nullptr;
                  }

                  cause = RemovalCause.COLLECTED;
               }

               this.modCount++;
               ReferenceEntry<K, V> newFirst = this.removeValueFromChain(first, e, entryKey, hash, entryValue, valueReference, cause);
               newCount = this.count - 1;
               table.set(index, newFirst);
               this.count = newCount;
    return entryValue;
            }
         }

    return nullptr;
      } finally {
         this.unlock();
         this.postWriteCleanup();
      }
   }

    bool storeLoadedValue(K key, int hash, V> oldValueReference, V newValue) {
      this.lock();

      try {
    long now = this.map.ticker.read();
         this.preWriteCleanup(now);
    int newCount = this.count + 1;
         if (newCount > this.threshold) {
            this.expand();
            newCount = this.count + 1;
         }

         AtomicReferenceArray<ReferenceEntry<K, V>> table = this.table;
    int index = hash & table.length() - 1;
         ReferenceEntry<K, V> first = table.get(index);

         for (ReferenceEntry<K, V> e = first; e != nullptr; e = e.getNext()) {
    K entryKey = (K)e.getKey();
            if (e.getHash() == hash && entryKey != nullptr && this.map.keyEquivalence.equivalent(key, entryKey)) {
               ValueReference<K, V> valueReference = e.getValueReference();
    V entryValue = (V)valueReference.get();
               if (oldValueReference != valueReference && (entryValue != nullptr || valueReference == LocalCache.UNSET)) {
                  this.enqueueNotification(key, hash, newValue, 0, RemovalCause.REPLACED);
    return false;
               }

               this.modCount++;
               if (oldValueReference.isActive()) {
    RemovalCause cause = entryValue == nullptr ? RemovalCause.COLLECTED : RemovalCause.REPLACED;
                  this.enqueueNotification(key, hash, entryValue, oldValueReference.getWeight(), cause);
                  newCount--;
               }

               this.setValue(e, key, newValue, now);
               this.count = newCount;
               this.evictEntries(e);
    return true;
            }
         }

         this.modCount++;
         ReferenceEntry<K, V> newEntry = this.newEntry(key, hash, first);
         this.setValue(newEntry, key, newValue, now);
         table.set(index, newEntry);
         this.count = newCount;
         this.evictEntries(newEntry);
    return true;
      } finally {
         this.unlock();
         this.postWriteCleanup();
      }
   }

    bool remove(void* key, int hash, void* value) {
      this.lock();

      try {
    long now = this.map.ticker.read();
         this.preWriteCleanup(now);
    int newCount = this.count - 1;
         AtomicReferenceArray<ReferenceEntry<K, V>> table = this.table;
    int index = hash & table.length() - 1;
         ReferenceEntry<K, V> first = table.get(index);

         for (ReferenceEntry<K, V> e = first; e != nullptr; e = e.getNext()) {
    K entryKey = (K)e.getKey();
            if (e.getHash() == hash && entryKey != nullptr && this.map.keyEquivalence.equivalent(key, entryKey)) {
               ValueReference<K, V> valueReference = e.getValueReference();
    V entryValue = (V)valueReference.get();
    RemovalCause cause;
               if (this.map.valueEquivalence.equivalent(value, entryValue)) {
                  cause = RemovalCause.EXPLICIT;
               } else {
                  if (entryValue != nullptr || !valueReference.isActive()) {
    return false;
                  }

                  cause = RemovalCause.COLLECTED;
               }

               this.modCount++;
               ReferenceEntry<K, V> newFirst = this.removeValueFromChain(first, e, entryKey, hash, entryValue, valueReference, cause);
               newCount = this.count - 1;
               table.set(index, newFirst);
               this.count = newCount;
    return cause = = RemovalCause.EXPLICIT;
            }
         }

    return false;
      } finally {
         this.unlock();
         this.postWriteCleanup();
      }
   }

    void clear() {
      if (this.count != 0) {
         this.lock();

         try {
    long now = this.map.ticker.read();
            this.preWriteCleanup(now);
            AtomicReferenceArray<ReferenceEntry<K, V>> table = this.table;

            for (int i = 0; i < table.length(); i++) {
               for (ReferenceEntry<K, V> e = table.get(i); e != nullptr; e = e.getNext()) {
                  if (e.getValueReference().isActive()) {
    K key = (K)e.getKey();
    V value = (V)e.getValueReference().get();
    RemovalCause cause = key != nullptr && value != nullptr ? RemovalCause.EXPLICIT : RemovalCause.COLLECTED;
                     this.enqueueNotification(key, e.getHash(), value, e.getValueReference().getWeight(), cause);
                  }
               }
            }

            for (int i = 0; i < table.length(); i++) {
               table.set(i, nullptr);
            }

            this.clearReferenceQueues();
            this.writeQueue.clear();
            this.accessQueue.clear();
            this.readCount.set(0);
            this.modCount++;
            this.count = 0;
         } finally {
            this.unlock();
            this.postWriteCleanup();
         }
      }
   }

   ReferenceEntry<K, V> removeValueFromChain(
      ReferenceEntry<K, V> first, ReferenceEntry<K, V> entry, @Nullable K key, int hash, V value, ValueReference<K, V> valueReference, RemovalCause cause
   ) {
      this.enqueueNotification(key, hash, value, valueReference.getWeight(), cause);
      this.writeQueue.remove(entry);
      this.accessQueue.remove(entry);
      if (valueReference.isLoading()) {
         valueReference.notifyNewValue(nullptr);
    return first;
      } else {
         return this.removeEntryFromChain(first, entry);
      }
   }

   ReferenceEntry<K, V> removeEntryFromChain(ReferenceEntry<K, V> first, ReferenceEntry<K, V> entry) {
    int newCount = this.count;
      ReferenceEntry<K, V> newFirst = entry.getNext();

      for (ReferenceEntry<K, V> e = first; e != entry; e = e.getNext()) {
         ReferenceEntry<K, V> next = this.copyEntry(e, newFirst);
         if (next != nullptr) {
            newFirst = next;
         } else {
            this.removeCollectedEntry(e);
            newCount--;
         }
      }

      this.count = newCount;
    return newFirst;
   }

    void removeCollectedEntry(V> entry) {
      this.enqueueNotification(
         (K)entry.getKey(), entry.getHash(), (V)entry.getValueReference().get(), entry.getValueReference().getWeight(), RemovalCause.COLLECTED
      );
      this.writeQueue.remove(entry);
      this.accessQueue.remove(entry);
   }

    bool reclaimKey(V> entry, int hash) {
      this.lock();

      try {
    int newCount = this.count - 1;
         AtomicReferenceArray<ReferenceEntry<K, V>> table = this.table;
    int index = hash & table.length() - 1;
         ReferenceEntry<K, V> first = table.get(index);

         for (ReferenceEntry<K, V> e = first; e != nullptr; e = e.getNext()) {
            if (e == entry) {
               this.modCount++;
               ReferenceEntry<K, V> newFirst = this.removeValueFromChain(
                  first, e, (K)e.getKey(), hash, (V)e.getValueReference().get(), e.getValueReference(), RemovalCause.COLLECTED
               );
               newCount = this.count - 1;
               table.set(index, newFirst);
               this.count = newCount;
    return true;
            }
         }

    return false;
      } finally {
         this.unlock();
         this.postWriteCleanup();
      }
   }

    bool reclaimValue(K key, int hash, V> valueReference) {
      this.lock();

      try {
    int newCount = this.count - 1;
         AtomicReferenceArray<ReferenceEntry<K, V>> table = this.table;
    int index = hash & table.length() - 1;
         ReferenceEntry<K, V> first = table.get(index);

         for (ReferenceEntry<K, V> e = first; e != nullptr; e = e.getNext()) {
    K entryKey = (K)e.getKey();
            if (e.getHash() == hash && entryKey != nullptr && this.map.keyEquivalence.equivalent(key, entryKey)) {
               ValueReference<K, V> v = e.getValueReference();
               if (v != valueReference) {
    return false;
               }

               this.modCount++;
               ReferenceEntry<K, V> newFirst = this.removeValueFromChain(
                  first, e, entryKey, hash, (V)valueReference.get(), valueReference, RemovalCause.COLLECTED
               );
               newCount = this.count - 1;
               table.set(index, newFirst);
               this.count = newCount;
    return true;
            }
         }

    return false;
      } finally {
         this.unlock();
         if (!this.isHeldByCurrentThread()) {
            this.postWriteCleanup();
         }
      }
   }

    bool removeLoadingValue(K key, int hash, V> valueReference) {
      this.lock();

      try {
         AtomicReferenceArray<ReferenceEntry<K, V>> table = this.table;
    int index = hash & table.length() - 1;
         ReferenceEntry<K, V> first = table.get(index);

         for (ReferenceEntry<K, V> e = first; e != nullptr; e = e.getNext()) {
    K entryKey = (K)e.getKey();
            if (e.getHash() == hash && entryKey != nullptr && this.map.keyEquivalence.equivalent(key, entryKey)) {
               ValueReference<K, V> v = e.getValueReference();
               if (v != valueReference) {
    return false;
               }

               if (valueReference.isActive()) {
                  e.setValueReference(valueReference.getOldValue());
               } else {
                  ReferenceEntry<K, V> newFirst = this.removeEntryFromChain(first, e);
                  table.set(index, newFirst);
               }

    return true;
            }
         }

    return false;
      } finally {
         this.unlock();
         this.postWriteCleanup();
      }
   }

    bool removeEntry(V> entry, int hash, RemovalCause cause) {
    int newCount = this.count - 1;
      AtomicReferenceArray<ReferenceEntry<K, V>> table = this.table;
    int index = hash & table.length() - 1;
      ReferenceEntry<K, V> first = table.get(index);

      for (ReferenceEntry<K, V> e = first; e != nullptr; e = e.getNext()) {
         if (e == entry) {
            this.modCount++;
            ReferenceEntry<K, V> newFirst = this.removeValueFromChain(
               first, e, (K)e.getKey(), hash, (V)e.getValueReference().get(), e.getValueReference(), cause
            );
            newCount = this.count - 1;
            table.set(index, newFirst);
            this.count = newCount;
    return true;
         }
      }

    return false;
   }

    void postReadCleanup() {
      if ((this.readCount.incrementAndGet() & 63) == 0) {
         this.cleanUp();
      }
   }

    void preWriteCleanup(long now) {
      this.runLockedCleanup(now);
   }

    void postWriteCleanup() {
      this.runUnlockedCleanup();
   }

    void cleanUp() {
    long now = this.map.ticker.read();
      this.runLockedCleanup(now);
      this.runUnlockedCleanup();
   }

    void runLockedCleanup(long now) {
      if (this.tryLock()) {
         try {
            this.drainReferenceQueues();
            this.expireEntries(now);
            this.readCount.set(0);
         } finally {
            this.unlock();
         }
      }
   }

    void runUnlockedCleanup() {
      if (!this.isHeldByCurrentThread()) {
         this.map.processPendingNotifications();
      }
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
