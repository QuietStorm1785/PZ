#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class BiMap {
public:
    virtual ~BiMap() = default;
    V put(@Nullable K, @Nullable V);

    V forcePut(@Nullable K, @Nullable V);

    void putAll(Map<? extends, ? extends);

   Set<V> values();

   BiMap<V, K> inverse();
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
