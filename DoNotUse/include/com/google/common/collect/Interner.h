#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class Interner {
public:
    virtual ~Interner() = default;
    E intern(E var1);
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
