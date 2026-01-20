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
namespace base {


class Function {
public:
    virtual ~Function() = default;
    T apply(@Nullable F);

    bool equals(@Nullable Object);
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
