#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/MapMakerInternalMap/DummyInternalEntry.h"
#include "com/google/common/collect/MapMakerInternalMap/WeakValueReference.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class MapMakerInternalMap {
public:
    DummyInternalEntry getEntry() {
    return nullptr;
   }

    void clear() {
   }

    void* get() {
    return nullptr;
   }

   public WeakValueReference<Object, Object, DummyInternalEntry> copyFor(ReferenceQueue<Object> queue, DummyInternalEntry entry) {
    return this;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
