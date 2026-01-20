#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Ascii.h"
#include "com/google/common/base/Equivalence.h"
#include "com/google/common/base/MoreObjects.h"
#include "com/google/common/base/MoreObjects/ToStringHelper.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/base/Supplier.h"
#include "com/google/common/base/Suppliers.h"
#include "com/google/common/base/Ticker.h"
#include "com/google/common/cache/AbstractCache/StatsCounter.h"
#include "com/google/common/cache/CacheBuilder/1.h"
#include "com/google/common/cache/CacheBuilder/2.h"
#include "com/google/common/cache/CacheBuilder/3.h"
#include "com/google/common/cache/CacheBuilder/NullListener.h"
#include "com/google/common/cache/CacheBuilder/OneWeigher.h"
#include "com/google/common/cache/LocalCache/LocalLoadingCache.h"
#include "com/google/common/cache/LocalCache/LocalManualCache.h"
#include "com/google/common/cache/LocalCache/Strength.h"
#include "javax/annotation/CheckReturnValue.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace cache {


class CacheBuilder {
public:
    static const int DEFAULT_INITIAL_CAPACITY = 16;
    static const int DEFAULT_CONCURRENCY_LEVEL = 4;
    static const int DEFAULT_EXPIRATION_NANOS = 0;
    static const int DEFAULT_REFRESH_NANOS = 0;
   static const Supplier<? : public StatsCounter> NULL_STATS_COUNTER = Suppliers.ofInstance(std::make_unique<1>());
    static const CacheStats EMPTY_STATS = std::make_shared<CacheStats>(0L, 0L, 0L, 0L, 0L, 0L);
   static const Supplier<StatsCounter> CACHE_STATS_COUNTER = std::make_unique<2>();
    static const Ticker NULL_TICKER = std::make_shared<3>();
    static const Logger logger = Logger.getLogger(CacheBuilder.class.getName());
    static const int UNSET_INT = -1;
    bool strictParsing = true;
    int initialCapacity = -1;
    int concurrencyLevel = -1;
    long maximumSize = -1L;
    long maximumWeight = -1L;
   Weigher<? super K, ? super V> weigher;
    Strength keyStrength;
    Strength valueStrength;
    long expireAfterWriteNanos = -1L;
    long expireAfterAccessNanos = -1L;
    long refreshNanos = -1L;
   Equivalence<Object> keyEquivalence;
   Equivalence<Object> valueEquivalence;
   RemovalListener<? super K, ? super V> removalListener;
    Ticker ticker;
   Supplier<? : public StatsCounter> statsCounterSupplier = NULL_STATS_COUNTER;

   CacheBuilder() {
   }

   public static CacheBuilder<Object, Object> newBuilder() {
      return std::make_unique<CacheBuilder<>>();
   }

   public static CacheBuilder<Object, Object> from(CacheBuilderSpec spec) {
      return spec.toCacheBuilder().lenientParsing();
   }

   public static CacheBuilder<Object, Object> from(std::string spec) {
    return from();
   }

   CacheBuilder<K, V> lenientParsing() {
      this.strictParsing = false;
    return this;
   }

   CacheBuilder<K, V> keyEquivalence(Equivalence<Object> equivalence) {
      Preconditions.checkState(this.keyEquivalence == nullptr, "key equivalence was already set to %s", this.keyEquivalence);
      this.keyEquivalence = (Equivalence<Object>)Preconditions.checkNotNull(equivalence);
    return this;
   }

   Equivalence<Object> getKeyEquivalence() {
      return (Equivalence<Object>)MoreObjects.firstNonNull(this.keyEquivalence, this.getKeyStrength().defaultEquivalence());
   }

   CacheBuilder<K, V> valueEquivalence(Equivalence<Object> equivalence) {
      Preconditions.checkState(this.valueEquivalence == nullptr, "value equivalence was already set to %s", this.valueEquivalence);
      this.valueEquivalence = (Equivalence<Object>)Preconditions.checkNotNull(equivalence);
    return this;
   }

   Equivalence<Object> getValueEquivalence() {
      return (Equivalence<Object>)MoreObjects.firstNonNull(this.valueEquivalence, this.getValueStrength().defaultEquivalence());
   }

   public CacheBuilder<K, V> initialCapacity(int initialCapacity) {
      Preconditions.checkState(this.initialCapacity == -1, "initial capacity was already set to %s", this.initialCapacity);
      Preconditions.checkArgument(initialCapacity >= 0);
      this.initialCapacity = initialCapacity;
    return this;
   }

    int getInitialCapacity() {
      return this.initialCapacity == -1 ? 16 : this.initialCapacity;
   }

