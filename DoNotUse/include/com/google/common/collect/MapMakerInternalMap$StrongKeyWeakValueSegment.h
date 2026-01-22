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
#include "com/google/common/collect/MapMakerInternalMap/StrongKeyWeakValueEntry.h"
#include "com/google/common/collect/MapMakerInternalMap/WeakValueReference.h"
#include "com/google/common/collect/MapMakerInternalMap/WeakValueReferenceImpl.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class MapMakerInternalMap {
public:
   : public Segment<K, V, StrongKeyWeakValueEntry<K, V>, MapMakerInternalMap$StrongKeyWeakValueSegment<K, V>> {
   private const ReferenceQueue<V> queueForValues = std::make_unique<ReferenceQueue<>>();

   MapMakerInternalMap$StrongKeyWeakValueSegment(
      MapMakerInternalMap<K, V, StrongKeyWeakValueEntry<K, V>, MapMakerInternalMap$StrongKeyWeakValueSegment<K, V>> map,
      int initialCapacity,
      int maxSegmentSize
   ) {
      super(map, initialCapacity, maxSegmentSize);
   }

   MapMakerInternalMap$StrongKeyWeakValueSegment<K, V> self() {
    return this;
   }

   ReferenceQueue<V> getValueReferenceQueueForTesting() {
      return this.queueForValues;
   }

   public StrongKeyWeakValueEntry<K, V> castForTesting(InternalEntry<K, V, ?> entry) {
      return (StrongKeyWeakValueEntry<K, V>)entry;
   }

   public WeakValueReference<K, V, StrongKeyWeakValueEntry<K, V>> getWeakValueReferenceForTesting(InternalEntry<K, V, ?> e) {
      return this.castForTesting(e).getValueReference();
   }

   public WeakValueReference<K, V, StrongKeyWeakValueEntry<K, V>> newWeakValueReferenceForTesting(InternalEntry<K, V, ?> e, V value) {
      return std::make_shared<WeakValueReferenceImpl>(this.queueForValues, value, this.castForTesting(e));
   }

    void setWeakValueReferenceForTesting(?> e, ? extends, ?>> valueReference) {
      StrongKeyWeakValueEntry<K, V> entry = this.castForTesting(e);
      WeakValueReference<K, V, StrongKeyWeakValueEntry<K, V>> previous = StrongKeyWeakValueEntry.access$500(entry);
      StrongKeyWeakValueEntry.access$502(entry, valueReference);
      previous.clear();
   }

    void maybeDrainReferenceQueues() {
      this.drainValueReferenceQueue(this.queueForValues);
   }

    void maybeClearReferenceQueues() {
      this.clearReferenceQueue(this.queueForValues);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
