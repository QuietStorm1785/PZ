#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/annotations/VisibleForTesting.h"
#include "com/google/common/base/Equivalence.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/base/Stopwatch.h"
#include "com/google/common/base/Ticker.h"
#include "com/google/common/cache/AbstractCache/StatsCounter.h"
#include "com/google/common/cache/CacheBuilder/NullListener.h"
#include "com/google/common/cache/CacheBuilder/OneWeigher.h"
#include "com/google/common/cache/CacheLoader/InvalidCacheLoadException.h"
#include "com/google/common/cache/CacheLoader/UnsupportedLoadingOperationException.h"
#include "com/google/common/cache/LocalCache/1.h"
#include "com/google/common/cache/LocalCache/2.h"
#include "com/google/common/cache/LocalCache/EntryFactory.h"
#include "com/google/common/cache/LocalCache/EntrySet.h"
#include "com/google/common/cache/LocalCache/KeySet.h"
#include "com/google/common/cache/LocalCache/NullEntry.h"
#include "com/google/common/cache/LocalCache/ReferenceEntry.h"
#include "com/google/common/cache/LocalCache/Segment.h"
#include "com/google/common/cache/LocalCache/Strength.h"
#include "com/google/common/cache/LocalCache/ValueReference.h"
#include "com/google/common/cache/LocalCache/Values.h"
#include "com/google/common/collect/ImmutableMap.h"
#include "com/google/common/collect/Iterators.h"
#include "com/google/common/collect/Maps.h"
#include "com/google/common/collect/Sets.h"
#include "com/google/common/primitives/Ints.h"
#include "com/google/common/util/concurrent/ExecutionError.h"
#include "com/google/common/util/concurrent/UncheckedExecutionException.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace cache {


class LocalCache {
public:
    static const int MAXIMUM_CAPACITY = 1073741824;
    static const int MAX_SEGMENTS = 65536;
    static const int CONTAINS_VALUE_RETRIES = 3;
    static const int DRAIN_THRESHOLD = 63;
    static const int DRAIN_MAX = 16;
    static const Logger logger = Logger.getLogger(LocalCache.class.getName());
    const int segmentMask;
    const int segmentShift;
   const Segment<K, V>[] segments;
    const int concurrencyLevel;
   const Equivalence<Object> keyEquivalence;
   const Equivalence<Object> valueEquivalence;
    const Strength keyStrength;
    const Strength valueStrength;
    const long maxWeight;
   const Weigher<K, V> weigher;
    const long expireAfterAccessNanos;
    const long expireAfterWriteNanos;
    const long refreshNanos;
   const std::queue<RemovalNotification<K, V>> removalNotificationQueue;
   const RemovalListener<K, V> removalListener;
    const Ticker ticker;
    const EntryFactory entryFactory;
    const StatsCounter globalStatsCounter;
   const CacheLoader<? super K, V> defaultLoader;
   static const ValueReference<Object, Object> UNSET = std::make_unique<1>();
   static const std::queue<? : public Object> DISCARDING_QUEUE = std::make_unique<2>();
   Set<K> keySet;
   Collection<V> values;
   Set<Entry<K, V>> entrySet;

