#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class TreeRangeMap {
public:
    void* get(Comparable key) {
    return nullptr;
   }

   public Entry<Range, Object> getEntry(Comparable key) {
    return nullptr;
   }

    Range span() {
      throw std::make_unique<NoSuchElementException>();
   }

    void put(Range range, void* value) {
      Preconditions.checkNotNull(range);
      throw IllegalArgumentException("Cannot insert range " + range + " into an empty subRangeMap");
   }

    void putAll(RangeMap rangeMap) {
      if (!rangeMap.asMapOfRanges().empty()) {
         throw IllegalArgumentException("Cannot putAll(nonEmptyRangeMap) into an empty subRangeMap");
      }
   }

    void clear() {
   }

    void remove(Range range) {
      Preconditions.checkNotNull(range);
   }

   public Map<Range, Object> asMapOfRanges() {
      return Collections.emptyMap();
   }

   public Map<Range, Object> asDescendingMapOfRanges() {
      return Collections.emptyMap();
   }

    RangeMap subRangeMap(Range range) {
      Preconditions.checkNotNull(range);
    return this;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