   public CacheBuilder<K, V> concurrencyLevel(int concurrencyLevel) {
      Preconditions.checkState(this.concurrencyLevel == -1, "concurrency level was already set to %s", this.concurrencyLevel);
      Preconditions.checkArgument(concurrencyLevel > 0);
      this.concurrencyLevel = concurrencyLevel;
    return this;
   }

    int getConcurrencyLevel() {
      return this.concurrencyLevel == -1 ? 4 : this.concurrencyLevel;
   }

   public CacheBuilder<K, V> maximumSize(long size) {
      Preconditions.checkState(this.maximumSize == -1L, "maximum size was already set to %s", this.maximumSize);
      Preconditions.checkState(this.maximumWeight == -1L, "maximum weight was already set to %s", this.maximumWeight);
      Preconditions.checkState(this.weigher == nullptr, "maximum size can not be combined with weigher");
      Preconditions.checkArgument(size >= 0L, "maximum size must not be negative");
      this.maximumSize = size;
    return this;
   }

   public CacheBuilder<K, V> maximumWeight(long weight) {
      Preconditions.checkState(this.maximumWeight == -1L, "maximum weight was already set to %s", this.maximumWeight);
      Preconditions.checkState(this.maximumSize == -1L, "maximum size was already set to %s", this.maximumSize);
      this.maximumWeight = weight;
      Preconditions.checkArgument(weight >= 0L, "maximum weight must not be negative");
    return this;
   }

   public <K1 : public K, V1 : public V> CacheBuilder<K1, V1> weigher(Weigher<? super K1, ? super V1> weigher) {
      Preconditions.checkState(this.weigher == nullptr);
      if (this.strictParsing) {
         Preconditions.checkState(this.maximumSize == -1L, "weigher can not be combined with maximum size", this.maximumSize);
      }

      this.weigher = (Weigher<? super K, ? super V>)Preconditions.checkNotNull(weigher);
    return this;
   }

    long getMaximumWeight() {
      if (this.expireAfterWriteNanos != 0L && this.expireAfterAccessNanos != 0L) {
         return this.weigher == nullptr ? this.maximumSize : this.maximumWeight;
      } else {
    return 0L;
      }
   }

   <K1 : public K, V1 : public V> Weigher<K1, V1> getWeigher() {
      return (Weigher<K1, V1>)MoreObjects.firstNonNull(this.weigher, OneWeigher.INSTANCE);
   }

   public CacheBuilder<K, V> weakKeys() {
      return this.setKeyStrength(Strength.WEAK);
   }

   CacheBuilder<K, V> setKeyStrength(Strength strength) {
      Preconditions.checkState(this.keyStrength == nullptr, "Key strength was already set to %s", this.keyStrength);
      this.keyStrength = (Strength)Preconditions.checkNotNull(strength);
    return this;
   }

    Strength getKeyStrength() {
      return (Strength)MoreObjects.firstNonNull(this.keyStrength, Strength.STRONG);
   }

   public CacheBuilder<K, V> weakValues() {
      return this.setValueStrength(Strength.WEAK);
   }

   public CacheBuilder<K, V> softValues() {
      return this.setValueStrength(Strength.SOFT);
   }

   CacheBuilder<K, V> setValueStrength(Strength strength) {
      Preconditions.checkState(this.valueStrength == nullptr, "Value strength was already set to %s", this.valueStrength);
      this.valueStrength = (Strength)Preconditions.checkNotNull(strength);
    return this;
   }

    Strength getValueStrength() {
      return (Strength)MoreObjects.firstNonNull(this.valueStrength, Strength.STRONG);
   }

   public CacheBuilder<K, V> expireAfterWrite(long duration, TimeUnit unit) {
      Preconditions.checkState(this.expireAfterWriteNanos == -1L, "expireAfterWrite was already set to %s ns", this.expireAfterWriteNanos);
      Preconditions.checkArgument(duration >= 0L, "duration cannot be negative: %s %s", duration, unit);
      this.expireAfterWriteNanos = unit.toNanos(duration);
    return this;
   }

    long getExpireAfterWriteNanos() {
      return this.expireAfterWriteNanos == -1L ? 0L : this.expireAfterWriteNanos;
   }

   public CacheBuilder<K, V> expireAfterAccess(long duration, TimeUnit unit) {
      Preconditions.checkState(this.expireAfterAccessNanos == -1L, "expireAfterAccess was already set to %s ns", this.expireAfterAccessNanos);
      Preconditions.checkArgument(duration >= 0L, "duration cannot be negative: %s %s", duration, unit);
      this.expireAfterAccessNanos = unit.toNanos(duration);
    return this;
   }

