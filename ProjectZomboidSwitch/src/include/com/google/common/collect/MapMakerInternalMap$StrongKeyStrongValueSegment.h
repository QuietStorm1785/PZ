#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/MapMakerInternalMap/InternalEntry.h"
#include "com/google/common/collect/MapMakerInternalMap/Segment.h"
#include "com/google/common/collect/MapMakerInternalMap/StrongKeyStrongValueEntry.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class MapMakerInternalMap {
public:
   : public Segment<K, V, StrongKeyStrongValueEntry<K, V>, MapMakerInternalMap$StrongKeyStrongValueSegment<K, V>> {
   MapMakerInternalMap$StrongKeyStrongValueSegment(
      MapMakerInternalMap<K, V, StrongKeyStrongValueEntry<K, V>, MapMakerInternalMap$StrongKeyStrongValueSegment<K, V>> map,
      int initialCapacity,
      int maxSegmentSize
   ) {
      super(map, initialCapacity, maxSegmentSize);
   }

   MapMakerInternalMap$StrongKeyStrongValueSegment<K, V> self() {
    return this;
   }

   public StrongKeyStrongValueEntry<K, V> castForTesting(InternalEntry<K, V, ?> entry) {
      return (StrongKeyStrongValueEntry<K, V>)entry;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
