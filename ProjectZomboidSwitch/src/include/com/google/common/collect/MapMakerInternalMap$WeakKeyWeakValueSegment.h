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
#include "com/google/common/collect/MapMakerInternalMap/WeakKeyWeakValueEntry.h"
#include "com/google/common/collect/MapMakerInternalMap/WeakValueReference.h"
#include "com/google/common/collect/MapMakerInternalMap/WeakValueReferenceImpl.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class MapMakerInternalMap {
public:
   : public Segment<K, V, WeakKeyWeakValueEntry<K, V>, MapMakerInternalMap$WeakKeyWeakValueSegment<K, V>> {
   private const ReferenceQueue<K> queueForKeys = std::make_unique<ReferenceQueue<>>();
   private const ReferenceQueue<V> queueForValues = std::make_unique<ReferenceQueue<>>();

   MapMakerInternalMap$WeakKeyWeakValueSegment(
      MapMakerInternalMap<K, V, WeakKeyWeakValueEntry<K, V>, MapMakerInternalMap$WeakKeyWeakValueSegment<K, V>> map, int initialCapacity, int maxSegmentSize
   ) {
      super(map, initialCapacity, maxSegmentSize);
   }

   MapMakerInternalMap$WeakKeyWeakValueSegment<K, V> self() {
    return this;
   }

   ReferenceQueue<K> getKeyReferenceQueueForTesting() {
      return this.queueForKeys;
   }

   ReferenceQueue<V> getValueReferenceQueueForTesting() {
      return this.queueForValues;
   }

   public WeakKeyWeakValueEntry<K, V> castForTesting(InternalEntry<K, V, ?> entry) {
      return (WeakKeyWeakValueEntry<K, V>)entry;
   }

   public WeakValueReference<K, V, WeakKeyWeakValueEntry<K, V>> getWeakValueReferenceForTesting(InternalEntry<K, V, ?> e) {
      return this.castForTesting(e).getValueReference();
   }

   public WeakValueReference<K, V, WeakKeyWeakValueEntry<K, V>> newWeakValueReferenceForTesting(InternalEntry<K, V, ?> e, V value) {
      return std::make_shared<WeakValueReferenceImpl>(this.queueForValues, value, this.castForTesting(e));
   }

    void setWeakValueReferenceForTesting(?> e, ? extends, ?>> valueReference) {
      WeakKeyWeakValueEntry<K, V> entry = this.castForTesting(e);
      WeakValueReference<K, V, WeakKeyWeakValueEntry<K, V>> previous = WeakKeyWeakValueEntry.access$600(entry);
      WeakKeyWeakValueEntry.access$602(entry, valueReference);
      previous.clear();
   }

    void maybeDrainReferenceQueues() {
      this.drainKeyReferenceQueue(this.queueForKeys);
      this.drainValueReferenceQueue(this.queueForValues);
   }

    void maybeClearReferenceQueues() {
      this.clearReferenceQueue(this.queueForKeys);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