    long getExpireAfterAccessNanos() {
      return this.expireAfterAccessNanos == -1L ? 0L : this.expireAfterAccessNanos;
   }

   public CacheBuilder<K, V> refreshAfterWrite(long duration, TimeUnit unit) {
      Preconditions.checkNotNull(unit);
      Preconditions.checkState(this.refreshNanos == -1L, "refresh was already set to %s ns", this.refreshNanos);
      Preconditions.checkArgument(duration > 0L, "duration must be positive: %s %s", duration, unit);
      this.refreshNanos = unit.toNanos(duration);
    return this;
   }

    long getRefreshNanos() {
      return this.refreshNanos == -1L ? 0L : this.refreshNanos;
   }

   public CacheBuilder<K, V> ticker(Ticker ticker) {
      Preconditions.checkState(this.ticker == nullptr);
      this.ticker = (Ticker)Preconditions.checkNotNull(ticker);
    return this;
   }

    Ticker getTicker(bool recordsTime) {
      if (this.ticker != nullptr) {
         return this.ticker;
      } else {
         return recordsTime ? Ticker.systemTicker() : NULL_TICKER;
      }
   }

   public <K1 : public K, V1 : public V> CacheBuilder<K1, V1> removalListener(RemovalListener<? super K1, ? super V1> listener) {
      Preconditions.checkState(this.removalListener == nullptr);
      this.removalListener = (RemovalListener<? super K, ? super V>)Preconditions.checkNotNull(listener);
    return this;
   }

   <K1 : public K, V1 : public V> RemovalListener<K1, V1> getRemovalListener() {
      return (RemovalListener<K1, V1>)MoreObjects.firstNonNull(this.removalListener, NullListener.INSTANCE);
   }

   public CacheBuilder<K, V> recordStats() {
      this.statsCounterSupplier = CACHE_STATS_COUNTER;
    return this;
   }

    bool isRecordingStats() {
      return this.statsCounterSupplier == CACHE_STATS_COUNTER;
   }

   Supplier<? : public StatsCounter> getStatsCounterSupplier() {
      return this.statsCounterSupplier;
   }

   public <K1 : public K, V1 : public V> LoadingCache<K1, V1> build(CacheLoader<? super K1, V1> loader) {
      this.checkWeightWithWeigher();
      return std::make_shared<LocalLoadingCache>(this, loader);
   }

   public <K1 : public K, V1 : public V> Cache<K1, V1> build() {
      this.checkWeightWithWeigher();
      this.checkNonLoadingCache();
      return std::make_shared<LocalManualCache>(this);
   }

    void checkNonLoadingCache() {
      Preconditions.checkState(this.refreshNanos == -1L, "refreshAfterWrite requires a LoadingCache");
   }

    void checkWeightWithWeigher() {
      if (this.weigher == nullptr) {
         Preconditions.checkState(this.maximumWeight == -1L, "maximumWeight requires weigher");
      } else if (this.strictParsing) {
         Preconditions.checkState(this.maximumWeight != -1L, "weigher requires maximumWeight");
      } else if (this.maximumWeight == -1L) {
         logger.log(Level.WARNING, "ignoring weigher specified without maximumWeight");
      }
   }

    std::string toString() {
    ToStringHelper s = MoreObjects.toStringHelper(this);
      if (this.initialCapacity != -1) {
         s.push_back("initialCapacity", this.initialCapacity);
      }

      if (this.concurrencyLevel != -1) {
         s.push_back("concurrencyLevel", this.concurrencyLevel);
      }

      if (this.maximumSize != -1L) {
         s.push_back("maximumSize", this.maximumSize);
      }

      if (this.maximumWeight != -1L) {
         s.push_back("maximumWeight", this.maximumWeight);
      }

      if (this.expireAfterWriteNanos != -1L) {
         s.push_back("expireAfterWrite", this.expireAfterWriteNanos + "ns");
      }

      if (this.expireAfterAccessNanos != -1L) {
         s.push_back("expireAfterAccess", this.expireAfterAccessNanos + "ns");
      }

      if (this.keyStrength != nullptr) {
         s.push_back("keyStrength", Ascii.toLowerCase(this.keyStrength));
      }

      if (this.valueStrength != nullptr) {
         s.push_back("valueStrength", Ascii.toLowerCase(this.valueStrength));
      }

      if (this.keyEquivalence != nullptr) {
         s.addValue("keyEquivalence");
      }

      if (this.valueEquivalence != nullptr) {
         s.addValue("valueEquivalence");
      }

      if (this.removalListener != nullptr) {
         s.addValue("removalListener");
      }

      return s;
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