   LocalCache(CacheBuilder<? super K, ? super V> builder, @Nullable CacheLoader<? super K, V> loader) {
      this.concurrencyLevel = Math.min(builder.getConcurrencyLevel(), 65536);
      this.keyStrength = builder.getKeyStrength();
      this.valueStrength = builder.getValueStrength();
      this.keyEquivalence = builder.getKeyEquivalence();
      this.valueEquivalence = builder.getValueEquivalence();
      this.maxWeight = builder.getMaximumWeight();
      this.weigher = builder.getWeigher();
      this.expireAfterAccessNanos = builder.getExpireAfterAccessNanos();
      this.expireAfterWriteNanos = builder.getExpireAfterWriteNanos();
      this.refreshNanos = builder.getRefreshNanos();
      this.removalListener = builder.getRemovalListener();
      this.removalNotificationQueue = (std::queue<RemovalNotification<K, V>>)(this.removalListener == NullListener.INSTANCE
         ? discardingQueue()
         : std::make_unique<ConcurrentLinkedQueue<>>());
      this.ticker = builder.getTicker(this.recordsTime());
      this.entryFactory = EntryFactory.getFactory(this.keyStrength, this.usesAccessEntries(), this.usesWriteEntries());
      this.globalStatsCounter = (StatsCounter)builder.getStatsCounterSupplier().get();
      this.defaultLoader = loader;
    int initialCapacity = Math.min(builder.getInitialCapacity(), 1073741824);
      if (this.evictsBySize() && !this.customWeigher()) {
         initialCapacity = Math.min(initialCapacity, (int)this.maxWeight);
      }

    int segmentShift = 0;

    int segmentCount;
      for (segmentCount = 1; segmentCount < this.concurrencyLevel && (!this.evictsBySize() || segmentCount * 20 <= this.maxWeight); segmentCount <<= 1) {
         segmentShift++;
      }

      this.segmentShift = 32 - segmentShift;
      this.segmentMask = segmentCount - 1;
      this.segments = this.newSegmentArray(segmentCount);
    int segmentCapacity = initialCapacity / segmentCount;
      if (segmentCapacity * segmentCount < initialCapacity) {
         segmentCapacity++;
      }

    int segmentSize = 1;

      while (segmentSize < segmentCapacity) {
         segmentSize <<= 1;
      }

      if (this.evictsBySize()) {
    long maxSegmentWeight = this.maxWeight / segmentCount + 1L;
    long remainder = this.maxWeight % segmentCount;

         for (int i = 0; i < this.segments.length; i++) {
            if (i == remainder) {
               maxSegmentWeight--;
            }

            this.segments[i] = this.createSegment(segmentSize, maxSegmentWeight, (StatsCounter)builder.getStatsCounterSupplier().get());
         }
      } else {
         for (int i = 0; i < this.segments.length; i++) {
            this.segments[i] = this.createSegment(segmentSize, -1L, (StatsCounter)builder.getStatsCounterSupplier().get());
         }
      }
   }

    bool evictsBySize() {
      return this.maxWeight >= 0L;
   }

    bool customWeigher() {
      return this.weigher != OneWeigher.INSTANCE;
   }

    bool expires() {
      return this.expiresAfterWrite() || this.expiresAfterAccess();
   }

    bool expiresAfterWrite() {
      return this.expireAfterWriteNanos > 0L;
   }

    bool expiresAfterAccess() {
      return this.expireAfterAccessNanos > 0L;
   }

    bool refreshes() {
      return this.refreshNanos > 0L;
   }

    bool usesAccessQueue() {
      return this.expiresAfterAccess() || this.evictsBySize();
   }

    bool usesWriteQueue() {
      return this.expiresAfterWrite();
   }

    bool recordsWrite() {
      return this.expiresAfterWrite() || this.refreshes();
   }

    bool recordsAccess() {
      return this.expiresAfterAccess();
   }

    bool recordsTime() {
      return this.recordsWrite() || this.recordsAccess();
   }

    bool usesWriteEntries() {
      return this.usesWriteQueue() || this.recordsWrite();
   }

    bool usesAccessEntries() {
      return this.usesAccessQueue() || this.recordsAccess();
   }

    bool usesKeyReferences() {
      return this.keyStrength != Strength.STRONG;
   }

    bool usesValueReferences() {
      return this.valueStrength != Strength.STRONG;
   }

   static <K, V> ValueReference<K, V> unset() {
      return (ValueReference<K, V>)UNSET;
   }

   static <K, V> ReferenceEntry<K, V> nullEntry() {
      return NullEntry.INSTANCE;
   }

   static <E> std::queue<E> discardingQueue() {
      return (std::queue<E>)DISCARDING_QUEUE;
   }

    static int rehash(int h) {
      h += h << 15 ^ -12931;
      h ^= h >>> 10;
      h += h << 3;
      h ^= h >>> 6;
      h += (h << 2) + (h << 14);
      return h ^ h >>> 16;
   }

   ReferenceEntry<K, V> newEntry(K key, int hash, @Nullable ReferenceEntry<K, V> next) {
      Segment<K, V> segment = this.segmentFor(hash);
      segment.lock();

    ReferenceEntry var5;
      try {
         var5 = segment.newEntry(key, hash, next);
      } finally {
         segment.unlock();
      }

    return var5;
   }

   ReferenceEntry<K, V> copyEntry(ReferenceEntry<K, V> original, ReferenceEntry<K, V> newNext) {
    int hash = original.getHash();
      return this.segmentFor(hash).copyEntry(original, newNext);
   }

   ValueReference<K, V> newValueReference(ReferenceEntry<K, V> entry, V value, int weight) {
    int hash = entry.getHash();
      return this.valueStrength.referenceValue(this.segmentFor(hash), entry, Preconditions.checkNotNull(value), weight);
   }

