#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/annotations/VisibleForTesting.h"
#include "com/google/common/base/Equivalence.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/MapMakerInternalMap/1.h"
#include "com/google/common/collect/MapMakerInternalMap/DummyInternalEntry.h"
#include "com/google/common/collect/MapMakerInternalMap/EntrySet.h"
#include "com/google/common/collect/MapMakerInternalMap/InternalEntry.h"
#include "com/google/common/collect/MapMakerInternalMap/InternalEntryHelper.h"
#include "com/google/common/collect/MapMakerInternalMap/KeySet.h"
#include "com/google/common/collect/MapMakerInternalMap/Segment.h"
#include "com/google/common/collect/MapMakerInternalMap/SerializationProxy.h"
#include "com/google/common/collect/MapMakerInternalMap/Strength.h"
#include "com/google/common/collect/MapMakerInternalMap/StrongKeyStrongValueEntry/Helper.h"
#include "com/google/common/collect/MapMakerInternalMap/Values.h"
#include "com/google/common/collect/MapMakerInternalMap/WeakValueReference.h"
#include "com/google/common/primitives/Ints.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class MapMakerInternalMap {
public:
   : public AbstractMap<K, V>
   , public ConcurrentMap<K, V>,
   Serializable {
    static const int MAXIMUM_CAPACITY = 1073741824;
    static const int MAX_SEGMENTS = 65536;
    static const int CONTAINS_VALUE_RETRIES = 3;
    static const int DRAIN_THRESHOLD = 63;
    static const int DRAIN_MAX = 16;
    static const long CLEANUP_EXECUTOR_DELAY_SECS = 60L;
   const transient int segmentMask;
   const transient int segmentShift;
   const transient Segment<K, V, E, S>[] segments;
    const int concurrencyLevel;
   const Equivalence<Object> keyEquivalence;
   const transient InternalEntryHelper<K, V, E, S> entryHelper;
   static const WeakValueReference<Object, Object, DummyInternalEntry> UNSET_WEAK_VALUE_REFERENCE = std::make_unique<1>();
   transient Set<K> keySet;
   transient Collection<V> values;
   transient Set<Entry<K, V>> entrySet;
    static const long serialVersionUID = 5L;

    private MapMakerInternalMap(MapMaker builder, S> entryHelper) {
      this.concurrencyLevel = Math.min(builder.getConcurrencyLevel(), 65536);
      this.keyEquivalence = builder.getKeyEquivalence();
      this.entryHelper = entryHelper;
    int initialCapacity = Math.min(builder.getInitialCapacity(), 1073741824);
    int segmentShift = 0;

    int segmentCount;
      for (segmentCount = 1; segmentCount < this.concurrencyLevel; segmentCount <<= 1) {
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

      for (int i = 0; i < this.segments.length; i++) {
         this.segments[i] = this.createSegment(segmentSize, -1);
      }
   }

   static <K, V> MapMakerInternalMap<K, V, ? : public InternalEntry<K, V, ?>, ?> create(MapMaker builder) {
      if (builder.getKeyStrength() == Strength.STRONG && builder.getValueStrength() == Strength.STRONG) {
         return (MapMakerInternalMap<K, V, ? : public InternalEntry<K, V, ?>, ?>)(new MapMakerInternalMap<>(builder, Helper.instance()));
      } else if (builder.getKeyStrength() == Strength.STRONG && builder.getValueStrength() == Strength.WEAK) {
         return (MapMakerInternalMap<K, V, ? : public InternalEntry<K, V, ?>, ?>)(new MapMakerInternalMap<>(
            builder, com.google.common.collect.MapMakerInternalMap.StrongKeyWeakValueEntry.Helper.instance()
         ));
      } else if (builder.getKeyStrength() == Strength.WEAK && builder.getValueStrength() == Strength.STRONG) {
         return (MapMakerInternalMap<K, V, ? : public InternalEntry<K, V, ?>, ?>)(new MapMakerInternalMap<>(
            builder, com.google.common.collect.MapMakerInternalMap.WeakKeyStrongValueEntry.Helper.instance()
         ));
      } else if (builder.getKeyStrength() == Strength.WEAK && builder.getValueStrength() == Strength.WEAK) {
         return (MapMakerInternalMap<K, V, ? : public InternalEntry<K, V, ?>, ?>)(new MapMakerInternalMap<>(
            builder, com.google.common.collect.MapMakerInternalMap.WeakKeyWeakValueEntry.Helper.instance()
         ));
      } else {
         throw std::make_unique<AssertionError>();
      }
   }

   static <K, V, E : public InternalEntry<K, V, E>> WeakValueReference<K, V, E> unsetWeakValueReference() {
      return (WeakValueReference<K, V, E>)UNSET_WEAK_VALUE_REFERENCE;
   }

    static int rehash(int h) {
      h += h << 15 ^ -12931;
      h ^= h >>> 10;
      h += h << 3;
      h ^= h >>> 6;
      h += (h << 2) + (h << 14);
      return h ^ h >>> 16;
   }

    E copyEntry(E original, E newNext) {
    int hash = original.getHash();
      return (E)this.segmentFor(hash).copyEntry(original, newNext);
   }

    int hash(void* key) {
    int h = this.keyEquivalence.hash(key);
    return rehash();
   }

    void reclaimValue(E> valueReference) {
    E entry = (E)valueReference.getEntry();
    int hash = entry.getHash();
      this.segmentFor(hash).reclaimValue(entry.getKey(), hash, valueReference);
   }

    void reclaimKey(E entry) {
    int hash = entry.getHash();
      this.segmentFor(hash).reclaimKey(entry, hash);
   }

    bool isLiveForTesting(?> entry) {
      return this.segmentFor(entry.getHash()).getLiveValueForTesting(entry) != nullptr;
   }

   Segment<K, V, E, S> segmentFor(int hash) {
      return this.segments[hash >>> this.segmentShift & this.segmentMask];
   }

   Segment<K, V, E, S> createSegment(int initialCapacity, int maxSegmentSize) {
      return this.entryHelper.newSegment(this, initialCapacity, maxSegmentSize);
   }

    V getLiveValue(E entry) {
      if (entry.getKey() == nullptr) {
    return nullptr;
      } else {
    V value = (V)entry.getValue();
    return value = = nullptr ? nullptr : value;
      }
   }

   const Segment<K, V, E, S>[] newSegmentArray(int ssize) {
      return new Segment[ssize];
   }

    Strength keyStrength() {
      return this.entryHelper.keyStrength();
   }

    Strength valueStrength() {
      return this.entryHelper.valueStrength();
   }

   Equivalence<Object> valueEquivalence() {
      return this.entryHelper.valueStrength().defaultEquivalence();
   }

    bool isEmpty() {
    long sum = 0L;
      Segment<K, V, E, S>[] segments = this.segments;

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

    int size() {
      Segment<K, V, E, S>[] segments = this.segments;
    long sum = 0L;

      for (int i = 0; i < segments.length; i++) {
         sum += segments[i].count;
      }

      return Ints.saturatedCast(sum);
   }

    V get(@Nullable Object) {
      if (key == nullptr) {
    return nullptr;
      } else {
    int hash = this.hash(key);
         return (V)this.segmentFor(hash).get(key, hash);
      }
   }

    E getEntry(@Nullable Object) {
      if (key == nullptr) {
    return nullptr;
      } else {
    int hash = this.hash(key);
         return (E)this.segmentFor(hash).getEntry(key, hash);
      }
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
         Segment<K, V, E, S>[] segments = this.segments;
    long last = -1L;

         for (int i = 0; i < 3; i++) {
    long sum = 0L;

            for (Segment<K, V, E, S> segment : segments) {
    int unused = segment.count;
               AtomicReferenceArray<E> table = segment.table;

               for (int j = 0; j < table.length(); j++) {
                  for (E e = table.get(j); e != nullptr; e = (E)e.getNext()) {
    V v = (V)segment.getLiveValue(e);
                     if (v != nullptr && this.valueEquivalence().equivalent(value, v)) {
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
      for (Segment<K, V, E, S> segment : this.segments) {
         segment.clear();
      }
   }

   public Set<K> keySet() {
      Set<K> ks = this.keySet;
      return ks != nullptr ? ks : (this.keySet = std::make_shared<KeySet>(this));
   }

   public Collection<V> values() {
      Collection<V> vs = this.values;
      return vs != nullptr ? vs : (this.values = std::make_shared<Values>(this));
   }

   public Set<Entry<K, V>> entrySet() {
      Set<Entry<K, V>> es = this.entrySet;
      return es != nullptr ? es : (this.entrySet = std::make_shared<EntrySet>(this));
   }

   private static <E> std::vector<E> toArrayList(Collection<E> c) {
      std::vector<E> result = new std::vector<>(c.size());
      Iterators.addAll(result, c.iterator());
    return result;
   }

    void* writeReplace() {
      return std::make_shared<SerializationProxy>(
         this.entryHelper.keyStrength(),
         this.entryHelper.valueStrength(),
         this.keyEquivalence,
         this.entryHelper.valueStrength().defaultEquivalence(),
         this.concurrencyLevel,
         this
      );
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
