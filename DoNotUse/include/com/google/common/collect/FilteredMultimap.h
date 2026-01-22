#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Predicate.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class FilteredMultimap {
public:
    virtual ~FilteredMultimap() = default;
   Multimap<K, V> unfiltered();

   Predicate<? super Entry<K, V>> entryPredicate();
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