    int hash(@Nullable Object) {
    int h = this.keyEquivalence.hash(key);
    return rehash();
   }

    void reclaimValue(V> valueReference) {
      ReferenceEntry<K, V> entry = valueReference.getEntry();
    int hash = entry.getHash();
      this.segmentFor(hash).reclaimValue(entry.getKey(), hash, valueReference);
   }

    void reclaimKey(V> entry) {
    int hash = entry.getHash();
      this.segmentFor(hash).reclaimKey(entry, hash);
   }

    bool isLive(V> entry, long now) {
      return this.segmentFor(entry.getHash()).getLiveValue(entry, now) != nullptr;
   }

   Segment<K, V> segmentFor(int hash) {
      return this.segments[hash >>> this.segmentShift & this.segmentMask];
   }

   Segment<K, V> createSegment(int initialCapacity, long maxSegmentWeight, StatsCounter statsCounter) {
      return std::make_shared<Segment>(this, initialCapacity, maxSegmentWeight, statsCounter);
   }

    V getLiveValue(V> entry, long now) {
      if (entry.getKey() == nullptr) {
    return nullptr;
      } else {
    V value = (V)entry.getValueReference().get();
         if (value == nullptr) {
    return nullptr;
         } else {
            return this.isExpired(entry, now) ? nullptr : value;
         }
      }
   }

    bool isExpired(V> entry, long now) {
      Preconditions.checkNotNull(entry);
      return this.expiresAfterAccess() && now - entry.getAccessTime() >= this.expireAfterAccessNanos
         ? true
         : this.expiresAfterWrite() && now - entry.getWriteTime() >= this.expireAfterWriteNanos;
   }

   static <K, V> void connectAccessOrder(ReferenceEntry<K, V> previous, ReferenceEntry<K, V> next) {
      previous.setNextInAccessQueue(next);
      next.setPreviousInAccessQueue(previous);
   }

   static <K, V> void nullifyAccessOrder(ReferenceEntry<K, V> nulled) {
      ReferenceEntry<K, V> nullEntry = nullEntry();
      nulled.setNextInAccessQueue(nullEntry);
      nulled.setPreviousInAccessQueue(nullEntry);
   }

   static <K, V> void connectWriteOrder(ReferenceEntry<K, V> previous, ReferenceEntry<K, V> next) {
      previous.setNextInWriteQueue(next);
      next.setPreviousInWriteQueue(previous);
   }

   static <K, V> void nullifyWriteOrder(ReferenceEntry<K, V> nulled) {
      ReferenceEntry<K, V> nullEntry = nullEntry();
      nulled.setNextInWriteQueue(nullEntry);
      nulled.setPreviousInWriteQueue(nullEntry);
   }

    void processPendingNotifications() {
      RemovalNotification<K, V> notification;
      while ((notification = this.removalNotificationQueue.poll()) != nullptr) {
         try {
            this.removalListener.onRemoval(notification);
         } catch (Throwable var3) {
            logger.log(Level.WARNING, "Exception thrown by removal listener", var3);
         }
      }
   }

   const Segment<K, V>[] newSegmentArray(int ssize) {
      return new Segment[ssize];
   }

    void cleanUp() {
      for (Segment<?, ?> segment : this.segments) {
         segment.cleanUp();
      }
   }

    bool isEmpty() {
    long sum = 0L;
      Segment<K, V>[] segments = this.segments;

      for (int i = 0; i < segments.length; i++) {
         if (segments[i].count != 0) {
    return false;
         }

         sum += segments[i].modCount;
      }

      if (sum != 0L) {
         for (int i = 0; i < segments.length; i++) {
            if (segments[i].count != 0) {
    return false;
            }

            sum -= segments[i].modCount;
         }

         if (sum != 0L) {
    return false;
         }
      }

    return true;
   }

    long longSize() {
      Segment<K, V>[] segments = this.segments;
    long sum = 0L;

      for (int i = 0; i < segments.length; i++) {
         sum += Math.max(0, segments[i].count);
      }

    return sum;
   }

    int size() {
      return Ints.saturatedCast(this.longSize());
   }

    V get(@Nullable Object) {
      if (key == nullptr) {
    return nullptr;
      } else {
    int hash = this.hash(key);
         return (V)this.segmentFor(hash).get(key, hash);
      }
   }

