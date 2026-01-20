#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class MapDifference {
public:
    virtual ~MapDifference() = default;
    V leftValue();

    V rightValue();

    bool equals(@Nullable Object);

    int hashCode();
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
