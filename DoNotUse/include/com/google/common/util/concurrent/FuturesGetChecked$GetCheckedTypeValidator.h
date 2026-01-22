#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/VisibleForTesting.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class FuturesGetChecked {
public:
    virtual ~FuturesGetChecked() = default;
    void validateClass(Class<? extends);
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
