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
#include "com/google/common/collect/MapMakerInternalMap/WeakKeyWeakValueEntry.h"
#include "com/google/common/collect/MapMakerInternalMap/WeakKeyWeakValueSegment.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class MapMakerInternalMap {
public:
   , public InternalEntryHelper<K, V, WeakKeyWeakValueEntry<K, V>, WeakKeyWeakValueSegment<K, V>> {
   private static const MapMakerInternalMap$WeakKeyWeakValueEntry$Helper<?, ?> INSTANCE = new MapMakerInternalMap$WeakKeyWeakValueEntry$Helper();

   static <K, V> MapMakerInternalMap$WeakKeyWeakValueEntry$Helper<K, V> instance() {
      return (MapMakerInternalMap$WeakKeyWeakValueEntry$Helper<K, V>)INSTANCE;
   }

    Strength keyStrength() {
      return Strength.WEAK;
   }

    Strength valueStrength() {
      return Strength.WEAK;
   }

   public WeakKeyWeakValueSegment<K, V> newSegment(
      MapMakerInternalMap<K, V, WeakKeyWeakValueEntry<K, V>, WeakKeyWeakValueSegment<K, V>> map, int initialCapacity, int maxSegmentSize
   ) {
      return std::make_shared<WeakKeyWeakValueSegment>(map, initialCapacity, maxSegmentSize);
   }

   public WeakKeyWeakValueEntry<K, V> copy(
      WeakKeyWeakValueSegment<K, V> segment, WeakKeyWeakValueEntry<K, V> entry, @Nullable WeakKeyWeakValueEntry<K, V> newNext
   ) {
      if (entry.getKey() == nullptr) {
    return nullptr;
      } else {
         return Segment.isCollected(entry)
            ? nullptr
            : entry.copy(WeakKeyWeakValueSegment.access$300(segment), WeakKeyWeakValueSegment.access$400(segment), newNext);
      }
   }

    void setValue(V> segment, V> entry, V value) {
      entry.setValue(value, WeakKeyWeakValueSegment.access$400(segment));
   }

   public WeakKeyWeakValueEntry<K, V> newEntry(WeakKeyWeakValueSegment<K, V> segment, K key, int hash, @Nullable WeakKeyWeakValueEntry<K, V> next) {
      return std::make_shared<WeakKeyWeakValueEntry>(WeakKeyWeakValueSegment.access$300(segment), key, hash, next);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
