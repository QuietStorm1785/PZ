#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class CheckedFuture {
public:
    virtual ~CheckedFuture() = default;
    V checkedGet();

    V checkedGet(long var1, TimeUnit var3);
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
