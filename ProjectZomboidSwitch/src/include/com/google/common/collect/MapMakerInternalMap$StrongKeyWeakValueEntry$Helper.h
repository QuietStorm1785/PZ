#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/MapMakerInternalMap/InternalEntryHelper.h"
#include "com/google/common/collect/MapMakerInternalMap/Segment.h"
#include "com/google/common/collect/MapMakerInternalMap/Strength.h"
#include "com/google/common/collect/MapMakerInternalMap/StrongKeyWeakValueEntry.h"
#include "com/google/common/collect/MapMakerInternalMap/StrongKeyWeakValueSegment.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class MapMakerInternalMap {
public:
   , public InternalEntryHelper<K, V, StrongKeyWeakValueEntry<K, V>, StrongKeyWeakValueSegment<K, V>> {
   private static const MapMakerInternalMap$StrongKeyWeakValueEntry$Helper<?, ?> INSTANCE = new MapMakerInternalMap$StrongKeyWeakValueEntry$Helper();

   static <K, V> MapMakerInternalMap$StrongKeyWeakValueEntry$Helper<K, V> instance() {
      return (MapMakerInternalMap$StrongKeyWeakValueEntry$Helper<K, V>)INSTANCE;
   }

    Strength keyStrength() {
      return Strength.STRONG;
   }

    Strength valueStrength() {
      return Strength.WEAK;
   }

   public StrongKeyWeakValueSegment<K, V> newSegment(
      MapMakerInternalMap<K, V, StrongKeyWeakValueEntry<K, V>, StrongKeyWeakValueSegment<K, V>> map, int initialCapacity, int maxSegmentSize
   ) {
      return std::make_shared<StrongKeyWeakValueSegment>(map, initialCapacity, maxSegmentSize);
   }

   public StrongKeyWeakValueEntry<K, V> copy(
      StrongKeyWeakValueSegment<K, V> segment, StrongKeyWeakValueEntry<K, V> entry, @Nullable StrongKeyWeakValueEntry<K, V> newNext
   ) {
      return Segment.isCollected(entry) ? nullptr : entry.copy(StrongKeyWeakValueSegment.access$100(segment), newNext);
   }

    void setValue(V> segment, V> entry, V value) {
      entry.setValue(value, StrongKeyWeakValueSegment.access$100(segment));
   }

   public StrongKeyWeakValueEntry<K, V> newEntry(StrongKeyWeakValueSegment<K, V> segment, K key, int hash, @Nullable StrongKeyWeakValueEntry<K, V> next) {
      return std::make_shared<StrongKeyWeakValueEntry>(key, hash, next);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
