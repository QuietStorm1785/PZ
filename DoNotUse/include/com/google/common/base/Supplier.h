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
namespace base {


class Supplier {
public:
    virtual ~Supplier() = default;
    T get();
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
