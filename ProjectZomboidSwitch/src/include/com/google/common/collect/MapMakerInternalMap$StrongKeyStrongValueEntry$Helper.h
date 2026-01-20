#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/MapMakerInternalMap/InternalEntryHelper.h"
#include "com/google/common/collect/MapMakerInternalMap/Strength.h"
#include "com/google/common/collect/MapMakerInternalMap/StrongKeyStrongValueEntry.h"
#include "com/google/common/collect/MapMakerInternalMap/StrongKeyStrongValueSegment.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class MapMakerInternalMap {
public:
   , public InternalEntryHelper<K, V, StrongKeyStrongValueEntry<K, V>, StrongKeyStrongValueSegment<K, V>> {
   private static const MapMakerInternalMap$StrongKeyStrongValueEntry$Helper<?, ?> INSTANCE = new MapMakerInternalMap$StrongKeyStrongValueEntry$Helper();

   static <K, V> MapMakerInternalMap$StrongKeyStrongValueEntry$Helper<K, V> instance() {
      return (MapMakerInternalMap$StrongKeyStrongValueEntry$Helper<K, V>)INSTANCE;
   }

    Strength keyStrength() {
      return Strength.STRONG;
   }

    Strength valueStrength() {
      return Strength.STRONG;
   }

   public StrongKeyStrongValueSegment<K, V> newSegment(
      MapMakerInternalMap<K, V, StrongKeyStrongValueEntry<K, V>, StrongKeyStrongValueSegment<K, V>> map, int initialCapacity, int maxSegmentSize
   ) {
      return std::make_shared<StrongKeyStrongValueSegment>(map, initialCapacity, maxSegmentSize);
   }

   public StrongKeyStrongValueEntry<K, V> copy(
      StrongKeyStrongValueSegment<K, V> segment, StrongKeyStrongValueEntry<K, V> entry, @Nullable StrongKeyStrongValueEntry<K, V> newNext
   ) {
      return entry.copy(newNext);
   }

    void setValue(V> segment, V> entry, V value) {
      entry.setValue(value);
   }

   public StrongKeyStrongValueEntry<K, V> newEntry(StrongKeyStrongValueSegment<K, V> segment, K key, int hash, @Nullable StrongKeyStrongValueEntry<K, V> next) {
      return std::make_shared<StrongKeyStrongValueEntry>(key, hash, next);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
