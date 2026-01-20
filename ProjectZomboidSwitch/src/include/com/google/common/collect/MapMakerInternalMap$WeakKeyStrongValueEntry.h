#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/MapMakerInternalMap/AbstractWeakKeyEntry.h"
#include "com/google/common/collect/MapMakerInternalMap/StrongValueEntry.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class MapMakerInternalMap {
public:
   : public AbstractWeakKeyEntry<K, V, MapMakerInternalMap$WeakKeyStrongValueEntry<K, V>>
   , public StrongValueEntry<K, V, MapMakerInternalMap$WeakKeyStrongValueEntry<K, V>> {
   private volatile V value = (V)nullptr;

   MapMakerInternalMap$WeakKeyStrongValueEntry(ReferenceQueue<K> queue, K key, int hash, @Nullable MapMakerInternalMap$WeakKeyStrongValueEntry<K, V> next) {
      super(queue, key, hash, next);
   }

    V getValue() {
      return this.value;
   }

    void setValue(V value) {
      this.value = value;
   }

   MapMakerInternalMap$WeakKeyStrongValueEntry<K, V> copy(ReferenceQueue<K> queueForKeys, MapMakerInternalMap$WeakKeyStrongValueEntry<K, V> newNext) {
      MapMakerInternalMap$WeakKeyStrongValueEntry<K, V> newEntry = new MapMakerInternalMap$WeakKeyStrongValueEntry<>(
         queueForKeys, (K)this.getKey(), this.hash, newNext
      );
      newEntry.setValue(this.value);
    return newEntry;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
