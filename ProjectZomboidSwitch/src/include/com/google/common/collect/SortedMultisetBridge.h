#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class SortedMultisetBridge {
public:
    virtual ~SortedMultisetBridge() = default;
   SortedSet<E> elementSet();
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
