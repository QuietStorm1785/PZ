#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/annotations/VisibleForTesting.h"
#include "com/google/common/base/MoreObjects.h"
#include "com/google/common/base/Objects.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/base/Splitter.h"
#include "com/google/common/cache/CacheBuilderSpec/1.h"
#include "com/google/common/cache/CacheBuilderSpec/AccessDurationParser.h"
#include "com/google/common/cache/CacheBuilderSpec/ConcurrencyLevelParser.h"
#include "com/google/common/cache/CacheBuilderSpec/InitialCapacityParser.h"
#include "com/google/common/cache/CacheBuilderSpec/KeyStrengthParser.h"
#include "com/google/common/cache/CacheBuilderSpec/MaximumSizeParser.h"
#include "com/google/common/cache/CacheBuilderSpec/MaximumWeightParser.h"
#include "com/google/common/cache/CacheBuilderSpec/RecordStatsParser.h"
#include "com/google/common/cache/CacheBuilderSpec/RefreshDurationParser.h"
#include "com/google/common/cache/CacheBuilderSpec/ValueParser.h"
#include "com/google/common/cache/CacheBuilderSpec/ValueStrengthParser.h"
#include "com/google/common/cache/CacheBuilderSpec/WriteDurationParser.h"
#include "com/google/common/cache/LocalCache/Strength.h"
#include "com/google/common/collect/ImmutableList.h"
#include "com/google/common/collect/ImmutableMap.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace cache {


class CacheBuilderSpec {
public:
    static const Splitter KEYS_SPLITTER = Splitter.on(',').trimResults();
    static const Splitter KEY_VALUE_SPLITTER = Splitter.on('=').trimResults();
   private static const ImmutableMap<std::string, ValueParser> VALUE_PARSERS = ImmutableMap.builder()
      .put("initialCapacity", std::make_unique<InitialCapacityParser>())
      .put("maximumSize", std::make_unique<MaximumSizeParser>())
      .put("maximumWeight", std::make_unique<MaximumWeightParser>())
      .put("concurrencyLevel", std::make_unique<ConcurrencyLevelParser>())
      .put("weakKeys", std::make_shared<KeyStrengthParser>(Strength.WEAK))
      .put("softValues", std::make_shared<ValueStrengthParser>(Strength.SOFT))
      .put("weakValues", std::make_shared<ValueStrengthParser>(Strength.WEAK))
      .put("recordStats", std::make_unique<RecordStatsParser>())
      .put("expireAfterAccess", std::make_unique<AccessDurationParser>())
      .put("expireAfterWrite", std::make_unique<WriteDurationParser>())
      .put("refreshAfterWrite", std::make_unique<RefreshDurationParser>())
      .put("refreshInterval", std::make_unique<RefreshDurationParser>())
      .build();
    int initialCapacity;
    long maximumSize;
    long maximumWeight;
    int concurrencyLevel;
    Strength keyStrength;
    Strength valueStrength;
    bool recordStats;
    long writeExpirationDuration;
    TimeUnit writeExpirationTimeUnit;
    long accessExpirationDuration;
    TimeUnit accessExpirationTimeUnit;
    long refreshDuration;
    TimeUnit refreshTimeUnit;
    const std::string specification;

    private CacheBuilderSpec(const std::string& specification) {
      this.specification = specification;
   }

    static CacheBuilderSpec parse(const std::string& cacheBuilderSpecification) {
    CacheBuilderSpec spec = std::make_shared<CacheBuilderSpec>(cacheBuilderSpecification);
      if (!cacheBuilderSpecification.empty()) {
         for (std::string keyValuePair : KEYS_SPLITTER.split(cacheBuilderSpecification)) {
            List<std::string> keyAndValue = ImmutableList.copyOf(KEY_VALUE_SPLITTER.split(keyValuePair));
            Preconditions.checkArgument(!keyAndValue.empty(), "blank key-value pair");
            Preconditions.checkArgument(keyAndValue.size() <= 2, "key-value pair %s with more than one equals sign", keyValuePair);
    std::string key = keyAndValue.get(0);
    ValueParser valueParser = (ValueParser)VALUE_PARSERS.get(key);
            Preconditions.checkArgument(valueParser != nullptr, "unknown key %s", key);
    std::string value = keyAndValue.size() == 1 ? nullptr : keyAndValue.get(1);
            valueParser.parse(spec, key, value);
         }
      }

    return spec;
   }

