#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/MapMakerInternalMap/AbstractStrongKeyEntry.h"
#include "com/google/common/collect/MapMakerInternalMap/StrongValueEntry.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class MapMakerInternalMap {
public:
   : public AbstractStrongKeyEntry<K, V, MapMakerInternalMap$StrongKeyStrongValueEntry<K, V>>
   , public StrongValueEntry<K, V, MapMakerInternalMap$StrongKeyStrongValueEntry<K, V>> {
   private volatile V value = (V)nullptr;

   MapMakerInternalMap$StrongKeyStrongValueEntry(K key, int hash, @Nullable MapMakerInternalMap$StrongKeyStrongValueEntry<K, V> next) {
      super(key, hash, next);
   }

    V getValue() {
      return this.value;
   }

    void setValue(V value) {
      this.value = value;
   }

   MapMakerInternalMap$StrongKeyStrongValueEntry<K, V> copy(MapMakerInternalMap$StrongKeyStrongValueEntry<K, V> newNext) {
      MapMakerInternalMap$StrongKeyStrongValueEntry<K, V> newEntry = new MapMakerInternalMap$StrongKeyStrongValueEntry<>((K)this.key, this.hash, newNext);
      newEntry.value = this.value;
    return newEntry;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
