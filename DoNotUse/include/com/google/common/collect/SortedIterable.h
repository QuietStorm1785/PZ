#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class SortedIterable {
public:
    virtual ~SortedIterable() = default;
   Comparator<? super T> comparator();

   Iterator<T> iterator();
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