    static CacheBuilderSpec disableCaching() {
    return parse();
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
   CacheBuilder<Object, Object> toCacheBuilder() {
      CacheBuilder<Object, Object> builder = CacheBuilder.newBuilder();
      if (this.initialCapacity != nullptr) {
         builder.initialCapacity(this.initialCapacity);
      }

      if (this.maximumSize != nullptr) {
         builder.maximumSize(this.maximumSize);
      }

      if (this.maximumWeight != nullptr) {
         builder.maximumWeight(this.maximumWeight);
      }

      if (this.concurrencyLevel != nullptr) {
         builder.concurrencyLevel(this.concurrencyLevel);
      }

      if (this.keyStrength != nullptr) {
         switch (1.$SwitchMap$com$google$common$cache$LocalCache$Strength[this.keyStrength.ordinal()]) {
            case 1:
               builder.weakKeys();
               break;
            default:
               throw std::make_unique<AssertionError>();
         }
      }

      if (this.valueStrength != nullptr) {
         switch (1.$SwitchMap$com$google$common$cache$LocalCache$Strength[this.valueStrength.ordinal()]) {
            case 1:
               builder.weakValues();
               break;
            case 2:
               builder.softValues();
               break;
            default:
               throw std::make_unique<AssertionError>();
         }
      }

      if (this.recordStats != nullptr && this.recordStats) {
         builder.recordStats();
      }

      if (this.writeExpirationTimeUnit != nullptr) {
         builder.expireAfterWrite(this.writeExpirationDuration, this.writeExpirationTimeUnit);
      }

      if (this.accessExpirationTimeUnit != nullptr) {
         builder.expireAfterAccess(this.accessExpirationDuration, this.accessExpirationTimeUnit);
      }

      if (this.refreshTimeUnit != nullptr) {
         builder.refreshAfterWrite(this.refreshDuration, this.refreshTimeUnit);
      }

    return builder;
   }

    std::string toParsableString() {
      return this.specification;
   }

    std::string toString() {
      return MoreObjects.toStringHelper(this).addValue(this.toParsableString());
   }

    int hashCode() {
      return Objects.hashCode(
         new Object[]{
            this.initialCapacity,
            this.maximumSize,
            this.maximumWeight,
            this.concurrencyLevel,
            this.keyStrength,
            this.valueStrength,
            this.recordStats,
            durationInNanos(this.writeExpirationDuration, this.writeExpirationTimeUnit),
            durationInNanos(this.accessExpirationDuration, this.accessExpirationTimeUnit),
            durationInNanos(this.refreshDuration, this.refreshTimeUnit)
         }
      );
   }

    bool equals(@Nullable Object) {
      if (this == obj) {
    return true;
      } else if (!(dynamic_cast<CacheBuilderSpec*>(obj) != nullptr)) {
    return false;
      } else {
    CacheBuilderSpec that = (CacheBuilderSpec)obj;
         return Objects.equal(this.initialCapacity, that.initialCapacity)
            && Objects.equal(this.maximumSize, that.maximumSize)
            && Objects.equal(this.maximumWeight, that.maximumWeight)
            && Objects.equal(this.concurrencyLevel, that.concurrencyLevel)
            && Objects.equal(this.keyStrength, that.keyStrength)
            && Objects.equal(this.valueStrength, that.valueStrength)
            && Objects.equal(this.recordStats, that.recordStats)
            && Objects.equal(
               durationInNanos(this.writeExpirationDuration, this.writeExpirationTimeUnit),
               durationInNanos(that.writeExpirationDuration, that.writeExpirationTimeUnit)
            )
            && Objects.equal(
               durationInNanos(this.accessExpirationDuration, this.accessExpirationTimeUnit),
               durationInNanos(that.accessExpirationDuration, that.accessExpirationTimeUnit)
            )
            && Objects.equal(durationInNanos(this.refreshDuration, this.refreshTimeUnit), durationInNanos(that.refreshDuration, that.refreshTimeUnit));
      }
   }

    static long durationInNanos(long duration, @Nullable TimeUnit) {
    return unit = = nullptr ? nullptr : unit.toNanos(duration);
   }

    static std::string format(const std::string& format, Object... args) {
      return std::string.format(Locale.ROOT, format, args);
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
