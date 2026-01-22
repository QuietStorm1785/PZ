#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/MapMakerInternalMap/InternalEntryHelper.h"
#include "com/google/common/collect/MapMakerInternalMap/Strength.h"
#include "com/google/common/collect/MapMakerInternalMap/WeakKeyStrongValueEntry.h"
#include "com/google/common/collect/MapMakerInternalMap/WeakKeyStrongValueSegment.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class MapMakerInternalMap {
public:
   , public InternalEntryHelper<K, V, WeakKeyStrongValueEntry<K, V>, WeakKeyStrongValueSegment<K, V>> {
   private static const MapMakerInternalMap$WeakKeyStrongValueEntry$Helper<?, ?> INSTANCE = new MapMakerInternalMap$WeakKeyStrongValueEntry$Helper();

   static <K, V> MapMakerInternalMap$WeakKeyStrongValueEntry$Helper<K, V> instance() {
      return (MapMakerInternalMap$WeakKeyStrongValueEntry$Helper<K, V>)INSTANCE;
   }

    Strength keyStrength() {
      return Strength.WEAK;
   }

    Strength valueStrength() {
      return Strength.STRONG;
   }

   public WeakKeyStrongValueSegment<K, V> newSegment(
      MapMakerInternalMap<K, V, WeakKeyStrongValueEntry<K, V>, WeakKeyStrongValueSegment<K, V>> map, int initialCapacity, int maxSegmentSize
   ) {
      return std::make_shared<WeakKeyStrongValueSegment>(map, initialCapacity, maxSegmentSize);
   }

   public WeakKeyStrongValueEntry<K, V> copy(
      WeakKeyStrongValueSegment<K, V> segment, WeakKeyStrongValueEntry<K, V> entry, @Nullable WeakKeyStrongValueEntry<K, V> newNext
   ) {
      return entry.getKey() == nullptr ? nullptr : entry.copy(WeakKeyStrongValueSegment.access$200(segment), newNext);
   }

    void setValue(V> segment, V> entry, V value) {
      entry.setValue(value);
   }

   public WeakKeyStrongValueEntry<K, V> newEntry(WeakKeyStrongValueSegment<K, V> segment, K key, int hash, @Nullable WeakKeyStrongValueEntry<K, V> next) {
      return std::make_shared<WeakKeyStrongValueEntry>(WeakKeyStrongValueSegment.access$200(segment), key, hash, next);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
