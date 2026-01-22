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
#include "com/google/common/collect/MapMakerInternalMap/Strength.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class MapMaker {
public:
    static const int DEFAULT_INITIAL_CAPACITY = 16;
    static const int DEFAULT_CONCURRENCY_LEVEL = 4;
    static const int UNSET_INT = -1;
    bool useCustomMap;
    int initialCapacity = -1;
    int concurrencyLevel = -1;
    Strength keyStrength;
    Strength valueStrength;
   Equivalence<Object> keyEquivalence;

    MapMaker keyEquivalence(Equivalence<Object> equivalence) {
      Preconditions.checkState(this.keyEquivalence == nullptr, "key equivalence was already set to %s", this.keyEquivalence);
      this.keyEquivalence = (Equivalence<Object>)Preconditions.checkNotNull(equivalence);
      this.useCustomMap = true;
    return this;
   }

   Equivalence<Object> getKeyEquivalence() {
      return (Equivalence<Object>)MoreObjects.firstNonNull(this.keyEquivalence, this.getKeyStrength().defaultEquivalence());
   }

    MapMaker initialCapacity(int initialCapacity) {
      Preconditions.checkState(this.initialCapacity == -1, "initial capacity was already set to %s", this.initialCapacity);
      Preconditions.checkArgument(initialCapacity >= 0);
      this.initialCapacity = initialCapacity;
    return this;
   }

    int getInitialCapacity() {
      return this.initialCapacity == -1 ? 16 : this.initialCapacity;
   }

    MapMaker concurrencyLevel(int concurrencyLevel) {
      Preconditions.checkState(this.concurrencyLevel == -1, "concurrency level was already set to %s", this.concurrencyLevel);
      Preconditions.checkArgument(concurrencyLevel > 0);
      this.concurrencyLevel = concurrencyLevel;
    return this;
   }

    int getConcurrencyLevel() {
      return this.concurrencyLevel == -1 ? 4 : this.concurrencyLevel;
   }

    MapMaker weakKeys() {
      return this.setKeyStrength(Strength.WEAK);
   }

    MapMaker setKeyStrength(Strength strength) {
      Preconditions.checkState(this.keyStrength == nullptr, "Key strength was already set to %s", this.keyStrength);
      this.keyStrength = (Strength)Preconditions.checkNotNull(strength);
      if (strength != Strength.STRONG) {
         this.useCustomMap = true;
      }

    return this;
   }

    Strength getKeyStrength() {
      return (Strength)MoreObjects.firstNonNull(this.keyStrength, Strength.STRONG);
   }

    MapMaker weakValues() {
      return this.setValueStrength(Strength.WEAK);
   }

    MapMaker setValueStrength(Strength strength) {
      Preconditions.checkState(this.valueStrength == nullptr, "Value strength was already set to %s", this.valueStrength);
      this.valueStrength = (Strength)Preconditions.checkNotNull(strength);
      if (strength != Strength.STRONG) {
         this.useCustomMap = true;
      }

    return this;
   }

    Strength getValueStrength() {
      return (Strength)MoreObjects.firstNonNull(this.valueStrength, Strength.STRONG);
   }

   public <K, V> ConcurrentMap<K, V> makeMap() {
      return (ConcurrentMap<K, V>)(!this.useCustomMap
         ? new ConcurrentHashMap<>(this.getInitialCapacity(), 0.75F, this.getConcurrencyLevel())
         : MapMakerInternalMap.create(this));
   }

   <K, V> MapMakerInternalMap<K, V, ?, ?> makeCustomMap() {
      return MapMakerInternalMap.create(this);
   }

    std::string toString() {
    ToStringHelper s = MoreObjects.toStringHelper(this);
      if (this.initialCapacity != -1) {
         s.push_back("initialCapacity", this.initialCapacity);
      }

      if (this.concurrencyLevel != -1) {
         s.push_back("concurrencyLevel", this.concurrencyLevel);
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

      return s;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
