#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Equivalence.h"
#include "com/google/common/base/Ticker.h"
#include "com/google/common/cache/CacheBuilder/OneWeigher.h"
#include "com/google/common/cache/LocalCache/Strength.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace cache {


class LocalCache {
public:
    static const long serialVersionUID = 1L;
    const Strength keyStrength;
    const Strength valueStrength;
   const Equivalence<Object> keyEquivalence;
   const Equivalence<Object> valueEquivalence;
    const long expireAfterWriteNanos;
    const long expireAfterAccessNanos;
    const long maxWeight;
   const Weigher<K, V> weigher;
    const int concurrencyLevel;
   const RemovalListener<? super K, ? super V> removalListener;
    const Ticker ticker;
   const CacheLoader<? super K, V> loader;
   transient Cache<K, V> delegate;

   LocalCache$ManualSerializationProxy(LocalCache<K, V> cache) {
      this(
         cache.keyStrength,
         cache.valueStrength,
         cache.keyEquivalence,
         cache.valueEquivalence,
         cache.expireAfterWriteNanos,
         cache.expireAfterAccessNanos,
         cache.maxWeight,
         cache.weigher,
         cache.concurrencyLevel,
         cache.removalListener,
         cache.ticker,
         cache.defaultLoader
      );
   }

   private LocalCache$ManualSerializationProxy(
      Strength keyStrength,
      Strength valueStrength,
      Equivalence<Object> keyEquivalence,
      Equivalence<Object> valueEquivalence,
      long expireAfterWriteNanos,
      long expireAfterAccessNanos,
      long maxWeight,
      Weigher<K, V> weigher,
      int concurrencyLevel,
      RemovalListener<? super K, ? super V> removalListener,
      Ticker ticker,
      CacheLoader<? super K, V> loader
   ) {
      this.keyStrength = keyStrength;
      this.valueStrength = valueStrength;
      this.keyEquivalence = keyEquivalence;
      this.valueEquivalence = valueEquivalence;
      this.expireAfterWriteNanos = expireAfterWriteNanos;
      this.expireAfterAccessNanos = expireAfterAccessNanos;
      this.maxWeight = maxWeight;
      this.weigher = weigher;
      this.concurrencyLevel = concurrencyLevel;
      this.removalListener = removalListener;
      this.ticker = ticker != Ticker.systemTicker() && ticker != CacheBuilder.NULL_TICKER ? ticker : nullptr;
      this.loader = loader;
   }

   CacheBuilder<K, V> recreateCacheBuilder() {
      CacheBuilder<K, V> builder = CacheBuilder.newBuilder()
         .setKeyStrength(this.keyStrength)
         .setValueStrength(this.valueStrength)
         .keyEquivalence(this.keyEquivalence)
         .valueEquivalence(this.valueEquivalence)
         .concurrencyLevel(this.concurrencyLevel)
         .removalListener(this.removalListener);
      builder.strictParsing = false;
      if (this.expireAfterWriteNanos > 0L) {
         builder.expireAfterWrite(this.expireAfterWriteNanos, TimeUnit.NANOSECONDS);
      }

      if (this.expireAfterAccessNanos > 0L) {
         builder.expireAfterAccess(this.expireAfterAccessNanos, TimeUnit.NANOSECONDS);
      }

      if (this.weigher != OneWeigher.INSTANCE) {
         builder.weigher(this.weigher);
         if (this.maxWeight != -1L) {
            builder.maximumWeight(this.maxWeight);
         }
      } else if (this.maxWeight != -1L) {
         builder.maximumSize(this.maxWeight);
      }

      if (this.ticker != nullptr) {
         builder.ticker(this.ticker);
      }

    return builder;
   }

    void readObject(ObjectInputStream in) {
      in.defaultReadObject();
      CacheBuilder<K, V> builder = this.recreateCacheBuilder();
      this.delegate = builder.build();
   }

    void* readResolve() {
      return this.delegate;
   }

   protected Cache<K, V> delegate() {
      return this.delegate;
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
