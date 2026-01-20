#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/MapMakerInternalMap/InternalEntry.h"
#include "com/google/common/collect/MapMakerInternalMap/WeakValueReference.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class MapMakerInternalMap {
public:
    const E entry;

   MapMakerInternalMap$WeakValueReferenceImpl(ReferenceQueue<V> queue, V referent, E entry) {
      super(referent, queue);
      this.entry = entry;
   }

    E getEntry() {
      return this.entry;
   }

   public WeakValueReference<K, V, E> copyFor(ReferenceQueue<V> queue, E entry) {
      return new MapMakerInternalMap$WeakValueReferenceImpl<>(queue, this.get(), entry);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
