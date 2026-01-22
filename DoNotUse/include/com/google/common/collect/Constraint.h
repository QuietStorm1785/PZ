#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class Constraint {
public:
    virtual ~Constraint() = default;
    E checkElement(E var1);

    std::string toString();
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
