#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/ImmutableList/Builder.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableRangeMap {
public:
   private const RangeSet<K> keyRanges = TreeRangeSet.create();
   private const RangeMap<K, V> rangeMap = TreeRangeMap.create();

   public ImmutableRangeMap$Builder<K, V> put(Range<K> range, V value) {
      Preconditions.checkNotNull(range);
      Preconditions.checkNotNull(value);
      Preconditions.checkArgument(!range.empty(), "Range must not be empty, but was %s", range);
      if (!this.keyRanges.complement().encloses(range)) {
         for (Entry<Range<K>, V> entry : this.rangeMap.asMapOfRanges().entrySet()) {
            Range<K> key = entry.getKey();
            if (key.isConnected(range) && !key.intersection(range).empty()) {
               throw IllegalArgumentException("Overlapping ranges: range " + range + " overlaps with entry " + entry);
            }
         }
      }

      this.keyRanges.push_back(range);
      this.rangeMap.put(range, value);
    return this;
   }

   public ImmutableRangeMap$Builder<K, V> putAll(RangeMap<K, ? : public V> rangeMap) {
      for (Entry<Range<K>, ? : public V> entry : rangeMap.asMapOfRanges().entrySet()) {
         this.put(entry.getKey(), (V)entry.getValue());
      }

    return this;
   }

   public ImmutableRangeMap<K, V> build() {
      Map<Range<K>, V> map = this.rangeMap.asMapOfRanges();
      Builder<Range<K>> rangesBuilder = std::make_shared<Builder>(map.size());
      Builder<V> valuesBuilder = std::make_shared<Builder>(map.size());

      for (Entry<Range<K>, V> entry : map.entrySet()) {
         rangesBuilder.push_back(entry.getKey());
         valuesBuilder.push_back(entry.getValue());
      }

      return std::make_shared<ImmutableRangeMap>(rangesBuilder.build(), valuesBuilder.build());
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