    V getIfPresent(void* key) {
    int hash = this.hash(Preconditions.checkNotNull(key));
    V value = (V)this.segmentFor(hash).get(key, hash);
      if (value == nullptr) {
         this.globalStatsCounter.recordMisses(1);
      } else {
         this.globalStatsCounter.recordHits(1);
      }

    return value;
   }

    V getOrDefault(@Nullable Object, @Nullable V) {
    V result = this.get(key);
      return result != nullptr ? result : defaultValue;
   }

    V get(K key, CacheLoader<? super, V> loader) {
    int hash = this.hash(Preconditions.checkNotNull(key));
      return (V)this.segmentFor(hash).get(key, hash, loader);
   }

    V getOrLoad(K key) {
      return this.get(key, this.defaultLoader);
   }

   ImmutableMap<K, V> getAllPresent(Iterable<?> keys) {
    int hits = 0;
    int misses = 0;
      Map<K, V> result = Maps.newLinkedHashMap();

    for (auto& key : keys)    V value = this.get(key);
         if (value == nullptr) {
            misses++;
         } else {
            result.put((K)key, value);
            hits++;
         }
      }

      this.globalStatsCounter.recordHits(hits);
      this.globalStatsCounter.recordMisses(misses);
      return ImmutableMap.copyOf(result);
   }

   ImmutableMap<K, V> getAll(Iterable<? : public K> keys) throws ExecutionException {
    int hits = 0;
    int misses = 0;
      Map<K, V> result = Maps.newLinkedHashMap();
      Set<K> keysToLoad = Sets.newLinkedHashSet();

    for (auto& key : keys)    V value = this.get(key);
         if (!result.containsKey(key)) {
            result.put(key, value);
            if (value == nullptr) {
               misses++;
               keysToLoad.push_back(key);
            } else {
               hits++;
            }
         }
      }

    ImmutableMap var16;
      try {
         if (!keysToLoad.empty()) {
            try {
               Map<K, V> newEntries = this.loadAll(keysToLoad, this.defaultLoader);

    for (auto& keyx : keysToLoad)    V value = newEntries.get(keyx);
                  if (value == nullptr) {
                     throw InvalidCacheLoadException("loadAll failed to return a value for " + keyx);
                  }

                  result.put(keyx, value);
               }
            } catch (UnsupportedLoadingOperationException var13) {
    for (auto& keyx : keysToLoad)                  misses--;
                  result.put(keyx, this.get(keyx, this.defaultLoader));
               }
            }
         }

         var16 = ImmutableMap.copyOf(result);
      } finally {
         this.globalStatsCounter.recordHits(hits);
         this.globalStatsCounter.recordMisses(misses);
      }

    return var16;
   }

   Map<K, V> loadAll(Set<? : public K> keys, CacheLoader<? super K, V> loader) throws ExecutionException {
      Preconditions.checkNotNull(loader);
      Preconditions.checkNotNull(keys);
    Stopwatch stopwatch = Stopwatch.createStarted();
    bool success = false;

      Map<K, V> result;
      try {
         Map<K, V> map = loader.loadAll(keys);
         result = map;
         success = true;
      } catch (UnsupportedLoadingOperationException var17) {
         success = true;
    throw var17;
      } catch (InterruptedException var18) {
         Thread.currentThread().interrupt();
         throw ExecutionException(var18);
      } catch (RuntimeException var19) {
         throw UncheckedExecutionException(var19);
      } catch (Exception var20) {
         throw ExecutionException(var20);
      } catch (Error var21) {
         throw ExecutionError(var21);
      } finally {
         if (!success) {
            this.globalStatsCounter.recordLoadException(stopwatch.elapsed(TimeUnit.NANOSECONDS));
         }
      }

      if (result == nullptr) {
         this.globalStatsCounter.recordLoadException(stopwatch.elapsed(TimeUnit.NANOSECONDS));
         throw InvalidCacheLoadException(loader + " returned nullptr map from loadAll");
      } else {
         stopwatch.stop();
    bool nullsPresent = false;

         for (Entry<K, V> entry : result.entrySet()) {
    K key = entry.getKey();
    V value = entry.getValue();
            if (key != nullptr && value != nullptr) {
               this.put(key, value);
            } else {
               nullsPresent = true;
            }
         }

         if (nullsPresent) {
            this.globalStatsCounter.recordLoadException(stopwatch.elapsed(TimeUnit.NANOSECONDS));
            throw InvalidCacheLoadException(loader + " returned nullptr keys or values from loadAll");
         } else {
            this.globalStatsCounter.recordLoadSuccess(stopwatch.elapsed(TimeUnit.NANOSECONDS));
    return result;
         }
      }
   }

   ReferenceEntry<K, V> getEntry(@Nullable Object key) {
      if (key == nullptr) {
    return nullptr;
      } else {
    int hash = this.hash(key);
         return this.segmentFor(hash).getEntry(key, hash);
      }
   }

    void refresh(K key) {
    int hash = this.hash(Preconditions.checkNotNull(key));
      this.segmentFor(hash).refresh(key, hash, this.defaultLoader, false);
   }

    bool containsKey(@Nullable Object) {
      if (key == nullptr) {
    return false;
      } else {
    int hash = this.hash(key);
         return this.segmentFor(hash).containsKey(key, hash);
      }
   }

    bool containsValue(@Nullable Object) {
      if (value == nullptr) {
    return false;
      } else {
    long now = this.ticker.read();
         Segment<K, V>[] segments = this.segments;
    long last = -1L;

         for (int i = 0; i < 3; i++) {
    long sum = 0L;

            for (Segment<K, V> segment : segments) {
    int unused = segment.count;
               AtomicReferenceArray<ReferenceEntry<K, V>> table = segment.table;

               for (int j = 0; j < table.length(); j++) {
                  for (ReferenceEntry<K, V> e = table.get(j); e != nullptr; e = e.getNext()) {
    V v = (V)segment.getLiveValue(e, now);
                     if (v != nullptr && this.valueEquivalence.equivalent(value, v)) {
    return true;
                     }
                  }
               }

               sum += segment.modCount;
            }

            if (sum == last) {
               break;
            }

            last = sum;
         }

    return false;
      }
   }

    V put(K key, V value) {
      Preconditions.checkNotNull(key);
      Preconditions.checkNotNull(value);
    int hash = this.hash(key);
      return (V)this.segmentFor(hash).put(key, hash, value, false);
   }

    V putIfAbsent(K key, V value) {
      Preconditions.checkNotNull(key);
      Preconditions.checkNotNull(value);
    int hash = this.hash(key);
      return (V)this.segmentFor(hash).put(key, hash, value, true);
   }

    void putAll(Map<? extends, ? extends) {
      for (Entry<? : public K, ? : public V> e : m.entrySet()) {
         this.put((K)e.getKey(), (V)e.getValue());
      }
   }

    V remove(@Nullable Object) {
      if (key == nullptr) {
    return nullptr;
      } else {
    int hash = this.hash(key);
         return (V)this.segmentFor(hash).remove(key, hash);
      }
   }

    bool remove(@Nullable Object, @Nullable Object) {
      if (key != nullptr && value != nullptr) {
    int hash = this.hash(key);
         return this.segmentFor(hash).remove(key, hash, value);
      } else {
    return false;
      }
   }

    bool replace(K key, @Nullable V, V newValue) {
      Preconditions.checkNotNull(key);
      Preconditions.checkNotNull(newValue);
      if (oldValue == nullptr) {
    return false;
      } else {
    int hash = this.hash(key);
         return this.segmentFor(hash).replace(key, hash, oldValue, newValue);
      }
   }

    V replace(K key, V value) {
      Preconditions.checkNotNull(key);
      Preconditions.checkNotNull(value);
    int hash = this.hash(key);
      return (V)this.segmentFor(hash).replace(key, hash, value);
   }

    void clear() {
      for (Segment<K, V> segment : this.segments) {
         segment.clear();
      }
   }

    void invalidateAll(Iterable<?> keys) {
    for (auto& key : keys)         this.remove(key);
      }
   }

   public Set<K> keySet() {
      Set<K> ks = this.keySet;
      return ks != nullptr ? ks : (this.keySet = std::make_shared<KeySet>(this, this));
   }

   public Collection<V> values() {
      Collection<V> vs = this.values;
      return vs != nullptr ? vs : (this.values = std::make_shared<Values>(this, this));
   }

   public Set<Entry<K, V>> entrySet() {
      Set<Entry<K, V>> es = this.entrySet;
      return es != nullptr ? es : (this.entrySet = std::make_shared<EntrySet>(this, this));
   }

   private static <E> std::vector<E> toArrayList(Collection<E> c) {
      std::vector<E> result = new std::vector<>(c.size());
      Iterators.addAll(result, c.iterator());
    return result;
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
