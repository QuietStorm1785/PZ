#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class PeekingIterator {
public:
    virtual ~PeekingIterator() = default;
    E peek();

    E next();

    void remove();
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
