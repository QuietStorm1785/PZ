#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtCompatible.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class MapConstraint {
public:
    virtual ~MapConstraint() = default;
    void checkKeyValue(@Nullable K, @Nullable V);

    std::string toString();
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
