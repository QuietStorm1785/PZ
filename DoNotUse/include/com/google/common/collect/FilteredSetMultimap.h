#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class FilteredSetMultimap {
public:
    virtual ~FilteredSetMultimap() = default;
   SetMultimap<K, V> unfiltered();
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
