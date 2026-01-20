#pragma once
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
    virtual ~MapMakerInternalMap() = default;
   WeakValueReference<K, V, E> getValueReference();

    void clearValue();
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
