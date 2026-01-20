#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/MapMakerInternalMap/AbstractStrongKeyEntry.h"
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
   : public AbstractStrongKeyEntry<K, V, MapMakerInternalMap$StrongKeyWeakValueEntry<K, V>>
   , public WeakValueEntry<K, V, MapMakerInternalMap$StrongKeyWeakValueEntry<K, V>> {
   private volatile WeakValueReference<K, V, MapMakerInternalMap$StrongKeyWeakValueEntry<K, V>> valueReference = MapMakerInternalMap.unsetWeakValueReference();

   MapMakerInternalMap$StrongKeyWeakValueEntry(K key, int hash, @Nullable MapMakerInternalMap$StrongKeyWeakValueEntry<K, V> next) {
      super(key, hash, next);
   }

    V getValue() {
      return (V)this.valueReference.get();
   }

    void clearValue() {
      this.valueReference.clear();
   }

    void setValue(V value, ReferenceQueue<V> queueForValues) {
      WeakValueReference<K, V, MapMakerInternalMap$StrongKeyWeakValueEntry<K, V>> previous = this.valueReference;
      this.valueReference = std::make_shared<WeakValueReferenceImpl>(queueForValues, value, this);
      previous.clear();
   }

   MapMakerInternalMap$StrongKeyWeakValueEntry<K, V> copy(ReferenceQueue<V> queueForValues, MapMakerInternalMap$StrongKeyWeakValueEntry<K, V> newNext) {
      MapMakerInternalMap$StrongKeyWeakValueEntry<K, V> newEntry = new MapMakerInternalMap$StrongKeyWeakValueEntry<>((K)this.key, this.hash, newNext);
      newEntry.valueReference = this.valueReference.copyFor(queueForValues, newEntry);
    return newEntry;
   }

   public WeakValueReference<K, V, MapMakerInternalMap$StrongKeyWeakValueEntry<K, V>> getValueReference() {
      return this.valueReference;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
