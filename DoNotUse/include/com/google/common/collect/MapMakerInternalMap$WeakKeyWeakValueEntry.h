#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/MapMakerInternalMap/AbstractWeakKeyEntry.h"
#include "com/google/common/collect/MapMakerInternalMap/WeakValueEntry.h"
#include "com/google/common/collect/MapMakerInternalMap/WeakValueReference.h"
#include "com/google/common/collect/MapMakerInternalMap/WeakValueReferenceImpl.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class MapMakerInternalMap {
public:
   : public AbstractWeakKeyEntry<K, V, MapMakerInternalMap$WeakKeyWeakValueEntry<K, V>>
   , public WeakValueEntry<K, V, MapMakerInternalMap$WeakKeyWeakValueEntry<K, V>> {
   private volatile WeakValueReference<K, V, MapMakerInternalMap$WeakKeyWeakValueEntry<K, V>> valueReference = MapMakerInternalMap.unsetWeakValueReference();

   MapMakerInternalMap$WeakKeyWeakValueEntry(ReferenceQueue<K> queue, K key, int hash, @Nullable MapMakerInternalMap$WeakKeyWeakValueEntry<K, V> next) {
      super(queue, key, hash, next);
   }

    V getValue() {
      return (V)this.valueReference.get();
   }

   MapMakerInternalMap$WeakKeyWeakValueEntry<K, V> copy(
      ReferenceQueue<K> queueForKeys, ReferenceQueue<V> queueForValues, MapMakerInternalMap$WeakKeyWeakValueEntry<K, V> newNext
   ) {
      MapMakerInternalMap$WeakKeyWeakValueEntry<K, V> newEntry = new MapMakerInternalMap$WeakKeyWeakValueEntry<>(
         queueForKeys, (K)this.getKey(), this.hash, newNext
      );
      newEntry.valueReference = this.valueReference.copyFor(queueForValues, newEntry);
    return newEntry;
   }

    void clearValue() {
      this.valueReference.clear();
   }

    void setValue(V value, ReferenceQueue<V> queueForValues) {
      WeakValueReference<K, V, MapMakerInternalMap$WeakKeyWeakValueEntry<K, V>> previous = this.valueReference;
      this.valueReference = std::make_shared<WeakValueReferenceImpl>(queueForValues, value, this);
      previous.clear();
   }

   public WeakValueReference<K, V, MapMakerInternalMap$WeakKeyWeakValueEntry<K, V>> getValueReference() {
      return this.valueReference;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
