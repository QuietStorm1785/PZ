#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace google {
namespace common {
namespace collect {

class TreeRangeMap {
public:
   private const Range<K> range;
    const V value;

   TreeRangeMap$RangeMapEntry(Cut<K> lowerBound, Cut<K> upperBound, V value) {
      this(Range.create(lowerBound, upperBound), value);
   }

   TreeRangeMap$RangeMapEntry(Range<K> range, V value) {
      this.range = range;
      this.value = value;
   }

   public Range<K> getKey() {
      return this.range;
   }

    V getValue() {
      return this.value;
   }

    bool contains(K value) {
      return this.range.contains(value);
   }

   Cut<K> getLowerBound() {
      return this.range.lowerBound;
   }

   Cut<K> getUpperBound() {
      return this.range.upperBound;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
