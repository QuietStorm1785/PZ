#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/MapMakerInternalMap/InternalEntry.h"
#include "com/google/common/collect/MapMakerInternalMap/Segment.h"
#include "com/google/common/collect/MapMakerInternalMap/Strength.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class MapMakerInternalMap {
public:
    virtual ~MapMakerInternalMap() = default;
    Strength keyStrength();

    Strength valueStrength();

    S newSegment(S> var1, int var2, int var3);

    E newEntry(S var1, K var2, int var3, @Nullable E);

    E copy(S var1, E var2, @Nullable E);

    void setValue(S var1, E var2, V var3);
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
