#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/MapMakerInternalMap/InternalEntry.h"
#include "com/google/common/collect/MapMakerInternalMap/Segment.h"
#include "com/google/common/collect/MapMakerInternalMap/WeakKeyStrongValueEntry.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class MapMakerInternalMap {
public:
   : public Segment<K, V, WeakKeyStrongValueEntry<K, V>, MapMakerInternalMap$WeakKeyStrongValueSegment<K, V>> {
   private const ReferenceQueue<K> queueForKeys = std::make_unique<ReferenceQueue<>>();

   MapMakerInternalMap$WeakKeyStrongValueSegment(
      MapMakerInternalMap<K, V, WeakKeyStrongValueEntry<K, V>, MapMakerInternalMap$WeakKeyStrongValueSegment<K, V>> map,
      int initialCapacity,
      int maxSegmentSize
   ) {
      super(map, initialCapacity, maxSegmentSize);
   }

   MapMakerInternalMap$WeakKeyStrongValueSegment<K, V> self() {
    return this;
   }

   ReferenceQueue<K> getKeyReferenceQueueForTesting() {
      return this.queueForKeys;
   }

   public WeakKeyStrongValueEntry<K, V> castForTesting(InternalEntry<K, V, ?> entry) {
      return (WeakKeyStrongValueEntry<K, V>)entry;
   }

    void maybeDrainReferenceQueues() {
      this.drainKeyReferenceQueue(this.queueForKeys);
   }

    void maybeClearReferenceQueues() {
      this.clearReferenceQueue(this.queueForKeys);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
